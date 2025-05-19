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
 * @file number.h
 * @brief Declaration of the number class used for card numbers.
 */

#pragma once

#include <string>
#include <mutex>

namespace ac
{
    class suit; ///< Forward declaration of the suit class.
    class deck; ///< Forward declaration of the deck class.

    /**
     * @class number
     * @brief Represents a card number in a card game.
     *
     * The number class encapsulates the properties and behaviors associated with a card number,
     * including its name, display name, and its association with a suit and deck.
     * This class is apt for multithread programming.
     */
    class number
    {
        friend class suit; ///< Allows the suit class to access private members of number.

    public:
        /**
         * @brief Destructor for the number class.
         */
        virtual ~number();

    public:
        /**
         * @brief Gets the name of the card number.
         * @return The name of the card number as a string.
         */
        std::string get_name() const;

        /**
         * @brief Gets the display name of the card number.
         * @return The display name of the card number as a string.
         */
        std::string get_display_name() const;

        /**
         * @brief Sets the display name of the card number.
         * @param sDisplayName The new display name to set.
         */
        void set_display_name(const std::string &sDisplayName);

    public:
        /**
         * @brief Gets the suit associated with the card number.
         * @return A pointer to the suit associated with this card number.
         */
        const suit *get_suit() const;

        /**
         * @brief Gets the suit associated with the card number.
         * @return A pointer to the suit associated with this card number.
         */
        suit *get_suit();

    public:
        /**
         * @brief Gets the deck associated with the card number.
         * @return A pointer to the deck associated with this card number.
         */
        const deck *get_deck() const;

        /**
         * @brief Gets the deck associated with the card number.
         * @return A pointer to the deck associated with this card number.
         */
        deck *get_deck();

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
        suit *m_pSuit;               ///< Pointer to the suit associated with the card number.
        std::string m_sName;         ///< The name of the card number.
        std::string m_sDisplayName;  ///< The display name of the card number.
        mutable std::mutex m_oMutex; ///< Mutex for multithread applications

    private:
        /**
         * @brief Constructor to create a number with a suit and name.
         * @param pSuit Pointer to the associated suit.
         * @param sName The name of the card number.
         */
        number(suit *pSuit, const std::string &sName);

        /**
         * @brief Constructor to create a number with a suit, name, and display name.
         * @param pSuit Pointer to the associated suit.
         * @param sName The name of the card number.
         * @param sDisplayName The display name of the card number.
         */
        number(suit *pSuit, const std::string &sName, const std::string &sDisplayName);

    private:
        /**
         * @brief Clones the current number object.
         * @return A pointer to a new number object that is a copy of this one.
         */
        number *clone() const;
    };

} // namespace ac
