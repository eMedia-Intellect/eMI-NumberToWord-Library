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

#include <cctype>
#include <string>
#include "Converter.hpp"
#include "ProcessedTriplet.hpp"

namespace NumberToWord
{
	bool Converter::HasAnd{true};
	bool Converter::HasComma{true};
	bool Converter::IsCapitalised{true};
	bool Converter::IsEndedWithFullStop{true};

	std::map<char, std::string> const Converter::zeroToNine{{'0', "zero"}, {'1', "one"}, {'2', "two"}, {'3', "three"}, {'4', "four"}, {'5', "five"}, {'6', "six"}, {'7', "seven"}, {'8', "eight"}, {'9', "nine"}};
	std::map<char, std::string> const Converter::tenToNineteen{{'0', "ten"}, {'1', "eleven"}, {'2', "twelve"}, {'3', "thirteen"}, {'4', "fourteen"}, {'5', "fifteen"}, {'6', "sixteen"}, {'7', "seventeen"}, {'8', "eighteen"}, {'9', "nineteen"}};
	std::map<char, std::string> const Converter::twentyToNinety{{'2', "twenty"}, {'3', "thirty"}, {'4', "forty"}, {'5', "fifty"}, {'6', "sixty"}, {'7', "seventy"}, {'8', "eighty"}, {'9', "ninety"}};
	std::map<int, std::string> const Converter::hundredToSeptillion{{1, "hundred"}, {2, "thousand"}, {3, "million"}, {4, "billion"}, {5, "trillion"}, {6, "quadrillion"}, {7, "quintillion"}, {8, "sextillion"}, {9, "septillion"}};

	std::vector<ProcessedTriplet> Converter::processedTriplets;

	std::string Converter::ToString(std::string number)
	{
		/*
		 * Validate the number.
		 */

		auto invalidCharacterPosition{number.find_first_not_of("0123456789")};

		if (invalidCharacterPosition != std::string::npos)
		{
			throw "The argument passed to the program was not a valid number. It contained invalid characters.";
		}
		else if (number.length() > 1 && number[0] == '0')
		{
			throw "The argument passed to the program was not a valid number. It contained a leading zero.";
		}
		else if (number.length() > 27)
		{
			throw "The argument passed to the program was a number that was too long. The number can not be more than 27 characters in length.";
		}

		/*
		 * The number is processed as a triplet so it must be divisible by 3.
		 * Calculate the remainder when the number is divided by 3.
		 * Prepend leading 0's to the number if necessary.
		 */

		auto remainder{number.length() % 3};

		switch (remainder)
		{
			case 1:
				number = "00" + number;

				break;
			case 2:
				number = "0" + number;

				break;
		}

		/*
		 * Calculate the number of triplets in the number.
		 */

		auto tripletsCount{number.length() / 3};

		/*
		 * Loop over each triplet and process it.
		 */

		unsigned short startingPosition{0};

		for (auto i{tripletsCount}; i > 0; --i)
		{
			auto substring{number.substr(startingPosition, 3)};

			processedTriplets.push_back(ProcessTriplet(substring));

			startingPosition += 3;
		}

		/*
		 * Return the number as a string.
		 */

		std::string word;

		if (processedTriplets.size() != 1)
		{
			for (std::vector<ProcessedTriplet>::size_type i{0}; i != processedTriplets.size(); ++i)
			{
				if (processedTriplets.at(i).TripletNumber == 0)
				{
					--tripletsCount;

					continue;
				}

				if (i != processedTriplets.size() - 1)
				{
					word += processedTriplets.at(i).TripletWord;
					word += " " + hundredToSeptillion.at(tripletsCount);

					if (HasComma)
					{
						word += ", ";
					}
					else
					{
						word += " ";
					}
					
				}
				else
				{
					if (HasAnd)
					{
						if (processedTriplets.at(i).TripletNumber < 100)
						{
							word += "and ";
						}
					}

					word += processedTriplets.at(i).TripletWord;
				}

				--tripletsCount;
			}
		}
		else
		{
			word += processedTriplets.at(0).TripletWord;
		}

		if (word.back() == ' ' || word.back() == ',')
		{
			word.pop_back();
		}

		if (word.back() == ' ' || word.back() == ',')
		{
			word.pop_back();
		}

		if (HasComma)
		{
			std::string::size_type position = word.find(", and");

			if (position != std::string::npos)
			{
				word.replace(position, 5, " and");
			}
		}

		if (IsCapitalised)
		{
			word[0] = std::toupper(word[0]);
		}

		if (IsEndedWithFullStop)
		{
			word += ".";
		}

		return word;
	}

	ProcessedTriplet Converter::ProcessTriplet(std::string const &triplet)
	{
		ProcessedTriplet processedTriplet{0, zeroToNine.at('0')};

		/*
		 * Return an empty string for 0 (000 as a triplet).
		 */

		if (triplet == "000")
		{
			return processedTriplet;
		}

		/*
		 * Determine the triplet number.
		 */

		processedTriplet.TripletNumber = std::stoul(triplet);

		/*
		 * Determine the triplet word by looping over the triplet and concatenating the word.
		 */

		auto placeCounter{triplet.length()};

		std::string word;

		bool canHypen{false};
		bool hasTen{false};

		for (auto const &i : triplet)
		{
			switch (placeCounter)
			{
				case 3:
					if (i != '0')
					{
						word += zeroToNine.at(i);
						word += " ";
						word += hundredToSeptillion.at(1);
					}

					break;
				case 2:
					if (i != '1' && i != '0')
					{
						if (word.length() != 0)
						{
							if (HasAnd)
							{
								word += " and ";
							}
							else
							{
								word += " ";
							}
						}

						word += twentyToNinety.at(i);

						canHypen = true;
					}
					else if (i == '1')
					{
						hasTen = true;
					}

					break;
				case 1:
					if (hasTen)
					{
						if (word.length() != 0)
						{
							if (HasAnd)
							{
								word += " and ";
							}
							else
							{
								word += " ";
							}
						}

						word += tenToNineteen.at(i);
					}
					else
					{
						if (i != '0')
						{
							if (canHypen)
							{
								word += "-";
							}
							else
							{
								if (word.length() != 0)
								{
									if (HasAnd)
									{
										word += " and ";
									}
									else
									{
										word += " ";
									}
								}
							}

							word += zeroToNine.at(i);
						}
					}

					break;
			}

			--placeCounter;
		}

		processedTriplet.TripletWord = word;

		/*
		 * Return the processed triplet.
		 */

		return processedTriplet;
	}
}
