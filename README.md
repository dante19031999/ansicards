<!--
This file is part of AnsiCards.

AnsiCards is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AnsiCards is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with AnsiCards.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2025 Dante Doménech Martínez
-->

# Ansi Cards

Ansi Cards is a C++ library designed for working with cards in an ANSI terminal. It provides a layer of abstraction, allowing developers to utilize the library outside the scope of an ANSI terminal, although implementation details will need to be handled by the user.

## Motivations

This library has been developed for a practical class for first-year Computer Engineering students. The exercise requires a library capable of performing specific tasks; however, only an object file for Windows has been provided. Therefore, this library serves as an alternative for Linux systems and any ANSI terminal in general. I am sharing it here in the hope that this code may be helpful to someone in the future.

## License

This file is part of AnsiCards.

AnsiCards is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

AnsiCards is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with AnsiCards.  If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2025 Dante Doménech Martínez

## Project Overview

This library is built to support multithreading development paradigms. Classes within the library utilize an internal mutex to lock resources during internal changes, ensuring thread safety. Users may need to make modifications to suit their specific use cases.

### Key Components

- `deck`: A collection of `suit(s)`.
- `suit`: A collection of `number(s)`.
- `number`: Represents the value of a card.

### Creating and Managing Decks

1. **`deck` creation**: use the `deck` constructor to create a `deck`.
1. **`suit` creation**: use `suit deck::create_suit` to create a `suit`.
1. **`number` creation**: use `number deck::create_number` to create a `number`.

#### Predefined deck:

1. Poker deck: use `deck *deck::generate_poker_deck` to generate a poker deck.
1. Spanish deck: use `deck *deck::generate_spanish_deck` to generate a spanish deck.

### Accessing numbers

- Retrieve `number(s)` in a suit using:
  - `std::vector<number*> suit::get_numbers()`
  - `std::vector<const number*> suit::get_numbers() const`
  
- Retrieve `number(s)` in a deck using:
  - `std::vector<number*> deck::get_numbers()`
  - `std::vector<const number*> deck::get_numbers() const`
  
- Retrieve `suit(s)` in a deck using:
  - `std::vector<suit*> deck::get_suits()`
  - `std::vector<const suit*> deck::get_suits() const`

### Playing the Game

The game can be played on a `card_table`, which allows for operations such as adding, removing, swapping, and reorganizing cards. 

- A `card_table` can utilize a `card_renderer` to render the table and its cards.
- The `ansi_card_table` is a specialization of `card_table` that uses an `ansi_card_renderer`, specifically designed for ANSI terminal play.

Only `number(s)` can be displayed by the `card_table`. If the table needs to support extended features, such as backguard cards, a "technical `suit`" may be created to implement them.

If a `number` needs to appear twice, two `number(s)` with different names but the same display name can be used. Another option is to place the repeated card into a "technical `suit`."

The provided `ansi_card_renderer` only supports the poker and Spanish `deck(s)` available through the `deck` class methods. Other implementations may be created over the `card_renderer` interface.

## Project Structure

- `./includes`: Header files for the project (see documentation for details).
- `./src`: Source files for the project (see documentation for details).
- `./resources`: Resource files for the project.
- `./CMakeLists.txt`: CMake configuration file for the project.
- `./Makefile`: Makefile for building the project.
- `./Doxyfile`: Doxygen configuration file for generating documentation.

### CMake Configuration

The `CMakeLists.txt` file contains configurations for two C++ build projects:
- **ansicards**: Executable used for testing the project, including the main file.
- **libansicards**: Static library for the project, built with position-independent code for use in dynamic libraries.

**Settings (loaded from the environment)**:
- `AC_USE_DEFAULT_JSON` (`TRUE`/`FALSE`): Determines whether to use the default JSON parser implementation (nlohmann_json). Using this option requires additional setup.

### Makefile Targets

- `make cmake`: Run CMake on the project.
- `make build`: Build the project.
- `make debug`: Build the project and run debug tests.
- `make dbg`: Build the project and run debug tests under dbg.
- `make release`: Generate release files.
- `make clean`: Clean CMake/build files.
- `make docs`: Generate Doxygen documentation.

**Release Files Include**:
- Compiled static library: `./build/libansicards.a`
- Header files: `./build/headersansicards.tar.gz`

## Doxygen Documentation

A simple Doxygen configuration file is provided to generate HTML documentation. To generate the full documentation, run `make docs` in the main project directory.
