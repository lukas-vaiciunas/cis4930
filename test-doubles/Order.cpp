#include "Order.h"

Order::Order(unsigned int customerId, unsigned int numGoodsPurchased) :
	customerId_(customerId),
	numGoodsPurchased_(numGoodsPurchased)
{}

unsigned int Order::customerId() const
{
	return customerId_;
}

unsigned int Order::numGoodsPurchased() const
{
	return numGoodsPurchased_;
}