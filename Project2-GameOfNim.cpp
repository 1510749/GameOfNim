//File: Project2-GameOfNim.cpp
//Date: 10/25/2018
//Course: CompSci 1
//Description:  This program will be a fool proof program versus a computer in a game of Nim.
//Usage:  This program will ask the user for input for playing the game. That is all.

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <cstring>
#include <cctype>
#include <sstream>

using namespace std;

string Uppercase(string string1) {
	for (int i = 0; i < string1.length(); i++) {
		string1[i] = toupper(string1[i]);
	}
	return string1;
}

int Play(int gamemode2, int stones2, int player2) {
	string notIntegers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+|=\\-[]{}:;\"',./<>?`~";
	int computersMove = 0;
	int playerChoice;
	bool temp1 = false;
	bool temp2 = false;
	string inputChecker;

	if (stones2 != 1) {
		printf("\nThere are %u stones in the pile.\n", stones2);
	}
	else {
		printf("\nThere is %u stone left in the pile.\n", stones2);
	}
//PLAYER'S MOVE
	if (player2 == 0) {
		do {
			//INPUT WARNING
			if (temp1 == true) {
				cout << "You're only allowed to remove 1 to 3 stones." << endl;
			}
			else if (temp2 == true) {
				cout << "You cannot remove that many stones from the stones remaining." << endl;
			}
			inputChecker = "";
			playerChoice = 0;
			cout << "How many stones do you want to remove?:(1-3)" << endl;
			getline(cin, inputChecker);
			inputChecker = Uppercase(inputChecker);
			//CHECKS FOR PROPER INPUT
			for (int i = 0; i < notIntegers.length(); i++) {
				if (inputChecker.find(notIntegers[i]) != string::npos) {
					playerChoice = 10;
				}
			}
			if (playerChoice == 0) {
				stringstream(inputChecker) >> playerChoice;
			}
		} while (!(playerChoice <= 3 && playerChoice >= 1));
		stones2 -= playerChoice;
		cout << "-------------------------" << endl;
	}
//COMPUTER'S MOVE
	else {
		cout << "The computer is making a move..." << endl;
		Sleep(1250);
		if (gamemode2 == 2 && ((stones2 % 4 == 1 && stones2 <= 9) || stones2 == 6)) {
			computersMove = 1;
		}
		else if (gamemode2 == 2 && stones2 <= 5) {
			computersMove = -1 + stones2;
		}
		else {
			do {
				srand(time(0));
				computersMove = (rand() % 3) + 1;
			} while (computersMove > stones2 && computersMove < 4);
		}
		stones2 -= computersMove;
		printf("The computer removed %u stones\n\n", computersMove);

	}
	return stones2;
}

bool WinCheck(int stones2, int player2) {
	if (stones2 == 0 && player2 == 0) {
		cout << "\nYou have won!" << endl;
		return false;
	}
	else if (stones2 == 0 && player2 == 1) {
		cout << "\nYou have lost." << endl;
		return false;
	}
	return true;
}

int main()
{
	bool done = false;
	bool mainMenu = true;
	bool instructions = false;
	bool playing = false;
	string response;

	while (!done) {
//MAIN MENU LOOP
		while (mainMenu) {
			cout << "Welcome to the game of Nim!\n"
				<< left << setw(10) << "1) Play"
				<< left << setw(16) << "2) Instructions"
				<< right << setw(10) << "3) Quit\n";
			getline(cin,response);
			if (response == "1") {
				mainMenu = false;
				playing = true;
			}
			else if (response == "2") {
				mainMenu = false;
				instructions = true;
			}
			else if (response == "3") {
				return 0;
			}
		}
//INSTRUCTIONS LOOP
		while (instructions) {
			cout << "\n\n\n\n\n*Enter \"back\" to return to the main menu.*\nInstructions:\n\nInitially there is a pile of x stones, where x is a random integer between 10 & 21(inclusive)\n"
				<< "\nEach player (the computer vs. the human player) alternates turns removing 1, 2, or 3 stones.\n"
				<< "\nThe player who makes the last move loses.\n\n";
			getline(cin, response);
			cout << "\n\n\n\n\n";
			response = Uppercase(response);
			if (response == "BACK") {
				instructions = false;
				mainMenu = true;
			}
		}
//PLAYING LOOP
		while (playing) {
			bool selectingMode = true;
			int gamemode, player;
//PICKING GAME DIFFICULTY
			do {
				cout << "\n\n\n\n\n*Enter \"back\" to return to the main menu.*\nSelect gamemode: Easy(1) Hard(2)\n";
				getline(cin, response);
				cout << "\n\n\n\n\n";
				response = Uppercase(response);
			} while (response != "1" && response != "2" && response != "BACK");
			if (response == "1") {
				gamemode = 1;
			}
			else if (response == "2") {
				gamemode = 2;
			}
			else {
				playing = false;
				mainMenu = true;
				break;
			}
//PICKING WHO IS FIRST
			srand(time(0));
			player = (rand() % 2);
			if (player == 0) {
				cout << "You go first!" << endl;
			}
			else {
				cout << "The computer goes first!" << endl;
			}
//DETERMINING INITIAL STONES
			int stones = (rand() % 11) + 10;
//PLAY FUNCTION
			bool turns = true;
			while (turns) {
				stones = Play(gamemode, stones, player);
				//switching turns here
				if (player == 1) {
					player = 0;
				}
				else {
					player = 1;
				}
//CHECKS FOR WINNER
				turns = WinCheck(stones, player);
			}
		}
	}
	return 0;
}
