#pragma once

class Order
{
private:
	unsigned int customerId_;
	unsigned int numGoodsPurchased_;
public:
	Order(unsigned int customerId, unsigned int numGoodsPurchased);
	virtual ~Order() {}

	unsigned int customerId() const;
	unsigned int numGoodsPurchased() const;
};