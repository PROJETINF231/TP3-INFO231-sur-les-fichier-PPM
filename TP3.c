#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* =======================================================
   STRUCTURES ET DEFINITIONS
   ======================================================= */

typedef struct {
    int r, g, b;  // Composantes de couleur
} Pixel;

typedef struct {
    char version[3];
    int largeur;
    int hauteur;
    int max_val;
    Pixel **pixels;
} ImagePPM;

/* =======================================================
   FONCTIONS DE BASE : LECTURE & ECRITURE DE FICHIERS PPMApplication de traitement d'images PPM realisee par Sasuke.
ppmviewer > size image1.ppm
Erreur : impossible d'ouvrir le fichier image1.ppm

   ======================================================= */

// Lecture d'une image PPM au format P3
ImagePPM* lirePPM(const char* nomFichier) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return NULL;
    }

    ImagePPM* img = malloc(sizeof(ImagePPM));

    // Lecture de l'en-tête
    fscanf(f, "%s", img->version);
    if (strcmp(img->version, "P3") != 0) {
        printf("Format non supporté (seul P3 est accepté)\n");
        fclose(f);
        free(img);
        return NULL;
    }

    // Ignorer les commentaires (# ...)
    char c = fgetc(f);
    while (c == '#') {
        while (fgetc(f) != '\n');
        c = fgetc(f);
    }
    ungetc(c, f);

    fscanf(f, "%d %d %d", &img->largeur, &img->hauteur, &img->max_val);

    // Allocation du tableau 2D
    img->pixels = malloc(img->hauteur * sizeof(Pixel*));
    for (int i = 0; i < img->hauteur; i++)
        img->pixels[i] = malloc(img->largeur * sizeof(Pixel));

    // Lecture des pixels
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            fscanf(f, "%d %d %d", &img->pixels[i][j].r,
                                  &img->pixels[i][j].g,
                                  &img->pixels[i][j].b);
        }
    }

    fclose(f);
    return img;
}

// Sauvegarde d'une image PPM
void ecrirePPM(ImagePPM* img, const char* nomFichier) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur : impossible de créer le fichier %s\n", nomFichier);
        return;
    }

    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n%d\n", img->largeur, img->hauteur, img->max_val);

    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            fprintf(f, "%d %d %d ",
                img->pixels[i][j].r,
                img->pixels[i][j].g,
                img->pixels[i][j].b);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

/* =======================================================
   OPERATIONS DE TRAITEMENT
   ======================================================= */

// 1️⃣ Foncer ou éclaircir selon la couleur dominante
void dom(ImagePPM* img, char couleur, int val) {
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel* p = &img->pixels[i][j];
            int max = p->r;
            char dom = 'R';
            if (p->g > max) { max = p->g; dom = 'G'; }
            if (p->b > max) { max = p->b; dom = 'B'; }

            if (dom == couleur) {
                p->r = fmin(255, fmax(0, p->r + val));
                p->g = fmin(255, fmax(0, p->g + val));
                p->b = fmin(255, fmax(0, p->b + val));
            }
        }
    }
}

// 2️⃣ Niveaux de gris
void gris(ImagePPM* img) {
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel* p = &img->pixels[i][j];
            int m = (p->r + p->g + p->b) / 3;
            p->r = p->g = p->b = m;
        }
    }
}

// 3️⃣ Négatif
void negatif(ImagePPM* img) {
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            img->pixels[i][j].r = 255 - img->pixels[i][j].r;
            img->pixels[i][j].g = 255 - img->pixels[i][j].g;
            img->pixels[i][j].b = 255 - img->pixels[i][j].b;
        }
    }
}

// 4️⃣ Afficher la taille
void afficher_taille(ImagePPM* img) {
    printf("%d x %d\n", img->largeur, img->hauteur);
}

// 5️⃣ Découper une image
ImagePPM* cut(ImagePPM* img, int l1, int l2, int c1, int c2) {
    if (l1 >= l2 || c1 >= c2 ||
        l2 > img->hauteur || c2 > img->largeur) {
        printf("Erreur : valeurs incorrectes pour le découpage.\n");
        return NULL;
    }

    ImagePPM* result = malloc(sizeof(ImagePPM));
    strcpy(result->version, img->version);
    result->max_val = img->max_val;
    result->hauteur = l2 - l1 + 1;
    result->largeur = c2 - c1 + 1;

    result->pixels = malloc(result->hauteur * sizeof(Pixel*));
    for (int i = 0; i < result->hauteur; i++)
        result->pixels[i] = malloc(result->largeur * sizeof(Pixel));

    for (int i = 0; i < result->hauteur; i++)
        for (int j = 0; j < result->largeur; j++)
            result->pixels[i][j] = img->pixels[l1 + i][c1 + j];

    return result;
}

/* =======================================================
   LIBERATION MEMOIRE
   ======================================================= */
void liberer(ImagePPM* img) {
    for (int i = 0; i < img->hauteur; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

/* =======================================================
   PROGRAMME PRINCIPAL (INTERFACE UTILISATEUR)
   ======================================================= */

int main() {
    printf("Application de traitement d'images PPM realisee par NOTRE GROUPE DE TP DE 6 ETUDIANTS.\n");
    char commande[50];

    while (1) {
        printf("ppmviewer > ");
        scanf("%s", commande);

        if (strcmp(commande, "quit") == 0) break;

        else if (strcmp(commande, "size") == 0) {
            char nom[100];
            scanf("%s", nom);
            ImagePPM* img = lirePPM(nom);
            if (img) {
                afficher_taille(img);
                liberer(img);
            }
        }

        else if (strcmp(commande, "gris") == 0) {
            char nom[100];
            scanf("%s", nom);
            ImagePPM* img = lirePPM(nom);
            if (img) {
                gris(img);
                strcat(nom, "_gris.ppm");
                ecrirePPM(img, nom);
                printf("opération effectuée ; %s créé\n", nom);
                liberer(img);
            }
        }

        else if (strcmp(commande, "neg") == 0) {
            char in[100], out[100];
            scanf("%s %s", in, out);
            ImagePPM* img = lirePPM(in);
            if (img) {
                negatif(img);
                ecrirePPM(img, out);
                printf("opération effectuée ; %s créé\n", out);
                liberer(img);
            }
        }

        else if (strcmp(commande, "dom") == 0) {
            char c, nom[100];
            int val;
            scanf(" %c %d %s", &c, &val, nom);
            ImagePPM* img = lirePPM(nom);
            if (img) {
                dom(img, c, val);
                strcat(nom, "_dom.ppm");
                ecrirePPM(img, nom);
                printf("opération effectuée ; %s créé\n", nom);
                liberer(img);
            }
        }

        else if (strcmp(commande, "cut") == 0) {
            char in[100], out[100];
            int l1, l2, c1, c2;
            scanf("%s %d %d %d %d %s", in, &l1, &l2, &c1, &c2, out);
            ImagePPM* img = lirePPM(in);
            if (img) {
                ImagePPM* part = cut(img, l1, l2, c1, c2);
                if (part) {
                    ecrirePPM(part, out);
                    printf("opération effectuée ; %s créé\n", out);
                    liberer(part);
                }
                liberer(img);
            }
        }

        else {
            printf("Commande inconnue.\n");
        }
    }

    printf("Fermeture du programme.\n");
    return 0;
}
