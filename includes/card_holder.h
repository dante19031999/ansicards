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
 * @file card_holder.h
 * @brief Declaration of the card_holder class used for helping the management of cards on a table.
 */

#pragma once

#include "number.h"
#include "point.h"

namespace ac
{

    /**
     * @struct card_holder
     * @brief A structure to hold card information and its position.
     *
     * This structure contains the x and y coordinates of the card and a pointer to the card itself.
     */
    class card_holder
    {
    public:
        const number *m_pCard; ///< Pointer to the card.
        point m_oPos;          ///< The horizontal coordinate of the card.
        bool m_bVisible;       ///< Visibility of the card.

    public:
        /**
         * @brief Default copy constructor.
         *
         * This constructor creates a new card_holder object as a copy of an existing one.
         *
         * @param other The card_holder object to copy.
         */
        card_holder(const card_holder &) = default;

        /**
         * @brief Parameterized constructor.
         *
         * This constructor initializes a card_holder with the specified position, card pointer, and visibility.
         *
         * @param oPos The position of the card.
         * @param pCard Pointer to the card.
         * @param bVisible The visibility status of the card.
         */
        card_holder(const number *pCard, point oPos, bool bVisible);

        /**
         * @brief Default copy assignment operator.
         *
         * This operator assigns the values from one card_holder object to another.
         *
         * @param other The card_holder object to assign from.
         * @return Reference to the current object.
         */
        card_holder &operator=(const card_holder &) = default;

        /**
         * @brief Default move assignment operator.
         *
         * This operator moves the values from one card_holder object to another.
         *
         * @param other The card_holder object to move from.
         * @return Reference to the current object.
         */
        card_holder &operator=(card_holder &&) = default;
    };

} // namespace ac