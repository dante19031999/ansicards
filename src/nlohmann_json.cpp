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

#include "nlohmann_json.h"

#include <nlohmann/json.hpp>

#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace ac
{

    nlohmann_json_item::nlohmann_json_item(std::istream &oIstream)
        : m_pJsonData(nullptr)
    {
        nlohmann::json *pJson = new nlohmann::json();
        oIstream >> *pJson;
        this->m_pJsonData = pJson;
    }

    static inline nlohmann::json *json(void *pJson) { return static_cast<nlohmann::json *>(pJson); }

    static inline const nlohmann::json *cjson(const void *pJson) { return static_cast<const nlohmann::json *>(pJson); }

    nlohmann_json_item::nlohmann_json_item(const void *pJsonData)
        : m_pJsonData(pJsonData) {}

    nlohmann_json_item::~nlohmann_json_item()
    {
        for (auto &oIter : this->m_mReadItems)
            delete json(oIter.second);

        for (auto &oIter1 : this->m_mArrayItems)
            for (auto &oIter2 : oIter1.second)
                delete json(oIter2);

        this->m_mReadItems.clear();
        this->m_mArrayItems.clear();
    }

    const json_item *nlohmann_json_item::get_item(const std::string &sKey) const
    {
        // Search in map
        auto pIter = this->m_mReadItems.find(sKey);
        if (pIter != this->m_mReadItems.cend())
            return pIter->second;

        // Search in object
        if (cjson(this->m_pJsonData)->contains(sKey))
        {
            const nlohmann::json *pJson = &cjson(this->m_pJsonData)->at(sKey);
            if (pJson->is_object())
            {
                nlohmann_json_item *pItem = new nlohmann_json_item(pJson);
                this->m_mReadItems.insert({sKey, pItem});
                return pItem;
            }
        }

        throw std::runtime_error("Json item with key \'" + sKey + "\' not found.");
    }

    std::string nlohmann_json_item::get_string(const std::string &sKey) const
    {
        // Search in object
        if (cjson(this->m_pJsonData)->contains(sKey))
        {
            const nlohmann::json *pJson = &cjson(this->m_pJsonData)->at(sKey);
            if (pJson->is_string())
                return pJson->get<std::string>();
        }

        throw std::runtime_error("String with key \'" + sKey + "\' not found.");
    }

    std::vector<const json_item *> nlohmann_json_item::get_array(const std::string &sKey) const
    {
        // Search in map
        auto pIter = this->m_mArrayItems.find(sKey);
        if (pIter != this->m_mArrayItems.cend())
        {
            std::vector<const json_item *> vItems;
            vItems.reserve(pIter->second.size());

            for (const auto &pChild : pIter->second)
                vItems.push_back(pChild);

            return vItems;
        }

        // Search in object
        if (cjson(this->m_pJsonData)->contains(sKey))
        {
            const nlohmann::json *pJson = &cjson(this->m_pJsonData)->at(sKey);
            if (pJson->is_array())
            {
                std::vector<json_item *> vItems;
                std::vector<const json_item *> vConstItems;

                vItems.reserve(pJson->size());
                for (const auto &oChild : *pJson)
                {
                    nlohmann_json_item *pItem = new nlohmann_json_item(&oChild);
                    vItems.push_back(pItem);
                    vConstItems.push_back(pItem);
                }

                this->m_mArrayItems.insert({sKey, vItems});
                return vConstItems;
            }
        }

        throw std::runtime_error("Json item with key \'" + sKey + "\' not found.");
    }

} // namespace ac
