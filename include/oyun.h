#ifndef _OYUN_
#define _OYUN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dllist.h"
#include "fields.h"
#include "jval.h"

typedef struct player_struct {
  int Coordinate_X;
  int Coordinate_Y;
  int Current_PP;
  int Max_PP;
  char* Name;
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

//Player structu olusturup jval.void olarak atayan ifade
#define Create_Player_As_Jval() (new_jval_v((struct player_struct*) malloc (1* sizeof(struct player_struct))))

//Verilen Jval icerisindeki Playeri dondurur
#define Get_Jval_As_Player(Jval) ((Player)jval_v(Jval))

//Malloc ile player tipinde yer ayrılır
#define Malloc_Player() ((struct player_struct*) malloc (1* sizeof(struct player_struct)))

//Verilen playeri jvala donunturur
#define Player_to_Jval(Player) (new_jval_v(Player))

//Argumanlari tutan global degisken
extern Properties properties;

//Butun oyuncuları tutan global liste
extern Dllist allPlayers;

//Yapilan toplam iyilestirmeyi tutan global deger
int totalHealing;

/*
Parametre olarak aldığı IS içerisinden okuyacağı oyuncu bilgilerini
kullanarak Player olusturup bu playerleri bir listeye ekleyip
listeyi donduren fonksiyon
1.Parametre Dosyayı iceren fields.h in icerisindeki IS structi
return Butun playerlari iceren Dllist
*/
extern Dllist read_file(IS);//Kubra

/*
Properties global degiskenine set eden fonksiyon
1.Parametre create_properties() fonksiyonundan donen deger atanabilir
*/
extern void set_properties(Properties);//Kubra

/*
 Argumanlar okunduktan sonra malloc ile properties structi olusturan fonksiyon
 return olusturulan properties dondurulur
 1.Parametre initial_range
 2.Parametre jump_range
 3.Parametre num_jumps
 4.Parametre initial_power
 5.Parametre power_reduction
*/
extern Properties create_properties(int,int,int,int,int);//Kubra

/*
dosya okunduktan sonra allPlayers global degiskenini set eden fonksiyon
*/
extern void set_allPlayers();//Kubra

/*
  Verilen parametrelere uygun olarak player olusturup donduren fonksiyon
  1.Parametre Coordinate_X
  2.Parametre Coordinate_Y
  3.Parametre Current_PP
  4.Parametre Max_PP
  5.Parametre Name
  6.Parametre Turn
*/
extern Player create_player(int,int,int,int,char[],int);//Samet

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
