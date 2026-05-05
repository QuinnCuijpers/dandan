#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"

namespace dandan::core
{
    class PlayCardAction : public IAction
    {
    public:
        PlayCardAction(Card *card, Game *game) : m_card{card}, m_game{game}
        {
        }

        void execute() override
        {
            std::cout << "Playing card: " << m_card->getName() << '\n';
            for (const auto &ability : m_card->getAbilities())
            {
                m_game->getEventManager().subscribe(ability.get());
            }
        }

    private:
        Card *m_card;
        [[maybe_unused]] Game *m_game;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H