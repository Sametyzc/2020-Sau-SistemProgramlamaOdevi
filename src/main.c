#include <stdio.h>
#include <stdlib.h>
#include "oyun.h"


int main(int argc, char **argv)
{
  Dllist liste = new_dllist();
  dll_append(liste,Create_Player_As_Jval());
  Get_Player_In_Node(dll_first(liste))->Max_PP=100;
  printf("max_pp : %d\n",  Get_Player_In_Node(dll_first(liste))->Max_PP);
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
