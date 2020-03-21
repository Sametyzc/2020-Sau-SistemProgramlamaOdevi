#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"

Properties properties;
Dllist allPlayers;

int main(int argc, char **argv)
{
  allPlayers = new_dllist();

  properties = (struct input_struct*) malloc (1* sizeof(struct input_struct));
  properties->initial_range=2;
  properties->jump_range=1;
  properties->jump_count=0;

  Player Player1=create_player(0,0,100,200,"Samet",1);
  Player Player2=create_player(1,0,100,500,"Kubra",0);
  Player Player3=create_player(1,1,300,450,"Ahmet",0);
  Player Player4=create_player(3,1,123,452,"Kagan",0);

  dll_append(allPlayers, new_jval_v(Player1));
  dll_append(allPlayers, new_jval_v(Player2));
  dll_append(allPlayers, new_jval_v(Player3));
  dll_append(allPlayers, new_jval_v(Player4));

  printf("Player1 get_required_pp : %d\n",  get_required_pp(Player1));
  printf("Player2 get_required_pp : %d\n",  get_required_pp(Player2));
  printf("deger : %d\n", is_player_in_range(Player1,Player2));

  Dllist inRangeList = all_players_in_range(Player1);
  Dllist itr;

  printf("'%s' playerinin menzilindeki playerlar ->\n", Player1->Name );
  dll_traverse(itr,inRangeList) printf("-%s\n", Get_Player_In_Node(itr)->Name);
  free(inRangeList);

  printf("Okunan Dosya:\n");
  IS is;
  is = new_inputstruct(NULL);
  if (is == NULL) {
    perror("Dosya bulunamadı!");
    exit(1);
  }
  while (get_line(is)) {
    for(int i=0; i<is->NF; i++)
    {
      printf("%s ",is->fields[i]);
    }
    printf("\n");
  }
  exit(0);
}
