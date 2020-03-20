#ifndef _OYUN_
#define _OYUN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dllist.h"
#include "fields.h"
#include "jval.h"

#define MAX_NAME 100
typedef struct player_struct {
  int Coordinate_X;
  int Coordinate_Y;
  int Current_PP;
  int Max_PP;
  char Name[MAX_NAME];
  int Turn;/*iyilesmeyi sektirecek kisiyi gosterir 1 ve ya 0 olabilir baslangicta sira Lokmanda olmali*/
} *Player;

//Program calistirildiginda verilen argumanlari tutan struct
typedef struct input_struct {
  int initial_range;
  int jump_range;
  int num_jumps;
  int initial_power;
  int power_reduction;

  int current_power;/*Sahip olunan suanki guc baslangicta initial_power a esit olmali*/
  int jump_count; /*Her sicramada bir artirilacak degisken*/
} *Properties;

//Verilen node icerisindeki player_structi dondurur.
#define Get_Player_In_Node(node) (((Player)jval_v(node->val)))

#define Create_Player_As_Jval() (new_jval_v((struct player_struct*) malloc (1* sizeof(struct player_struct))))

//Argumanlari tutan global degisken
Properties properties;
//Butun oyuncuları tutan global liste
Dllist allPlayers;
//Yapilan toplam iyilestirmeyi tutan global deger
int totalHealing;

/*Parametre olarak aldığı IS içerisinden okuyacağı oyuncu bilgilerini
kullanarak Player olusturup bu playerleri bir listeye ekleyip
listeyi donduren fonksiyon
1.Parametre Dosyayı iceren fields.h in icerisindeki IS structi
return Butun playerlari iceren Dllist*/
extern Dllist read_file(IS);//Kubra

/*Programa verilen argumanlari structa atayip
Properties global degiskenine set eden fonksiyon*/
extern void set_properties();//Kubra

/*
dosya okunduktan sonra allPlayers global degiskenini set eden fonksiyon
*/
extern void set_allPlayers();//Kubra
/* Verilen playerin ne kadar pp ye ihtiyac duydugunu hesaplayan fonksiyon
1.Parametre Hesap yapilmak istenen player
return Gerekli olan PP nin sayisal degeri
*/
extern int get_required_pp(Player);//Samet

/* Bir playerin jump_rangede olup olmadigini dondurecek fonksiyon
1.Parametre Suan iyilestirme sirasi 1 olan player
2.Parametre Range olup olmadigina bakilacak player
return 0 false 1 true olarak dondurulecek
*/
extern int is_player_in_range(Player,Player);//Samet

/*
Verilen playerin range indeki playerlarin listesini donduren fonksiyon
1.Parametre Referans player
return range deki playerlari iceren Dllist
*/
extern Dllist all_players_in_range(Player);//Samet

/*
playeri Properties goz onune alinarak iyitestiren fonksiyon
1.Parametre iyilestirme yapilacak player
iyilestirme yapildiktan sonra properties degerleri guncellenmeli
*/
extern void heal_player(Player);//Yoruk

/*
iyilestirme yaptiktan sonra properties icerisindeki current_power degerini
guncellemek icin kullanilan fonksiyon
*/
extern void update_power();//Yoruk

/*
Oyun boyunca yapilan toplam iyilestirmeyi tutan totalHealing degerini iyilestirme yaptiktan sonra update eden fonksiyon
1.Parametre totalHealing e eklenecek olan deger
*/
extern void update_totalHealing(int);//Yoruk


#endif
