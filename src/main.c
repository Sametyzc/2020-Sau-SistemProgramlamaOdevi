#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Properties properties;
Dllist allPlayers;

int main(int argc, char **argv)
{
	start_game(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atof(argv[5]));
  /*
  Dllist itr;
  int i=0;
  dll_traverse(itr,allPlayers)
  {
    printf("%d-Name: %s\n", i,Get_Player_In_Node(itr)->Name);
    i++;
  }
  */
  exit(0);
}
