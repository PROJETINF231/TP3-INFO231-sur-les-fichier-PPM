🎨 PPM Viewer – Projet de Traitement d’Images

Université de Yaoundé 1
Département d’Informatique – INF L2 (2025-2026)
Module : INF231 - Techniques de Conception d’Algorithmes et Structures de Données
Travail Pratique n°1 : Traitement d’images avec les fichiers et tableaux

👥 Équipe (TPE1)
Nom	Tâche principale
LONTSI TCHINDA ARTHUR	Foncer / Éclaircir selon la dominante
KENDO DJOSSEU CARELLE	Conversion en Niveaux de Gris + README
AMOUGOU FANJIP MAEVA	Création du Négatif
MEKOUDJA MENGAM DIANE	Interface CLI + Taille de l’image
NCHARE NJUTAP RONALD	Découpage d’image
FEZEU DOMGOUO BRAYAN	Application du Filtre Médian
🧩 Description du Projet

Ce projet implémente un visualiseur et éditeur d’images au format PPM (Portable PixMap), écrit en langage C.
Le programme fonctionne en ligne de commande (CLI) sous le nom PPMVIEWER, et permet de réaliser plusieurs opérations de traitement d’images non compressées.

📦 Structure des Données
typedef struct {
    int r, g, b;
} pixels;

typedef struct {
    char format[2];
    int largeur, hauteur, max;
    pixels tab[255][255];
} images;

⚙️ Fonctionnalités Principales
Fonction	Description
generer_image()	Génère une image de test avec dégradé
largeur_hauteur()	Affiche les dimensions d’une image
foncer_eclaicir()	Fonce ou éclaircit selon la couleur dominante
gris()	Convertit une image en niveaux de gris
negatif()	Crée le négatif d’une image
couper()	Découpe une portion spécifique
filtre_median()	Applique un filtre médian (lissage)
💻 Interface CLI

Au lancement :

****WELCOME DEAR USER****
PPMVIEWER>

🔧 Commandes Disponibles
Commande	Description
dom c val fichier.ppm	Fonce ou éclaircit selon la dominante (R, G ou B)
gris fichier.ppm	Conversion en niveaux de gris
neg fichier.ppm resultat.ppm	Crée le négatif
size fichier.ppm	Affiche les dimensions
cut fichier.ppm l1 l2 c1 c2 resultat.ppm	Découpe une zone
fil fichier.ppm resultat.ppm	Applique un filtre médian
help	Affiche la liste des commandes
clear	Efface l’écran
quit	Quitte l’application
🧠 Exemples d’Utilisation
PPMVIEWER> size image.ppm
100 x 205px

PPMVIEWER> dom R 50 image.ppm
Image_dom.ppm cree avec succes!!!

PPMVIEWER> gris image.ppm
Image_gris.ppm cree avec succes!!!

PPMVIEWER> neg image.ppm resultat.ppm
Image en negatif avec succes!!!

PPMVIEWER> help
LISTE DES COMMANDES:
 quit
 clear
 dom c val fichier.ppm
 gris fichier.ppm
 size fichier.ppm
 cut fichier.ppm l1 l2 c1 c2 resultat.ppm
 neg fichier.ppm resultat.ppm
 fil fichier.ppm resultat.ppm

PPMVIEWER> quit

🧱 Compilation et Exécution
# Compilation
gcc ppmviewer.c -o ppmviewer

# Exécution
./ppmviewer

📁 Fichiers du Projet
Fichier	Description
ppmviewer.c	Code source principal
README.md	Documentation du projet
image.ppm	Fichier d’image d’exemple
🖼️ Fichiers Générés

Image_dom.ppm

Image_gris.ppm

Image3.ppm

Image_resultat.ppm

📸 Format PPM (P3 – ASCII)

Structure :

P3
# commentaire
largeur hauteur
valeur_max
r1 g1 b1  r2 g2 b2  ...


Exemple :

P3
# exemple d'image
4 4
255
3 8 25  0 0 0  0 0 0  15 0 15
0 0 0  0 15 7  0 0 0  255 0 18
0 0 0  0 0 0  0 15 7  0 0 0
15 0 15  0 0 0  0 0 0  66 0 4

⚠️ Contraintes et Limites

Taille maximale : 255 × 255 pixels

Format supporté : PPM P3 (ASCII) uniquement

Certaines fonctions lisent par défaut image.ppm

Améliorations possibles :

Support du format P6 (binaire)

Allocation dynamique (images plus grandes)

Meilleure gestion des fichiers d’entrée/sortie

🧪 Méthodologie

Développement modulaire

Tests individuels de chaque fonction

Intégration progressive dans l’interface

Gestion des erreurs (fichiers, paramètres, etc.)

📅 Informations Administratives

Date limite de dépôt : 🗓️ 10 Octobre 2025 à 20h00

Groupe : TPE1

Encadrant : Département d’Informatique – Université de Yaoundé 1

📚 Références

Spécification du format PPM – Adobe

Énoncé du TP : TP_Serie1.pdf

🏁 Conclusion

🎯 Le projet PPM Viewer démontre la maîtrise des structures de données, de la gestion de fichiers et du traitement d’images basique en langage C.
💡 Une base solide pour explorer le traitement d’images plus avancé (filtrage, histogrammes, convolution, etc.).
