/*
 * absSales.hpp
 *
 *  Created on: Nov 2, 2023
 *      Author: jenniferha
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class supervisor;
class manager;

// Abstract base class representing a salesperson
class absSales {
private:
	string title;
	string name;
	string salesPersonID;
	string BossID;
	double totalSales;


public:
	supervisor* boss; // Pointer to supervisor object

	// Constructor initializing the salesperson with transaction and order data
	absSales(string t, string n, string s, string b , Transaction& trans, Order& order)
	{
		title = t;
		name = n;
		salesPersonID = s;
		BossID = b;

		double total_amount = 0;

		// Set total sales by iterating through transactions and orders
		for (auto i : trans.getTransactions())
		{
			if (i.salesperson_id == this->salesPersonID)
			{
				for (auto j : order.getOrders())
				{
					if (j.orderID == i.order_id)
					{
						total_amount += j.amount;
					}

				}
			}
		}
		totalSales = total_amount;
		boss = nullptr;
	}
	// Getter functions for class attributes
	string getTitle()
	{
		return title;
	}
	string getName() const
	{
		return name;
	}
	string getSalesPersonID() const
	{
		return salesPersonID;
	}
	string getBossID()
	{
		return BossID;
	}
	double getTotalSales() const
	{
		return totalSales;
	}
	void setTotalSales(double d) {
		totalSales = d;
	}
	double virtual getCommission() const = 0;

	// Virtual destructor to allow proper cleanup in derived classes
	virtual ~absSales() {} // Declare the destructor as virtual

	// Setter function for boss (supervisor)
	void setBoss(supervisor* boss)
	{
		this->boss = boss;
	}

};

// Derived class representing a regular salesperson
class Sales : public absSales
{
public:
	 // Constructor forwarding parameters to the base class constructor
	Sales(string t, string n, string s, string b ,Transaction& tr, Order& o):absSales(t, n, s, b,tr,o)
	{}
	/*
	 * Implementation of the virtual function to calculate commission for a regular salesperson
	 * Everything that we put in this class will go to absSales() object
	 */
	double virtual getCommission() const override
	{
		return 0.05 * getTotalSales();
	}
	// Destructor for the Sales class
	~Sales()
	{} // Note: No dynamic memory allocation in this class, so no explicit cleanup needed
};

// Derived class representing a super salesperson
class superSales : public absSales
{
public:
	// Constructor
	superSales(string t, string n, string s, string b, Transaction& tr, Order& o) :absSales(t, n, s, b, tr, o)
	{}
	/*
	 * Implementation of the virtual function to calculate commission for a super salesperson
	 * Everything that we put in this class will go to absSales() object
	 */
	double virtual getCommission() const override
	{
		return 0.065 * getTotalSales();
	}
	// Destructor
	~superSales()
	{}
};

class supervisor : public superSales
{
private:
	double empSales; // Attribute for supervisor's subordinates' sales
public:
	void setEmpSales(double e)
	{
		empSales = e;
	}
	double getEmpSales() const
	{
		return empSales;
	}
	void incEmpSales(double amount)
	{
		empSales += amount; // Add all the sales of the subordinates
	}
	// Constructor
	supervisor(string t, string n, string s, string b, Transaction& tr, Order& o) :superSales(t, n, s, b, tr, o)
	{
		empSales = 0;
	}
	// Everthing that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		return 0.065 * getTotalSales() + empSales * 0.03;
	}
	// Destructor
	~supervisor()
	{
		delete boss;
	}
};

class manager : public supervisor
{
public:
	// Constructor
	manager(string t, string n, string s, string b, Transaction& tr, Order& o):supervisor(t, n, s, b,tr,o)
	{
		setEmpSales(0);
	}
	// Everything that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		/*
		 * The manager earn 6.5% of their sales and 3% of the sales from the subordinates
		 * who are supervisors and the supervisors' subordinates included
		 */
		return 0.065 *  getTotalSales() + getEmpSales() * 0.03;
	}
	// Destructor
	~manager()
	{}
};
// The end of absSales class
