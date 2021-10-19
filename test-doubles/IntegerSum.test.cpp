#define BOOST_TEST_MODULE Assign_2_Tests

#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include <filesystem>
#include <random>
#include <string>
#include "IntegerSum.h"

BOOST_AUTO_TEST_SUITE(IntegerSum_Test);

//	#mock
BOOST_AUTO_TEST_CASE(should_read_sum)
{
	class IntegerSumMock : public IntegerSum
	{
	private:
		bool wasInvoked_;
	public:
		IntegerSumMock(const char *path) :
			IntegerSum(path),
			wasInvoked_(false)
		{}

		inline int readSum() override
		{
			wasInvoked_ = true;

			return IntegerSum::readSum();
		}

		inline void verify()
		{
			assert(wasInvoked_);
		}
	};

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> valueDis(-1000, 1000);
	std::uniform_int_distribution<unsigned int> amountDis(10, 20);

	unsigned int amount = amountDis(eng);
	int sumPut = 0;

	std::ofstream testout("testfile.txt");

	for (unsigned int i = 0; i < amount; i++)
	{
		int value = valueDis(eng);

		testout << value << std::endl;
		sumPut += value;
	}

	testout.close();

	IntegerSumMock integerSumMock("testfile.txt");

	integerSumMock.doSum();

	std::filesystem::remove("testfile.txt");

	integerSumMock.verify();
}

//	#mock
BOOST_AUTO_TEST_CASE(should_write_sum)
{
	class IntegerSumMock : public IntegerSum
	{
	private:
		bool wasInvoked_;
	public:
		IntegerSumMock(const char *path) :
			IntegerSum(path),
			wasInvoked_(false)
		{}

		inline void writeSum(int sum) override
		{
			wasInvoked_ = true;

			IntegerSum::writeSum(sum);
		}

		inline void verify()
		{
			assert(wasInvoked_);
		}
	};

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> valueDis(-1000, 1000);
	std::uniform_int_distribution<unsigned int> amountDis(10, 20);

	unsigned int amount = amountDis(eng);
	int sumPut = 0;

	std::ofstream testout("testfile.txt");

	for (unsigned int i = 0; i < amount; i++)
	{
		int value = valueDis(eng);

		testout << value << std::endl;
		sumPut += value;
	}

	testout.close();

	IntegerSumMock integerSumMock("testfile.txt");

	integerSumMock.doSum();

	std::filesystem::remove("testfile.txt");

	integerSumMock.verify();
}

BOOST_AUTO_TEST_CASE(should_read_and_write_correct_sum)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> valueDis(-1000, 1000);
	std::uniform_int_distribution<unsigned int> amountDis(10, 20);

	unsigned int amount = amountDis(eng);
	int sumPut = 0;

	std::ofstream testout("testfile.txt");

	for (unsigned int i = 0; i < amount; i++)
	{
		int value = valueDis(eng);

		testout << value << std::endl;
		sumPut += value;
	}

	testout.close();

	IntegerSum integerSum("testfile.txt");

	integerSum.doSum();

	std::ifstream testin("testfile.txt");
	std::string token = "";
	int sumGet = 0;
	bool found = false;

	while (true)
	{
		if (!(testin >> token))
			break;

		if (token == "Sum:")
		{
			testin >> token;
			sumGet = std::stoi(token);
			found = true;
			break;
		}
	}

	testin.close();

	std::filesystem::remove("testfile.txt");

	BOOST_CHECK(found && sumPut == sumGet);
}

BOOST_AUTO_TEST_CASE(should_throw_error_on_missing_filename)
{
	IntegerSum integerSumTest("missing_file_name.fake_extension");

	BOOST_CHECK_THROW(
		integerSumTest.doSum(),
		std::exception);
}

BOOST_AUTO_TEST_CASE(should_read_correct_sum)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> valueDis(-1000, 1000);
	std::uniform_int_distribution<unsigned int> amountDis(10, 20);

	unsigned int amount = amountDis(eng);
	int sumPut = 0;

	std::ofstream testout("testfile.txt");

	for (unsigned int i = 0; i < amount; i++)
	{
		int value = valueDis(eng);

		testout << value << std::endl;
		sumPut += value;
	}

	testout.close();

	IntegerSum integerSum("testfile.txt");

	BOOST_CHECK(sumPut == integerSum.readSum());

	std::filesystem::remove("testfile.txt");
}

BOOST_AUTO_TEST_CASE(should_write_correct_sum)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> valueDis(-1000, 1000);
	std::uniform_int_distribution<unsigned int> amountDis(10, 20);

	unsigned int amount = amountDis(eng);
	int sumPut = 0;

	std::ofstream testout("testfile.txt");

	for (unsigned int i = 0; i < amount; i++)
	{
		int value = valueDis(eng);

		testout << value << std::endl;
		sumPut += value;
	}

	testout.close();

	IntegerSum integerSumTest("testfile.txt");

	integerSumTest.writeSum(sumPut);

	std::ifstream testin("testfile.txt");
	std::string token = "";
	int sumGet = 0;
	bool found = false;

	while (true)
	{
		if (!(testin >> token))
			break;

		if (token == "Sum:")
		{
			testin >> token;
			sumGet = std::stoi(token);
			found = true;
			break;
		}
	}

	testin.close();

	std::filesystem::remove("testfile.txt");

	BOOST_CHECK(found && sumPut == sumGet);
}

BOOST_AUTO_TEST_SUITE_END()