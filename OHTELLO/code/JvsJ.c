#include "struct.h"
int joueurvsjoueur(int chargement)//si chargement =0 c est une nouvelle partie, si un c est un chargement de partie
{
    // Initialiser le plateau de jeu et l'afficher
    Board board;
    charger_partie(&board, chargement,"code/enregistrement.txt"); // load.c
    efface_fichier("code/precedent.txt"); // on efface la sauvegarde
    int fin = 0;
    int coup_jouable = 0; // si c est egal a 2 ca veux dire que les 2 adversaires on passer leur tour donc que c est finis
    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Event event;
    int quit = 0;
    
    while (quit == 0)
    {   
        fin = finis_ou_pas(&board);                  // si la grille est complete ou si il n y a plus de coup jouable des 2 cotés
        if (fin==0){
        affiche_tour(renderer);
        afficher_coup_jouable(&board, grey_texture); // afficher les coups jouables pour le joueur en cours
        }

     

        if (fin == 1) // si la partie est finis
        {
            End_game(&board);       // on affiche le gagnant
            efface_fichier("code/enregistrement.txt"); // on efface la sauvegarde
            efface_fichier("code/precedent.txt"); // on efface la sauvegarde
            
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
                    int cell_x = (x - board.grid_x) / board.cell_size;
                    int cell_y = (y - board.grid_y) / board.cell_size;
                    printf("%d =x et %d = y\n,", x, y);
                    if (fin == 0)
                    {
                        if (cell_x < 0 || cell_x >= BOARD_SIZE || x < 800 * 0.19 || cell_y < 0 || cell_y >= BOARD_SIZE || y < 800 * 0.2) // si en dehors de la grille
                        {
                            if (x > 650 && x < 800 && y > 350 && y < 425) //click bouton precedent
                            {
                                printf("\n precedent \n");
                                if (is_file_empty("code/precedent.txt"))
                                {
                                    continue;
                                }
                                else
                                {
                                    charger_partie(&board, 1, "code/precedent.txt"); // charger le coup precedent
                                }
                            }

                            if (x > 300 && x < 500 && y > 40 && y < 115) //bouton menu
                            {
                                printf("\n menu \n");
                                save_board(&board, "code/enregistrement.txt");
                                return 1;
                                
                            }
                            if (x > 60 && x < 160 && y > 60 && y < 110)//bouton information
                            {
                                showInformation();
                                printf("\n information \n");
                                
                            }
               
                        }
                        else
                        {
                            
                            coup_jouable = jouer(&board, x, y, coup_jouable); // remet a 0 le compteur pour le coup jouable, dans le cas ou un joueur a passer son tour mais que l autre peut jouer
                            save_board(&board,"code/enregistrement.txt");
                        }
                    }
                    if (fin == 1)
                    { // pour cliquer et revenir au menu
                        if (x > 275 && x < 625 && y > 550 && y < 650)
                        { // il faut changer la zone de clique en dehors de la grille sinon ca click tout seul sur le bouton fin si on place le dernier bouton dans la zone
                            printf("\n click sur le bouton fin \n");
                           quit = 1;
                        }
                    }
                }

                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    printf("\n programme de jeu finis, retour au menu principal \n");

    return 1;
}
