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

#include "number.h"

#include "suit.h"
#include "deck.h"
#include "json.h"

#include <sstream>

namespace ac
{

    number::number(suit *pSuit, const std::string &sName)
        : m_pSuit(pSuit),
          m_sName(sName),
          m_sDisplayName(sName)
    {
    }

    number::number(suit *pSuit, const std::string &sName, const std::string &sDisplayName)
        : m_pSuit(pSuit),
          m_sName(sName),
          m_sDisplayName(sDisplayName)

    {
    }

    number::~number()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
    }

    std::string number::get_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sName;
    }

    std::string number::get_display_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sDisplayName;
    }

    void number::set_display_name(const std::string &sDisplayName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->m_sDisplayName = sDisplayName;
    }

    const suit *number::get_suit() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pSuit;
    }

    suit *number::get_suit()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pSuit;
    }

    const deck *number::get_deck() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pSuit->get_deck();
    }

    deck *number::get_deck()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pSuit->get_deck();
    }

    number *number::clone() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return new number(this->m_pSuit, this->m_sName, this->m_sDisplayName);
    }

    void number::to_json(std::ostream &oOstream) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        oOstream << "{ name: ";
        write_json_string(oOstream, this->m_sName);
        oOstream << ", display_name: ";
        write_json_string(oOstream, this->m_sDisplayName);
        oOstream << " }";
    }

    std::string number::to_json() const
    {
        std::ostringstream oStream;
        this->to_json(oStream);
        return oStream.str();
    }

} // namespace ac
