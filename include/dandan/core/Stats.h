#ifndef DANDAN_STATS_H
#define DANDAN_STATS_H

namespace dandan::core
{
    /** @brief A struct to hold the stats (power and toughness) of a creature
     * card.
     * @struct Stats
     */
    struct Stats
    {
        /// The power of the creature. Defaults to 0.
        int power{0};
        /// The toughness of the creature, defaults to 1 as creatures with 0
        /// toughness are immediately put into the graveyard.
        int toughness{1};
    };
} // namespace dandan::core

#endif
