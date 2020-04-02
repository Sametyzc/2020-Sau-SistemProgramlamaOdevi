#ifndef _GAME_
#define _GAME_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dllist.h"
#include "fields.h"

typedef struct player_struct {
    int Coordinate_X;
    int Coordinate_Y;
    int Current_PP;
    int Max_PP;
    char* Name;
} * Player;

//Program calistirildiginda verilen argumanlari tutan struct
typedef struct input_struct {
    int initial_range;
    int jump_range;
    int num_jumps;
    int initial_power;
    double power_reduction;
    int current_power; /*Sahip olunan suanki guc baslangicta initial_power a esit olmali*/
    int jump_count; /*Her sicramada bir artirilacak degisken*/
} * Properties;

typedef struct tree_node {
    int Child_Count; //Kac cocuga sahip oldugunu belirten degisken
    struct tree_node* Child_Nodes; //Cocuklarin listesini tutan dizi
    struct tree_node* Parent; //Suan bulunan nodun parentini gosteren degisken
    struct player_struct* Player; //Suanki node icindeki playeri gosteren degisken
    int Level; //Node ne kadar derinlikte oldugunu gosterir
} * Tree;

//Argumanlari tutan global degisken
extern Properties properties;

//Butun oyuncuları tutan global liste
extern Dllist allPlayers;

//Cocogu olmayan agac dugumlerini tutan liste
extern Dllist allChildlessTreeNodes;

//Verilen liste node icerisindeki player_structi dondurur.
#define Get_Player_In_Node(node) (((Player)jval_v(node->val)))

//Verilen liste node icerisindeki player_structi dondurur.
#define Get_Tree_In_Node(node) (((Tree)jval_v(node->val)))

//Malloc ile player tipinde yer ayrılır
#define Malloc_Player() ((struct player_struct*)malloc(1 * sizeof(struct player_struct)))

//Malloc ile Tree tipinde yer ayrılır
#define Malloc_Tree(number) ((struct tree_node*)malloc(number * sizeof(struct tree_node)))

//Verilen tree node dan baslayarak heade dogru tarama yapan ifade
#define tree_scan_to_head(itr, tree) \
for(itr = tree->Parent; itr->Parent != NULL; itr = itr->Parent)

#define tree_scan_to_head2(itr, tree) \
for(itr = tree; itr->Parent != NULL; itr = itr->Parent)

/*
Parametre olarak aldığı IS içerisinden okuyacağı oyuncu bilgilerini
kullanarak Player olusturup bu playerleri bir listeye ekleyip
listeyi donduren fonksiyon
1.Parametre Dosyayı iceren fields.h in icerisindeki IS structi
return Butun playerlari iceren Dllist
*/
extern Dllist read_file();

/*
Properties global degiskenine set eden fonksiyon
1.Parametre create_properties() fonksiyonundan donen deger atanabilir
*/
extern void set_properties(Properties);

/*
Argumanlar okunduktan sonra malloc ile properties structi olusturan fonksiyon
return olusturulan properties dondurulur
1.Parametre initial_range
2.Parametre jump_range
3.Parametre num_jumps
4.Parametre initial_power
5.Parametre power_reduction
*/
extern Properties create_properties(int, int, int, int, double);

/*
dosya okunduktan sonra allPlayers global degiskenini set eden fonksiyon
*/
extern void set_allPlayers();

/*
Verilen parametrelere uygun olarak player olusturup donduren fonksiyon
1.Parametre Coordinate_X
2.Parametre Coordinate_Y
3.Parametre Current_PP
4.Parametre Max_PP
5.Parametre Name
*/
extern Player create_player(int, int, int, int, char[]);

/* Verilen playerin ne kadar pp ye ihtiyac duydugunu hesaplayan fonksiyon
1.Parametre Hesap yapilmak istenen player
return Gerekli olan PP nin sayisal degeri
*/
extern int get_required_pp(Player);

/* Bir playerin jump_rangede olup olmadigini dondurecek fonksiyon
1.Parametre Suan iyilestirme sirasi 1 olan player
2.Parametre Rangede olup olmadigina bakilacak player
return 0 false 1 true olarak dondurulecek
*/
extern int is_player_in_range(Player, Player);

/*
Verilen playerin range indeki playerlarin listesini donduren fonksiyon
1.Parametre Referans player
return range deki playerlari iceren Dllist
*/
extern Dllist all_players_in_range(Player);

/*
Parametre olarak verilen listenin icerisinde kac node oldugunu bulan fonksiyon
1.Parametre icinde kac tane node oldugu bilinmek istenen liste
return listenin node sayisi int olarak geri dondurulur
*/
extern int get_node_count_in_list(Dllist);

/*
Parametre olarak gelen dugumun icerisindeki playerin atlayabilecegi playerlarin listesini dondurur
1.Parametre bakilmak istenen dugum
return playerlari iceren listeyi dondurur
*/
extern Dllist get_jumpable_players(Tree);

/*
İyileştirmenin en verimli olduğu yolu bulan fonksiyon
*/
extern void find_best_way();

/*
playeri Properties goz onune alinarak simüle etme
1.Parametre iyilestirme yapilacak player
*/
extern void Simulate(Player, int);

extern void Heal(Player, int);

//oyun icin gerekli fonksiyon cagirilarinin yapildigi yer
extern void start_game(int, int, int, int, double);

/*          TREE         */

/*
Bir agac olusturup ilk deger atamasini ve cocuk atamasini yapan fonksiyon
*/
extern void create_tree();

/*
Agacin icerisine yinelemeli olarak cocuk ekleyen fonksiyon
*/
extern void insert_tree(Tree, int);

/*
mumkun olan yollari bulup ekrana yazdiran fonksiyon
*/
extern void print_ways();

/*      		Free             */

/*
Parametre olarak gonderilen oyuncunun heapteki alanlarini ve kendisini serbest birakan fonksiyon
*/
extern void free_player(Player);

/*
global degisken olan allPlayers listesinin icerisindeki playerlari ve en son listeyi serbest birakan fonksiyon
*/
extern void free_allPlayers();

/*
agaci serbest birakan fonksiyon
*/
extern void free_tree(Tree);

/*
oyun kutuphanesi iceriside heapte olusturulmus her seyi serbest birakan fonksiyon
diger free fonksiyonlari bunun icerisinde cagirilabilir
*/
extern void free_game();

#endif
