#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Transaction {
public:
	// Structure to store transaction information
    struct TransactionInfo
	{
        int customer_id; // Customer ID associated with the transaction
        string salesperson_id; // Salesperson ID associated with the transaction
        string order_id; // Order ID for the transaction

        TransactionInfo(int cus_id, string sale_id, string order_id)
        {
            customer_id = cus_id;
            sale_id = salesperson_id;
            this->order_id = order_id;
        }

        TransactionInfo()
        {
            customer_id = 0;
            salesperson_id = "";
            order_id = "";
        }
    };

private:
	// vector that stored all of the transaction information
    vector<TransactionInfo> transactions;

public:
	//constructor that loads the transactions
    Transaction(const string& file_path)
    {
        loadTransactions(file_path);
    }

	//load everything into the vector and open the file for reading
    void loadTransactions(const string& file_path)
    {
        ifstream file(file_path);
        if (!file)
		{
			cout << "Error: Could not open file " << file_path << endl;
			exit(1);
		}
        string line;
        string temp;

		//separating all the info from the file using the semicolon as a delimiter
        while (getline(file, line))
        {
            stringstream ss(line);
            int customer_id;
            string salesperson_id;
            string order_id;

            getline(ss, temp, ';');
            customer_id = atoi(temp.c_str());
            getline(ss, salesperson_id, ';');
            getline(ss, order_id, '\n');
            order_id.erase(remove(order_id.begin(), order_id.end(), '\r'), order_id.end());

            TransactionInfo info;
            info.customer_id = customer_id;
            info.salesperson_id = salesperson_id;
            info.order_id = order_id;

            transactions.push_back(info);
        }

        file.close();
    }

    // Add this public method to retrieve a transaction by order_id.
	TransactionInfo getTransaction(const string& order_id) const
	{
		for (const TransactionInfo& transaction : transactions)
		{
			if (transaction.order_id == order_id)
			{
				return transaction;
			}
		}

            // If not found, return a default TransactionInfo object.
            TransactionInfo notFoundTransaction;
            notFoundTransaction.customer_id = -1;
            notFoundTransaction.salesperson_id = "Not Found";
            notFoundTransaction.order_id = "Not Found";
            return notFoundTransaction;
        }

	vector<TransactionInfo> getTransactions() const
	{
		return transactions;
	}

    void addTransaction(const TransactionInfo& info)
    {
        transactions.push_back(info);
    }
};
