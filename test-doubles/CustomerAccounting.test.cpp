#include <boost/test/unit_test.hpp>
#include "CustomerAccounting.h"
#include "Customer.h"
#include "Order.h"

BOOST_AUTO_TEST_SUITE(CustomerAccounting_Test);

BOOST_AUTO_TEST_CASE(should_successfully_open_database)
{
	BOOST_CHECK_NO_THROW(
		CustomerAccounting testDatabase = CustomerAccounting();
		testDatabase.init();
	);
}

//	#mock
BOOST_AUTO_TEST_CASE(should_successfully_create_customer_table)
{
	class CustomerAccountingMock : public CustomerAccounting
	{
	private:
		bool wasInvoked_;

		inline void createCustomerTable_() override
		{
			CustomerAccounting::createCustomerTable_();
			wasInvoked_ = true;
		}
	public:
		CustomerAccountingMock() :
			CustomerAccounting(),
			wasInvoked_(false)
		{}

		inline void verify()
		{
			assert(wasInvoked_);
		}
	};

	CustomerAccountingMock testDatabaseMock = CustomerAccountingMock();
	testDatabaseMock.init();

	testDatabaseMock.verify();
}

//	#mock
BOOST_AUTO_TEST_CASE(should_successfully_create_order_table)
{
	class CustomerAccountingMock : public CustomerAccounting
	{
	private:
		bool wasInvoked_;

		inline void createOrderTable_()
		{
			CustomerAccounting::createOrderTable_();
			wasInvoked_ = true;
		}
	public:
		CustomerAccountingMock() :
			CustomerAccounting(),
			wasInvoked_(false)
		{}

		inline void verify()
		{
			assert(wasInvoked_);
		}
	};

	CustomerAccountingMock testDatabaseMock = CustomerAccountingMock();
	testDatabaseMock.init();

	testDatabaseMock.verify();
}

//	#dummy
BOOST_AUTO_TEST_CASE(should_successfully_create_customer)
{
	unsigned int dummyId = 0;
	const std::string dummyName = "";
	unsigned int dummyTotalNumGoods = 0;

	CustomerAccounting testDatabase = CustomerAccounting();
	testDatabase.init();

	BOOST_CHECK_NO_THROW(
		testDatabase.createCustomer(Customer(dummyId, dummyName, dummyTotalNumGoods));
	);
}

//	#dummy
BOOST_AUTO_TEST_CASE(should_successfully_create_order)
{
	unsigned int dummyCustomerId = 0;
	unsigned int dummyNumGoods = 0;

	CustomerAccounting testDatabase = CustomerAccounting();
	testDatabase.init();

	BOOST_CHECK_NO_THROW(
		testDatabase.createOrder(Order(dummyCustomerId, dummyNumGoods));
	);
}

//	#stub
BOOST_AUTO_TEST_CASE(should_successfully_create_customer_no_side_effects)
{
	class CustomerStub : public Customer
	{
	public:
		CustomerStub() : Customer(1, "Phil Tester", 10) {}
	};

	CustomerAccounting testDatabase = CustomerAccounting();
	testDatabase.init();

	BOOST_CHECK_NO_THROW(
		testDatabase.createCustomer(CustomerStub())
	);
}

//	#stub
BOOST_AUTO_TEST_CASE(should_successfully_create_order_no_side_effects)
{
	class OrderStub : public Order
	{
	public:
		OrderStub() : Order(1, 5) {}
	};

	CustomerAccounting testDatabase = CustomerAccounting();
	testDatabase.init();

	BOOST_CHECK_NO_THROW(
		testDatabase.createOrder(OrderStub())
	);
}

BOOST_AUTO_TEST_CASE(should_successfully_retrieve_customers)
{
	CustomerAccounting testDatabase = CustomerAccounting();
	testDatabase.init();

	testDatabase.createCustomer(Customer(1, "Phil Tester", 10));
	testDatabase.createCustomer(Customer(100, "John UnitTester", 25));
	testDatabase.createCustomer(Customer(9999, "Bob DoubleTester", 300));

	BOOST_CHECK_NO_THROW(
		testDatabase.retrieveCustomers()
	);
}

//	#mock
BOOST_AUTO_TEST_CASE(should_successfully_output_customers_with_callback)
{
	class CustomerAccountingMock : public CustomerAccounting
	{
	private:
		bool wasInvoked_;
	public:
		CustomerAccountingMock() :
			CustomerAccounting(),
			wasInvoked_(false)
		{}

		inline void retrieveCustomers()
		{
			CustomerAccounting::retrieveCustomers();

			wasInvoked_ = true;
		}

		inline void verify()
		{
			assert(wasInvoked_);
		}
	};

	CustomerAccountingMock testDatabaseMock = CustomerAccountingMock();
	testDatabaseMock.init();

	testDatabaseMock.createCustomer(Customer(1, "Phil Tester", 10));
	testDatabaseMock.createCustomer(Customer(100, "John UnitTester", 25));
	testDatabaseMock.createCustomer(Customer(9999, "Bob DoubleTester", 300));

	testDatabaseMock.retrieveCustomers();

	testDatabaseMock.verify();
}

BOOST_AUTO_TEST_SUITE_END()