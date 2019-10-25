//
// Created by Jordan on 10/20/2019.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "source.h"

#define CARRIER 1
#define BATTLESHIP 2
#define CRUISER  3
#define SUBMARINE  4
#define DESTROYER  5

#define HIT '*'
#define MISS 'm'

#define UP  1
#define DOWN  2
#define RIGHT  3
#define LEFT  4

void start() {
    srand(time(NULL));

    //Handle the initial menu
    printMenu();
    system("pause");
//    system("cls");

    //Create the variables for player and computer
    char player[10][10];
    char computer[10][10];
    int playerHits = 0;
    int playerMisses = 0;
    int computerHits = 0;
    int computerMisses = 0;


    //Create LOG file
    FILE *log = fopen("C:\\Users\\Jordan\\CLionProjects\\PA6\\battleship.log","r");

    //Set every element to '-'
    emptyArray(player);
    emptyArray(computer);

    //Set up the boards
    generateRandomShips(computer);
    setUpPlayerBoard(player);

    int turn = (rand() % 2) + 1;
    int game = 1;


    while(game == 1){

        if(turn == 1){
            game = playerTurn(player,computer,log,&playerHits,&playerMisses);
            if(game == -1){
                logGame(playerHits,playerMisses,computerHits,computerMisses,1,log);
            }
        }

        if(turn == 2){
            game = computerTurn(player,computer,log,&computerHits,&computerMisses);
            if(game == -1){
                logGame(playerHits,playerMisses,computerHits,computerMisses,2,log);
            }
        }



        if(turn == 1){turn = 2;
        continue;}
        if(turn == 2)turn = 1;

    }


    fclose(log);
}

void setUpPlayerBoard(char array[10][10]) {

    int choice = 0;
    while (choice != 1 && choice != 2) {
        printf("Please select from the following menu:\n");
        printf("1. Enter positions of ships manually.\n");
        printf("2. Allow the program to randomly select positions of ships.\n");
        scanf("%d", &choice);

        if (choice < 1 || choice > 2)continue;

        if (choice == 1) {
            for (int i = 1; i <= 5; ++i) {

                int x, y;
                char d;
                int isPlaced = -1;

                while (isPlaced != 1) {
                    displayPlayerBoard(array);
                    printf(
                            "Please enter the row,column and direction (u/d/r/l) you want to place the %s, it is %d tiles long\n",
                            getNameFromShip(i), getSizeFromShip(i));
                    scanf("%d %d %c", &x, &y, &d);

                    if (x < 0 || x > 9)continue;
                    if (y < 0 || y > 9)continue;
                    if (d != 'u' && d != 'd' && d != 'r' && d != 'l')continue;

                    int direction = 0;
                    if (d == 'u')direction = UP;
                    if (d == 'd')direction = DOWN;
                    if (d == 'r')direction = RIGHT;
                    if (d == 'l')direction = LEFT;

                    int canPlace = canPlaceShip(array, x, y, direction, i);

                    if (canPlace != 1) {
                        printf("Sorry that ship will not fit there!\n");
                        system("pause");
                        continue;
                    }

                    placeShip(array, x, y, direction, i);
                    isPlaced = 1;
                }

            }
        } else generateRandomShips(array);
    }
}

char *getNameFromShip(int ship) {
    if (ship == CARRIER)return "Carrier";
    if (ship == DESTROYER)return "Destroyer";
    if (ship == SUBMARINE)return "Submarine";
    if (ship == CRUISER)return "Cruiser";
    return "Destroyer";
}

void generateRandomShips(char array[10][10]) {
    for (int i = 1; i <= 5; ++i) {
        int placed = -1;
        while (placed == -1) {
            int x = rand() % 10;
            int y = rand() % 10;
            int direction = (rand() % 4) + 1;


            if (canPlaceShip(array, x, y, direction, i) == 1) {
                placeShip(array, x, y, direction, i);
                placed = 1;
            }

        }

    }


}

void placeShip(char array[10][10], int x, int y, int direction, int ship) {
    int length = getSizeFromShip(ship);
    char shipChar = getCharFromShip(ship);
    if (direction == UP) {
        for (int i = 0; i < length; ++i) {
            array[x - i][y] = shipChar;
        }
    }

    if (direction == DOWN) {
        for (int i = 0; i < length; ++i) {
            array[x + i][y] = shipChar;
        }
    }

    if (direction == RIGHT) {
        for (int i = 0; i < length; ++i) {
            array[x][y + i] = shipChar;
        }
    }

    if (direction == LEFT) {
        for (int i = 0; i < length; ++i) {
            array[x][y - i] = shipChar;
        }
    }
}

int canPlaceShip(char array[10][10], int x, int y, int direction, int ship) {
    //Collect ship size and type
    int size = getSizeFromShip(ship);
    char c = getCharFromShip(ship);

    if (direction == UP) {
        if (x - size < 0)return -1;

        for (int i = 0; i < size; ++i) {
            if (array[x - i][y] != '-')return -1;
        }

        return 1;
    }

    if (direction == DOWN) {
        if (x + size > 9)return -1;

        for (int i = 0; i < size; ++i) {
            if (array[x + i][y] != '-')return -1;
        }

        return 1;

    }

    if (direction == RIGHT) {
        if (y + size > 9)return -1;
        for (int i = 0; i < size; ++i) {
            if (array[x][y + i] != '-')return -1;
        }

        return 1;
    }

    if (direction == LEFT) {
        if (y - size < 0)return -1;
        for (int i = 0; i < size; ++i) {
            if (array[x][y - i] != '-')return -1;
        }
        return 1;
    }

    return -1;
}

char getCharFromShip(int ship) {
    if (ship == CARRIER) return 'c';
    if (ship == BATTLESHIP) return 'b';
    if (ship == CRUISER) return 'r';
    if (ship == SUBMARINE) return 's';
    return 'd';
}

int getSizeFromShip(int ship) {
    if (ship == CARRIER) return 5;
    if (ship == BATTLESHIP) return 4;
    if (ship == CRUISER) return 3;
    if (ship == SUBMARINE) return 3;
    return 2;
}

void emptyArray(char array[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            array[i][j] = '-';
        }
    }
}

int playerTurn(char player[10][10],char computer[10][10],FILE *log,int *playerHits,int *playerMisses){
    displayPlayerBoard(player);
    displayComputerBoard(computer);
    int x,y;
    int keepGoing = 1;
    while (keepGoing == 1){
        printf("Enter a target:\n");
        scanf("%d%d",&x,&y);

        if (x < 0 || x > 9)continue;
        if (y < 0 || y > 9)continue;

        char charAt = computer[x][y];

        if(charAt == MISS){
            printf("You have already shot there chose a different location\n");
            continue;
        }

        int hit = isTileAShip(charAt);

        if(hit == 1){
            //Increase stats
            *playerHits += 1;

            char ship = computer[x][y];
            computer[x][y] = HIT;
            if(doesBoardContainChar(computer,ship) == 1){
                printf("%d,%d is a hit!\n",x,y);
                fprintf(log,"Player1: %d,%d \"hit\"");
            }

            else {
                printf("%d,%d is a hit! sunk %s!\n",x,y,getNameFromShip(ship));
                fprintf(log,"Player1: %d,%d \"hit\" sunk %s!");
            }

            //Check if they have sunk every ship
            if(isPlayerAlive(computer) == -1){
                printf("Player 1 wins!\n");
                printf("Outputting stats to the log file\n");
                return -1;
            }
        } else {
            //Increase stats
            *playerMisses += 1;

            printf("%d,%d is a miss!\n",x,y);
            computer[x][y] = MISS;
            fprintf(log,"Player1: %d,%d \"miss\"",x,y);
            keepGoing = -1;
        }
    }
    system("pause");
    return 1;
}

int isTileAShip(char found){
    if(found == 'c')return 1;
    if(found == 'd')return 1;
    if(found == 'r')return 1;
    if(found == 's')return 1;
    if(found == 'b')return 1;
    return -1;
}

int computerTurn(char player[10][10],char computer[10][10],FILE *log,int *computerHits,int *computerMisses){
    displayPlayerBoard(player);
    displayComputerBoard(computer);
    int x,y,keepGoing = 1;

    while(keepGoing == 1){
        x = rand() % 10;
        y = rand() % 10;

        if (player[x][y] == MISS)continue;

        printf("Player 2 selects %d,%d\n",x,y);
        char charAtShot = player[x][y];

        int hit = isTileAShip(charAtShot);

        if(hit == 1){
            //Increase stats
            *computerHits += 1;
            char ship = player[x][y];
            player[x][y] = HIT;
            if(doesBoardContainChar(player,ship) == 1){
                fprintf(log,"Player2: %d,%d \"hit\"");
                printf("%d,%d is a hit!\n",x,y);
            }
            else{
                fprintf(log,"Player2: %d,%d \"hit\" sunk %s!",x,y,getNameFromShip(ship));
                printf("is a hit! %d,%d \"hit\" sunk %s!",x,y,getNameFromShip(ship));
            }

            //Check if they have sunk every ship
            if(isPlayerAlive(player) == -1){
                printf("Player 2 wins!\n");
                printf("Outputting stats to the log file\n");
                return -1;
            }
        } else {
            //Increase stats
            *computerMisses += 1;

            printf("%d,%d is a miss!\n",x,y);
            player[x][y] = MISS;
            fprintf(log,"Player1: %d,%d \"miss\"",x,y);
            keepGoing = -1;
        }
        system("pause");
    }

    return 1;
}

void logGame(int playerHits,int playerMisses,int computerHits,int computerMisses,int whoWon,FILE *log){
    //Log Winners
    if(whoWon == 1)fprintf(log,"Player 1 wins Player 2 loses\n");
    else fprintf(log,"Player 2 wings Player 1 loses\n");

    //Log player stats
    fprintf(log,"*** Player1 Stats ***\n");
    fprintf(log,"Number of Hits: %d\n",playerHits);
    fprintf(log,"Number of Misses: %d\n",playerMisses);
    fprintf(log,"Total Shots: %d\n",playerHits + playerMisses);
    fprintf(log,"Hit/Miss Ratio %d%%\n", (int)((double)playerHits/playerMisses * 100));
    fprintf(log,"\n");
    //Log computer stats
    fprintf(log,"*** Player2 Stats ***\n");
    fprintf(log,"Number of Hits: %d\n",computerHits);
    fprintf(log,"Number of Misses: %d\n",computerMisses);
    fprintf(log,"Total Shots: %d\n",computerHits + computerMisses);
    fprintf(log,"Hit/Miss Ratio %d%%\n", (int)((double)computerHits/computerMisses * 100));
}

void printMenu() {
    printf("***** Welcome to Battleship! *****\n");
    printf("1. This is a two player game.\n");
    printf("2. Player1 is you and Player2 is the computer.");
    printf("3. Etc. (You need to list the rest of the rules here.)\n");
}


void displayPlayerBoard(char array[10][10]) {
    printf("Player 1's Board\n");
    printf("  0123456789\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", i);
        for (int j = 0; j < 10; ++j) {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }
}

void displayComputerBoard(char array[10][10]) {
    printf("Player 2's Boarder\n");
    printf("  0123456789\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", i);
        for (int j = 0; j < 10; ++j) {
            char found = array[i][j];
            if (found == MISS || found == HIT)printf("%c", found);
            else printf("-");
        }
        printf("\n");
    }
}

int doesBoardContainChar(char array[10][10], char c) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (array[i][j] == c)return 1;
        }
    }
    return -1;
}

int isPlayerAlive(char board[10][10]){

    for (int i = 1; i < 5; ++i) {
        if(doesBoardContainChar(board,getCharFromShip(i)) == 1)return 1;
    }
    return -1;
}