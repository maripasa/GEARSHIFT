#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Function declarations
void clearScreen();
void showScreen(char matrix[11][11]);
void buildMap(char matrix[11][11]);
void introduction();
void bootIntroduction();
char takeInput();

// Global Structs
struct mobSettings {
    int playerY;
    int playerX;
    char playerSkin;
};

int main() {
    clearScreen();

    struct mobSettings player;
    player.playerX = 5;
    player.playerY = 5;
    player.playerSkin = 'O';

    char charInput[100];
    int intInput = 0;

    bootIntroduction();

    printf("      ⚙  <Enter any input> ⚙\n");
    sleep(1);
    printf("> ");
    scanf("%s", charInput);

    while (1){
        sleep(1);
        char matrix[11][11];
        buildMap(matrix);
        matrix[player.playerY][player.playerX] = player.playerSkin;
        showScreen(matrix);
        if (strcmp(takeInput(), "w") != 0) {
        }else if {
    

    return 0;
}

void bootIntroduction() {
    printf("Está pronto? [S/N]"); 
    sleep(1);
    printf("Dica: <skip> para pular a introdução.\"\n");
    sleep(1);

    char charInput[100];
    scanf("%s", charInput);
    if (strcmp(charInput, "skip") != 0) {
        introduction();
    }
}

void buildMap(char matrix[11][11]) {
    char initialMatrix[11][11] = { 
    {'+', '=', '=', '=', '=', '=', '=', '=', '=', '=', '+'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'|', '~', '~', '~', '~', '~', '~', '~', '~', '~', '|'},
    {'+', '=', '=', '=', '=', '=', '=', '=', '=', '=', '+'}

    };

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            matrix[i][j] = initialMatrix[i][j];  // Copy values from initialMatrix
        }
    }
}

void introduction(){
    clearScreen();
    printf("No ir do tempo, desperta um autômato de mistério e potencial.\n");
    sleep(4);
    printf("O golem metálico emerge do sono, um guardião perdido nas areias do esquecimento.\n");
    sleep(3);
    printf("Sob um céu límpido e sereno,\n");
    sleep(3);
    printf("Um mundo de maravilhas e enigmas é contemplado,\n");
    sleep(3);
    printf("Montes flutuam em harmonia,\n");
    sleep(3);
    printf("Antigas ruínas são abraçadas pela vegetação exuberante.\n\n");
    sleep(5);
    printf("    ██████╗ ███████╗ █████╗ ██████╗     ███████╗██╗  ██╗██╗███████╗████████╗\n");
    sleep(1);
    printf("   ██╔════╝ ██╔════╝██╔══██╗██╔══██╗    ██╔════╝██║  ██║██║██╔════╝╚══██╔══╝\n");
    sleep(1);
    printf("   ██║  ███╗█████╗  ███████║██████╔╝    ███████╗███████║██║█████╗     ██║\n"); 
    sleep(1);
    printf("   ██║   ██║██╔══╝  ██╔══██║██╔══██╗    ╚════██║██╔══██║██║██╔══╝     ██║\n"); 
    sleep(1);
    printf("   ╚██████╔╝███████╗██║  ██║██║  ██║    ███████║██║  ██║██║██║        ██║\n"); 
    sleep(1);
    printf("    ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚══════╝╚═╝  ╚═╝╚═╝╚═╝        ╚═╝ \n\n");
    sleep(1);
}

void showScreen(char matrix[11][11]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            printf("%2c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void clearScreen() {
    system("@cls||clear");
}

char takeInput() {

    char charInput[100];
    scanf("%s", charInput);
    return charInput
}