//Go Fish in C++
//Christopher Carney - crc5464
//Fall 2013 - CMPCSC 121

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void playGoFish();
void drawHand(int hand[], int ocean[], int& length, int numberOfCards);
void evaluateHand(int hand[], int& sets, int& handLength);
void playerTurn(int playerHand[], int computerHand[], int ocean[], int& playerSets, int& playerHandLength, int& computerHandLength, int& length);
void computerTurn(int computerHand[], int playerHand[], int ocean[], int& computerSets, int& computerHandLength, int& playerHandLength, int& length);
void showHand(int hand[], int handLength);
void doYouHaveAny(int guess, int guessingHand[], int guessedHand[], int ocean[], int& newCard, int& guesserLength, int& guessedAtLength, int& length);
void drawCard(int hand[], int ocean[]);
int nthDigit( int combination, int position );
int checkGameOver(int playerHandLength, int computerHandLength, int length, int computerSets, int playerSets);
void drawCard(int hand[], int ocean[], int length);

int main(){

	char playing = 'y';
	do{
		playGoFish();
		cout << "Would you like to play again? (y/n) ";
		cin >> playing;
	} while (playing != 'n');	//will play until player enters in 'n'

return 0;
}

void playGoFish(){
	int ocean[] = {12, 22, 32, 42, 13, 23, 33, 43, 14, 24, 34, 44, 15, 25, 35, 45, 
					16, 26, 36, 46, 17, 27, 37, 47, 18, 28, 38, 48, 19, 29, 39, 49};		// int array with numbers 2-9 in the ones place (card numbers) and 1-4 in the tens place (diamonds, clubs, etc)
	int playerHand[16];
	int computerHand[16];		//players hand can have up to 16 
	int length = 32;			//number of values left in the ocean

	int playerSets = 0;			//player and computer start with 0 sets and a hand of 5 cards
	int playerHandLength = 5;

	int computerSets = 0;
	int computerHandLength = 5;

	drawHand(playerHand, ocean, length, 5);		//draws hands for player and computer and trims the ocean and length accordingly
	drawHand(computerHand, ocean, length, 5);
	
		do{
			playerTurn(playerHand, computerHand, ocean, playerSets, playerHandLength, computerHandLength, length);	//simulates players turn
			cout << "You have " << playerSets << " sets." << endl;													//how many sets he has
			cout << endl;

			if (checkGameOver(playerHandLength, computerHandLength, length, playerSets, computerSets) == 1)			//check for conditions if game is over
				return;																								//if game is over, return

			computerTurn(computerHand, playerHand, ocean, computerSets, computerHandLength, playerHandLength, length);	//simulate computer's turn

		} while (checkGameOver(playerHandLength, computerHandLength, length, playerSets, computerSets) == 0);		//while game is not over conditions

	return;
}

void playerTurn(int playerHand[], int computerHand[], int ocean[], int& playerSets, int& playerHandLength, int& computerHandLength, int& length){
	
	int guess;				//players guess
	int newCard;			//new card gotten to see if turn is over
	int oldLength;			//two variables to check if output is needed
	int oldFirst;

	do{
		cout << "Your hand: " ;
		showHand(playerHand, playerHandLength);												//displays current hand every time guessing sequence starts

		do{
			cout << "(Your turn) Do you have any... ";
			cin >> guess;																	//player enters a single digit guess (e.g.) 7
		} while (guess < 2 || guess > 9);													//usable input must be given		

		cout << endl;

		oldLength = playerHandLength;														// variable to determine whether a new card was drawn
		oldFirst = playerHand[0];															//checks the first card in the hand

		doYouHaveAny(guess, playerHand, computerHand, ocean, newCard, playerHandLength, computerHandLength, length);	//compares players hand to computers
																														//acts accordingly (fishing, swapping cards, etc)
		if (oldLength != playerHandLength && oldFirst != playerHand[0]){					//conditions for a new card drawn rather than taken from computers hand
			cout << "you draw a: ";															//if a new card was drawn output what it was
			showHand(playerHand, 1);														//new card will always be in subscript 0
		}

		evaluateHand(playerHand, playerSets, playerHandLength);								//check to see if there are any sets and trim hand accordingly

	} while (newCard == guess && (playerHandLength != 0 || computerHandLength != 0 || length != 0) );	//if any of these conditions are met the turn is over
																										//or the game is over, but the playGoFish function will decide what to do
	return;
}

void computerTurn(int computerHand[], int playerHand[], int ocean[], int& computerSets, int& computerHandLength, int& playerHandLength, int& length){
	cout << "My turn. " << endl;

	int newCard = 0;		//to see if turn is over after
	int compGuess = 0;		//computers guess
	int possibleGuesses[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};	//reinitialize the list at the start of every turn because they are all up for grabs again
	int counter = 0;

	do{	
		
		do {
			compGuess = (rand() % 8) + 2;					//chooses a random number between 2-9

			for (int i = 3; i < 10; i++){
				if (possibleGuesses[i] == 0)				//checks to see if the possible guests list is empty (will cause infinite loop)
					counter++;
				if (counter == 8)
					int possibleGuesses[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};	//if it is, just reinitialize the array
			}


		} while (possibleGuesses[compGuess] == 0);			//if the number has already been chosen this turn choose again
		possibleGuesses[compGuess] = 0;						//set that possibleGuess = 0 so it cannot be chosen again this turn
		

	cout << "(Computer) Do you have any... " << compGuess << endl;	//computer guesses
	doYouHaveAny(compGuess, computerHand, playerHand, ocean, newCard, computerHandLength, playerHandLength, length);
	evaluateHand(computerHand, computerSets, computerHandLength);

	} while (newCard == compGuess && (playerHandLength != 0 || computerHandLength != 0 || length != 0));	//while the newCard added to the hand is equal to the guess the turn isnt over
																											//or the game is over, but the playGoFish function will decide what to do
	return;

}


void doYouHaveAny(int guess, int whoGuessingHand[], int guessedAtHand[], int ocean[], int& newCard,int& guesserLength, int& guessedAtLength, int& length){

	int counter = 0;							//counter equal to the number of cards taken from other player
	newCard = 0;

	for (int i = 0; i < guessedAtLength; i++){  //searches through entire hand
		if (nthDigit(guessedAtHand[i], 1) == guess){ //if there is a match
			counter++;
			whoGuessingHand[guesserLength] = guessedAtHand[i];	//put that card at the end of the recieving players hand
			guesserLength++;									//their # of cards in hand goes up 1
			
			guessedAtHand[i] = 0;								//set the card in the opponents hand to zero

				while (guessedAtHand[guessedAtLength - 1] == 0)	//search for the next value in the opponents hand that isn't 0
					guessedAtLength--;

				guessedAtHand[i] = guessedAtHand[guessedAtLength-1];	//set the removed card equal to the card at the end
				guessedAtHand[guessedAtLength-1] = 0;					//set the value at the end equal to 0
				
				if (guessedAtLength > 0)
					guessedAtLength--;										//their hand length goes down
				else if (guessedAtLength < 0)
					guessedAtLength = 0;

				newCard = guess;										//new card in the players hand is equal to the guess so they get to go again						
				i = 0;													//start back at the beginning of the hand, just in case. ***
		}

	}

	if (counter > 0)
		cout << "I have " << counter << " of them." << endl;			//output amount of cards taken / recieved 

	else if (counter == 0){
			cout << "No I do not, go fish." << endl;					//no cards have been taken, or recieved, draw a card
			cout << endl;

			if (length != 0){											//only draw if there are cards in the ocean
				whoGuessingHand[guesserLength] = whoGuessingHand[0];	//put the card in the beginning of the hand at the end
				drawHand(whoGuessingHand, ocean, length, 1);			//draw a single card and add it to the first spot in the hand
				guesserLength++;										//guesser's hand is increased by 1
				newCard = nthDigit(whoGuessingHand[0], 1);				//the new card is the digit in 1's place of the card drawn
			}
			else
				newCard = -1;
	}

	return;

}



void showHand(int hand[], int handLength){			//outputs hand with rank and suit
	string numbers[] = {"zero", "one", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine "};	//rank of cards (subscripts match card name)
	string suffix[] = {" ", "of hearts", "of spades", "of diamonds", "of clubs"};									//arbitrary suit names of 1-4 with matching subscript

	for (int i = 0; i < handLength; i++){			//go through the whole hand (or amount of values desired)
		int num = nthDigit(hand[i], 1);				//find rank	
		int suf = nthDigit(hand[i], 2);				//find suit

		string nameNum, nameSuf;					//strings to hold those names

		nameNum = numbers[num];						//assign names
		nameSuf = suffix[suf];

		cout << nameNum << nameSuf;					//output full name (e.g. three of hearts)

		if (i < (handLength - 1))					//if its not the last one add a coma to be neat
			cout << ", ";

		if (i == 3)									//every three cards skip a line so it doesn't cut any off
			cout << endl;
	}
	cout << endl;									//end a light just to keep things tidy

	return;
}

void drawHand(int hand[], int ocean[], int& length, int numberOfCards){		//draws an initial random hand of 5 cards if numberOfCards = 5, else draw 1
	
	int random;

	for (int i = 0; i < numberOfCards && length > 0; i++){
			random = rand() % length;		//get a random number between 0 and the number of elements left in the ocean
			hand[i] = ocean[random];		//set the first element in the array equal to the card

			while (ocean[length - 1] == 0)	//find first card in ocean not equal to 0
				length--;

			ocean[random] = ocean[length - 1];	//set the card "taken" to the card at the end of the ocean
			ocean[length - 1] = 0;				//set the end of the ocean card to 0
			length--;							//number of cards in the ocean goes down by 1
	}

	return;
}


void evaluateHand(int hand[], int& sets, int& handLength){
	
	int digit = 0;
	int counter = 0;

	for (int i = 9; i >= 2; i--){				//nested for loop to check all values starts with card rank 9

		for (int b = 0; b < handLength; b++){	//starts at first card in hand
			if (nthDigit(hand[b], 1) == i){		//checks if card is equal to the rank
				digit++;						//number of cards of that rank goes up 1
			}
		}

		if (digit == 4){						//if 4 of one rank a set is made
			sets++;								//increment
			cout << "A set has been completed!" << endl;

			for (int q = 0; q < handLength; q++){
				if (nthDigit(hand[q], 1) == i){ //set the cards of the set rank equal to zero
					hand[q] = 0;
					counter++;					//how many zeros are in the hand array
				}
			}

			while (counter != 0){               //as long as there are still zeros in the array
				
				while (hand[handLength-1] == 0)	//find first card in ocean not equal to 0
					handLength--;
				
				for (int p = 0; p < handLength; p++){ //find the first element in the array that is 0
					if (hand[p] == 0){
						hand[p] = hand[handLength - 1]; //set it equal to the value at the end
						hand[handLength-1] = 0;			//set value at end to 0
					}

					if (hand[handLength-1] == 0)		//just in case check if the last value is zero and get rid of it
						handLength--;

				}
				counter--;								//one less zero in the set
			}
		}

		digit = 0;										//there isn't a set any more, go on to check the rest of the values
	}

	return;
}

int nthDigit(int evaluateVal, int position){

	int number;									//a place holder value
	int place = pow(10, (position-1));			//takes the poower of 10 to the minus position 1. For example if taking the 3rd number from the right it would be 10^(3-1) = 100
	number = evaluateVal  / place;				//divide the number its evaluating by 'place' to "drop" the un-needed integers for example 3254/100 = 32
	number = number % 10;						//take this number and take the remainder when divided by 10 to find the actual value...32 % 10 = 2.

	return number;								//returns the actual integer value of a specific place. The 3rd position of 3254 would return 2 (as in the example above)
}

//checks conditions for end game
int checkGameOver(int playerHandLength, int computerHandLength, int length, int playerSets, int computerSets){
	
	if (length == 0 || playerHandLength == 0 || computerHandLength == 0){		//any of these things happen the game is over
			cout << "Game over!";								
				if (computerSets > playerSets)									//outputs end game stats and who wins what, etc
					cout << " You lose! The computer had " << computerSets << " set(s). You had " << playerSets << " set(s)." << endl;
				else if (computerSets < playerSets)
					cout << " You win! The computer had " << computerSets << " set(s). You had " << playerSets << " set(s)." << endl;
				else if (computerSets == playerSets)
					cout << " Tie Game! The computer had " << computerSets << " set(s). You had " << playerSets << " set(s)." << endl;

			return 1;	//1 == true
		}
	else
		return 0;		//0 == flase
}