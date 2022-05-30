#include"cyfighters.h"

void initPersonnage(){
  
}
void initAttaque() { // initialise les attaques de chacuns.
  
  FILE * attackFile; 
    char ligne[512]; 
    char * strToken; 
    const char * separators = ";";
    
    attackFile = fopen( "attaques.txt", "r" ); 
    
    if ( attackFile == NULL ) {
        printf( "\n Cannot open file %s\n", "attaques.txt" ); 
    }
    
    int i=0;
    int j =0;
    while ( !(feof(attackFile )|| i > 17 )) 
    {
        fgets( ligne, 511, attackFile ); 
        if ( ferror( attackFile ) ) 
        {
            fprintf( stderr, "Reading error with code %d\n", errno );
            break; 
        }
        
        puts( ligne ); 
        strToken = strtok ( ligne, separators ); 
        j=0;
        while ( strToken != NULL )  
        {
            printf ( "%s\n", strToken );
          
            if(j==0){ 
            strcpy(tabAttaques[i].nom_type,strToken);
            }
            if(j==1){
            tabAttaques[i].type= atoi(strToken); 
            }
            if(j==2){
            strcpy(tabAttaques[i].personnage,strToken);
            }
            if(j==3){
            tabAttaques[i].codePersonnage= atoi(strToken);
            }
            if(j==4){
            tabAttaques[i].degat= atoi(strToken);
            }
            if(j==5){
            tabAttaques[i].dispo= atoi(strToken);
            }
            if(j==6){
            strcpy(tabAttaques[i].descAttaque,strToken);
            }
          
            strToken = strtok ( NULL, separators );
            j++;
        }
    i++;    
    }

}


void vide_buffer(){    // pour faire en sorte que ca prenne pas les caracteres. 
  while(getc(stdin)!='\n'){

  }
}

int main() {

srand(time(NULL));
  
initAttaque();



  Personnage perso[NB_PERSONNAGE] = { // creer une fonction initialisation, j'aurai juste à l'appeler
        {"PYRO", 1, " histoire de pyro",100, 0, NULL, NULL, NULL },
        {"TOTO", 2, " histoire de toto",100,0,NULL,NULL,NULL},
        {"SOSO", 3, " histoire de soso", 100,0, NULL,NULL,NULL},
        {"WIWI", 4, " histoire de wiwi", 100,0, NULL,NULL,NULL},
        {"FIFI", 5, " histoire de fifi", 100,0, NULL,NULL,NULL},
        {"DODO", 6, " histoire de dodo", 100,0, NULL,NULL,NULL}
};


for ( int i = 0; i < NB_PERSONNAGE; i++){ // fonction association personage attaque
    perso[i].attaque1 = &tabAttaques[i]; 
    perso[i].attaque2 = &tabAttaques[i+6]; 
    perso[i].ultime = &tabAttaques[i+12]; 
  }


  

int i=0; // on fait un tableau qui va appeler chaque joueur parce que flemme de repeter mille fois la meme chose
    printf ("PRESENTATION DES PERSONNAGES : \n\n");
    for (i=0; i< NB_PERSONNAGE; i++) {

        printf(">> %s\n", perso[i].nom_personnage);
        printf("Attaque basique : %s\n" , perso[i].attaque1->descAttaque); // ducoup ca pas besoin non ? je peut juste demander à printf la structure nn ? askip ca existe pas
      
        printf("Attaque moyenne : %s\n", perso[i].attaque2->descAttaque);
        printf("Ultime : %s\n", perso[i].ultime -> descAttaque);
        printf("~ %s ~\n", perso[i].histoire);
        printf("_______________________________________________\n"); // nb à refaire mieux avec les printf
}
// faire un fichier.h ou je donne deja ttes les caracteristiques de chaque perso ensuite y'aura juste à les print.


for (int i=0; i < 6; i++) {
    printf( "|%d| %s ",i+1, perso[i].nom_personnage); // là on met juste les joueurs dispos, il faut affciger le tableaui des joueurs avec celui qui est plus dispo
}

int val_tape; 

printf("PV DE DEPART : PV = 100");

// LE FOR QUI SUIT C EST POUR REPETER LES BOUCLES DE PERSO 1 ET 2 3 FOIS. 

/*int modeChoisi;
printf(" Etes vous à deux ou bien seul ?");
scanf("%d", modeChoisi);
*/
  


for ( int j = 0; j < 3; j++) { // la boucle qui va faire que chaque joueur aura aura 3 persos. Pas plus pas moins



  // BOUCLE CHOIX DU PERSONNAGE 1 
     
    do { // on fait en sorte que si la valeur tapé n'est pas dispo il redemande
    
        printf("\n \n >> joueur 1, choisit ton personnage en entrant son numéro : \n"); // là on demande d'entree un joueur
        scanf("%d", &val_tape);
        while(  val_tape < 1 || val_tape > 6){
          
	vide_buffer();
           
          printf("\n impossible perso inexistant\n\n"); 
          printf("\n \n >> joueur 1, choisit ton personnage en entrant son numéro : \n"); // là on demande d'entree un joueur
          scanf("%d", &val_tape);

          }


        if (perso[val_tape -1].numEquipe == 0) { // si personnage disponible et que la valeur tapé c'est le meme que le perso alors i leut le prendre
            perso[val_tape - 1].numEquipe = 1;
            printf ( " vous avez choisi %s \n \n " , perso[val_tape - 1].nom_personnage); }
        else {
        printf(" \n impossible, choisissez un autre personnage ! \n \n"); // il peut pas et grace à la boucle ca va redemander 
        }

      for ( i = 0 ; i < 6 ; i++) { // ici on reecrit les joueurs dispo seulement.
          if(perso[i].numEquipe == 0) {
            printf( " |%d| %s ",i+1, perso[i].nom_personnage); 
            }
        }

      
     if ( perso[val_tape - 1].numEquipe == 1){
       break; 
      }
} while(perso[val_tape - 1].numEquipe != 0);



// BOUCLE CHOIX DU PERSONNAGE 2 

  
//if(modeChoisi == 1) {
  int b ;
printf("\n \n >> l'ordinateur va choisir un personnage... \n"); // là on demande d'entree un joueur
  
   do {
           b = rand() %6;
} while((perso[b].numEquipe != 0) ); // vu que les joueurs qui son dispo ils ont leur numEquipe = 0 bah si c'est pas zero c'est mort
   printf ( " l'ordi a choisi %s \n \n " , perso[b].nom_personnage); 
  perso[b].numEquipe = 2;    
 // }     
  
printf( " \n MERCI, LE JEU PEUT COMMENCER ! >>>> \n \n ");
printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n ");

    do {
        printf("\n \n >> joueur 2, choisit ton personnage en entrant son numéro : \n"); // là on demande d'entree un joueur
        scanf("%d", &val_tape);
          while(  val_tape < 1 || val_tape > 6){
	

            printf("impossible perso inexistant\n\n"); 
            printf("\n \n >> joueur 1, choisit ton personnage en entrant son numéro : \n"); // là on demande d'entree un joueur
            scanf("%d", &val_tape);
          }

            if (perso[val_tape -1].numEquipe == 0) { // si personnage disponible et que la valeur tapé c'est le meme que le perso alors i leut le prendre
              perso[val_tape - 1].numEquipe = 2;
              printf ( " vous avez choisi %s \n \n " , perso[val_tape - 1].nom_personnage); }
            else {
	vide_buffer();
              printf(" \n impossible, choisissez un autre personnage ! \n \n"); // il peut pas et grace à la boucle ca va redemander 
                  }
      for ( i = 0 ; i < 6 ; i++) { // ici on reecrit les joueurs dispo seulement.
          if(perso[i].numEquipe == 0) {
            printf( " |%d| %s ",i+1, perso[i].nom_personnage); 
            }
        }
      
    
  
  if ( perso[val_tape - 1].numEquipe == 2 ){
        break;
      }
} while((perso[val_tape - 1].numEquipe != 0) || (val_tape < 1 || val_tape > 6)); // vu que les joueurs qui son dispo ils ont leur numEquipe = 0 bah si c'est pas zero c'est mort
    }

    
        int b ;
          printf("\n \n >> l'ordinateur va choisir un personnage... \n"); // là on demande d'entree un joueur

             do {
                 b = rand() %6;
                printf("%d",b);
} while((perso[b].numEquipe != 0) ); // vu que les joueurs qui son dispo ils ont leur numEquipe = 0 bah si c'est pas zero c'est mort
  printf ( " l'ordi a choisi %s \n \n " , perso[b].nom_personnage); 
  perso[b].numEquipe = 2;    
     

  printf( " \n MERCI, LE JEU PEUT COMMENCER ! >>>> \n \n ");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n ");


// là on demande au joueur un et deux de choisir le perso qui va attaquer et qui va etre icblé.
 
int persoChoisi;
// JOUEUR 1
//do {
printf(" \n \n joueur 1, quel personnage veux-tu faire jouer ? \n\n"); // nb faire un while qui dit que tant que t'as pas mis un joeuru que t'as bah tu recommence. 
  
  for (i = 0 ; i < 6; i++){    // /!\ METTRE UN WHILE NOUHA
  if( perso[i].numEquipe == 1) {
      printf("|%d| %s  ", i+1, perso[i].nom_personnage);
      }
  } // la on met les persos du joueur 1
  
scanf("%d",&persoChoisi); 
printf("\n <<<< tu as choisi de jouer %s >>>> \n\n", perso[persoChoisi-1].nom_personnage);

int attaqueChoisi; // là je demande l'attaque qu etu veux utiliser.
printf("--> Quelle attaque veux-tu choisir ? tape son numéro ! \n\n"); // /!\ METTRE UN WHILE NOUHA
  
printf("|%d| %s \n ", 1, perso[persoChoisi -1 ].attaque1-> descAttaque);
printf("|%d| %s \n ", 2, perso[persoChoisi -1 ].attaque2 -> descAttaque);
printf("|%d| %s \n ", 3, perso[persoChoisi -1 ].ultime -> descAttaque);

scanf("%d", &attaqueChoisi);
    
  if (attaqueChoisi == 1) {
      printf("tu as choisi d'attaquer avec  %s \n", perso[persoChoisi-1].attaque1 -> descAttaque);
    }
  if (attaqueChoisi == 2) {
      printf("tu as choisi d'attaquer avec %s \n", perso[persoChoisi-1].attaque2 -> descAttaque);
    }
  
    if (attaqueChoisi == 3) {
      printf("tu as choisi d'attaquer avec %s \n", perso[persoChoisi-1].ultime -> descAttaque);
      }
   // là on a scan l'attaque choisi mtn attention il faut faire les do while !!! pour pas qu'on ecrive n'importe quoi !
// mtn on demande le joueur qui va etre cible.

printf(" \n --> Qui veux tu cibler ? Entre son numéro ! \n\n");

int persoCible;
  for (i = 0 ; i < 6; i++){         // là on met les perso ennemis
    if( perso[i].numEquipe == 2) {
      printf("|%d| %s  ", i+1, perso[i].nom_personnage);
      }
  }
  
scanf("%d",&persoCible); 
printf("\n <<<< tu as choisi de cibler %s >>>> \n\n", perso[persoCible-1].nom_personnage);  

int a;
Personnage *attaquant = &perso[persoChoisi-1];
Personnage *cible = &perso[persoCible-1];

if ( attaqueChoisi == 1){            // ici on dit ce qu'il se passe en fonction des attaques choisies ! 
printf(" la cible %s va tenter une esquive...\n", cible);
  cible->pv = cible->pv + attaquant-> attaque1-> degat ;
 a=rand()%5;
if (a==3){
	cible->pv=cible->pv-attaquant->attaque1->degat;
	printf("%s a réussi à esquiver \n", cible);
}
else {
	printf("dommage %s n'a pas reussi à esquiver\n", cible);
	}

  }
if ( attaqueChoisi == 2){
	printf(" la cible %s va tenter une esquive...\n", cible);
  cible->pv = cible->pv + attaquant-> attaque2-> degat ;
a=rand()%5;    // la on fait un random pour choisir un chiffre entre 0 et 3.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
if (a==3){
	cible->pv=cible->pv-attaquant->attaque2->degat;
	printf("%s a réussi à esquiver \n", cible);
}
else {
	printf("dommage %s n'a pas reussi à esquiver\n", cible);
	}
}

  if ( attaqueChoisi == 3){   // ici on sait que fifi est la seule à redonner des pv.
  
    if( perso [persoChoisi - 1].codePersonnage == 5) {    // cas particulier de fifi.
      for(i = 0; i<6; i++){
        if (perso[4].numEquipe == perso[i].numEquipe){
          perso[i].pv = perso[i].pv + attaquant-> ultime -> degat; 
        }
      }
      printf(" /!/ %s soigne ses alliés en plus de faire subir des degats à %s !! \n \n ", attaquant, cible);
      
      for (i = 0; i<6; i++) {
        if(perso[i].numEquipe == 1){
        printf("PV restants de %s : |%d| \n", perso[i].nom_personnage, perso[i].pv);
          }
    }
      printf("PV restants de %s : |%d| \n ", cible, cible-> pv -10 );
      }
      
    else {
cible->pv = cible->pv + attaquant-> ultime-> degat ;
      
		

printf(" la cible %s va tenter une esquive...\n ", cible);
a=rand()%5;

if (a==3){
  cible->pv=cible->pv-attaquant->ultime->degat;
	printf("\n %s a réussi à esquiver\n", cible);
	}
else {
	printf("\n dommage %s n'a pas reussi à esquiver \n ", cible);
	}
        }
  }

// JOEUR 2 
printf("____________________________________________________________________________");

printf(" \n \n joueur 2, quel personnage veux-tu faire jouer ? \n\n"); // nb faire un while qui dit que tant que t'as pas mis un joeuru que t'as bah tu recommence. 
  
for (i = 0 ; i < 6; i++){
    if( perso[i].numEquipe == 2) {
      printf("|%d| %s  ", i+1, perso[i].nom_personnage);
      }
  } // la on met les persos du joueur 2
  
scanf("%d",&persoChoisi); 
printf("\n <<<< tu as choisi de jouer %s >>>> \n\n", perso[persoChoisi-1].nom_personnage);

 // là je demande l'attaque qu etu veux utiliser.
printf("--> Quelle attaque veux-tu choisir ? tape son numéro ! \n\n");
  
printf("|%d| %s \n ", 1, perso[persoChoisi -1 ].attaque1-> descAttaque);
printf("|%d| %s \n ", 2, perso[persoChoisi -1 ].attaque2 -> descAttaque);
printf("|%d| %s \n ", 3, perso[persoChoisi -1 ].ultime -> descAttaque);

scanf("%d", &attaqueChoisi);
    
  if (attaqueChoisi == 1) {
      printf("tu as choisi d'attaquer avec  %s \n", perso[persoChoisi-1].attaque1 -> descAttaque);
    }
  if (attaqueChoisi == 2) {
      printf("tu as choisi d'attaquer avec %s \n", perso[persoChoisi-1].attaque2 -> descAttaque);
    }
  
    if (attaqueChoisi == 3) {
      printf("tu as choisi d'attaquer avec %s \n", perso[persoChoisi-1].ultime -> descAttaque);
      }
   // là on a scan l'attaque choisi mtn attention il faut faire les do while !!! pour pas qu'on ecrive n'importe quoi !
// mtn on demande le joueur qui va etre cible.

printf(" \n --> Qui veux tu cibler ? Entre son numéro ! \n\n");

  for (i = 0 ; i < 6; i++){         // là on met les perso ennemis
    if( perso[i].numEquipe == 1) {
      printf("|%d| %s  ", i+1, perso[i].nom_personnage);
      }
  }
  
scanf("%d",&persoCible); 
printf("\n <<<< tu as choisi de cibler %s >>>> \n\n", perso[persoCible-1].nom_personnage);  

if ( attaqueChoisi == 1){            // ici on dit ce qu'il se passe en fonction des attaques choisies ! 
printf(" la cible %s va tenter une esquive...\n", cible);
  cible->pv = cible->pv + attaquant-> attaque1-> degat ;
 a=rand()%5;
if (a==3){
	cible->pv=cible->pv-attaquant->attaque1->degat;
	printf("%s a réussi à esquiver \n", cible);
}
else {
	printf("dommage %s n'a pas reussi à esquiver\n", cible);
	}

  }
if ( attaqueChoisi == 2){
	printf(" la cible %s va tenter une esquive...\n", cible);
  cible->pv = cible->pv + attaquant-> attaque2-> degat ;
a=rand()%5;    // la on fait un random pour choisir un chiffre entre 0 et 3.                                    
  
if (a==3){
	cible->pv=cible->pv-attaquant->attaque2->degat;
	printf("%s a réussi à esquiver \n", cible);
}
else {
	printf("dommage %s n'a pas reussi à esquiver\n", cible);
	}
}

  if ( attaqueChoisi == 3){
cible->pv = cible->pv + attaquant-> ultime-> degat ;

printf("la cible %s va tenter une esquive...\n ", cible);
a=rand()%5;

if (a==3){
	cible->pv=cible->pv-attaquant->ultime->degat;
	printf("\n %s a réussi à esquiver\n", cible);
	}
else {
	printf("\n dommage %s n'a pas reussi à esquiver \n ", cible);
	}
}

printf(" \n PV restants de %s : |%d|",cible->nom_personnage,cible-> pv); // a modifier dans l'ergonomie
  //}while( // tout les perso de l'equipe 1 ou 2 sont KO);

  




return 0;
  // la fermeture du " si vous etes deux joueurs"



}

