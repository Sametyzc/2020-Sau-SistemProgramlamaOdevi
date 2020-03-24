#include "oyun.h"


Properties properties;
Dllist allPlayers;

Dllist read_file(IS inputstruct)//Kubra
{

}

void set_properties(Properties properties)//Kubra
{

}

Properties create_properties(int initialRange,int jumpRange,int numJumps,int initialPower,int powerReduction)//Kubra
{

}

void set_allPlayers()//Kubra
{

}

Player create_player(int coordinate_x,int coordinate_y,int current_pp,int max_pp,char* name,int turn)//Samet
{
  Player new_player = Malloc_Player();
  new_player->Coordinate_X = coordinate_x;
  new_player->Coordinate_Y =coordinate_y;
  new_player->Current_PP = current_pp;
  new_player->Max_PP = max_pp;
  new_player->Name = name;
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
