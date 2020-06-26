
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
int board[]={
	:,:,:,:,:,
	:,o,-,x,:,
	:,x,-,-,:,
	:,-,-,-,:,
	:,:,:,:,:,


	 0, 1, 2, 3, 4,
	 5, 6, 7, 8, 9,
	10,11,12,13,14,
	15,16,17,18,19,
	20,21,22,23,24


	 0, 1, 2, 3, 4,
	 5, 6, 7, 8, 9,
	10,11,12,13,14,
	15,16,17,18,19,
	20,21,22,23,24	
}
*/


/*const int NOUGHTS = 1;
const int CROSSES = 2;
const int BORDER = 3;
const int EMPTY = 0;*/
enum {NOUGHTS, CROSSES, BORDER, EMPTY};

const int ConvertTo25[9] ={ 6,   7,  8,
                           11,  12, 13,
                           16,  17, 18};



const int Directions[4] = { 1, 5, 4, 6 };


void InitialiseBoard (int *board) {
    int index = 0;
    
	for (index = 0; index < 25; ++index){
		board[index] = BORDER  ;

	}

	for (index = 0; index < 9; ++index){
		board[ConvertTo25[index]] = EMPTY;

	}

}


void PrintBoard (int *board) {
	int index = 0;
	char pcechars[] = "ox|-";

	printf("\nBoard:\n\n");
	for (index = 0; index < 9 ; ++index){

		if (index != 0 && index%3 == 0){
        	printf("\n\n");
		}

		printf("%4c" ,pcechars[board[ConvertTo25[index]]]);
    }
    printf("\n\n");
}


int GetHumanMove(const int *board) {
		char userInput[4]; 
		int moveOk = 0;
		int move = -1 ;

		while (moveOk == 0) {  

			printf("Please enter a move from 1 to 9:");		
			fgets(userInput, 3, stdin);
			puts(userInput);
			fflush(stdin);


			if(strlen(userInput) != 2) {

				printf("Invalid strlen()\n");
				continue;			
			}

		    if( sscanf(userInput, "%d", &move) != 1) {
		  	       
					move = -1;
					printf("Invalid sscanf()\n");
		            continue;
			}	

		    if( move < 1 || move > 9) {
					move = -1;
					printf("Invalid range\n");
					continue;	
		    }

		    if( board[ConvertTo25[move-1]]!=EMPTY) {
					move= -1;
					printf("Square not available\n");
					continue;
			} 

			moveOk = 1;	  

		}
				
				printf("Making Move...%d\n",(move+1));
				return ConvertTo25[move-1];	   
}

void MakeMove(int *board, const int sq, const int side) {
	board[sq] = side;
}

/* 
	GetComputerMove
	@take: int
	@return: int
*/
int GetComputerMove(const int *board) {

	int index = 0;
	int numFree = 0;
	int availableMoves[9];
	int randMove = 0;

	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) {
			availableMoves[numFree++] = ConvertTo25[index];			
		};
	}

    randMove = (rand() % numFree);
	return availableMoves[randMove];
}


int GetNumForDir(int startSq, const int dir, const int *board, const int us) {
	int found = 0;
	while(board[startSq] != BORDER) {		
		if(board[startSq] != us) {	
			break;
		}
		found++;	
		startSq += dir;
	}	
	return found;
}

int FindThreeInARow(const int *board, const int ourindex, const int us) {

	int DirIndex = 0;
	int Dir = 0;
	int threeCount = 1;
	
	for(DirIndex = 0; DirIndex < 4; ++DirIndex) {
		Dir = Directions[DirIndex];
		threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
		threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);
		if(threeCount == 3) {
			break;
		}
		threeCount = 1;
	}
	return threeCount;
}


int HasEmpty(const int *board) {
	int index = 0;
	
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) return 1;
	}
	return 0;
}


void RunGame(){

	int GameOver = 0;
	int Side = NOUGHTS;
	int LastMoveMade = 0;

	int board[25];

	InitialiseBoard(&board[0]);
	PrintBoard(&board[0]);

	while(!GameOver) {
		if(Side==NOUGHTS) {	
			LastMoveMade = GetHumanMove(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=CROSSES;
			PrintBoard(&board[0]);
		} else {
			
            LastMoveMade = GetComputerMove(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=NOUGHTS;
			PrintBoard(&board[0]);
        }

        if( FindThreeInARow(board, LastMoveMade, Side ^ 1) == 3){

        	printf("Game over!\n");
			GameOver = 1;

			if(Side==NOUGHTS) {
				printf("Computer Wins\n");
			} else {
				printf("Human Wins\n");
			}
        }
		
		
       if (!HasEmpty(board) ){
        printf("Game over!\n");
	    GameOver = 1;
	    printf("It's a draw\n");
       }

		}

		PrintBoard(&board[0]);
	}






int main()
{

	RunGame();
   	
   	return 0;
}
