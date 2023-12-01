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
		// Iterate over potential worded number.
		for (auto itr = map.begin(); itr != map.end(); ++itr)
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
		// in vals[0] and vals[1] respectively.
		char* vals = new char[2] {0, 0};

		for (int i = 0; i < cur.size(); ++i)
		{
			// ASCII character codes 48-57 represent the numbers 0-9.
			if (cur[i] < 48 || cur[i] > 57) continue;

			if (vals[0] == 0) vals[0] = cur[i];
			else vals[1] = cur[i];
		}

		if (vals[1] == 0) vals[1] = vals[0];

		sum += std::strtol(vals, nullptr, 10);

		delete[] vals;
	}

	input.close();

	std::cout << "Sum of all the calibration values: " << sum << std::endl;

	return 0;
}