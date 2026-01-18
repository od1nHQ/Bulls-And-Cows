#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <random>
#include <limits>

using namespace std;

void generate_digits_for_game(vector<int>& generate_digits, vector<int>& ask_digits, int& boy_cow_count, int& cow_count);
void restart_game(vector<int>& digits, vector<int>& ask_digits, int& boy_cow_count, int& cow_count, bool& game_over);
int randint(int min, int max);

int main()
{
	bool game_over = false;
	int x1;
	vector<int> digits_for_game;
	vector<int> ask_digits;
	int boy_cow_count = 0, cow_count = 0;
	generate_digits_for_game(digits_for_game, ask_digits, boy_cow_count, cow_count);

	cout << '\n';


	cout <<
		"========================================\n"
		"          BULLS AND COWS GAME           \n"
		"========================================\n"
		"Welcome to the Bulls and Cows game!\n"
		"\n"
		"Rules:\n"
		"1. Guess the 4-digit number.\n"
		"2. Each digit is unique.\n"
		"3. After each guess, you will see:\n"
		"   - Bulls: correct digit in correct position\n"
		"   - Cows:  correct digit in wrong position\n"
		"\n"
		"Try to guess the number in as few attempts as possible.\n"
		"\n"
		"Enter 4 digits separated by space (e.g. 1 2 3 4): \n"
		"----------------------------------------\n\n";



	while (!game_over)
	{
		if (!(cin >> x1))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Enter a number.\n";
			continue;
		}
		ask_digits.push_back(x1);
		if (ask_digits.size() == 4)
		{

			restart_game(digits_for_game, ask_digits, boy_cow_count, cow_count, game_over);

		}
	}

	return 0;
}


void generate_digits_for_game(vector<int>& generate_digits, vector<int>& ask_digits, int& boy_cow_count, int& cow_count)
{
	ask_digits.clear();
	boy_cow_count = cow_count = 0;

	generate_digits.clear();

	while (generate_digits.size() < 4)
	{
		int n = randint(0, 9);

		if (find(generate_digits.begin(), generate_digits.end(), n) == generate_digits.end())
		{
			generate_digits.push_back(n);
		}
	}

}

void restart_game(vector<int>& digits, vector<int>& ask_digits, int& boy_cow_count, int& cow_count, bool& game_state)
{
	if (digits == ask_digits)
	{
		cout << "\n********************************\n";
		cout << "*         YOU WIN!!!           *\n";
		cout << "*      4 Bulls, 0 Cows         *\n";
		cout << "********************************\n\n";
		cout << "Do you want to play again? (y/n)\n";

		char answer;
		while (true) {
			cin >> answer;

			if (answer == 'y') {
				generate_digits_for_game(digits, ask_digits, boy_cow_count, cow_count);
				cout << "Enter 4 digits separated by space: \n\n";
				break;
			}
			else if (answer == 'n') {
				game_state = true;
				break;
			}
			else {
				cout << "You need to answer y or n. Try again.\n";
			}
		}



	}
	else {

		set<int> unique_check(ask_digits.begin(), ask_digits.end());

		if (unique_check.size() < ask_digits.size())
		{
			cout << "\nEach digit must be unique! Try again.\n\n";
			ask_digits.clear();
			return;
		}



		for (int i = 0; i < digits.size(); i++)
		{
			for (int j = 0; j < ask_digits.size(); j++)
			{
				if (i == j)
				{
					if (digits[i] == ask_digits[i]) boy_cow_count++;
					continue;
				}
				else if (i != j)
				{
					if (digits[i] == ask_digits[j]) cow_count++;
				}
			}
		}


		cout << "\n==============================\n";
		cout << "Results of your guess:\n";
		cout << "Bulls: " << boy_cow_count << "\n";
		cout << "Cows:  " << cow_count << "\n";
		cout << "==============================\n\n";




		ask_digits.clear();
		boy_cow_count = cow_count = 0;
	}
}

int randint(int min, int max) {
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dist(min, max);
	return dist(gen);
}