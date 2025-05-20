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

#ifdef _WIN32
#include <windows.h>
#endif

namespace ac
{

    namespace ansi
    {

#ifdef _WIN32
        static int ansi_to_windows_color(ansi_color nColor);
#endif

        void set_ansi_foreground_color(ansi_color nColor)
        {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Preserve background
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            // Set foreground
            int wColor = ansi_to_windows_color(nColor);
            SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xF0) | wColor);
#else
            std::ostringstream oOstream;
            oOstream << "\033[" << static_cast<int>(nColor) << "m";
            std::cout << oOstream.str();
#endif
        }

        void set_ansi_background_color(ansi_color nColor)
        {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Preserve foreground
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            // Set background
            int wColor = ansi_to_windows_color(nColor);
            SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0x0F) | (wColor << 4));
#else
            // Background colors are 10 more than foreground
            std::ostringstream oOstream;
            oOstream << "\033[" << (static_cast<int>(nColor) + 10) << "m";
            std::cout << oOstream.str();
#endif
        }

        void reset_ansi_colors()
        {
#ifdef _WIN32
            // 7 is el color white over black by default
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 7);
#else
            // Reset to default colors
            std::cout << "\033[0m";
#endif
        }

        void move_ansi_cursor(std::size_t x, std::size_t y)
        {
#ifdef _WIN32
            COORD coord;
            coord.X = static_cast<SHORT>(x);
            coord.Y = static_cast<SHORT>(y);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
            // Move cursor to (x, y)
            std::ostringstream oOstream;
            oOstream << "\033[" << (y + 1) << ";" << (x + 1) << "H";
            std::cout << oOstream.str();
#endif
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

#ifdef _WIN32
        int ansi_to_windows_color(ansi_color nColor)
        {
            switch (nColor)
            {
            case ansi_color::BLACK:
                return 0;
            case ansi_color::RED:
                return 4;
            case ansi_color::GREEN:
                return 2;
            case ansi_color::YELLOW:
                return 6;
            case ansi_color::BLUE:
                return 1;
            case ansi_color::MAGENTA:
                return 5;
            case ansi_color::CYAN:
                return 3;
            case ansi_color::WHITE:
                return 7;
            case ansi_color::BRIGHT_BLACK:
                return 8;
            case ansi_color::BRIGHT_RED:
                return 12;
            case ansi_color::BRIGHT_GREEN:
                return 10;
            case ansi_color::BRIGHT_YELLOW:
                return 14;
            case ansi_color::BRIGHT_BLUE:
                return 9;
            case ansi_color::BRIGHT_MAGENTA:
                return 13;
            case ansi_color::BRIGHT_CYAN:
                return 11;
            case ansi_color::BRIGHT_WHITE:
                return 15;
            default:
                return 7;
            }
        }
#endif

    } // namespace ansi

} // namespace ac
