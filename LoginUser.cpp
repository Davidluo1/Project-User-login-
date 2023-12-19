#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;
void GameAccount();

# create borad game display
void displayBoard(char board[][3])												// Board isplay funtion
{
	cout << "Welcome to the Tic Tac Toe game!\n";										// Game introdution
	cout << "1" << "|" << "2" << "|" << "3" << endl;
	cout << "4" << "|" << "5" << "|" << "6" << endl;
	cout << "7" << "|" << "8" << "|" << "9" << endl;
	cout << "\nEnter the position that you want to place your mark.\n";
	cout << board[0][0] << " |" << board[0][1] << " |" << board[0][2] << endl;
	cout << "--|--|--\n";
	cout << board[1][0] << " |" << board[1][1] << " |" << board[1][2] << endl;
	cout << "--|--|--\n";
	cout << board[2][0] << " |" << board[2][1] << " |" << board[2][2] << endl;
}

# Player winning condition
bool PlayerWin(char board[][3], char Player)											// Player winning condition
{
	if (board[0][0] == Player && board[0][1] == Player && board[0][2] == Player) { return true; }
	else if (board[1][0] == Player && board[1][1] == Player && board[1][2] == Player) { return true; }
	else if (board[2][0] == Player && board[2][1] == Player && board[2][2] == Player) { return true; }
	else if (board[0][0] == Player && board[1][0] == Player && board[2][0] == Player) { return true; }
	else if (board[0][1] == Player && board[1][1] == Player && board[2][1] == Player) { return true; }
	else if (board[0][2] == Player && board[1][2] == Player && board[2][2] == Player) { return true; }
	else if (board[0][0] == Player && board[1][1] == Player && board[2][2] == Player) { return true; }
	else if (board[0][2] == Player && board[1][1] == Player && board[2][0] == Player) { return true; }
	else { return false; }

}

# robot winning condition
bool RobotWin(char board[][3], char robot)											// Robot winning condition
{
	if (board[0][0] == robot && board[0][1] == robot && board[0][2] == robot) { return true; }
	else if (board[1][0] == robot && board[1][1] == robot && board[1][2] == robot) { return true; }
	else if (board[2][0] == robot && board[2][1] == robot && board[2][2] == robot) { return true; }
	else if (board[0][0] == robot && board[1][0] == robot && board[2][0] == robot) { return true; }
	else if (board[0][1] == robot && board[1][1] == robot && board[2][1] == robot) { return true; }
	else if (board[0][2] == robot && board[1][2] == robot && board[2][2] == robot) { return true; }
	else if (board[0][0] == robot && board[1][1] == robot && board[2][2] == robot) { return true; }
	else if (board[0][2] == robot && board[1][1] == robot && board[2][0] == robot) { return true; }
	else { return false; }
}

# robot movement
void robotMove(char board[][3])									// Robot move function
{
	int randrow, randcolumn;
	srand(time(0));

	for (int i = 0; i < 10; i++)								// choose a random spot to place X
	{
		randcolumn = rand() % 3;
		randrow = rand() % 3;
		if (board[randrow][randcolumn] == ' ' && !PlayerWin(board, 'O'))
		{
			board[randrow][randcolumn] = 'X';
			break;
		}
	}
}

# Tie check
bool isBoardFull(char board[][3])								// Check tie condition: when there is no empty space
{
	int count = 0;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ') { count++; }
		}
	}
	
	if (count == 0 && !PlayerWin(board, 'O') && !RobotWin(board, 'X')) {
		return true;
	}
	else { return false; }
}

# Login check
bool islogin()											// Login function check for correct account name and password
{	
	string account, password, acc, pass;

	cout << "\nLogin:\nEnter the account name: ";
	cin >> account;
	cout << "Enter the password: ";
	cin >> password;
	
	ifstream file("Account.txt");								// Create a file called Account.txt

	while (!file.eof())									// Loop through Account.txt to check if there is a exist account created
	{	
		getline(file, acc);										
		getline(file, pass);
		if (acc == account && pass == password)
		{
			return true;
		}
	}	
	file.close();										// Close the file
	return false;
}

void Game(const string &name)
{
	cout << "Game Start!\n";
	char command, choice;
	bool play = true;

	while (play == true)
	{
		int score = 0;
		char board[3][3] = { 	{' ',' ',' '},						// Basic board design
					            {' ',' ',' '},
					            {' ',' ',' '} };
		
		while (true) {
			displayBoard(board);															
			if (score < 0)
			{
				cout << "Games over! Robot wins this time.\n";
				play = false;
				break;
			}
			/* // condition which tie, player win, or robot win */
			if (PlayerWin(board, 'O')) { 
				cout << "Player Wins!\n";
				score++; 
				cout << "Your current score is: " << score << endl;
				break; 
			}
			else if (isBoardFull(board)) { cout << "Tie! The board is full.\n\n\n"; break; }
			if (RobotWin(board, 'X')) { 
				cout << "Robot Wins!\n"; 
				score--; 
				cout << "Your current score is: " << score << endl;
				break; 
			}
			else if (isBoardFull(board)) { cout << "Tie! The board is full.\n\n\n"; break; }
			cin >> command;
			if (command == 'q' ) { break; }							// Player move
			else
			{
				switch (command)
				{
				case '1':
					if (board[0][0] == ' ') { board[0][0] = 'O'; robotMove(board);}
					break;
				case '2':
					if (board[0][1] == ' ') { board[0][1] = 'O'; robotMove(board);}
					break;
				case '3':
					if (board[0][2] == ' ') { board[0][2] = 'O'; robotMove(board);}
					break;
				case '4':
					if (board[1][0] == ' ') { board[1][0] = 'O'; robotMove(board);}
					break;
				case '5':
					if (board[1][1] == ' ') { board[1][1] = 'O'; robotMove(board);}
					break;
				case '6':
					if (board[1][2] == ' ') { board[1][2] = 'O'; robotMove(board);}
					break;
				case '7':
					if (board[2][0] == ' ') { board[2][0] = 'O'; robotMove(board);}
					break;
				case '8':
					if (board[2][1] == ' ') { board[2][1] = 'O'; robotMove(board);}
					break;
				case '9':
					if (board[2][2] == ' ') { board[2][2] = 'O'; robotMove(board);}
					break;
				default:
					cout << "Invalid input\n";
					break;
				}
				// robotMove(board);								            // Display updated board
			}
		}
		cout << "Want to play another round?(y/n): ";						// Multiple plays allowed
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			cout << "Thanks for playing!\n";
			play = false;
		}
		else if (choice == 'y' || choice == 'Y')
		{
			play = true;
		}
	}
}

void Chat(string name)											// Chat function: send message and display chat history
{
	bool chat = true;
	ofstream chat_history;
	ifstream read_chat;
	string message, item;

	cout << "\nWelcome to the chatting room! Let's chat!\nEnter exist to leave the chat room\n\n";
	while (chat == true)
	{
		cout << "Enter message: ";							
		getline(cin, message);

		if (message == "Exist" || message == "exist")						// Exist the Chat room 
		{
			chat = false;
		}
		else
		{
			chat_history.open("ChatHistory.txt", ios::app);					// Open and append item to ChatHistroy.txt 
			chat_history << name << ": " << message << endl;
			chat_history.close();								// Close the file


			int count = 0;
			read_chat.open("ChatHistory.txt");						// Open the ChatHistroy.txt to read
			cout << "\nChat room:\n";
			while (!read_chat.eof())							// Print chat history: loop and print all the items in ChatHistroy.txt 
			{
				count++;
				getline(read_chat, item);
				cout << item << endl;
			}
			read_chat.close();								// Close the file

			if (count > 20)									// Remove all the items in ChatHistroy.txt when number of items reaches 20
			{
				remove("ChatHistory.txt");
			}
		}
	}
}

# Game account registeration
void GameAccount()
{
	string choice;
	bool run = true;
	vector<string> password_check;


	while (run == true)
	{
		cout << "\n1: Login\n2: Register\nChoice: ";
		cin >> choice;

		if (choice == "1")									// Check if the login account and password is registered 
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
		else if (choice == "2")									// Register account option
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

			if (password_check[0] != password_check[1])					// Check if password matches
			{
				cout << "Password you entered does not match!\n";
				password_check.pop_back();						// Clean the vector
				password_check.pop_back();
			}
			else if (account_name.length() < 5)						// Security measures: length
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
				for (auto element : password)						// Security measures: should contain symbols or upper case letter
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
				file.open("Account.txt",ios::app);					// Open and append account information into the file
				file << account_name << endl << password << endl;
				file.close();								// Close file
				cout << "Register successfully!\n";
			}
		}
		else { cout << "Inavlid input!\n"; }
	}
}

# main function
int main()
{
	string choice;
	string name;

	# declare Game Function
	GameAccount();											// Function to create an account

	cout << "Create your name (no space please): ";
	cin >> name;

	# Game start
	while (true) {
		cout << "\n1: Chat room\n2: Game\nYour choice (Enter q log out): ";
		cin >> choice;

		if (choice == "1")									// If statement to choice program between chat and game
		{
			Chat(name);
		}
		else if (choice == "2")
		{
			Game(name);
		}
		else if (choice == "q")
		{
			cout << "logged out.\n";
			break;
		}
		else
		{
			cout << "Inavlid choice.\n";
		}
	}

	system("pause");
	return 0;
}
