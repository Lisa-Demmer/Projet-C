#include <stdio.h>
#include <stdlib.h>

struct Case{ //type permettant de connaitre la ligne et la colonne d'une case
    int x; // numéro de ligne
    int y; // numéro de colonne
};

struct Candidat{ //type permettant de compter le nombre de candidat et les candidats d'une case donnée
    int nbc; // nombre de candidats
    int tab[10]; // table des candidats
};

int candcol(struct Candidat **C,int j,int i, int chiffre){ //verifie si le chiffre est candidat de la colonne
int n,nb,can=1;
    for(n=0;n<9;n++){
      if(n==i)	continue;
        for(nb=1;nb<=C[n][j].nbc;nb++){
        if(C[n][j].tab[nb]==chiffre)
            can =0;
        }}
    return can;
}

int candligne(struct Candidat **C,int i,int j, int chiffre){   //verifie si le chiffre est candidat de la ligne
int n,nb,can=1;
    for(n=0;n<9;n++){
      if(n==j) continue ;
        for(nb=1;nb<=C[i][n].nbc;nb++){
        if(C[i][n].tab[nb]==chiffre)
            can=0;
        }}
    return can;
}
void Zone(int x, int y, int *min_l, int *max_l, int *min_c, int *max_c){    // Définit la zone 3*3 par rapport à notre emplacement
    int zone =(3*((x)/3)+((y)/3));
    switch(zone){
        case 0 : {*min_l=0;
            *max_l=3;
            *min_c=0;
            *max_c=3;};break;
        case 1 : {*min_l=0;
            *max_l=3;
            *min_c=3;
            *max_c=6;};break;
        case 2 : {*min_l=0;
            *max_l=3;
            *min_c=6;
            *max_c=9;};break;
        case 3 : {*min_l=3;
            *max_l=6;
            *min_c=0;
            *max_c=3;};break;
        case 4 : {*min_l=3;
            *max_l=6;
            *min_c=3;
            *max_c=6;};break;
        case 5 : {*min_l=3;
            *max_l=6;
            *min_c=6;
            *max_c=9;};break;
        case 6 : {*min_l=6;
            *max_l=9;
            *min_c=0;
            *max_c=3;};break;
        case 7 : {*min_l=6;
            *max_l=9;
            *min_c=3;
            *max_c=6;};break;
        case 8 : {*min_l=6;
            *max_l=9;
            *min_c=6;
            *max_c=9;};break;
    }
}

int candzone(struct Candidat **C,int i,int j,int chiffre){  //verifie si le chiffre est candidat de la ligne
int min_l, max_l,min_c,max_c,nb,l,c,can=1;
Zone(i,j, &min_l,&max_l,&min_c,&max_c);   //Appel de la fonction qui définie la zone ou l'on se situe
  for(l=min_l;l<max_l;l++){
    for(c=min_c;c<max_c;c++){
      if((l==i)&&(c==j)) continue;
        for(nb=1;nb<=C[l][c].nbc;nb++){
        if(C[l][c].tab[nb]==chiffre)
            can=0;}}}
    return can;
}


void lireGrille(int **G){   //Initialise la grille G avec le contenu du fichier .txt
    FILE* grille=NULL, *f_out;       // La grille ne contient que des 0(espaces vides)
    int i,j,k, noL,noC,nombre,verif=0;  //noL : numéro de la ligne et noC : numéro de la colonne
    for (j=0;j<9;j++){
    for (k=0;k<9;k++){
        G[j][k]=0;}}    //initialisation de la grille à 0
    grille = fopen("g1.txt", "r+");      // la variable grille prend le contenu du fichier .txt
    if (grille != NULL){
        for (i=0; verif!=EOF; i++){
            verif=fscanf(grille,"%d%d%d",&noL,&noC,&nombre);    //verif : vérifie si on est arrivé ou non à la fin du fichier
            G[noL][noC]=nombre;             // Remplit la grille avec les chiffres précisés dans le fichier .txt
             //verif : vérifie si on est arrivé ou non à la fin du fichier
        }
    }
    else if (grille == NULL){               //si grille est NULL alors la lecture du fichier à échouée
        printf("La lecture du fichier a échoué");
    }
    fclose(grille);
}

void ecrireGrille (int **G){  //Affiche la grille G à l'écran
  int i, j ;
  for (i=0;i<9;i++){
    for (j=0;j<9;j++){
      if ((G[i][j]<1)||(G[i][j]>9))
	printf("|  ");
      else printf("| %d",G[i][j]);
    }
    printf("|\n");
  }
}

int estcandidat (int **G, int i, int j,int chiffre) {  //la fonction retourne si le chiffre est candidat d'une case donnée
int n,l,c, min_l,max_l,min_c,max_c,can=1;
  for (n=0;n<=8;n++){
    if ((G[i][n]== chiffre) || (G[n][j]==chiffre))  //Vérifie ligne et colonne (Si le chiffre y est situé alors il n'est pas candidat)
      can=0;}
  Zone(i,j, &min_l,&max_l,&min_c,&max_c);   //Appel de la fonction qui définie la zone ou l'on se situe
 if(can==1){
  for(l=min_l;l<max_l;l++){
    for(c=min_c;c<max_c;c++){
        if (G[l][c]==chiffre) //Vérifie la zone (Si le chiffre y est situé alors il n'est pas candidat
            can=0;}}}
            //printf("%d%d%d%d\n",can,chiffre,i,j); //teste si la fonction estcandidat fonctionne
            return can;}

void initTab (struct Case *O,struct Candidat **C, int **G){ //Initialise les tables C et O
  int i,j,NBO=0,chiffre,can=1;
  for (i=0;i<9;i++){
    for (j=0;j<9;j++){
      if(G[i][j] == 0){     // Si la case est ouverte la table O est initialisée
	C[i][j].nbc=0;
    //*(C[i][j]).tab=NULL;
	O[NBO].x =i;
	O[NBO].y =j;
	//printf("%d%d%d%d%d\n",O[NBO].x,O[NBO].y,NBO,i,j); //Test si la table O est bien initialisée
	NBO++;}
	else {C[i][j].nbc=-1;} //Si la case est fermée le nombre de candidat est initialisé à -1
	if (C[i][j].nbc==0){   //Si la case est ouverte la table C est initialisée
	  for(chiffre=1;chiffre<10;chiffre++){
	      can=estcandidat(G,i,j,chiffre);
              if (can==1){
                C[i][j].nbc+=1;
                C[i][j].tab[C[i][j].nbc]=chiffre;
                //printf("%d%d%d%d\n",C[i][j].tab[C[i][j].nbc],i,j,C[i][j].nbc); //test si la table C est bien initialisée
              }
            }}}}}

void ecrirecand(struct Candidat **C){       //Affiche les candidats à l'écran
    int i,j, nb;
    for (i=0;i<9;i++)
        for (j=0;j<9;j++){
            if(C[i][j].nbc>0){
            printf("nombre de candidat de la case %d,%d: %d - ",i,j, C[i][j].nbc);
            for(nb=1;nb<=C[i][j].nbc;nb++){
                printf(" %d", C[i][j].tab[nb]);}
            printf("\n");
        }}
}

int AdmetUnique(struct Candidat **C, int pos_x, int pos_y,int chiffre){ //Retourne 0 ou la valeur du candidat unique
    if (C[pos_x][pos_y].nbc==1)
        return C[pos_x][pos_y].tab[1];
    else if (candligne(C,pos_x,pos_y,chiffre)==1) //test si il est candidat de la ligne
        return chiffre;
    else if (candcol(C,pos_y,pos_x,chiffre)==1)   //test si il est candidat de la colonne
        return chiffre;
    else if (candzone(C,pos_x,pos_y,chiffre)==1)    //test si il est candidat de la zone
        return chiffre;
    else return 0;
}

void FermerCase(struct Candidat **C, int **G, struct Case *O, int x, int y, int val){ //Met le candidat unique dans la case et initialise les tables O et C
    G[x][y]=val; //la case prend la valeur (Car admet un unique candidat)
    C[x][y].nbc=-1; //le nombre de candidat est mis à 0 (Car admet un unique candidat)
    initTab(O,C,G); //Les tables O et C sont de nouveaux initialisées après avoir inséré les candidat unique dans la grille
}

void FermerGrille(struct Candidat **C, int **G, struct Case *O){ //Ferme la grille en testant chaque case si elles disposent d'un candidat unique
    int lig, col, val ,nb,chiffre;
    for (lig=0;lig<9;lig++)
        for (col=0;col<9;col++)
            for(nb=1;nb<=C[lig][col].nbc;nb++){
            chiffre=C[lig][col].tab[nb];
                if (AdmetUnique(C, lig, col,chiffre)!=0){  //si la case admet un unique candidat, il fait appel à FermerCase
                    val=AdmetUnique(C, lig, col,chiffre);
                    //printf("%d",val);   //test si admetunique retourne des valeurs cohérentes
                    FermerCase(C, G, O, lig, col, val);
                    }}
    }

int main() {
  int i,j,sol, ligne=9, col=9,test;
/*Initialisation de la table G*/
  int **G=malloc(sizeof(*G)*ligne);
  for (i=0;i<ligne;i++)
    G[i]=malloc(sizeof(**G)*col);
/*----------------------------*/
  struct Case O[81];
/*Initialisation de la table C*/
  struct Candidat **C=malloc(sizeof(*C)*ligne);
  for (i=0;i<ligne;i++)
    C[i]=malloc(sizeof(**C)*col);
/*----------------------------*/
  lireGrille(G);
  ecrireGrille(G);
  printf("\n");
  initTab(O,C,G);
  ecrirecand(C);
  printf("\n");
  FermerGrille(C,G,O);
  ecrirecand(C);

  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
    if(C[i][j].nbc>=0) //Parcourt la table, si une case est ouverte, lance la fonction qui ferme la grille
    FermerGrille(C,G,O);}}
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
    if(C[i][j].nbc>=0){ //Si il reste des candidats, la grille n'a pas pu être résolue entièrement par la méthode des candidats uniques
        sol=0;}}}
  ecrireGrille(G);

  ecrirecand(C);
  printf("\n");
  if (sol==0)
    printf("Il n'y a plus de candidat unique :/\nLa grille n'a pas pu etre resolue :(\n");
  else printf("La grille a ete resolue ! :)\n");
	return 0;
}
