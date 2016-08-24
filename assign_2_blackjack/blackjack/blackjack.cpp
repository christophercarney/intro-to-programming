//Blackjack.cpp
//Christopher Carney
//CMPSC 121 - Sectoion 002 - Homework #2
//September 2013

#include <iostream>
#include <iomanip>
using namespace std;

int playerCard1, playerCard2, dealerCard1, dealerCard2;		//First four variables represent the players initial cards and the dealers initial cards
int playerTotal, dealerTotal;								//the totals of the player and dealers card so the game can check if its 21 or over
int dealingCard;											//a variable used in loops to hold cards
double bankroll;											//The initial bankroll or amount of money the player has
double bet;													//The amount of money a player bets on the current hand
char playing;												//Variable for the game to determine if it is being played or if the game is over
char hitOrStand;											//Variable for the game to detemine if the player wants to hit or stand

int dealCard(){											 //Function to deal cards, otherwise this code would be ctrl + c and ctrl + v many times.
	int card;
	
	card = 1 + (rand() % 13);								//set local variable card to a random integer between 1 and 13 to simulate a full deck
	if (card == 11 || card ==  12 || card == 13){		 //if the integer is 11, 12, or 13 then it is a face card and by the rules of blackjack it's value is = 10
		card = 10;
	}
return card;											//Function will return an integer "card" which will then be set equal to the player or dealer's cards.
}


int main(){
	bankroll = 100;						//Initial bankroll is $100
	playing = 'y';						//Set the game to start playing

	while (playing == 'y'){				//Start a while loop, the game will continue playing as long as the player doesn't change to 'n' after a hand
		bet = 0;						//set bet = 0 so that when the game plays again the player can bet a different amount
		while (bet == 0){				//start a while loop for the betting process
			cout << fixed << setprecision (2) << "You have $" << bankroll << ", what is your bet? "; 		//tells the player their current bankroll. Set decimal value to 2 because you can't have $0.035983
			cin >> bet;																						//player enters bet
			if (bet > bankroll || bet <= 0){																//statement to search for invalid bets
				cout << "That is not a valid bet. Try again" << endl;
				bet = 0;																					//if the bet is invalid, the betting process starts over until a valid bet is entered
			}
		}
	
		int playerAces = 0;				//set two variables so the game knows how many aces both the dealer and the player has
		int dealerAces = 0;				//game will then act accordingly based on what is best for the player


										// next 4 blocks of code deal the original hand for both the player and dealer, all four work the same
		playerCard1 = dealCard();		//gets a random integer from the dealCard function sets it equal to a player card
		if (playerCard1 == 1){           //checks if the player's card is an ace
			playerAces++;				//increments the amount of aces the player has by 1
			playerCard1 = 11;			//sets the player card = 11 because that is the more desirable value at the beginning of the game
		}

		playerCard2 = dealCard();
		if (playerCard2 == 1){
			playerAces++;
			playerCard2 = 11;
		}

		dealerCard1 = dealCard();
		if (dealerCard1 == 1){
			dealerAces++;
			dealerCard1 = 11;
		}

		dealerCard2 = dealCard();
		if (dealerCard2 == 1){
			dealerAces++;
			dealerCard2 = 11;
		}


		if (playerAces == 2){		//next two blocks of code check to see if the player was delt double aces
			playerCard2 = 1;		//since this would be a bust the computer sets the second card = 1
			playerAces--;			//because the ace is "used" and there would be no point in bringing it to equal 11 again because that could only hurt the player
		}
		if (dealerAces == 2){
			dealerCard2 = 1;
			dealerAces--;
		}


		playerTotal = playerCard1 + playerCard2;											//finds  the totals for the cards for both the player and dealer
		dealerTotal = dealerCard1 + dealerCard2;

		cout << "Your cards are " << playerCard1 << " and " << playerCard2 << endl;			//outputs the cards the player currently has
		cout << "Dealer is showing a " << dealerCard1 << endl;								//outputs the first card the dealer has (player only gets to see 1)
		cout << "Your current total is " << playerTotal << endl;							//outputs the player's total
		

		cout << "Would you like to hit or stand (h / s)? ";									//prompts the player for an h or s based on what they want to do
		cin >> hitOrStand;
		while (hitOrStand != 'h' && hitOrStand != 's'){										//creates a loop for if the input is not valid
			cout << "I don't understand. Please enter h or s: ";							//outputs instructions and statement if input is invalid																			//starts the loop over until it is a value the computer accepts
			cin >> hitOrStand;																//asks for a new input. Will repeat until valid input is given
		}
		
		while (hitOrStand == 'h'){                                                          //what to execute if the player wants to be given more cards

			dealingCard = dealCard();														//deals a random card to the player
			if (dealingCard == 1){                                                           //checks to see if the card delt is an ace
			playerAces++;
			dealingCard = 11;																//if the card is an ace set it equal to 11 but the computer knows it has an ace if it needs to change it to 1
			}

			playerTotal = playerTotal + dealingCard;										//calculates a new player total

			if (playerTotal > 21 && playerAces >= 1){                                       //checks to see if the player is over 21, if they are  AND have aces 
				playerTotal = playerTotal - 10;												//the ace is changed to a 1 by subtracting 10 from the total
				playerAces--;																//subtract 1 from the ace count because it is "used" just in case a rare scenario where >3 aces drawn may break the game
			}

			cout << "The dealer gives you a " << dealingCard << ". Your new total is now " << playerTotal << endl;		//outputs players new card delt and new total

			if (playerTotal > 21){                                                          //if the total is greater than 21 the player is bust and the loop breaks
				break;
			}
			else{                                                                           //if the players total is not 21 it asks if they want to hit or stand again
				cout << "Would you like to hit or stand? (h / s) ";                      
				cin >> hitOrStand;                                                         
				while (hitOrStand != 'h' && hitOrStand != 's'){                             //checks for valid input
					cout << "I don't understand. Please enter h or s " << endl;				//outputs instructions and statement if input is invalid
					cin >> hitOrStand; 
				}
			}
		}	
		
		if (hitOrStand == 's'){
			cout << "Player standing on " << playerTotal << endl;							//if the player ever inputs 's' or stay it outputs this first before doing into the while loop
			cout << "Dealer shows other card, it is a " << dealerCard2 << ". Dealer's total is " << dealerTotal << endl;	//reveals the dealers other card and total
		}

		while (hitOrStand == 's'){                                                          //starts a while loop for if the player wants to stay. Dealer's turn to act
			if (dealerTotal >= 17){                                                         //If the dealers total ever equals 17 then he is forced to stay. Check his total before doing anything else
				break;																		//if the dealer is at or above 17 then the stand phase is over an the loop breaks
			}

			dealingCard = dealCard();														//deals a random card to the dealer
			if (dealingCard == 1){                                                           //checks to see if the card delt is an ace
			dealerAces++;
			dealingCard = 11;
			}

			dealerTotal = dealerTotal + dealingCard;										//calculates a new dealer total

			if (dealerTotal > 21 && dealerAces >= 1){                                       //checks to see if the dealer is over 21, if they are  AND have aces 
				dealerTotal = dealerTotal - 10;												//the ace is changed to a 1 by subtracting 10 from the total
				dealerAces--;
			}

			cout << "The dealer draws a " << dealingCard << ". Dealers total is " << dealerTotal << endl;		//outputs dealers new card delt and new total

		}

		if (playerTotal > 21){                                                              //player loses because they bust
			cout << "BUST, you loose $" << bet << endl;										// calculates the players new bankroll based on whether they won or lost
			bankroll = bankroll - bet;
			cout << "Your new bankroll is now $" << bankroll << endl;
			
			if (bankroll <= 0){                                                                 //if the player wants to play again but their bankroll is empty then they cannot play again and the game ends
			cout << "You've run out of money! GAME OVER." << endl;
			break;
			}

			cout << "Play again? (y / n)" << endl;											//prompts player to play agan
			cin >> playing;
			while (playing != 'y' && playing != 'n'){										// calculates the players new bankroll based on whether they won or lost
					cout << "I don't understand. Please enter y or n" << endl;				//outputs instructions and statement
					cin >> playing; 
			}
		}
		else if (dealerTotal > 21){                                                         //dealer loses because he busts
			cout << "Dealer busts! you win $" << bet << endl;
			bankroll = bankroll + bet;														// calculates the players new bankroll based on whether they won or lost
			cout << "Your new bankroll is now $" << bankroll << endl;
			
			if (bankroll <= 0){                                                                 //if the player wants to play again but their bankroll is empty then they cannot play again and the game ends
			cout << "You've run out of money! GAME OVER." << endl;
			break;
			}

			cout << "Play again? (y / n)" << endl;
			cin >> playing;
			while (playing != 'y' && playing != 'n'){										// calculates the players new bankroll based on whether they won or lost
					cout << "I don't understand. Please enter y or n" << endl;				//outputs instructions and statement
					cin >> playing; 
			}
		}
		else if (dealerTotal > playerTotal){                                                //dealer wins because his total is greater than the players
			cout << "Dealer wins! You loose $" << bet << endl;
			bankroll = bankroll - bet;														// calculates the players new bankroll based on whether they won or lost
			cout << "Your new bankroll is now $" << bankroll << endl;
			
			if (bankroll <= 0){                                                                 //if the player wants to play again but their bankroll is empty then they cannot play again and the game ends
			cout << "You've run out of money! GAME OVER." << endl;
			break;
			}

			cout << "Play again? (y / n)" << endl;
			cin >> playing;
			while (playing != 'y' && playing != 'n'){                                       // calculates the players new bankroll based on whether they won or lost
					cout << "I don't understand. Please enter y or n" << endl;				//outputs instructions and statement
					cin >> playing; 
			}
		}
		else if (playerTotal > dealerTotal){												//player wins because his total is greater
			cout << "You win! you win $" << bet << endl;
			bankroll = bankroll + bet;														// calculates the players new bankroll based on whether they won or lost
			cout << "Your new bankroll is now $" << bankroll << endl;
			
			if (bankroll <= 0){                                                                 //if the player wants to play again but their bankroll is empty then they cannot play again and the game ends
			cout << "You've run out of money! GAME OVER." << endl;
			break;
			}

			cout << "Play again? (y / n)" << endl;
			cin >> playing;
			while (playing != 'y' && playing != 'n'){                                       // calculates the players new bankroll based on whether they won or lost
					cout << "I don't understand. Please enter y or n" << endl;				//outputs instructions and statement
					cin >> playing; 
			}
		}
		else if (playerTotal == dealerTotal){                                               //tie b/c the totals equal
			cout << "It is a tie! Your bet is returned" << endl;
			cout << "Your new bankroll is still $" << bankroll << endl;						//because its a tie the bankroll doesn't change (although the house should always win in a tie situation)
			
			if (bankroll <= 0){                                                                 //if the player wants to play again but their bankroll is empty then they cannot play again and the game ends
			cout << "You've run out of money! GAME OVER." << endl;
			break;
			}

			cout << "Play again? (y / n)" << endl;
			cin >> playing;
			while (playing != 'y' && playing != 'n'){                                       // calculates the players new bankroll based on whether they won or lost
					cout << "I don't understand. Please enter y or n" << endl;				//outputs instructions and statement
					cin >> playing; 
			}
		}

	}

	if (bankroll != 0){
	cout << "Thanks for playing! Your final bankroll was $" << bankroll <<endl;					//if the input for playing is 'n' then the while loop for the entire game breaks and thanks the player for playing and outputs the final bankroll
	}

	return 0;
}
