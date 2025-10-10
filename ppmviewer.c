#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    int r,g,b;
}pixels;
typedef struct{
    char format[2];
    int largeur,hauteur,max;
    pixels tab[255][255];
}images;
images img;
int max=255;
pixels Tab[100][100][3];
void generer_image(int largeur,int hauteur){
    images img;
    FILE *file=fopen("image.ppm","w");
    if(file==NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    int max =255;
    fprintf(file,"P3\n");
    fprintf(file,"#image genere par mon programme\n");
    fprintf(file,"%d %d\n",largeur,hauteur);
    fprintf(file,"%d\n",max);
    pixels Tab[largeur][hauteur][3];
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            Tab[j][i]->r=(j*255)/(hauteur-1);
            Tab[i][j]->g=(i*255)/(largeur-1);
            Tab[j][i]->b=(i+j)/2 +1;
        }
    }
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fprintf(file,"%d %d %d  ",Tab[i][j]->r,Tab[j][i]->g,Tab[j][i]->b);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Image (%dx%d) cree avec sucess!!\n",largeur,hauteur);
}
void largeur_hauteur(FILE *fichier){
    images img;
    char c,ligne[255],hauteur[10];
    int cmpt_ligne=0,i,j=0,l,h,n=0;
    fgets(ligne,sizeof(ligne),fichier);
    do{
        fgets(ligne,sizeof(ligne),fichier);
    }while(ligne[0]=='#');
    sscanf(ligne,"%d%d",&l,&h);
        fgetc(fichier);
        img.largeur=l;
        img.hauteur=h;
       printf("%d x %dpx\n",l,h);
}
void foncer_eclaicir(FILE *ficher,int val,char c[1],int largeur,int hauteur){
    FILE *f=fopen("image.ppm","r");
    if(!f){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    int max =255;
    fscanf(f,"P3\n");
    fscanf(f,"#image genere par mon programme\n");
    fscanf(f,"%d %d\n",&largeur,&hauteur);
    fscanf(f,"%d\n",&max);
    pixels Tab[largeur][hauteur][3];
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fscanf(f,"%d %d %d  ",&Tab[i][j]->r,&Tab[j][i]->g,&Tab[j][i]->b);
        }
    }
    fclose(f);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
           // if(strcmp(c,'r')==0 || strcmp(c,'g')==0 || strcmp(c,'b')==0){
            if(Tab[i][j]->r > Tab[j][i]->g && Tab[i][j]->r > Tab[j][i]->b){
                Tab[i][j]->r =Tab[i][j]->r +val;
            }else if(Tab[j][i]->g > Tab[i][j]->r && Tab[j][i]->g > Tab[j][i]->b){
                Tab[j][i]->g =Tab[j][i]->g +val;
            }else{
                Tab[j][i]->b=Tab[j][i]->b+val;
            }
       // }
        }
    }
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            if(Tab[i][j]->r >max ||Tab[j][i]->g >max ||Tab[j][i]->b>max){
                Tab[i][j]->r =Tab[j][i]->g =Tab[j][i]->b=max;
            }
            if(Tab[i][j]->r <0 ||Tab[j][i]->g <0 ||Tab[j][i]->b<0){
                Tab[i][j]->r =Tab[j][i]->g =Tab[j][i]->b=0;
            }
        }
    }
    FILE *file=fopen("Image_dom.ppm","w");
    fprintf(file,"P3\n");
    fprintf(file,"#image genere par mon programme\n");
    fprintf(file,"%d %d\n",largeur,hauteur);
    fprintf(file,"%d\n",max);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fprintf(file,"%d %d %d  ",Tab[i][j]->r,Tab[j][i]->g,Tab[j][i]->b);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Image_dom cree avec succes!!!\n");
    printf("\nOperation effectuee!");
}
void gris(FILE *fichier,int largeur,int hauteur){
    FILE *f=fopen("image.ppm","r");
    if(!f){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    int max =255;
    fscanf(f,"P3\n");
    fscanf(f,"#image genere par mon programme\n");
    fscanf(f,"%d %d\n",&largeur,&hauteur);
    fscanf(f,"%d\n",&max);
    pixels Tab[largeur][hauteur][3];
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fscanf(f,"%d %d %d  ",&Tab[i][j]->r,&Tab[j][i]->g,&Tab[j][i]->b);
        }
    }
    fclose(f);
    int gris=0;
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            gris+=(Tab[i][j]->r+Tab[j][i]->g+Tab[j][i]->b)/3;
            Tab[i][j]->r =Tab[j][i]->g =Tab[j][i]->b=gris;
            gris=0;
        }
    }
    FILE *file=fopen("Image_gris.ppm","w");
    fprintf(file,"P3\n");
    fprintf(file,"#image genere par mon programme\n");
    fprintf(file,"%d %d\n",largeur,hauteur);
    fprintf(file,"%d\n",max);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fprintf(file,"%d %d %d  ",Tab[i][j]->r,Tab[j][i]->g,Tab[j][i]->b);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Image_gris.ppm cree avec succes!!!\n");
    printf("\nOperation effectue");
}
void negatif(FILE *fichier,int largeur,int hauteur){
    FILE *f=fopen("image.ppm","r");
    if(!f){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    int max =255;
    fscanf(f,"P3\n");
    fscanf(f,"#image genere par mon programme\n");
    fscanf(f,"%d %d\n",&largeur,&hauteur);
    fscanf(f,"%d\n",&max);
    pixels Tab[largeur][hauteur][3];
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fscanf(f,"%d %d %d  ",&Tab[i][j]->r,&Tab[j][i]->g,&Tab[j][i]->b);
        }
    }
    fclose(f);
    int gris=0;
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            Tab[i][j]->r =max-Tab[i][j]->r;
            Tab[j][i]->g =max-Tab[j][i]->g;
            Tab[j][i]->b=max-Tab[j][i]->b;
        }
    }
    FILE *file=fopen("Image3.ppm","w");
    fprintf(file,"P3\n");
    fprintf(file,"#image genere par mon programme\n");
    fprintf(file,"%d %d\n",largeur,hauteur);
    fprintf(file,"%d\n",max);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fprintf(file,"%d %d %d  ",Tab[i][j]->r,Tab[j][i]->g,Tab[j][i]->b);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Image en negatif avec succes!!!\n");
}
void couper(FILE *fichier,int largeur,int hauteur,int l1,int l2,int c1,int c2){
    FILE *f=fopen("image.ppm","r");
    fscanf(f,"P3\n");
    fscanf(f,"#image genere par mon programme\n");
    fscanf(f,"%d %d\n",&largeur,&hauteur);
    fscanf(f,"%d\n",&max);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            fscanf(f,"%d %d %d  ",&Tab[i][j]->r,&Tab[j][i]->g,&Tab[j][i]->b);
        }
    }
    fclose(f);
    FILE *file=fopen("Image_resultat.ppm","w");
    fprintf(file,"P3\n");
    fprintf(file,"#image genere par mon programme\n");
    fprintf(file,"%d %d\n",largeur,hauteur);
    fprintf(file,"%d\n",max);
    for(int i=l1;i<l2;i++){
        for(int j=c1;j<c2;j++){
            fprintf(file,"%d %d %d  ",Tab[i][j]->r,Tab[j][i]->g,Tab[j][i]->b);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Image couper avec succes!!!\n");
}
void filtre_median(FILE *fichier){
    pixels temp[255][255][3];
    for(int i=0;i<img.hauteur;i++){
        for(int j=0;j<img.largeur;j++){
            if(Tab[i][j]->r>Tab[i+1][j+1]->r){
                temp[i][j] ->r=Tab[i][j]->r;
                Tab[i][j]->r=Tab[i+1][j+1]->r;
                Tab[i+1][j+1]->r=temp[i][j]->r;
            }
            if(Tab[i][j]->g>Tab[i+1][j+1]->g){
                 temp[i][j]->r=Tab[i][j]->r;
                Tab[i][j]->g=Tab[i+1][j+1]->g;
                Tab[i+1][j+1]->g=temp[i][j]->g;
            }
            if(Tab[i][j]->b>Tab[i+1][j+1]->b){
                 temp[i][j]->r=Tab[i][j]->r;
                Tab[i][j]->b=Tab[i+1][j+1]->b;
                Tab[i+1][j+1]->b=temp[i][j]->b;
            }
        }
    }
    for(int i=0;i<img.hauteur;i++){
        for(int j=0;j<img.largeur;j++){
            for(int k=0;k<9;k++){
                
            }
        }
    }
}
int main(){
    FILE *f=fopen("image.ppm","r");
  /* int largeur,hauteur,v,l1,l2,c1,c2;
    char c;
    FILE *f=fopen("image.ppm","r");
    printf("entrez la largeur de votre image\t");
    scanf("%d",&largeur);
    printf("\nentrez la hauteur de votre image\t");
    scanf("%d",&hauteur);
    generer_image(largeur,hauteur);
    printf("entrez la valeur a ajouter:\t");
    scanf("%d",&v);
    foncer_eclaicir(f,v,c,largeur,hauteur);
    gris(f,hauteur,largeur);
    negatif(f,largeur,hauteur);
    filtre_median(f);
    largeur_hauteur(f);
    do{
        printf("valeurs des lignes\t");
        scanf("%d%d",&l1,&l2);
        printf("valeurs des colonnes\t");
        scanf("%d%d",&c1,&c2);
    }while(l1>l2 &&l2>hauteur &&c1>c2 &&c2>largeur);
    couper(f,largeur,hauteur,l1,l2,c1,c2);
    */

    char commande[200];
    char c[1],elem_commande1[50], nom_fichier[100], nom_fichier_resultat[100];
    int  val, l1, l2, c1, c2,hauteur,largeur;
    int arguments_commande0,arguments_commande1, arguments_commande2, arguments_commande3, arguments_commande4,arguments_commande5,arguments_commande6,arguments_commande7,arguments_commande8;

    system("clear");
    printf("\n\n");
    printf("\t****WELCOME DEAR USER****\n");

    do{
        printf("PPMVIEWER> ");
        if(fgets(commande, sizeof(commande),stdin) == NULL){
            printf("\nErreur lors de la lecture de la commande!\n\n");
            return 1;
        }
    
        commande[strcspn(commande,"\n")] = 0;
    
        arguments_commande0 = sscanf(commande, "%s", elem_commande1);
        arguments_commande1 = sscanf(commande, "%s %s %d %s", elem_commande1, c, &val, nom_fichier);
        arguments_commande2 = sscanf(commande, "%s %s", elem_commande1,nom_fichier);
        arguments_commande3 = sscanf(commande, "%s %s", elem_commande1,nom_fichier);
        arguments_commande4 = sscanf(commande, "%s %s %d %d %d %d %s",elem_commande1,nom_fichier,&l1,&l2,&c1,&c2,nom_fichier_resultat);
        arguments_commande5 = sscanf(commande, "%s %s %s",elem_commande1,nom_fichier,nom_fichier_resultat);
        arguments_commande6 = sscanf(commande, "%s %s %s",elem_commande1,nom_fichier,nom_fichier_resultat);
        arguments_commande7 = sscanf(commande, "%s", elem_commande1);
        arguments_commande8 = sscanf(commande, "%s", elem_commande1);
    
        if(arguments_commande1 == 4 && strcmp(elem_commande1,"dom")==0){
            foncer_eclaicir(f,val,c,largeur, hauteur);
            printf("\ncommande 1 succès!\n\n");
        }
        else if(arguments_commande2 == 2 && strcmp(elem_commande1,"gris")==0){
            gris(f, largeur, hauteur);
            printf("\ncommande 2 succès!\n");
        }
        else if(arguments_commande3 == 2 && strcmp(elem_commande1,"size")==0){
            largeur_hauteur(f);
            printf("\ncommande 3 succès!\n");
        }
        /*else if(arguments_commande4 == 7 && strcmp(elem_commande1,"cut")==0){
            printf("\ncommande 4 succès!\n");
        }
        else if(arguments_commande5 == 3 && strcmp(elem_commande1,"neg")==0){
            printf("\ncommande 2 succès!\n");
        }
        else if(arguments_commande5 == 3 && strcmp(elem_commande1,"fil")==0){
            printf("\ncommande 6 succès!\n");
        }
        else if(arguments_commande0 == 1 && strcmp(elem_commande1,"quit")==0){
            break;
        }*/
        else if(arguments_commande7 == 1 && strcmp(elem_commande1,"help")==0){
            printf("\n\tLISTE DES COMMANDES:\n\n");
            printf("\t quit\n");
            printf("\t clear\n");
            printf("\t dom c val fichier.ppm\n");
            printf("\t gris fichier.ppm\n");
            printf("\t size fichier.ppm\n");
            printf("\t cut fichier.ppm l1 l2 c1 c2 fichier_resultat.ppm\n");
            printf("\t neg fichier.ppm fichier_resultat.ppm\n");
            printf("\t fil fichier.ppm fichier_resulata.ppm\n\n");
        }
        else if(arguments_commande8 == 1 && strcmp(elem_commande1,"clear")==0){
            system("clear");
        }
        else{
            printf("\nCommand not found, type 'help' to list commands!!!\n\n");
        }
    }while(strcmp(elem_commande1,"quit")!=0);
    return 0;
}