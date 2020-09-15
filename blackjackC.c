/*
This file will have base functions that are used for the main function

Assembly functions will be used within these except for shuffle which is commented out and replaced by an ARM version
*/

#include <stdlib.h>
#include <stdio.h>

//function prototypes needed
extern void shuffleFlipARM(int deck[], int count);
extern void shuffleSwapARM(int deck[]);
extern int  pseudoRandomGen(int);

void shuffle(int deck[])
/*
function description:
  this function is meant to pass the deck array and then mix around the content while still
  maintaining all of the content within it

additional notes:
  this shuffle function is meant to be passed right when the game starts so that the deck
  used within the game will be unable to read/predict consistently, also this function
  depends on the user inputting a number of players that can use only one deck per game

  When translating to assembly, this function will probably be split into seperate shuffle
  functions to make it easier and less confusing for myself
*/
{
  int count = 51;
  int seed;
  //deck is the array and count is the size of the array, giving us the entire deck array in this function
  
  printf("|Enter a shuffle seed(any integer) for this game: ");
  scanf("%d",&seed);
  seed = pseudoRandomGen(seed);
  int temp = seed;
  int tempCard;
  while(temp > 52)
  {
    temp = temp/2 +1;
  }
  
  for(int i = 0; i <= temp; i++)
  {
    //this part of shuffling will switch card places with other cards to get some general mizing around

    shuffleFlipARM(deck,count/2);
//    for(int j = 0; j < count/2; j+=2)
//    {
//      tempCard = deck[j];
//      deck[j] = deck[count];
//      deck[count] = tempCard;
//      count = count-2;
//    }

    //swaps cards by two's throughout the whole deck

    shuffleSwapARM(deck);
//    
//    for(int j = 0; j < 52; j+=2)
//    {
//      tempCard = deck[j];
//      
//      deck[j] = deck[j+1];
//      deck[j+1] = tempCard;
//
//    }
    
  }
}
