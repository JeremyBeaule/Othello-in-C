#include "struct.h"
#include "stdbool.h"

void save_board(Board *board)
{
    FILE *fp = NULL;
    printf("enregistrement du plateau");
    fp = fopen("code/enregistrement.txt", "w");
    if (fp == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier ");
        return;
    }
   // printf("enregistrement");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->cells[i][j].player != 0)
            {
                fprintf(fp, "%d %d %d\n", i, j, board->cells[i][j].player);
            }
        }
    }

    fprintf(fp, "%d\n", current_player->couleur);

    fclose(fp);
}

int charger_pions(Board *board)
{
    FILE *fp = NULL;
    printf("\n chargement en cours \n");
    fp = fopen("code/enregistrement.txt", "r");
    if (fp == NULL)
    {
        printf("\nErreur : impossible d'ouvrir le fichier\n");
        return 3;
    }

    char buffer[128];
    int x, y, player, couleur;

    // Lecture des lignes du fichier
    while (fgets(buffer, 128, fp) != NULL)
    {
        if (sscanf(buffer, "%d %d %d", &x, &y, &player) != 3)
        {
            continue;
        }
        if (feof(fp))
        {
            break;
        }

        printf(" %d %d %d\n", x, y, player);
        placer_pion_chargement_partie(board, x, y, player);
    }

    // Lecture de la dernière valeur
    fseek(fp, -2, SEEK_END);   // Positionnement du curseur à l'avant-dernier caractère
    fgets(buffer, 2, fp);      // Lecture du dernier caractère
    couleur = buffer[0] - '0'; // Conversion du caractère en entier
    // printf("%d \n",couleur);

    fclose(fp);
    return couleur;
}
void efface_fichier()
{
    FILE *fp = fopen("code/enregistrement.txt", "w");

    fclose(fp);
}

int is_file_empty() {
    FILE* fp = fopen("code/enregistrement.txt", "r");
    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return 1;
    }

    int is_empty = 1;
    char c = fgetc(fp);
    if (c != EOF) {
        is_empty = 0;
    }

    fclose(fp);
    return is_empty;
}
