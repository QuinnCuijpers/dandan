#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/effects/IReplacementEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::abilities {

class ReplacementAbility : public IAbility {
public:
  ReplacementAbility() = default;
  ReplacementAbility(
      std::unique_ptr<dandan::events::IEvent> event,
      std::unique_ptr<dandan::effects::IReplacementEffect> replace_effect)
      : m_event(std::move(event)), m_replace_effect(std::move(replace_effect)) {
  }

  void resolve() override;

  const dandan::events::IEvent *getEvent() const { return m_event.get(); }
  const dandan::effects::IReplacementEffect *getReplaceEffect() const {
    return m_replace_effect.get();
  }

private:
  std::unique_ptr<dandan::events::IEvent> m_event;
  std::unique_ptr<dandan::effects::IReplacementEffect> m_replace_effect;
};
} // namespace dandan::abilities

#endif