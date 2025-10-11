#include "entity.h"
#include "weaponTable.c"   // contains extern struct weaponData weapon[];

struct entityData enemies[2];  // Declare but don’t initialize weapons yet

void initEnemies(void) {
    enemies[0] = (struct entityData){
        "Slime", 20, 20,
        weapon[0],  // ✅ assign at runtime
        1, 1, 4, 3, 2,
        1.0f, 1.0f,
        {0,0,0,0}
    };

    enemies[1] = (struct entityData){
        "Goblin", 50, 50,
        weapon[2],
        2, 3, 10, 8, 5,
        1.2f, 1.2f,
        {0,0,0,0}
    };
}
