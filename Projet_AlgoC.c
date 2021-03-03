#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#define VMIN 5
#define VMAX 9
#define taille 100
#define TRUE 1
#define FALSE 0


//--------------------Structure----------------------//

typedef struct T_case
{
int x;
int y;
}T_case;

typedef T_case T_Tab_Case;

/* ------------------ Fonction --------------------*/
void Parametres(int *nlig, int *ncol, int *niveau, int *next, int *joueur_joue);

int max(int a, int b);

void Hasard_Ban(T_Tab_Case ban[],int nlig,int ncol,int *nban);

void nimb(int nimber[taille][taille],int nlig,int ncol);

int hasard_coup(int num);

/*----------------- Programme Principal ----------------------*/

int main()
{
    int nbgagne=0,nbperdu=0,ratio=0,nbpartie=0,rejoue;
    do{
    /*Intialisation variable, tableau...*/
   int nlig,ncol,niveau,next,nban,joueur_joue;      // variable paramettres
   int i,j,rep,tab,a=1,num;                         //variables d'iterration
   int X,repbot=0,ban1,blok_rep;                    // variables booleen
   int x,y;                                         // variables coordonnees
   struct T_case pion={x,y};                        /*initialisation des tables et structure */
   T_Tab_Case ban[taille];
   int nimber[taille][taille];
   srand((unsigned int)time(NULL));

   pion.x=pion.y=1;
   Parametres(&nlig,&ncol,&niveau,&next,&joueur_joue);
   Hasard_Ban(ban,nlig,ncol,&nban);
   nimb(nimber,nlig,ncol);

   //for(i=0;i<nban;i++) printf("ban[%d].x=%d    ban[%d].y=%d\n",i,ban[i].x,i,ban[i].y);
   do{
   /*--------------------------Création de l'affichage----------------------------------*/
     // printf("x=%d  y=%d\n",pion.x,pion.y);
      printf(" ");
      for(i=1;i<=ncol;i++)
         printf(" %d",i);                                       //numérotation de la grille
      printf("\n");
      for(i=1;i<=nlig;i++)
      {
         printf("%d|",a);                                       //numérotation de la grille
         for(j=1;j<=ncol;j++)
         {
            if((i==pion.x)&&(j==pion.y))                        //Affiche pion
               printf("0|");
            else{
                for(tab=0;tab<nban;tab++)
                if((i==(ban[tab].x))&&(j==(ban[tab].y))) X=1;   // affiche cases bannies
                if(X==1) printf("X|");
                else printf("-|");
                }
            X=0;                                                // X = booléen ; détermine si il y a une case bannie ou non
         }
         printf("\n");
         a=a+1;
      }

      a=1;
        //printf("x= %d  y=%d",pion.x,pion.y);
       /*------------------------------------Selection du mouvement----------------------------------------*/

    //=======Les Choix=======//
    num=1;
    blok_rep=0;
    ban1=0;
      printf("\n Saisir la destination : ");
                                                                                    ////
      for(tab=0;tab<nban;tab++){                                                    //     Verification si case ban + si limite
        if(((ban[tab].x)==(pion.x))&&((pion.y+1)==(ban[tab].y))){ blok_rep=1;       //
        ban1=1;}}                                                                   //       //Déplacement de 1 vers la Droite//
      if ((pion.y+1 <= ncol)&&(blok_rep==0)){                                       //
         printf(" %d:(%d,%d)",num,pion.x,pion.y+1);                                 //
         if((nimber[pion.x][pion.y+1])==0) repbot=num;                              //
         num=num+1;}                                                                //
      blok_rep=0;                                                                   ////

                                                                             ////
      for(tab=0;tab<nban;tab++)                                              //
        if(((ban[tab].x)==(pion.x))&&((ban[tab].y)==(pion.y+2))) blok_rep=1; //                                                    //
      if ((pion.y+2 <= ncol)&&(blok_rep==0)&&(ban1==0)){                     //     //Deplacement de 2 vers la droite//
         printf(" %d:(%d,%d)",num,pion.x,pion.y+2);                          //           si pas de case ban avant
         if((nimber[pion.x][pion.y+2])==0) repbot=num;                       //
         num=num+1;}                                                         //
      blok_rep=0;                                                            //
      ban1=0;                                                                ////

                                                                             ////
      for(tab=0;tab<nban;tab++)                                              //
        if(((ban[tab].x)==(pion.x+1))&&((ban[tab].y)==(pion.y))){ blok_rep=1;//
        ban1=1;}                                                             //     //Déplacement de 1 vers le bas//
      if ((pion.x+1 <= nlig)&&(blok_rep==0)){                                //
         printf(" %d:(%d,%d)",num,pion.x+1,pion.y);                          //
         if((nimber[pion.x+1][pion.y])==0) repbot=num;                       ////
         num=num+1;}
      blok_rep=0;

                                                                             ////
      for(tab=0;tab<nban;tab++)                                              //
        if(((ban[tab].x)==(pion.x+2))&&((ban[tab].y)==(pion.y))) blok_rep=1; //
      if ((pion.x+2 <= nlig)&&(blok_rep==0)&&(ban1==0)){                     //     //Déplacement de 2 vers le bas//
         printf(" %d:(%d,%d)",num,pion.x+2,pion.y);                          //
         if((nimber[pion.x+1][pion.y])==0) repbot=1;                         //
         num=num+1;}                                                         ////
      blok_rep=0;
      ban1=0;

      printf("\n");



      /*------------------------------Cette partie gère la reponse su bot mais aussi la notre--------------------------------------------------*/

      switch(niveau){

   case 1:{
       if (joueur_joue==FALSE){                               //On a créer un boolean grâce au macro afin de gérer qui de l'ordinateur ou du joueur doit jouer à un instant T
      do{
         scanf("%d",&rep);                                    // si il est faux alors c'est nous qui jouons
      }
      while(rep>=num);
            joueur_joue=TRUE;                                //enfin nous le passons à vrai pour que l'odinateur puisse jouer à son tour
}

        else if(joueur_joue=TRUE)
 {         do{
             rep=hasard_coup(num)+1;                        //On se trouve au premier niveau l'ordinateur ne peut jouer que au hasard
            }while(rep>=num);
                printf("l'ordinateur a joue...\n");
                joueur_joue=FALSE;}                         //On le passe à Faux pour redonner la main au joueur

}break;
/*__________________________________________________________________________________________________________________________________________________*/
   case 2:{
         if (joueur_joue==FALSE){
       do{                                            //Meme principe
         scanf("%d",&rep);
      }
      while(rep>=num);
            joueur_joue=TRUE;
   }

        else if(joueur_joue=TRUE){
                if ((rand()%2==2)){                  //Par contre nous gérons des probabilités donc on fait une triple condition celle ci gère la probas de coup_gagnant
                        if (repbot!=0){              //si elle est verifier alors on regarde si il y a possibilité de jouer un coup_gagnant
                printf("l'ordinateur à joué \n");
                rep=repbot;
                joueur_joue=FALSE;
                }}
             else                                   // sinon dans les deux cas si la condition n'est pas verifié alors on joue aléatoire
{               do{
             rep=hasard_coup(num)+1;
            }while(rep>=num);
            printf("%d\n",rep);
                printf("l'ordinateur a joue... \n");
                joueur_joue=FALSE;
                }}

}
break;
/*__________________________________________________________________________________________________________________________________________________*/
   case 3:{
        if (joueur_joue==FALSE){
       do{
         scanf("%d",&rep);
      }
      while(rep>=num);
            joueur_joue=TRUE;                           //Meme principe que la 2 avec une proba plus grande
   }

        else if(joueur_joue=TRUE){
                if (((rand()%2)+1)==2){
                        if (repbot!=0){
                printf("l'ordinateur à joué \n");
                rep=repbot;
                joueur_joue=FALSE;
                }}
             else
{                 do{
             rep=hasard_coup(num)+1;
            }while(rep>=num);
                printf("l'ordinateur a joue... \n");
                joueur_joue=FALSE;
                }}

  }break;

/*__________________________________________________________________________________________________________________________________________________*/
   case 4:{if (joueur_joue==FALSE){
      do{
         scanf("%d",&rep);
      }
      while(rep>=num);
            joueur_joue=TRUE;
}

         else if(joueur_joue=TRUE){

            if (repbot!=0){
                printf("l'ordinateur à joué \n");                   //Dans tous les cas y joue gagnant si c'est possible
                rep=repbot;
                joueur_joue=FALSE;
                }
             else

{                do{
             rep=hasard_coup(num);
            }while(rep>=num-1);
                printf("l'ordinateur a joue... A votre tour...\n");     //Sinon y joue au hasard
                joueur_joue=FALSE;
                }}
}break;
      }

   /*  ----------------------------------------------------------------------------------------------------- */
/*----La reponce--- */
      num=1;//non_conforme=1;

      for(tab=0;tab<nban;tab++)
        if(((ban[tab].x)==(pion.x))&&((ban[tab].y)==(pion.y+1))){ blok_rep=1;       /////
        ban1=1;}                                                                    //
      if ((pion.y+1 <= ncol)&&(blok_rep==0)){                                       //      On utilise le meme pricipe que pour choisir la destination
         if(rep==num) pion.y=pion.y+1;                                              //          sauf que l'on affiche rien mais on modifie les coordonnees
         num=num+1;}                                                                //          du pion quand la reponce == num
      blok_rep=0;                                                                   /////


      for(tab=0;tab<nban;tab++)
        if(((ban[tab].x)==(pion.x))&&((ban[tab].y)==(pion.y+2))) blok_rep=1;
      if ((pion.y+2 <= ncol)&&(blok_rep==0)&&(ban1==0)){
         if(rep==num) pion.y=pion.y+2;
         num=num+1;}
      blok_rep=0;
      ban1=0;

      for(tab=0;tab<nban;tab++)
        if(((ban[tab].x)==(pion.x+1))&&((ban[tab].y)==(pion.y))){ blok_rep=1;       //
        ban1=1;}
      if ((pion.x+1 <= nlig)&&(blok_rep==0)){
         if(rep==num) pion.x=pion.x+1;
         num=num+1;}
      blok_rep=0;

      for(tab=0;tab<nban;tab++)
        if(((ban[tab].x)==(pion.x+2))&&((ban[tab].y)==(pion.y))) blok_rep=1;
      if ((pion.x+2 <= nlig)&&(blok_rep==0)&&(ban1==0)){
         if(rep==num) pion.x=pion.x+2;
         num=num+1;}
      blok_rep=0;
      ban1==0;


   }while((pion.x!=nlig)||(pion.y!=ncol));
   /* Un message s'affichera pour présenter le gagnant, cette partie gère aussi le partie statistique des parties jouer */
    printf("La partie est gagne par :");
    if (joueur_joue==0){
            nbperdu+=1;
            printf("l'ordinateur \n");}

    else if (joueur_joue==1){
              printf("Vous, felicitation \n");
              nbgagne+=1;
}
    nbpartie+=1;
    ratio=nbgagne/nbpartie;
   /* La partie ci dessous va gérer si oui ou nous le joueur veut jouer une nouvelle partie*/

printf("vous avez jouer %d partie...\n Partie gagné: %d \n Partie perdu: %d \n votre ratio: %d",nbpartie,nbgagne,nbperdu,ratio);
printf("voulez vous rejouer ? (Oui=1/N=2)\n");
scanf("%d",&rejoue);
}
while(rejoue!=2);
}






/* ------------------Definition des Fonction -----------------------*/

//Fonction Paramettre://
void Parametres(int *nlig, int *ncol, int *niveau, int *next, int *joueur_joue)

{
    printf("************************************************ \n Les règles du jeu sont simple, une grille vous sera affichez avec la taille de votre choix\n Il vous suffira de deplacer le pion suivant les proposition generer,\n Attention certaines des cases sont bannies et ne peuvent etre sauter \n Le premier qui deplace le pion dans le puits à gagne \n NB: Vous vous opposez a l'ordinteur qui propose different niveau,\n Allant du plus facile au plus dure Bonne chance \n ************************************************ \n\n \n ");
   do{
      printf("Saisir qui joue en premier 1 pour l'ordinateur et 0 pour vous\n");
      scanf("%d",joueur_joue);
   }
   while((*joueur_joue<0)||(*joueur_joue>1));

   do{
      printf("Saisir un nombre de ligne superieur a %d et inferieur a %d :\n", VMIN,VMAX);
      scanf("%d",nlig);
   }
   while((*nlig<VMIN)||(*nlig>VMAX));

   do{
      printf("Saisir un nombre de colonne superieur a %d et inferieur a %d :\n", VMIN,VMAX);
      scanf("%d",ncol);
   }
   while((*ncol<VMIN)||(*ncol>VMAX));

   do{
      printf("Saisir le niveau de diffiulte : (1/2/3/4)\n");
      scanf("%d",niveau);
   }
   while((*niveau<1)||(*niveau>4));

   srand((unsigned int)time(NULL));
   *next=rand()%2+1;
}

//Fonction Hasard_Ban //
void Hasard_Ban(T_Tab_Case ban[],int nlig,int ncol,int *nban){
   int i,j;
   int ban_x,ban_y;
   int non1,non_puit,non_diag,non_conforme;
   srand((unsigned int)time(NULL));
   *nban=rand()%(max(nlig,ncol)+1);
   for(i=0;i<*nban;i++){

      non_conforme=1;                       // non_conforme permet de changer les coordonnes d'une case_ban si elle pose probleme
      do{
         non_conforme=0;
         ban_x=(rand()%(max(nlig,ncol)))+1;
         ban_y=(rand()%(max(nlig,ncol)))+1;
         ban[i].x=ban_x;
         ban[i].y=ban_y;
         if(((ban[i].x==1)&&(ban[i].y==1))||((ban[i].x==nlig)&&(ban[i].y==ncol))) non_conforme=1;       /////
         else if((ban[i].x==1)||(ban[i].y==1)||(ban[i].x==nlig)||(ban[i].y==ncol)) non_conforme=1;      //
         for(j=0;j<i;j++){                                                                              //    Condition pour le placement des cases bannies
            if(((ban[j].x)==(ban[i].x))&&((ban[j].y)==(ban[i].y))) non_conforme=1;                      //
            if(((ban[j].x)==(ban[i].x-1))&&((ban[j].y)==(ban[i].y+1))) non_conforme=1;                  //
            if(((ban[j].x)==(ban[i].x+1))&&((ban[j].y)==(ban[i].y-1))) non_conforme=1;                  /////
         }
      }while(non_conforme==1);
   }
}

//Fonction max//
int max(int a, int b){
if(a>b) return a;        //Nous aurions pu la mettre dans une macro mais nous y avons eu l'idée un peut tard
else return b;
}
//Fonction coup au hasard//
int hasard_coup(int num){
    int rep;
    srand((unsigned int)time(NULL));
         rep=(rand()%num);
         return rep;
}


//Fonction du nimber//
void nimb(int nimber[taille][taille],int nlig,int ncol){
int nb1,i,j;
for(j=ncol;j>0;j--){
    for(i=nlig;i>0;i--){
        if((i==nlig)&&(j==ncol)) nimber[i][j]=0;
        else if(j==ncol){                                                        //je fais une condition spéciale pour la dernière colonne
                if((nimber[i+1][j]==0)||(nimber[i+2][j]==0)) nimber[i][j]=1;
                else nimber[i][j]=0;}
        else if(i==nlig){                                                        //je fais une condition spéciale pour la dernière ligne
                if((nimber[i][j+1]==0)||(nimber[i][j+2]==0)) nimber[i][j]=1;
                else nimber[i][j]=0;}
        else
                if((nimber[i][j+1]==1)&&(nimber[i+1][j]==1)) nimber[i][j]=0;
                else nimber[i][j]=1;
            }
}
}

