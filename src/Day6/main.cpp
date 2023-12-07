#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

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

	std::string timeStr;
	std::string distanceStr;

	// Read times and distances
	std::getline(fstream, timeStr);
	std::getline(fstream, distanceStr);

	fstream.close();

	std::vector<int> times, distances;

	double singleTime, singleDistance;
	std::string singleTimeStr, singleDistanceStr;

	std::sregex_iterator timeItr = std::sregex_iterator(timeStr.begin(), timeStr.end(), digits);
	std::sregex_iterator distanceItr = std::sregex_iterator(distanceStr.begin(), distanceStr.end(), digits);

	// Use a regular expression to capture digits and insert them as times
	// and distances. Can be done in one loop as there is an equal number of
	// times and distances.
	while (timeItr != std::sregex_iterator())
	{
		std::smatch time = *timeItr, distance = *distanceItr;
		singleTimeStr += time.str();
		singleDistanceStr += distance.str();
		times.push_back(strtol(time.str().c_str(), nullptr, 10));
		distances.push_back(strtol(distance.str().c_str(), nullptr, 10));
		++timeItr;
		++distanceItr;
	}

	singleTime = strtod(singleTimeStr.c_str(), nullptr);
	singleDistance = strtod(singleDistanceStr.c_str(), nullptr);

	// This value is multiplied with the win count of
	// each record, therefore it is necessary to start at 1.
	int multipleRecordWins = 1;
	for (int i = 0; i < times.size(); ++i)
	{
		int wins = 0;
		for (int j = 1; j < times[i]; ++j)
			if (j * (times[i] - j) > distances[i])
				++wins;
		multipleRecordWins *= wins;
	}

	double singleRecordWins = 0;
	for (double i = 1; i < singleTime; ++i)
	{
		if (i * (singleTime - i) > singleDistance)
			++singleRecordWins;
	}

	std::cout << "Product of the number of ways to beat each record: " << multipleRecordWins << std::endl;
	std::cout << "Number of ways to beat the single record: " << singleRecordWins << std::endl;

	return 0;
}