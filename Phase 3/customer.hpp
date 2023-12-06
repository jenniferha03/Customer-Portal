/*
 * customer.hpp
 *
 *  Created on: Sep 23, 2023
 *      Author: jenniferha
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> // needed for toString()
#include <cstdio>

using namespace std;

class customer {
private:
	int CustomerID;
	string FirstName;
	string LastName;
	string address;
	string city;
	string state;
	int zip;

public:
	//constructors
	customer() // default constructor
	{
		CustomerID = 0;
		FirstName = "";
		LastName = "";
		address = "";
		city = "";
		state = "";
		zip = 0;
	}

	//destructor
	~customer() { };

	//accessors
	int getID()
	{
		return CustomerID;
	}
	string getFirstName()
	{
		return FirstName;
	}
	string getLastName()
	{
		return LastName;
	}
	string getAddress()
	{
		return address;
	}
	string getCity()
	{
		return city;
	}
	string getState()
	{
		return state;
	}
	int getZip()
	{
		return zip;
	}


	// Set all customer information
	void setAll(int CusID, string FirstName, string LastName, string address, string city, string state, int zip)
	{
		this->CustomerID = CusID;
		this->FirstName = FirstName;
		this->LastName = LastName;
		this->address = address;
		this->city = city;
		this->state = state;
		this->zip = zip;
	}

	// Constructor that initializes customer with provided data
	customer(string data) {
		setAll(CustomerID, FirstName, LastName, address, city, state, zip);
	}

	// Constructor that allows creating a customer with provided information
	customer(int CustomerID, string FirstName, string LastName, string address, string city, string state, int zip) {
		setAll(CustomerID, FirstName, LastName, address, city, state, zip);
	}

	// Convert the customer information to a string
	string toString() {
		ostringstream msg;
		char ID_temp[7];
		snprintf(ID_temp, sizeof(ID_temp), "%06d", CustomerID);
		char zip_temp[6];
		snprintf(zip_temp, sizeof(zip_temp), "%05d", zip);
		msg << ID_temp << " "
			<< this->FirstName << " "
			<< this->LastName << ", "
			<< this->address << ", "
			<< this->city << ", "
			<< this->state << ", "
			<< zip_temp;
		return msg.str();
	}
}; // end of customer class
