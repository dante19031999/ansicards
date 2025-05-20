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
 * @file ansi_card_renderer.h
 * @brief Declaration of the ansi_card_renderer class.
 */

#pragma once

#include "card_renderer.h"
#include "ansi.h"

namespace ac
{

    /**
     * @class ansi_card_renderer
     * @brief A class for rendering cards in a terminal using ANSI colors.
     *
     * This class provides methods to render cards with different nColors for
     * suits and a background nColor. It inherits from the card_renderer class.
     */
    class ansi_card_renderer : public card_renderer
    {
    public:
        /**
         * @brief The default width of a card.
         * This constant defines the default width of a card when rendered.
         */
        static constexpr std::size_t DEFAULT_CARD_WIDTH = 5;

        /**
         * @brief The default height of a card.
         * This constant defines the default height of a card when rendered.
         */
        static constexpr std::size_t DEFAULT_CARD_HEIGHT = 4;

        /**
         * @brief The default width of the table.
         * This constant defines the default width of the table where cards are rendered.
         */
        static constexpr std::size_t DEFAULT_TABLE_WIDTH = 100;

        /**
         * @brief The default height of the table.
         * This constant defines the default height of the table where cards are rendered.
         */
        static constexpr std::size_t DEFAULT_TABLE_HEIGHT = 26;

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the card renderer with default ANSI colors.
         */
        ansi_card_renderer();

        /**
         * @brief Parameterized constructor.
         *
         * Initializes the card renderer with specified ANSI colors for each suit
         * and background.
         *
         * @param nCardWidth card width
         * @param nCardHeight card height
         * @param nClubsColor color for clubs.
         * @param nHeartsColor color for hearts.
         * @param nDiamondsColor color for diamonds.
         * @param nSpadesColor color for spades.
         * @param nGoldsColor color for golds.
         * @param nCupsColor color for cups.
         * @param nSwordsColor color for swords.
         * @param nJokersColor color for jokers.
         * @param nFrameColor Card frame color.
         * @param nCardPaperColor Card paper color.
         */
        ansi_card_renderer(
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
            ansi_color nBackgroundColor,
            ansi_color nCardPaperColor);

    public:
        /**
         * @brief Renders a card at a specified position.
         *
         * This method outputs the card representation to the terminal using
         * ANSI colors.
         *
         * @param pCard Pointer to the card to be rendered.
         * @param oPos The position where the card should be rendered.
         */
        virtual void render_card(const number *pCard, point oPos) const override;

        /**
         * @brief Renders the card table.
         *
         * This method outputs the card representation to the terminal using
         * ANSI colors.
         *
         */
        virtual void render_table() const override;

    public:
        /**
         * @brief Gets the card width.
         * @return The ANSI card width.
         */
        std::size_t get_card_width() const;

        /**
         * @brief Gets the card height.
         * @return The ANSI card width.
         */
        std::size_t get_card_height() const;

        /**
         * @brief Gets the table width.
         * @return The ANSI table width.
         */
        std::size_t get_table_width() const;

        /**
         * @brief Gets the table height.
         * @return The ANSI table width.
         */
        std::size_t get_table_height() const;

        /**
         * @brief Gets the color for hearts.
         * @return The ANSI color for hearts.
         */
        ansi_color get_hearts_color() const;

        /**
         * @brief Gets the color for clubs.
         * @return The ANSI color for clubs.
         */
        ansi_color get_clubs_color() const;

        /**
         * @brief Gets the color for diamonds.
         * @return The ANSI color for diamonds.
         */
        ansi_color get_diamonds_color() const;

        /**
         * @brief Gets the color for spades.
         * @return The ANSI color for spades.
         */
        ansi_color get_spades_color() const;

        /**
         * @brief Gets the color for golds.
         * @return The ANSI color for golds.
         */
        ansi_color get_golds_color() const;

        /**
         * @brief Gets the color for cups.
         * @return The ANSI color for cups.
         */
        ansi_color get_cups_color() const;

        /**
         * @brief Gets the color for swords.
         * @return The ANSI color for swords.
         */
        ansi_color get_swords_color() const;

        /**
         * @brief Gets the color for jokers.
         * @return The ANSI color for jokers.
         */
        ansi_color get_jokers_color() const;

        /**
         * @brief Gets the card frame color.
         * @return The ANSI card frame color.
         */
        ansi_color get_frame_color() const;

        /**
         * @brief Gets the card paper color.
         * @return The ANSI card paper color.
         */
        ansi_color get_card_paper_color() const;

        /**
         * @brief Gets the table color.
         * @return The ANSI table color.
         */
        ansi_color get_table_color() const;

    public:
        /**
         * @brief Sets the card width.
         *
         * If invalid, DEFAULT_CARD_WIDTH is set.
         * @param nCardWidth The card width.
         */
        void set_card_width(std::size_t nCardWidth);

        /**
         * @brief Sets the card height.
         *
         * If invalid, DEFAULT_CARD_HEIGHT is set.
         * @param nCardWidth The card hight.
         */
        void set_card_height(std::size_t nHeight);

        /**
         * @brief Sets the table width.
         *
         * If invalid, DEFAULT_TABLE_WIDTH is set.
         * @param nTableWidth The table width.
         */
        void set_table_width(std::size_t nTableWidth);

        /**
         * @brief Sets the table hight.
         *
         * If invalid, DEFAULT_TABLE_HEIGHT is set.
         * @param nCardWidth The table hight.
         */
        void set_table_height(std::size_t nTableHeight);

        /**
         * @brief Sets the color for clubs.
         * @param nColor The ANSI color to set for clubs.
         */
        void set_clubs_color(ansi_color nColor);

        /**
         * @brief Sets the color for hearts.
         * @param nColor The ANSI color to set for hearts.
         */
        void set_hearts_color(ansi_color nColor);

        /**
         * @brief Sets the color for diamonds.
         * @param nColor The ANSI color to set for diamonds.
         */
        void set_diamonds_color(ansi_color nColor);

        /**
         * @brief Sets the color for spades.
         * @param nColor The ANSI color to set for spades.
         */
        void set_spades_color(ansi_color nColor);

        /**
         * @brief Sets the color for golds.
         * @param nColor The ANSI color to set for golds.
         */
        void set_golds_color(ansi_color nColor);

        /**
         * @brief Sets the color for cups.
         * @param nColor The ANSI color to set for cups.
         */
        void set_cups_color(ansi_color nColor);

        /**
         * @brief Sets the color for swords.
         * @param nColor The ANSI color to set for swords.
         */
        void set_swords_color(ansi_color nColor);

        /**
         * @brief Sets the color for jokers.
         * @param nColor The ANSI color to set for jokers.
         */
        void set_jokers_color(ansi_color nColor);

        /**
         * @brief Sets the card frame color.
         * @param nColor The ANSI color to set for the card frame.
         */
        void set_frame_color(ansi_color nColor);

        /**
         * @brief Sets the card pape color.
         * @param nColor The ANSI color to set for the card paper.
         */
        void set_card_paper_color(ansi_color nColor);

        /**
         * @brief Sets the table color.
         * @param nColor The ANSI color to set for the table.
         */
        void set_table_color(ansi_color nColor);

    private:
        std::size_t m_nCardWidth;     ///< The card width
        std::size_t m_nCardHeight;    ///< The card hight
        std::size_t m_nTableWidth;    ///< The table width
        std::size_t m_nTableHeight;   ///< The table hight
        ansi_color m_nClubsColor;     ///< The ANSI color for clubs.
        ansi_color m_nHeartsColor;    ///< The ANSI color for hearts.
        ansi_color m_nDiamondsColor;  ///< The ANSI color for diamonds.
        ansi_color m_nSpadesColor;    ///< The ANSI color for spades.
        ansi_color m_nGoldsColor;     ///< The ANSI color for golds.
        ansi_color m_nCupsColor;      ///< The ANSI color for cups.
        ansi_color m_nSwordsColor;    ///< The ANSI color for swords.
        ansi_color m_nJokersColor;    ///< The ANSI color for jokers.
        ansi_color m_nFrameColor;     ///< The ANSI color for the card frame.
        ansi_color m_nCardPaperColor; ///< The ANSI color for the card paper.
        ansi_color m_nTableColor;     ///< The ANSI color for the table.
    };

} // namespace ac
