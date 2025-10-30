#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "armorTable.c"
#include "weaponTable.c"
#include "enemyTable.c"
#include "playerData.c"

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

#ifdef _WIN32
void clearScreen() { system("cls"); }
#else
void clearScreen() { system("clear"); }
#endif

int borderWidth = 40;
int borderHeight = 5;

// ---------- Function Declarations ----------
void matrixAnimation(const char* stringData, unsigned int characterDelay, unsigned int textDelay);
void drawHealth(int health, int maxHealth);
void battleUI(struct Player player, struct entityData enemy);
struct Player startBattle(struct Player player, struct entityData enemy);
void battleAttack(struct Player* player, struct entityData* enemy);
struct entityData randomBattle();
void battleEnd(struct Player* player, struct entityData* enemy);
void mainMenu(struct Player player);
void gameOver();


void matrixAnimation(const char* stringData, unsigned int characterDelay, unsigned int textDelay) {
    srand(time(NULL));
    char output[1024] = "";
    int len = strlen(stringData);
    int out_len = 0;

    for (int i = 0; i < len; i++) {
        char realChar = stringData[i];
        for (int j = 0; j < 15; j++) {
            char randChar = (char)((rand() % 94) + 33);
            printf("\r%s%c", output, randChar);
            fflush(stdout);
            usleep(characterDelay);
        }

        output[out_len++] = realChar;
        output[out_len] = '\0';
        printf("\r%s", output);
        fflush(stdout);
        usleep(textDelay);
    }
    printf("\n");
}

void drawHealth(int health, int maxHealth) {
    const char *healthSymbol = "\xE2\x96\x88"; //'█'
    float healthPercent = (float)health / maxHealth;
    int filledBars = (int)(healthPercent * 10);

    printf("[");
    for (int i = 0; i < 10; i++) {
        if (i < filledBars)
            printf("%s%c", AC_GREEN, healthSymbol);
        else
            printf("%s%c", AC_RED, healthSymbol);
    }
    printf("%s]", AC_NORMAL);
}

void battleUI(struct Player player, struct entityData enemy) {
    for (int i = 0; i < borderWidth; i++) printf("=");
    printf("\n");

    printf("%s%s%s HP: %d/%d\n", AC_RED, enemy.name, AC_NORMAL, enemy.health, enemy.maxHealth);
    drawHealth(enemy.health, enemy.maxHealth);

    printf("\n\n%s%s%s HP: %d/%d\n", AC_CYAN, player.name, AC_NORMAL, player.health, player.maxHealth);
    drawHealth(player.health, player.maxHealth);

    printf("\n");
    for (int i = 0; i < borderWidth; i++) printf("=");
    printf("\n");
}

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

    char message[256];

    if (playerFirst) {
        int dealt = playerDamage - enemy->defense;
        if (dealt < 0) dealt = 0;

        enemy->health -= dealt;
        if (enemy->health < 0) enemy->health = 0;

        snprintf(message, sizeof(message),
                 "%s attacked %s for %d damage!", player->name, enemy->name, dealt);
        matrixAnimation(message, 5000, 20000);

        if (enemy->health == 0) {
            printf("%s defeated!\n", enemy->name);
            battleEnd(player, enemy);
            return;
        }

        // Enemy retaliates
        int taken = enemyDamage - player->armor.baseDefense;
        if (taken < 0) taken = 0;

        player->health -= taken;
        if (player->health < 0) player->health = 0;

        snprintf(message, sizeof(message),
                 "%s attacked %s for %d damage!", enemy->name, player->name, taken);
        matrixAnimation(message, 5000, 20000);

        if (player->health == 0) gameOver();
    } else {
        // Enemy attacks first
        int taken = enemyDamage - player->armor.baseDefense;
        if (taken < 0) taken = 0;

        player->health -= taken;
        if (player->health < 0) player->health = 0;

        snprintf(message, sizeof(message),
                 "%s attacked %s for %d damage!", enemy->name, player->name, taken);
        matrixAnimation(message, 5000, 20000);

        if (player->health == 0) gameOver();

        int dealt = playerDamage - enemy->defense;
        if (dealt < 0) dealt = 0;

        enemy->health -= dealt;
        if (enemy->health < 0) enemy->health = 0;

        snprintf(message, sizeof(message),
                 "%s attacked %s for %d damage!", player->name, enemy->name, dealt);
        matrixAnimation(message, 5000, 20000);

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
    extern struct entityData enemies[];
    srand(time(NULL));

    int randomIndex = rand() % 2;

    return enemies[randomIndex];
}

struct Player startBattle(struct Player player, struct entityData enemy) {
    if (enemy.name == NULL) {
        enemy = randomBattle();
    }

    while (player.health > 0 && enemy.health > 0) {
        clearScreen();
        battleUI(player, enemy);

        printf("\n(A)ttack, (D)efend, or (R)un: ");
        char choice;
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a':
                battleAttack(&player, &enemy);
                break;

            case 'D':
            case 'd': {
                char msg[128];
                snprintf(msg, sizeof(msg),
                         "%s braces for impact! Defense increased!", player.name);
                matrixAnimation(msg, 500, 200);

                int originalDefense = player.armor.baseDefense;
                player.armor.baseDefense *= 2; // temporary buff

                int enemyDamage = enemy.baseDamage + enemy.weapon.damage;
                int taken = enemyDamage - player.armor.baseDefense;
                if (taken < 0) taken = 0;
                player.health -= taken;
                if (player.health < 0) player.health = 0;

                snprintf(msg, sizeof(msg),
                         "%s attacked %s for %d reduced damage!",
                         enemy.name, player.name, taken);
                matrixAnimation(msg, 500, 200);

                player.armor.baseDefense = originalDefense; // revert buff

                if (player.health == 0) gameOver();
                break;
            }

            case 'R':
            case 'r': {
                int escapeChance = rand() % 100;
                if (escapeChance < 50) {
                    char msg[128];
                    snprintf(msg, sizeof(msg), "%s successfully ran away!", player.name);
                    matrixAnimation(msg, 500, 200);
                    sleep(1);
                    return player;
                } else {
                    char msg[128];
                    snprintf(msg, sizeof(msg),
                             "%s failed to run! %s attacks!", player.name, enemy.name);
                    matrixAnimation(msg, 500, 200);

                    int enemyDamage = enemy.baseDamage + enemy.weapon.damage;
                    int taken = enemyDamage - player.armor.baseDefense;
                    if (taken < 0) taken = 0;
                    player.health -= taken;
                    if (player.health < 0) player.health = 0;

                    snprintf(msg, sizeof(msg),
                             "%s attacked %s for %d damage!",
                             enemy.name, player.name, taken);
                    matrixAnimation(msg, 500, 200);

                    if (player.health == 0) gameOver();
                }
                break;
            }

            default:
                printf("Invalid choice!\n");
                sleep(1);
                break;
        }

        sleep(1);
    }

    if (player.health > 0)
        battleEnd(&player, &enemy);
    else
        gameOver();

    return player;
}

void mainMenu(struct Player player) {
    while (1) {
        int pilihan;
        clearScreen();
        printf("==== MAIN MENU ====\n");
        printf("1. Random Battle\n2. Exit\n");
        printf("Choose: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                struct entityData enemy = randomBattle();
                player = startBattle(player, enemy);
                break;
            }
            case 2:
                return;
            default:
                printf("Invalid input!\n");
                break;
        }
    }
    
}

void gameOver() {
    printf("\n%sGAME OVER!%s\n", AC_RED, AC_NORMAL);
    exit(0);
}

