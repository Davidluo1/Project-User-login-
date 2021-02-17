#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
void GameAccount();
bool islogin()													// Login function check for correct account name and password
{	
	string account, password, acc, pass;

	cout << "\nLogin:\nEnter the account name: ";
	cin >> account;
	cout << "Enter the password: ";
	cin >> password;
	
	ifstream file("Account.txt");								// Create a file called Account.txt

	while (!file.eof())											// Loop through Account.txt to check if there is a exist account created
	{	
		getline(file, acc);										
		getline(file, pass);
		if (acc == account && pass == password)
		{
			return true;
		}
		else { return false; }
	}	
	file.close();												// Close the file
}

void Game(const string &name)
{
	cout << "Game Start!\n";
}

void Chat(string name)												// Chat function: send message and display chat history
{
	bool chat = true;
	ofstream chat_history;
	ifstream read_chat;
	string message, item;

	cout << "\nWelcome to the chatting room! Let's chat!\nEnter exist to leave the chat room\n";
	while (chat == true)
	{
		cout << "Enter message: ";							
		getline(cin, message);

		if (message == "Exist" || message == "exist")					// Exist the program 
		{
			cout << "Logged out.\n";
			break;
		}
		chat_history.open("ChatHistory.txt",ios::app);					// Open and append item to ChatHistroy.txt 
		chat_history << name << ": " << message << endl;
		chat_history.close();											// Close the file
		

		int count = 0;
		read_chat.open("ChatHistory.txt");								// Open the ChatHistroy.txt to read
		cout << "Chat room:\n";
		while (!read_chat.eof())										// loop and print all the items in ChatHistroy.txt 
		{
			count++;
			getline(read_chat, item);
			cout << item << endl;
		}
		read_chat.close();												// Close the file
		if (count > 20)													// Remove all the items in ChatHistroy.txt when number of items reaches 20
		{
			remove("ChatHistory.txt");	
		}

	}
}

int main()
{
	int choice;
	string name;
	GameAccount();														// Function to create an account

	cout << "\n1: Chat room\n2: Game\nYour choice: ";
	cin >> choice;
	cin.ignore();														// Ignore to avoid conflicts between cin and getline
	cout << "Create your name: ";
	getline(cin, name);


	if (choice == 1)													// If statement to choice program between chat and game
	{
		Chat(name);
	}
	else if (choice == 2)
	{
		Game(name);
	}

	
	system("pause");
	return 0;
}

void GameAccount()
{
	int choice;
	bool run = true;
	vector<string> password_check;


	while (run == true)
	{
		cout << "\n1: Login\n2: Register\nChoice: ";
		cin >> choice;

		if (choice == 1)												// Check if the login account and password is registered 
		{
			bool status = islogin();

			if (!status)
			{
				cout << "Information you entered does not match the data or didn't exist\n";
			}
			else
			{
				run = false;
				cout << "Successfully logged in!\n";
			}
		}
		else if (choice == 2)											// Register account option
		{
			string account_name, password;

			/* Input: account name & password
				Two inputs of password to a vector check 
				if they match and its security measure*/
			cout << "Please enter the account name: ";
			cin >> account_name;
			cout << "Please enter the password: ";
			cin >> password;
			password_check.push_back(password);
			cout << "Please enter the password again: ";
			cin >> password;
			password_check.push_back(password);

			if (password_check[0] != password_check[1])							// Check if password matches
			{
				cout << "Password you entered does not match!\n";
				password_check.pop_back();										// Clean the vector
				password_check.pop_back();
			}
			else if (account_name.length() < 5)									// Security measures: length
			{
				cout << "Your account name is too short.\n";
			}
			else if (password.length() <= 5)
			{
				cout << "Your password is too short.\n";
			}
			else
			{
				int count = 0;
				for (auto element : password)									// Security measures: should contain symbols or upper case letter
				{
					if (char(element) >= 48 && char(element) <= 57 || char(element) >= 97 && char(element) <= 122)     
					{
						count++;
					}
				}
				if (password.length() == count)
				{
					cout << "Your password should contain at least one Captial or symbol.\n";
					continue;
				}
				ofstream file;
				file.open("Account.txt",ios::app);								// Open and append account information into the file
				file << account_name << endl << password << endl;
				file.close();													// Close file
				cout << "Register successfully!\n";
			}
		}
	}
}
