#pragma once

class IntegerSum
{
private:
	const char *path_;
public:
	IntegerSum(const char *path);
	virtual ~IntegerSum() {}

	void doSum();

	virtual int readSum();
	virtual void writeSum(int sum);
	void readAndWriteSum();
};