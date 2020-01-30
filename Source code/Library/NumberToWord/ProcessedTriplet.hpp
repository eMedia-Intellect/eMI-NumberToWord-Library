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

#ifndef PROCESSEDTRIPLET
#define PROCESSEDTRIPLET

#include <string>

namespace NumberToWord
{
	class ProcessedTriplet
	{
		public:
			ProcessedTriplet(unsigned long number, std::string word) : TripletNumber(number), TripletWord(word)
			{}

			unsigned long TripletNumber;
			std::string TripletWord;
	};
}

#endif