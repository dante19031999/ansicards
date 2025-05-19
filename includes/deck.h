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
 * @file deck.h
 * @brief Declaration of the deck class used for card decks.
 */

#pragma once

#include "suit.h"

namespace ac
{
    /**
     * @class deck
     * @brief Represents a deck of cards in a card game.
     *
     * The deck class encapsulates the properties and behaviors associated with a deck of cards,
     * including its name, display name, and its collection of suits.
     * This class is apt for multithread programming.
     */
    class deck
    {
    public:
        /**
         * @brief Generates a standard poker deck of cards.
         *
         * This function creates a standard poker deck consisting of 52 cards,
         * optionally including a specified number of jokers.
         *
         * @param nJokers The number of jokers to include in the deck. Default is 0.
         * @return A pointer to a dynamically allocated deck containing the cards.
         *         The caller is responsible for freeing the allocated memory.
         */
        static deck *generate_poker_deck(std::size_t nJokers = 0);

        /**
         * @brief Generates a Spanish deck of cards.
         *
         * This function creates a Spanish deck consisting of 40 or 48 cards,
         * depending on whether the full deck is requested, and optionally includes
         * a specified number of jokers.
         *
         * @param nJokers The number of jokers to include in the deck. Default is 0.
         * @return A pointer to a dynamically allocated deck containing the cards.
         *         The caller is responsible for freeing the allocated memory.
         */
        static deck *generate_spanish_deck(std::size_t nJokers = 0);

    public:
        /**
         * @brief Constructor to create a deck with a name.
         * @param sName The name of the deck.
         */
        deck(const std::string &sName);

        /**
         * @brief Constructor to create a deck with a name and display name.
         * @param sName The name of the deck.
         * @param sDisplayName The display name of the deck.
         */
        deck(const std::string &sName, const std::string &sDisplayName);

        /**
         * @brief Destructor for the deck class.
         */
        virtual ~deck();

    public:
        /**
         * @brief Gets the name of the deck.
         * @return The name of the deck as a string.
         */
        std::string get_name() const;

        /**
         * @brief Gets the display name of the deck.
         * @return The display name of the deck as a string.
         */
        std::string get_display_name() const;

        /**
         * @brief Sets the display name of the deck.
         * @param sDisplayName The new display name to set.
         */
        void set_display_name(const std::string &sDisplayName);

    public:
        /**
         * @brief Creates a suit with the specified name.
         * @param sName The name of the suit to create.
         * @return A pointer to the newly created suit.
         */
        suit *create_suit(const std::string &sName);

        /**
         * @brief Creates a suit with the specified name and display name.
         * @param sName The name of the suit to create.
         * @param sDisplayName The display name of the suit to create.
         * @return A pointer to the newly created suit.
         */
        suit *create_suit(const std::string &sName, const std::string &sDisplayName);

    public:
        /**
         * @brief Gets a suit by its name.
         * @param sName The name of the suit to retrieve.
         * @return A pointer to the suit if found, otherwise nullptr.
         */
        const suit *get_suit(const std::string &sName) const;

        /**
         * @brief Gets a suit by its name.
         * @param sName The name of the suit to retrieve.
         * @return A pointer to the suit if found, otherwise nullptr.
         */
        suit *get_suit(const std::string &sName);

    public:
        /**
         * @brief Gets a vector of suits associated with the deck.
         * @return A vector of pointers to the suits associated with this deck.
         */
        std::vector<const suit *> get_suits() const;

        /**
         * @brief Gets a vector of suits associated with the deck.
         * @return A vector of pointers to the suits associated with this deck.
         */
        std::vector<suit *> get_suits();

        /**
         * @brief Gets the total number of suits currently stored.
         *
         * @return The total number of numbers stored.
         */
        std::size_t get_suit_count();

    public:
        /**
         * @brief Gets a vector of suits associated with the deck.
         * @return A vector of pointers to the suits associated with this deck.
         */
        std::vector<const number *> get_numbers() const;

        /**
         * @brief Gets a vector of suits associated with the deck.
         * @return A vector of pointers to the suits associated with this deck.
         */
        std::vector<number *> get_numbers();

        /**
         * @brief Gets the total number of numbers currently stored.
         *
         * @return The total number of numbers stored.
         */
        std::size_t get_number_count();

    public:
        /**
         * @brief Clones the current deck object.
         *
         * Custom logic may be used to clone the object.
         * Use deck::copy in order to acquire the deck data.
         * @return A pointer to a new deck object that is a copy of this one.
         */
        virtual deck *clone() const;

        /**
         * @brief Copies the deck object into the current deck object.
         *
         * @return A pointer to a new deck object that is a copy of this one.
         */
        void copy(const deck *pDeck);

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
        std::string m_sName;                    ///< The name of the deck.
        std::string m_sDisplayName;             ///< The display name of the deck.
        std::map<std::string, suit *> m_mSuits; ///< Map of suits associated with the deck.
        mutable std::mutex m_oMutex;            ///< Mutex for multithread applications
    };

} // namespace ac
