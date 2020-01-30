# Copyright © 2017, 2019 eMedia Intellect.

# This file is part of eMI NumberToWord Library.

# eMI NumberToWord Library is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# eMI NumberToWord Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with eMI NumberToWord Library. If not, see <http://www.gnu.org/licenses/>.

all:
	if [ ! -d ./32-bit/ ]; then mkdir ./32-bit/; fi

	g++ -m32 -pedantic -std=c++14 -Wall -Weffc++ -Wextra -Wshadow ../../Library/main.cpp ../../Library/NumberToWord/Converter.cpp -o ./32-bit/NumberToWord

	if [ ! -d ./64-bit/ ]; then mkdir ./64-bit/; fi

	g++ -m64 -pedantic -std=c++14 -Wall -Weffc++ -Wextra -Wshadow ../../Library/main.cpp ../../Library/NumberToWord/Converter.cpp -o ./64-bit/NumberToWord

clean:
	if [ -d ./32-bit/ ]; then rm --recursive ./32-bit/; fi

	if [ -d ./64-bit/ ]; then rm --recursive ./64-bit/; fi