#include "lib/graphiclib.c"
#include "entity.c"

// VARIABLE KRUSIAL
// JANGAN DIHAPUS ATAU VALUE = 0
int borderWidth = 50;
int borderHeight = 5;

int main()
{ 
    char* ui = battleUI("Player", "Goblin", 10, 15, 20, 30);
    if (ui) {
        printf("%s", ui);
        free(ui);
    }

    printf("%s", AC_RED);
    MatrixAnimation("Goblin Menyerang Anda", 10000, 10000);

    clearScreen();
}
