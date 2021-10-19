#include <fstream>
#include <string>
#include "IntegerSum.h"

IntegerSum::IntegerSum(const char *path) :
	path_(path)
{}

void IntegerSum::doSum()
{
	this->readAndWriteSum();
}

int IntegerSum::readSum()
{
	std::ifstream in(path_);

	if (!in.is_open())
		throw std::exception("Failed to open target path for reading!");

	std::string token = "";
	int sum = 0;

	while (true)
	{
		if (!(in >> token))
			break;

		sum += stoi(token);
	}

	in.close();

	return sum;
}

void IntegerSum::writeSum(int sum)
{
	std::ofstream out(path_, std::ios_base::app);

	if (!out.is_open())
		throw std::exception("Failed to open target path for writing!");

	out << "Sum: " << sum;

	out.close();
}

void IntegerSum::readAndWriteSum()
{
	this->writeSum(this->readSum());
}