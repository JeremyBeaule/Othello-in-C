#include <stdio.h>

// structure représentant les données de la partie
struct Partie {
    int placement; //je ne sais pas quoi mettre comme donnée
};

int sauvegarder_partie(struct Partie *partie, const char *nom_fichier) {
    // ouvrir un fichier en écriture binaire
    FILE *fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier pour écrire\n");
        return 0;
    }

    // écrire les données de la partie dans le fichier
    fwrite(partie, sizeof(struct Partie), 1, fichier);

    // fermer le fichier
    fclose(fichier);

    printf("Partie sauvegardée avec succès\n");
    return 1;
}

int charger_partie(struct Partie *partie, const char *nom_fichier) {
    // ouvrir un fichier en lecture binaire
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier pour lire\n");
        return 0;
    }

    // lire les données de la partie depuis le fichier
    fread(partie, sizeof(struct Partie), 1, fichier);

    // fermer le fichier
    fclose(fichier);

    printf("Partie chargée avec succès\n");
    return 1;
}

int main() {
    // créer une instance de la structure Partie avec des données de test
    struct Partie partie = { /* score */, /* niveau */ };

    // sauvegarder la partie
    sauvegarder_partie(&partie, "partie.sav");

    // modifier les données de la partie pour simuler une nouvelle session
    partie.score = 100;
    partie.niveau = 5;

    // charger la partie sauvegardée
    charger_partie(&partie, "partie.sav");

    // afficher les données de la partie chargée
    printf("Score : %d, Niveau : %d\n", partie.score, partie.niveau);

    return 0;
}
