#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Order
{
public:
	// Struct to represent order data
	struct OrderData
	{
		string orderID;
		string date;
		int quantity;
		double amount;

		OrderData(string orderID, string date, int quantity, double amount)
		{
			this->orderID = orderID;
			this->date = date;
			this->quantity = quantity;
			this->amount = amount;
		}

		OrderData()
		{
			orderID = "";
			date = "";
			quantity = 0;
			amount = 0;
		}
	};

private:
	// A vector to store all of the order transaction information
	vector<OrderData> orders;

public:
	// Constructor to initialize the class with order data from a file
	Order(const string& filename)
	{
		readData(filename);
	}

	// Function to read order data from a file
	void readData(const string& filename)
	{

		ifstream file(filename);
		if (!file)
		{
			cout << "Error: Could not open file " << filename << endl;
			exit(1);
		}

		string line;
		string temp;

		// Split data using the semicolon for the delimiter
		while (getline(file, line))
		{
			stringstream ss(line);
			string orderID;
			string date;
			int quantity;
			double amount;
			getline(ss, orderID, ';');
			getline(ss, date, ';');
			getline(ss, temp, ';');
			quantity = atoi(temp.c_str());
			getline(ss, temp, '\n');
			amount = atof(temp.c_str());

			OrderData data;
			data.orderID = orderID;
			data.date = date;
			data.quantity = quantity;
			data.amount = amount;
			orders.push_back(data);
    }

    file.close();
}

	// Function to retrieve order data by order ID
	OrderData getOrder(const string& orderID) const
	{
		for (const auto& order : orders)
		{
			if (order.orderID == orderID)
			{
				return order;
			}
		}

		// Return a default OrderData object if not found
		OrderData notFoundOrder;
		notFoundOrder.orderID = "Not Found";
		notFoundOrder.date = "";
		notFoundOrder.quantity = 0;
		notFoundOrder.amount = 0.0;
		return notFoundOrder;
	}

	// Function to get the list of all order data
	vector<OrderData> getOrders() const
	{
		return orders;
	}

	void addOrder(const OrderData& info)
	{
		orders.push_back(info);
	}
};
