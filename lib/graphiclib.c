#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
void clearScreen()
{
    system("cls");
}
#else
void clearScreen()
{
    system("clear");
}
#endif

int borderWidth, borderHeight;

void matrixAnimation(char* stringData,unsigned int characterDelay, unsigned int textDelay)
{
    // Memastikan randomness akan berbeda setiap kali program dijalankan
	srand(time(NULL));
	char output[1024] = "";
	int len = strlen(stringData);
	int out_len = 0;

	for (int i = 0; i < len; i++)
    	{
		char realChar = stringData[i];
		for (int j = 0; j < 15; j++)
		{
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
}

// Fungsi battle UI
void battleUI(struct player, struct enemy, int borderHeight, borderWidth)
{
    char borderBuffer[borderWidth];
    for (int i = 0; i <= borderWidth; i++)
    {
        borderBuffer[i] = '=';
    }
    printf("%s\n", borderBuffer);
    
    printf("%s%s %sHP %d/%d\n", AC_RED, enemy.name, AC_NORMAL, enemy.health, enemy.maxHealth);

    drawHealth(enemy.health, enemy.maxHealth);
    
    printf("\n%s%s %sHP %d/%d\n", AC_RED, player.name, AC_NORMAL, player.health, player.maxHealth);
    
    printf("%s\n", borderBuffer)

    return;
}

void drawHealth(int health, int maxHealth)
{
    char* healthSymbol = '█';

    float entityHealthPercentage = (float)health / maxHealth * 100;
    int barLength = (int)entityHealthPercentage % 10;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= barLength; j++)
        {
            printf("%s%c", AC_GREEN, healthSymbol);
        }
        
        printf("%s%c", AC_RED, healthSymbol);
    }

    return;
}

void mainMenu(struct player)
{
    while(1)
    {
        int pilihan;
        clearScreen();
        printf("1. Random Battle\n2.Exit");
        scanf("%d", &pilihan);
        switch(pilihan)
        {
            case 1:
                randomBattle(player, 0);
                break;
            case 2:
                return;
        }
    }
}

void startBattle(struct player, struct enemy)
{
    
    if (enemy == NULL)
    {
        enemy = randomBattle();
    }
    
    battleUI(player, enemy);
    matrixAnimation("%s%s Menyerang!", AC_RED, enemy.name);

    while (1)
    {
        char pilihan;
        scanf("(A)ttack     (D)efense");
        switch (pilihan)
        {
            case 'A':
                battleAttack(&player, &enemy);
                break;
            case 'D':
                battleDefense();
                break;
            default:
                clearScreen();
                break;

        }
    }
}

struct battleAttack(struct *player, struct *enemy)
{
    srand(time(NULL));
    int playerDamage = player->baseDamage + player->weapon->damage;
    int enemyDamage = enemy->baseDamage + enemy->weapon->damage;

    bool isPlayerCrit = false;
    bool isEnemyCrit = false;
    int critPlayer = rand() % 100;
    int critEnemy = rand() % 100;
    if (critPlayer <= player->weapon->critRate * 100){isPlayerCrit = true;}
    if (critEnemy <= enemy->weapon->critRate * 100){isEnemyCrit = true;}
    if (isPlayerCrit)
    {
        playerDamage =  (int)((float)playerDamage * player->weapon->critDamage)
    }
    if (isEnemyCrit)
    {
        enemyDamage = (int)((float)playerDamage * player->weapon->critDamage);
    }
    bool isPlayerMove = false;
    // Siapa yang jalan duluan
    if (player->weapon->speed > enemy->weapon->speed){
        isPlayerMove = true;
    }

    if (isPlayerMove)
    {
        enemy->health = enemy->health - (playerDamage - enemy->defense);
        player->health = player->health - (enemyDamage - player->armor->baseDefense);
        if (player->health == 0) gameOver();
    } else
    {
        player->health = player->health - (enemyDamage - player->armor->baseDefense);
        if (player->health == 0) gameOver();
        enemy->health = enemy->health - (playerDamage - enemy->defense);
    }

}

struct battleEnd(struct player, struct enemy)
{
    int levelRequirement[100];
    int expNeeded = 150;
    for (int i = 0; i <= 100; i++)
    {
        levelRequirement[i] = 150 + 2**i;
    }
    srand(time(NULL));
    int expBonus = rand() % enemy.baseExpDrop;
    int totalExp = enemy.baseExpDrop + expBonus;

    int moneyBonus = rand() % enemy.baseMoneyDrop;
    int totalMoney = enemy.baseMoneyDrop + moneyBonus;

    player.exp += totalExp;
    player.money += totalMoney;

    for (int i = 0; i <= 100; i++)
    {
        if(player.exe >= levelRequirement[i])
        {
            player.level = i + 1;
        }
    }
    return player;
}

struct randomBattle()
{
    srand(time(NULL));

    int entityCount = sizeof(enemies)/sizeof(enemies[0]);

    int randomIndex = rand() % entityCount;

    struct entityData randomEnemy = enemies[randomIndex];

    return randomEnemy;
}
