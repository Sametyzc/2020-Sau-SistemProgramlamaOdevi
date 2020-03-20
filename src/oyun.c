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
  
}

Dllist all_players_in_range(Player p_reference)//Samet
{

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
