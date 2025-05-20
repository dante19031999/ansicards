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
 * @file ansi_card_table.h
 * @brief Declaration of the ansi_card_table class.
 */

#pragma once

#include "card_table.h"
#include "ansi_card_renderer.h"

namespace ac
{

    /**
     * @class ansi_card_table
     * @brief Represents a card table that uses ANSI rendering.
     *
     * The ansi_card_table class extends the card_table class and provides
     * functionality to render cards using an ANSI card renderer. It allows
     * for setting a custom renderer or using a default one.
     */
    class ansi_card_table : public card_table
    {
    public:
        static const ansi_card_renderer *DEFAULT_RENDERER; ///< A constant pointer to the default ANSI card renderer.

    public:
        /**
         * @brief Constructs an ansi_card_table object.
         *
         * @param pRenderer A pointer to an ansi_card_renderer object. If nullptr, DEFAULT_RENDERER is used.
         * @param bRenderOnChange A boolean value indicating if rendering should occur on change. Default is true.
         */
        ansi_card_table(const ansi_card_renderer *pRenderer = nullptr, bool bRenderOnChange = true);

        /**
         * @brief Sets the card renderer.
         *
         * @param pRenderer A pointer to an ansi_card_renderer object to be set. This function is const.
         *                  If it is null, DEFAULT_RENDERER is set.
         */
        void set_renderer(const ansi_card_renderer *pRenderer);

    };

} // namespace ac
