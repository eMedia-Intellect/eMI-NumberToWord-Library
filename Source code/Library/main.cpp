/*
Copyright © 2017, 2019 eMedia Intellect.

This file is part of eMI NumberToWord Library.

eMI NumberToWord Library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

eMI NumberToWord Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with eMI NumberToWord Library. If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include "NumberToWord/Converter.hpp"

int main(int argc, char **argv)
{
	std::string number;

	if (argc < 0)
	{
		std::cerr << "The number of arguments passed to the program was a negative number." << std::endl;

		return EXIT_FAILURE;
	}
	else if (argc == 0)
	{
		std::cerr << "No argument was passed to the program, not even its name." << std::endl;

		return EXIT_FAILURE;
	}
	else if (argc == 1)
	{
		std::cerr << "No argument was passed to the program." << std::endl;

		return EXIT_FAILURE;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if (i == 1)
			{
				number = *(argv + 1);

				continue;
			}

			if (strcmp(*(argv + i), "--noand") == 0)
			{
				NumberToWord::Converter::HasAnd = false;
			}
			else if (strcmp(*(argv + i), "--nocapitalise") == 0)
			{
				NumberToWord::Converter::IsCapitalised = false;
			}
			else if (strcmp(*(argv + i), "--nocomma") == 0)
			{
				NumberToWord::Converter::HasComma = false;
			}
			else if (strcmp(*(argv + i), "--nofullstop") == 0)
			{
				NumberToWord::Converter::IsEndedWithFullStop = false;
			}
			else
			{
				std::cerr << "\"" << *(argv + i) << "\" is not a valid option." << std::endl;

				return EXIT_FAILURE;
			}
		}
	}

	try
	{
		std::cout << NumberToWord::Converter::ToString(number) << std::endl;

		return EXIT_SUCCESS;
	}
	catch (char const *e)
	{
		std::cerr << e << std::endl;

		return EXIT_FAILURE;
	}
}