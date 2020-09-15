/*********************************************************************
* Author: Dimitri Duron
*
* Description: Play a game of Blackjack
*
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/


//header files
#include <stdio.h>
#include <stdlib.h>



/**************function prototypes*****************/

// i/o functions
extern void intro();
extern void mainMenu();
//extern void settingsOut();
//extern void patchNotes();
extern void endProgram();
extern void replay();
extern void outputCard(int);
extern void win(int, int);
extern void lose(int, int);
extern void tie(int);

// other functions
extern void shuffle(int deck[]);
extern int handSum(int, int);

/*
These are the general steps that the program will undergo to successfully complete the program description
--------------------------------------------------------------------------------------------------------------------
Step 1: Introduction
This step will contain various user interfaces and different commands that will have results

Step 2: Main Menu
This step will contain a "Start" function that will start a game with the settings in place.
There will also be a "Settings" function that will cover different things such as user-players and computer-players.
There will also be an "Patch Notes" selection that will display the various updates through out production that
  will cover updates made to the game after the first successful run. This will contain major such as bug fixes etc.

***"START" was selected at this point and 2 user-players and 2 computer-players will be assumed past this point

Step 3: Deck Shuffle
The deck that is created in main will be mixed up the deck array. This will simulate shuffling and make sure that the
  game is authentic and not a seed or pre-planned.

Step 4: Deal Cards
The deck will lose 1 card per person, twice. Each card will be taken from the beginning of the array and deck array will
  shift over and the array will have a counter in which when it reaches 0, the deck will be "empty" and will be randomized again

*Start with Player 1*
*If there are no more user-players, cycle to next computer-player, then go to house hand*

Step 5: Check for Blackjack/Hold/Bust
Examine the total value of the player's hand. If total is 21, declare "Blackjack" for the user. If user has a hand value
  of 17-20, then the player will "Hold". If below or at 16, the player will hit. The options will be automatically set for
  computer-controlled players and the house hand. The user-controlled players will have the option to choose either option.
  Continue until "Bust" or "Hold". Bust is if the hand is >21.

Step 6: Cycle to next Player
If at Player n, shift to Player n+1, if there is no n+1, then shift to house hand.
The player array will be displayed for informational needs above.
Continue to shift until the house has "Bust" or "Hold"

*At this point the House as either bust or hold*

Step 7: Compare House Hand
If the house is at status = -1 or has busted, then everyone that has not yet busted will get status = 2 signifying a win,
  otherwise they get status = -2 for lose.
If the house has not busted, each player will get a comparison to the house and if higher will get status = 2,
  if equal then status = 3 signifying a push, if lower than the house then status = -2 for lose.

Step 8: Replayability
After step7, restart from step 3 if wanted to replay or return to step 2 to go to main menu


*/


int main()
{
  //variable names                         variable descriptions
  int exit    = 0;                        //will end the game if set to 1
  //int players = 1;                        //number of total user controlled players within the game, excludes the house
  //int numNPC  = 0;                        //number of players that will be program-controlled, also excludes the house
  int deck[52];                           //creates the deck as an array to be randomized
  int user[10] = {0,0,0,0,0,0,0,0,0,0};
  int house[10] = {0,0,0,0,0,0,0,0,0,0};
  int menu    = 0;                        //will select what menu option to enter within the main menu
  int exit2menu=0;                        //will exit back to the menu if set to 1, otherwise stay
  int input;
  int input2;
  int game = 1;
  int count1;
  int userCount;
  int houseCount;
  int *deckPtr = &deck[0];


/*
array num     card representation
---------------------------------
1 = Ace
2-10 = num cards
11,12,13 = jack,queen,king respectively
---------------------------------
*/


  //fills the deck with 4 of each type of card given the card representation used above
  int count = 0;
  for(int i = 0;i < 4; i++)
  {
    for(int y = 1; y <= 13; y++)
    {
      deck[count] = y;
      count++;
    }
  }
  count = 0;



  //*****************basically beginning of main function*******************
  intro();
  int i = 0;
  while(exit == 0)
  {
    mainMenu();
    printf("|");
    scanf("%d",&input);

    if(input == 0)
    {
      exit = 1;
      menu = 0;
    }
    else if(input == 1)
    {
      menu = 1;
    }
    

    if(menu == 1)                               //Starts a game with the given settings
    {
      while(exit2menu == 0)
      {
        /*BEGINNING OF GAME*/
        shuffle(deck);
        user[0] = 0;
        house[0] = 0;

        user[1] = deck[0];
        user[0] = handSum(user[0],deck[0]);
        user[2] = deck[1];
        user[0] = handSum(user[0],deck[1]);
        house[1] = deck[2];
        house[0] = handSum(house[0],deck[2]);
        house[2] = deck[3];
        house[0] = handSum(house[0],deck[3]);
        userCount = 2;
        houseCount = 2;
        count = 4;

hit:
        printf("|--------------   Your Cards ---------------|\n");
        printf("---------------------------------------------\n");
        count1 = 1;
        do
        {
          outputCard(user[count1]);
          count1++;
          if(userCount >= count1)
          {
            printf("& ");
          }
        } while(userCount >= count1);

        //if the player busts, it will be checked at this point of the game
        if(user[0] > 21)
        {
          printf("\n|Total: %d BUSTED, YOU LOST\n", user[0]);
          goto end;
        }
        else if(user[0] == 21)
        {
          printf("\n|BLACKJACK! I wonder if you win...\n");
          goto blackjack;
        }

        printf("\n|--------------  House Card  ---------------|\n");
        printf("---------------------------------------------\n");
        outputCard(house[1]);
        printf("\n---------------------------------------------\n");
        printf("|--------------  Hit or Hold ---------------|\n");
        printf("---------------------------------------------\n");
        printf("| 1) Hit                                    |\n");
        printf("| 0) Hold                                   |\n");
        printf("---------------------------------------------\n");
        //scanf("%d", input2);
        scanf("%d", &input);

        //i was really lazy when coding this part so instead of implementing another while loop i just did a goto because thats easier
        //to fit into here, I will be careful when using it though bc i know people say it can really mess with your code sometimes.
       if(input == 1)
        {
          //this section takes care of the "hit" action such as adding a card to user array and incrementing the deck array
          userCount++;
          user[userCount] = deck[count];
          user[0] = handSum(user[0],deck[count]);
          count++;
          goto hit;
        }

blackjack:
        while(house[0] < 17)
        {
          houseCount++;
          house[houseCount] = deck[count];
          house[0] = handSum(house[0],deck[count]);
          count++;
          //displays house hand as it comes into their hand
          count1 = 1;
          printf("\n|--------------  House Hand  ---------------|\n");
          printf("---------------------------------------------\n");
          do
          {
            outputCard(house[count1]);
            count1++;
            if(houseCount >= count1)
            {
              printf("& ");
            }
          } while(houseCount >= count1);
          //if house busts, user automatically wins at this point given that user either is not going to be here if they
          //havent busted yet, user[0] is set to 1 to represent win
        }
        
        //user wins here
        if(house[0] > 21 || user[0] > house[0])
        {
          win(user[0],house[0]);
          user[0] = 1;
        }
        //user loses here
        else if(house[0] > user[0])
        {
          lose(user[0],house[0]);
          user[0] = 0;
        }
        //the game is tied and no one loses/wins
        else
        {
          tie(user[0]);
        }


end:
        replay();
        printf("|");
        scanf("%d",&input);
        if(input == 0)
        {
          exit2menu = 1;
        }
      }
    }
/*


    else if(menu == 2)                           //Enters into settings to show what current settings can be edited
    {
      while(exit2menu == 0)
      {
        /*BEGINNING OF SETTINGS*
        settingsOut();
      }
    }


/*
    else if(menu == 3)                          //Goes into patch notes that the game has undergone after initial completion
    {
      while(exit2menu == 0)
      {
        /*BEGINNING OF PATCH NOTES*
        patchNotes();
      }
    }
*/

  }//end of menu while loop



  endProgram();



  return 0;
}//end of main function

/*The code below will mostly be i/o functions that do not need any actual coding/problem thinking*/
//printf("||\n");


//intro output
void intro()
{
  printf("---------------------------------------------\n");
  printf("|------Welcome to Dimitri's Blackjack-------|\n");
  printf("---------------------------------------------\n");
  printf("|Game: Blackjack                            |\n");
  printf("|Goal: Reach a card count of 21 or a value  |\n");
  printf("|       closer to 21 than the house         |\n");
  printf("---------------------------------------------\n");
  printf("|This project is for CompE-271              |\n");
  printf("---------------------------------------------\n");
  printf("|Entering the Main Menu...                  |\n");
  printf("---------------------------------------------\n");
}

//main menu output
void mainMenu()
{
  printf("|Main Menu                                  |\n");
  printf("---------------------------------------------\n");
  printf("|Enter a valid number to choose an action   |\n");
  printf("---------------------------------------------\n");
  printf("| 1) New Game                               |\n");
//  printf("| 2) Settings                               |\n");
//  printf("| 3) Patch Notes                            |\n");
  printf("|                                           |\n");
  printf("| 0) Exit                                   |\n");
  printf("---------------------------------------------\n");
}

/*Scrapped as of now
void settingsOut()
{
  printf("|Settings Menu                              |\n");
  printf("---------------------------------------------\n");
  printf("|Enter an input to adjust game settings     |\n");
  printf("---------------------------------------------\n");
  printf("| 1) Computer controlled Players            |\n");
  printf("|                                           |\n");
  printf("| 0) Exit Settings Menu                     |\n");
  printf("---------------------------------------------\n");
}
*/

/*Scrapped as of now
void patchNotes()
{
  printf("|Patch Notes                                |\n");
  printf("---------------------------------------------\n");
  printf("|                                           |\n");
  printf("|                                           |\n");
  printf("| 0) Exit                                   |\n");
  printf("---------------------------------------------\n");
}
*/

void win(int user, int house)
{
  printf("\n|You won with %d versus the house's %d\n", user, house);
}

void lose(int user, int house)
{
  printf("\n|You lost with %d versus the house's %d\n",user, house);
}

void tie(int val)
{
  printf("\n|You tied with the house with a hand value of %d\n", val);
}


//needs to get converted to ARM

//int handSum(int deck, int card)
//{
//  int sum = 0;
//
//  if(card == 13 || card == 12 || card == 11)
//  {
//    card = 10;
//  }
//  if(card == 1 && deck+11 <= 21)
//  {
//    card = 11;
//  }
//  sum = deck + card;
//
//  return sum;
//}


void outputCard(int card)
{
  if(card == 1)
  {
    printf("Ace ");
  }
  else if(card == 11)
  {
    printf("Jack ");
  }
  else if(card == 12)
  {
    printf("Queen ");
  }
  else if(card == 13)
  {
    printf("King ");
  }
  else 
  {
    printf("%d ",card);
  }

}

void replay()
{
  printf("|Another Game?                              |\n");
  printf("---------------------------------------------\n");
  printf("| 1) Yes                                    |\n");
  printf("| 0) No                                     |\n");
  printf("---------------------------------------------\n");
}

void endProgram()
{
  printf("|--------------Ending Program---------------|\n");
  printf("---------------------------------------------\n");
}

/*************************** End of file ****************************/
