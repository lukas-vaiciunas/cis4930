#include "CustomerAccounting.h"
#include "Customer.h"
#include "Order.h"

CustomerAccounting::CustomerAccounting() :
	db_(nullptr)
{}

CustomerAccounting::~CustomerAccounting()
{
	sqlite3_close(db_);
}

void CustomerAccounting::init()
{
	this->openDatabase_();
	this->createCustomerTable_();
	this->createOrderTable_();
}

void CustomerAccounting::createCustomer(const Customer &customer)
{
	char *zErrMsg = 0;

	std::string sql = "INSERT INTO CUSTOMERS "
		"VALUES ("
		+ std::to_string(customer.id()) + ", "
		+ "'" + customer.name() + "'" + ", "
		+ std::to_string(customer.totalNumGoods())
		+ ");";

	int rc = sqlite3_exec(db_, sql.c_str(), nullptr, 0, &zErrMsg);

	if (rc != SQLITE_OK)
		throw std::exception(zErrMsg);

	sqlite3_free(zErrMsg);
}

void CustomerAccounting::createOrder(const Order &order)
{
	char *zErrMsg = 0;

	std::string sql = "INSERT INTO ORDERS "
		"VALUES ("
		+ std::to_string(order.customerId()) + ", "
		+ std::to_string(order.numGoodsPurchased())
		+ ");";

	int rc = sqlite3_exec(db_, sql.c_str(), nullptr, 0, &zErrMsg);

	if (rc != SQLITE_OK)
		throw std::exception(zErrMsg);

	sqlite3_free(zErrMsg);
}

void CustomerAccounting::retrieveCustomers() const
{
	char *zErrMsg = 0;

	std::string sql = "SELECT * from CUSTOMERS;";

	int rc = sqlite3_exec(db_, sql.c_str(), selectCallback_, nullptr, &zErrMsg);

	if (rc != SQLITE_OK)
		throw std::exception(zErrMsg);

	sqlite3_free(zErrMsg);
}

int CustomerAccounting::selectCallback_(void *data, int argc, char **argv, char **azColName)
{
	for (int i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");

	return 0;
}

void CustomerAccounting::createCustomerTable_()
{
	std::string sql;
	int rc;
	char *zErrMsg = 0;

	sql = "CREATE TABLE CUSTOMERS ("
		"ID INT,"
		"NAME TEXT,"
		"TOTAL_NUM_GOODS_PURCHASED INT,"
		"PRIMARY KEY (ID)"
		");";

	rc = sqlite3_exec(db_, sql.c_str(), nullptr, 0, &zErrMsg);

	if (rc != SQLITE_OK)
		throw std::exception(zErrMsg);

	sqlite3_free(zErrMsg);
}

void CustomerAccounting::createOrderTable_()
{
	std::string sql;
	int rc;
	char *zErrMsg = 0;

	sql = "CREATE TABLE ORDERS ("
		"CUSTOMER_ID INT,"
		"NUM_GOODS_PURCHASED INT"
		");";

	rc = sqlite3_exec(db_, sql.c_str(), nullptr, 0, &zErrMsg);

	if (rc != SQLITE_OK)
		throw std::exception(zErrMsg);

	sqlite3_free(zErrMsg);
}

void CustomerAccounting::openDatabase_()
{
	if (sqlite3_open(NULL, &db_) != SQLITE_OK)
	{
		std::string errmsg = "Can't open databse: " + std::string(sqlite3_errmsg(db_));
		throw std::exception(errmsg.c_str());
	}
}