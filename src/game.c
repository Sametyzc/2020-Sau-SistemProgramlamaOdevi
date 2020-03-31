#include "game.h"

Properties properties;
Dllist allPlayers;
Dllist allChildlessTreeNodes;

Dllist read_file()	//Kubra
{
	printf("--Dosya okunmaya baslandi!\n\n");
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
		if (strcmp(is->fields[4], "Lokman_Hekim"))
		{
			new_player = create_player(atoi(is->fields[0]), atoi(is->fields[1]), atoi(is->fields[2]), atoi(is->fields[3]), is->fields[4], 0);
		}
		else
		{
			new_player = create_player(atoi(is->fields[0]), atoi(is->fields[1]), atoi(is->fields[2]), atoi(is->fields[3]), is->fields[4], 1);
		}
		dll_append(allPlayers, new_jval_v(new_player));
	}
	printf("--Dosya okumasi tamamlandi!\n\n");
	printf("--allPlayers global degiskenine deger atandi!\n\n");
	return allPlayers;
}

Properties create_properties(int initialRange, int jumpRange, int numJumps, int initialPower, double powerReduction)	//Kubra
{
	properties = (struct input_struct *) malloc(1* sizeof(struct input_struct));
	properties->initial_range = initialRange;
	properties->jump_range = jumpRange;
	properties->num_jumps = numJumps;
	properties->initial_power = initialPower;
	properties->power_reduction = powerReduction;
	properties->current_power = initialPower;
	properties->jump_count = 0;

	printf("-Properties degerleri ->\n");
	printf("initial range : %d \n", properties->initial_range);
	printf("jump_range : %d \n", properties->jump_range);
	printf("num_jumps : %d \n", properties->num_jumps);
	printf("initial_power : %d \n", properties->initial_power);
	printf("power_reduction : %lf \n", properties->power_reduction);
	printf("--properties global degiskenine atama yapildi!\n\n");

	return properties;
}

Player create_player(int coordinate_x, int coordinate_y, int current_pp, int max_pp, char *name, int turn)	//Samet
{
	Player new_player;
	new_player = Malloc_Player();
	new_player->Coordinate_X = coordinate_x;
	new_player->Coordinate_Y = coordinate_y;
	new_player->Current_PP = current_pp;
	new_player->Max_PP = max_pp;
	new_player->Name = strdup(name);
	new_player->Turn = turn;

	printf("-Yeni player degerleri ->\n");
	printf("Name: %s\n", new_player->Name);
	printf("Coordinate_X: %d\n", new_player->Coordinate_X);
	printf("Coordinate_Y: %d\n", new_player->Coordinate_Y);
	printf("Current_PP: %d\n", new_player->Current_PP);
	printf("Max_PP: %d\n", new_player->Max_PP);
	printf("Turn: %d\n", new_player->Turn);
	printf("--Yeni player olusturuldu!\n\n");

	return new_player;
}

int get_required_pp(Player player)	//Samet
{
	return ((player->Max_PP) - (player->Current_PP));
}

int is_player_in_range(Player p_reference, Player p_target)	//Samet
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

Dllist all_players_in_range(Player p_reference)	//Samet
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
	printf("------get_jumpable_players '%s' calismaya basladi----\n\n", Node->Player->Name);
	Tree itr_tree;
	Dllist itr_list;
	Dllist rangeList = all_players_in_range(Node->Player);
	Dllist playersList = new_dllist();
	int i, isParent;
	dll_traverse(itr_list, rangeList)
	{
		Player itr_player = Get_Player_In_Node(itr_list);
		printf("--tree_scan_to_head calismaya basladi\n");
		i = 0;
		isParent = 0;
		tree_scan_to_head(itr_tree, Node)
		{
			printf("%d--- iterasyon basladi\n", i);
			if (strcmp((itr_tree->Player)->Name, itr_player->Name) == 0)
			{
				isParent = 1;
				break;
				printf("%d---- iterasyonda %s isimli oyuncu parent olarak bulundu\n", i, itr_player->Name);
			}
			printf("%d--- iterasyon bitti\n", i);
			i++;
		}
		if (isParent == 0)
		{
			printf("%d--- iterasyonda listeye '%s' isimli oyuncu eklendi \n", i, itr_player->Name);
			dll_append(playersList, itr_list->val);
		}
		printf("--tree_scan_to_head calismayi bitirdi\n");
	}
	free_dllist(rangeList);
	printf("-get_jumpable_players calismayi bitirdi\n\n");
	//Donus degeri new ile olusturuldugu icin cagirildigi yerde free ile serbest birakilmali
	return playersList;
}

int get_node_count_in_list(Dllist list)	//Samet
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
	return nodeCount + 1;
}

double healvalue = 0;
double totalheal = 0;
double temp = 0;
void find_best_way()	//Yoruk
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

void Simulate(Player player, int count)	//Yoruk
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

void free_player(Player player) {}	//Alperen

void free_allPlayers() {}	//Alperen

void free_properties() {}	//Alperen

void free_oyun() {}	//Alperen

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

	printf("-- head Child_Count :%d\n", head->Child_Count);
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
	free_dllist(rangeList);
}

void insert_tree(Tree Node, int Level)
{
	properties->jump_count++;

	printf("--level :%d\n", Level);
	if (Level == properties->num_jumps)
	{
		printf("----Seviye sinirina geldi-----\n\n");
		dll_append(allChildlessTreeNodes, new_jval_v(Node));
		return;
	}
	Level++;

	Dllist rangeList = get_jumpable_players(Node);
	Node->Child_Count = get_node_count_in_list(rangeList);
	printf("--Child_Count :%d\n", Node->Child_Count);
	if (Node->Child_Count == 0)
	{
		printf("----Atlamak icin cocuk kalmadi-----\n\n");
		dll_append(allChildlessTreeNodes, new_jval_v(Node));
		return;
	}

	printf("-insert_tree '%s' icin calismaya basladi\n", Node->Player->Name);

	Node->Child_Nodes = Malloc_Tree(Node->Child_Count);

	int i = 0;
	Dllist itr;
	printf("--- dll_traverse calismaya basladi\n");
	dll_traverse(itr, rangeList)
	{
		printf("---%s oyuncusunun %d inci cocugu -> %s\n", Node->Player->Name, i, Get_Player_In_Node(itr)->Name);
		((Node->Child_Nodes) + i)->Level = Level;
		((Node->Child_Nodes) + i)->Parent = Node;
		((Node->Child_Nodes) + i)->Player = Get_Player_In_Node(itr);
		insert_tree((Node->Child_Nodes) + i, Level);
		i++;
	}
	printf("-insert_tree calismayi bitidi\n\n");
	free_dllist(rangeList);
}

void print_allChildlessTreeNodes()
{
	properties->jump_count = 0;
	Dllist itr_list;
	Tree itr_tree;
	Tree node_tree;
	int i = 0;
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
	print_allChildlessTreeNodes();
	find_best_way();
}