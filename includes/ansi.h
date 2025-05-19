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
 * @file ansi.h
 * @brief Provides tools for working with ansi terminals.
 */
#pragma once

#include <cstddef>

namespace ac
{

    /**
     * @enum ansi_color
     * @brief Enum class representing ANSI color codes for terminal output.
     */
    enum class ansi_color
    {
        BLACK = 30,          ///< Black nColor
        RED = 31,            ///< Red nColor
        GREEN = 32,          ///< Green nColor
        YELLOW = 33,         ///< Yellow nColor
        BLUE = 34,           ///< Blue nColor
        MAGENTA = 35,        ///< Magenta nColor
        CYAN = 36,           ///< Cyan nColor
        WHITE = 37,          ///< White nColor
        BRIGHT_BLACK = 90,   ///< Bright black nColor
        BRIGHT_RED = 91,     ///< Bright red nColor
        BRIGHT_GREEN = 92,   ///< Bright green nColor
        BRIGHT_YELLOW = 93,  ///< Bright yellow nColor
        BRIGHT_BLUE = 94,    ///< Bright blue nColor
        BRIGHT_MAGENTA = 95, ///< Bright magenta nColor
        BRIGHT_CYAN = 96,    ///< Bright cyan nColor
        BRIGHT_WHITE = 97,   ///< Bright white nColor
    };

    namespace ansi
    {

        /**
         * @brief Sets the foreground color of the terminal output.
         * @param nColor The color to set as the foreground color, specified as an ansi_color enum.
         */
        void set_ansi_foreground_color(ansi_color nColor);

        /**
         * @brief Sets the background color of the terminal output.
         * @param nColor The color to set as the background color, specified as an ansi_color enum.
         */
        void set_ansi_background_color(ansi_color nColor);

        /**
         * @brief Resets the terminal colors to their default values.
         * This function resets both the foreground and background colors.
         */
        void reset_ansi_colors();

        /**
         * @brief Moves the cursor to a specified position in the terminal.  Origin: (0,0).
         * @param x The x-coordinate (column) to move the cursor to. Origin: 0.
         * @param y The y-coordinate (row) to move the cursor to. Origin: 0.
         */
        void move_ansi_cursor(std::size_t x, std::size_t y);

        /**
         * @brief Reserves an ANSI terminal with the specified width and height.
         *
         * This function configures the terminal to have the specified dimensions,
         * allowing for better control over the terminal's display properties.
         *
         * @param w The width of the terminal in characters.
         * @param h The height of the terminal in characters.
         *
         * @note This function may throw an exception if the terminal cannot be resized
         *       to the specified dimensions.
         */
        void reserve_ansi_terminal(std::size_t w, std::size_t h);

        /**
         * @brief Clears the console screen.
         *
         * This function clears the console screen by calling the appropriate
         * system command based on the operating system. It uses "CLS" for
         * Windows and "clear" for Unix-like systems.
         *
         * @note This function uses the `system` function, which may have
         *       security implications. Consider alternatives for production code.
         */
        void clear_screen();

    } // namespace ansi

} // namespace ac
