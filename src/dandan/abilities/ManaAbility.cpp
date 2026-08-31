#include "dandan/abilities/ManaAbility.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Game.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaList.h"
#include <memory>

namespace dandan::abilities
{
    ManaAbility::ManaAbility(mana::ManaList manaList)
        : m_mana_list(std::move(manaList))
    {
    }

    ManaAbility::ManaAbility(std::unique_ptr<costs::ICost> cost,
                             mana::ManaList manaList)
        : m_cost(std::move(cost)), m_mana_list(std::move(manaList))
    {
    }

    std::string ManaAbility::displayOption(size_t index) const
    {
        std::string res{};
        res += m_cost->display();
        res += "Add ";
        auto option{m_mana_list.getOptions().at(index)};
        res += mana::ManaBag::ManaToSymbols(option);
        return res;
    }

    std::string ManaAbility::display() const
    {
        std::string res{};
        res += m_cost->display();
        res += "Add ";

        assert(!getManaList().getOptions().empty() &&
               "Mana List was empty when trying to display ManaAbility");
        const auto mana{m_mana_list.getOptions().at(0)};
        res += mana::ManaBag::ManaToSymbols(mana);

        for (size_t i{1}; i < m_mana_list.getOptions().size(); ++i)
        {
            res += " or ";
            const auto mana_option{m_mana_list.getOptions().at(i)};
            res += mana::ManaBag::ManaToSymbols(mana_option);
        }
        return res;
    }

    [[nodiscard]] const mana::ManaList &ManaAbility::getManaList() const
    {
        return m_mana_list;
    }

    [[nodiscard]] const costs::ICost *ManaAbility::getCost() const

    {
        return m_cost.get();
    }

    std::unique_ptr<effects::IOneShotEffect> ManaAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        effects::EffectContext effect_context{context.source_card_id,
                                              context.controller_id};
        m_cost->pay(exec_ctx, context);
        if (context.chosen_mode_index.has_value())
        {
            const auto &option =
                m_mana_list.getOptions()[context.chosen_mode_index.value()];
            return std::make_unique<effects::AddManaEffect>(option,
                                                            effect_context);
        }

        return std::make_unique<effects::AddManaEffect>(
            m_mana_list.getOptions()[0], effect_context);
    }

    [[nodiscard]] bool ManaAbility::canActivate(
        core::ExecutionContext exec_ctx, const AbilityContext &context) const
    {
        if (m_cost)
        {
            auto *source{(exec_ctx.cards.get())[context.source_card_id]};
            return m_cost->canPay(*source, exec_ctx.state.get().getPlayer(
                                               source->getControllerID()));
        }
        return true;
    }

    [[nodiscard]] size_t ManaAbility::optionsAmount() const
    {
        return m_mana_list.getOptions().size();
    }

} // namespace dandan::abilities
