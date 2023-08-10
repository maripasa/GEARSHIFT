#include <stdlib.h>
#include <stdio.h>

void clrscr();
void shwscr(char matrix[11][11]);

struct playerSettings {
    int playerY;
    int playerX;
    char playerSkin;
};

int main() {

    struct playerSettings player;
    player.playerX = 5;
    player.playerY = 5;
    player.playerSkin = 'o';

    char matrix[11][11] = {
        {'+','=','=','=','=','=','=','=','=','=','+'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'|','-','-','-','-','-','-','-','-','-','|'},
        {'+','=','=','=','=','=','=','=','=','=','+'},
    };

    matrix[player.playerY][player.playerX] = player.playerSkin;

    shwscr(matrix);
    return 0;
}

void shwscr(char matrix[11][11]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            printf("%2c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void clrscr() {
    system("@cls||clear");
}