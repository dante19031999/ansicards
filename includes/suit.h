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
 * @file suit.h
 * @brief Declaration of the suit class used for card suits.
 */

#pragma once

#include <number.h>
#include <map>
#include <vector>

namespace ac
{
    class deck; ///< Forward declaration of the deck class.

    /**
     * @class suit
     * @brief Represents a suit in a card game.
     *
     * The suit class encapsulates the properties and behaviors associated with a card suit,
     * including its name, display name, and its association with a deck of cards.
     * This class is apt for multithread programming.
     */
    class suit
    {
        friend class deck; ///< Allows the deck class to access private members of suit.

    public:
        /**
         * @brief Destructor for the suit class.
         */
        virtual ~suit();

    public:
        /**
         * @brief Gets the name of the suit.
         * @return The name of the suit as a string.
         */
        std::string get_name() const;

        /**
         * @brief Gets the display name of the suit.
         * @return The display name of the suit as a string.
         */
        std::string get_display_name() const;

        /**
         * @brief Sets the display name of the suit.
         * @param sDisplayName The new display name to set.
         */
        void set_display_name(const std::string &sDisplayName);

    public:
        /**
         * @brief Gets the deck associated with the suit.
         * @return A pointer to the deck associated with this suit.
         */
        const deck *get_deck() const;

        /**
         * @brief Gets the deck associated with the suit.
         * @return A pointer to the deck associated with this suit.
         */
        deck *get_deck();

    public:
        /**
         * @brief Creates a number with the specified name.
         * @param sName The name of the number to create.
         * @return A pointer to the newly created number.
         */
        number *create_numer(const std::string &sName);

        /**
         * @brief Creates a number with the specified name and display name.
         * @param sName The name of the number to create.
         * @param sDisplayName The display name of the number to create.
         * @return A pointer to the newly created number.
         */
        number *create_numer(const std::string &sName, const std::string &sDisplayName);

    public:
        /**
         * @brief Gets a number by its name.
         * @param sName The name of the number to retrieve.
         * @return A pointer to the number if found, otherwise nullptr.
         */
        const number *get_number(const std::string &sName) const;

        /**
         * @brief Gets a number by its name.
         * @param sName The name of the number to retrieve.
         * @return A pointer to the number if found, otherwise nullptr.
         */
        number *get_number(const std::string &sName);

    public:
        /**
         * @brief Gets a vector of numbers associated with the suit.
         * @return A vector of pointers to the numbers associated with this suit.
         */
        std::vector<const number *> get_numbers() const;

        /**
         * @brief Gets a vector of numbers associated with the suit.
         * @return A vector of pointers to the numbers associated with this suit.
         */
        std::vector<number *> get_numbers();

        /**
         * @brief Gets the total number of numbers currently stored.
         *
         * @return The total number of numbers stored.
         */
        std::size_t get_number_count() const noexcept;

    public:
        /**
         * @brief Serializes the object to JSON format and writes it to the output stream.
         *
         * @param oOstream The output stream to which the JSON representation will be written.
         */
        void to_json(std::ostream &oOstream) const;

        /**
         * @brief Serializes the object to JSON format and returns the output string.
         *
         * @return Output as string
         */
        std::string to_json() const;

    private:
        deck *m_pDeck;                              ///< Pointer to the deck associated with the suit.
        std::string m_sName;                        ///< The name of the suit.
        std::string m_sDisplayName;                 ///< The display name of the suit.
        std::map<std::string, number *> m_mNumbers; ///< Map of numbers associated with the suit.
        mutable std::mutex m_oMutex;                ///< Mutex for multithread applications

    private:
        /**
         * @brief Constructor to create a suit with a deck and name.
         * @param pDeck Pointer to the associated deck.
         * @param sName The name of the suit.
         */
        suit(deck *pDeck, const std::string &sName);

        /**
         * @brief Constructor to create a suit with a deck, name, and display name.
         * @param pDeck Pointer to the associated deck.
         * @param sName The name of the suit.
         * @param sDisplayName The display name of the suit.
         */
        suit(deck *pDeck, const std::string &sName, const std::string &sDisplayName);

    private:
        /**
         * @brief Clones the current suit object.
         * @return A pointer to a new suit object that is a copy of this one.
         */
        suit *clone() const;
    };

} // namespace ac
