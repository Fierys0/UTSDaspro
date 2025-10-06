#include "lib/graphiclib.c"

int borderWidth = 50;
int borderHeight = 5;

int main()
{ 
    char* ui = battleUI("Player", "Goblin", 10, 15, 20, 30);
    if (ui) {
        printf("%s", ui);
        free(ui);
    }
}
