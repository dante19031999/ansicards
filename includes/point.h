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
 * @file point.h
 * @brief Declaration of the point class used for representing a point in a 2D space.
 */

#pragma once

#include <limits>

namespace ac
{

    /**
     * @class point
     * @brief Represents a point in a 2D space with x and y coordinates.
     *
     * The point class encapsulates the properties and behaviors associated with a point,
     * including its x and y coordinates, and provides methods for comparison and retrieval
     * of these coordinates.
     */
    class point
    {
        friend class card_table; ///< Allows the card_table class to access private members of point.

    public:
        /**
         * @brief Constructs a point with specified x and y coordinates.
         * @param nX The x coordinate of the point.
         * @param nY The y coordinate of the point.
         */
        constexpr point(std::size_t nX, std::size_t nY) : m_nX(nX), m_nY(nY) {}

        /**
         * @brief Copy constructor for the point class.
         * @param oPoint The point to copy.
         */
        constexpr point(const point &oPoint) = default;

        /**
         * @brief Move constructor for the point class.
         * @param oPoint The point to move.
         */
        constexpr point(point &&oPoint) = default;

    public:
        /**
         * @brief Copy assignment operator for the point class.
         * @param oPoint The point to copy.
         * @return A reference to this point.
         */
        point &operator=(const point &oPoint) = default;

        /**
         * @brief Move assignment operator for the point class.
         * @param oPoint The point to move.
         * @return A reference to this point.
         */
        point &operator=(point &&oPoint) = default;

    public:
        /**
         * @brief Compares this point with another point for equality.
         * @param oPoint The point to compare with.
         * @return True if the points are equal, false otherwise.
         */
        constexpr bool operator==(const point &oPoint) const;

        /**
         * @brief Compares this point with another point for inequality.
         * @param oPoint The point to compare with.
         * @return True if the points are equal, false otherwise.
         */
        constexpr bool operator!=(const point &oPoint) const;

    public:
        /**
         * @brief Gets the x coordinate of the point.
         * @return The x coordinate as a size_t.
         */
        constexpr std::size_t get_x() const;

        /**
         * @brief Gets the y coordinate of the point.
         * @return The y coordinate as a size_t.
         */
        constexpr std::size_t get_y() const;

    private:
        std::size_t m_nX; ///< The x coordinate of the point.
        std::size_t m_nY; ///< The y coordinate of the point.
    };

    /// Constant representing a value beyond reach.
    constexpr std::size_t BEYOND_REACH = std::numeric_limits<std::size_t>::max();

    /// Constant representing a point defined by the maximum size_t values.
    constexpr point YOUR_IMAGINATION = point(BEYOND_REACH, BEYOND_REACH);

    constexpr bool point::operator==(const point &oPoint) const
    {
        return this->m_nX == oPoint.m_nX && this->m_nY == oPoint.m_nY;
    }

    constexpr bool point::operator!=(const point &oPoint) const
    {
        return this->m_nX != oPoint.m_nX || this->m_nY != oPoint.m_nY;
    }

    constexpr std::size_t point::get_x() const
    {
        return this->m_nX;
    }

    constexpr std::size_t point::get_y() const
    {
        return this->m_nY;
    }

} // namespace ac
