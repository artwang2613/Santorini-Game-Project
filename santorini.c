#include <stdio.h>

//AI is dumb so always chooses the first legal move that the player can make as its starting pos
void setAIStartingPos(int board[6][6], int legalMoves[][2], int aPos[3]){
    aPos[0] = legalMoves[0][0];
    aPos[1] = legalMoves[0][1];
    aPos[2] = 2;
    board[aPos[0]][aPos[1]] = 16;
}

//prompts player for starting pos, asks again if invalid "# #" choice
void setPlayerStartingPos(int board[6][6], int pPos[3]){
    char pInput[8] = {0};
    printf("Please Choose Starting Position\n");
    scanf("%5c", pInput);
    int pX = pInput[0] - 48;
    int pY = pInput[2] - 48;
    
    while((pX > 6 || pX < 1) || (pY > 6 || pY < 1)){
        
        printf("Please Choose Different Position\n");
        scanf("%5c", pInput);
        pX = pInput[0] - 48; //char to int conversion
        pY = pInput[2] - 48;
    }
    pPos[0] = pX - 1;
    pPos[1] = pY - 1;
    pPos[2] = 2; //starting value;
    board[pX-1][pY-1] = 15;
}

//generates all legal moves of the first position passed in, other position is for player/ai collision
//checks if the 8 tiles around the first pos are legal to travel to
void getLegalMoves(int legalMoves[8][2], int pos[3], int otherPos[3]){
    int insert = 0;
    int pX = pos[0];
    int pY = pos[1];
    int oX = otherPos[0];
    int oY = otherPos[1];
    for(int row = pos[0] - 1; row < pos[0] + 2; ++row){
        for(int col = pos[1] - 1; col < pos[1] + 2; ++col){
            if((row != otherPos[0] || col != otherPos[1]) && (row != pos[0] || col != pos[1])){
                if((row >= 0 && row < 7) && (col >= 0 && col < 7)){
                        legalMoves[insert][0] = row;
                        legalMoves[insert][1] = col;
                        ++insert;
    
                }
            }
            
        }
    }
}

//pOrAi -> 1 if player to increment, -1 for AI to decrement.
//takes care of building and destroying "buildings" for both AI and player
void build(int board[6][6], int legalMoves[][2], int pos[2], int aPos[2], int pOrAI){
    int buildR = -1;
    int buildC = -1;
    int row = pos[0];
    int col = pos[1];
    int stepRow = 0;
    int stepCol = 0;
    for(int i = 0; i < 8; i++){
        buildR = legalMoves[i][0];
        buildC = legalMoves[i][1];
        stepRow = buildR - row; //figures out which direction to build/destroy
        stepCol = buildC - col; 
        
        while((buildR >= 0 && buildR < 6) && (buildC >= 0 && buildC < 6)){
            if(buildR == aPos[0] && buildC == aPos[1]){
                break;
            }
            if(board[buildR][buildC] == 0 || board[buildR][buildC] == 4){
                break;
            }
            board[buildR][buildC] = board[buildR][buildC] + pOrAI;
            buildR += stepRow;
            buildC += stepCol;
        }
    }
}

//my simple ai takes the move/chooses a move if multiple to get it closest to the player.
//Not particularly smart or successful, but 5 year old worthy
void aiMove(int board[6][6],int legalMoves[][2], int pPos[], int aPos[]){
    int futureRow = -1;
    int futureCol = -1;
    int pRow = pPos[0];
    int pCol = pPos[1];
    int diffRow = 0;
    int diffCol = 0;
    
    int approxDist = 0;
    
    int shortest = 10000;
    int shortestIndex = 0;
    
    for(int i = 0; i < 8; ++i){
        futureRow = legalMoves[i][0];
        futureCol = legalMoves[i][1];
        
        diffRow = pRow - futureRow;
        diffCol = pCol - futureCol;
        approxDist = diffRow * diffRow + diffCol * diffCol;
        
        if(approxDist < shortest){
            shortest = approxDist;
            shortestIndex = i;
        }
    }
    board[aPos[0]][aPos[1]] = aPos[2];
    aPos[0] = legalMoves[shortestIndex][0];
    aPos[1] = legalMoves[shortestIndex][1];
    aPos[2] = board[aPos[0]][aPos[1]];
    board[aPos[0]][aPos[1]] = 16;
    printf("AI Moved To: %i %i\n", aPos[0], aPos[1]);
}



void playerMove(int board[6][6],int legalMoves[][2], int pPos[]){
    char pInput[5] = {0};
    printf("Please Choose Move\n");
    scanf("%4c", pInput);
    int pX = pInput[0] - 48;
    int pY = pInput[2] - 48;
    int temp[8][2];  
    
    int legal = 0; //0 is false, 1 is true;
    while(legal == 0){
        for(int i = 0; i < 8; ++i){
            if(pX - 1 == legalMoves[i][0] && pY - 1 == legalMoves[i][1]){
                board[pPos[0]][pPos[1]] = pPos[2]; //replace current tile with its value stored in pPos
                pPos[0] = pX - 1;
                pPos[1] = pY - 1;
                pPos[2] = board[pPos[0]][pPos[1]];
                board[pPos[0]][pPos[1]] = 15;  //player is designated as 15
                legal = 1;
            }
        }
        if(legal == 0){
            printf("Please Choose Different Move\n");
            scanf("%4c", pInput);
            pX = pInput[0] - 48;
            pY = pInput[2] - 48;
        }
    }
}




void printBoard(int board[6][6]){
    printf(" 0  1  2  3  4  5  6\n");
    for(int i = 0; i < 6; ++i){
        printf("%2i ", i + 1);
        for(int j = 0; j < 6; ++j){
            printf("%2i ", board[i][j]);
        }
        printf("\n");
    }
}

void updateCount(int board[6][6], int fourAndZero[2]){
    int fourCounter = 0;
    int zeroCounter = 0;
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 6; ++j){
            if(board[i][j] == 4){
                fourCounter += 1;
            }
            if(board[i][j] == 0){
                zeroCounter += 1;
            }
        }
    }
    fourAndZero[0] = fourCounter;
    fourAndZero[1] = zeroCounter;
}

void resetLegal(int legalMoves[8][2]){
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 2; ++j){
            legalMoves[i][j] = -10; //-10 is kinda arbitrary, just using a negative number to indicate illegal moves
        }
    }
}

//player is represented by num 15
//ai is represented by num 16



int main()
{
    int board[6][6] = {{2, 2, 2, 2, 2, 2},
                       {2, 2, 2, 2, 2, 2},
                       {2, 2, 2, 2, 2, 2},
                       {2, 2, 2, 2, 2, 2},
                       {2, 2, 2, 2, 2, 2},
                       {2, 2, 2, 2, 2, 2}};
    int legalMoves[8][2];//contains the 8 legal or illegal moves you could take from a single tile
    resetLegal(legalMoves);
    int pPos[3] = {0, 0, 0};//row, col, val of tile
    int aPos[3] = {-1, -1, -1};
    
    int fourAndZero[2] = {0, 0}; //# of 4, # of 0
     
    int turn = 0; //0 is player, 1 is AI
    setPlayerStartingPos(board, pPos);
    getLegalMoves(legalMoves, pPos, aPos);
    setAIStartingPos(board, legalMoves, aPos);
    
    printBoard(board);
    
    
    
    while(fourAndZero[0] < 10 && fourAndZero[1] < 10){
        resetLegal(legalMoves);
        if(turn == 0){
            printf("Player Turn\n");
            getLegalMoves(legalMoves, pPos, aPos);
            playerMove(board, legalMoves, pPos);
            resetLegal(legalMoves);
           
	    getLegalMoves(legalMoves, pPos, aPos);
            build(board, legalMoves, pPos, aPos, 1);
            updateCount(board, fourAndZero);
            resetLegal(legalMoves);
           
	    turn = 1;
        }else{
            printf("AI Turn\n");
            getLegalMoves(legalMoves, aPos, pPos);
            aiMove(board, legalMoves, pPos, aPos);
	    resetLegal(legalMoves);

            getLegalMoves(legalMoves, aPos, pPos);
            build(board, legalMoves, aPos, pPos, -1);
            updateCount(board, fourAndZero);

            resetLegal(legalMoves);
            turn = 0;
        }
        printBoard(board);
	printf("Score: %i fours vs. %i zeroes\n", fourAndZero[0], fourAndZero[1]);
	printf("\n");
    }
    if(fourAndZero[0] > fourAndZero[1]){
        printf("Player Wins!\n");
    }else{
        printf("AI Wins!\n");
    }
    printf("Score: %i fours vs. %i zeroes\n", fourAndZero[0], fourAndZero[1]);
    return 0;
}


