#include "game.h"

Properties properties;
Dllist allPlayers;
Dllist allChildlessTreeNodes;

Dllist read_file()
{
	allPlayers = new_dllist();
	IS is;
	is = new_inputstruct(NULL);
	if (is == NULL)
	{
		perror("Dosya okunurken hata olustu!");
		exit(1);
	}
	while (get_line(is) > 0)
	{
		Player new_player;
		new_player = create_player(atoi(is->fields[0]), atoi(is->fields[1]), atoi(is->fields[2]), atoi(is->fields[3]), is->fields[4]);
		dll_append(allPlayers, new_jval_v(new_player));
	}
//jettison_inputstruct(is);
	return allPlayers;
}

Properties create_properties(int initialRange, int jumpRange, int numJumps, int initialPower, double powerReduction)
{
	properties = (struct input_struct *) malloc(1* sizeof(struct input_struct));
	properties->initial_range = initialRange;
	properties->jump_range = jumpRange;
	properties->num_jumps = numJumps;
	properties->initial_power = initialPower;
	properties->power_reduction = powerReduction;
	properties->current_power = initialPower;
	properties->jump_count = 0;
	return properties;
}

Player create_player(int coordinate_x, int coordinate_y, int current_pp, int max_pp, char *name)
{
	Player new_player;
	new_player = Malloc_Player();
	new_player->Coordinate_X = coordinate_x;
	new_player->Coordinate_Y = coordinate_y;
	new_player->Current_PP = current_pp;
	new_player->Max_PP = max_pp;
	new_player->Name = strdup(name);
	return new_player;
}

int get_required_pp(Player player)
{
	return ((player->Max_PP) - (player->Current_PP));
}

int is_player_in_range(Player p_reference, Player p_target)
{
	int coordinate_x = abs(p_reference->Coordinate_X - p_target->Coordinate_X);
	int coordinate_y = abs(p_reference->Coordinate_Y - p_target->Coordinate_Y);
	double distance = sqrt(pow((double) coordinate_x, (double) 2) + pow((double) coordinate_y, (double) 2));
	if (properties->jump_count == 0)
	{
		if (distance <= properties->initial_range)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		if (distance <= properties->jump_range)
		{
			return 1;
		}
		return 0;
	}
}

Dllist all_players_in_range(Player p_reference)
{
	Dllist itr;
	Dllist playersList = new_dllist();
	dll_traverse(itr, allPlayers)
	{
		Player itr_player = Get_Player_In_Node(itr);
		if (is_player_in_range(p_reference, itr_player) == 1)
		{
			if (strcmp(p_reference->Name, itr_player->Name) != 0)
			{
				dll_append(playersList, itr->val);
			}
		}
	}
	//Donus degeri new ile olusturuldugu icin cagirildigi yerde free ile serbest birakilmali
	return playersList;
}

Dllist get_jumpable_players(Tree Node)
{
	Tree itr_tree;
	Dllist itr_list;
	Dllist rangeList = all_players_in_range(Node->Player);
	Dllist playersList = new_dllist();
	int i, isParent;
	dll_traverse(itr_list, rangeList)
	{
		Player itr_player = Get_Player_In_Node(itr_list);
		i = 0;
		isParent = 0;
		tree_scan_to_head(itr_tree, Node)
		{
			if (strcmp((itr_tree->Player)->Name, itr_player->Name) == 0)
			{
				isParent = 1;
				break;
			}
			i++;
		}
		if (isParent == 0)
		{
			dll_append(playersList, itr_list->val);
		}
	}
	free_dllist(rangeList);
	//Donus degeri new ile olusturuldugu icin cagirildigi yerde free ile serbest birakilmali
	return playersList;
}

int get_node_count_in_list(Dllist list)
{
	if (list->flink == list)
	{
		return 0;
	}
	int nodeCount = 0;
	Dllist itr;
	dll_traverse(itr, list)
	{
		nodeCount++;
	}
	return nodeCount;
}

/**/
double healvalue = 0;
double totalheal = 0;
double temp = 0;
/**/

void find_best_way()
{
	Tree node_tree;
	Dllist ptr;
	Tree ptr2;
	int waycounter = 1, counter = 1;
	int wayheal = 0;

	healvalue = properties->current_power;
	dll_traverse(ptr, allChildlessTreeNodes)
	{

		node_tree = Get_Tree_In_Node(ptr);

		tree_scan_to_head2(ptr2, node_tree)
		{

			Simulate(ptr2->Player, ptr2->Level - 1);
		}
		if (totalheal > wayheal)
		{
			wayheal = totalheal;

			waycounter = counter;
		}

		totalheal = 0;
		counter++;
	}
	printf("\nEn iyi yol :%d. yol\n", waycounter);
	printf("\nEn iyi yol iyileştirmesi :%d\n", wayheal);
	ptr = allChildlessTreeNodes->flink;
	for (int j = 1; j < waycounter; j++)
	ptr = ptr->flink;
	node_tree = Get_Tree_In_Node(ptr);
	tree_scan_to_head2(ptr2, node_tree)
	{
		printf("\n%s  ", ptr2->Player->Name);
		Heal(ptr2->Player, ptr2->Level - 1);
	}
}

void Simulate(Player player, int count)
{

	if (count == 0)
	healvalue = properties->initial_power;
	else
	{
		healvalue = (properties->initial_power) *pow(1 - properties->power_reduction, count);
		healvalue = rint(healvalue);
	}

	if (get_required_pp(player) != 0 && get_required_pp(player) < healvalue)
	{

		totalheal += get_required_pp(player);
	}
	else if (get_required_pp(player) != 0)
	{

		totalheal += healvalue;
	}
}

void Heal(Player player, int count)
{
	if (count == 0)
	healvalue = properties->initial_power;
	else
	{
		healvalue = (properties->initial_power) *pow(1 - properties->power_reduction, count);
		healvalue = rint(healvalue);
	}

	if (get_required_pp(player) != 0 && get_required_pp(player) < healvalue)
	{
		printf("%f\n", rint(get_required_pp(player)));
		totalheal += get_required_pp(player);
		player->Current_PP = player->Max_PP;
	}
	else if (get_required_pp(player) != 0)
	{

		printf(" %f\n", rint(healvalue));
		totalheal += healvalue;
		player->Current_PP += healvalue;
	}
	else printf(" %d\n", 0);

}

/*      		Tree             */

void create_tree()
{
	Dllist rangeList = all_players_in_range(Get_Player_In_Node(dll_first(allPlayers)));
	allChildlessTreeNodes = new_dllist();

	Tree head;
	head = Malloc_Tree(1);
	head->Parent = NULL;
	head->Player = NULL;
	head->Level = 0;
	head->Child_Count = get_node_count_in_list(rangeList) + 1;

	//Buradaki +1 lokman hekim cunku onun rangeindekileri getiriyoruz listede lokman yok.
	head->Child_Nodes = Malloc_Tree(head->Child_Count);

	int i = 1;
	Dllist itr;
	((head->Child_Nodes))->Level = 1;
	((head->Child_Nodes))->Parent = head;
	((head->Child_Nodes))->Player = Get_Player_In_Node(dll_first(allPlayers));
	insert_tree((head->Child_Nodes), 1);

	dll_traverse(itr, rangeList)
	{
		((head->Child_Nodes) + i)->Level = 1;
		((head->Child_Nodes) + i)->Parent = head;
		((head->Child_Nodes) + i)->Player = Get_Player_In_Node(itr);
		insert_tree(((head->Child_Nodes) + i), 1);
		i++;
	}
	Head=head;
	free_dllist(rangeList);
}

void insert_tree(Tree Node, int Level)
{
	properties->jump_count++;

	if (Level == properties->num_jumps)
	{
		dll_append(allChildlessTreeNodes, new_jval_v(Node));
		return;
	}
	Level++;

	Dllist rangeList = get_jumpable_players(Node);
	Node->Child_Count = get_node_count_in_list(rangeList);
	if (Node->Child_Count == 0)
	{
		dll_append(allChildlessTreeNodes, new_jval_v(Node));
		return;
	}

	Node->Child_Nodes = Malloc_Tree(Node->Child_Count);

	int i = 0;
	Dllist itr;
	dll_traverse(itr, rangeList)
	{
		((Node->Child_Nodes) + i)->Level = Level;
		((Node->Child_Nodes) + i)->Parent = Node;
		((Node->Child_Nodes) + i)->Player = Get_Player_In_Node(itr);
		insert_tree((Node->Child_Nodes) + i, Level);
		i++;
	}
	free_dllist(rangeList);
}

void print_ways()
{
	properties->jump_count = 0;
	Dllist itr_list;
	Tree itr_tree;
	Tree node_tree;
	int i = 1;
	int parent_count;
	printf("\n\n--Bulunan Yollar--\n");
	dll_traverse(itr_list, allChildlessTreeNodes)
	{
		node_tree = Get_Tree_In_Node(itr_list);
		parent_count = 1;
		printf("%d-[%s] ", i, node_tree->Player->Name);
		tree_scan_to_head(itr_tree, node_tree)
		{
			parent_count++;
			printf("[%s] ", itr_tree->Player->Name);
		}
		printf("- %d Node\n", parent_count);
		i++;
	}
}

void start_game(int initialRange, int jumpRange, int numJumps, int initialPower, double powerReduction)
{
	create_properties(initialRange, jumpRange, numJumps, initialPower, powerReduction);
	read_file();
	create_tree();
	print_ways();
	find_best_way();
	free_game();
}

/*      		Free             */

void free_player(Player player)
{
	free(player->Name);
	free(player);
}

void free_allPlayers()
{

}

void free_tree(Tree Node)
{
	Tree Parent;
	if(Node->Parent!=NULL)
	{
	 	Parent = Node->Parent;
	}
	else
	{
		free(Node);
		return;
	}
	for(int i = 0;i<Parent->Child_Count;i++)
	{
		if((((Parent->Child_Nodes)+i)->Child_Count)!=0)
		{
			free_tree(((Parent->Child_Nodes)+i)->Child_Nodes);
			return;
		}
	}
	free(Parent->Child_Nodes);
	Parent->Child_Count=0;
	free_tree(Parent);
}

void free_game()
{
	free_tree(Get_Tree_In_Node(dll_first(allChildlessTreeNodes)));


	free(properties);
	free_dllist(allChildlessTreeNodes);
}
