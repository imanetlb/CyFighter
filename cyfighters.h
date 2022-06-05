#include <stdio.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
#include<errno.h>


#ifndef _CYFIGTHERS_H_
#define _CYFIGTHERS_H_

#define NB_PERSONNAGE 6
#define NB_ATTAQUE 18

typedef enum { false, true } bool;

char nomjoueur2[24]; 
bool joueur2estlePC;

typedef struct Attaque Attaque ; // structure pour attaque 


struct Attaque {
char nom_type[32];
int type; //0 ultime, 1 attack1, 2 attack2
char personnage[32];
int codePersonnage;
int degat;  // les degats
int dispo; // la description de l'attaque
char descAttaque [120];
};  

Attaque tabAttaques[NB_ATTAQUE];
Attaque *attaqueEnCours;


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
};  

Personnage perso[NB_PERSONNAGE];
Personnage *attaquant; //pointeur sur l'attaquant en cours
Personnage *cible; //pointeur sur le personnage ciblé en cours


// je declare ici les fonctions.
void chargerAttaques();
void chargerPersonnages();
void associerAttaquesPersonnage();
void afficherPersonnages();
void presentationPersonnages();
//void choixPersonnages();
void composerLesEquipes();
void vide_buffer();
void ergonomie(int numEquipe, int);
int verifierPV();
int choisirJoueur(int);
int choisirAttaque();
void attaquer();
void incmenterDisponibilite();
void composerPersonnagePC();
int choisirJoueurPC(int equipe);
void choisirModeJeu();

#endif

//----fin déclarations -----------//