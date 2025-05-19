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
 * @file card_renderer.h
 * @brief Declaration of the card_renderer class.
 */

#pragma once

#include "point.h"
#include "number.h"

namespace ac
{
    /**
     * @class card_renderer
     * @brief Abstract base class for rendering cards and tables.
     *
     * This class serves as an abstract interface for rendering cards and tables.
     * Derived classes must implement the methods to provide specific rendering
     * functionality for different types of card representations.
     */
    class card_renderer
    {
    public:
        virtual ~card_renderer();

    public:
        /**
         * @brief Renders a card at a specified position.
         *
         * This method is responsible for rendering a card represented by the
         * given number at the specified position on the screen or output medium.
         *
         * @param pCard Pointer to the card number to be rendered.
         * @param nPos The position where the card should be rendered.
         */
        virtual void render_card(const number *pCard, point nPos) const = 0;

        /**
         * @brief Renders the table.
         *
         * This method is responsible for rendering the table where cards are
         * displayed. It may include the layout and any additional information
         * relevant to the game or display context.
         */
        virtual void render_table() const = 0;
    };

} // namespace ac
