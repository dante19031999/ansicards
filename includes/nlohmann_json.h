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
 * @file nlohmann_json.h
 * @brief An implementatio of the json tools for card decks using the library nlohmann_json.
 */

#pragma once

#include "json.h"
#include <map>

namespace ac
{

    /**
     * @class nlohmann_json_item
     * @brief Implementation of json_item using the nlohmann_json library.
     *
     * This class provides an implementation of the json_item interface using
     * the nlohmann_json library for JSON parsing. It manages JSON data and
     * provides methods to retrieve items, strings, and arrays from the JSON structure.
     */
    class nlohmann_json_item : public json_item
    {
    public:
        /**
         * @brief Constructs a nlohmann_json_item from an input stream.
         *
         * This constructor initializes the JSON item by reading from the provided
         * input stream.
         *
         * @param oIstream The input stream from which to read the JSON data.
         */
        nlohmann_json_item(std::istream &oIstream);

        /**
         * @brief Destructor for nlohmann_json_item.
         *
         * This destructor cleans up any allocated resources and destroys all
         * subitems associated with this JSON item.
         */
        virtual ~nlohmann_json_item();

        /**
         * @brief Retrieves a JSON item associated with the specified key.
         *
         * This method overrides the get_item method from the json_item interface
         * to return a JSON item corresponding to the given key.
         *
         * @param sKey The key for which to retrieve the JSON item.
         * @return A pointer to the JSON item associated with the key, or nullptr if not found.
         */
        virtual const json_item *get_item(const std::string &sKey) const override;

        /**
         * @brief Retrieves a string value associated with the specified key.
         *
         * This method overrides the get_string method from the json_item interface
         * to return a string value corresponding to the given key.
         *
         * @param sKey The key for which to retrieve the string value.
         * @return The string value associated with the key.
         */
        virtual std::string get_string(const std::string &sKey) const override;

        /**
         * @brief Retrieves an array of JSON items associated with the specified key.
         *
         * This method overrides the get_array method from the json_item interface
         * to return an array of JSON items corresponding to the given key.
         *
         * @param sKey The key for which to retrieve the array of JSON items.
         * @return A vector of pointers to the JSON items associated with the key.
         */
        virtual std::vector<const json_item *> get_array(const std::string &sKey) const override;

    private:
        const void *m_pJsonData;                                               ///< Pointer to the JSON data managed by this item.
        mutable std::map<std::string, json_item *> m_mReadItems;               ///< Map of read JSON items by key.
        mutable std::map<std::string, std::vector<json_item *>> m_mArrayItems; ///< Map of array items by key.

        /**
         * @brief Private constructor for creating a nlohmann_json_item from raw JSON data.
         *
         * This constructor is used internally to create a nlohmann_json_item
         * from a pointer to JSON data.
         *
         * @param pJsonData Pointer to the raw JSON data.
         */
        nlohmann_json_item(const void *pJsonData);
    };

} // namespace ac
