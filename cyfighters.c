#include "cyfighters.h"


//==================================================================================================================//
//fonction vérfier pv, renvoie 0 si les jeoeurs sont vivants, 1 si l'equipe 1 est gagnante,  2 si l'équipe 2 gagnante sinon -1 ==> erreur.
//==================================================================================================================//
int verifierPV(){
    bool equipe1Morte = true, equipe2Morte = true;
    int resultat =-1;
    for(int i=0; i<6; i++){
        if(perso[i].numEquipe ==1 && perso[i].pv > 0){
          equipe1Morte= false;
        } 
        
        if(perso[i].numEquipe ==2 && perso[i].pv > 0){
          equipe2Morte= false;
        }
  } //fin for
  
   if(equipe1Morte==false && equipe2Morte==false){
       resultat = 0;
    }
    
    else if(equipe1Morte==false && equipe2Morte==true){ //equipe 2 morte
        resultat = 1;
        printf( "\n WELL DONE Team 1");
        printf ("\n========== GAME OVER ==========\n");

    }
    
    else if(equipe1Morte==true && equipe2Morte==false){ //equipe 1 morte
        printf( "\n WELL DONE Team 2");
        printf ("\n========== GAME OVER ==========\n");
       resultat = 2;
    }
    else { 
         printf( "\nHP ERROR\n");
         resultat = -1;
        }

    return resultat;
}


//==========================================
//
//===========================================
void choisirModeJeu(){
  int retour;
   int modeDeJeu =0 ; // = 0 si 2 joueurs;   =1 si contre le PC.  
        printf(" choose game mode: \n" );
        printf(" enter 0 : to play team1 VS team2\n");
        printf(" enter 1 : to play team1 VS PC\n");
        do{
            retour = scanf("%d", &modeDeJeu);
            if (modeDeJeu<0 || modeDeJeu>1){
                vide_buffer(); 
                printf("Incorrect input, choose game mode\n");
                continue;
            }
            else if(modeDeJeu ==1)
            {
                joueur2estlePC = true;
                strcpy(&nomjoueur2[0],"computer") ;
                printf("\n>>>>>>>>>>>> Thank you ! You have chosen to play against the PC\n");
                break;
            }
            else if(modeDeJeu ==0) {
                joueur2estlePC = false;
                strcpy(&nomjoueur2[0],"player 2");
                printf("\n>>>>>>>>>>>> You have chosen to play equipe1 VS equipe2 \n");
                break;
            }
            else{
                printf("game mode not available!!! choose mode 0 or 1\n");
                vide_buffer();
            }
    }while(1);
}




//----------------------------------------------------------------------------//
//pour faire en sorte que les caracteres autre que les caractères numérique ne soient pas pris en compte.  ----//
//------------------------------------------------------------------------//
void vide_buffer() {
  while(getc(stdin)!='\n'){
  }
}

//----------------------------------------------------------------------------//
//vérifier que les pessonages sont bien chargés dans les structures.     ----//
//---------------------------------------------------------------------------//
void afficherPersonnages() {
    for(int t = 0; t<6; t++) { // pour verifier si ca marche bien
              printf("\n the character of order %d \n ", t);
              printf("name = %s | ",perso[t].nom_personnage);
              printf("code = %d | ",perso[t].codePersonnage);
              printf("history : %s | ",perso[t].histoire);
              printf("hp = %d | ",perso[t].pv);
    }
}

//---------------------------------------------------------//
//charger les attaques depuis le fichier attaques.txt ----//
//-------------------------------------------------------//
void chargerAttaques() { // charger les attaques.
  char* retour;
      printf ("\n>>>>>> loading of the attacks...");
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
        retour = fgets( ligne, 511, attackFile ); 
        if ( ferror( attackFile ) ) 
        {
            fprintf( stderr, "Reading error with code %d\n", errno );
            break; 
        }
        
        //puts( ligne ); 
        strToken = strtok ( ligne, separators ); 
        j=0;
        while ( strToken != NULL )  
        {
            //printf ( "%s\n", strToken );
          
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
      printf ("\n>>>>>>  END loading attacks.\n");
      
}

//=================================================================================//
// fonction chrgement et intialisation des personnages à partir du fichier
//
//=================================================================================//
void chargerPersonnages() {
    char * retour;
    printf ("\n>>>>>>  Loading of the characters...");
    FILE * personnageFile; 
    char ligne[512]; 
    char tmp[512];
    
    personnageFile = fopen( "personnages.txt", "r" ); 
    if ( personnageFile == NULL ) {
        printf( "\n Cannot open file %s\n", "personnages.txt" ); 
    }
    
    int j =0; // indice dans la ligne
    int k =0; //indice dans le tableau temporaire  tmp
    int numeroLigne =0; // numero de ligne dans le fichier
    int ordre =0; //ordre du champ dans la structure personnage
    while ( !(feof(personnageFile)|| numeroLigne > 5 ))  //on lit 6 lignes maximum (6 joueurs)
    {
        retour = fgets( ligne, 511, personnageFile ); 
        if ( ferror( personnageFile ) ) 
        {
            fprintf( stderr, "Reading error with code %d\n", errno );
            break; 
        }
        
        //puts ( ligne );
      ordre =0;
        for( j=0; j<=strlen(ligne); j++) {
           
            if( !(ligne[j] == ';' ||ligne[j] == '\0')) { 
                tmp[k] = ligne[j];
                k++;
            }
            else { // on a recontré un ';'
              tmp[k] = '\0';
                if(ordre == 0 ) {
                    strcpy(perso[numeroLigne].nom_personnage,tmp); 
                }
                if(ordre == 1 ) {
                    perso[numeroLigne].codePersonnage = atoi(tmp); 
                }
                if(ordre == 2 ) { 
                    perso[numeroLigne].pv= atoi(tmp); 
                }
                if(ordre == 3 ) {
                     strcpy(perso[numeroLigne].histoire,tmp); 
                }  
                perso[numeroLigne].numEquipe = 0;
                perso[numeroLigne].attaque1 = NULL;
                perso[numeroLigne].attaque2 = NULL;
                perso[numeroLigne].ultime = NULL;
              k=0;
              ordre++;
            }

        } 
    numeroLigne++;
    }
    printf ("\n>>>>>>  END loading characters.\n");
}

//---------------------------------------------------------//
// fonction association perso aux attaques.----------------//
//-------------------------------------------------------//
void associerAttaquesPersonnage(){
    for ( int i = 0; i < NB_PERSONNAGE; i++){ // fonction association perso aux attaques. 
        perso[i].attaque1 = &tabAttaques[i]; 
        perso[i].attaque2 = &tabAttaques[i+6]; 
        perso[i].ultime = &tabAttaques[i+12]; 
    //    printf(" %s   %d   %s \n",perso[i].attaque1->nom_type, perso[i].attaque1->type, perso[i].attaque1->personnage);
    //    printf(" %s   %d   %s \n",perso[i].attaque2->nom_type, perso[i].attaque2->type, perso[i].attaque2->personnage); 
    //    printf(" %s   %d   %s \n",perso[i].ultime->nom_type, perso[i].ultime->type, perso[i].ultime->personnage); 
    }
}

//---------------------------------------------------------//
// présentation à l'écran des personnages---------------------------//
//-------------------------------------------------------//
void presentationPersonnages(){
    int i=0; // on fait un tableau qui va appeler chaque joueur et les montrer au joueur
    printf("\033[0;31m");
    printf ("\n \n/////PRESENTATION OF THE CHARACTERS///// \n\n");
    printf("\033[0m");
    for (i=0; i< NB_PERSONNAGE; i++) {
        printf("\033[0;35m");
        printf("\n >> %s\n", perso[i].nom_personnage);
        printf("\033[0m");
        printf("\033[0;33m");
        printf("Basic attack is \n");
        printf("\033[0m");
        printf("%s\n" , perso[i].attaque1->descAttaque);
        printf("\033[0;36m");
        printf("Medium attack is \n");
        printf("\033[0m");
        printf("%s\n", perso[i].attaque2->descAttaque);
        printf("\033[0;32m");
        printf("Ultimate attack is \n");
        printf("\033[0m");
        printf("%s\n", perso[i].ultime -> descAttaque);
        printf("history : %s ", perso[i].histoire);
        printf("\n_______________________________________________\n"); 
    }
}


//===========================================================
// lorsque le PC compose son équipe
//========================================
  void composerPersonnagePC(){
  int val_tape;

        printf("\n \n >> the computer is choosing its character... \n");  
do { 
          val_tape= 1 + rand()%6;       
          
        if (perso[val_tape -1].numEquipe == 0) {
            perso[val_tape - 1].numEquipe = 2;
            printf ( " the computer has chosen %s \n \n " , perso[val_tape - 1].nom_personnage); 
            break;
              }
        else {
            continue;
        }
    } while(1); 

}

//=============================================================//
//fonction le PC choisit attaquant ou la cible
//=============================================================//
int choisirJoueurPC(int equipe){
    int numJoueur;
    for (int i = 0 ; i < 6; i++){   
        if( perso[i].numEquipe == equipe && perso[i].pv>0 ) {
            printf("|%d| %s  ", i+1, perso[i].nom_personnage);
        }
    }    
    do{
        numJoueur = 1+ rand()%6;
      } while(perso[numJoueur-1].numEquipe != equipe);
       // fin du choix si c'est le joueur 2 qui choisit       
  return numJoueur;
}

//---------------------------------------------------------------------//
// permet à chacun des joueurs de choisir 3 personnages --------------//
//--------------------------------------------------------------------//
void composerLesEquipes(){
int val_tape; 

printf("\n>>>>>>>>>>>>>>>>>>>>>> the game starts >>>>>>>>>>>>>>>>>>>>>> \n");

// LE FOR QUI SUIT C'EST POUR REPETER LES BOUCLES DE PERSO 1 ET 2; 3 FOIS. 

for ( int j = 0; j < 3; j++) { // la boucle qui va faire que chaque joueur aura aura 3 persos.
  // BOUCLE CHOIX DU PERSONNAGE pour composer l'équipe 1
    do { // on fait en sorte que si la valeur tapé n'est pas dispo il redemande
        for (int i = 0 ; i < 6 ; i++) { // ici on reecrit les joueurs dispo seulement.
        if(perso[i].numEquipe == 0) {
            printf( " |%d| %s ",i+1, perso[i].nom_personnage); 
            }
        }   
         printf("\n \n >> player 1, choose your character by entering his number : \n"); 
        scanf("%d", &val_tape);
        if( val_tape < 1 || val_tape > 6){
            vide_buffer();
            printf(" \n impossible, choose another character from the list ! \n");
            continue;
        }
        if (perso[val_tape -1].numEquipe == 0) { // si personnage disponible et valeur tapé  est celle du perso qu'il veut alors il peut le prendre
            perso[val_tape - 1].numEquipe = 1;
            printf ( " you chose %s \n\n " , perso[val_tape - 1].nom_personnage);
            break;
        }
        else if(perso[val_tape - 1].numEquipe == 1){
            vide_buffer();
            printf(" you have already taken this character, choose nother one \n");
        }
        else {
            vide_buffer();
            printf(" \n character unvailable !!! choose another one \n"); // il peut pas et grace à la boucle ca va redemander 
         }
    } while(1);  //en boucle tant que le personnage n'est pas choisi

// BOUCLE CHOIX DU PERSONNAGE 2 ou de l'ordi
  
      // l'ordinateur fait ses choix 
    if (joueur2estlePC) {
        for (int i = 0 ; i < 6 ; i++) { // ici on reecrit les joueurs dispo seulement.
            if(perso[i].numEquipe == 0) {
                printf( " |%d| %s ",i+1, perso[i].nom_personnage); 
              }
        }   
        composerPersonnagePC();    // si on joue seul contre l'ordi.  
    } // fin choix ordi 
    
    else{ // on joue à 2 équipes
        do {
            for (int i = 0 ; i < 6 ; i++) { // ici on reecrit les joueurs dispo seulement.
                if(perso[i].numEquipe == 0) {
                    printf( " |%d| %s ",i+1, perso[i].nom_personnage); 
                }
            }   
            printf("\n \n >> player 2, choose your character by entering his number : \n"); 
            scanf("%d", &val_tape);
            if( val_tape < 1 || val_tape > 6){
                vide_buffer();
                 printf(" \n impossible, choose another character from the list ! \n");
                continue;
            }
            if (perso[val_tape -1].numEquipe == 0) { // si personnage disponible et que la valeur tapé c'est le meme que le perso alors il peut le prendre
                perso[val_tape - 1].numEquipe = 2;
                printf ( " you chose %s \n\n " , perso[val_tape - 1].nom_personnage);
                break;
            }
            else if(perso[val_tape - 1].numEquipe == 2){
                vide_buffer();
                printf(" you have already taken this character, choose nother one \n");
            }
            else {
                vide_buffer();
                 printf(" \n character unvailable !!! choose another one \n"); // il peut pas et grace à la boucle ca va redemander 
            }   
        } while(1);  // on boucle tant que le personnage de joueur 2 n'est pas choisi
    } // fin if n = 2

}// fin for 
    
  printf( " \n THANKS, THE GAME CAN START! >>>> \n \n ");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n ");
} //fin focntion choix des personnages

//=============================================================//
//fonction choix du joueur pour l'attaque ou la cible
//=============================================================//
int choisirJoueur(int equipe){
    int numJoueur;
    
    for (int i = 0 ; i < 6; i++){   
        if( perso[i].numEquipe == equipe && perso[i].pv>0 ) {
        printf("|%d| %s  ", i+1, perso[i].nom_personnage);}
    }    
    
    vide_buffer();  
    do{
        scanf("%d",&numJoueur); 
        if( numJoueur < 1 || numJoueur > 6){
            vide_buffer();
            printf(" \n impossible, choose another character from the list ! \n");
            continue;
        }
        else if(perso[numJoueur-1].numEquipe!=equipe  || perso[numJoueur-1].pv <=0  ){
            printf (" \n \n Impossible, try again by typing a valid number \n");
            vide_buffer(); 
            continue;
        }
        else if( perso[numJoueur-1].numEquipe ==equipe && perso[numJoueur-1].pv >0){
             printf (" \n \n Impossible, try again by typing a valid number \n");
            break;
        }
        else{
            vide_buffer();    
        }
    } while(1); // (perso[numJoueur-1].numEquipe != equipe);    
        
    return numJoueur;
}

//=============================================================//
//Choix de l'attaque
//=============================================================//
int choisirAttaque(){
    int numAttaque;
    int attaque2Dispo = true, ultimeDispo = true;
    //vérifier si les attaques sont dispo
    if(attaquant->attaque2->dispo%2 !=0) attaque2Dispo =false;
    if(attaquant->ultime->dispo%4 !=0) ultimeDispo =false;

    if((joueur2estlePC) && ( attaquant -> numEquipe == 2)){
        do{
            numAttaque = 1+ rand()%3;
            if( (numAttaque ==1) ||(numAttaque ==2 && attaque2Dispo) || (numAttaque ==3 && ultimeDispo) )
            {
                break;
            }
        }while(1);
    }
    else{ 
        do{
            scanf("%d", &numAttaque);
            if (numAttaque<1 || numAttaque>3){
                vide_buffer(); 
                printf("inexistant attack ! which attack do you want to chose? \n");
                continue;
            }
            if( (numAttaque ==1) ||(numAttaque ==2 && attaque2Dispo) || (numAttaque ==3 && ultimeDispo) )
            {
                break;
            }
            else{
                printf(" chosen attack unavailable!!! choose an attack from the list \n");
                vide_buffer();
            }
        }while(1); 
    }
    
    if (numAttaque == 1) {
      printf("you chose to attack with  %s \n", attaquant->attaque1-> descAttaque);
      attaqueEnCours =attaquant->attaque1;
    }
    if (numAttaque == 2) {
        printf("you chose to attack with  %s \n", attaquant->attaque2-> descAttaque);
        attaqueEnCours =attaquant->attaque2;
    }
  
    if (numAttaque == 3) {
        printf("you chose to attack with  %s \n", attaquant->ultime-> descAttaque);
        attaqueEnCours =attaquant->ultime;
      }

    return numAttaque;
}


//=============================================================//
//fonction attaquer
//=============================================================//
void attaquer(){
    int a;
    
    printf("Attack in progress %s ; type=  %d \n",attaqueEnCours->nom_type, attaqueEnCours->type );
    printf("The damage of the current attack %s; the damage= %d \n",attaqueEnCours->nom_type, attaqueEnCours->degat );
    
    //attaqueEnCours->dispo++;
    
    if ( attaqueEnCours->type == 1){// attaques basique 
        printf(" the target %s will try a dodge...\n", cible->nom_personnage);
        //cible->pv = cible->pv + attaquant-> attaque1-> degat ;
        a=rand()%5;
        if (a==3){
	        printf("%s managed to dodge \n", cible->nom_personnage);
        }
        else {
            cible->pv=cible->pv-attaquant->attaque1->degat;
            if(cible->pv<0) cible->pv =0;
	             printf("Too bad, %s couldn't dodge\n \n", cible->nom_personnage);
	    }
         printf(" remaining HP de %s : |%d| \n ", cible->nom_personnage, cible-> pv);
    }//fin attaque basique
    
    else if ( attaqueEnCours->type  == 2){ //attaque moyenne
	         printf(" the target %s will try a dodge...\n", cible->nom_personnage);
            //cible->pv = cible->pv + attaquant-> attaque2-> degat ;
            a=rand()%5;    // la on fait un random pour choisir un chiffre entre 0 et 4.                                                                                                                                                                         
            if (a==3){
	            printf("%s managed to dodge \n", cible->nom_personnage);
            }
            else {
	            cible->pv=cible->pv - attaquant->attaque2->degat;
	            if(cible->pv<0) cible->pv =0;
	             printf("Too bad, %s couldn't dodge\n \n", cible->nom_personnage);
	        }
            printf(" remaining HP de %s : |%d| \n ", cible->nom_personnage, cible-> pv);
    }//fin attaque moyenne

    else if ( attaqueEnCours->type  == 0){   // on gère l'attaque ultime
        if( attaquant -> codePersonnage == 5) {    // cas particulier de FLORA, seule à redonner des pv.
            for( int i = 0; i<6; i++){
                if (perso[4].numEquipe == perso[i].numEquipe){
                    //fifi ne doit pas se donner des pv, et ne pas donner à ceux éliminés ou à ceux ayant déja le plein à 100
                    if(perso[i].codePersonnage  != 5 && perso[i].pv >0 && perso[i].pv <100){ //FLORA ne doit pas se donner des pv, et ne pas donner à ceux élimne
                        perso[i].pv = perso[i].pv +40;  //FLORA donne 20 PV à ses alliés
                        printf(" FLORA gaves 20 HP to her allies");
                        if(perso[i].pv > 100) perso[i].pv =100; //en plafonne à 100. 
                    }
                }
            }

            a=rand()%5;    // la on fait un random pour choisir un chiffre entre 0 et 4.                                                                                                                                                                         
            if (a==3){
	            printf("%s managed to dodge \n", cible->nom_personnage);
            }
            else {
	            cible->pv=cible->pv - attaquant->attaque2->degat;
	            if(cible->pv<0) cible->pv =0;
	            printf("Too bad, %s couldn't dodge\n \n", cible->nom_personnage);
	        }
        } // fin du cas particulier fifi 
        else {
            //cible->pv = cible->pv + attaquant-> ultime-> degat ;
            printf(" the target %s will try a dodge...\n", cible->nom_personnage);
            a=rand()%5;
            if (a==3){
	            printf("\n %s managed to dodge\n", cible->nom_personnage);
	        }
            else {
                cible->pv=cible->pv - attaquant->ultime->degat;
                if(cible->pv<0) cible->pv =0;
	            printf("Too bad, %s couldn't dodge\n \n", cible->nom_personnage);
	        }
        }
    printf(" remaining HP de %s : |%d| \n ", cible->nom_personnage, cible-> pv);
    }//fin attaque ultime
}//fin attaquer

//---------------------------------------------------------------------//
// fonction traiter les disponibilité---------------------------------//
// ne jamais changer attaque basique
// attaque2 incrémenté: 
//  - incémenté si attaque courante = attaque2
//  - si courante = BASIQUE est que que attaque2 n'est pas dispo
//  - si courante = ultime est que que attaque2 n'est pas dispo 
// ultime incrémenté: 
//  - incémenté si attaque courante = ultime
//  - si courante = BASIQUE est que que ultime n'est pas dispo
//  - si courante = attaque2 est que que ultime n'est pas dispo 
//--------------------------------------------------------------------//
void incmenterDisponibilite(){
    
    if(attaqueEnCours->type ==1){
        if(attaquant->attaque2->dispo%2 !=0){ //si attaque2 pas dispo on incrémente pour la rendre disponible
            attaquant->attaque2->dispo++;
        }
        if(attaquant->ultime->dispo%4 !=0){ //si ultime pas dispo on incrémente pour la rendre prochainnement dispo (au bout de 4 tours)
            attaquant->ultime->dispo++; 
        }
    }
    else if(attaqueEnCours->type ==2){
           attaquant->attaque2->dispo++;
        if(attaquant->ultime->dispo%4 !=0){
            attaquant->ultime->dispo++; 
        }
    }
    else if(attaqueEnCours->type ==0){
        attaquant->ultime->dispo++;
        if(attaquant->attaque2->dispo%2 !=0){
            attaquant->attaque2->dispo++; 
        }
    }
    else{
        printf("========= ERROR IN THE CURRENT ATTACK ===============");
    }
}


//---------------------------------------------------------------------//
// fonction d'ergonomie à completer                     --------------//
//--------------------------------------------------------------------//
void ergonomie(int equipe, int estAttaquant){ // 1 sir equipe1 , 2 si equipe 2
    char tabEquip1[9][120];
    char tabEquip2[9][120];
    char tabEquipe[9][120];
    int perso1 =-1, perso2 =-1, perso3 =-1; 
    bool perso1IsDead = false,perso2IsDead = false,perso3IsDead = false;
    char symbole[2];
    char tabDiez1[21];
    char tabDiez2[21];
    char tabDiez3[21];
    char infoPerso1[40];
    char infoPerso2[40];
    char infoPerso3[40];
    char attaque1[512];
    char attaque2[512];
    char ultime[512];
//int sprintf( char * buffer, const char *format, ... ); 
//int sprintf(chaine cible, "%-s %d", chaine source)

if(estAttaquant == 1){
    //vérifier si les attaques sont dispo
    sprintf(&attaque1[0], "|%d| %s ", 1, attaquant->attaque1-> descAttaque);
    if(attaquant->attaque2->dispo%2 ==0)
        sprintf(&attaque2[0], "|%d| %s ", 2, attaquant->attaque2 -> descAttaque);
    else 
     sprintf(&attaque2[0], "|-| %s ", attaquant->attaque2 -> descAttaque);
    
    if(attaquant->ultime->dispo%4 ==0)
    sprintf(&ultime[0],"|%d| %s ", 3, attaquant->ultime -> descAttaque);
    else 
     sprintf(&ultime[0],"|-| %s ", attaquant->ultime -> descAttaque);
   }
   
    for(int i =0; i<6; i++ ){
        if(perso[i].numEquipe == equipe && perso1 == -1){
            perso1 =i;
            if(perso[i].pv<=0){
                perso1IsDead = true;
                symbole[0] = 'X';
                symbole[1] = '\0';
                tabDiez1[0]= '\0';
            }
            else if(perso[i].pv<5){
                sprintf(&symbole[0],"%d",i+1);
                tabDiez1[0] ='#';
                tabDiez1[1] = '\0';
            }
            else{
                sprintf(&symbole[0],"%d",i+1);
                for(int n=0; n<perso[i].pv/5 && n<20; n++){
                    tabDiez1[n] ='#';
                    tabDiez1[n+1] ='\0';
                }

            }
            sprintf(&infoPerso1[0], "%s [%s]", perso[i].nom_personnage,symbole);
        }  
        else if(perso[i].numEquipe == equipe && perso2 == -1){
            perso2 =i;
            if(perso[i].pv<=0){
                perso1IsDead = true;
                symbole[0] = 'X';
                symbole[1] = '\0';
                tabDiez2[0]= '\0';
            }
            else if(perso[i].pv<5){
                sprintf(&symbole[0],"%d",i+1);
                tabDiez2[0] ='#';
                tabDiez2[1] = '\0';
            }
            else{
                sprintf(&symbole[0],"%d",i+1);
                for(int n=0; n<perso[i].pv/5 && n<20; n++){
                    tabDiez2[n] ='#';
                    tabDiez2[n+1] ='\0';
                }

            }
        
        sprintf(&infoPerso2[0], "%s [%s]", perso[i].nom_personnage,symbole);    
        } 
        
        else if (perso[i].numEquipe == equipe && perso3 == -1) {
            perso3 =i;
            if(perso[i].pv<=0){
                perso1IsDead = true;
                symbole[0] = 'X';
                symbole[1] = '\0';
                tabDiez3[0]= '\0';
            }
            else if(perso[i].pv<5){
                sprintf(&symbole[0],"%d",i+1);
                tabDiez3[0] ='#';
                tabDiez3[1] = '\0';
            }
            else{
                sprintf(&symbole[0],"%d",i+1);
                for(int n=0; n<perso[i].pv/5 && n<20; n++){
                    tabDiez3[n] ='#';
                    tabDiez3[n+1] ='\0';
                }

            }
        sprintf(&infoPerso3[0], "%s [%s]", perso[i].nom_personnage,symbole);  
        }
        else ;
    }
    
    if(estAttaquant){
        printf("\n _[Equipe %d]_<< %-7s >>________________________________________________________________________\n", equipe,attaquant->nom_personnage);
        printf("|                                                                                                 |\n");  
        printf("|  %-20s            %-20s                 %-20s      |\n",&infoPerso1[0],&infoPerso2[0],&infoPerso3[0] );    
        printf("| [%-20s]          [%-20s]               [%-20s]     |\n",&tabDiez1[0],&tabDiez2[0],&tabDiez3[0] );          
        printf("|                                                                                                 |\n");  
        printf("|_________________________________________________________________________________________________|________________________\n");
        printf("| %-120s |\n",&attaque1[0]);
        printf("| %-120s |\n",&attaque2[0]); 
        printf("| %-120s |\n",&ultime[0]); 
        printf("|__________________________________________________________________________________________________________________________|\n"); 
    }  
   else{
        printf("\n _[Equipe %d]______________________________________________________________________________________\n", equipe);
        printf("|                                                                                                 |\n");  
        printf("|  %-20s            %-20s                 %-20s      |\n",&infoPerso1[0],&infoPerso2[0],&infoPerso3[0] );    
        printf("| [%-20s]          [%-20s]               [%-20s]     |\n",&tabDiez1[0],&tabDiez2[0],&tabDiez3[0] );            
        printf("|                                                                                                 |\n");  
        printf("|_________________________________________________________________________________________________|\n"); 
    }    
    
}
