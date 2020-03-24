#include "oyun.h"


Properties properties;
Dllist allPlayers;



Dllist read_file()//Kubra
{
	
	allPlayers = new_dllist();
	IS is;
	is = new_inputstruct(NULL);
  if (is == NULL) 
	{
    perror("hata!");
    exit(1);
  }
	while(get_line(is) > 0) 
  {
		Player new_player;
		if(strcmp(is->fields[4],"Lokman_Hekim"))
	{
		new_player=create_player(atoi(is->fields[0]),atoi(is->fields[1]),atoi(is->fields[2]),atoi(is->fields[3]),is->fields[4],0);
	
	}
	else
	{
		new_player=create_player(atoi(is->fields[0]),atoi(is->fields[1]),atoi(is->fields[2]),atoi(is->fields[3]),is->fields[4],1);
	
	}
	  dll_append(allPlayers, new_jval_v(new_player));
	}
	return allPlayers;
}

Properties create_properties(int initialRange,int jumpRange,int numJumps,int initialPower,double powerReduction)//Kubra
{
	properties = (struct input_struct*) malloc (1* sizeof(struct input_struct));
  properties->initial_range=initialRange;
  properties->jump_range=jumpRange;
	properties->num_jumps=numJumps;
  properties->initial_power=initialPower;
	properties->power_reduction=powerReduction;
	properties->current_power=initialPower;
	properties->jump_count=0;
	printf("initial range : %d \n",properties->initial_range);
printf("jump_range : %d \n",properties->jump_range);
printf("num_jumps : %d \n",properties->num_jumps);
printf("initial_power : %d \n",properties->initial_power);
printf("power_reduction : %lf \n",properties->power_reduction);
	return properties;
}

Player create_player(int coordinate_x,int coordinate_y,int current_pp,int max_pp,char* name,int turn)//Samet
{
	Player new_player;
  new_player = Malloc_Player();
  new_player->Coordinate_X = coordinate_x;
  new_player->Coordinate_Y =coordinate_y;
  new_player->Current_PP = current_pp;
  new_player->Max_PP = max_pp;
  new_player->Name = strdup(name);
  new_player->Turn = turn;
  return new_player;
}

int get_required_pp(Player player)//Samet
{
  return ((player->Max_PP)-(player->Current_PP));
}

int is_player_in_range(Player p_reference,Player p_target)//Samet
{
  int coordinate_x = abs(p_reference->Coordinate_X-p_target->Coordinate_X);
  int coordinate_y = abs(p_reference->Coordinate_Y-p_target->Coordinate_Y);
  double distance = sqrt(pow((double)coordinate_x,(double)2)+pow((double)coordinate_y,(double)2));
  if(properties->jump_count==0)
  {
    if(distance <= properties->initial_range)
    {
      return 1;
    }
    return 0;
  }
  else
  {
    if(distance <= properties->jump_range)
    {
      return 1;
    }
    return 0;
  }
}

Dllist all_players_in_range(Player p_reference)//Samet
{
  Dllist itr;
  Dllist playersList = new_dllist();
  dll_traverse(itr, allPlayers)
  {
    Player itr_player = Get_Player_In_Node(itr);
    if(is_player_in_range(p_reference,itr_player)==1)
    {
      if(strcmp(p_reference->Name, itr_player->Name) !=0)
      {
        dll_append(playersList,itr->val);
      }
    }
  }
  //Donus degeri new ile olusturuldugu icin cagirildigi yerde free ile serbest birakilmali
  return playersList;
}

void heal_player(Player player)//Yoruk
{

}

void update_power()//Yoruk
{

}

void update_totalHealing(int value)//Yoruk
{

}

void free_player(Player player)//Alperen
{

}

void free_allPlayers()//Alperen
{

}

void free_properties()//Alperen
{

}

void free_oyun()//Alperen
{

}
