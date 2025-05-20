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

#include "card.h"

namespace ac
{

    card::card(const number *pNumber)
        : m_pNumber(pNumber) {}

    bool card::operator==(const card &oCard) const noexcept
    {
        return this->m_pNumber == oCard.m_pNumber;
    }

    bool card::operator!=(const card &oCard) const noexcept
    {
        return this->m_pNumber == oCard.m_pNumber;
    }

    std::weak_ordering card::operator<=>(const card &oCard) const
    {
        return this->compare(oCard);
    }

    card::operator const number *() const noexcept
    {
        return this->m_pNumber;
    }

    const number *card::get_number()
    {
        return this->m_pNumber;
    }

} // namespace ac
