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

#include "card_table.h"

#include <algorithm>

namespace ac
{

    card_table::card_table(const card_renderer *pRenderer, bool bRenderOnChange)
        : m_pRenderer(pRenderer),
          m_bRenderOnChange(bRenderOnChange)
    {
        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

    card_table::~card_table() {}

    void card_table::render() const
    {
        if (this->m_pRenderer == nullptr)
            return;

        this->m_pRenderer->render_table();
        for (auto oHolder : this->m_lCards)
        {
            if (oHolder.m_bVisible)
                this->m_pRenderer->render_card(oHolder.m_pCard, oHolder.m_oPos);
        }
    }

    void card_table::render_safe() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->render();
    }

    bool card_table::get_render_on_change() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_bRenderOnChange;
    }

    void card_table::set_render_on_change(bool bRenderOnChange)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->m_bRenderOnChange = bRenderOnChange;
    }

    const card_renderer *card_table::get_renderer_unlocked() const
    {
        return this->m_pRenderer;
    }

    const card_renderer *card_table::get_renderer() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_pRenderer;
    }

    void card_table::set_renderer(const card_renderer *pRenderer)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        this->m_pRenderer = pRenderer;
    }

    std::list<card_holder> card_table::get_holders_unlocked() const
    {
        return this->m_lCards;
    }

    std::list<card_holder> card_table::get_holders() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        return this->m_lCards;
    }

    void card_table::stack_card(const number *pCard, const point &oPos)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if the card is nullptr
        if (pCard == nullptr)
            return;

        // Remove card if already present (all ocurrences)
        this->m_lCards.remove_if([pCard](const card_holder &oHolder)
                                 { return oHolder.m_pCard == pCard; });

        // Add card
        this->m_lCards.emplace_back(pCard, oPos, true);

        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

    void card_table::repace_card(const number *pOriginalCard, const number *pNewCard)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if any card is nullptr
        if (pOriginalCard == nullptr || pNewCard == nullptr)
            return;

        // Replace card (all ocurrences)
        bool bRender = false;
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pOriginalCard)
            {
                oHolder.m_pCard = pNewCard;
                bRender = true;
            }
        }

        // Render
        if (bRender && this->m_bRenderOnChange)
            this->render();
    }

    void card_table::remove_card(const number *pCard)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if the card is nullptr
        if (pCard == nullptr)
            return;
        std::size_t nSize = this->m_lCards.size();

        // Remove card (all ocurrences)
        this->m_lCards.remove_if([pCard](const card_holder &oHolder)
                                 { return oHolder.m_pCard == pCard; });

        // Render
        if (nSize != this->m_lCards.size() && this->m_bRenderOnChange)
            this->render();
    }

    void card_table::remove_all_cards()
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);
        bool bEmpty = this->m_lCards.empty();

        // Clear cards
        this->m_lCards.clear();

        // Render
        if (!bEmpty && this->m_bRenderOnChange)
            this->render();
    }

    bool card_table::has_card(const number *pCard) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return false if the card is nullptr
        if (pCard == nullptr)
            return false;

        // Look for the card
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard)
                return true;
        }

        return false;
    }

    point card_table::get_card_horizontal_position(const number *pCard) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return constant if card is nullptr
        if (pCard == nullptr)
            return YOUR_IMAGINATION;

        // Look for the card
        for (const auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard)
                return oHolder.m_oPos;
        }

        // Return constant if card not found
        return YOUR_IMAGINATION;
    }

    std::size_t card_table::get_card_vertical_positoin(const number *pCard) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return constant if card is nullptr
        if (pCard == nullptr)
            return BEYOND_REACH;

        // Look for the card
        std::size_t nPos = 0;
        for (const auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard)
                return nPos;
            ++nPos;
        }

        // Return constant if card not found
        return BEYOND_REACH;
    }

    std::size_t card_table::get_card_count() const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        return this->m_lCards.size();
    }

    void card_table::shift_horizontal_card(const number *pCard, const point &oPos)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if the card is nullptr
        if (pCard == nullptr)
            return;

        // Update horizontal position (all ocurrences)
        bool bShifted = false;
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard)
            {
                oHolder.m_oPos = oPos;
                bShifted = true;
            }
        }

        // Render
        if (bShifted && this->m_bRenderOnChange)
            this->render();
    }

    void card_table::shift_vertical_card(const number *pCard, std::size_t nPosition)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if the card is nullptr
        if (pCard == nullptr)
            return;

        // Find the card in the list
        auto pIt = std::find_if(m_lCards.begin(), m_lCards.end(),
                                [pCard](const card_holder &oHolder)
                                {
                                    return oHolder.m_pCard == pCard;
                                });

        // If the card is not found, return
        if (pIt == m_lCards.cend())
            return;

        // Store the oHolder to reinsert later
        card_holder oHolder = *pIt;

        // Remove the card from its current position
        m_lCards.erase(pIt);

        // Adjust the new position if pIt is out of bounds
        if (nPosition >= m_lCards.size())
        {
            // If the new position is greater than the current size, place pIt at the end
            nPosition = m_lCards.size();
        }

        // Insert the card at the new position
        auto pInsertPosition = m_lCards.begin();
        std::advance(pInsertPosition, nPosition);
        m_lCards.insert(pInsertPosition, oHolder);

        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

    void card_table::move_card_up(const number *pCard, std::size_t nLayers)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if the card is nullptr
        if (pCard == nullptr)
            return;

        // Find the card in the list
        auto pIt = std::find_if(m_lCards.begin(), m_lCards.end(),
                                [pCard](const card_holder &oHolder)
                                {
                                    return oHolder.m_pCard == pCard;
                                });

        // If the card is not found, return
        if (pIt == m_lCards.end())
            return;

        // Get the current position of the card
        std::size_t nCurrentIndex = std::distance(m_lCards.begin(), pIt);

        // Store the holder to reinsert later
        card_holder oHolder = *pIt;

        // Remove the card from its current position
        m_lCards.erase(pIt);

        // Calculate the new position
        std::size_t nNewIndex = nCurrentIndex + nLayers;
        if (nNewIndex >= m_lCards.size())
        {
            // If the new position is greater than the current size, place pIt at the end
            nNewIndex = m_lCards.size();
        }

        // Insert the card at the new position
        auto pInsertPosition = m_lCards.begin();
        std::advance(pInsertPosition, nNewIndex);
        m_lCards.insert(pInsertPosition, oHolder);

        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

    void card_table::move_card_down(const number *pCard, std::size_t nLayers)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        if (pCard == nullptr)
            return; // Return if the card is nullptr

        // Find the card in the list
        auto pIt = std::find_if(m_lCards.begin(), m_lCards.end(),
                                [pCard](const card_holder &holder)
                                {
                                    return holder.m_pCard == pCard;
                                });

        // If the card is not found, return
        if (pIt == m_lCards.end())
            return;

        // Get the current position of the card
        std::size_t nCurrentIndex = std::distance(m_lCards.begin(), pIt);

        // Store the holder to reinsert later
        card_holder oHolder = *pIt;

        // Remove the card from its current position
        m_lCards.erase(pIt);

        // Ensure the new index does not exceed the bounds of the list
        if (nCurrentIndex > nLayers)
        {
            // Insert the card at the new position
            std::size_t nNewIndex = nCurrentIndex - nLayers;
            auto insertPosition = m_lCards.begin();
            std::advance(insertPosition, nNewIndex);
            m_lCards.insert(insertPosition, oHolder);
        }
        else
        {
            // Insert the card at the new front
            m_lCards.push_front(oHolder);
        }

        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

    void card_table::horizontal_swap_card(const number *pCard1, const number *pCard2)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if any card is nullptr
        if (pCard1 == nullptr || pCard2 == nullptr)
            return;

        card_holder *pHolder1 = nullptr;
        card_holder *pHolder2 = nullptr;

        // Locate the holders
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard1)
                pHolder1 = &oHolder;
            else if (oHolder.m_pCard == pCard2)
                pHolder2 = &oHolder;

            if (pHolder1 != nullptr && pHolder2 != nullptr)
                break;
        }

        // Swap horizontal positions
        if (pHolder1 != nullptr && pHolder2 != nullptr)
        {
            std::swap(pHolder1->m_oPos, pHolder2->m_oPos);
            // Render
            if (this->m_bRenderOnChange)
                this->render();
        }
    }

    void card_table::vertical_swap_card(const number *pCard1, const number *pCard2)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        if (pCard1 == nullptr || pCard2 == nullptr)
            return; // Return if any card is nullptr

        card_holder *pHolder1 = nullptr;
        card_holder *pHolder2 = nullptr;

        // Locate the holders
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard1)
                pHolder1 = &oHolder;
            else if (oHolder.m_pCard == pCard2)
                pHolder2 = &oHolder;

            if (pHolder1 != nullptr && pHolder2 != nullptr)
                break;
        }

        // Swap vertical positions
        if (pHolder1 && pHolder2)
        {
            std::swap(pHolder1->m_pCard, pHolder2->m_pCard);
            // Render
            if (this->m_bRenderOnChange)
                this->render();
        }
    }

    void card_table::full_swap_card(const number *pCard1, const number *pCard2)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return if any card is nullptr
        if (pCard1 == nullptr || pCard2 == nullptr)
            return;

        card_holder *pHolder1 = nullptr;
        card_holder *pHolder2 = nullptr;

        // Locate the holders
        for (auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCard1)
                pHolder1 = &oHolder;
            else if (oHolder.m_pCard == pCard2)
                pHolder2 = &oHolder;

            if (pHolder1 != nullptr && pHolder2 != nullptr)
                break;
        }

        // Swap horizontal positions
        if (pHolder1 != nullptr && pHolder2 != nullptr)
        {
            std::swap(pHolder1->m_oPos, pHolder2->m_oPos);
            std::swap(pHolder1->m_oPos, pHolder2->m_oPos);
            // Render
            if (this->m_bRenderOnChange)
                this->render();
        }
    }

    bool card_table::is_above(const number *pCardAbove, const number *pCardBelow) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return false if any card is nullptr
        if (pCardAbove == nullptr || pCardBelow == nullptr)
            return false;

        // Look for the card
        std::size_t nPos = 0;
        std::size_t nPosAbove = BEYOND_REACH;
        std::size_t nPosBelow = BEYOND_REACH;
        for (const auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCardAbove)
                nPosAbove = nPos;
            else if (oHolder.m_pCard == pCardBelow)
                nPosBelow = nPos;
            ++nPos;

            if (nPosAbove != BEYOND_REACH && nPosBelow != BEYOND_REACH)
                break;
        }

        // pCardAbove is above pCardDown if its vertical position is lesser
        if (nPosAbove != BEYOND_REACH && nPosBelow != BEYOND_REACH)
            return nPosAbove > nPosBelow;
        else
            return false;
    }

    bool card_table::is_bellow(const number *pCardAbove, const number *pCardBelow) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Return false if any card is nullptr
        if (pCardAbove == nullptr || pCardBelow == nullptr)
            return false;

        // Look for the card
        std::size_t nPos = 0;
        std::size_t nPosAbove = BEYOND_REACH;
        std::size_t nPosBelow = BEYOND_REACH;
        for (const auto &oHolder : this->m_lCards)
        {
            if (oHolder.m_pCard == pCardAbove)
                nPosAbove = nPos;
            else if (oHolder.m_pCard == pCardBelow)
                nPosBelow = nPos;
            ++nPos;

            if (nPosAbove != BEYOND_REACH && nPosBelow != BEYOND_REACH)
                break;
        }

        // pCardAbove is above pCardDown if its vertical position is lesser
        if (nPosAbove != BEYOND_REACH && nPosBelow != BEYOND_REACH)
            return nPosAbove < nPosBelow;
        else
            return false;
    }

    bool card_table::is_card_visible(const number *pCard) const
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Find the card in the list
        auto pIt = std::find_if(m_lCards.begin(), m_lCards.end(),
                                [pCard](const card_holder &oHolder)
                                {
                                    return oHolder.m_pCard == pCard;
                                });

        // If the card is not found, return
        if (pIt == m_lCards.cend())
            return false;

        // Return state
        return (*pIt).m_bVisible;
    }

    void card_table::set_card_visible(const number *pCard, bool bVisible)
    {
        std::lock_guard<std::mutex> oLock(this->m_oMutex);

        // Find the card in the list
        auto pIt = std::find_if(m_lCards.begin(), m_lCards.end(),
                                [pCard](const card_holder &oHolder)
                                {
                                    return oHolder.m_pCard == pCard;
                                });

        // If the card is not found, return
        if (pIt == m_lCards.cend())
            return;

        // Return state
        (*pIt).m_bVisible = bVisible;

        // Render
        if (this->m_bRenderOnChange)
            this->render();
    }

}
