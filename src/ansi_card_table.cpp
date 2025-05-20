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

#include "ansi_card_table.h"

namespace ac
{

    const ansi_card_renderer *ansi_card_table::DEFAULT_RENDERER = new ansi_card_renderer();

    static inline const ansi_card_renderer *renderer(const ansi_card_renderer *pRenderer)
    {
        return pRenderer != nullptr ? pRenderer : ansi_card_table::DEFAULT_RENDERER;
    }

    ansi_card_table::ansi_card_table(const ansi_card_renderer *pRenderer, bool bRenderOnChange)
        : card_table(renderer(pRenderer), bRenderOnChange) {}

    void ansi_card_table::set_renderer(const ansi_card_renderer *pRenderer)
    {
        card_table::set_renderer(renderer(pRenderer));
    }

} // namespace ac
