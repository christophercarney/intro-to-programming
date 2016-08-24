//Christopher Carney - CRC5464@psu.edu
//October 2013
//Homework #3 - Mastermind in C++

#include <iostream>
#include <math.h>
using namespace std;

void playMastermind();							//declaring function prototypes for all the functions needed to play
int rollDie(int);
void evaluate(int, int, int&, int&);
int nthDigit(int, int);
int clearNthDigit(int, int);
int getAnswer();

int numDigits, guessesAllowed, dieSides;		//[E.C] global variables allowed for input of the degree of difficulty for the user. 

int main(){

	char playing = 'y';								//declares variable so the game can play once.

	cout << "Guess the correct combination. A white peg denotes a correct";
	cout << "number in the wrong position. A black beg denotes a correct number in correct position" << endl;

	do{					
		playMastermind();					//do while loop calls playMastermind function to play one full game
		do {
			cout << "Would you like to play again? y/n ";		//Once function returns asks player if they want to play again
			cin >> playing;
		} while (playing != 'y' && playing != 'n');				//checks for valid input
	} while (playing == 'y');

	cout << "Thanks for playing!" << endl;							//game exits if player enters n after game ends

	return 0;
}

//playMastermind fucntion handles playing the actual game.
void playMastermind(){
	do{
		cout << "Please enter how many digits (1-9) you want the computer's generated answer to be: ";	//following three prompts have the user set their difficulty
		cin >> numDigits; 
	}while (numDigits < 1 || numDigits > 9);															//guess cannot exceed 9 numbers because int cannot hold that big of a number
	cout << "What is the maximum number of guesses desired: ";
	cin >> guessesAllowed; 
	do{
		cout << "Please enter a number 1-9 for the range of digits for each number: ";			//makes sure the number entered is between 1 and 9
		cin >> dieSides; 
	}while (dieSides > 9 || dieSides < 1);

	int guessesTaken = 0;
	int blackPegs = 0;
	int whitePegs = 0;
	int playerGuess;
	int answer = 5742;																//sets the combination the player must guess

	while (guessesTaken < guessesAllowed){

		do{
			cout << "Please enter a " << numDigits << " digit guess: ";								//player enters a guess according to their set difficulty
			cin >> playerGuess;
		} while (playerGuess >= pow(10, numDigits));												//guess must be the amount of digits specified long or else it will reprompt the user for another input

		evaluate (answer, playerGuess, blackPegs, whitePegs);										//calls the evalutate function to see what the players Guess earns. Return value modifies whitePegs and BlackPegs

		cout << "You earn " << blackPegs << " black pegs and " << whitePegs << " white pegs." << endl;	//loop will exit and game will end if the player's black peg count equals the degree of difficulty set (i.e. a correct guess)
		guessesTaken ++;

		if (blackPegs == numDigits){
				cout << "Congratulations, you have guessed the combination!" << endl;				//if player's black pegs == number of places he has all the blackpegs and has won. The game will exit
				return;
		}

		blackPegs = 0;																				//returns peg counts to zero after each guess so pegs are not over counted
		whitePegs = 0;

	}
		cout << "Maximum number of guesses reached! You Lose!" << endl;								//if the maximum guesses is reached game exits.
		cout << "My combination was " << answer << endl;
		
		return;
}

//function to simulate 1 die roll
int rollDie(int dieSides){
	int roll;
	roll = (1 + (rand() % dieSides));			//the roll is a number between 1 and dieSides, a degree of difficulty entered by the user
	return roll;								//returns the value of the random integer
}

//function to generate the computers answer that the player must guess
int getAnswer(){

	int power = 10;
	int answer = rollDie(dieSides);							//gets the first digit of the combination (furthest one to the right)
	for (int counter = numDigits; counter > 1; counter--){
		answer = (rollDie(dieSides) * power) + answer;		//for loop to repeat the number of times the player wants the length of the answer to be 
		power = power * 10;									//increases by a power of 10 to add the next number to the left
	}														//example if numDigits = 4; (6 * 1000) + (5*100) + (2*10) + 1 = 6521 (the computer generated answer)

	return answer;
}

//function to compare the nth digits of the combination and guess and to set the number of whitePegs and blackPegs given for a guess
void evaluate(int combination, int playerGuess, int& blackPegs, int& whitePegs){
	int counter = numDigits;															//how many times the loop will go through, examining each number against one another
	int answerNth, playerNth;

	while (counter > 0){
		
		answerNth = nthDigit(combination, counter);										//checks the actual and player nth digit according to the counter, starting with furthest to the left
		playerNth = nthDigit(playerGuess, counter);

		if (answerNth == playerNth){
			blackPegs++;																//if they ever equal, they are in the same position and a black peg is awarded
			combination = clearNthDigit(combination, counter);							//sets that same decimal place equal to 0 so pegs are not double counted by the white peg counter below
			playerGuess = clearNthDigit(playerGuess, counter);
		}

		counter--;																		//decrements the counter by 1; goes to the next digit to the right
	}

	if (blackPegs == numDigits){
		return;																			//if blackPegs == numDigits then the player has won and the function can end
	}


	counter = numDigits;																
	int counter2 = numDigits;															//two counters needed to compare one place of the combinaiton against every place of the player guess before moving on
	while (counter2 > 0){
		answerNth = nthDigit(combination, counter);										//gets the first available digit

		if (answerNth == 0){
			counter--;																	//if the nth digit is a 0 then it has already been awarded a black peg, decrement the counter so the next digit can be examined
			counter2++;																	//increase the second counter by 1 to stop the loop from exiting early
		}

		playerNth = nthDigit(playerGuess, counter2);									//takes the nth digit of the player guess, according to counter2

		if ((answerNth == playerNth) && (answerNth != 0 && playerNth != 0) ){
			whitePegs++;																//if the nth digits match (and they aren't zero) a white peg is awarded

			combination = clearNthDigit(combination, counter);							//clear the nth digit to stop double counting
			playerGuess = clearNthDigit(playerGuess, counter2);							//clear the nth digit at the position counter2 to stop from double counting

			if(nthDigit(combination, counter) == 0)
				counter--;																//the nth digit is now 0 so it decrements the counter so it can test the new available number

			counter2 = numDigits + 1;													//counter2 is about to decrement as loop exits so restart to the number of decimal places of the player guess + 1
			if (counter == 0 || counter2 == 0 || combination == 0)
				return;																	//if any of these situations is ever reached the evaluate() phase is already over and would continue on to crash the progra by dividing by 0 in the nthDigit() function
		}

		counter2--;																		//decrements the counter2 (the once measuring the playerGuess to evaluate the next digit to the right
	}

	return;

}

//evaluates the nth digit of any number. For example in 3235 at position 1 it will give 5. At position 2 it will give 3. 
int nthDigit(int evaluateVal, int position){

	int number;									//a place holder value
	int place = pow(10, (position-1));			//takes the poower of 10 to the minus position 1. For example if taking the 3rd number from the right it would be 10^(3-1) = 100
	number = evaluateVal  / place;				//divide the number its evaluating by 'place' to "drop" the un-needed integers for example 3254/100 = 32
	number = number % 10;						//take this number and take the remainder when divided by 10 to find the actual value...32 % 10 = 2.

	return number;								//returns the actual integer value of a specific place. The 3rd position of 3254 would return 2 (as in the example above)
}


int clearNthDigit(int combination, int position){

	int nth;									
	int place = pow(10, (position-1));			
	nth = combination  / place;				
	nth = nth % 10;									//same as the nthDigit function. First finds the nthDigit again
	combination = combination - (nth * place);		//sets the new combination equal to the inputted combo - the nth digit * the place
													//e.g. in 52892 the third digit cleared would be (8 * 100) = 800. 52892 - 800 = 52092
	return combination;
}