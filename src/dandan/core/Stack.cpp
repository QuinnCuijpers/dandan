#include "dandan/core/Stack.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/overloadVisitor.h"
#include <memory>

namespace dandan::core
{
    void Stack::resolveNext(core::Game &game)
    {
        if (m_stack.empty())
        {
            return;
        }

        auto object{m_stack.back()};

        std::cout << "Resolving object on stack\n";
        m_stack.pop_back();

        auto effect{std::visit(
            overloaded{
                [](Card &card) -> std::unique_ptr<effects::IOneShotEffect>
                { return std::make_unique<effects::ETBEffect>(card); },
                [&game](const abilities::BoundAbility &ability)
                    -> std::unique_ptr<effects::IOneShotEffect>
                { return ability.createEffect(game); }},
            object)};
    }
} // namespace dandan::core