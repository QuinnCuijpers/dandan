#include "dandan/effects/one_shot/CastEffect.h"
#include <utility>

namespace dandan::effects::impl
{
    void choose_targets(core::Card *cardp,
                        const effects::IOneShotEffectDefinition &effect,
                        core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        auto choices = std::vector<core::Target>{};
        if (const auto *targets = effect.getTargetRequirement())
        {
            for (const auto &target_types : targets->getTargetTypes())
            {
                {
                    auto valid_targets = std::vector<core::Target>{};
                    for (const auto &target_type : target_types.types)
                    {
                        auto new_valid_targets = game.getValidTargets(
                            exec_ctx, target_type, target_types.controller);

                        valid_targets.insert(valid_targets.end(),
                                             new_valid_targets.begin(),
                                             new_valid_targets.end());
                    }

                    if (valid_targets.empty())
                    {
                        throw std::runtime_error(
                            "No valid targets for this effect");
                    }

                    for (size_t i = 0; i < valid_targets.size(); ++i)
                    {
                        std::cout << i << ": " << valid_targets[i] << '\n';
                    }
                    std::cout << "Choose a target (0-"
                              << valid_targets.size() - 1 << "): ";
                    std::string target_input;
                    std::getline(istream, target_input);
                    int target_choice = std::stoi(target_input);
                    auto target{valid_targets.at(target_choice)};
                    choices.push_back(target);
                }
                cardp->addTargetChoices(effect, choices);
            }
        }
    }

    IOneShotEffectDefinition *choose_mode(
        core::Card *cardp, const ModalEffectDefinition &modal_effect,
        core::ExecutionContext exec_ctx)
    {
        auto &istream{exec_ctx.input_manager.get().stream()};

        std::cout << modal_effect.display();
        std::cout << "Choose an option (0-"
                  << modal_effect.getOptions().size() - 1 << "): ";
        std::string input;
        std::getline(istream, input);
        int choice = std::stoi(input);
        if (choice < 0 ||
            choice >= static_cast<int>(modal_effect.getOptions().size()))
        {
            throw std::runtime_error("Invalid choice for modal effect");
        }
        cardp->addModalChoice(modal_effect, choice);

        auto *chosen_effect{modal_effect.getOptions()[choice].get()};
        return chosen_effect;
    }
} // namespace dandan::effects::impl

namespace dandan::effects
{
    CastEffect::CastEffect(core::CastContext cast_ctx, EffectContext context)
        : IOneShotEffect(std::move(context)), m_cast_ctx(std::move(cast_ctx))
    {
    }

    std::unique_ptr<IOneShotEffect> CastEffect::copy() const
    {
        return std::make_unique<CastEffect>(m_cast_ctx, getEffectContext());
    }

    std::unique_ptr<events::IEvent> CastEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &priority_manager{exec_ctx.priority_manager.get()};

        auto *card{card_registry.get(m_cast_ctx.card_id)};

        std::cout << "Applying PlayCardEffect\n";
        auto &prio_player{
            game.getPlayer(priority_manager.getPlayerWithPriority()),
        };

        auto mana_cost{m_cast_ctx.cost};

        std::cout << "generic_mana: " << mana_cost.generic() << '\n';
        std::cout << "specific_mana: " << mana_cost.specific() << '\n';
        std::cout << "mana_pool: " << prio_player.manaPool() << '\n';
        if (prio_player.manaPool().canPay(mana_cost))
        {
            prio_player.manaPool().pay(mana_cost);
        }
        else
        {
            throw std::runtime_error("Not enough mana to play card " +
                                     std::string{card->getData().name});
        }

        if (card->getData().type == core::Type::Instant ||
            card->getData().type == core::Type::Sorcery)
        {
            auto spell_ability_it{
                std::find_if(
                    card->getData().abilities.begin(),
                    card->getData().abilities.end(),
                    [](const auto &ability)
                    {
                        return dynamic_cast<const abilities::SpellAbility *>(
                                   ability.get()) != nullptr;
                    }),
            };

            if (spell_ability_it == card->getData().abilities.end())
            {
                throw std::runtime_error("Instant or sorcery card does not "
                                         "have a spell ability");
            }
            const auto &spell_ability =
                dynamic_cast<const abilities::SpellAbility *>(
                    spell_ability_it->get());
            for (const auto &effect : spell_ability->effects())
            {
                if (const auto *modal_effect =
                        dynamic_cast<const ModalEffectDefinition *>(
                            effect.get()))
                // choose mode
                {
                    const auto *chosen_effect =
                        impl::choose_mode(card, *modal_effect, exec_ctx);
                    std::cout << "Chosen effect: " << chosen_effect->display()
                              << '\n';
                    impl::choose_targets(card, *chosen_effect, exec_ctx);
                }
                else
                {
                    impl::choose_targets(card, *effect, exec_ctx);
                }
            }
        }

        game.moveCardFromZone(game.getPlayer(card->getControllerID()), *card);
        card->setZone(core::Zone::STACK);
        game.stack().push(m_cast_ctx);
        return nullptr;
    }
} // namespace dandan::effects
