#include "struct.h"
#include <limits.h> // Pour INT_MIN et INT_MAX
#include <stdlib.h> // Pour malloc, realloc et free
#include <stdio.h>  // Pour printf
typedef struct GameTreeNode
{
    Board board;
    int score;
    struct GameTreeNode *children;
    int num_children;
    int move_x;
    int move_y;
} GameTreeNode;

void placer_pion_logique(int x, int y, PlayerColor color, Board *board)
{
    board->cells[x][y].player = color;
}
void delete_placer_pion_logique(int x, int y, PlayerColor color, Board *board)
{
    board->cells[x][y].player = EMPTY;
}
int mouvement_valide(Board *board, int cell_x, int cell_y)
{
    // printf("\n test mouvement valide \n");
    // printf("\n cell_x = %d , cell_y = %d \n", cell_x, cell_y);
    if (verif_place_horiz_d(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_horiz_g(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_verti_h(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_verti_b(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_diag_bd(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_diag_bg(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_diag_hd(cell_x, cell_y, board, white_texture, 0) == 0 && verif_place_diag_hg(cell_x, cell_y, board, white_texture, 0) == 0)
    {
        // si le coup est pas jouable
        // printf(" \n mouvement pas valide\n ");
        return 0;
    }
    else
    { // si jouable on flip les pions
        // printf("\n mouvement valide \n");
        return 1;
    }
    // printf("\n fin test mouvement valide \n");
}
Board *copy_board(Board *original_board)
{
    Board *new_board = (Board *)malloc(sizeof(Board));
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            new_board->cells[x][y].player = original_board->cells[x][y].player;
        }
    }
    return new_board;
}
int evaluate_board(Board *board)
{
    // printf("\n evaluate_board\n");
    //  Calculate the difference between the number of black and white pieces
    int black_count = 0;
    int white_count = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->cells[i][j].player == BLACK)
            {
                black_count++;
            }
            else if (board->cells[i][j].player == WHITE)
            {
                white_count++;
            }
        }
    }
    // printf("\n evaluate_board end\n");
    return black_count - white_count;
}

int minimax(GameTreeNode *node, int depth, int alpha, int beta, int maximizingPlayer)
{
    // printf("\n minimax \n");
    if (depth == 0 || finis_ou_pas(&(node->board)))
    {
        return evaluate_board(&(node->board));
    }

    if (maximizingPlayer)
    {
        int maxEval = INT_MIN;
        for (int i = 0; i < node->num_children; i++)
        {
            int eval = minimax(&(node->children[i]), depth - 1, alpha, beta, 0);
            maxEval = fmax(maxEval, eval);
            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        for (int i = 0; i < node->num_children; i++)
        {
            int eval = minimax(&(node->children[i]), depth - 1, alpha, beta, 1);
            minEval = fmin(minEval, eval);
            beta = fmin(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
    // printf("\n minimax end\n ");
}

GameTreeNode *generate_children(Board *board, PlayerColor color, int *num_children, int depth)
{
    // printf("\n generate_children \n");
    GameTreeNode *children = NULL;
    *num_children = 0;

    if (depth >= 8) //1,3,5,7 les nombres pair bug et au dessus de 7 trop gourmand en ressources
    {
        return NULL;
    }

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            // printf("\n x = %d, y = %d\n", x, y);
            if (board->cells[x][y].player == EMPTY)
            {
                Board *newBoard = copy_board(board);

                if (mouvement_valide(newBoard, x, y))
                {
                    placer_pion_logique(x, y, color, newBoard);
                    (*num_children)++;

                    children = realloc(children, (*num_children) * sizeof(GameTreeNode));
                    if (children == NULL)
                    {
                        printf("Erreur d'allocation de mémoire pour les enfants\n");
                        exit(EXIT_FAILURE);
                    }

                    children[*num_children - 1].board = *newBoard;
                    children[*num_children - 1].score = 0;
                    children[*num_children - 1].children = NULL;
                    children[*num_children - 1].num_children = 0;
                    children[*num_children - 1].move_x = x;
                    children[*num_children - 1].move_y = y;

                    if (newBoard != NULL)
                    {
                        children[*num_children - 1].children = generate_children(newBoard, (color == WHITE) ? BLACK : WHITE, &(children[*num_children - 1].num_children), depth + 1);
                    }
                    else
                    {
                        children[*num_children - 1].children = NULL;
                    }

                    free(newBoard);
                }
            }
        }
    }
    // printf("\n generate_children end \n");
    // printf("\n nombre d'enfant ! %d \n", *num_children);

    return children;
}

void IA(Board *board, int *best_move_x, int *best_move_y)
{
    // printf("\n IA \n");
    int depth = 1; // You can adjust the depth based on your desired complexity
    int bestScore = INT_MIN;
    int num_children;
    GameTreeNode root;
    root.board = *board;
    root.children = NULL;
    root.num_children = 0;

    // Generate child nodes for the current player (AI)
    root.children = generate_children(board, current_player->couleur, &num_children, depth);
    root.num_children = num_children;

    for (int i = 0; i < root.num_children; i++)
    {
        int score = minimax(&(root.children[i]), depth - 1, INT_MIN, INT_MAX, 0);

        if (score > bestScore)
        {
            bestScore = score;
            *best_move_x = root.children[i].move_x;
            *best_move_y = root.children[i].move_y;
        }
    }

    // Free the allocated memory for child nodes
    for (int i = 0; i < root.num_children; i++)
    {
        if (root.children[i].children != NULL)
            free(root.children[i].children);
    }
    if (root.children != NULL)
        free(root.children);
    printf("\n IA end \n");
}

char placer_pion_IA(int x, int y, SDL_Texture *texture, Board *board)
{
    int jouable = 0;

    Cell *cell = &board->cells[x][y];

    // verifie les regles
    jouable = coup_jouable_ou_non(x, y, board, texture, 0);
    if (jouable == 0)
    {
        afficher_popup(renderer, "coup impossible");
        return 0;
    }

    // mis a jour de la cellule
    if (current_player == joueur_blanc)
    {
        cell->player = WHITE;
    }
    else
    {
        cell->player = BLACK;
    }

    // Afficher le pion
    SDL_Rect dest_rect = {
        board->grid_x + x * board->cell_size + 3,
        board->grid_y + y * board->cell_size + 3,
        board->cell_size - 5,
        board->cell_size - 5};
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);

    // printf("\n test fin placer_pion()\n");
    return 1;
}

void jouer_IA(Board *board)
{

    if (current_player == joueur_noir)
    {
        SDL_Delay(1000);
        printf("\njoueur noir\n");
        afficher_coup_jouable(board, carre_grille_texture); // remetre les cases a leur textures normal

        int best_move_x, best_move_y;
        IA(board, &best_move_x, &best_move_y);
        printf("\nbest_move_x = %d, best_move_y = %d\n", best_move_x, best_move_y);
        placer_pion_IA(best_move_x, best_move_y, black_texture, board);
        printf("\n L'ia a jouer son coup \n");
        current_player = joueur_blanc;
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    printf("\n L'ia a finis son tour \n");
}

void jouer_joueur(Board *board, int x, int y)
{
    if (current_player == joueur_blanc)
    {
        printf("\njoueur blanc\n");

        afficher_coup_jouable(board, carre_grille_texture); // remetre les cases a leur textures normal

        if (placer_pion(x, y, white_texture, board) == 1)
        { // la texture definit la couleur du pion qu'on va placer

            current_player = joueur_noir;
            SDL_Delay(500);
        }
        SDL_RenderPresent(renderer);
        return;
    }
}
