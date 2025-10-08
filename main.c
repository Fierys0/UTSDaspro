#include "lib/graphiclib.c"
#include "weaponTable.c"
#include "enemyTable.c"
#include "playerData.c"
#include "armorTable.c"

// VARIABLE KRUSIAL
// JANGAN DIHAPUS ATAU VALUE = 0
int borderWidth = 50;
int borderHeight = 5;

int main()
{ 
    clearScreen();
    printf("======= Untitled RPG =======\n");
    char namaPlayer[20];
    while (1)
    {
        printf("Siapa namamu?\n> ");
        scanf("%19s", &namaPlayer);
        if (namaPlayer != 1) {break;}
        clearScreen();
    }
    strcpy(player.name, namaPlayer);

    mainMenu(player);

    clearScreen();

    return 0;
}
