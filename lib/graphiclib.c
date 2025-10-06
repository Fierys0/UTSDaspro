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

void MatrixAnimation(char* stringData,unsigned int characterDelay, unsigned int textDelay)
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

char* createBorder() {
    // init buffer string yang akan digunakan dengan menggunakan data panjang dan lebar yang sudah diberikan 
    int bufferSize = (borderWidth + 1) * borderHeight + 1;
    char* borderString = malloc(bufferSize);

    // Mengecek agar borderString tidak kosong, jika kosong maka return null atau keluar function
    if (!borderString) return NULL;

    //initialize variabel k yang akan di gunakan dalam loop nanti
    int k = 0;

    // meloop data sesuai dengan panjang dari border
    for (int i = 0; i < borderHeight; i++) 
    {
        for (int j = 0; j < borderWidth; j++) 
        {
            // Mengecek jika posisi panjang ada di paling atas atau paling bawah
            if (i == 0 || i == borderHeight - 1 || j == 0 || j == borderWidth - 1) 
            {
                borderString[k++] = '#';
            } else {
                borderString[k++] = ' ';
            }
        }
        borderString[k++] = '\n';
    }

    // memastikan bahwa akhir string adalah null
    borderString[k] = '\0';
    return borderString;
}

void putBar(int row, const char* name, int hp, int maxHP, char* ui, int barWidth) {
    char line[256];
    int filled = (hp * barWidth) / maxHP;
    if (filled > barWidth) filled = barWidth;

    // Membuat hp bar dengan format "[======  ]"
    int len = sprintf(line, "<%s HP %d/%d [", name, hp, maxHP);

    for (int b = 0; b < barWidth; b++) {
        line[len++] = (b < filled) ? '=' : ' ';
    }
    line[len++] = ']';
    line[len++] = '>';
    line[len] = '\0';

    // Menghitung offset antara hp bar dan border
    int offset = row * (borderWidth + 1) + 1;

    int maxLen = borderWidth - 2;
    if ((int)strlen(line) > maxLen) {
        line[maxLen] = '\0';
    }

    strncpy(&ui[offset], line, strlen(line));
}

// Fungsi battle UI
char* battleUI(const char* playerName, const char* enemyName, int enemyHP, int playerHP, int enemyMaxHP, int playerMaxHP)
{
    // Membuat ruang untuk tanda "<" dan ">" nanti
    int barWidth = borderWidth - 22;
    if (barWidth < 10) barWidth = 10;

    // allocate buffer untuk kotaknya
    int bufferSize = (borderWidth + 1) * borderHeight + 1;
    char* ui = malloc(bufferSize);
    if (!ui) return NULL;

    int k = 0;
    for (int i = 0; i < borderHeight; i++) {
        for (int j = 0; j < borderWidth; j++) {
            if (i == 0 || i == borderHeight - 1 || j == 0 || j == borderWidth - 1) {
                ui[k++] = '#';
            } else {
                ui[k++] = ' ';
            }
        }
        ui[k++] = '\n';
    }
    ui[k] = '\0';

    // Memasukan hpbar musuh di paling atas
    putBar(1, enemyName, enemyHP, enemyMaxHP, ui, barWidth);

    // Memasukan hpbar player di paling bawah
    putBar(borderHeight - 2, playerName, playerHP, playerMaxHP, ui, barWidth);

    return ui;
}
