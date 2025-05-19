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

#include "ansi.h"
#include <sstream>
#include <iostream>

namespace ac
{

    namespace ansi
    {

        void set_ansi_foreground_color(ansi_color nColor)
        {
            std::ostringstream oOstream;
            oOstream << "\033[" << static_cast<int>(nColor) << "m";
            std::cout << oOstream.str();
        }

        void set_ansi_background_color(ansi_color nColor)
        {
            // Background colors are 10 more than foreground
            std::ostringstream oOstream;
            oOstream << "\033[" << (static_cast<int>(nColor) + 10) << "m";
            std::cout << oOstream.str();
        }

        void reset_ansi_colors()
        {
            // Reset to default colors
            std::cout << "\033[0m";
        }

        void move_ansi_cursor(std::size_t x, std::size_t y)
        {
            // Move cursor to (x, y)
            std::ostringstream oOstream;
            oOstream << "\033[" << (y + 1) << ";" << (x + 1) << "H";
            std::cout << oOstream.str();
        }

        void reserve_ansi_terminal(std::size_t w, std::size_t h)
        {
            // Move cursor to (x, y)
            std::ostringstream oOstream;
            oOstream << "\033[8;" << h << ";" << w << "t";
            std::cout << oOstream.str();
        }

        void clear_screen()
        {
#ifdef _WIN32
            system("CLS");
#else
            system("clear");
#endif
        }

    } // namespace ansi

} // namespace ac
