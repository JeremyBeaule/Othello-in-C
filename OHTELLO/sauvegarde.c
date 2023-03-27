#include <stdio.h>
#include <stdlib.h>

// Structure représentant les données de la partie
struct GameData {
    int score;
    int placement;
};

int main() {
    // Créer une instance de la structure GameData avec des données de test
    struct GameData gameData = { 1000 /* score */, 1 /* level */ };

    // Ouvrir un fichier en écriture binaire
    FILE* file = fopen("game.sav", "wb");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier pour écrire\n");
        return 1;
    }

    // Écrire les données de la partie dans le fichier
    fwrite(&gameData, sizeof(gameData), 1, file);

    // Fermer le fichier
    fclose(file);

    printf("La partie a été sauvegardée.\n");

    // ... Jouer à votre jeu ...

    // Charger les données de la partie depuis le fichier
    file = fopen("game.sav", "rb");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier pour lire\n");
        return 1;
    }

    struct GameData savedGameData;
    fread(&savedGameData, sizeof(savedGameData), 1, file);

    // Fermer le fichier
    fclose(file);

    printf("La partie a été chargée. Score : %d, Level : %d\n", savedGameData.score, savedGameData.level);

    return 0;
}
