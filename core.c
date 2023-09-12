#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Forward declaration of the struct mobSettings
struct mobSettings;

// Function declarations
int  isPassable(char character);
void clearScreen();
void showScreen(char matrix[11][11]);
void buildMap(char matrix[11][11]);
void introduction();
void bootIntroduction();
char takeInput(char question[10], int nothing);
void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[11][11]);
void takeCommand(struct mobSettings *player);

// Global Struct
struct mobSettings {
    int playerY;
    int playerX;
    char playerSkin;
};

int main() {
    clearScreen();

    // Initialize player settings
    struct mobSettings player;
    player.playerX = 5;
    player.playerY = 5;
    player.playerSkin = 'O';

    // Display boot introduction and wait for input
    bootIntroduction();

    takeCommand(&player);

    return 0;
}

void takeCommand(struct mobSettings *player){
    while (1) {
        char matrix[11][11];
        buildMap(matrix);
        matrix[player->playerY][player->playerX] = player->playerSkin;
        showScreen(matrix);

        char input = takeInput("What next?", 1);

        // Check for user input and perform actions
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            handlePlayerMovement(player, input, matrix);

    }
}
}

void bootIntroduction() {
    printf(" | Está pronto? [S/N]\n");
    printf(" | \"Dica: <skip> para pular a introdução.\"\n");
    printf(" └─> ");
    char charInput[100];
    scanf("%s", charInput);
    if (strcmp(charInput, "skip") != 0) {
        introduction();
    }
}

void buildMap(char matrix[11][11]) {
    
    clearScreen();

    char initialMatrix[11][11] = {

    "WWWWWWWWWWW",
    "W~~~~~~~~~W",
    "W~~~~~~~~~W",
    "W~~~~~~~~~W",
    "W~~W~~~~~~W",
    "W~~~~~~~~~W",
    "W~~~~~~I~~W",
    "W~~~~~~~~~W",
    "W~~~~~~~~~W",
    "W~~~~~~~~~W",
    "WWWWWWWWWWW"
    
    };
        
    // Copy initial map layout to the game matrix
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            matrix[i][j] = initialMatrix[i][j];
        }
    }
}

void introduction() {
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
    printf("    ██████╗ ███████╗ █████╗ ██████╗ ███████╗██╗  ██╗██╗███████╗████████╗\n");
    sleep(1);
    printf("   ██╔════╝ ██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║██║██╔════╝╚══██╔══╝\n");
    sleep(1);
    printf("   ██║  ███╗█████╗  ███████║██████╔╝███████╗███████║██║█████╗     ██║\n"); 
    sleep(1);
    printf("   ██║   ██║██╔══╝  ██╔══██║██╔══██╗╚════██║██╔══██║██║██╔══╝     ██║\n"); 
    sleep(1);
    printf("   ╚██████╔╝███████╗██║  ██║██║  ██║███████║██║  ██║██║██║        ██║\n"); 
    sleep(1);
    printf("    ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝        ╚═╝ \n\n");
    sleep(3);
    }

void showScreen(char matrix[11][11]) {
    // Display each cell of the game matrix
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

char takeInput(char question[10], int nothing) {
    puts("");
    if (nothing) {
        printf(" │ %s\n", question);
    }
    printf(" └─> ");
    char charInput[100];
    scanf("%s", charInput);
    return charInput[0];
}

// Function to check if a character is passable
int isPassable(char character) {
    // Add conditions for different characters here
    // For now, only 'W' (wall) is considered impassable
    return character != 'W';
}

void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[11][11]) {
    // Define the player's new position
    int newPlayerX = player->playerX;
    int newPlayerY = player->playerY;

    // Calculate the new position based on the direction
    switch (direction) {
        case 'w':
            newPlayerY--;
            break;
        case 'a':
            newPlayerX--;
            break;
        case 's':
            newPlayerY++;
            break;
        case 'd':
            newPlayerX++;
            break;
        default:
            // Handle invalid input
            return;
    }

    // Check if the new position is within bounds and is passable
    if (newPlayerX >= 0 && newPlayerX < 11 && newPlayerY >= 0 && newPlayerY < 11 && isPassable(matrix[newPlayerY][newPlayerX])) {
        // Update the player's position
        player->playerX = newPlayerX;
        player->playerY = newPlayerY;
    }
}
