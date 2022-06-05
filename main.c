#include "cyfighters.h"

//int joueur2estlePC;

int main() {
    
    bool  gameOpen =true; 
    int persoChoisi;
    int retour;

    srand(time(NULL)); // plusieurs choses aleatoire vont etre utiliseé : esquive, ordinateur...
    chargerAttaques();
    chargerPersonnages();  
    associerAttaquesPersonnage();
    //afficherPersonnages(); //fonction pour débuguer
    choisirModeJeu(); //contre pc ou jouer à deux
    presentationPersonnages();
    //début de jeu -- on commence par choir si contre PC ou à 2

    //début de jeu
    composerLesEquipes(); //composer les équipes


    // le jeu commence
while (gameOpen == true) { // nb faire un while qui dit que tant que t'as pas mis un joeur KO, bah tu recommence. 
    ergonomie(1, 0);
    ergonomie(2, 0);
    printf(" \n player 1, which character do you want to play ? \n"); 

    persoChoisi = choisirJoueur(1);
    if(persoChoisi <=0 || persoChoisi >6){
        printf( "\n ==== ERROR IN THE PLAYER'S CHOICE");
        break;
    }
        
    attaquant = &perso[persoChoisi-1];        
    printf("\n <<<< you chose to play %s >>>> \n", attaquant->nom_personnage);
    ergonomie(1,1); //affiche la matrice joueur 1 comme attaquant
    ergonomie(2,0); //affiche la matrice joueur 2 comme cible
    printf("--> Which attack do you want to chose for the character %s ? \n",attaquant->nom_personnage );
    int attaqueChoisi = choisirAttaque();

  
// mtn on demande le joueur qui va etre cible.

    printf(" \n --> Who do you want to target ? Enter his number ! \n");
    
    int persoCible;
        persoCible = choisirJoueur(2);
        if(persoCible <=0 || persoCible >6)
            printf( "\n ==== ERROR IN THE PLAYER'S CHOICE");
            cible = &perso[persoCible-1];  
            printf("\n <<<< you chose to target %s >>>> \n", cible->nom_personnage);  

//============= ON A CHOISI l'ATTAQUANT  dans l'équipe 1 et la CIBLE dans équipe 2======================//
    attaquer();
    incmenterDisponibilite();

    if( verifierPV() == 0){ 
        printf("\n ======================== no winner, the game continues =================\n"); //tout va bien on continue
    }
    else {
         gameOpen =false;
         break;
    }

    // JOEUR 2 
    printf("____________________________________________________________________________");
    ergonomie(1,0);
    ergonomie(2,0);
    printf(" \n %s, which character do you want to play ? \n",nomjoueur2); 
    if(joueur2estlePC){
        persoChoisi = choisirJoueurPC(2);
        if(persoChoisi <=0 || persoChoisi >6){
           printf( "\n ==== ERROR IN THE PLAYER'S CHOICE");
            break;
        }
    }
    else{
        persoChoisi = choisirJoueur(2); //
        if(persoChoisi <=0 || persoChoisi >6){
            printf( "\n ==== ERROR IN THE PLAYER'S CHOICE");
            break;
          }
    }
    
    attaquant =&perso[persoChoisi-1];
    printf("\n <<<< you chose to play %s >>>> \n", attaquant->nom_personnage);
    ergonomie(1,0); //affiche la matrice joueur 1 comme attaquant
    ergonomie(2,1); //affiche la matrice joueur 2 comme cible
    // là je demande l'attaque qu etu veux utiliser.
    printf("--> Which attack do you want to chose ? Enter his number !\n");  

    attaqueChoisi = choisirAttaque();

// mtn on demande le joueur qui va etre cible.
    printf(" \n --> Who do you want to target ? Enter his number ! \n");
    if(joueur2estlePC){    
        persoCible = choisirJoueurPC(1);
    }
    else{
        persoCible = choisirJoueur(1);
    }
    cible = &perso[persoCible-1];        
    printf("\n <<<< you chose to target %s >>>> \n", cible->nom_personnage); 
    //============= ON A CHOISI l'ATTAQUANT  dans l'équipe 2 et la CIBLE dans équipe 1
    attaquer();
    incmenterDisponibilite();

    if( verifierPV() == 0){ //vérfier les PV et fin de jeu
        printf("\n ======================== no winner, the game continues =================\n"); //tout va bien on continue
    }
    else {
         gameOpen =false;
         break;
    }
}//fin boucle de game open
return 0;
}