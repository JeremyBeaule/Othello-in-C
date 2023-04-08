#include "struct.h"
int joueurvsjoueur(int chargement)
{
    // Initialiser le plateau de jeu et l'afficher
    Board board;
    charger_partie(&board, chargement); // logique.c
    int fin = 0;
    int coup_jouable = 0; // si c est egal a 2 ca veux dire que les 2 adversaires on passer leur tour donc que c est finis
    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Event event;
    int quit = 0;
    while (quit == 0)
    {
        affiche_tour(renderer);
        afficher_coup_jouable(&board, grey_texture); // afficher les coups jouables pour le joueur en cours
        fin = finis_ou_pas(&board);                  // si la grille est complete ou si il n y a plus de coup jouable des 2 cotés

        if (fin == 1) // si la partie est finis
        {
            End_game();       // on affiche le gagnant
            efface_fichier(); // on efface la sauvegarde
        }
        while (SDL_PollEvent(&event))
        {

            // printf("la case est de type : %d", board.cells[3][3].player);

            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    printf("%d =x et %d = y\n,", x, y);
                    if (fin == 0)
                    {
                        coup_jouable = jouer(&board, x, y, coup_jouable); // remet a 0 le compteur pour le coup jouable, dans le cas ou un joueur a passer son tour mais que l autre peut jouer

                        if (x > 350 && x < 550 && y > 350 && y < 550)
                        {
                            // TODO
                            // revenir en arriere lors du clique sur un bouton
                            //rajouter les elements graphiques sur la fonction affichez_plateau
                        }
                        if (x > 350 && x < 550 && y > 350 && y < 550)
                        {
                            // TODO
                            // activer ou desactiver l'enregistrement de partie automatique et changer l emoticon
                            //on enregistre dans tout les cas pour revenir un coup en arriere mais si on desactive la sauvegarde auto et que l'on quitte le jeu alors le fichier s efface
                            //il faut rajouter une condition dans le SDL_QUIT
                        
                        }
                    }
                    if (fin == 1)
                    { // pour cliquer et revenir au menu
                        if (x > 350 && x < 550 && y > 350 && y < 550)
                        { // il faut changer la zone de clique en dehors de la grille sinon ca click tout seul sur le bouton fin si on place le dernier bouton dans la zone
                            printf("\n click sur le bouton fin \n");
                            return 1;
                        }
                    }
                }

                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    printf("\n programme de jeu finis, retour au menu principal \n");

    // Libérer les ressources allouées
    SDL_DestroyTexture(black_texture);
    SDL_DestroyTexture(white_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
