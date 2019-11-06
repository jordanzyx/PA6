/*
Name: Jordan Muehlbauer
Date: 10/20/2019
Usage: Method definitions for source.c to use and to be started from main.c
*/

#include <stdio.h>

void start();

void printMenu();

void generateRandomShips(char array[10][10]);

void placeShip(char array[10][10], int x, int y, int direction, int ship);

int getSizeFromShip(int ship);

char getCharFromShip(int ship);

int canPlaceShip(char array[10][10], int x, int y, int direction, int ship);

void displayPlayerBoard(char array[10][10]);

void displayComputerBoard(char array[10][10]);

void setUpPlayerBoard(char array[10][10]);

char* getNameFromShip(int ship);

int playerTurn(char player[10][10], char computer[10][10], FILE* log, int* playerHits, int* playerMisses);

int computerTurn(char player[10][10], char computer[10][10], FILE* log, int* computerHits, int* computerMisses);

int isPlayerAlive(char board[10][10]);

int isTileAShip(char found);

void logGame(int playerHits, int playerMisses, int computerHits, int computerMisses, int whoWon, FILE* log);

int doesBoardContainChar(char array[10][10], char c);

void emptyArray(char array[10][10]);

