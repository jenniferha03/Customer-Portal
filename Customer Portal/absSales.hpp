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

class absSales {
private:
	string title;
	string name;
	string salesPersonID;
	string BossID;
	double totalSales;


public:
	supervisor* boss;
	absSales(string t, string n, string s, string b , Transaction& trans, Order& order)
	{
		title = t;
		name = n;
		salesPersonID = s;
		BossID = b;

		double total_amount = 0;
		// Set total sales
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

	virtual ~absSales() {} // Declare the destructor as virtual

	void setBoss(supervisor* boss)
	{
		this->boss = boss;
	}

};

class Sales : public absSales
{
public:
	Sales(string t, string n, string s, string b ,Transaction& tr, Order& o):absSales(t, n, s, b,tr,o)
	{}
	// Everthing that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		return 0.05 * getTotalSales();
	}
	~Sales()
	{
//		delete boss;
	}
};

class superSales : public absSales
{
public:
	superSales(string t, string n, string s, string b, Transaction& tr, Order& o) :absSales(t, n, s, b, tr, o)
	{}
	// Everthing that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		return 0.065 * getTotalSales();
	}
	~superSales()
	{}
};

class supervisor : public superSales
{
private:
	double empSales;
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
//		cout << "1. Emp Sales at the beginning: $ " << empSales << endl;
//		cout << "2. Supervisor Total Sales and their Emp Sales added: $ " << amount << endl;
		empSales += amount;
//		cout << "3. Emp Sales after adding new amount: $ " << empSales << endl;
	}
	supervisor(string t, string n, string s, string b, Transaction& tr, Order& o) :superSales(t, n, s, b, tr, o)
	{
		empSales = 0;
	}
	// Everthing that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		return 0.065 * getTotalSales() + empSales * 0.03;
	}
	~supervisor()
	{
		delete boss;
	}
};

class manager : public supervisor
{
public:
	manager(string t, string n, string s, string b, Transaction& tr, Order& o):supervisor(t, n, s, b,tr,o)
	{
		setEmpSales(0);
	}
	// Everthing that we put in this class will go to absSales() object
	double virtual getCommission() const override
	{
		return 0.065 *  getTotalSales() + getEmpSales() * 0.03;
	}
	~manager()
	{}
};
// The end of absSales class
