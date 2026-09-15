#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/engine/ConditionManager.h"
#include "dandan/core/engine/EventManager.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/core/engine/ReplacementManager.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/CastEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"

namespace dandan::core
{

    PlayCardAction::PlayCardAction(CastRequest req) : m_cast_request{req}
    {
    }

    [[nodiscard]] CardID PlayCardAction::getCardID() const
    {
        return m_cast_request.card_id;
    }

    std::unique_ptr<effects::IOneShotEffect> PlayCardAction::createEffect(
        core::ExecutionContext exec_ctx)
    {
        const auto &card_registry{exec_ctx.cards.get()};
        auto &prevention_manager{exec_ctx.prevention_manager.get()};
        auto &replacement_manager{exec_ctx.replacement_manager.get()};
        auto &event_manager{exec_ctx.event_manager.get()};
        auto &condition_manager{exec_ctx.condition_manager.get()};

        auto *card{card_registry.get(m_cast_request.card_id)};

        auto cast = CastContext::resolveCast(m_cast_request, exec_ctx);

        const auto &data = card->getData();

        std::cout << "Playing card: " << data.name << '\n';

        for (auto &ability : card->getCurrentAbilities())
        {
            event_manager.subscribe(ability);

            replacement_manager.subscribe(ability);

            prevention_manager.subscribe(ability);

            condition_manager.addStateTriggeredAbility(&ability);
        }

        effects::EffectContext context{card->getControllerID()};

        // lands dont use the stack and thus immediately enter
        switch (data.type)
        {
        case Type::Land:
            return std::make_unique<effects::ETBEffect>(*card, context);

        case Type::Creature:
        case Type::Sorcery:
        case Type::Instant:
            return std::make_unique<effects::CastEffect>(cast, context);

        default:
            throw std::runtime_error(
                "Only land/creature cards can be played for now");
        }
    }
} // namespace dandan::core
