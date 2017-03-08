// CS135 Project #1
// Math pratice for basic levels

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>//For RNG
#include <ctime> //RNG  need to seed system time for "truly" random numbers
#include <cmath> 
//#include <iomanip>

using namespace std;

void studentTeacher();
void teacherMenu(int attempts);
void studentMenu();
void teacherSettings();
void writeFile(string filepath, string info);
string readFile(string filepath);
void operatorMenu(string name);
void levelMenu(string name, int mathType);
void quiz(char mathType, int &score);
int randNum(int magnitude, bool negatives);
int randNum(int min, int max);
string crappyResponse();
string happyResponse();



//main only used to initiate the first menu function adn to seed RNG
int main()
{
	// Seed random number generator
	unsigned seed = time(0);
	srand(seed);

	studentTeacher();
	return 0;
}

void studentTeacher() // Student, teacher or quit: main menu
{
	const int INITIAL_ATTEMPT = 1; //declaring & assigning in same line, initialization

	int choice;
	bool quit = false;
	/*If using a menu function
	const int TEACHER_CHOICE = 1,
	STUDENT_CHOICE = 2 */
	while (!quit)  //bool shortcut allows us to not need quit == false, b/c bool (quit varible is a bool, expecting a bool in () )
	{
		//system("CLS"); ***need to figure out where to clear screen
		cout << "Main Menu" << endl
			<< "________________" << endl << endl
			<< "\n1. I am an instructor." << endl
			<< "2. I am a student." << endl
			<< "3. Quit." << endl << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			teacherMenu(INITIAL_ATTEMPT); //correct password parameter to get to teacher settings menu
			break;
		case 2:
			studentMenu();
			break;
		case 3:
			quit = true; //assignment
			break;
		default: //anything else, gives message
			cout << "Please enter either option 1, 2 or 3.\n";
		}
	}
}

void teacherMenu(int attempts)
{
	string password;
	cout << "(case-sensitive) Password, please: " << endl;

	cin >> password;

	if (password == "pass") //password correct; == tests equality
	{
		teacherSettings(); //if password is correct, to teacher settings
	}
	else
	{
		if (attempts >= 3)//3 tries
		{
			cout << "Sorry, that password is wrong." << endl; //return to studentTeacher menu if pass wrong
			return;
		}
		else
		{
			teacherMenu(attempts + 1); //each attempt adds 1 to counter
		}
		return;
	}
}


void teacherSettings()//instructor settings
{
	int choice;
	int percentage = 0;
	cout << "Instructor Settings Menu" << endl
		<< "__________________________" << endl << endl;
	cout << "Please choose an option from the following:" << endl << endl;
	cout << "1. Set passing %" << endl; //currently only only option
										//maybe add option to update happy/crappy responses
	cin >> choice;

	switch (choice)
	{
	case 1:
		break;
	}
	if (choice == 1)
	{
		string percentage = readFile("storage/passing_percentage.txt");//read in percentage from file where it's stored as a string only
		cout << "The current percentage is " << percentage << "%, to what would you like to change the passing percentage?" << endl;
		cin >> percentage;
		cout << "The new percentage required to pass a level is " << percentage << "%." << endl; //display new percentage
		writeFile("storage/passing_percentage.txt", percentage);  //output new percentage/write to file
	}
}

//******************
// FILE I/O
//******************

void writeFile(string filepath, string info)
{
	ofstream outputFile; //declare 
	outputFile.open(filepath);//parameter is filepath variable
	outputFile << info; //output the new info to file
	outputFile.close(); //close file
	return;

}

string readFile(string filepath)
{
	ifstream inputFile; //declare
	string info; //file info is stored as a string
	inputFile.open(filepath); //parameter is variable filepath
	inputFile >> info; //reading info from the file
	inputFile.close();
	return info;
}

void studentMenu()
{
	ofstream outputFile;

	string name;
	cout << "Please enter your name with no spaces [first_last]: " << endl;
	cin >> name;
	outputFile.open("storage/users/" + name); //how to incorporate name as variable with the filestream
	operatorMenu(name); //no need for declaration/data type when calling function

}

void operatorMenu(string name)
{
	int choice; //options 1-5 (easier than char or string)


	cout << "Student Menu" << endl
		<< "______________" << endl << endl
		<< "Please enter an option from the following: " << endl << endl
		<< "1. Addition (levels 1-5)" << endl
		<< "2. Subtraction (levels 1-5)" << endl
		<< "3. Multiplication (levels 1-5)" << endl
		<< "4. Division (levels 1-5)" << endl
		<< "5. Combination of all operators (levels 1-5)" << endl << endl;

	cin >> choice;
	switch (choice)
	{
	case 1:
		levelMenu(name, '+'); //each menu parameter gives a menu with the 4 (8) level options 
		break;
	case 2:
		levelMenu(name, '-');
		break;
	case 3:
		levelMenu(name, '*');
		break;
	case 4:
		levelMenu(name, '/');
		break;
	case 5:
		levelMenu(name, 'C');
	default:
		cout << "Please enter a valid selection, 1-5.";
	}
}

void levelMenu(string name, int mathType)
{
	int percentage;
	int level;
	int levels[8]; // array!
	levels[0] = 0;
	cout << "Your unlocked levels: " << endl << endl;
	//need to cout unlocked levels

	cin >> level;
	switch (level)
	{
	case 1:
		quiz(mathType, levels[0]);
		break;

	}
}

void quiz(char mathType, int &score) //char mathType here because we are pulling in the paramenter from operatorMenu
									 //passing scores in the array as a reference 
{
	int level;
	bool negatives;
	level = 1;
	negatives = 0;
	int answer;
	//answer == (num1 mathType num2);
	int quotient;
	int remainder;
	int questions;
	int correctCount = 0;
	
	ifstream inFile;
	int percentage; //need to convert percentage from string (in file) to int for math

	for (questions = 0; questions < 10; questions++) //display 10 questions
	{
		int num1 = randNum(level, negatives);
		int num2 = randNum(level, negatives);
		
		cout << endl << num1 << " " << mathType << " " << num2 << "  =  "; //display equation and prompt for answer

		switch (mathType)
		{
		case '+':
			cin >> answer;

			if (answer == (num1 + num2)) //if correct
			{
				correctCount++; //only working for addition?!
				cout << happyResponse() << endl << endl;
			}
			else // or incorrect (could probably do this outside switch statement
				cout << "Incorrect. The answer is " << (num1 + num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case '-':
			cin >> answer;
			if (answer == (num1 - num2))
			{
				correctCount++;
				cout << happyResponse() << endl << endl;
			}
			else
				cout << "Incorrect. The answer is " << (num1 - num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case '*':
			cin >> answer;
			if (answer == (num1 * num2))
			{
				correctCount++;
				cout << happyResponse() << endl << endl;
			}
			else
				cout << "Incorrect. The answer is " << (num1 * num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case '/':
			if (num2 == 0)
				num2 += 1;
			cout << "please enter quotient (without remainder):  ";
			cin >> quotient;
			cout << "and remainder:  ";
			cin >> remainder;
			if ((quotient == (num1 / num2)) && (remainder == (num1 % num2)))
			{
				correctCount++;
				cout << happyResponse() << endl << endl;
			}
			else
				cout << "Incorrect. The answer is " << (num1 / num2) << " with R = " << (num1 % num2) << "." << endl
				<< crappyResponse() << endl << endl;
			break;
		case 'C':
			//cin >> answer
			//how to randomize this?
			//how to deal with quotients again?
			break;
		}
		//calculate percentage correct after these 10 problems
		//int score;
		// int score = () need to define correct answer so I can use it
		
	}
     inFile.open("storage/passing_percentage.txt"); //open percentage file
	 inFile >> percentage; //read in current passing percentage from file where it's stored
	 inFile.close();
	  

	if (correctCount * 10 >= percentage) //this part is (incorrectly) always true due to not reading the proper file.
	{
		cout << percentage;
		//int percentage = readFile("storage/passing_percentage.txt"); //read in current passing percentage from file where it's stored
		cout << "Your score is " << (correctCount * 10) << "%. " << " Congratulations, you are ready to move on to the next level!" << endl << endl; 
		//displays total score
	}
	else
	{
		cout << "Your score is " << (correctCount * 10) << "%." << "Please see your teacher for some extra help." << endl << endl; 
	}
}

int randNum(int level, bool negatives)
{
	int magnitude = pow(10, level); //magnitude for multiple digits according to level
	int num;

	num = rand() % magnitude;

	return num;
}

int randNum(int min, int max)
{
	int x = (rand() % (max - min + 1)) + min;
	return x;
}

string happyResponse()
//generate random response
{
	//srand up top
	const int MIN_SIZE = 0;
	const int MAX_SIZE = 9;
	string response;
	string responses[10]; //negative responses will be in diff scope, so reuse variable
	responses[0] = "Correct!";
	responses[1] = "Great job!";
	responses[2] = "Cool beans!";
	responses[3] = "Correct-o-mundo!";
	responses[4] = "Cowabunga, dude!";
	responses[5] = "Smashing!";
	responses[6] = "Super-duper!";
	responses[7] = "Someone had their milk this morning!";
	responses[8] = "Awesome, keep it up!";
	responses[9] = "Bingo!";


	//generate an index for array
	int index = randNum(MIN_SIZE, MAX_SIZE);  //initializing index for array
	response = responses[index];

	return response;
}

string crappyResponse()
{
	const int MIN_SIZE = 0;
	const int MAX_SIZE = 9;
	string response;
	string responses[10]; //positive responses in diff scope, so reusing variable
	responses[0] = "Bummer, dude!";
	responses[1] = "Oops! Try again";
	responses[2] = "Bullocks!";
	responses[3] = "Mmm...Let's try another.";
	responses[4] = "Drat!";
	responses[5] = "False!";
	responses[6] = "Sorry, that's incorrect.";
	responses[7] = "Scat!";
	responses[8] = "Oh, no!";
	responses[9] = "Whoops! Keep trying.";


	//generate an index for array
	int index = randNum(MIN_SIZE, MAX_SIZE);  //initializing index for array
	response = responses[index];

	return response;
}
/*
//array for level score keeping
const int LEVELS = 8; //array size
int scores[LEVELS]; //array has 8 elements
ofstream outputFile;

*/

//******************************************
//TO DO:
// - negative numbers for B levels
// - array to store scores and levels
// - display available levels
// - option for mix of all operators
// - determine if new user and create file, or read from existing
// - convert percentage from string to int for comparison
// - not connecting to storage file anymore...
// - correctCount++ only displaying correct score for addition.
//******************************************
