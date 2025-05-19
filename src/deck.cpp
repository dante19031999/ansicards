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

#include <sstream>
#include <iostream>
#include <array>

namespace ac
{

    static std::array<std::string, 4> aPokerNames = {
        "heart", "diamond", "club", "spade"};

    static std::array<std::string, 4> aPokerDisplays = {
        "\u2665", "\u2666", "\u2663", "\u2660"};

    static std::array<std::string, 4> aSpanishNames = {
        "gold", "cup", "club", "sword"};

    static std::array<std::string, 4> aSpanishDisplays = {
        "\U0001F3C5", "\U0001F3C6", "\U0001F3CF", "\U00002694"};

    deck *deck::generate_poker_deck(std::size_t nJokers)
    {
        deck *pDeck = new deck("poker_deck", "Poker deck");
        for (std::size_t nPos = 0; nPos < 4; ++nPos)
        {
            suit *pSuit = pDeck->create_suit(aPokerNames[nPos], aPokerDisplays[nPos]);
            pSuit->create_numer("1", "A");
            for (std::size_t nNumber = 2; nNumber < 11; ++nNumber)
                pSuit->create_numer(std::to_string(nNumber));
            pSuit->create_numer("11", "J");
            pSuit->create_numer("12", "Q");
            pSuit->create_numer("13", "K");
        }
        suit *pJokers = pDeck->create_suit("joker", "Joker");
        for (std::size_t nCount = 0; nCount < nJokers; ++nCount)
            pJokers->create_numer(std::to_string(nCount), "J");
        return pDeck;
    }

    deck *deck::generate_spanish_deck(std::size_t nJokers)
    {
        deck *pDeck = new deck("spanish_deck", "Spanish Deck");
        for (std::size_t nPos = 0; nPos < 4; ++nPos)
        {
            suit *pSuit = pDeck->create_suit(aSpanishNames[nPos], aSpanishDisplays[nPos]);
            pSuit->create_numer("1", "A");
            for (std::size_t nNumber = 2; nNumber < 8; ++nNumber)
                pSuit->create_numer(std::to_string(nNumber));
            pSuit->create_numer("8", "S");
            pSuit->create_numer("9", "C");
            pSuit->create_numer("10", "R");
        }
        suit *pJokers = pDeck->create_suit("joker", "Joker");
        for (std::size_t nCount = 0; nCount < nJokers; ++nCount)
            pJokers->create_numer(std::to_string(nCount), "J");
        return pDeck;
    }

    deck::deck(const std::string &sName)
        : m_sName(sName),
          m_sDisplayName(sName)
    {
    }

    deck::deck(const std::string &sName, const std::string &sDisplayName)
        : m_sName(sName),
          m_sDisplayName(sDisplayName)
    {
    }

    deck::~deck()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        for (auto &oIter : this->m_mSuits)
            delete oIter.second;
        this->m_mSuits.clear();
    }

    std::string deck::get_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sName;
    }

    std::string deck::get_display_name() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_sDisplayName;
    }

    void deck::set_display_name(const std::string &sDisplayName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->m_sDisplayName = sDisplayName;
    }

    std::vector<const suit *> deck::get_suits() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<const suit *> vSuits;
        vSuits.reserve(this->m_mSuits.size());
        for (auto &oIter : this->m_mSuits)
            vSuits.push_back(oIter.second);
        return vSuits;
    }

    std::vector<suit *> deck::get_suits()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<suit *> vSuits;
        vSuits.reserve(this->m_mSuits.size());
        for (auto &oIter : this->m_mSuits)
            vSuits.push_back(oIter.second);
        return vSuits;
    }

    std::size_t deck::get_suit_count()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_mSuits.size();
    }

    suit *deck::create_suit(const std::string &sName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        suit *pSuit = new suit(this, sName);
        auto pIter = this->m_mSuits.find(sName);
        if (pIter != this->m_mSuits.cend())
        {
            delete pIter->second;
            pIter->second = pSuit;
        }
        else
        {
            this->m_mSuits.insert({sName, pSuit});
        }
        return pSuit;
    }

    suit *deck::create_suit(const std::string &sName, const std::string &sDisplayName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        suit *pSuit = new suit(this, sName, sDisplayName);
        auto pIter = this->m_mSuits.find(sName);
        if (pIter != this->m_mSuits.cend())
        {
            delete pIter->second;
            pIter->second = pSuit;
        }
        else
        {
            this->m_mSuits.insert({sName, pSuit});
        }
        return pSuit;
    }

    const suit *deck::get_suit(const std::string &sName) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mSuits.find(sName);
        if (pIter == this->m_mSuits.cend())
            return nullptr;
        return pIter->second;
    }

    suit *deck::get_suit(const std::string &sName)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        auto pIter = this->m_mSuits.find(sName);
        if (pIter == this->m_mSuits.cend())
            return nullptr;
        return pIter->second;
    }

    std::vector<const number *> deck::get_numbers() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<const number *> vNumbers;
        for (auto oIter : this->m_mSuits)
        {
            const suit *pSuit = oIter.second;
            std::vector<const number *> vSuitNumbers = pSuit->get_numbers();
            vNumbers.insert(vNumbers.end(), vSuitNumbers.begin(), vSuitNumbers.end());
        }
        return vNumbers;
    }

    std::vector<number *> deck::get_numbers()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::vector<number *> vNumbers;
        for (auto oIter : this->m_mSuits)
        {
            suit *pSuit = oIter.second;
            std::vector<number *> vSuitNumbers = pSuit->get_numbers();
            vNumbers.insert(vNumbers.end(), vSuitNumbers.begin(), vSuitNumbers.end());
        }
        return vNumbers;
    }

    std::size_t deck::get_number_count()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        std::size_t nNumbers = 0;
        for (auto oIter : this->m_mSuits)
            nNumbers += oIter.second->get_number_count();
        return nNumbers;
    }

    deck *deck::clone() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        deck *pDeck = new deck(this->m_sName, this->m_sDisplayName);
        for (auto &oIter : this->m_mSuits)
            pDeck->m_mSuits.insert({oIter.first, oIter.second->clone()});
        return pDeck;
    }

    void deck::copy(const deck *pDeck)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Do not relock itself
        if (pDeck == this)
            return;

        // Lock the copied deck
        std::lock_guard<std::mutex> oLockCopy(pDeck->m_oMutex);

        // Perform copy
        for (auto &oIter : this->m_mSuits)
            this->m_mSuits.insert({oIter.first, oIter.second->clone()});
    }

    void deck::to_json(std::ostream &oOstream) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        oOstream << "deck: { name: ";
        oOstream << this->m_sName;
        oOstream << ", display_name: ";
        oOstream << this->m_sDisplayName;
        oOstream << ", suits: ";

        auto pIter = this->m_mSuits.cbegin();
        while (pIter != this->m_mSuits.cend())
        {
            pIter->second->to_json(oOstream);

            if (std::next(pIter) != this->m_mSuits.cend())
                oOstream.write(", ", 2);

            pIter = std::next(pIter);
        }

        oOstream << " ] }";
    }

    std::string deck::to_json() const
    {
        std::ostringstream oStream;
        this->to_json(oStream);
        return oStream.str();
    }

} // namespace ac
