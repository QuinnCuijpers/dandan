#ifndef DANDAN_TARGETREQUIREMENT_H
#define DANDAN_TARGETREQUIREMENT_H

#include <algorithm>
#include <cstdint>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>
namespace dandan::core
{

    /** @brief The kinds of objects or players that can be targeted. */
    enum class TargetType : uint8_t
    {
        /// A player.
        Player,
        /// A creature permanent.
        Creature,
        /// A land permanent.
        Land,
        /// Any permanent.
        Permanent,
        /// A spell on the stack.
        Spell,
        /// A planeswalker permanent.
        Planeswalker,
        /// A card in any zone.
        Card,
        /// Any valid target.
        Any,
    };

    /** @brief Restricts which player may control a target. */
    enum class Controller : uint8_t
    {
        /// The controller of the source must control the target.
        You,
        /// An opponent of the controller must control the target.
        Opponent,
        /// Any player may control the target.
        Any,
    };

    /** @brief Describes where a target is chosen from. */
    enum class TargetSource : uint8_t
    {
        /// The target is chosen interactively when the effect resolves.
        Prompt,
        /// The target is read from a previously linked choice.
        Linked,
    };

    /** Converts a target type to a human-readable string.
     * @param target_type The target type to convert.
     * @return The string representation of the target type.
     */
    std::string targetTypeToString(TargetType target_type);

    /** Writes a target type to a stream.
     * @param ostream The stream to write to.
     * @param target_type The target type to write.
     * @return The stream.
     */
    std::ostream &operator<<(std::ostream &ostream, TargetType target_type);

    struct TargetSpec
    {
        std::vector<TargetType> types;
        Controller controller{Controller::Any};
        TargetSource source{TargetSource::Prompt};
        std::optional<std::string> key;

        explicit TargetSpec(std::vector<TargetType> types,
                            Controller controller = Controller::Any);

        TargetSpec(std::vector<TargetType> types, const std::string &key,
                   Controller controller = Controller::Any);
    };

    class TargetRequirement
    {
    public:
        explicit TargetRequirement(const std::vector<TargetSpec> &target_types);

        explicit TargetRequirement(
            const std::vector<std::vector<TargetType>> &target_types);

        [[nodiscard]] const std::vector<TargetSpec> &getTargetTypes() const;

    private:
        std::vector<TargetSpec> m_targets;
    };
} // namespace dandan::core

#endif
