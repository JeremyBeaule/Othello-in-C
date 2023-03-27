#include <stdio.h>
#include <string.h>

// structure représentant les données de chaque joueur
struct Joueur {
    char nom[20];
    int score;
    // autres données du joueur...
};

// structure représentant les données du jeu
struct Jeu {
    int tour;
    struct Joueur joueur1;
    struct Joueur joueur2;
    // autres données du jeu...
};

// fonction pour sauvegarder les données du jeu dans un fichier binaire
int sauvegarder_jeu(struct Jeu *jeu, const char *nom_fichier) {
    // ouvrir le fichier en écriture binaire
    FILE *fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier pour écrire\n");
        return 0;
    }

    // écrire les données du jeu dans le fichier
    fwrite(jeu, sizeof(struct Jeu), 1, fichier);

    // fermer le fichier
    fclose(fichier);

    printf("Jeu sauvegardé avec succès\n");
    return 1;
}

// fonction pour charger les données du jeu à partir d'un fichier binaire
int charger_jeu(struct Jeu *jeu, const char *nom_fichier) {
    // ouvrir le fichier en lecture binaire
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier pour lire\n");
        return 0;
    }

    // lire les données du jeu depuis le fichier
    fread(jeu, sizeof(struct Jeu), 1, fichier);

    // fermer le fichier
    fclose(fichier);

    printf("Partie chargée avec succès\n");
    return 1;
}

int main() {
    // créer une instance de la structure Jeu avec des données de test
    struct Jeu jeu = {
        1 /* tour */,
        { "Joueur 1", 0 /* score */ } /* joueur 1 */,
        { "Joueur 2", 0 /* score */ } /* joueur 2 */
        // autres données du jeu...
    };

    // sauvegarder le jeu
    sauvegarder_jeu(&jeu, "jeu.sav");

    // modifier les données du jeu pour simuler une nouvelle session
    jeu.tour = 2;
    strcpy(jeu.joueur1.nom, "Joueur A");
    jeu.joueur1.score = 10;
    strcpy(jeu.joueur2.nom, "Joueur B");
    jeu.joueur2.score = 5;

    // charger le jeu sauvegardé
    charger_jeu(&jeu, "jeu.sav");

    // afficher les données du jeu chargé
    printf("Tour : %d\n", jeu.tour);
    printf("Joueur 1 : %s, Score : %d\n", jeu.joueur1.nom, jeu.joueur1.score);
    printf("Joueur 2 : %s, Score : %d\n", jeu.joueur2.nom, jeu.joueur2.score);

    return 0;
}
