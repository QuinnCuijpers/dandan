#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/effects/one_shot/PlayCardEffect.h"

namespace dandan::core
{

    std::unique_ptr<effects::IOneShotEffect> PlayCardAction::createEffect()
    {
        // lands dont use the stack and their effects are applied
        // immediately
        const auto &data = m_card.getData();
        if (data.getType() == CardData::Type::Land)
        {
            std::cout << "Playing card: " << data.getName() << '\n';
            m_game.eventManager().subscribe(m_card);

            for (const auto &ability : m_card.getData().getAbilities())
            {
                if (const auto *static_ability =
                        dynamic_cast<const abilities::StaticAbility *>(
                            ability.get()))
                {
                    if (static_ability->getType() ==
                        abilities::StaticAbility::Type::Replacement)
                    {
                        const auto *replacement_ability =
                            dynamic_cast<const effects::IReplacementEffect *>(
                                static_ability->getEffect());
                        std::cout << "Subscribing replacement ability to "
                                     "replacement manager\n";
                        m_game.replacementManager().subscribe(
                            replacement_ability);
                    }
                }
            }
            std::cout << m_game.eventManager().size()
                      << " effects subscribed\n";
            // lands dont use the stack and thus immediately enter
            return std::make_unique<effects::ETBEffect>(m_card);
        }

        // add paying mana cost
        // add moving onto the stack
        if (data.getType() == CardData::Type::Creature)
        {
            std::cout << "Playing card: " << data.getName() << '\n';
            return std::make_unique<effects::PlayCardEffect>(m_card);
        }

        throw std::runtime_error(
            "Only land/creature cards can be played for now");
    }
} // namespace dandan::core