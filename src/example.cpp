/*
 * This file is part of AnsiCards.
 *
 * AnsiCards is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AnsiCards is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AnsiCards.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2025 Dante Doménech Martínez
 */

#include "deck.h"
#include "ansi_card_renderer.h"
#include "ansi_card_table.h"

#include <iostream>

namespace ac
{

    namespace example
    {

        static void display_suit(ansi_card_table *pTable, suit *pSuit, std::size_t x, std::size_t y);
        static void display_deck(ansi_card_table *pTable, deck *pDeck, std::size_t x, std::size_t y);
        static void display_suit_joker(ansi_card_table *pTable, suit *pSuit, std::size_t x, std::size_t y);

        void display_poker_deck()
        {
            // Generate deck with four jokers
            deck *pDeck = deck::generate_poker_deck(4);

            // Create the renderer
            ansi_card_renderer *pRenderer = new ansi_card_renderer();

            // Create the table
            ansi_card_table *pTable = new ansi_card_table(pRenderer, true);

            // Try to "reserve space" in the terminal for the table
            ansi::reserve_ansi_terminal(pRenderer->get_table_width(), pRenderer->get_table_height());

            // Display the deck
            display_deck(pTable, pDeck, 1, 1);

            // Free allocated stuff
            delete pTable;
            delete pRenderer;
            delete pDeck;

            // Go to end of table
            ansi::move_ansi_cursor(0, pRenderer->get_table_height());

            // User interface
            std::cout << "This is the poker deck." << std::endl;
            std::cout << "Press any key to continue...";
            std::cin.get();
            ansi::clear_screen();
        }

        void display_spanish_deck()
        {
            // Generate deck with four jokers
            deck *pDeck = deck::generate_spanish_deck(4);

            // Create the renderer
            ansi_card_renderer *pRenderer = new ansi_card_renderer();

            // Create the table
            ansi_card_table *pTable = new ansi_card_table(pRenderer, true);

            // Try to "reserve space" in the terminal for the table
            ansi::reserve_ansi_terminal(pRenderer->get_table_width(), pRenderer->get_table_height());

            // Display the deck
            display_deck(pTable, pDeck, 1, 1);

            // Free allocated stuff
            delete pTable;
            delete pRenderer;
            delete pDeck;

            // Go to end of table
            ansi::move_ansi_cursor(0, pRenderer->get_table_height());

            // User interface
            std::cout << "This is the spanish deck." << std::endl;
            std::cout << "Press any key to continue...";
            std::cin.get();
            ansi::clear_screen();
        }

        void display_suit(ansi_card_table *pTable, suit *pSuit, std::size_t x, std::size_t y)
        {
            // Get the number count
            std::size_t nCount = pSuit->get_number_count();

            // Get the renderer from the table
            const ansi_card_renderer *pRenderer = static_cast<const ansi_card_renderer *>(pTable->get_renderer());

            // Calculate the distance between cards (horzontal)
            std::size_t nStep = pRenderer->get_card_width() + 1;

            // Iterate all numbers in the suit
            for (std::size_t nPos = 0; nPos < nCount; ++nPos)
            {
                // Get the card by number
                number *pCard = pSuit->get_number(std::to_string(nPos + 1));

                // Display the card
                pTable->stack_card(pCard, point(x + nPos * nStep, y));
            }
        }

        void display_suit_joker(ansi_card_table *pTable, suit *pSuit, std::size_t x, std::size_t y)
        {
            // Get the jokers
            std::vector<number *> vNums = pSuit->get_numbers();

            // Get the renderer from the table
            const ansi_card_renderer *pRenderer = static_cast<const ansi_card_renderer *>(pTable->get_renderer());

            // Calculate the distance between cards (horzontal)
            std::size_t nStep = pRenderer->get_card_width() + 1;

            // Iterate all numbers in the suit
            for (std::size_t nPos = 0; nPos < vNums.size(); ++nPos)
            {
                // Display the card
                pTable->stack_card(vNums[nPos], point(x + nPos * nStep, y));
            }
        }

        void display_deck(ansi_card_table *pTable, deck *pDeck, std::size_t x, std::size_t y)
        {
            // Disable render on change (so as not to refresh untill fully painted)
            pTable->set_render_on_change(false);

            // Get the suits
            std::vector<suit *> vSuits = pDeck->get_suits();

            // Get the renderer from the table
            const ansi_card_renderer *pRenderer = static_cast<const ansi_card_renderer *>(pTable->get_renderer());

            // Calculate the distance between cards (vertical)
            std::size_t nStep = pRenderer->get_card_height() + 1;

            // Variable to count the suit number
            std::size_t nPos = 0;

            // Joker suit (if available)
            suit *pJoker = nullptr;

            // Iterate suits
            for (suit *pSuit : vSuits)
            {
                if (pSuit->get_name() == "joker")
                {
                    // Keep joker suit for last
                    pJoker = pSuit;
                }
                else
                {
                    // Display the suit
                    display_suit(pTable, pSuit, x, y + nPos * nStep);

                    // Increase the suit count
                    ++nPos;
                }
            }

            // Display joker suit if available
            if (pJoker != nullptr)
                display_suit_joker(pTable, pJoker, x, y + nPos * nStep);

            // Reenable display on change
            pTable->set_render_on_change(true);

            // Render the table
            pTable->render_safe();
        }

    } // namespace example

} // namespace ac
