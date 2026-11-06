#include "dandan/abilities/IAbility.h"
#include <stdexcept>

namespace dandan::abilities
{
    std::string IAbility::display() const
    {
        throw std::runtime_error("Unimplemented display for " +
                                 std::string(typeid(*this).name()));
    }

    std::string IAbility::displayOption([[maybe_unused]] size_t index) const
    {
        throw std::runtime_error("Unimplemented display option for ability " +
                                 std::string(typeid(*this).name()));
    }

    bool IAbility::canActivate(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] const AbilityContext &context) const
    {
        return false;
    }

    size_t IAbility::optionsAmount() const
    {
        throw std::runtime_error("Unimplemented options count for ability " +
                                 std::string(typeid(*this).name()));
    }
} // namespace dandan::abilities
