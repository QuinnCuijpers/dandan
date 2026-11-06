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

    enum class TargetType : uint8_t
    {
        Player,
        Creature,
        Land,
        Permanent,
        Spell,
        Planeswalker,
        Card,
        Any,
    };

    enum class Controller : uint8_t
    {
        You,
        Opponent,
        Any,
    };

    enum class TargetSource : uint8_t
    {
        Prompt,
        Linked,
    };

    std::string targetTypeToString(TargetType target_type);

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
