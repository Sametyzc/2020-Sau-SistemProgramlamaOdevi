#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"


int main(int argc, char **argv)
{
  Properties properties = (struct input_struct*) malloc (1* sizeof(struct input_struct));
  properties->initial_range=2;
  properties->jump_range=1;
  properties->jump_count=0;
  Player Player1=create_player(0,0,100,200,"Player1",0);
  Player Player2=create_player(1,0,100,500,"Player2",0);
  printf("Player1 get_required_pp : %d\n",  get_required_pp(Player1));
  printf("Player2 get_required_pp : %d\n",  get_required_pp(Player2));
  is_player_in_range(Player1,Player2);

  IS is;
  is = new_inputstruct(NULL);
  if (is == NULL) {
    perror("Dosya bulunamadı!");
    exit(1);
  }
  while (get_line(is)) {
    for(int i=0;i<is->NF;i++)
    {
      printf("%s ",is->fields[i]);
    }
    printf("\n");
  }
  exit(0);
}
