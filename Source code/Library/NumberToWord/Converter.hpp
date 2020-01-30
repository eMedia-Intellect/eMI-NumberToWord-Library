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

#ifndef CONVERTER
#define CONVERTER

#include <map>
#include <string>
#include <vector>

#include "ProcessedTriplet.hpp"

namespace NumberToWord
{
	class Converter
	{
		public:
			static bool HasAnd;
			static bool HasComma;
			static bool IsCapitalised;
			static bool IsEndedWithFullStop;

			static std::string ToString(std::string number);

		private:
			Converter();

			static std::map<char, std::string> const zeroToNine;
			static std::map<char, std::string> const tenToNineteen;
			static std::map<char, std::string> const twentyToNinety;
			static std::map<int, std::string> const hundredToSeptillion;

			static std::vector<ProcessedTriplet> processedTriplets;

			static ProcessedTriplet ProcessTriplet(std::string const &triplet);
	};
}

#endif