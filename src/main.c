#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"

Properties properties;
Dllist allPlayers;

int main(int argc, char **argv)
{
  create_properties(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atof(argv[5]));
  Dllist itr;
  read_file();
  dll_traverse(itr,allPlayers)
  {
   printf("-%s\n", Get_Player_In_Node(itr)->Name);
   printf("%d\n", Get_Player_In_Node(itr)->Turn);
   printf("%d\n", Get_Player_In_Node(itr)->Coordinate_X);
   printf("%d\n", Get_Player_In_Node(itr)->Coordinate_Y);
   printf("%d\n", Get_Player_In_Node(itr)->Current_PP);
   printf("%d\n \n", Get_Player_In_Node(itr)->Max_PP);
  }
  exit(0);
}
