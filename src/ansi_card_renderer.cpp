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

#include "ansi_card_renderer.h"

#include "number.h"
#include "suit.h"
#include <iostream>
#include <sstream>

namespace ac
{

    static inline std::string first_codepoint(const std::string &sString);

    static std::mutex s_RenderMutex;

    ansi_card_renderer::ansi_card_renderer(
        std::size_t nCardWidth,
        std::size_t nCardHeight,
        std::size_t nTableWidth,
        std::size_t nTableHeight,
        ansi_color nClubsColor,
        ansi_color nHeartsColor,
        ansi_color nDiamondsColor,
        ansi_color nSpadesColor,
        ansi_color nGoldsColor,
        ansi_color nCupsColor,
        ansi_color nSwordsColor,
        ansi_color nJokersColor,
        ansi_color nFrameColor,
        ansi_color nCardPaperColor,
        ansi_color nTableColor)
        : m_nClubsColor(nClubsColor),
          m_nHeartsColor(nHeartsColor),
          m_nDiamondsColor(nDiamondsColor),
          m_nSpadesColor(nSpadesColor),
          m_nGoldsColor(nGoldsColor),
          m_nCupsColor(nCupsColor),
          m_nSwordsColor(nSwordsColor),
          m_nJokersColor(nJokersColor),
          m_nFrameColor(nFrameColor),
          m_nCardPaperColor(nCardPaperColor),
          m_nTableColor(nTableColor)
    {
        this->set_card_width(nCardWidth);
        this->set_card_height(nCardHeight);
        this->set_table_width(nTableWidth);
        this->set_table_height(nTableHeight);
    }

    ansi_card_renderer::ansi_card_renderer()
        : m_nCardWidth(ansi_card_renderer::DEFAULT_CARD_WIDTH),
          m_nCardHeight(ansi_card_renderer::DEFAULT_CARD_HEIGHT),
          m_nTableWidth(ansi_card_renderer::DEFAULT_TABLE_WIDTH),
          m_nTableHeight(ansi_card_renderer::DEFAULT_TABLE_HEIGHT),
          m_nClubsColor(ansi_color::GREEN),
          m_nHeartsColor(ansi_color::RED),
          m_nDiamondsColor(ansi_color::CYAN),
          m_nSpadesColor(ansi_color::BRIGHT_BLACK),
          m_nGoldsColor(ansi_color::YELLOW),
          m_nCupsColor(ansi_color::CYAN),
          m_nSwordsColor(ansi_color::BRIGHT_BLACK),
          m_nJokersColor(ansi_color::MAGENTA),
          m_nCardPaperColor(ansi_color::WHITE),
          m_nTableColor(ansi_color::GREEN) {}

    void ansi_card_renderer::render_card(const number *pCard, point oPos) const
    {
        std::lock_guard<std::mutex> oLock(s_RenderMutex);

        // Render the frame
        ansi::set_ansi_background_color(this->m_nCardPaperColor);
        ansi::set_ansi_foreground_color(this->m_nFrameColor);
        ansi::move_ansi_cursor(oPos.get_x(), oPos.get_y());
        std::cout << "*" << std::string(this->m_nCardWidth - 2, '-') << "*";
        ansi::move_ansi_cursor(oPos.get_x(), oPos.get_y() + this->m_nCardHeight - 1);
        std::cout << "*" << std::string(this->m_nCardWidth - 2, '-') << "*";
        for (std::size_t nHeight = 1; nHeight < this->m_nCardHeight - 1; ++nHeight)
        {
            ansi::move_ansi_cursor(oPos.get_x(), oPos.get_y() + nHeight);
            std::cout << "|" << std::string(this->m_nCardWidth - 2, ' ') << "|";
        }

        // Calcultare values
        std::string sNumber = first_codepoint(pCard->get_display_name());
        std::string sSuit = first_codepoint(pCard->get_suit()->get_display_name());
        std::string sDisplayL = sSuit + sNumber;
        std::string sDisplayR = sNumber + sSuit;
        std::string sStdSuit = pCard->get_suit()->get_name();

        // Set suit color
        if (sStdSuit == "heart")
        {
            ansi::set_ansi_foreground_color(this->m_nHeartsColor);
        }
        else if (sStdSuit == "diamond")
        {
            ansi::set_ansi_foreground_color(this->m_nDiamondsColor);
        }
        else if (sStdSuit == "club")
        {
            ansi::set_ansi_foreground_color(this->m_nClubsColor);
        }
        else if (sStdSuit == "spade")
        {
            ansi::set_ansi_foreground_color(this->m_nSpadesColor);
        }
        else if (sStdSuit == "gold")
        {
            ansi::set_ansi_foreground_color(this->m_nGoldsColor);
        }
        else if (sStdSuit == "cup")
        {
            ansi::set_ansi_foreground_color(this->m_nCupsColor);
        }
        else if (sStdSuit == "sword")
        {
            ansi::set_ansi_foreground_color(this->m_nSwordsColor);
        }
        else if (sStdSuit == "joker")
        {
            ansi::set_ansi_foreground_color(this->m_nJokersColor);
        }

        // Draw displays
        if (sStdSuit != "joker")
        {
            ansi::move_ansi_cursor(oPos.get_x() + 1, oPos.get_y() + 1);
            std::cout << sDisplayL;
            ansi::move_ansi_cursor(oPos.get_x() + this->m_nCardWidth - 3, oPos.get_y() + this->m_nCardHeight - 2);
            std::cout << sDisplayR;
        }
        else
        {
            ansi::move_ansi_cursor(oPos.get_x() + 1, oPos.get_y() + 1);
            std::cout << "J";
            ansi::move_ansi_cursor(oPos.get_x() + this->m_nCardWidth - 2, oPos.get_y() + this->m_nCardHeight - 2);
            std::cout << "J";
        }

        // Reset colors
        ansi::reset_ansi_colors();
        std::cout.flush();
    }

    void ansi_card_renderer::render_table() const
    {
        std::lock_guard<std::mutex> oLock(s_RenderMutex);
        ansi::clear_screen();

        // Render the table
        std::string sBlank(this->m_nTableWidth, ' ');
        ansi::set_ansi_background_color(this->m_nTableColor);
        for (std::size_t nHeight = 0; nHeight < this->m_nTableHeight; ++nHeight)
        {
            ansi::move_ansi_cursor(0, nHeight);
            std::cout << "\033[42m";
            std::cout << sBlank;
        }

        // Reset colors
        ansi::reset_ansi_colors();
        std::cout.flush();
    }

    std::size_t ansi_card_renderer::get_card_width() const
    {
        return this->m_nCardWidth;
    }

    std::size_t ansi_card_renderer::get_card_height() const
    {
        return this->m_nCardHeight;
    }

    std::size_t ansi_card_renderer::get_table_width() const
    {
        return this->m_nTableWidth;
    }

    std::size_t ansi_card_renderer::get_table_height() const
    {
        return this->m_nTableHeight;
    }

    ansi_color ansi_card_renderer::get_clubs_color() const
    {
        return this->m_nClubsColor;
    }

    ansi_color ansi_card_renderer::get_hearts_color() const
    {
        return this->m_nHeartsColor;
    }

    ansi_color ansi_card_renderer::get_diamonds_color() const
    {
        return this->m_nDiamondsColor;
    }

    ansi_color ansi_card_renderer::get_spades_color() const
    {
        return this->m_nSpadesColor;
    }

    ansi_color ansi_card_renderer::get_golds_color() const
    {
        return this->m_nGoldsColor;
    }

    ansi_color ansi_card_renderer::get_cups_color() const
    {
        return this->m_nCupsColor;
    }

    ansi_color ansi_card_renderer::get_swords_color() const
    {
        return this->m_nSwordsColor;
    }

    ansi_color ansi_card_renderer::get_jokers_color() const
    {
        return this->m_nJokersColor;
    }

    ansi_color ansi_card_renderer::get_frame_color() const
    {
        return this->m_nFrameColor;
    }

    ansi_color ansi_card_renderer::get_card_paper_color() const
    {
        return this->m_nCardPaperColor;
    }

    ansi_color ansi_card_renderer::get_table_color() const
    {
        return this->m_nTableColor;
    }

    void ansi_card_renderer::set_card_width(std::size_t nWidth)
    {
        if (nWidth < 4 || nWidth > 100)
            this->m_nCardWidth = ansi_card_renderer::DEFAULT_CARD_WIDTH;
        else
            this->m_nCardWidth = nWidth;
    }

    void ansi_card_renderer::set_card_height(std::size_t nHeight)
    {
        if (nHeight < 20 || nHeight > 1000)
            this->m_nCardHeight = ansi_card_renderer::DEFAULT_TABLE_HEIGHT;
        else
            this->m_nCardHeight = nHeight;
    }

    void ansi_card_renderer::set_table_width(std::size_t nWidth)
    {
        if (nWidth < 30 || nWidth > 1000)
            this->m_nTableWidth = ansi_card_renderer::DEFAULT_TABLE_WIDTH;
        else
            this->m_nTableWidth = nWidth;
    }

    void ansi_card_renderer::set_table_height(std::size_t nHeight)
    {
        if (nHeight < 4 || nHeight > 100)
            this->m_nTableHeight = ansi_card_renderer::DEFAULT_CARD_HEIGHT;
        else
            this->m_nTableHeight = nHeight;
    }

    void ansi_card_renderer::set_clubs_color(ansi_color nColor)
    {
        this->m_nClubsColor = nColor;
    }

    void ansi_card_renderer::set_hearts_color(ansi_color nColor)
    {
        this->m_nHeartsColor = nColor;
    }

    void ansi_card_renderer::set_diamonds_color(ansi_color nColor)
    {
        this->m_nDiamondsColor = nColor;
    }

    void ansi_card_renderer::set_spades_color(ansi_color nColor)
    {
        this->m_nSpadesColor = nColor;
    }

    void ansi_card_renderer::set_golds_color(ansi_color nColor)
    {
        this->m_nGoldsColor = nColor;
    }

    void ansi_card_renderer::set_cups_color(ansi_color nColor)
    {
        this->m_nCupsColor = nColor;
    }

    void ansi_card_renderer::set_swords_color(ansi_color nColor)
    {
        this->m_nSwordsColor = nColor;
    }

    void ansi_card_renderer::set_jokers_color(ansi_color nColor)
    {
        this->m_nJokersColor = nColor;
    }

    void ansi_card_renderer::set_frame_color(ansi_color nColor)
    {
        this->m_nFrameColor = nColor;
    }

    void ansi_card_renderer::set_card_paper_color(ansi_color nColor)
    {
        this->m_nCardPaperColor = nColor;
    }

    void ansi_card_renderer::set_table_color(ansi_color nColor)
    {
        this->m_nTableColor = nColor;
    }

    std::string first_codepoint(const std::string &sString)
    {

        if (sString.empty())
            return "";

        unsigned char cFirstByte = static_cast<unsigned char>(sString[0]);

        // Determine the number of bytes in the UTF-8 character
        if ((cFirstByte & 0x80) == 0)
        {
            // 1-byte character (ASCII)
            // Code point is the same as the byte value
            return sString.substr(0, 1);
        }
        else if ((cFirstByte & 0xE0) == 0xC0)
        {
            // 2-byte character
            if (sString.size() < 2)
                throw std::invalid_argument("Invalid UTF-8 string.");
            // Code point is the same as the byte value
            return sString.substr(0, 2);
        }
        else if ((cFirstByte & 0xF0) == 0xE0)
        {
            // 3-byte character
            if (sString.size() < 3)
                throw std::invalid_argument("Invalid UTF-8 string.");
            // Code point is the same as the byte value
            return sString.substr(0, 3);
        }
        else if ((cFirstByte & 0xF8) == 0xF0)
        {
            // 4-byte character
            if (sString.size() < 4)
                throw std::invalid_argument("Invalid UTF-8 string.");
            // Code point is the same as the byte value
            return sString.substr(0, 4);
        }
        else
        {
            throw std::invalid_argument("Invalid UTF-8 string.");
        }
    }

} // namespace ac
