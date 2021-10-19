#pragma once

#include <string>

class Customer
{
private:
	const std::string name_;
	unsigned int id_;
	unsigned int totalNumGoods_;
public:
	Customer(unsigned int id, const std::string &name, unsigned int totalNumGoods);
	virtual ~Customer() {}

	unsigned int id() const;
	const std::string &name() const;
	unsigned int totalNumGoods() const;
};