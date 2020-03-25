#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"

Properties properties;
Dllist allPlayers;

int main(int argc, char **argv)
{
  create_properties(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atof(argv[5]));
  read_file();
 find_best_way();
  exit(0);
}
