#include "game/core.c"

// VARIABLE KRUSIAL
// JANGAN DIHAPUS ATAU VALUE = 0
int main()
{ 
    initPlayer();
    initEnemies();
    clearScreen();
//    printf("======= Untitled RPG =======\n");
//    char namaPlayer[20];
//    while (1)
//    {
//        printf("Siapa namamu?\n> ");
//        scanf("%19s", &namaPlayer);
//        if (namaPlayer != '\0') {break;}
//        clearScreen();
//    }
//    strcpy(player.name, namaPlayer);

    mainMenu(player);

    clearScreen();

    return 0;
}
