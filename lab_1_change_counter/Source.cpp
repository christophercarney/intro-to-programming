#include <iostream>
using namespace std;

int main()
{
	int amount;     // amount of money to come up with (input)
	int quarters;   // number of quarters required (output)
	int nickels;    // number of nickels required (output)
	int pennies;    // number of pennies required;
	int dimes;
	cout << "How much money do we need? ";
	cin >> amount;  

	quarters = amount / 25;
	amount = amount % 25;

	dimes = amount / 10;
	amount = amount % 10;

	nickels = amount / 5;

	pennies = amount % 5;

	cout << "Your totals in quarters, nickels, dimes, and pennies (respectively) are: " << endl;
	cout << quarters << endl;
	cout << dimes << endl;
	cout << nickels << endl;
	cout << pennies << endl;
}