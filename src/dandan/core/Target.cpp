#include "dandan/core/Target.h"
#include "dandan/utils/overloadVisitor.h"
#include <ostream>

namespace dandan::core
{
    std::ostream &operator<<(std::ostream &ostream, const Target &target)
    {
        std::visit(
            utils::overloaded{
                [&ostream](const abilities::BoundAbility &bound_ability)
                {
                    ostream << "BoundAbility: "
                            << bound_ability.definition().display();
                },
                [&ostream](const PlayerID player_id)
                { ostream << "Player with ID: " << player_id.id(); },
                [&ostream](const CardID card_id)
                { ostream << "Card with ID: " << card_id.getID(); }},
            target);
        return ostream;
    }
} // namespace dandan::core