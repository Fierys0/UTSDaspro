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

void MatrixAnimation(char* stringData,unsigned int characterDelay, unsigned int textDelay)
{
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
