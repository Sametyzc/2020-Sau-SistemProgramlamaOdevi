#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(int argc, char **argv)
{
	/*int i =0;
	for (i = 0; i != 0; i++)
	printf("%d\n", i);*/
	start_game(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atof(argv[5]));

  exit(0);
}
