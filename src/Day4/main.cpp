#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <set>

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
	int totalPoints = 0, totalScratchcards = 0;
	std::vector<std::string> scratchcards;
	std::map<const int, int> scratchcardWins;
	std::string cur;

	// Read all scratchcards into vector.
	while (std::getline(fstream, cur))
		scratchcards.push_back(cur);

	fstream.close();

	// Initialize each scratchcard's count to 1.
	for (int i = 1; i <= scratchcards.size(); ++i)
		scratchcardWins[i] = 1;

	for (int i = 0; i < scratchcards.size(); ++i)
	{
		int matchIndex = 0, cardNumber = 0, cardPoints = 0;
		std::sregex_iterator itr = std::sregex_iterator(scratchcards[i].begin(), scratchcards[i].end(), digits);
		std::set<int> winningNumbers, myNumbers;

		while (itr != std::sregex_iterator())
		{
			std::smatch match = *itr;

			if (matchIndex == 0)
			{
				cardNumber = strtol(match.str().c_str(), nullptr, 10);
				++matchIndex;
				++itr;
				continue;
			}

			int number = strtol(match.str().c_str(), nullptr, 10);

			// Each card has 10 winning numbers, and 25 player numbers.
			if (matchIndex <= 10)
				winningNumbers.insert(number);
			else
				myNumbers.insert(number);

			++matchIndex;
			++itr;
		}

		int wins = 0;
		for (int number : myNumbers)
		{
			if (winningNumbers.find(number) == winningNumbers.end()) continue;

			if (cardPoints == 0) cardPoints = 1;
			else cardPoints *= 2;

			++wins;
		}

		for (int j = 0; j < scratchcardWins[cardNumber]; ++j)
			for (int k = 1; k <= wins; ++k)
				++scratchcardWins[cardNumber + k];

		totalPoints += cardPoints;
	}

	for (int i = 1; i <= scratchcardWins.size(); ++i)
		totalScratchcards += scratchcardWins[i];

	std::cout << "Total points: " << totalPoints << std::endl;
	std::cout << "Total scratchcards: " << totalScratchcards << std::endl;

	return 0;
}