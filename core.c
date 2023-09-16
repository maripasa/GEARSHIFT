#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define CENTER_Y 5
#define CENTER_X 5
#define MATRIX_HEIGHT 12
#define MATRIX_WIDTH 12
#define INPUT_SIZE 10

// Struct mobSettings
struct mobSettings;
struct Item;
struct Inventory;

// Introduction Functions
void bootIntroduction();
void introduction();

// Input Functions
char takeInput(const char *question, char *command, char *argument, int bufferSize);
void takeCommand(struct mobSettings *player);
void handleCommand(struct mobSettings *player, char matrix[MATRIX_HEIGHT][MATRIX_WIDTH], char command);

// Map Functions
void buildMap(char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]);
int  isPassable(char character);
void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]);

// Console functions
void showScreen(char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]);
void clearScreen();
void crossSleep(int milliseconds);

// Player inventory
void initializeInventory(struct Inventory* inventory, int capacity);
void freeInventory(struct Inventory* inventory);
void displayInventory(const struct Inventory* inventory);
void addItem(struct Inventory* inventory, const char* name, int quantity);

struct Inventory {
    struct Item* items;
    int capacity;
    int size;
};
struct Item {
    char name[50];
    int quantity;
};


// Global Mob Struct
struct mobSettings {
    int playerY;
    int playerX;
    char playerSkin;
    int playerRoom;
};


int main() {

    // Configura o código de página do console para UTF-8
    system("chcp 65001");
    clearScreen();

    // Create and initialize the player's inventory
    struct Inventory playerInventory;
    initializeInventory(&playerInventory, 10);

    // Initialize player settings
    struct mobSettings player;
    player.playerX = CENTER_X;
    player.playerY = CENTER_Y;
    player.playerSkin = 'O';

    /* Add items to the inventory
    addItem(&playerInventory, "Health Potion", 5);
    addItem(&playerInventory, "Sword", 1);
    addItem(&playerInventory, "Gold Coin", 100);
    
    // Display the inventory
    displayInventory(&playerInventory);
    */

    // Display boot introduction and wait for input
    bootIntroduction();

    takeCommand(&player);

    freeInventory(&playerInventory);

    return 0;
}

void bootIntroduction() {
    printf(" | Está pronto? [S/N]\n");
    printf(" | \"Dica: <skip> para pular a introdução.\"\n");
    printf(" └─> ");
    char charInput[INPUT_SIZE];
    scanf("%s", charInput);
    if (strcmp(charInput, "skip") != 0) {
        introduction();
    }
}

void introduction() {
    clearScreen();
    printf("No ir do tempo, desperta um autômato de mistério e potencial.\n");
    crossSleep(4000);
    printf("O golem metálico emerge do sono, um guardião perdido nas areias do esquecimento.\n");
    crossSleep(3000);
    printf("Sob um céu límpido e sereno,\n");
    crossSleep(3000);
    printf("Um mundo de maravilhas e enigmas é contemplado,\n");
    crossSleep(3000);
    printf("Montes flutuam em harmonia,\n");
    crossSleep(3000);
    printf("Antigas ruínas são abraçadas pela vegetação exuberante.\n\n");
    crossSleep(5000);
    printf("    ██████╗ ███████╗ █████╗ ██████╗ ███████╗██╗  ██╗██╗███████╗████████╗\n");
    crossSleep(1000);
    printf("   ██╔════╝ ██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║██║██╔════╝╚══██╔══╝\n");
    crossSleep(1000);
    printf("   ██║  ███╗█████╗  ███████║██████╔╝███████╗███████║██║█████╗     ██║\n");
    crossSleep(1000);
    printf("   ██║   ██║██╔══╝  ██╔══██║██╔══██╗╚════██║██╔══██║██║██╔══╝     ██║\n");
    crossSleep(1000);
    printf("   ╚██████╔╝███████╗██║  ██║██║  ██║███████║██║  ██║██║██║        ██║\n");
    crossSleep(1000);
    printf("    ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝        ╚═╝ \n\n");
    crossSleep(3000);
}

char takeInput(const char *question, char *command, char *argument, int bufferSize) {
    printf(" │ %s\n", question);
    printf(" └─> ");
    char userInput[INPUT_SIZE];
    fgets(userInput, sizeof(userInput), stdin);

    if (strlen(userInput) < 1) {
        return '\0'; // Empty input
    }

    char input = userInput[0];

    if (strlen(userInput) > 1) {
        // Parse command and argument
        sscanf(userInput, "%s %s", command, argument);
    } else {
        // Reset command and argument
        command[0] = '\0';
        argument[0] = '\0';
    }

    return input;
}

void takeCommand(struct mobSettings *player) {
    while (1) {
        char matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
        buildMap(matrix);
        matrix[player->playerY][player->playerX] = player->playerSkin;
        showScreen(matrix);

        char userCommand[INPUT_SIZE]; // Buffer to store the user's command
        char userArgument[INPUT_SIZE]; // Buffer to store the user's argument

        char input;
        do {
            input = takeInput("What next? (w/a/s/d/q): ", userCommand, userArgument, INPUT_SIZE);
            if (input == 'q') {
                // Handle the exit command
                exit(0); // Gracefully exit the program
            }
        } while (input != 'w' && input != 'a' && input != 's' && input != 'd');

        // Check for user input and perform actions
        handleCommand(player, matrix, input);
    }
}

void handleCommand(struct mobSettings *player, char matrix[MATRIX_HEIGHT][MATRIX_WIDTH], char command) {
    // Handle different commands here
    switch (command) {
        case 'w':
        case 'a':
        case 's':
        case 'd':
            handlePlayerMovement(player, command, matrix);
            break;
        case 'q':
            exit(0); // Exit the program gracefully
            break;
        // Add more command cases here
        default:
            // Handle unsupported commands
            break;
    }
}

void buildMap(char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]) {
    
    clearScreen();
	
    char initialMatrix[MATRIX_HEIGHT][MATRIX_WIDTH] = {
    {'W', 'W', 'W', 'W', 'O', 'W', 'W', 'W', 'W', 'W', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'O', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', '~', '~', '~', '~', '~', '~', '~', '~', '~', 'W', ' '},
    {'W', 'W', 'W', 'W', 'O', 'W', 'W', 'W', 'W', 'W', 'W', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'}
    };
        
    // Copy initial map layout to the game matrix
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            matrix[i][j] = initialMatrix[i][j];
        }
    }
}

int isPassable(char character) {
    // Add conditions for different characters here
    // For now, only 'W' (wall) is considered impassable
    return character != 'W';
}

void handlePlayerMovement(struct mobSettings *player, char direction, char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]) {
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
    if (isPassable(matrix[newPlayerY][newPlayerX])) {
        // Update the player's position
        player->playerX = newPlayerX;
        player->playerY = newPlayerY;
    }
}

void showScreen(char matrix[MATRIX_HEIGHT][MATRIX_WIDTH]) {
    // Display each cell of the game matrix
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            printf("%2c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void clearScreen() {
    #ifdef _WIN32
    system("cls"); // Windows
    #else
    system("clear"); // Linux
    #endif
}

void crossSleep(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds); // Windows
#else
    usleep(milliseconds * 1000); // Linux
#endif
}

void initializeInventory(struct Inventory* inventory, int capacity) {
    inventory->items = (struct Item*)malloc(sizeof(struct Item) * capacity);
    inventory->capacity = capacity;
    inventory->size = 0;
}

void addItem(struct Inventory* inventory, const char* name, int quantity) {
    if (inventory->size < inventory->capacity) {
        strcpy(inventory->items[inventory->size].name, name);
        inventory->items[inventory->size].quantity = quantity;
        inventory->size++;
    } else {
        printf("Inventory is full.\n");
    }
}

void displayInventory(const struct Inventory* inventory) {
    printf("Inventory Contents:\n");
    for (int i = 0; i < inventory->size; i++) {
        printf("%s x%d\n", inventory->items[i].name, inventory->items[i].quantity);
    }
}

void freeInventory(struct Inventory* inventory) {
    free(inventory->items);
    inventory->items = NULL;
    inventory->capacity = 0;
    inventory->size = 0;
}