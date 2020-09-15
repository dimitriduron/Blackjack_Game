/*
 * Project ARM Functions
 *
 *  Author: Dimitri Duron
 *  RedID: 821843458
 */


/*
function name: handSum
function objective:
  Accumulate the value of a hand's cards and return the result. This includes correcting the face card values and checking
  for Ace values. The Ace value will be either be 11 or 1, and will not be able to change throughout the game, so various Ace's
  may bug out the game.
*/
 .global handSum
  .data
  // declare any global variables here
  //r0 has deck value
  //r1 has card value
  .text
  handSum:
  mov   r12,r13		// save stack pointer into register r12
  sub   sp,#32		// reserve 32 bytes of space for local variables 
  push  {lr}		// push link register onto stack -- make sure you pop it out before you return 

  //r2 is sum ,will return this at the end of the function
  mov r2,#0
  
  //checks for numbered card
  cmp r1,#10
  ble skip
  cmp r1,#2
  bge skip

  //checks for face cards
  cmp r1,#11
  bge face

  //only aces at this point
  //if function here
  mov r3,#11
  add r3,r0
  //(r3 <= 21)
  cmp r3,#21
  blt skip

  //ace needs to be changed to be 11
  mov r1,#11
  b   skip


face:
  //moves hand value into card for face cards
  mov r1,#10

skip:
  add r2,r1,r0      //adds deck & card into sum
  mov r0,r2
  //end of function

  /*
  {
    int sum = 0;

    if(card == 13 || card == 12 || card == 11)
    {
      card = 10;
    }
    if(card == 1 && deck+11 <= 21)
    {
      card = 11;
    }
    sum = deck + card;

    return sum;
  }
  */


  pop {lr}			// pop link register from stack 
  mov sp,r12		// restore the stack pointer -- Please note stack pointer should be equal to the 
					// value it had when you entered the function .  
  mov pc,lr			// return from the function by copying link register into  program counter


/*
function name: shuffleFlipARM
function objective:
  Pick every 2 cards and swap it with a corresponding card at the end of the deck array
  Will go through half of the array so it doesnt crash into itself
*/
 .global shuffleFlipARM
  .data
  // declare any global variables here
  //r0 has deck array
  //r1 has count/2
  .text
  shuffleFlipARM:
  mov   r12,r13		// save stack pointer into register r12
  sub   sp,#32		// reserve 32 bytes of space for local variables 
  push  {lr}		// push link register onto stack -- make sure you pop it out before you return 

  mov r2,#0       //r2 is j
  mov r3,#0       //r3 is tempCard
  mov r4,#51      //r4 is count
  mov r5,#0       //r5 is deck[count]

start:
  cmp r2,r1
  bge endLoop
  
  lsl r6, r2, #2
  lsl r7, r4, #2
  ldr r3,[r0,r6]
  ldr r5,[r0,r7]
  str r5,[r0,r6]
  str r3,[r0,r7]

  sub r4,#2

  add r2,#2
  b   start

endLoop:


  pop {lr}			// pop link register from stack 
  mov sp,r12                  // restore the stack pointer -- Please note stack pointer should be equal to the 
                              // value it had when you entered the function .  
  mov pc,lr			// return from the function by copying link register into  program counter


/*
function name: shuffleSwapARM
function objective:
  Will cycle through the deck array and swap every 2 cards with themselves to randomize the deck
  for the user and to create a sense of randomization for the user.
*/
 .global shuffleSwapARM
  .data
  // declare any global variables here
  //r0 has deck array
  .text
  shuffleSwapARM:
  mov   r12,r13		// save stack pointer into register r12
  sub   sp,#32		// reserve 32 bytes of space for local variables 
  push  {lr}		// push link register onto stack -- make sure you pop it out before you return 

  
  mov r2,#0             //r0 = deck
                        //r1 = tempCard
                        //r2 = j
                        //r3 = tempVal
                        //r4 = j+1

begin:
  mov r3,#0
  cmp r2,#52
  bge exit              //(r2 - 52>= 0)

  lsl r5, r2, #2
  lsl r6, r4, #2
  ldr r1,[r0,r5]        //tempCard = deck[j]
  add r4,r2,#1          //j+1 = r4
  ldr r3,[r0,r6]        //deck[j] = deck[j+1]
  str r3,[r0,r5]
  str r1,[r0,r6]        //deck[j+1] = tempCard

  add r2,#2             //j+=2
  b   begin
exit:

  pop {lr}			// pop link register from stack 
  mov sp,r12                  // restore the stack pointer -- Please note stack pointer should be equal to the 
                              // value it had when you entered the function .  
  mov pc,lr			// return from the function by copying link register into  program counter

/*
function name: pseudoRandomGen
function objective:
  Will cycle through the deck array and swap every 2 cards with themselves to randomize the deck
  for the user and to create a sense of randomization for the user.
*/
 .global pseudoRandomGen
  .data
  // declare any global variables here
  //r0 has original seed val
  .text
  pseudoRandomGen:
  mov   r12,r13		// save stack pointer into register r12
  sub   sp,#32		// reserve 32 bytes of space for local variables 
  push  {lr}		// push link register onto stack -- make sure you pop it out before you return 

  mov r1,#1
  //original seed is xor'ed w/ #1
  eor r0,r1
  //then rotated binarily to the right by 1 bit
  ror r0,r1


  pop {lr}			// pop link register from stack 
  mov sp,r12                  // restore the stack pointer -- Please note stack pointer should be equal to the 
                              // value it had when you entered the function .  
  mov pc,lr			// return from the function by copying link register into  program counter
