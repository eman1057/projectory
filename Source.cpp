#include <iostream>
#include <cstdlib>
#include <time.h>
#define NOMINMAX
#include <windows.h> 
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
using namespace std;

void main_menu();
void set_Cards(int[][25], int N); //initialises Player's Card
bool already(int arr[][25], int n); //checks for a number's existence in Card and returns true/false
void display_Card(int arr[][25], int turn);//displays a player's Card
void remove_Num(int arr[][25], const int num); //remove a specific number from a player's Card
bool check_Win(int arr[][25], int& playerscore);//checks for win condition and returns true/false
void instructions();  //displays the instructions on how to play
void nextLine(int n); //performs endl n times
void exp(int& n);  //makes sure an integer is input by user and prevents errors
void exp(char& n); // makes sure a charachter is input by user and prevents errors
void bubbleSort(int scores[], string names[]);//sort the highscores
void readScore(string names[], int highScores[]);
void save_Game(fstream& file, int player1[][25], int player2[][25], int turn, string name1, string name2);//save game after each round
void save_Record(string name, string names[], int highscore[]);
void highScores(string names[], int highscore[]);
void Set_History(int gameid, int size, string name1, string name2, int turn);
void gameHistory();
bool validate_Name(string name, int size);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //used to change colors in console
int GameId, Size;

int main() {
	fstream file;
	int highscore[100] = {};
	string names[100] = {};
	int player1[25][25];
	int player2[25][25];
	int turn, choose, score1 = 0, score2 = 0, numbers;
	bool win, placed;
	char choice = 'z', selection;
	string name1, name2, temp;
	int name1length, name2length;

	srand(time(0)); //seeding time for random number
	cout << "\n\n\n";

	while (choice != 'e') {  //code runs until user chooses 'e' to exit

		main_menu(); //displays main menu
		cout << "Enter Your Choice: ";
		exp(choice);
		choice = tolower(choice);//incase user enters with caps on 

		switch (choice) {
		case 'a':
			win = false;  //initialize win to false so game continues until win becomes true
			cout << "Press (N) To Start New Game\nPress (C) To Continue Previous Game\nEnter Your Choice: ";
			exp(selection);
			selection = tolower(selection);

			while (selection != 'c' && selection != 'n') {   //if user inputs a wrong value
				cout << "Invalid Choice, Enter Again\n";
				cout << "Press (N) To Start New Game\nPress (C) To Continue Previous Game\nEnter Your Choice: ";
				exp(selection);
				selection = tolower(selection);   //incase user enters with caps on
			}

			if (selection == 'n') {    //If option for a new game is selected
				cout << "Enter size : ";
				exp(Size);
				cin.ignore(); //incase user enters a charachter after number by mistake
				while (Size < 4 || Size > 25) { //as game is playable for minimum 4 size and max 25 size
					cout << "\aEnter a valid Size 4-25: ";
					exp(Size);
					cin.ignore();
				}

				if (Size > 7) {//set console full screen if size greater than 7 is chosen
					keybd_event(VK_MENU, 0x36, 0, 0);
					keybd_event(VK_RETURN, 0x1c, 0, 0);
					keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
					nextLine(5);
					SetConsoleTextAttribute(hConsole, 4 + (3 * 16));
					cout << "\aFullScreen Set For Optimal Display\nIf you wish to use windowed mode,Press FN + F11";
					SetConsoleTextAttribute(hConsole, (3 * 16));
					nextLine(5);
				}

				numbers = Size * Size; //numbers that will be stored in array
				cout << "Player 1 Enter Your Name: ";
				getline(cin, name1);

				name1length = name1.length();

				while ((validate_Name(name1, name1length)) == false) { //prompt to re enter name if it has special characters or numbers
					cout << "Name cannot contain any special characters or numbers!\nPlayer 1 Re-enter your Name: ";
					getline(cin, name1);
					name1length = name1.length();
				}

				cout << "Player 2 Enter Your Name: ";
				getline(cin, name2);
				while (name2 == name1) { //loop to make sure both players enter a different name
					cout << "Both Players Name are same\nEnter Again!: ";
					getline(cin, name2);
					name2length = name2.length();
				}
				name2length = name2.length();
				while ((validate_Name(name2, name2length)) == false) { //prompt to re enter name if it has special characters or numbers
					cout << "Name cannot contain any special characters or numbers!\nPlayer 2 Re-enter your Name: ";
					getline(cin, name2);
					name2length = name2.length();
				}

				GameId = ((rand() % 9000) + 1000);
				set_Cards(player1, numbers);   //call the function to set up card for player 1
				set_Cards(player2, numbers);   //call the function to set up card for player 2
				turn = (rand() % 2) + 1;  //randomly choose which player will have the first turn
				score1 = 0;
				score2 = 0;
				save_Game(file, player1, player2, turn, name1, name2);//incase players exit game as soon as they start we need an initial save
			}
			else {
				file.open("SaveGame.txt", ios::in);
				if (file.peek() == ' ' || file.peek() == ifstream::traits_type::eof()) {//incase file was made for first time or a game was ended before
					cout << "No Previous Record Found!";
					return 0;
				}
				else {
					file >> temp;
					file.ignore();
					Size = stoi(temp);
					file >> temp;
					file.ignore();
					GameId = stoi(temp);
					file >> temp;
					file.ignore();
					turn = stoi(temp);
					getline(file, name1);
					getline(file, name2);
					for (int i = 0; i < Size; i++) {
						for (int j = 0; j < Size; j++) {
							getline(file, temp, ' ');
							player1[i][j] = stoi(temp);
						}
					}
					for (int i = 0; i < Size; i++) {
						for (int j = 0; j < Size; j++) {
							getline(file, temp, ' ');
							player2[i][j] = stoi(temp);
						}
					}
					numbers = Size * Size;
					win = false;
					file.close();
					cout << "Game Resumed Successfully!\n";
					system("pause");
				}
			}

			do {   //game does not end until win becomes true

				if (turn == 1) {    //If the first player has turn output his card and ask him to choose a number
					display_Card(player1, turn);
					cout << name1 << " Enter which number to pick: ";
				}
				else if (turn == 2) {    //If the second player has turn output his card and ask him to choose a number
					display_Card(player2, turn);
					cout << name2 << " Enter which number to pick: ";
				}

				exp(choose);
				cin.ignore();//incase user enters a charachter after number by mistake
				if (choose == -1) {  //temporary
					cout << "Game Exited Successfully";
					return 0;
				}
				placed = already(player1, choose); //checks if the chosen number exists in card

				while (choose < 1 || choose >numbers || placed == false) {   //loop to make sure that user inputs a valid number and a number that is not already chosen
					cout << "\aEnter a valid card not already placed between 1 and " << numbers << ": ";
					exp(choose);
					placed = already(player1, choose); // would work regardless of card deck of any player
					if (placed && choose > 1 && choose < numbers) {
						break;
					}

				}
				remove_Num(player1, choose);   //calling remove_Num to setchosen number to 0
				remove_Num(player2, choose);  //does not matter in what order i remove from both arrays

				if (turn == 1) {       //call check_Win to check win conditions for players whose turn it is
					win = check_Win(player1, score1);
				}
				else if (turn == 2) {
					win = check_Win(player2, score2);
				}
				if (win == false && turn == 1) {  //switch turn variable as the player with his turn has chosen his number
					turn = 2;
				}
				else if (win == false && turn == 2) {
					turn = 1;
				}
				else { //enters else if any of the player has won
					if (turn == 1) {  //if turn was 1 that means player 1 won
						nextLine(22);
						cout << "\aCongratulations " << name1 << " ,You Won!";
						file.open("SaveGame.txt", ios::out);
						file << ' ';//make file empty if a game ended
						file.close();
						save_Record(name1, names, highscore); //Update the highscores
						Set_History(GameId, Size, name1, name2, turn);//update the game history
						nextLine(21);
						score1 = 1;
						score2 = 0;
						system("pause");
						nextLine(21);
					}
					else if (turn == 2) {
						nextLine(22);
						cout << "\aCongratulations " << name2 << " ,You Won!";
						file.open("SaveGame.txt", ios::out);
						file << ' ';//make file empty if a game ended
						file.close();
						save_Record(name2, names, highscore); //Update the highscores
						Set_History(GameId, Size, name1, name2, turn);//update the game history
						nextLine(21);
						score1 = 0;
						score2 = 1;
						system("pause");
						nextLine(21);
					}
				}
				if (win == false) { //if a player has won the game no need to savegame
					save_Game(file, player1, player2, turn, name1, name2);
				}
			} while (win == false);
			break;


		case 'b':
			gameHistory();//displays the game history
			break;
		case 'c':
			highScores(names, highscore);
			break;
		case 'd':
			instructions();   //call the instructions function to display the instructions
			break;
		case 'e':  //if user chose to exit
			cout << "Game Ended!\n\n";
			break;
		default:
			cout << "Invalid choice,Choose again\a\n\n\n\n "; //if user enters an invalid choice
		}
	}
	system("pause");
	return 0;
}

void main_menu() {  //displays main menu
	system("Color 30"); //change colors

	//displaying ascii art bingo!
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(hConsole, 4 + (3 * 16));
	cout << " \t\t\t\t ________  ___  ________   ________  ________  ___       " << endl;
	cout << "\t\t\t\t|\\   __  \\|\\  \\|\\   ___  \\|\\   ____\\|\\   __  \\|\\  \\      " << endl;
	cout << "\t\t\t\t\\ \\  \\|\\ /\\ \\  \\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\     " << endl;
	cout << "\t\t\t\t \\ \\   __  \\ \\  \\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\    " << endl;
	cout << "\t\t\t\t  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\__\\   " << endl;
	cout << "\t\t\t\t   \\ \\_______\\ \\__\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\|__|   " << endl;
	cout << "\t\t\t\t    \\|_______|\\|__|\\|__| \\|__|\\|_______|\\|_______|   ___ " << endl;
	cout << "\t\t\t\t                                                    |\\__\\" << endl;
	cout << "\t\t\t\t                                                    \\|__|" << endl;
	SetConsoleTextAttribute(hConsole, (3 * 16)); // changes colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n\n";

	SetConsoleTextAttribute(hConsole, (3 * 16));//change colors
	nextLine(4);

	cout << "\t\t\t\t\t\t A) Play Game\n";
	cout << "\t\t\t\t\t\t B) Game History\n";
	cout << "\t\t\t\t\t\t C) View High Scores\n";
	cout << "\t\t\t\t\t\t D) How to Play ?\n";
	cout << "\t\t\t\t\t\t E) Exit\n";
	nextLine(8);
}

bool already(int arr[][25], const int n) {  //checks if a number exists in a card or not 
	bool flag = false;
	for (int i = 0; i < Size; i++) {     //nested loop to ccheck for a value in array
		for (int j = 0; j < Size; j++) {
			if (arr[i][j] == n) {
				flag = true;    //if the value entered is found
			}
		}
	}
	return flag;
}

void set_Cards(int arr[][25], const int N) { //sets a player's card
	bool flag = true;
	int num;
	for (int i = 0; i < Size; i++) {     //nested loop to insert into array the values;
		for (int j = 0; j < Size; j++) {
			while (flag == true) {
				num = (rand() % N) + 1;
				flag = already(arr, num);//if the random number already exists then the loop will run again and generate a new random number
			}
			arr[i][j] = num;
			flag = true;
		}
	}
}

void display_Card(int arr[][25], const int turn) {  //displays a player's card

	if (turn == 1) {  // displaying different color windows for each player
		system("Color F0");
	}
	else {
		system("Color E0");
	}

	nextLine(44);//calling function to move to next page(44 line feeds used)
	cout << "Game ID : " << GameId << "\n\nPlayer " << turn << " Cards \n\n\n";

	for (int i = 1; i <= Size * 5; i++) {   //printing 5 hyphens per column
		cout << "-";
	}
	cout << "\n B    I    N    G    O\n";
	for (int i = 1; i <= Size * 5; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < Size; i++) {     //nested loop to display the player card
		for (int j = 0; j < Size; j++) {
			if (arr[i][j] < 1000 && arr[i][j] >= 100) { //To make sure the numbers and spaces are displayed properly based on number of digits
				//do nothing
			}
			else if (arr[i][j] < 100 && arr[i][j] >= 10) {
				cout << " ";
			}
			else if (arr[i][j] < 10 && arr[i][j] >= 0) {
				cout << "  ";
			}
			cout << arr[i][j];
			if (arr[i][j] < 1000 && arr[i][j] >= 100) {
				cout << " ";
			}
			else if (arr[i][j] < 100 && arr[i][j] >= 10) {
				cout << " ";
			}
			else if (arr[i][j] < 10 && arr[i][j] >= 0) {
				cout << " ";
			}
			cout << "|";
		}
		cout << endl;
		for (int i = 1; i <= Size * 5; i++) {
			cout << "-";
		}
		cout << endl;
	}
	nextLine(6);
}

void remove_Num(int arr[][25], const int num) {  //function to find a number in array and set it to zero
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (arr[i][j] == num) {  //if value found at index then set it to zero
				arr[i][j] = 0;
			}
		}
	}
}

bool check_Win(int arr[][25], int& playerscore) { //checks for win conditions of a player
	int i = 0, j = 0, count = 0;
	int row = 0, col = 0, diag = 0;  //to hold count if any row column or diagonal has all zeros

	while (i < Size) { //nested loop to check each row for number of zeroes
		count = 0;
		j = 0;
		while (j < Size) {
			if (arr[i][j] == 0) {
				count++;
			}
			j++;
		}
		if (count == Size) {   //count has to be equal to size for condition to be true
			row++;
		}
		i++;
	}
	count = 0; //reset values for next case check
	i = 0;
	j = 0;

	while (i < Size) { //nested loop to check each column for number of zeroes
		count = 0;
		j = 0;
		while (j < Size) {
			if (arr[j][i] == 0) {  //to count number of zeroes
				count++;
			}
			j++;
		}
		if (count == Size) {  //count has to be equal to size for condition to be true
			col++;
		}
		i++;
	}
	count = 0;  //reset values for next case check
	i = 0;
	j = 0;

	while (i < Size) {  //checking  diagonal
		if (arr[i][j] == 0) {
			count++;
		}
		i++;
		j++;
	}
	if (count == Size) {  //count has to be equal to size for condition to be true
		diag++;
	}
	count = 0;   //reset values for next case check
	i = Size - 1;
	j = 0;

	while (j < Size) { //checking anti diagonal
		if (arr[i][j] == 0) {
			count++;
		}
		i--;
		j++;
	}
	if (count == Size) {  //count has to be equal for condition to be true
		diag++;
	}
	playerscore = (row + col + diag);
	if ((row + col + diag) >= 5) {//all of the three conditions need to be true and in total 5 or more for win
		return true;
	}
	else {
		return false;
	}
}

void instructions() { //displays how to play
	nextLine(6);
	system("Color 2F");  //changes colors
	SetConsoleTextAttribute(hConsole, (2 * 16));//change colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(hConsole, 7 + (2 * 16)); //changes colors
	cout << "\t\t   _____ _   _  _____ _______ _____  _    _  _____ _______ _____  ____  _   _  _____ " << endl;
	cout << "\t\t  |_   _| \\ | |/ ____|__   __|  __ \\| |  | |/ ____|__   __|_   _|/ __ \\| \\ | |/ ____|" << endl;
	cout << "\t\t    | | |  \\| | (___    | |  | |__) | |  | | |       | |    | | | |  | |  \\| | (___  " << endl;
	cout << "\t\t    | | | . ` |\\___ \\   | |  |  _  /| |  | | |       | |    | | | |  | | . ` |\\___ \\ " << endl;
	cout << "\t\t   _| |_| |\\  |____) |  | |  | | \\ \\| |__| | |____   | |   _| |_| |__| | |\\  |____) |" << endl;
	cout << "\t\t  |_____|_| \\_|_____/   |_|  |_|  \\_\\_____/ \\_____|  |_|  |_____|\\____/|_| \\_|_____/ " << endl;
	SetConsoleTextAttribute(hConsole, (2 * 16)); //changes colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n\n";


	cout << "1. Objective:\n - The goal of Bingo is to match numbers on your card with randomly called numbers.\n\n";
	cout << "2. Game Setup :\n - Each player receives a NxN Bingo card ; N is provided by user.\n - Numbers on the card are arranged randomly.\n\n";
	cout << "3. Calling Numbers :\n - A caller randomly selects numbers one at a time.\n\n";
	cout << "4. Marking Numbers :\n - The called number is set to 0 on both player's cards.\n\n";
	cout << "5. Winning Patterns :\n - Players aim to complete specific patterns, such as one horizontal, vertical or diagonal of 0s.\n\n";
	cout << " - The first player to complete atleast five pattern wins.\n\n\n";

	SetConsoleTextAttribute(hConsole, 4 + (2 * 16));  //change colors
	system("pause"); //allows user to press a key to continue 
	nextLine(7);
}

void nextLine(int n) { //performs endl n times
	for (int i = 1; i <= n; i++) {
		cout << endl;
	}
}

void exp(int& n) { //function to make sure an integer value is input
	while (true) {
		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter an integer input.\n";
		}
		else {
			break;
		}
	}

}

void exp(char& n) {  //function to make sure a charachter is input
	while (!(cin >> n) || cin.get() != '\n' || isspace(n)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a single character: ";
	}

}

bool validate_Name(string name, int size) {
	for (int i = 0; i < size; i++) {
		if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) {
			return false;
		}
	}
	return true;
}

void save_Game(fstream& file, int player1[][25], int player2[][25], int turn, string name1, string name2) { //save game after each round
	file.open("SaveGame.txt", ios::out);
	file << Size << endl << GameId << endl << turn << endl << name1 << endl << name2 << endl;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			file << player1[i][j] << " ";
		}
		file << endl;
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			file << player2[i][j] << " ";
		}
		file << endl;
	}
	file.close();
}
void bubbleSort(int scores[], string names[]) { //performs bubble sort on the two arrays
	int temp;
	string temporary;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 99 - i; j++) {
			if (scores[j] < scores[j + 1]) {
				temp = scores[j];
				temporary = names[j];
				scores[j] = scores[j + 1];
				names[j] = names[j + 1];
				scores[j + 1] = temp;
				names[j + 1] = temporary;
			}
		}
	}
}

void readScore(string names[], int highscore[]) { //reads highscores from a file into the arrays
	fstream score;
	score.open("HighScore.txt", ios::in);
	for (int i = 0; i < 100; i++) { //read from file into array the record
		getline(score, names[i], ',');
		score >> highscore[i];
		score.ignore(); // Ignore the newline character
	}
	score.close();
}
void save_Record(string name, string names[], int highscore[]) { //saves the highscores into a file
	int pos = -1; //to find position of free index.
	fstream score;
	readScore(names, highscore);//reads highscore record into array
	bool placed = false;
	int index = 0;
	while (placed == false && index < 100) {
		if (name == names[index]) {
			highscore[index] = highscore[index] + 1;
			placed = true;
		}
		index++;
	}
	if (placed == true) {
		bubbleSort(highscore, names);//sort the array after each update in highscores
	}
	else {
		for (int i = 0; i < 100; i++) { //loop checks first free position in the array
			if (highscore[i] == -1) {
				pos = i;
				break;
			}
		}
		if (pos == -1) { //incase all the database(array) was already full 
			cout << "DataBase is Full,We are unable to store your highscore!\n";
		}
		else {
			names[pos] = name;
			highscore[pos] = 1;//as player must have played an won first time in order for this line to run
		}
	}
	score.open("HighScore.txt", ios::out);
	for (int i = 0; i < 100; i++) {
		score << names[i] << ',' << highscore[i] << endl;
	}
	score.close();
}
void highScores(string names[], int highscore[]) { //displays the highscores
	int index = 0;
	nextLine(20);
	readScore(names, highscore); // reads high score record into array
	system("Color C0"); // change colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(hConsole, 7 + (12 * 16)); // changes colors
	cout << "\t\t\t         __  ______________  __   _____ __________  ____  ___________\n";
	cout << "\t\t\t        / / / /  _/ ____/ / / /  / ___// ____/ __ \\/ __ \\/ ____/ ___/\n";
	cout << "\t\t\t       / /_/ // // / __/ /_/ /   \\__ \\/ /   / / / / /_/ / __/  \\__ \\ \n";
	cout << "\t\t\t      / __  _/ // /_/ / __  /   ___/ / /___/ /_/ / _, _/ /___ ___/ / \n";
	cout << "\t\t\t     /_/ /_/___/\\____/_/ /_/   /____/\\____/\\____/_/ |_/_____//____/\n";
	SetConsoleTextAttribute(hConsole, (12 * 16)); // changes colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n\n";
	while (index < 10 && highscore[index] != -1) { // printing only the top 10 scores if stored
		cout << "\t\t\t\t" << index + 1 << ". ";
		if (index != 9) {// to display all the scores correctly
			cout << " ";
		}
		cout << setw(30) << left << names[index] << ": " << setw(10) << right << highscore[index] << endl;
		index++;
	}
	nextLine(10);
	SetConsoleTextAttribute(hConsole, 7 + (12 * 16)); // changes colors
	system("pause");
}
void Set_History(int gameid, int size, string name1, string name2, int turn) {
	fstream history, temporary;
	int lines = 0;
	string temp;
	history.open("GameHistory.txt", ios::in);
	while (!history.eof()) {
		lines++;
		history >> temp;//read to move to next line
		if (history.eof()) {
			break;
		}
	}
	history.close();
	if (lines >= 50) { //if 10 game's data are stored already than overwrite otherwise add
		temporary.open("Temp.txt", ios::out);
		history.open("GameHistory.txt", ios::in);//to read from this file to temp file all records except first
		for (int i = 0; i < 5; i++) {//not going to need the first record which consists of 5 lines
			getline(history, temp);  //will not use these lines
		}
		for (int i = 1; i <= 45; i++) { //reading the last 9 records
			getline(history, temp);
			temporary << temp << endl;
		}
		history.close();
		temporary.close();
		temporary.open("Temp.txt", ios::in);
		history.open("GameHistory.txt", ios::out);//will write new record and other 9 records from temporary files now
		for (int i = 1; i <= 45; i++) { //reading and writing the 9 records from Temp.txt to GameHistory.txt
			getline(temporary, temp);
			history << temp << endl;
		}
		history << gameid << endl << size << endl << name1 << endl << name2 << endl << turn << endl;//appending the new record at the end of file
		history.close();
		temporary.close();
	}
	else {
		history.open("GameHistory.txt", ios::app);//will append new record at the end of file
		history << gameid << endl << size << endl << name1 << endl << name2 << endl << turn << endl;
		history.close();
	}
}
void gameHistory() {
	fstream history;
	int i = 1;
	string temp, name1, name2;
	nextLine(25);
	system("Color 90"); // change colors
	SetConsoleTextAttribute(hConsole, (9 * 16)); // changes colors
	cout << "----------------------------------------------------------------------------------------------------------------------\n";
	SetConsoleTextAttribute(hConsole, 4 + (9 * 16)); // changes colors
	cout << "\t\t\t\t    _    _ _____  _____ _______ ____  _______     __" << endl;
	cout << "\t\t\t\t   | |  | |_   _|/ ____|__   __/ __ \\|  __ \\ \\   / /" << endl;
	cout << "\t\t\t\t   | |__| | | | | (___    | | | |  | | |__) \\ \\_/ /" << endl;
	cout << "\t\t\t\t   |  __  | | |  \\___ \\   | | | |  | |  _  / \\   /" << endl;
	cout << "\t\t\t\t   | |  | |_| |_ ____) |  | | | |__| | | \\ \\  | |" << endl;
	cout << "\t\t\t\t   |_|  |_|_____|_____/   |_|  \\____/|_|  \\_\\ |_|";
	SetConsoleTextAttribute(hConsole, (9 * 16)); // changes colors
	cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
	nextLine(5);
	SetConsoleTextAttribute(hConsole, 7 + (9 * 16)); // changes colors
	history.open("GameHistory.txt", ios::in);
	while (i <= 10 && getline(history, temp)) {
		cout << i << ".\n";
		cout << "\tGameId: " << temp << endl;
		getline(history, temp);
		cout << "\tSize: " << temp << endl;
		getline(history, temp);
		name1 = temp; // may be used later to display winner
		cout << "\tPlayer 1: " << temp << endl;
		getline(history, temp);
		name2 = temp; // may be used later to display winner
		cout << "\tPlayer 2: " << temp << endl;
		getline(history, temp); // this line gets the turn if the turn was 1 than player 1 was winner other wise player 2

		if (temp == "1") {
			cout << "\tWinner: " << name1 << endl;
		}
		else if (temp == "2") {
			cout << "\tWinner: " << name2 << endl;
		}
		nextLine(2);
		i++;
		if (i % 3 == 0) { // to properly allow the user to see the history and avoid scrolling
			cout << "Press Enter to continue...";
			cin.get();
			nextLine(2);
		}
	}
	history.close();
	nextLine(8);
	cout << "Press Enter to continue...";
	cin.get();
}

