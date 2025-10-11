#include "enemyTable.c"
#include "playerData.c"
#include "armorTable.c"
#include "weaponTable.c"
#include "lib/graphiclib.c"

void battleAttack(struct Player* player, struct entityData* enemy) {
    srand(time(NULL));

    int playerDamage = player->baseDamage + player->weapon.damage;
    int enemyDamage = enemy->baseDamage + enemy->weapon.damage;

    bool isPlayerCrit = ((float)rand() / RAND_MAX) < player->weapon.critRate;
    bool isEnemyCrit = ((float)rand() / RAND_MAX) < enemy->weapon.critRate;

    if (isPlayerCrit)
        playerDamage = (int)(playerDamage * player->weapon.critDamage);
    if (isEnemyCrit)
        enemyDamage = (int)(enemyDamage * enemy->weapon.critDamage);

    bool playerFirst = player->weapon.speed >= enemy->weapon.speed;

    if (playerFirst) {
        enemy->health -= (playerDamage - enemy->defense);
        if (enemy->health < 0) enemy->health = 0;
        if (enemy->health == 0) {
            printf("%s defeated!\n", enemy->name);
            battleEnd(player, enemy);
            return;
        }

        player->health -= (enemyDamage - player->armor.baseDefense);
        if (player->health < 0) player->health = 0;
        if (player->health == 0) gameOver();
    } else {
        player->health -= (enemyDamage - player->armor.baseDefense);
        if (player->health < 0) player->health = 0;
        if (player->health == 0) gameOver();

        enemy->health -= (playerDamage - enemy->defense);
        if (enemy->health < 0) enemy->health = 0;
        if (enemy->health == 0) {
            printf("%s defeated!\n", enemy->name);
            battleEnd(player, enemy);
        }
    }
}

void battleEnd(struct Player* player, struct entityData* enemy) {
    srand(time(NULL));

    int expGain = enemy->baseExpDrop + rand() % enemy->baseExpDrop;
    int moneyGain = enemy->baseMoneyDrop + rand() % enemy->baseMoneyDrop;

    player->exp += expGain;
    player->money += moneyGain;

    printf("%s defeated %s!\n", player->name, enemy->name);
    printf("Gained %d EXP and %d Money!\n", expGain, moneyGain);
}

struct entityData randomBattle() {
    extern struct entityData enemies[]; // defined elsewhere
    srand(time(NULL));

    int entityCount = sizeof(enemies) / sizeof(enemies[0]);
    int randomIndex = rand() % entityCount;

    return enemies[randomIndex];
}

void startBattle(struct Player player, struct entityData enemy) {
    if (enemy.name == NULL) {
        enemy = randomBattle();
    }

    while (player.health > 0 && enemy.health > 0) {
        clearScreen();
        battleUI(player, enemy);

        printf("\n(A)ttack or (D)efend: ");
        char choice;
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a':
                battleAttack(&player, &enemy);
                break;
            case 'D':
            case 'd':
                printf("%s defends!\n", player.name);
                break;
            default:
                printf("Invalid choice!\n");
        }
        sleep(1);
    }
}
