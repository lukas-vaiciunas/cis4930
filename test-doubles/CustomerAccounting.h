/*
 *	Database Information
 *	--------------------
 *
 *	Name:			Sqlite3
 *	Version:		3.36.0
 *	Port Number:	N/A (memory or file based)
 *	Download Link:	https://sqlite.org/download.html
 */

#pragma once

class Customer;
class Order;

#include <string>
#include <sqlite3.h>

class CustomerAccounting
{
protected:
	sqlite3 *db_;

	static int selectCallback_(void *data, int argc, char **argv, char **azColName);
	
	virtual void createCustomerTable_();
	virtual void createOrderTable_();
	void openDatabase_();
public:
	CustomerAccounting();
	virtual ~CustomerAccounting();

	void init();

	void createCustomer(const Customer &customer);
	void createOrder(const Order &order);

	void retrieveCustomers() const;
};