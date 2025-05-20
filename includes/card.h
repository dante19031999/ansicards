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
 * @file card.h
 * @brief Declaration of the card class used for representing cards.
 *
 * This file contains the definition of the `card` class, which is used to represent
 * a playing card in the context of the AnsiCards application. The class provides
 * functionality for comparing cards and managing their associated number.
 */

#pragma once

#include "deck.h"

#include <compare>
#include <list>
#include <vector>

namespace ac
{

    /**
     * @class card
     * @brief Represents a playing card.
     *
     * The `card` class encapsulates the properties and behaviors of a playing card,
     * including its associated number. It supports copy and move semantics, as well
     * as equality comparison between cards.
     */
    class card
    {
    public:
        /**
         * @brief Constructs a card with the specified number.
         * @param pNumber A pointer to the number associated with the card.
         */
        card(const number *pNumber);

    public:
        /**
         * @brief Copy constructor.
         * @param other The card to copy from.
         */
        card(const card &) = default;

        /**
         * @brief Move constructor.
         * @param other The card to move from.
         */
        card(card &&) = default;

    public:
        /**
         * @brief Copy assignment operator.
         * @param other The card to copy from.
         * @return A reference to this card.
         */
        card &operator=(const card &) = default;

        /**
         * @brief Move assignment operator.
         * @param other The card to move from.
         * @return A reference to this card.
         */
        card &operator=(card &&) = default;

    public:
        /**
         * @brief Compares this card with another card for equality.
         * @param oCard The card to compare with.
         * @return True if the cards are equal, false otherwise.
         */
        bool operator==(const card &oCard) const noexcept;

        /**
         * @brief Compares this card with another card for inequality.
         * @param oCard The card to compare with.
         * @return True if the cards are not equal, false otherwise.
         */
        bool operator!=(const card &oCard) const noexcept;

        /**
         * @brief Compares this card with another card for inequality.
         * @param oCard The card to compare with.
         * @return True if the cards are not equal, false otherwise.
         */
        std::weak_ordering operator<=>(const card &oCard) const;

    public:
        /**
         * @brief Converts this card to a pointer to const number.
         *
         * This conversion operator allows an instance of the `card` class to be
         * implicitly converted to a pointer of type `const number*`. This is useful
         * for passing the card's associated number to functions that expect a pointer
         * to a `number`.
         *
         * @return A pointer to the `const number` associated with this card.
         */
        operator const number *() const noexcept;

    public:
        /**
         * @brief Compares this card with another card.
         *
         * This function performs a comparison between this card and another card
         * and returns a weak ordering result. The comparison is intended to be
         * used for sorting or ordering cards.
         *
         * @param oCard The card to compare with.
         * @return A `std::weak_ordering` value indicating the relative order of the cards:
         *         - `std::weak_ordering::less` if this card is less than `oCard`,
         *         - `std::weak_ordering::greater` if this card is greater than `oCard`,
         *         - `std::weak_ordering::equivalent` if the cards are considered equivalent.
         */
        virtual std::weak_ordering compare(const card &oCard) const = 0;

    public:
        /**
         * @brief Retrieves the number associated with this card.
         *
         * This function returns a pointer to the `number` object that is associated
         * with this card. The caller is responsible for managing the lifetime of the
         * returned pointer.
         *
         * @return A pointer to the `number` associated with this card.
         *         Returns `nullptr` if no number is associated.
         */
        const number *get_number();

    public:
        /**
         * @brief Generates a deck of cards as a vector.
         *
         * This static template function creates a complete deck of cards based on the provided
         * deck and returns it as a `std::vector`. The deck includes all standard
         * playing cards. The card type must have a constructor that accepts a pointer to
         * `number`.
         *
         * @tparam card_t The type of card to be generated. This type must have a constructor
         *                 of the form `card_t(const number*)`.
         * @param pDeck A pointer to the `deck` object that serves as the basis for
         *              generating the card deck.
         * @return A `std::vector` containing all the cards in the generated deck.
         */
        template <typename card_t>
        static std::vector<card_t> generate_deck_as_vector(const deck *pDeck);

        /**
         * @brief Generates a deck of cards as a list.
         *
         * This static template function creates a complete deck of cards based on the provided
         * deck and returns it as a `std::list`. The deck includes all standard
         * playing cards. The card type must have a constructor that accepts a pointer to
         * `number`.
         *
         * @tparam card_t The type of card to be generated. This type must have a constructor
         *                 of the form `card_t(const number*)`.
         * @param pDeck A pointer to the `deck` object that serves as the basis for
         *              generating the card deck.
         * @return A `std::list` containing all the cards in the generated deck.
         */
        template <typename card_t>
        static std::list<card_t> generate_deck_as_list(const deck *pDeck);

    private:
        const number *m_pNumber; ///< Pointer to the number associated with the card.
    };

    template <typename card_t>
    std::vector<card_t> card::generate_deck_as_vector(const deck *pDeck)
    {
        std::vector<card_t> vCards;

        if (pDeck == nullptr)
            return vCards;

        std::vector<const number *> vNums = pDeck->get_numbers();
        vCards.reserve(vNums.size());

        for (const number *pNum : vNums)
            vCards.emplace_back(pNum);

        return vCards;
    }

    template <typename card_t>
    std::list<card_t> card::generate_deck_as_list(const deck *pDeck)
    {
        std::list<card> lCards;

        if (pDeck == nullptr)
            return lCards;

        std::vector<const number *> vNums = pDeck->get_numbers();

        for (const number *pNum : vNums)
            lCards.emplace_back(pNum);

        return lCards;
    }

} // namespace ac
