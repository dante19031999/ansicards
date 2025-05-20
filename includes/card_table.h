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
 * @file card_table.h
 * @brief Declaration of the card_table class used for managing cards on a table.
 */

#pragma once

#include <list>
#include "card_renderer.h"
#include "card_holder.h"

namespace ac
{
    class number; ///< Forward declaration of the card class.

    /**
     * @class card_table
     * @brief Represents a table for stacking and managing cards.
     *
     * The card_table class provides methods for placing, moving, and checking the position
     * of cards on a table. It does not own the cards; the owner is responsible for freeing them.
     * Each card can only be placed once; to display a card multiple times, it must be cloned.
     */
    class card_table
    {
    public:
        /**
         * @brief Constructs a card_table object.
         *
         * @param pRenderer A pointer to a card_renderer object. If nullptr, no renderer is set.
         * @param bRenderOnChange A boolean value indicating if rendering should occur on change. Default is true.
         */
        card_table(const card_renderer *pRenderer = nullptr, bool bRenderOnChange = true);

        /**
         * @brief Destructs a card_table object.
         */
        virtual ~card_table();

    protected:
        /**
         * @brief Renders the card table.
         *
         * This is a virtual function that may be overwritten by derived classes.
         * This method isn't protetected by the mutex, as it needs to be called from multiple sources.
         * If a protetected version is need, please use render_safe();
         */
        virtual void render() const;

    public:
        /**
         * @brief Renders the card table.
         *
         * This method is protetected by the mutex.
         * May be called at will.
         */
        void render_safe() const;

    public:
        /**
         * @brief Checks if rendering occurs on change.
         *
         * @return true if rendering is enabled on change, false otherwise.
         */
        bool get_render_on_change() const;

        /**
         * @brief Sets whether rendering should occur on change.
         *
         * @param bRenderOnChange A boolean value indicating if rendering should occur on change.
         */
        void set_render_on_change(bool bRenderOnChange);

        /**
         * @brief Gets the current card renderer.
         *
         * @return A pointer to the current card_renderer object.
         */
        const card_renderer *get_renderer() const;

        /**
         * @brief Sets the card renderer.
         *
         * @param pRenderer A pointer to a card_renderer object to be set. This function is const.
         */
        void set_renderer(const card_renderer *pRenderer);

        /**
         * @brief Gets the card holders.
         *
         * @param pRenderer A list of card holders.
         */
        std::list<card_holder> get_holders() const;

    protected:
        /**
         * @brief Gets the current card renderer.
         * This version does not lock the mutex.
         * To use from card_table::render.
         *
         * @return A pointer to the current card_renderer object.
         */
        const card_renderer *get_renderer_unlocked() const;

        /**
         * @brief Gets the card holders.
         *
         * @param pRenderer A list of card holders.
         * This version does not lock the mutex.
         * To use from card_table::render.
         */
        std::list<card_holder> get_holders_unlocked() const;

    public:
        /**
         * @brief Places a card on the table at the specified position.
         *
         * If the class is already present, it sets it on top.
         * @param pCard Pointer to the card to be placed.
         * @param oPos The position where the card should be placed.
         */
        void stack_card(const number *pCard, const point &oPos);

        /**
         * @brief Replaces an original card with a new card if the original is found.
         * @param pOriginalCard Pointer to the original card to be replaced.
         * @param pNewCard Pointer to the new card to place.
         */
        void repace_card(const number *pOriginalCard, const number *pNewCard);

        /**
         * @brief Removes a card from the table if it is found.
         * @param pCard Pointer to the card to be removed.
         */
        void remove_card(const number *pCard);

        /**
         * @brief Removes all cards from the table if it is found.
         */
        void remove_all_cards();

    public:
        /**
         * @brief Checks if a specific card is present on the table.
         * @param pCard Pointer to the card to check.
         * @return True if the card is present, false otherwise.
         */
        bool has_card(const number *pCard) const;

        /**
         * @brief Gets the horizontal position of a card on the table.
         * @param pCard Pointer to the card to find.
         * @return The horizontal position of the card, or constant YOUR_IMAGINATION if not found.
         */
        point get_card_horizontal_position(const number *pCard) const;

        /**
         * @brief Gets the vertical position of a card on the table.
         * @param pCard Pointer to the card to find.
         * @return The vertical position of the card, or constant BEYOND_REACH if not found.
         */
        std::size_t get_card_vertical_positoin(const number *pCard) const;

        /**
         * @brief Gets the total number of cards currently on the table.
         *
         * @return The total number of cards on the table.
         */
        std::size_t get_card_count() const;

    public:
        /**
         * @brief Shifts a card horizontally to a new position if it is found.
         * @param pCard Pointer to the card to shift.
         * @param oPos The new position for the card.
         */
        void shift_horizontal_card(const number *pCard, const point &oPos);

        /**
         * @brief Shifts a card vertically to a new position if it is found.
         *
         * If the new vertical position is outside the bounds of the table, the card will be placed
         * at the lowest position if moving down, or at the top position if moving up.
         * @param pCard Pointer to the card to shift.
         * @param nPosition The new vertical position for the card.
         */
        void shift_vertical_card(const number *pCard, std::size_t nPosition);

        /**
         * @brief Moves a card up by a specified number of layers if it is found.
         *
         * If the resulting position is above the top of the table, the card will be placed at the top position.
         * @param pCard Pointer to the card to move.
         * @param nLayers The number of layers to move the card up.
         */
        void move_card_up(const number *pCard, std::size_t nLayers);

        /**
         * @brief Moves a card down by a specified number of layers if it is found.
         *
         * If the resulting position is below the lowest position of the table, the card will be placed at the lowest position.
         * @param pCard Pointer to the card to move.
         * @param nLayers The number of layers to move the card down.
         */
        void move_card_down(const number *pCard, std::size_t nLayers);

    public:
        /**
         * @brief Swaps the horizontal positions of two cards.
         *
         * If either card is not found on the table, this operation does nothing.
         * @param pCard1 Pointer to the first card.
         * @param pCard2 Pointer to the second card.
         */
        void horizontal_swap_card(const number *pCard1, const number *pCard2);

        /**
         * @brief Swaps the vertical positions of two cards.
         *
         * If either card is not found on the table, this operation does nothing.
         * @param pCard1 Pointer to the first card.
         * @param pCard2 Pointer to the second card.
         */
        void vertical_swap_card(const number *pCard1, const number *pCard2);

        /**
         * @brief Swaps the positions of two cards, both horizontally and vertically.
         *
         * If either card is not found on the table, this operation does nothing.
         *
         * @param pCard1 Pointer to the first card.
         * @param pCard2 Pointer to the second card.
         */
        void full_swap_card(const number *pCard1, const number *pCard2);

    public:
        /**
         * @brief Checks if one card is above another on the table.
         *
         * If either card is not found on the table, this operation returns false.
         * @param pCardAbove Pointer to the card that is expected to be above.
         * @param pCardBelow Pointer to the card that is expected to be below.
         * @return True if pCardAbove is above pCardBelow, false otherwise.
         */
        bool is_above(const number *pCardAbove, const number *pCardBelow) const;

        /**
         * @brief Checks if one card is below another on the table.
         *
         * If either card is not found on the table, this operation returns false.
         * @param pCardAbove Pointer to the card that is expected to be above.
         * @param pCardBelow Pointer to the card that is expected to be below.
         * @return True if pCardAbove is below pCardBelow, false otherwise.
         */
        bool is_bellow(const number *pCardAbove, const number *pCardBelow) const;

    public:
        /**
         * @brief Checks if a specific card is visible.
         *
         * This function checks the visibility status of a card represented by the
         * given number. If the card is not on the table, the function returns false
         * and does nothing.
         *
         * @param pNumber A pointer to a `number` object representing the card.
         * @return true if the card is visible, false if the card is not on the table
         *         or if it is hidden.
         */
        bool is_card_visible(const number *pCard) const;

        /**
         * @brief Sets the visibility status of a specific card.
         *
         * This function sets the visibility status of a card represented by the
         * given number. If the card is not on the table, the function does nothing.
         *
         * @param pNumber A pointer to a `number` object representing the card.
         * @param bVisible A boolean value indicating the visibility status to set.
         *                 Pass true to make the card visible, or false to hide it.
         *                 If the card is not on the table, this function will do nothing.
         */
        void set_card_visible(const number *pCard, bool bVisible);

    protected:
        mutable std::mutex m_oMutex; ///< Mutex for multithread applications

    private:
        std::list<card_holder> m_lCards;  ///< List of cards on the table.
        const card_renderer *m_pRenderer; ///< Renderer for the card table
        bool m_bRenderOnChange;           ///< Render table when it changes
    };

} // namespace ac
