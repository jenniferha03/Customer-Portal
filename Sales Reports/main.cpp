/*------------------------------------------------------------------------------
 *  CSCE 306 - Object Oriented Software Development
 *  Assignment: Term Project - Phase 3
 *  Created on: Nov 2, 2023
 * 	Student Name: Jennifer (Khue) Ha
 *
 * 	Phase 3 Overview:
 * 	- Introduces a new sales division to handle direct-to-customer sales.
 * 	Salespersons may operate booths, conduct door-to-door sales, or
 * 	interact with customers in the Naperville store. The sales division
 * 	comprises four roles: Sales, SuperSales, Supervisors, and Managers,
 * 	each with specific responsibilities.
 *
 *  Phase 3, part 1:
 *  - Define a hierarchy of classes for the sales division, including
 *  Sales, SuperSales, Supervisors, and Managers. Create abstract classes
 *  to represent the common attributes and behaviors. Implement a
 *  getCommission() function at each level, with the base class function
 *  being abstract.
 *
 *  Phase 3, part 2:
 *	- Read sales staff data from the "salesStaff.txt" file and create
 *	objects based on their roles. Store these objects as pointers
 *	in a vector of the base class.
 *
 *  Phase 3, part 3:
 *	- Generate a sales report displaying each salesperson's first and
 *	last name, sales, and commission. Add an entry to the main menu to
 *	facilitate the display of the sales report.
 *
 *	1. Folder: Phase 3
 *	2. Text file: customer.txt, orders.txt, transactions.txt, salesStaff.txt
 *	3. Class: customer.hpp, orders.hpp, transaction.hpp, absSales.hpp
 *	4. Program: main.cpp
 *
 *	5. Function: GetCustomerData, displayMenu, getUserChoice, IDLinearSearch,
 *	Is_Existed_Customers_in_Transaction, NameLinearSearch, generateNewID,
 *	Input_NewCustomer, Add_NewCustomertoFile, getCustomerOrderInfo,
 *	generateOrderID, addNewOrde, subMenuforCase5, readData,
 *	generateSalesReport, main
 -----------------------------------------------------------------------------*/

#include "customer.hpp"
#include "transaction.hpp"
#include "orders.hpp"
#include "rainbowlist.hpp"
#include "absSales.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to load customer data from a file
void GetCustomerData(vector<customer>& temp_customer, string filename)
{
	//& is passing the address of the vector (passing by reference)
	ifstream infile(filename);
	if(!infile)
	{
		cerr << "Error - cannot open " << filename << endl;
		exit(1);
	}

	string inputLine;
	string temp;
	int ID;
	string FirstName;
	string LastName;
	string address;
	string city;
	string state;
	int zip;

	while (getline(infile, inputLine))
	{

		istringstream ss(inputLine,';');
		// Customer ID
		getline(ss, temp, ';');
		ID = atoi(temp.c_str());
		// First name
		getline(ss, FirstName, ';');
		// Last name
		getline(ss, LastName, ';');
		// address
		getline(ss, address, ';');
		// city
		getline(ss, city, ';');
		// state
		getline(ss, state, ';');
		// zip
		getline(ss, temp, '\n');
		zip = atoi(temp.c_str());

		// create an object
		customer c(ID, FirstName, LastName, address, city, state, zip);
		temp_customer.push_back(c);

	} // end while

   // At this point, all of the data has been read from the file.
   // close up and return.
	infile.close();

	return;
} // end GetCustomerData

// Function to display the main menu
void displayMenu()
{
	cout << "\tCustomer Menu" << endl
		 << "1. Search a customer by ID" << endl
		 << "2. Search a customer by first name or last name" << endl
		 << "3. Add new customer" << endl
		 << "4. Customer Sale" << endl
		 << "5. Rainbow Tribble list" << endl
		 << "6. Display Sales Report" << endl
		 << "X. Exit" << endl;
}

// Function to get a single character input from the user
char getUserChoice()
{
	char user_input;
	bool validInput = false;

	while (!validInput)
	{
		cout << "Input your option: ";
		cin >> user_input;

		if (cin.peek() == '\n')
		{
			cin.ignore(); // Clear the newline character from the input buffer
			validInput = true;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining characters in the input buffer
			cout << "Invalid input. Please enter a single character." << endl;
		}
	}

	return user_input;
}

// Function to search for a customer by ID
int IDLinearSearch(vector<customer>& data_list, int& target)
{
	for (int i = 0; i < data_list.size(); i++)
	{
		if (data_list[i].getID() == target)
		{
			return i; // Return the index of the target element if found
		}
	}

	return -1; // Return -1 to indicate that the target element was not found
}

bool Is_Existed_Customers_in_Transaction(const Transaction& trans, int target)
{
	for (auto i : trans.getTransactions())
	{
		if (i.customer_id == target)
		{
			return true;
		}
	}

	return false;
}
// Function to search for customers by name
vector<int> NameLinearSearch(vector<customer>& data_list, string& target)
{
	// Create a vector to hold customer names including those who have same names
	vector<int> matchingNames;
	for (int i = 0; i < data_list.size(); i++)
	{
		if (data_list[i].getFirstName() == target || data_list[i].getLastName() == target)
		{
			// Add the index of the matching customer to the vector
			matchingNames.push_back(i);
		}
	}

	return matchingNames; // Return a vector of matching customer indices
}

// Function to generate a new unique customer ID
int generateNewID(vector<customer>& data_list)
{
	int largestID = 0;

	for (int i = 0; i < data_list.size(); i++)
	{
		customer& c = data_list[i];
		// Create an object to hold the data reference to the current customer

		if (c.getID() > largestID)
		{
			largestID = c.getID();
		}
	}

	return largestID + 1; // Generate the new ID by increase 1 to the largest ID
}

// This function is to collect new customer data from input of keyboard
customer Input_NewCustomer(vector<customer>& data_list)
{
	int ID, zip;
	string FirstName, LastName, address, city, state;

	ID = generateNewID(data_list);

	cout << "Enter New Customer Infomation" << endl
		 << "Your new ID is generated automatically: " << ID << endl
		 << "First name: ";
	cin >> FirstName;
	cout << "Last name: ";
	cin >> LastName;
	cout << "Address: ";
	cin.ignore(); // Ignore any newline characters left in the buffer
	getline(cin, address);
	cout << "City: ";
	getline(cin, city);
	cout << "State: ";
	getline(cin, state);
	cout << "ZIP Code: ";
	cin >> zip;

	return customer(ID, FirstName, LastName, address, city, state, zip);
}

// This function is to add new customer information to the existing data file
void Add_NewCustomertoFile(customer& newCus, string& filename)
{
	ofstream outfile(filename, ios::app); // Open file to append new customer

	if (!outfile)
	{
		cerr << "Error - cannot open " << filename << endl;
		exit(1);
	}

	// Append new customer information to the file
	outfile << endl
			<< newCus.getID() << ";"
			<< newCus.getFirstName() << ";"
			<< newCus.getLastName() << ";"
			<< newCus.getAddress() << ";"
			<< newCus.getCity() << ";"
			<< newCus.getState() << ";"
			<< newCus.getZip();

	outfile.close();
}

// Function to get customer order information
string getCustomerOrderInfo(const Transaction& transactions, const int& customer_id, const Order& order)
{
	string customerInfo;
	customerInfo = "";
    // Loop through each transaction in the transactions vector
	for (const Transaction::TransactionInfo& transaction : transactions.getTransactions())
    {
        // Check if the customer ID in the transaction matches the provided customer_id
        if (customer_id == transaction.customer_id)
        {
        	// Retrieve the order for the current transaction
        	Transaction::TransactionInfo specificTransaction;
        	specificTransaction = transactions.getTransaction(transaction.order_id);
        	if (specificTransaction.order_id != "Not Found")
        	{
            	Order::OrderData specificOrder;
            	specificOrder = order.getOrder(specificTransaction.order_id);
				// If a matching order is found, construct a string with the customer's information
				// including customer ID, order ID, date, and amount

            	// Use setprecision to limit the number of decimals in the amount
				stringstream amountStream;
				amountStream << fixed << setprecision(2) << specificOrder.amount;

            	customerInfo += "Customer ID: " + to_string(customer_id) + "\nOrder ID: " + transaction.order_id
            	             + "\nDate: " + specificOrder.date
							 + "\nQuantity: " + to_string(specificOrder.quantity)
            	             + "\nAmount: $" + amountStream.str() + "\n";
            }
        }
    }

    // If no matching customer ID or order is found, return a "No orders found" message
    if (customerInfo.empty())
	{
		customerInfo = "No orders found for customer ID " + to_string(customer_id) + ".";
	}

    return customerInfo;
}

// Function to generate a new order ID
string generateOrderID(const string& lastOrderID)
{
    int largestID = 0;
    // Open "orders.txt" to find the largest existing order ID
    ifstream ordersFile("orders.txt");
    string line;

    while (getline(ordersFile, line))
    {
		string orderID = line.substr(0, 6);
		int orderIDInt = stoi(orderID);

		if (orderIDInt > largestID)
		{
			largestID = orderIDInt;
		}
    }

    ordersFile.close();

    // Increment the largest order ID by 1
    largestID++;

    // Format the new order ID to a fixed length of 5 characters
    ostringstream newOrderIDStream;
    newOrderIDStream << setw(6) << setfill('0') << largestID;
    string newOrderID = newOrderIDStream.str();

    return newOrderID;
}

// Function to add a new customer to both orders.txt and transactions.txt files
void addNewOrder(Transaction& trans, Order& order, vector<absSales*>& salesStaff)
{
    string lastOrderID;
    string customerID, date, salespersonID;
    int quantity;
    double amount = 0.0;

    // Read the last order ID from "orders.txt"
    ifstream ordersFile("orders.txt");
    string line;
    while (getline(ordersFile, line))
    {
        // Read the last line to get the last order ID
        lastOrderID = line.substr(0, 6); // Assuming a fixed format for order IDs
    }
    ordersFile.close();

    // Generate a new order ID
    string newOrderID = generateOrderID(lastOrderID);

    // Collect customer information
    cout << "Enter Customer ID: ";
    cin >> customerID;
    cout << "Enter Date (e.g. 1-Jan-90): ";
    cin >> date;
	cout << "Enter salesperson ID (6 digits): ";
	cin >> salespersonID;
    // Validate and collect quantity
    cout << "Enter Quantity (limit 1 to 5): ";
    cin >> quantity;

    while (quantity < 1 || quantity > 5)
    {
        cout << "Invalid quantity. Quantity should be between 1 and 5 tribbles." << endl;
        cout << "Enter Quantity (limit 1 to 5): ";
        cin >> quantity;
    }

	if (quantity == 1)
	{
		amount = 9.50;
	}
	else if (quantity == 2)
	{
		amount = 16.15;
	}
	else if (quantity == 3)
	{
		amount = 25.88;
	}
	else if (quantity == 4)
	{
		amount = 28.15;
	}
	else if (quantity == 5)
	{
		amount = 30.00;
	}

	// Output customer information
	cout << "New Customer Information:" << endl;
	cout << "Customer ID: " << customerID << endl;
	cout << "Order ID: " << newOrderID << endl;
	cout << "Date: " << date << endl;
	cout << "Salesperson ID: " << salespersonID << endl;
	cout << "Quantity: " << quantity << endl;
	cout << "Amount: $ " << amount << endl;

    // Open "orders.txt" for appending
    ofstream ordersFileAppend("orders.txt", ios::app);
    if (!ordersFileAppend)
    {
        cerr << "Error: Could not open 'orders.txt' for appending." << endl;
        return;
    }

    // Append the new customer order to "orders.txt" with the generated order ID
    ordersFileAppend << newOrderID << ";" << date << ";" << quantity << ";" << amount << endl;
    ordersFileAppend.close();
    order.addOrder(Order::OrderData(newOrderID, date, quantity, amount));
    // Open "transactions.txt" for appending
    ofstream transactionsFile("transactions.txt", ios::app);
    if (!transactionsFile)
    {
        cerr << "Error: Could not open 'transactions.txt' for appending." << endl;
        return;
    }

    // Append the new transaction information to "transactions.txt"
    transactionsFile << customerID << ";" << salespersonID << ';' << newOrderID << endl;
    transactionsFile.close();
    trans.addTransaction(Transaction::TransactionInfo(stoi(customerID), salespersonID, newOrderID));
    cout << "New customer added successfully with order ID: " << newOrderID << endl;

    // Update sales information for the salesperson and their supervisor in the sales report
    for (auto person : salesStaff)
	{
		if (person->getSalesPersonID() == salespersonID)
		{
			person->setTotalSales(person->getTotalSales() + amount);
			person->boss->setEmpSales(person->boss->getEmpSales() + amount);
		}
	}
}

/*------------------------------------------------------------------------------
 * Function: subMenuforCase5
 * - Sub-menu for managing Rainbow Tribble operations
 * - Allows displaying the Rainbow Tribble list, adding customers to the waiting
 * list, and selling Rainbow Tribbles
 -----------------------------------------------------------------------------*/
void subMenuforCase5(RainbowList &rainbowList, const string& filename)
{
	cout << endl
		 << "\tRainbow Tribble List" << endl
		 << "1. Display Rainbow List" << endl
		 << "2. Add a customer to the waiting list" << endl
		 << "3. Sell a rainbow tribble" << endl
		 << "B. Back to Customer Menu" << endl;
    char subMenuChoice = getUserChoice();
    ifstream inputFile(filename);

		if (inputFile.is_open())
		{
			int id;
			while (inputFile >> id)
			{
				rainbowList.addCustomerID(id);
			}

			inputFile.close();
		}
		else
		{
			cout << "Failed to open the rainbowlist.txt file." << endl;
		}
	while (subMenuChoice != 'B' && subMenuChoice != 'b')
	{
		switch (subMenuChoice)
        {
            case '1':
            {
            	// Display Rainbow List
            	cout << "\tRainbow List:" << endl;
            	cout << rainbowList.printCustomerIDs();
                break;
            }
            case '2':
            {
            	// Add a customer to the waiting list
            	int ID;
				cout << "Enter customer ID: ";
				if (!(cin >> ID))
				{
					cout << "Invalid input. Customer ID must be numeric. Please try again." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
				{
					rainbowList.addCustomerID(ID);
					rainbowList.inputNewCustomer(filename);
					cout << "Successfully added customer " << ID << " to the waiting list." << endl;
				}
                break;
            }
            case '3':
            {
            	// Sell a rainbow tribble
            	if (!rainbowList.getCustomerIDs().empty())
				{
					int topCustomerID = rainbowList.getTopCustomerID(rainbowList);
					cout << "Selling a rainbow tribble to customer ID " << topCustomerID << "." << endl;

					int quantityPurchased;
					// Validate and collect quantityPurchased
					cout << "Enter the quantity of rainbow tribbles (limit 1 only): ";

					if (cin >> quantityPurchased && quantityPurchased == 1)
					{
					    double amount = 9.50;

					    cout << "Customer ID: " << topCustomerID << endl;
					    cout << "Quantity purchased: " << quantityPurchased << " tribble." << endl;
					    cout << "Amount: $" << amount << endl;

					    // Remove the customer from the rainbow list
						rainbowList.removeCustomerID(topCustomerID);
					}
					else
					{
						cout << "Invalid quantity. Quantity must be only 1." << endl;
					}
				}
				else
				{
					cout << "The waiting list is empty. No rainbow tribbles to sell." << endl;
				}
                break;
            }
            case 'B':
            case 'b':
            	break;

            default:
                cout << "Invalid input. Please try again." << endl;
        } // end switch

		// Save the rainbow list to the file after each modification
		rainbowList.inputNewCustomer(filename);

		cout << endl
			 << "\tRainbow Tribble List" << endl
			 << "1. Display Rainbow List" << endl
			 << "2. Add a customer to the waiting list" << endl
			 << "3. Sell a rainbow tribble" << endl
			 << "B. Back to Customer Menu" << endl;
		subMenuChoice = getUserChoice();
	} // end while loop
}

void readData(vector<absSales*>& s, Transaction& trans, Order& order)
{
    // Open the file "salesStaff.txt" for reading
    ifstream infile("salesStaff.txt");
    if (!infile)
    {
        // If the file cannot be opened, print an error message and exit the program
        cerr << "Error - cannot open salesStaff.txt" << endl;
        exit(1);
    }

    string inputLine;
    string title;
    string name;
    string empID;
    string bossID;

    absSales* p;

    // Read each line from the file
    while (getline(infile, inputLine))
    {
        istringstream ss(inputLine);
        // Parse the line into title, name, employee ID, and boss ID using ';' as the delimiter
        getline(ss, title, ';');
        getline(ss, name, ';');
        getline(ss, empID, ';');
        getline(ss, bossID, ';');

        // Create an object based on the title
        if (title == "Sales")
        {
            p = new Sales(title, name, empID, bossID, trans, order);
        }
        else if (title == "SuperSales")
        {
            p = new superSales(title, name, empID, bossID, trans ,order);
        }
        else if (title == "Supervisor")
        {
            p = new supervisor(title, name, empID, bossID, trans, order);
        }
        else if (title == "Manager")
        {
            p = new manager(title, name, empID, bossID, trans, order);
        }

        // Add the created object to the vector of salespersons
        s.push_back(p);
    }

    // Calculate total sales for each supervisor and people who report to them
    for(auto person : s)
    {
        for (auto boss : s)
        {
            if (person->getBossID() == boss->getSalesPersonID())
            {
            	if (boss->getTitle() != "Manager")
            	{
					supervisor* Supervisor = dynamic_cast<supervisor*>(boss);
					if (Supervisor != nullptr)
					{
						// Set the boss of the person and update the supervisor's total sales
						person->setBoss(Supervisor);
//						cout << person->getTotalSales() << " " << Supervisor->getEmpSales() << endl;
//						cout << "Total: $ " << person->getTotalSales() + Supervisor->getEmpSales() << endl;
						Supervisor->setEmpSales(person->getTotalSales() + Supervisor->getEmpSales());
					}
            	}
            }
        }
    }

    manager* Manager = nullptr;
    // Find the manager in the vector
    for (auto person : s)
    {
        if (person->getTitle() == "Manager")
        {
            Manager = dynamic_cast<manager*>(person);
        }
    }

    // Calculate and print the total sales for the manager's commission
    for (auto person : s)
    {
        if (person->getBossID() == Manager->getSalesPersonID())
        {
            // Check the type of person before accessing getEmpSales
            supervisor* Supervisor = dynamic_cast<supervisor*>(person);
            if (Supervisor != nullptr)
            {
                Manager->incEmpSales(Supervisor->getTotalSales() + Supervisor->getEmpSales());
            }
        }
    }

    // Close the file after reading data
    infile.close();
}

void generateSalesReport(const vector<absSales*>& salesStaff, const Order& orders, const Transaction& transactions)
{
	cout <<"\t\t\t\tSales Report" << endl;
	cout << orders.getOrders().size() << " orders read in" << endl;
	cout << transactions.getTransactions().size() << " transactions read in" << endl;
	cout << salesStaff.size() << " salespersons read in" << endl;
	cout << "empID";
	cout << "\tName";
	cout << setw(26) << "Title";
	cout << setw(26) << "Total Sales";
	cout << setw(19) << "Commissions\n";

	for (int i = 0; i < 82; i++)
		cout << "=";
	cout << endl;

	for (auto person : salesStaff)
	{
		cout << person->getSalesPersonID() << '\t';
		// Display salesperson's title with left alignment
		cout << setw(25) << left << person->getName();
		cout << setw(10) << left << person->getTitle();
		// Display salesperson's total sales with right alignment and formatting
		cout << setw(13) << right << "$ ";
		printf("%.2f", person->getTotalSales());
		cout << '\t';
		cout << setw(11) << right << "$ ";
		printf("%.2f", person->getCommission());
		cout << endl;
	}
}


int main(int argc, char** argv)
{
	vector<customer> CustomerData; // The vector is not the part of customer class
	string filename;
	filename = "customers.txt";
	// The customer names and ID is stored in this file
	int largestID = 0; // Initialize the largest ID to 0
	// Retrieve and print out the data from the file
	GetCustomerData(CustomerData, filename);

	for (int i=0; i < CustomerData.size(); i++)
	{
		if (CustomerData[i].getID() > largestID)
		{
			largestID = CustomerData[i].getID();
		}
	}

	Transaction transaction("transactions.txt");
	Order order("orders.txt");

	string rainbowListFileName;
	rainbowListFileName = "rainbowlist.txt";
	RainbowList rainbowList; // Create a single instance of RainbowList

	// Vector to store instances of absSales and its deprived classes
	vector<absSales*> salesStaff;
	readData(salesStaff, transaction, order);

	displayMenu();
	char choice = getUserChoice();

	while(choice != 'x' && choice != 'X')
	{
		switch (choice)
		{
			case '1':
			{
				int targetID;
				cout << "Enter your ID: ";
				cin >> targetID;
				int resultID;
				resultID = IDLinearSearch(CustomerData, targetID);

				if (resultID != -1)
				{
					cout << "Customer ID " << targetID << " found." << endl;
					cout << CustomerData[resultID].toString() << endl; // Display the matching customer
				}
				else
				{
					cout << "Customer ID " << targetID << " is not found." << endl;
				}
				break;
			}
			case '2':
			{
				string targetName;
				cout << "Enter your first name or last name: ";
				cin >> targetName;
				vector<int> resultName;
				resultName = NameLinearSearch(CustomerData, targetName);

				if (!resultName.empty())
				{
					cout << "Customer name " << targetName << " found." << endl;
					for(int i = 0; i < resultName.size(); i++)
					{
						int name = resultName[i];
						cout << (i+1) << ". " << CustomerData[name].toString() << endl;
					}
					// Display the matching customer
					// In case they have same first name or last name,
					// how to print out all of them whose names are similar?
					cout << endl;
				}
				else
				{
					cout << "No customers with name " << targetName << " is not found." << endl;
				}
				break;
			}
			case '3':
			{
				// Create an object for new customer
				customer newCustomer = Input_NewCustomer(CustomerData);
				Add_NewCustomertoFile(newCustomer, filename);
				CustomerData.push_back(newCustomer);
				cout << "Successfully added new customer!" << endl; // Putting new customer to the object
				break;
			}
			case '4':
			{
				cout << endl
				     << "\tCustomer Sale Options" << endl
					 << "1. Display orders" << endl
					 << "2. Add new order" << endl
					 << "B. Back to Customer Menu" << endl;
				char saleChoice = getUserChoice();
				while (saleChoice != 'B' && saleChoice != 'b')
				{
					switch (saleChoice)
					{
						case '1':
						{
							// Load transactions from file
							cout << "Enter a customer ID: ";
							int customerID_to_find;
							cin >> customerID_to_find;
							if (Is_Existed_Customers_in_Transaction(transaction, customerID_to_find))
							{
								// Customer found, display customer information
								cout << "Customer ID " << customerID_to_find << " found." << endl;
								string customer_info;
								customer_info = getCustomerOrderInfo(transaction, customerID_to_find, order);
								cout << "Information for customer ID: " << endl << customer_info << endl;
							}
							else
							{
								cout << "Customer ID " << customerID_to_find << " is not found." << endl;
							}
							break;
						}

						case '2':
						{
							// Code for adding a new order
							addNewOrder(transaction, order, salesStaff);
							break;
						}

						case 'B':
						case 'b':
							// Return to the main menu
							break;

						default:
							cout << "Invalid option. Please try again." << endl;
					} // end switch

					cout << endl;
					cout << "\tCustomer Sale Options" << endl;
					cout << "1. Display orders" << endl;
					cout << "2. Add new order" << endl;
					cout << "B. Back to Customer Menu" << endl;
					saleChoice = getUserChoice();
				} // end while loop
				break;
			}

			case '5':
			{
				subMenuforCase5(rainbowList, rainbowListFileName); // Pass the RainbowList object to the sub-menu
				break;
			}

			case '6':
			{
				generateSalesReport(salesStaff, order, transaction);
				break;
			}

			case 'x':
			case 'X':
				break;

			default:
				cout << "Invalid input. Please try again." << endl;
		} // end switch
		cout << endl;
		displayMenu();
		choice = getUserChoice();

	} // end while loop

	return 0;
}
