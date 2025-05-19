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

/**
 * @file example.h
 * @brief Contains example code for this library.
 */

namespace ac
{

    namespace example
    {

        /**
         * @brief Displays a standard poker deck.
         *
         * This function renders all 52 cards of a standard poker deck
         * in the terminal using ANSI escape codes for styling. The cards
         * are displayed in a user-friendly format, allowing players to
         * visualize the deck easily.
         *
         * @note This function does not return any value and is intended
         *       for visual output only.
         */
        void display_poker_deck();

        /**
         * @brief Displays a Spanish deck of cards.
         *
         * This function renders a Spanish deck, which typically consists
         * of 40 or 48 cards, depending on the variant used. The cards are
         * displayed in the terminal using ANSI escape codes for styling.
         * This function is useful for games that utilize the Spanish deck.
         *
         * @note This function does not return any value and is intended
         *       for visual output only.
         */
        void display_spanish_deck();

    } // namespace example

} // namespace ac
