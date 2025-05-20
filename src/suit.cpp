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

#include "suit.h"

#include "json.h"
#include <iterator>
#include <sstream>

namespace ac
{

    suit::suit(deck *pDeck, const std::string &sName)
        : m_pDeck(pDeck),
          m_sName(sName),
          m_sDisplayName(sName)
    {
    }

    suit::suit(deck *pDeck, const std::string &sName, const std::string &sDisplayName)
        : m_pDeck(pDeck),
          m_sName(sName),
          m_sDisplayName(sDisplayName)
    {
    }

    suit::~suit()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        for (auto &oIter : this->m_mNumbers)
            delete oIter.second;
        this->m_mNumbers.clear();
    }

    std::string suit::get_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sName;
    }

    std::string suit::get_display_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sDisplayName;
    }

    void suit::set_display_name(const std::string &sDisplayName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->m_sDisplayName = sDisplayName;
    }

    const deck *suit::get_deck() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pDeck;
    }

    deck *suit::get_deck()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pDeck;
    }

    std::vector<const number *> suit::get_numbers() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<const number *> vSuits;
        vSuits.reserve(this->m_mNumbers.size());
        for (auto &oIter : this->m_mNumbers)
            vSuits.push_back(oIter.second);
        return vSuits;
    }

    std::vector<number *> suit::get_numbers()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<number *> vSuits;
        vSuits.reserve(this->m_mNumbers.size());
        for (auto &oIter : this->m_mNumbers)
            vSuits.push_back(oIter.second);
        return vSuits;
    }

    std::size_t suit::get_number_count() const noexcept
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_mNumbers.size();
    }

    number *suit::create_numer(const std::string &sName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mNumbers.find(sName);
        number *pNumber = new number(this, sName);
        if (pIter != this->m_mNumbers.cend())
        {
            delete pIter->second;
            pIter->second = pNumber;
        }
        else
        {
            this->m_mNumbers.insert({sName, pNumber});
        }
        return pNumber;
    }

    number *suit::create_numer(const std::string &sName, const std::string &sDisplayName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mNumbers.find(sName);
        number *pNumber = new number(this, sName, sDisplayName);
        if (pIter != this->m_mNumbers.cend())
        {
            delete pIter->second;
            pIter->second = pNumber;
        }
        else
        {
            this->m_mNumbers.insert({sName, pNumber});
        }
        return pNumber;
    }

    const number *suit::get_number(const std::string &sName) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mNumbers.find(sName);
        if (pIter == this->m_mNumbers.cend())
            return nullptr;
        return pIter->second;
    }

    number *suit::get_number(const std::string &sName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mNumbers.find(sName);
        if (pIter == this->m_mNumbers.cend())
            return nullptr;
        return pIter->second;
    }

    suit *suit::clone() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        suit *pSuit = new suit(this->m_pDeck, this->m_sName, this->m_sDisplayName);
        for (auto &oIter : this->m_mNumbers)
            pSuit->m_mNumbers.insert({oIter.first, oIter.second->clone()});
        return pSuit;
    }

    void suit::to_json(std::ostream &oOstream) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        oOstream << "{ name: ";
        write_json_string(oOstream, this->m_sName);
        oOstream << ", display_name: ";
        write_json_string(oOstream, this->m_sDisplayName);
        oOstream << ", numbers: [ ";

        auto pIter = this->m_mNumbers.cbegin();
        while (pIter != this->m_mNumbers.cend())
        {
            pIter->second->to_json(oOstream);

            if (std::next(pIter) != this->m_mNumbers.cend())
                oOstream.write(", ", 2);

            pIter = std::next(pIter);
        }

        oOstream << " ] }";
    }

    std::string suit::to_json() const
    {
        std::ostringstream oStream;
        this->to_json(oStream);
        return oStream.str();
    }

} // namespace ac
