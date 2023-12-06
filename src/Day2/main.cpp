#include <iostream>
#include <string>
#include <fstream>

int main()
{
	constexpr int MAX_RED = 12;
	constexpr int MAX_GREEN = 13;
	constexpr int MAX_BLUE = 14;

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

	std::string line;
	int gameSum = 0, powerSum = 0;

	// Iterate over each line.
	while (std::getline(fstream, line))
	{
		int red = 0, green = 0, blue = 0;
		bool isPossible = true;

		// Find the colon that comes after each game ID.
		size_t pos = line.find(":", 0);
		int gameId = strtol(line.substr(5, pos - 5).c_str(), nullptr, 10);

		// Iterate over each character in the line.
		for (size_t i = pos; i < line.size(); ++i)
		{
			// If the character is not a number, continue.
			if (line[i] < 48 || line[i] > 57) continue;

			// Store a buffer for each digit of the current number.
			// This is a bit of a cheat, as we assume each number has
			// a maximum of 2 digits.
			char* numbers = new char[2] {0, 0};

			// Store the first digit of the number.
			numbers[0] = line[i];

			// If the number is 2 digits long, store the second digit.
			if (line[i + 1] > 47 && line[i + 1] < 58)
			{
				numbers[1] = line[i + 1];
				++i;
			}

			int val = strtol(numbers, nullptr, 10);

			switch (line[i + 2])
			{
			case 'r':
				if (val > MAX_RED) isPossible = false;
				if (val > red) red = val;
				break;

			case 'g':
				if (val > MAX_GREEN) isPossible = false;
				if (val > green) green = val;
				break;

			case 'b':
				if (val > MAX_BLUE) isPossible = false;
				if (val > blue) blue = val;
				break;
			}
		}

		if (isPossible) gameSum += gameId;
		powerSum += red * green * blue;
	}

	fstream.close();

	std::cout << "Sum of the IDs of possible games: " << gameSum << std::endl;
	std::cout << "Sum of the power of the sets: " << powerSum << std::endl;

	return 0;
}