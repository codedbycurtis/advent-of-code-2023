#include <iostream>
#include <fstream>
#include <string>

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

	fstream.close();

	return 0;
}