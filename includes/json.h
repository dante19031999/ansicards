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
 * @file json.h
 * @brief Declaration of some json tools for card decks.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace ac
{

    /**
     * @brief Writes an escaped version of a string to the output stream.
     *
     * This function takes a string and writes it to the provided output stream,
     * escaping special characters and converting non-printable characters to their
     * hexadecimal representation in the format \xHH, where HH is the hexadecimal
     * value of the character.
     * The final string is enclosed by \".
     *
     * @param oOstream The output stream to which the escaped string will be written.
     * @param sString The string to be escaped and written.
     */
    void write_json_string(std::ostream &oOstream, const std::string &sString);

    /**
     * @class json_item
     * @brief Interface for parsing JSON data.
     *
     * This class serves as an interface for handling JSON items. It provides
     * methods to retrieve JSON items, strings, and arrays based on a given key.
     */
    class json_item
    {
    public:
        /**
         * @brief Retrieves a JSON item associated with the specified key.
         *
         * @param sKey The key for which to retrieve the JSON item.
         * @return A pointer to the JSON item associated with the key, or nullptr if not found.
         */
        virtual const json_item *get_item(const std::string &sKey) const = 0;

        /**
         * @brief Retrieves a string value associated with the specified key.
         *
         * @param sKey The key for which to retrieve the string value.
         * @return The string value associated with the key.
         */
        virtual std::string get_string(const std::string &sKey) const = 0;

        /**
         * @brief Retrieves an array of JSON items associated with the specified key.
         *
         * @param sKey The key for which to retrieve the array of JSON items.
         * @return A vector of pointers to the JSON items associated with the key.
         */
        virtual std::vector<const json_item *> get_array(const std::string &sKey) const = 0;
    };

} // namespace ac
