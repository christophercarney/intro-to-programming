/*  CHRISTOPHER CARNEY - crc5464
	CMPSC 121 - Homework #6
	December 6, 2013
	Blackjack in C++  v2.0		*/

#include <iostream>
#include <string>
using namespace std;

struct Card {			//structure to hold the names and ranks and int values of all the cards for easy access

	string name;
	string rank;
	int value;

};
 
struct Hand {		//structure to manage the use of players' hands
	
	int handSize;	//tell the size of the hand
	struct Card cardsHeld[5]; //holds all the cards in a hand (up to a max of 5)
	int totalValue;			//total worth of cards
	int bet;				//the bet wagered on that hand 

};

//function prototypes
void createDeck(Card bigDeck[] , int& deckSize);
void drawCard (Card bigDeck[], int& deckSize, Hand totalHands[11][10], int currentPlayer, int currentHand);
void dealCard(Card bigDeck[], int& deckSize, Hand totalHands[11][10], int players, int wallet[]);
void playerTurn(Card bigDeck[], int& deckSize, Hand totalHands[11][10], int wallet[], int currentPlayer, int& currentHand, int bet);
void dealerTurn(Card bigDeck[], int& deckSize, Hand totalHands[11][10]);
void payoff(Hand totalHands[11][10], int wallet[], int players);

int main(){

	int players;
	int wallet[10];				//holds the wallets of all 10 players

	for (int i = 0; i < 10; i++)	//sets all the players' initial wallets to $100
		wallet[i] = 100;

	Hand totalHands[11][10];	//holds all the hands for each of the players in one array (in case of double downs; dealers hand is always [0][0]

	for (int n = 0; n < 11; n++)			//nested for loop to set all the values in the 2D array to 0
		for (int m = 0; m < 10; m++){
				totalHands[n][m].totalValue = 0;
				totalHands[n][m].handSize = 0;
		}

	cout << "Welcome to blackjack, how many players? (up to 10): ";
	cin >> players;

	int originalPlayers = players;			//store the original amount of players seperately for functional purposes
	
	struct Card bigDeck[208];				//amount of cards in the deck will be 208 b/c 4 decks put together
	int deckSize = 0;						//current deck size is 0

	createDeck(bigDeck, deckSize);			//creates the full 208 card deck to use in play

	char playing = 'y';
	do {

		for (int i = 0; i < players; i++){		//for loop to enter in the bets for all players
			
			if (wallet[i] <= 0)					//if they have already busted out completly, skip them
				i++;

			cout << "Player " << (i + 1) << " place your bet (current wallet = $" << wallet[i] << "): ";
			do{
				cin >> totalHands[(i+1)][0].bet;	//enters in the bet for their fist hand
			} while (totalHands[(i+1)][0].bet > wallet[i]);		//makes sure they can actually bet that amount
		}
		
		dealCard(bigDeck, deckSize, totalHands, originalPlayers, wallet );	//deals cards to the dealers and all the players

		for (int i = 0; i < players; i++){									//for loop for all the players' individual turns

			if (wallet[i] <= 0)												//if the player is bust; skip their turn
				i++;

			cout << endl;
			cout << "It is player " << i + 1 << "'s turn" << endl;
			
			int currentHand = 0;											//at the beginning of a turn they only have one hand
			playerTurn(bigDeck, deckSize, totalHands, wallet, (i+1), currentHand, totalHands[(i+1)][0].bet);	//simulate the players full turn
		}

		dealerTurn(bigDeck, deckSize, totalHands);							//after all the players go, the dealer goes

		payoff(totalHands, wallet, originalPlayers);						//payoff and modify the wallets based on winners / losers

		cout << "Would you like to keep playing? (Y/N): ";			//play another round?
		cin >> playing;

		if (deckSize < 50){													//if the deck is running low
			deckSize = 0;
			createDeck(bigDeck, deckSize);									//recreate and reshuffle the deck
		}

		for (int i = 0; i < originalPlayers; i++){							//for loop to check for busts
			if (wallet[i] == 0){											//if wallet is  0 they are bust
				cout << "Player " << (i+1) << " busts out! They can no longer play" << endl;
				wallet[i] = -1;												//wallet equal to -1 to signify busted elsewhere in the program
				players--;													//players playing is decreased 
			}
		}

		if (players == 0){													//if no players left; end the game
			cout << "All Players bust, GAME OVER" << endl;
			playing = 'n';
		}

	} while (playing == 'y' || playing == 'Y');								//end of do while loop to repeat as long as players want to play & have money to play

	cout << "Thanks for playing!" << endl;

	return 0;
}

void createDeck(Card bigDeck[] , int& deckSize){

	struct Card cards[] = {				//an array of structures which defines a full 52 card deck
		{"Ace" , "Spades" , 11}	,	{"Ace" , "Clubs" , 11}	,	{"Ace" , "Diamonds" , 11}	,	{"Ace" , "Hearts" , 11}	,
		{"Two" , "Spades" , 2}	,	{"Two" , "Clubs" , 2}	,	{"Two" , "Diamonds" , 2}	,	{"Two" , "Hearts" , 2}	,
		{"Three" , "Spades" , 3}	,	{"Three" , "Clubs" , 3}	,	{"Three" , "Diamonds" , 3}	,	{"Three" , "Hearts" , 3} ,
		{"Four" , "Spades" , 4}	,	{"Four" , "Clubs" , 4}	,	{"Four" , "Diamonds" , 4}	,	{"Four" , "Hearts" , 4}	,
		{"Five" , "Spades" , 5}	,	{"Five" , "Clubs" , 5}	,	{"Five" , "Diamonds" , 5}	,	{"Five" , "Hearts" , 5}	,
		{"Six" , "Spades" , 6}	,	{"Six" , "Clubs" , 6}	,	{"Six" , "Diamonds" , 6}	,	{"Six" , "Hearts" , 6}	,
		{"Seven" , "Spades" , 7}	,	{"Seven" , "Clubs" , 7}	,	{"Seven" , "Diamonds" , 7}	,	{"Seven" , "Hearts" , 7} ,
		{"Eight" , "Spades" , 8}	,	{"Eight" , "Clubs" , 8}	,	{"Eight" , "Diamonds" , 8}	,	{"Eight" , "Hearts" , 8} ,
		{"Nine" , "Spades" , 9}	,	{"Nine" , "Clubs" , 9}	,	{"Nine" , "Diamonds" , 9}	,	{"Nine" , "Hearts" , 9}	,
		{"Ten" , "Spades" , 10}	,	{"Ten" , "Clubs" , 10}	,	{"Ten" , "Diamonds" , 10}	,	{"Ten" , "Hearts" , 10}	,
		{"Jack" , "Spades" , 10}	,	{"Jack" , "Clubs" , 10}	,	{"Jack" , "Diamonds" , 10}	,	{"Jack" , "Hearts" , 10} ,
		{"Queen" , "Spades" , 10}	,	{"Queen" , "Clubs" , 10}	,	{"Queen" , "Diamonds" , 10}	,	{"Queen" , "Hearts" , 10}	,
		{"King" , "Spades" , 10}	,	{"King" , "Clubs" , 10}	,	{"King" , "Diamonds" , 10}	,	{"King" , "Hearts" , 10} ,
	};

	int counter = 0;			
	while (deckSize < 208){						//loop to add 4 of each element to the big deck
		bigDeck[deckSize] = cards[counter];
		deckSize++;								//decksize will equal 208 when loop completes
		counter++;

		if (counter == 52)		//counter to reset deck when reaches 52
			counter = 0;
	}

	for (int i = 0; i < 208; i++)		//simple for loop to shuffle all the cards in the deck via swapping
		swap (bigDeck[i], bigDeck[ rand() % 208 ]);

}

void dealCard(Card bigDeck[], int& deckSize, Hand totalHands[11][10], int players, int wallet[]){

	drawCard(bigDeck, deckSize, totalHands, 0, 0);	//dealCard is only used for original dealing at the beginning of each round
	drawCard(bigDeck, deckSize, totalHands, 0, 0);  //drawCard actually draws individual cards; do this for the dealer first

	cout << "Dealer shows a " << totalHands[0][0].cardsHeld[0].name << " of " << totalHands[0][0].cardsHeld[0].rank << endl;	//only show the dealers up card
	cout << endl;
	
	for (int i = 1; i <= players; i++){		//deal cards to all the players

			if (wallet[i-1] > 0){			//only deal if their wallet > 0; aka they have no busted out

				drawCard(bigDeck, deckSize, totalHands, i, 0);		//draw card into the variable i (the current players) hand
				drawCard(bigDeck, deckSize, totalHands, i, 0);

				cout << "Player " << i << " shows a " << totalHands[i][0].cardsHeld[0].name << " of " << totalHands[i][0].cardsHeld[0].rank;	//shows the name and rank of both the players card
				cout << " and a " << totalHands[i][0].cardsHeld[1].name << " of " << totalHands[i][0].cardsHeld[1].rank;
				cout << endl;
			}
				
	}

}

void drawCard (Card bigDeck[], int& deckSize, Hand totalHands[11][10], int currentPlayer, int currentHand){

	int b;		//declare b outside for loop so it can be used elsewhere in the function
	for (b = 0; totalHands[currentPlayer][currentHand].cardsHeld[b].value > 0; b++) { /* EMPTY */ }		//finds the next empty slot in that current hand to place a card in

	totalHands[currentPlayer][currentHand].cardsHeld[b] = bigDeck[deckSize - 1];		//whatever the current hand is (typically 0 unless split pair) put the card from the top of the deck in it
	totalHands[currentPlayer][currentHand].handSize++;									//that hand has one more card
	totalHands[currentPlayer][currentHand].totalValue = totalHands[currentPlayer][currentHand].totalValue + totalHands[currentPlayer][currentHand].cardsHeld[b].value;	//the total value of that hand has changed
	deckSize--;		//go to the next card in the deck for next time

}

void playerTurn(Card bigDeck[], int& deckSize, Hand totalHands[11][10], int wallet[], int currentPlayer, int& currentHand, int bet){

	char doubleDown, splitPair, hit;			//characters for special cases

		if (bet * 2 <= wallet[currentPlayer]){	//these special cases can only be used if the player can double their bet; if they cant; skip these
		
			cout << "Would you like to Double Down? (Y/N) ";
			cin >> doubleDown;
			cout << endl;

			if (doubleDown == 'y' || doubleDown == 'Y'){
				totalHands[currentPlayer][currentHand].bet = totalHands[currentPlayer][currentHand].bet * 2;	//if they double down bet is increased by 2

				drawCard(bigDeck, deckSize, totalHands, currentPlayer, currentHand);							//only draw one card and declare what that card is

				cout << "Player " << currentPlayer << " draws a " << totalHands[currentPlayer][currentHand].cardsHeld[2].name << " of " << totalHands[currentPlayer][currentHand].cardsHeld[2].rank << endl;

				int aces = 0;
				if (totalHands[currentPlayer][currentHand].totalValue > 21){					//if they are over 21 check for aces
					for (int b = 0; b < totalHands[currentPlayer][currentHand].handSize; b++){
						if (totalHands[currentPlayer][currentHand].cardsHeld[b].value == 11){
							aces++;
						}
					}

				while (totalHands[currentPlayer][currentHand].totalValue > 21 && aces > 0){		//if ace(s) found then act accordingly (aka change to a 1)
					totalHands[currentPlayer][currentHand].totalValue = totalHands[currentPlayer][currentHand].totalValue - 10;
					aces--;
				}

					if (totalHands[currentPlayer][currentHand].totalValue > 21)					//else if no aces; bust
						cout << "BUST" << endl;
				}

				cout << "Your total is: " << totalHands[currentPlayer][currentHand].totalValue << endl;	//outputs total after the double down
				return; 

				}
			else if (totalHands[currentPlayer][currentHand].cardsHeld[0].name == totalHands[currentPlayer][currentHand].cardsHeld[1].name){		//if they dont want to double down and have two of the same value cards they can split a pair
				
				cout << "Would you like to Split a Pair? (Y/N): ";
				cin >> splitPair;
				cout << endl;

				if (splitPair == 'y' || splitPair == 'Y'){
					currentHand++;						//go to the next hand slot in the 2D array
					totalHands[currentPlayer][currentHand].cardsHeld[0] = totalHands[currentPlayer][currentHand - 1].cardsHeld[0];		//copy one of the cards over to the next hand

					totalHands[currentPlayer][currentHand - 1].cardsHeld[1] = bigDeck[deckSize - 1];	//draw a new card into the 1st hand and change total values
					totalHands[currentPlayer][currentHand - 1].totalValue = totalHands[currentPlayer][currentHand - 1].cardsHeld[0].value + totalHands[currentPlayer][currentHand - 1].cardsHeld[1].value;
					deckSize--;

					totalHands[currentPlayer][currentHand].cardsHeld[1] = bigDeck[deckSize - 1];		//draw a new card into the 2nd hand and change total values
					totalHands[currentPlayer][currentHand].totalValue = totalHands[currentPlayer][currentHand].cardsHeld[0].value + totalHands[currentPlayer][currentHand].cardsHeld[1].value;
					deckSize--;

					//declare and display both hands to the player
					cout << "Your current split is: " << totalHands[currentPlayer][currentHand - 1].cardsHeld[0].name << " of " << totalHands[currentPlayer][currentHand - 1].cardsHeld[0].rank << " , ";
					cout << totalHands[currentPlayer][currentHand - 1].cardsHeld[1].name << " of " << totalHands[currentPlayer][currentHand - 1].cardsHeld[1].rank << endl;
					cout << "AND" << endl;
					cout << totalHands[currentPlayer][currentHand].cardsHeld[0].name << " of " << totalHands[currentPlayer][currentHand].cardsHeld[0].rank << " , ";
					cout << totalHands[currentPlayer][currentHand].cardsHeld[1].name << " of " << totalHands[currentPlayer][currentHand].cardsHeld[1].rank << endl;

					//bet of equal value is placed on the new hand
					totalHands[currentPlayer][currentHand].bet = bet;

					//bet is doubled (for recursion purposes; incase the next hand can be split / doubled down)
					bet = bet * 2;

					cout << "Now playing second hand" << endl;
					playerTurn(bigDeck, deckSize, totalHands, wallet, currentPlayer, currentHand, bet);		//recursive function to play the second hand
					currentHand = currentHand - 1;															//after that hand is finished playing; play the first hand for the rest of the turn
				}
			}
		}

		do {
			cout << "Your current total is: " << totalHands[currentPlayer][currentHand].totalValue << endl;
			
			do {
				cout << "Hit or Stand? (H/S): ";							//simple hit or stand for the player
				cin >> hit;
			} while (hit != 'h' && hit != 'H' && hit != 's' && hit != 'S'); //checks for valid input

			if (hit == 'h' || hit == 'H'){
				drawCard(bigDeck, deckSize, totalHands, currentPlayer, currentHand);	//if the player wants a hit then draw them a card
				
				int b;
				for (b = 0; totalHands[currentPlayer][currentHand].cardsHeld[b].value > 0; b++) { /* EMPTY */ }		//find the new card in the hand that was just given

				//output that new card onto the screen
				cout << "You draw a " << totalHands[currentPlayer][currentHand].cardsHeld[b-1].name << " of " << totalHands[currentPlayer][currentHand].cardsHeld[b-1].rank << endl;
			}

			int aces = 0;												//same loop / if statement as above; checks for aces in the hand and acts accordingly
			if (totalHands[currentPlayer][currentHand].totalValue > 21){
				for (int b = 0; b < totalHands[currentPlayer][currentHand].handSize; b++){
					if (totalHands[currentPlayer][currentHand].cardsHeld[b].value == 11){
						aces++;
					}
				}

				while (totalHands[currentPlayer][currentHand].totalValue > 21 && aces > 0){
					totalHands[currentPlayer][currentHand].totalValue = totalHands[currentPlayer][currentHand].totalValue - 10;
					aces--;
				}

				cout << "Your total is now " << totalHands[currentPlayer][currentHand].totalValue << endl;	//output new total before asking if they want another hit or if they are bust

				if (totalHands[currentPlayer][currentHand].totalValue > 21){								//if still over 21 after ace check they are bust
					cout << "BUST" << endl;
					hit = 's';
				}
			}

			if (totalHands[currentPlayer][currentHand].handSize == 5 && totalHands[currentPlayer][currentHand].totalValue <= 21){	//if they ever have 5 cards in a hand and haven't bust they automatically win									
				cout << "You have 5 cards in one hand, you win" << endl;
				hit = 's';
			}

		} while (hit == 'h' || hit == 'H');

		return;
}


void dealerTurn(Card bigDeck[], int& deckSize, Hand totalHands[11][10]){
	
	cout << endl;
	cout << "It is now the dealer's turn" << endl;

	while (totalHands[0][0].totalValue < 17){			//keep drawing cards as long as total of the dealer is below 17
		drawCard(bigDeck, deckSize, totalHands, 0, 0);
		
		int b;
		for (b = 0; totalHands[0][0].cardsHeld[b].value > 0; b++) { /* EMPTY */ }	//finds newest card added to hand 

		cout << "The dealer draws a " << totalHands[0][0].cardsHeld[b-1].name << " of " << totalHands[0][0].cardsHeld[b-1].rank << endl;  //outputs new card 
	
		int aces = 0;												//same loop / if statement as above; checks for aces in the hand and acts accordingly
		if (totalHands[0][0].totalValue > 21){
			for (int b = 0; b < totalHands[0][0].handSize; b++){
				if (totalHands[0][0].cardsHeld[b].value == 11){
					aces++;
				}
			}

			while (totalHands[0][0].totalValue > 21 && aces > 0){
				totalHands[0][0].totalValue = totalHands[0][0].totalValue - 10;
				aces--;
			}
		} 
	}

	if (totalHands[0][0].totalValue > 21){ 
		cout << endl;
		cout << "The dealer reveals his other card; it is a " << totalHands[0][0].cardsHeld[1].name << " of " << totalHands[0][0].cardsHeld[1].rank << endl;
		cout << "Dealer's total is " << totalHands[0][0].totalValue << endl;
		cout << "The dealer busts." << endl;
	}
	else{		//if dealer is >= 17 and doesn't bust reveal their other card 
		cout << "The dealer reveals his other card; it is a " << totalHands[0][0].cardsHeld[1].name << " of " << totalHands[0][0].cardsHeld[1].rank << endl;
		cout << "Dealer stands on a " << totalHands[0][0].totalValue << endl;
	}

	cout << endl;
	return;

}

//function for the end of a round which checks for all the scenarios of winning and acts accordingly; paying out bets; resetting hands; etc
void payoff(Hand totalHands[11][10], int wallet[], int players){

	for (int n = 1; n <= players; n++){			//nested for loops to go through all the hands of players (to account for split pairs)
		for (int m = 0; m < 10; m++){

			if (totalHands[n][m].totalValue <= 0)	//if their is nothing in this had for this player; skip it
				break;

			if (totalHands[n][m].handSize == 5 && totalHands[n][m].totalValue <= 21){   //if they have 5 cards and less than 21 they win 
				cout << "Player " << n << " wins $" << totalHands[n][m].bet << endl;
				wallet[n-1] = wallet[n-1] + totalHands[n][m].bet;
			}
			else if (totalHands[n][m].totalValue == 21 && totalHands[n][m].handSize == 2){	//if they have 21 exactly and only 2 cards it is a natural blackjack
				cout << "Player " << n << " has a natural blackjack and wins $" << totalHands[n][m].bet * 1.5 << endl;
				wallet[n-1] = wallet[n-1] + (totalHands[n][m].bet * 1.5);					//payout is 1.5
			}
			else if (totalHands[n][m].totalValue > 21){										//if over 21 they are bust and lose their bet
				cout << "Player " << n << " loses $" << totalHands[n][m].bet << endl;
				wallet[n-1] = wallet[n-1] - totalHands[n][m].bet;
			}
			else if (totalHands[n][m].totalValue <= 21 && totalHands[0][0].totalValue > 21){ //if they haven't busted and the dealer busts they win their bet
				cout << "Player " << n << " wins $" << totalHands[n][m].bet << endl;
				wallet[n-1] = wallet[n-1] + totalHands[n][m].bet;
			}
			else if (totalHands[n][m].totalValue <= 21 && totalHands[0][0].totalValue <= 21 && totalHands[n][m].totalValue > totalHands[0][0].totalValue){ //if both the dealer and player are under 22 and the player is greater he wins his bet
				cout << "Player " << n << " wins $" << totalHands[n][m].bet << endl;
				wallet[n-1] = wallet[n-1] + totalHands[n][m].bet;
			}
			else if (totalHands[n][m].totalValue <= 21 && totalHands[0][0].totalValue <= 21 && totalHands[n][m].totalValue < totalHands[0][0].totalValue){ //if both the dealer and player are under 22 and the dealer is greater the player loses their bet
				cout << "Player " << n << " loses $" << totalHands[n][m].bet << endl;
				wallet[n-1] = wallet[n-1] - totalHands[n][m].bet;
			}
			else if (totalHands[n][m].totalValue == totalHands[0][0].totalValue){			//if their hands are tied they win nothing
				cout << "Player " << n << " ties with the dealer and wins nothing" << endl;
			}
		}
	}

	for (int n = 0; n < (players + 1); n++)				//triple nested for loop to set all bets and hands completely to 0
		for (int m= 0; m < 10; m++){
			
			totalHands[n][m].bet = 0;
			totalHands[n][m].handSize = 0;
			totalHands[n][m].totalValue = 0;
			for (int b = 0; b < 5; b++)					//set individual cards to 0 so computer knows they can be replaced
				totalHands[n][m].cardsHeld[b].value = 0;

		}

	return;

}
