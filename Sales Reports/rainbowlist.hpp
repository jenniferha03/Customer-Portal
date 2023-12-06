#ifndef RAINBOWLIST_HPP
#define RAINBOWLIST_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class RainbowList
{
private:
    vector<int> customerIDs;
    string filename;

public:
    // Getter for customer IDs
    vector<int> getCustomerIDs() const
    {
        return customerIDs;
    }

    // Setter to set the list of customer IDs
    void setCustomerIDs(const vector<int>& ids)
    {
        customerIDs = ids;
    }

    // Add a new customer ID to the list
    void addCustomerID(int id)
    {
        customerIDs.push_back(id);

    }

    void inputNewCustomer(const string& filename)
    {
        ofstream outputFile(filename);
        if (outputFile.is_open())
        {
            for (int id : customerIDs)
            {
                outputFile << id << endl;
            }
            outputFile.close();
        }
        else
        {
            cerr << "Failed to open " << filename << " for writing." << endl;
        }
    }

    // Remove a specific customer ID from the list
    bool removeCustomerID(int id)
    {
        auto it = find(customerIDs.begin(), customerIDs.end(), id);
        if (it != customerIDs.end())
        {
            customerIDs.erase(it);
            return true;
        }
        return false;
    }
    
    int getTopCustomerID(const RainbowList& rainbowList)
    {
        vector<int> customerIDs = rainbowList.getCustomerIDs();
        if (!customerIDs.empty())
        {
            return customerIDs.front(); // The first customer ID in the list
        }
        else
        {
            return -1; // Handle the case where the list is empty (no customer IDs)
        }
    }


    // Function to print the list of customer IDs
    string printCustomerIDs()
    {
    	ostringstream msg;
        cout << "Customer IDs in Rainbow List: " << endl;
        for (int id : customerIDs)
        {
           	char ID_temp[7];
        	snprintf(ID_temp, sizeof(ID_temp), "%06d", id);
        	msg << ID_temp << " ";

        }
        msg << endl;
        return msg.str();
    }
};

#endif // RAINBOWLIST_HPP
