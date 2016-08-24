//Christopher Carney - CRC5464@psu.edu
//October 2013
//Homework #4 - Mastermind Solver in C++

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

//declaring function prototypes for all the functions needed to play
int rollDie(int);
void evaluate(int, int, int&, int&);
int nthDigit(int, int);
void clearNthDigit(int&, int);

//function prototypes needed for mastermind solver
int generateAnswer();
void generateSearchSpace(int[], const int);
void trim (int[],int&, int, int, int);
int methodicalEliminate(int);
int guessAndEliminate(int);
int guessThreeThenEliminate(int);

const int numDigits = 4;			//constants converted from variables in the extra credit of homework 3 
const int dieSides = 8;		 			
int guesses[4096];				//array used to hold values to solve
int extraCredit = 1;				//extra credit variable used to turn extra credit on / off

int main(){

	char playing = 'y';				//variable used to play multiple games

	do{
		extraCredit = 1;							//turn the extra credit off if another game is played (so outputs are displayed)
		int answer = generateAnswer();
		cout << "Guessing at " << answer << endl;	//declares guessing at the number either the computer generates randomly or the player chose
		cout << endl;

		int guessesNeeded = methodicalEliminate(answer);								//Three different methods of guessing all return the Guesses needed to get the correct answer
		cout << "Methodical Eliminate required " << guessesNeeded << " tries." << endl;
		cout << endl;

		guessesNeeded = guessAndEliminate(answer);
		cout << "Guess and Eliminate required " << guessesNeeded << " tries." << endl;
		cout << endl;

		guessesNeeded = guessThreeThenEliminate(answer);
		cout << "Guess Three then Eliminate required " << guessesNeeded << " tries." << endl;
		cout << endl;

		extraCredit = 0;			//sets extra credit variable to on (bool true / false was causing problems)
		int counter = 0;			//counter to count from 1 to 100
		double sumMethodical = 0;	//holds the sum of guesses for each method over 100 trials before taking the average
		double sumGuessElim = 0;
		double sumGuessThree = 0;

		cout << "Simulating 100 trials...please wait..."; 					//100 trials takes a long time to simulate, statement added so user knows this
		while (counter < 100){
			answer = generateAnswer();										//for each new iteration and new random number is generated
			sumMethodical = sumMethodical + methodicalEliminate(answer);	//solves for each method and adds it to the total sum of guesses 
			sumGuessElim = sumGuessElim + guessAndEliminate(answer);
			sumGuessThree = sumGuessThree + guessThreeThenEliminate(answer);
			counter++;														//increments counter, up to 100
			if (counter == 25 || counter == 50 || counter == 75)
				cout << "...";
		}

		cout << endl;
		cout << "After running 100 times, on average it took: " << endl;									//outputting results
		cout << setprecision(3) << "Methodical Eliminate " << (sumMethodical / counter) << " tries." << endl;	//averages are the total sum / trials so the total sum / 100
		cout << setprecision(3) << "Guess and Eliminate " << (sumGuessElim / counter) << " tries." << endl;
		cout << setprecision(3) << "Guess Three Then Eliminate " << (sumGuessThree / counter) << " tries." << endl;
		
		do{
			cout << "Play another round? (y / n)";											//asks to play again
			cin >> playing;
		} while (playing != 'y' && playing != 'n');											//do while used to check for valid input

	} while (playing == 'y');																//runs as long as user inputs 'y'
	
	return 0;
}

//function to generate the computers answer that the player must guess
int generateAnswer(){

	int generate = 0;				//set generate initially to 0 so it generates a random number if extra credit is turned on
						
	if (extraCredit == 1){			//extra credit is off so it asks the user if they want to input a test value
		do {
			cout << "Please enter a combination to try for, or 0 for a random value: " << endl;
			cin >> generate;
		} while ((generate > 8888 || generate < 0 || nthDigit(generate, 1) == 0 || nthDigit(generate, 2) == 0 || nthDigit(generate, 3) == 0 || 
			nthDigit(generate, 4) == 0 || nthDigit(generate, 1) == 9 || nthDigit(generate, 2) == 9 ||nthDigit(generate, 3) == 9 || 
			nthDigit(generate, 4) == 9) && generate != 0);	//checks for invalid inputs. Anything negative, anything over 8888, and any number with a 0 or 9 in it
	}

	if (generate == 0){
		int power = 10;
		int answer = rollDie(dieSides);							//gets the first digit of the combination (furthest one to the right)
		for (int counter = numDigits; counter > 1; counter--){
			answer = (rollDie(dieSides) * power) + answer;		//for loop to repeat the number of times the player wants the length of the answer to be 
			power = power * 10;									//increases by a power of 10 to add the next number to the left
		}														//example if numDigits = 4; (6 * 1000) + (5*100) + (2*10) + 1 = 6521 (the computer generated answer)
		return answer;
	}
	else{
		int answer = generate;									//if generate isn't 0 then the player has their own test number
		return answer;											//use that as the answer and return that number
	}
}

void generateSearchSpace(int guesses[], int length){		//function to generate an array with values 1111-8888, excluding any numbers with 0's or 9's

	int space = 0;												//the first "space" in the array aka the subscript
	int number = 1111;											//the first number we know we need to add to the array
	while (space < length){								//start with subscript and go all the way up to one minus the length (4096 - 1) to encompass all subscripts available

		int position = 1;										//sets a position variable to scan for 0's and 9's
		while (position <= 4){
			if (nthDigit(number, position) == 0 || nthDigit(number, position) == 9){ //scans through the number's 4 position and looks for 0's and 9's
				number++;															 //if one is found, skip that number (do not add to array)
				position = 1;														 //set position back to 1 to scan the next number
			}
			else
				position++;															//if a 0 or 9 isn't foun in that position, increment it to check the next position
		}
		//when loop exits, current number variable does not have a 0 or 9 in it																			

		guesses[space] = number;	//at the current subscript, add that number so for guesses[0] = 1111
		space++;					//go to the next subscript to add the next number
		number++;					//go to the next number to test

	}
	//once space has reached 4095, the array is populated with with all possible combinations of four-digit values in the range 1 to 8.

}

//function trims the array of guesses that can no longer be correct based on a computer guess which has been evaluated
void trim(int guesses[], int& length, int CompGuess, int blackPegs, int whitePegs){
	
	int space = 0;													//sets subscript to 0 to start scanning through the array from the beginning		
	int whitePegsList = 0;											//two variables for the amount of black and white pegs found per array element
	int blackPegsList = 0;
	int newLength = 0;

	while (space < length){											//scans through every element in the array
		
		evaluate(CompGuess, guesses[space], blackPegsList, whitePegsList);	//evaluates what the computer is guessing vs. the array at a certain element 
																			//returns blackpegs and whitepegs related to the array element
		if(blackPegs != blackPegsList){									//blackPegs are the black pegs already evaluated for the computer's guess
			guesses[space] = 0;												//if the blackPegs in the computer's guess don't equal the black pegs in the array element it cannot be an answer and is eliminated
		}
		
		if(whitePegsList > whitePegs){									//if there are too many white pegs it cannot be an answer so eliminate it
			guesses[space] = 0;
		}

		whitePegsList = 0;													//set array elements pegs = 0 for the next iteration
		blackPegsList = 0;
		space++;															//test the next subscript
	}

	space = 0;																	
	for(int counter = 0; space < length; counter++){						//start at first subscript and go up to the last subscript
		while (guesses[space] == 0 && space < length)					//skip empty elements until you have one with an actual value
			space++;
		if (guesses[counter] == 0){
			guesses[counter] = guesses[space];                              //copy the first actual element in the array and replace the first 0 with that number
			guesses[space] = 0;												//"moving it to the front"
		}
		newLength = counter;												//what the newLength of the array is
		space++;
	}

	length = newLength;														//sends back what the new length is so there is less to scan through
	if (length == 0)														//if length ever == 0 an error has occured so repopulate the length sufficiently
		length = 40;									
}

//function that guesses the first item in the list according to what was eliminated
int methodicalEliminate(int answer){
	int length = 4096;
	generateSearchSpace(guesses, length);								//generates the searchspace to guess from

	int whitePegs = 0;													//initialize pegs and guessesNeeded for the method
	int blackPegs = 0;
	int guessesNeeded = 0;

	int space = 0;														//since it's methodical guess it starts at the first subscript and goes from there
	while (blackPegs != 4){												//when black pegs == 4 the computer has solved it

		blackPegs = 0;													//set black pegs = 0 for every subscript tested
		whitePegs = 0;

		if (extraCredit == 1)											//if extra credit is enabled output is disabled
			cout << "Guessing " << guesses[space] << "..." << endl;

		evaluate(answer, guesses[space], blackPegs, whitePegs);			//evaluates the computer's guess against the answer, returns whtie and black pegs accordingly
		trim (guesses, length, guesses[space], blackPegs, whitePegs);	//trims the array guesses[] by setting values that cannot be used equal to zero
		guessesNeeded++;												
		space = 0;														//sets subscript back to zero because it always guesses the first value in the list			

	}

	return guessesNeeded;
}

//method that guesses randomly then used that info to shorten list of possible answers
int guessAndEliminate (int answer){
	int length = 4096;
	generateSearchSpace(guesses, length);			//same as the methodicalEliminate function except...

	int whitePegs = 0;
	int blackPegs = 0;
	int guessesNeeded = 0;

	int space = rand() % length;					//guesses a random number between 0 and 4095
	while (blackPegs != 4){

		blackPegs = 0;
		whitePegs = 0;

		while (guesses[space] == 0)					//if the number in the array has already been cleared choose another random number
			space = rand() % length;

		if (extraCredit == 1)
			cout << "Guessing " << guesses[space] << "..." << endl;

		evaluate(answer, guesses[space], blackPegs, whitePegs);
		trim (guesses, length, guesses[space], blackPegs, whitePegs);
		guessesNeeded++;
		
		if (length != 0)
			space = rand() % length;					//chose another random number to work with

	}

	return guessesNeeded;

}

//makes three guesses randomly BEFORE trimming the list
int guessThreeThenEliminate(int answer){
	int length = 4096;
	generateSearchSpace(guesses, length);		//similar to the other method functions except...

	int space = 0;
	int whitePegs = 0;
	int blackPegs  = 0;
	int guessesNeeded = 3;						//minimum three guesses needed before anything else happens

	int guess1 = guesses[rand() % length];				//chooses three random subscripts to test first before doing anything else
	int guess2 = guesses[rand() % length];				//saves them as a number because the subscripts will be different
	int guess3 = guesses[rand() % length];
	
			
		if (extraCredit == 1){
			cout << "Guessing " << guess1 << "..." << endl;		//outputs the three values it's guessing
			cout << "Guessing " << guess2 << "..." << endl;
			cout << "Guessing " << guess3 << "..." << endl;
		}

			evaluate(answer, guess1, blackPegs, whitePegs);			//send the values to be evaluated and trimmed
			trim (guesses, length, guess1, blackPegs, whitePegs);
			whitePegs = blackPegs = 0;								//reset the pegs for the next test

			evaluate(answer, guess2, blackPegs, whitePegs);
			trim (guesses, length, guess2, blackPegs, whitePegs);
			whitePegs = blackPegs = 0;

			evaluate(answer, guess3, blackPegs, whitePegs);
			trim (guesses, length, guess3, blackPegs, whitePegs);

	if (length != 0)
		space = rand() % length;											//from then on guesses random numbers the same as the Guess and Eliminate function
	
	while (blackPegs != 4){

		blackPegs = 0;
		whitePegs = 0;

		while (guesses[space] == 0)					//if the number in the array has already been cleared choose another random number
			space = rand() % length;

		if (extraCredit == 1)
			cout << "Guessing " << guesses[space] << "..." << endl;

		evaluate(answer, guesses[space], blackPegs, whitePegs);
		trim (guesses, length, guesses[space], blackPegs, whitePegs);
		guessesNeeded++;

		if (length != 0)
			space = rand() % length;

	}
	
	return guessesNeeded;

}


//function to compare the nth digits of the combination and guess and to set the number of whitePegs and blackPegs given for a guess
void evaluate( int guess, int answer, int &black, int &white )
{
	black = 0;			// nothing confirmed yet
	white = 0;
	for (int i=1; i<=4; i++)
		if (nthDigit( guess, i ) == nthDigit( answer, i ) )
		{
			black++;						// digit in correct spot
			clearNthDigit( guess, i );		// don't match these again
			clearNthDigit( answer, i );
		}
	for (int i=1; i<=4; i++)
		for (int j=1; j<=4 && nthDigit(guess,i)>0; j++)
											// don't try a cleared peg
			if (nthDigit( guess,i ) == nthDigit( answer, j ) )
			{
				white++;					// digit in incorrect spot
				clearNthDigit( guess, i );  // don't match these again
				clearNthDigit( answer, j );
			}
}
		
// nthDigit
// Identifies the n'th digit of a 4 digit number
// This implementation treats the 1's place as the 4th digit,
// but the program would work equally well if it counted in reverse.
int nthDigit( int combination, int position )
{
	int current;			// current digit in the 1's place
	while (position < 4)
	{
		combination /= 10;		// knock off a digit
		position++;				// desired digit moved to the right
	}
	//  Now that the desired digit is in the one's place,
	// remove the leading digits.
	return (combination % 10);			// remainder modulo 10 is one's place
}

// clearNthDigit
// Replaces the n'th digit of a 4-digit number with a 0
// Again, this implementation counts digits from left to right,
// but counting in the reverse order is also valid.
void clearNthDigit( int &combination, int position )
{
	int current;			// position currently being examined
	int digitValue;			// the actual positional value of that digit
	current = 4;			// the 4th digit is in the 1's place
	digitValue = 1;			// the 1's place has a value of 1
	while (position < current)
	{
		digitValue *= 10;	// previou digit has 10 times the value
		current--;			// digitValue refers to previous digit
	}
	// subtract the digit minus itself to make it into a zero digit
	combination -= digitValue * nthDigit( combination, position );
}

// rollDie
// picks a random integer >=1 and <= the provided argument
int rollDie( int sides )
{
	return 1 + rand() % sides;
}