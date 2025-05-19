# This file is part of AnsiCards.
#
# AnsiCards is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# AnsiCards is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AnsiCards.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright (C) 2025 Dante Doménech Martínez

# Build settings
export AC_USE_DEFAULT_JSON = TRUE
export AC_INCLUDE_EXAMPLE = TRUE

# Get the directory where the Makefile is located
MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

.PHONY: cmake build debug gdb release clean clear docs

# Clear screen
clear:
	clear

# Create the build directory and configure the project
cmake: clear
	mkdir -p $(MAKEFILE_DIR)/cmake
	cd $(MAKEFILE_DIR)/cmake && cmake ..

# Build the project
build: cmake
	cd $(MAKEFILE_DIR)/cmake && make dbgansicards

# Debug the library
debug: cmake
	cd $(MAKEFILE_DIR)/cmake && make dbgansicards
	chmod +x $(MAKEFILE_DIR)/build/dbgansicards
	$(MAKEFILE_DIR)/build/dbgansicards

# Debug the library
gdb: cmake
	cd $(MAKEFILE_DIR)/cmake && make dbgansicards
	chmod +x $(MAKEFILE_DIR)/build/dbgansicards
	gdb $(MAKEFILE_DIR)/build/dbgansicards

# Release build
release: cmake
	mkdir -p $(MAKEFILE_DIR)/build
	cd $(MAKEFILE_DIR)/cmake && make release

# Clear the trash
clean:
	rm -rf $(MAKEFILE_DIR)/cmake
	rm -rf $(MAKEFILE_DIR)/build
	rm -rf $(MAKEFILE_DIR)/docs

# Generate documentation
docs:
	doxygen $(MAKEFILE_DIR)/Doxyfile