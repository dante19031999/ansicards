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

#include "json.h"

#include <iomanip>

namespace ac
{

    void write_json_string(std::ostream &oOstream, const std::string &sString)
    {
        // Start the JSON string with a quote
        oOstream.write("\"", 1);

        for (char c : sString)
        {
            switch (c)
            {
            case '\"': // Escape double quotes
                oOstream.write("\\\"", 2);
                break;
            case '\\': // Escape backslashes
                oOstream.write("\\\\", 2);
                break;
            case '\b': // Escape backspace
                oOstream.write("\\b", 2);
                break;
            case '\f': // Escape form feed
                oOstream.write("\\f", 2);
                break;
            case '\n': // Escape newline
                oOstream.write("\\n", 2);
                break;
            case '\r': // Escape carriage return
                oOstream.write("\\r", 2);
                break;
            case '\t': // Escape tab
                oOstream.write("\\t", 2);
                break;
            default:
                if (c < 32 || c > 126)
                {
                    // Non-printable characters
                    oOstream.write("\\x", 2);
                    int nChar = static_cast<int32_t>(c) & 0x000000FF;
                    oOstream << std::setw(2) << std::setfill('0') << std::hex << nChar;
                }
                else
                {
                    // Print printable characters as-is
                    oOstream.write(&c, 1);
                }
                break;
            }
        }

        // End the JSON string with a quote
        oOstream.write("\"", 1);
    }

} // namespace ac
