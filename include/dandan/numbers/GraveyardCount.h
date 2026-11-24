#ifndef DANDAN_GRAVEYARDCOUNT_H
#define DANDAN_GRAVEYARDCOUNT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    /** @brief Counts cards with a given name in a graveyard.
     * @class GraveyardCount
     * @implements INumber
     */
    class GraveyardCount : public INumber
    {
    public:
        /** Constructs a count for the given card name.
         * @param name The card name to count.
         */
        explicit GraveyardCount(std::string name);

        /** Gets the card name being counted.
         * @return A const reference to the card name.
         */
        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] int getValue(
            core::ExecutionContext exec_ctx,
            [[maybe_unused]] effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

    private:
        std::string m_name;
    };
} // namespace dandan::numbers


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::numbers;
    using namespace dandan::serialization;

    inline const auto registeredGraveyardCount = []
    {
        NumberRegistry::instance().registerType<GraveyardCount>(
            "GraveyardCount",
            [](const INumber *number)
            {
                auto json = nlohmann::json::object();
                const auto *graveyard_count{
                    dynamic_cast<const GraveyardCount *>(number),};
                json["card_name"] = graveyard_count->getName();
                return json;
            },
            [](const nlohmann::json &json)
            {
                std::string name = json.at("card_name").get<std::string>();
                return std::make_unique<GraveyardCount>(name);
            });
        return true;
    }();
} // namespace
#endif

#endif // DANDAN_GRAVEYARDCOUNT_H
