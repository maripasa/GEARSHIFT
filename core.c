#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Forward declaration of the struct mobSettings
struct mobSettings;

// Function declarations
void clearScreen();
void showScreen(char matrix[11][11]);
void buildMap(char matrix[11][11]);
void introduction();
void bootIntroduction();
char takeInput(char question[10], int nothing);
void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[11][11]);

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

    while (1) {
        char matrix[11][11];
        buildMap(matrix);
        matrix[player.playerY][player.playerX] = player.playerSkin;
        showScreen(matrix);

        char direction = takeInput("What next?", 1);

        // Check for user input and perform actions
        if (direction == 'w' || direction == 'a' || direction == 's' || direction == 'd') {
            handlePlayerMovement(&player, direction, matrix);
        } else {
            // Handle other input cases
        }
    }

    return 0;
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

        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', 'W', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', 'W', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', 'I', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}
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

void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[11][11]) {
    // Move the player based on the given direction
    switch (direction) {
        case 'w':
            if (player->playerY > 0 && matrix[player->playerY - 1][player->playerX] != 'W') {
                player->playerY--;
            }
            break;
        case 'a':
            if (player->playerX > 0 && matrix[player->playerY][player->playerX - 1] != 'W') {
                player->playerX--;
            }
            break;
        case 's':
            if (player->playerY < 10 && matrix[player->playerY + 1][player->playerX] != 'W') {
                player->playerY++;
            }
            break;
        case 'd':
            if (player->playerX < 10 && matrix[player->playerY][player->playerX + 1] != 'W') {
                player->playerX++;
            }
            break;
        default:
            // Handle invalid input
            break;
    }
}
