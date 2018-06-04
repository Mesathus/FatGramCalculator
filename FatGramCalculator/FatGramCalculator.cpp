// FatGramCalculator.cpp : Defines the entry point for the console application.
//

/*
	Author: John O'Brien
	6/4/2018
	Chapter 4.18 Fat Gram Calculator

	Problem Goal:
	Write a program that asks for the number of calories and fat grams in a food. The program
	should display the percentage of calories that come from fat. If the calories from
	fat are less than 30% of the total calories of the food, it should also display a message
	indicating that the food is low in fat.
	One gram of fat has 9 calories, so
	Calories from fat  fat grams * 9
	The percentage of calories from fat can be calculated as
	Calories from fat  total calories
	Input Validation: Make sure the number of calories and fat grams are not less than
	0. Also, the number of calories from fat cannot be greater than the total number of
	calories. If that happens, display an error message indicating that either the calories or
	fat grams were incorrectly entered.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctype.h>	//header for isdigit function
using namespace std;


bool TryParse(string toParse, int &result)	//parsing function to take in a string and return a boolean
{
	int value;
	bool number = false;
	for (int i = 0; i < toParse.length(); i++)	//examine each character in our string to determine if it's a number
	{
		if (isdigit(toParse[i]))	//change our flag value to true if the character is a number
		{
			number = true;
		}
		else
		{
			number = false;	//change our flag to false and break out of the loop if it's not a number
			break;	//this would also be a good spot to just return false
		}
	}
	if(number)	//parse the string if all characters are digits
	{
		result = stoi(toParse);	//result is passed by value, changing the variable in main()
	}
	return number;	//return the flag value
}

int main()
{
	//variable declarations
	int fat, calories, calFat;
	string fatSt, calorieSt;
	const int CALORIES_FROM_FAT = 9;
	double calPercent;
	bool result = false;
	while (!result)	//loop so we can continue asking for values if we receive incorrect input
	{
		cout << "Please enter the grams of calories in the food: ";	//receive calorie value
		getline(cin, calorieSt);
		result = TryParse(calorieSt, calories);	//test if it's an integer
		cout << endl << "Please enter the grams of fat in the food: ";	//receive fat value
		getline(cin, fatSt);
		result = TryParse(fatSt, fat);	//test for integer
		if (!result)	//output to indicate invalid input
		{
			cout << "\nPlease be sure to enter only whole numbers as values." << endl << endl;
		}
		if (result)	//further calculation if input is valid
		{
			if (calories > 0 && fat > 0) //ensure both numbers are greater than 0
			{
				if ((fat * CALORIES_FROM_FAT) > calories)	//ensure fat value is possible from calorie count
				{
					cout << "Error in input, please enter grams of calories first, followed by grams of fat." << endl << endl;
					result = false;
				}
				else
				{
					try
					{
						calFat = fat * CALORIES_FROM_FAT;	//calculate calories contributed by fat
						calPercent = static_cast<double>(calFat) / calories * 100;	//calculate the % of calories from fat
						if (calPercent < 30)	//decision if food is low fat
						{
							cout << "The percentage of calories from fat is: " << calPercent << endl << "This is a low fat food.";
						}
						else
						{
							cout << "The percentage of calories from fat is: " << calPercent;
						}
					}
					catch (exception ex)
					{
						cout << "Invalid input.";
						result = false;
					}
				}
			}
			else
			{
				cout << "Input error, please enter whole numbers greater than zero." << endl << endl;
				result = false;
			}
		}
	}
	cin.get();	//pause console for user
    return 0;
}

