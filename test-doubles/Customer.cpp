#include "Customer.h"

Customer::Customer(unsigned int id, const std::string &name, unsigned int totalNumGoods) :
	name_(name),
	id_(id),
	totalNumGoods_(totalNumGoods)
{}

unsigned int Customer::id() const
{
	return id_;
}

const std::string &Customer::name() const
{
	return name_;
}

unsigned int Customer::totalNumGoods() const
{
	return totalNumGoods_;
}