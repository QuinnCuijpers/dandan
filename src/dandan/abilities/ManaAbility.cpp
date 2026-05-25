#include "dandan/abilities/ManaAbility.h"
#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/mana/Mana.h"
#include "dandan/mana/ManaList.h"
#include <memory>

namespace dandan::abilities
{

    std::unique_ptr<effects::IOneShotEffect> ManaAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        m_cost->pay(game, context);
        if (context.chosen_mode_index.has_value())
        {
            const auto &option =
                m_mana_list.getOptions()[context.chosen_mode_index.value()];
            return std::make_unique<effects::AddManaEffect>(option->getMana());
        }

        return std::make_unique<effects::AddManaEffect>(
            m_mana_list.getOptions()[0]->getMana());
    }

    [[nodiscard]] bool ManaAbility::canActivate(core::Game &game,
                                                AbilityContext context) const
    {
        if (m_cost)
        {
            auto *source{game.getCardByID(context.source_card_id)};
            return m_cost->canPay(*source,
                                  game.getPlayer(source->getControllerID()));
        }
        return true;
    }

} // namespace dandan::abilities