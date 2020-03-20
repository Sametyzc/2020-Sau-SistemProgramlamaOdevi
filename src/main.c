#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"

int main(int argc, char **argv)
{
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
