#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{
	const std::map<std::string, std::string> map =
	{
		{"one", "1"},
		{"two", "2"},
		{"three", "3"},
		{"four", "4"},
		{"five", "5"},
		{"six", "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine", "9"},
	};

	std::ifstream input;
	std::string filename, cur;
	int sum = 0;

	std::cout << "Enter input file name: ";
	std::getline(std::cin, filename);

	input.open(filename);
	if (!input.is_open())
	{
		std::cout << "An error occurred opening the specified file." << std::endl;
		return 0;
	}

	while (std::getline(input, cur))
	{
		// Iterate over all worded numbers.
		for (std::map<std::string, std::string>::const_iterator itr = map.begin(); itr != map.end(); ++itr)
		{
			// Replace all instances with its numeric equivalent.
			size_t pos = cur.find(itr->first);
			while (pos != cur.npos)
			{
				// Worded numbers can overlap, e.g. 'twone' is equivalent to '21,'
				// therefore keep the first and last characters to account for this.
				// I.e. nine will become n9e.
				cur = cur.replace(pos + 1, itr->first.length() - 2, itr->second);
				pos = cur.find(itr->first);
			}
		}

		// Store the first and last number in the sequence
		// in values[0] and values[1] respectively.
		char* values = new char[2] {0, 0};

		for (int i = 0; i < cur.size(); ++i)
		{
			// ASCII character codes 48-57 represent the numbers 0-9.
			if (cur[i] < 48 || cur[i] > 57) continue;

			if (values[0] == 0) values[0] = cur[i];
			values[1] = cur[i];
		}

		sum += std::strtol(values, nullptr, 10);

		delete[] values;
	}

	input.close();

	std::cout << "Sum of all the calibration values: " << sum << std::endl;

	return 0;
}