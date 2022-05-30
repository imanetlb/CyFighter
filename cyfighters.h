#include <stdio.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
#include<errno.h>


//#include<conio.h> // pour utiliser le gotoxy
#define NB_PERSONNAGE 6
#define NB_ATTAQUE 18



// creer structure pour les attaques.

typedef struct Attaque Attaque ; // structure pour attaque 

struct Attaque {
char nom_type[32];
int type; //0 ultime, 1 attack1, 2 attack2
char personnage[32];
int codePersonnage;
int degat;  // les degats de l'ultime
int dispo; // la description de l'attaque ultime
char descAttaque [64];
char description [512];
};  

Attaque tabAttaques[NB_ATTAQUE];



typedef struct Personnage Personnage;

struct Personnage {  // structure personnage. 
char nom_personnage[32];
int codePersonnage;
char histoire [512];
int pv;
int numEquipe;
Attaque *ultime;  //  pointe sur ultime, idem pour les autres.
Attaque *attaque1;
Attaque *attaque2;


};   // à mettre dans un fichier texte.









/* // là on demande au joueur 1 de choisir son perso.
int perso_choisi;
for (i = 0 ; i < 6; i++);
    if( perso[i].numEquipe == 1) {
      printf("|%d| %s \n", i+1, perso[i].nom_personnage);
      }
printf(" joueur 1, quel personnage veux-tu faire jouer ? "); // nb faire un while qui dit que tant que t'as pas mis un joeuru que t'as bah tu recommence.
scanf("%d",&persoChoisi); // j'aile droit de reutiliser ca ? vu que je l'ai utilisé avant.
printf(" tu as choisi %s \n \n", perso[persoChoisi-1].nom_personnage);

printf("|%d| %s \n ", perso[persoChoisi-1].attaque1, perso[persoChoisi -1 ].desc_attaque1);
printf("|%d| %s \n ", perso[persoChoisi-1].attaque2, perso[persoChoisi -1 ].desc_attaque2);
printf("|%d| %s \n ", perso[persoChoisi-1].ultime, perso[persoChoisi -1 ].desc_ultime);
  int attaqueChoisi;
  int persoCible;

  printf(" que veux- tu faire ? "); // le joueur choisi l'attaque qu'il veut
  scanf("%d", &attaqueChoisi);
  printf(" qui veux tu cibler ?"); // il choisit qui va subir son attaque.
  scanf("%d", &persoCible); 
 
if ( attaqueChoisi = perso[val_tape-1].attaque1) { // et là on modifie les pv du */ 
//perso attaque en fonction de l'attaque du joueur.
// faire les degats qu'il faut à perso [persoCible-1].pv
//}
//*/


/*
questions pour prof : vous vouliez qu'on fasse une structure avec toutes les attaques mais chaque perso à des attaques qui lui sont propre. 
 Est ce que j'ai le droit de faire une structure qui découle d'une autre structure ? comme ce qu'il y a en bas ? 



------------------------------------------------------------------------

typedef struct equipe1 equipe1;

struct equipe1 {
int perso[].numEquipe = 1;    // comment faire pour que l'ordi classe dans l'equipe 1 les joueurs choisi par le joueur 1 ? je fais une structure ? 
}



printf(" joueur 1, quel personnage veux-tu faire jouer ? ")
scanf("%d",&val_tape); // j'aile droit de reutiliser ca ? vu que je l'ai utilisé avant.
printf(" tu as choisi %s \n \n", perso[val_tape-1].nom_personnage);

printf("|%d| %s \n ", perso[val_tape-1].attaque1, perso[val_tap -1 ].desc_attaque1);
printf("|%d| %s \n ", perso[val_tape-1].attaque2, perso[val_tap -1 ].desc_attaque2);
printf("|%d| %s \n ", perso[val_tape-1].ultime, perso[val_tap -1 ].desc_ultime);

int attaqueChoisi; 
int persoCible;

printf(" que veux- tu faire ? "); // le joueur choisi l'attaque qu'il veut 
scanf("%d", &attaqueChoisi );

printf(" qui veux tu cibler ?"); // il choisit qui va subir son attaque.
for ( i = 0 ; i <6; i++);
if ( perso[persoCible-1].numEquipe == 2);
printf( "|%d| %s ",i+1, perso[persoCible-1].numEquipe);
scanf("%d", &persoCible);

if ( attaqueChoisi = perso[val_tape-1].attaque1) {    // et là on modifie les pv du perso attaque en fonction de l'attaque du joueur. 
    // faire les degats qu'il faut à perso [persoCible-1].pv
} 
*/