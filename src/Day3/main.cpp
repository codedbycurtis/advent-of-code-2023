#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>

int main()
{
	std::string filename;
	std::ifstream fstream;

	std::cout << "Enter input file name: ";
	std::getline(std::cin, filename);

	fstream.open(filename);
	if (!fstream.is_open())
	{
		std::cout << "An error occurred while opening the file '" << filename << "'." << std::endl;
		return 0;
	}

	const std::regex digits("\\d+");
	const std::regex specials("[*=/$%@#&+-]+");
	int partSum = 0, gearSum = 0;
	std::string cur;

	std::vector<std::string> vec;
	while (std::getline(fstream, cur))
		vec.push_back(cur);

	fstream.close();

	/*
	* Store the position of each gear as a key,
	* and each part number that is adjacent to
	* the gear in a vector with other adjacent
	* part numbers.
	*/
	std::map<const int, std::vector<int>> gears;

	for (int i = 0; i < vec.size(); ++i)
	{
		for (std::sregex_iterator itr = std::sregex_iterator(vec[i].begin(), vec[i].end(), digits); itr != std::sregex_iterator(); ++itr)
		{
			std::smatch match = *itr, symbolMatch;
			std::string str = match.str(), adjacent;
			int partNumber = strtol(str.c_str(), nullptr, 10);
			int pos = match.position(), prevPos = std::max(pos - 1, 0);

			// Check the character before and after the part number.
			adjacent = vec[i].substr(prevPos, str.size() + 2);
			if (std::regex_search(adjacent, symbolMatch, specials))
				partSum += partNumber;

			// If the character is an asterisk...
			if (symbolMatch.str() == "*")
				// (i (+/-1) * vec[i].size() + prevPos + symbolMatch.position()) tracks the absolute
				// position of each asterisk within the input, which allows me to track which gears
				// are associated with which numbers.
				gears[(i * vec[i].size()) + (prevPos + symbolMatch.position())].push_back(partNumber);

			// If this is not the first line, check the line above.
			if (i != 0)
			{
				// Get the symbols adjacent to the current part number.
				adjacent = vec[i - 1].substr(prevPos, str.size() + 2);

				// If there is an adjacent symbol...
				if (std::regex_search(adjacent, symbolMatch, specials))
				{
					partSum += partNumber;

					// If the symbol is a gear...
					if (symbolMatch.str() == "*")
						gears[((i - 1) * vec[i].size()) + (prevPos + symbolMatch.position())].push_back(partNumber);
				}
			}

			// If this is not the last line, check the line below.
			if (i != vec.size() - 1)
			{
				// Get the symbols adjacent to the current part number.
				adjacent = vec[i + 1].substr(prevPos, str.size() + 2);

				// If there is an adjacent symbol...
				if (std::regex_search(adjacent, symbolMatch, specials))
				{
					partSum += partNumber;

					// If the symbol is a gear...
					if (symbolMatch.str() == "*")
						gears[((i + 1) * vec[i].size()) + (prevPos + symbolMatch.position())].push_back(partNumber);
				}
			}
		}
	}

	for (std::pair<const int, std::vector<int>>& pair : gears)
	{
		if (pair.second.size() == 2)
			gearSum += pair.second[0] * pair.second[1];
	}

	std::cout << "Sum of all part numbers: " << partSum << std::endl;
	std::cout << "Sum of all gear ratios: " << gearSum << std::endl;

	return 0;
}