🧾 README – Projet PPM Viewer (INF231 – Techniques de Conception d’Algorithmes & Structures de Données)
🎓 Université de Yaoundé I

Département d’Informatique – Niveau L2
Année académique : 2025–2026
Encadrant : Pr. Metatagia

🧠 1️⃣ Présentation du projet

Ce projet s’inscrit dans le cadre du cours INF231 – Techniques de Conception d’Algorithmes et Structures de Données.
Il consiste à développer en langage C une application de traitement d’images PPM (Portable PixMap) permettant d’effectuer différentes opérations de manipulation d’images en format P3.

Le programme fonctionne sous forme interactive à travers une invite de commande personnalisée :

ppmviewer >

🧩 2️⃣ Objectifs pédagogiques

Manipuler les fichiers textes et binaires en C.

Travailler avec des tableaux 2D et structures.

Appliquer les algorithmes de filtrage et de transformation d’images.

Savoir structurer un projet C complet (lecture, traitement, sauvegarde, interface).

Utiliser GitHub pour la collaboration et la version du code.

Travailler en group de 6 et un esprit d'equipe.

🖼️ 3️⃣ Le format d’image PPM (P3)

Une image PPM (version P3) est un fichier texte contenant :

P3
# Commentaire optionnel
largeur hauteur
valeur_maximale
R G B R G B R G B ...


Chaque pixel est défini par trois entiers (R, G, B) entre 0 et 255.

Exemple minimal :

P3
# Exemple 2x2
2 2
255
255 0 0   0 255 0
0 0 255   255 255 0

⚙️ 4️⃣ Fonctionnalités implémentées

Le programme prend en charge les commandes suivantes :

| Commande                                 | Description                                                                                     |
| ---------------------------------------- | ----------------------------------------------------------------------------------------------- |
| `size fichier.ppm`                       | Affiche la taille (largeur × hauteur) de l’image                                                |
| `gris fichier.ppm`                       | Convertit l’image en niveaux de gris                                                            |
| `neg fichier_in fichier_out`             | Crée le négatif d’une image                                                                     |
| `dom C val fichier.ppm`                  | Fonce/éclaircit les pixels dominants selon la couleur `C` (`R`, `G`, ou `B`) et la valeur `val` |
| `cut fichier_in l1 l2 c1 c2 fichier_out` | Découpe une sous-image entre les lignes/colonnes données                                        |
| `fil fichier_in fichier_out`             | Applique un filtre médian (à compléter)                                                         |
| `quit`                                   | Quitte le programme                                                                             |


💻 5️⃣ Compilation et exécution (Kali Linux)
🔹 Étape 1 : Compilation

Dans le terminal, placez-vous dans le dossier du projet :

cd /home/sasuke/TP_PPM/
gcc ppmviewer.c -o ppmviewer -lm

🔹 Étape 2 : Exécution

Lancez l’application :

./ppmviewer

🔹 Étape 3 : Utilisation

Exemple de session :

Application de traitement d’images PPM réalisée par Sasuke.
ppmviewer > size image1.ppm
100 x 205
ppmviewer > gris image1.ppm
opération effectuée ; image1.ppm_gris.ppm créé
ppmviewer > neg image1.ppm image2.ppm
opération effectuée ; image2.ppm créé
ppmviewer > quit
Fermeture du programme.

📂 6️⃣ Structure du projet
TP_PPM/
│
├── ppmviewer.c          # Code source principal
├── ppmviewer            # Programme compilé (exécutable)
├── README.md            # Fichier de description du projet
├── image1.ppm           # Exemple d'image d'entrée
└── mesimages/           # Dossier de sortie
    ├── image2.ppm
    ├── image2_dom.ppm
    ├── image3.ppm
    ├── image3_gris.ppm
    └── image4.ppm

🧰 7️⃣ Explications techniques

Structures utilisées :

typedef struct {
    int r, g, b;
} Pixel;

typedef struct {
    char version[3];
    int largeur, hauteur, max_val;
    Pixel **pixels;
} ImagePPM;


Principales fonctions implémentées :

lirePPM() : lecture d’un fichier PPM

ecrirePPM() : sauvegarde d’une image PPM

gris() : conversion en niveaux de gris

negatif() : génération du négatif

dom() : modification des pixels dominants

cut() : extraction d’une sous-image

afficher_taille() : affichage de la taille de l’image

filtre_median() : (à implémenter)

🧑‍💻 8️⃣ Auteurs et contribution
| Nom complet                                 | Rôle / Contribution                                                                          |
| ------------------------------------------- | -------------------------------------------------------------------------------------------- |
| **Nchare Roniald**                          | Développement du code principal, conception des fonctions de traitement, rédaction du README |
| *(Avec tout les memebres du groupe qui 
mon aider a comprendre le travail ou nous avons
travailler desous sans relache)*              
|ET aussi avec l'aide de ChatGPT               une IA qui nous a aider avec la comprehension et le deploiyement du code

🧠 9️⃣ Améliorations possibles

Implémentation complète du filtre médian (fonction fil()).

Ajout d’un module de chargement automatique des chemins.

Interface graphique minimale (GTK ou SDL).

Gestion du format P6 (binaire).

🧾 10️⃣ Licence et remerciements

Projet académique réalisé dans le cadre du cours INF231 à l’Université de Yaoundé I.
Utilisation libre à des fins pédagogiques uniquement.
Merci au Pr. Melatagia pour la supervision et le suivi pédagogique.
