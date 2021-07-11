// Oath defence calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
using namespace std;

enum DEFENCE_DIE_RESULT
{
	BLANK,
	ONE,
	TWO,
	DOUBLE
};


int GetInput(string prompt)
{
	while (true)
	{
		string input;
		std::cout << prompt + '\n';
		std::cin >> input;

		int n = stoi(input); // How many dice do we roll?
		if (n < 0)
		{
			std::cout << "Invalid input. Input mus be a natural number.\n";
			continue;
		}
		else
			return n;
	}
}

void GenerateDiceValues(DEFENCE_DIE_RESULT *values, int length) // We fill an array with randomly generated results
{

	for (int i = 0; i < length; i++)
	{
		int result = (rand() % 6) + 1; // We roll an integer between 1 and 6
		//cout << to_string(i+1) + " -> ";
		switch (result)
		{
		case 1:
		case 2:
			//cout << "BLANK\n";
			values[i] = BLANK;
			break;

		case 3:
		case 4:
			//cout << "ONE\n";
			values[i] = ONE;
			break;

		case 5:
			//cout << "TWO\n";
			values[i] = TWO;
			break;

		case 6:
			//cout << "DOUBLE\n";
			values[i] = DOUBLE;
			break;

		default:
			break;
		}
	}
}

int GetDefenceScore(DEFENCE_DIE_RESULT *values, int length, int base) // We 
{
	int defenceScore = 0;
	int doubling     = 0;

	for (int i = 0; i < length; i++)
	{
		switch (values[i])
		{
		case ONE:
			defenceScore += 1;
			break;

		case TWO:
			defenceScore += 2;
			break;
			
		case DOUBLE:
			doubling	 += 1;
			break;

		default:
			break;
		}
	}

	defenceScore += base; 
	defenceScore *= pow(2, doubling);
	return defenceScore;
}

float GetAverage(int *values, int n)
{
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += values[i];

	}

	return sum/n;
}

int main()
{
	srand(time(0)); // seed RNG with current time
	rand(); // clean up the rand
		
	std::string input;
	std::cout << "Welcome to Esko's Oath Defence calculator!\n";
	while (true)
	{

		// Retrieve input.
		int baseDefense = GetInput("How much base defence do you have?");
		int nDice       = GetInput("How many dice do you want to roll?");
		int simCount    = GetInput("How many times do you want the roll to be simulated?");

		cout << "Simulating...";

		DEFENCE_DIE_RESULT *diceValues = new DEFENCE_DIE_RESULT[nDice]; // Dynamically allocate a new array to store our data.

		int *scores = new int[simCount];
		for (int i = 0; i < simCount; i++)
		{
			GenerateDiceValues(diceValues, nDice);
			scores[i] = GetDefenceScore(diceValues, nDice, baseDefense);
		}
		
		float average = GetAverage(scores, simCount);

		delete[] scores;
		delete[] diceValues; // Delete dynamically allocated operator

		std::cout << "Defence score: " + to_string(average) + '\n';
	}
}

