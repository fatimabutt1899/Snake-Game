#include<iostream>
#include<string>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<istream>
#include<fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
void loader();
const int width = 60, hight = 20;//FOR WIDTH/HIGHT OF FRAME
int foodx, foody;
int x, y;//FOR CONTROLLING X/Y AXIS
int score = 0;//FOR ADDING SCORE
int tailx[200] = { 0 }, taily[200] = { 0 };
int tail = 0;
string name;
string records;
enum direction { LEFT, RIGHT, UP, DOWN };
direction dir;
COORD coord;
bool gameover;//FOR STARTING GAME

int numArr[10], arrNum = 0;
string nameArr[10];// only for 10 records

void sorting();
void file_handling();

void loader()
{
	int barl = 50;
	system("color 0e");
	cout << "\n\n\n\n\n\n\t\t\t\tLOADING SYSTEM, PLEASE WAIT.." << endl;
	cout << "\t\t\t[";
	for (int i = 0; i < barl; i++) {
		Sleep(10);
		cout << char(254);
	}
	cout << "]" << endl;
	cout << "\n\t\t\t\t\tSystem loaded";
	for (int i = 0; i < barl; i++) {
		Sleep(50);
	}
}
void start() {
	system("cls");
	gameover = false;
	x = width / 2;//SET THE VALUE OF X=20
	y = hight / 2;//SET THE VALUE OF Y=10
	foodx = rand() % width;//RANDOMLY GENERATE FOOD OF X AXIS
	foody = rand() % hight;//RANDOMLY GENERATE FOOD OF Y AXIS
}
void frame()
{

	for (int i = 0; i < width + 2; i++)
		cout << char(254);//FOR PRINTING UPPER WALL MEAN CEALING
	cout << endl;
	for (int i = 0; i < hight; i++) {//FOR PRINTING SIDE WALLS
		for (int j = 0; j < width; j++) {
			if (j == 0) {//PRINT LEFT SIDE WALL
				cout << char(219);
			}
			if (i == y && j == x)//FOR MAKING THE SNAKE HEAD IN CENTRE
				cout << char(153);
			else if (i == foody && j == foodx)//FOR GENERATING RANDOM FOOD IN FRAME
				cout << "@";
			else {
				bool print = false;
				for (int k = 0; k < tail; k++) {
					if (tailx[k] == j && taily[k] == i) {
						cout << "0";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
			if (j == width - 1) {//FOR PRINTING RIGHT SIDE WALL
				cout << char(219);
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {//FOR PRINTING LOWER WALL MEAN FLOOR
		cout << char(254);
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
}

void direct() {
	if (_kbhit()) {//WHEN USER ENTER THE KEYBOARD
		switch (_getch()) {//IT TAKES CHARACTER
		case'a':
			dir = LEFT;
			break;
		case's':
			dir = DOWN;
			break;
		case'w':
			dir = UP;
			break;
		case'd':
			dir = RIGHT;
			break;
		}
	}
}
void move() {
	int previousx = tailx[0];
	int previousy = taily[0];
	int prev2x = 0;
	int prev2y = 0;
	tailx[0] = x;//remind first tail value of x axis
	taily[0] = y;//remind second tail value of y-ais
	for (int i = 1; i < tail; i++) {//for reminding previous tail position
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = previousx;
		taily[i] = previousy;
		previousx = prev2x;
		previousy = prev2y;
	}
	switch (dir) {
	case LEFT://decrease value of x when a is pressed
		x--;
		break;
	case RIGHT://increase value of x when a is pressed
		x++;
		break;
	case UP:
		y--;//decrease value of y when w is pressed
		break;
	case DOWN:
		y++;//increase value of y when s is pressed
		break;
	default:
		break;
	}
	if (x > width - 1 || x<0 || y > hight - 1 || y < 0)//when snake hit the wall game end
		gameover = true;
	for (int i = 0; i < tail; i++) {
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}

	if (x == foodx && y == foody) {//WHEN FOODX=x AND FOODY=y then generate new food
		foodx = rand() % width;
		foody = rand() % hight;
		tail++;
		score += 10;//when food is eaten then score added by ten
	}
}
int get_rank(std::string input) {
	std::stringstream ss(input);
	std::string s;
	// keep extracting strings, last one would be your 'int' rank
	for (; ss >> s;);
	return std::atoi(s.c_str());
}

void file_handling()
{
	string line;
	int i = 1, len, num = 0;
	string cpyScore;
	system("cls");
	nameArr[0] = name + "\t";
	numArr[0] = score;
	cout << "-------------SCOREBOARD----------------" << endl;
	fstream MyFile("records.txt", ios::in); // reading from file
	if (MyFile.is_open())
	{
		while (MyFile)
		{
			arrNum++;
			len = 0;
			getline(MyFile, line);// to clear buffer
			if (line == "")
				break;
			len = line.size();
			len -= 5;
			nameArr[i] = line.substr(0, len);
			cpyScore = line.substr(len, 5);
			len += 5;
			numArr[i] = stoi(cpyScore); // converting score taken from file to int
			i++;
		}
		sorting();
	}
	else
		cout << "Error, could not read from file" << endl;
	MyFile.close();
	remove("records.txt"); // deletes the content of file // deleting the previous
	// content so that new content can be inserted

	MyFile.open("records.txt", ios::app);// writing data in the file/ ------------------ move thissss
	if (MyFile.is_open())
	{
		for (int i = 0; i < arrNum; i++)
		{
			len = numArr[i];
			cpyScore = to_string(numArr[i]);
			len = to_string(len).length();
			if (len == 4)
				cpyScore = "0" + cpyScore;
			else if (len == 3)
				cpyScore = "00" + cpyScore;
			else if (len == 2)
				cpyScore = "000" + cpyScore;
			else if (len == 1)
				cpyScore = "0000" + cpyScore;
			MyFile << nameArr[i] << cpyScore << endl;
			cout << nameArr[i] << cpyScore << endl;
		}
	}
	else
		cout << "Error! File could not be created";
	MyFile.close();
}
void sorting()
{
	for (int pas = 0; pas < arrNum + 1; pas++)
	{
		for (int j = 0; j < (arrNum - pas - 1); j++)
		{
			if (numArr[j] < numArr[j + 1])
			{
				int temp1 = numArr[j];
				numArr[j] = numArr[j + 1];
				numArr[j + 1] = temp1;
				string temp2 = nameArr[j];
				nameArr[j] = nameArr[j + 1];
				nameArr[j + 1] = temp2;
			}
		}
	}
}

int main() {
	char choice;

	srand(time(NULL));// for rand function to work
	loader();
	system("cls");
	cout << "\n\n\n\t\t\t\t THE SNAKE GAME\n\n";
	cout << "\t\t\t\t  Group members" << endl;
	cout << "\t\t\t\t-----------------" << endl;
	cout << "\n\t\t\t  1.Muhammad Nawfal Burhan\n\t\t\t  2.Fatima Butt\n\t\t\t  3.Abdul Sameeh Qureshi\n\n";
	cout << "\tCONTROLS:\n\n\tw=UP\n\ts=DOWN\n\ta=RIGHT\n\td=LEFT\n\n\n    Please enter your username:";
	cin >> name;
	ofstream MyFile;
	start();
	while (!gameover) {//game condition is true
		frame();
		direct();
		move();
		Sleep(100);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	system("cls");

	cout << "\n\n\n\t\t\t\t     Game over :(\n" << "\t\t\t\t---------------------" << "\n\t\t\t\tBetter luck next time\n";
	cout << "\n\n\t" << name << " , you scored : " << score << endl;
	cout << "\n\n\tDo you want to see the scoreboard? (y/n) :";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		file_handling();
	}
	system("pause");
}