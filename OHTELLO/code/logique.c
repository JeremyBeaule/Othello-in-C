#include "struct.h"
  extern  int screen_height;
  extern  int screen_width;
  
  //permet de changer la texture de n mporte quelle case
void changer_texture_case(int x, int y, Board* board,SDL_Texture* texture) {
    // Vérifier que les indices sont valides
		printf("\n coucfffou \n");
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        printf("Indices de case invalides\n");
        return;
    }
	//on met a jour la cellule
	Cell* cell = &board->cells[x][y];
	if(current_player==joueur_blanc){
            cell->player = WHITE;
            }
	else{
            cell->player = BLACK;  
            }

    // Afficher la nouvelle texture
    SDL_Rect dest_rect = {
        board->grid_x + x * board->cell_size+3,
        board->grid_y + y * board->cell_size+3,
        board->cell_size-5,
        board->cell_size-5
    };
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
}


int verif_place_horiz_d(int x, int y, Board* board,SDL_Texture* texture){
int x_board=x+1;//si x=7 c'est la mouise

		if(board->cells[x_board][y].player==EMPTY || board->cells[x_board][y].player==current_player->couleur){
			return 0;
		}
	//tant que la case a droite n'est pas egale a notre couleur et que la case a droite est pas vide on passe a la suivante
	//si on depasse le tableau ca veux dire qu'on peut pas faire de ligne
	//on pose le pion, on regarde a droite de celui-ci si on a bien une case contenant a pion adverse, pareil pour la case d'apres, et si il y a une case vide on peut poser
	while(board->cells[x_board][y].player!=current_player->couleur && board->cells[x_board][y].player!=EMPTY){ 
		if(x_board>7){
			return 0;
			}

		x_board++;
	}
	if(board->cells[x_board][y].player==EMPTY){
		return 0;
		}
		x_board=x+1;
	while(board->cells[x_board][y].player!=current_player->couleur && board->cells[x_board][y].player!=EMPTY){ 
		printf("\n droite \n");

		changer_texture_case(x_board,y,board,texture);
		x_board++;
	}
	
	return 1;
}


int verif_place_horiz_g(int x, int y, Board* board,SDL_Texture* texture){
int x_board=x-1;//si x=0 mm pb
		if(board->cells[x_board][y].player==EMPTY || board->cells[x_board][y].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x_board][y].player!=current_player->couleur && board->cells[x_board][y].player!=EMPTY){
		if(x_board<0){
			return 0;
		}

		x_board--;
	}
	if(board->cells[x_board][y].player==EMPTY){
		return 0;
	}
	x_board=x-1;//si x=0 mm pb
	while(board->cells[x_board][y].player!=current_player->couleur && board->cells[x_board][y].player!=EMPTY){
		printf("\n gauche \n");
		changer_texture_case(x_board,y,board,texture);
		x_board--;
	}
	return 1;
}

int verif_place_verti_h(int x, int y, Board* board,SDL_Texture* texture){
int y_board=y+1;//si y=7 c'est la mouise
		if(board->cells[x][y_board].player==EMPTY || board->cells[x][y_board].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x][y_board].player!=current_player->couleur && board->cells[x][y_board].player!=EMPTY){
		if(y_board>7){
			return 0;
		}

		y_board++;
	}
	if(board->cells[x][y_board].player==EMPTY){
		return 0;
	}
	y_board=y+1;
	while(board->cells[x][y_board].player!=current_player->couleur && board->cells[x][y_board].player!=EMPTY){
		printf("\n haut \n");
		changer_texture_case(x,y_board,board,texture);

		y_board++;
	}
	return 1;
}


int verif_place_verti_b(int x, int y, Board* board,SDL_Texture* texture){//verticale bas
int y_board=y-1;//si y=0 c'est la mouise
		if(board->cells[x][y_board].player==EMPTY || board->cells[x][y_board].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x][y_board].player!=current_player->couleur && board->cells[x][y_board].player!=EMPTY){
		if(y_board<0){
			return 0;
		}
		y_board--;
	}
	if(board->cells[x][y_board].player==EMPTY){
		return 0;
	}
	y_board=y-1;
	while(board->cells[x][y_board].player!=current_player->couleur && board->cells[x][y_board].player!=EMPTY){
		printf("\n bas \n");
		changer_texture_case(x,y_board,board,texture);
		y_board--;
	}
	return 1;
}
int verif_place_diag_bg(int x, int y, Board* board,SDL_Texture* texture){//diag bas à gauche
int x_board=x-1;//si x=0 c'est la mouise
int y_board=y-1;//si y=0 c'est la mouise
		if(board->cells[x_board][y_board].player==EMPTY || board->cells[x_board][y_board].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		if(x_board<0)
			return 0;
		if(y_board<0)
			return 0;
		
		x_board--;
		y_board--;
	}
	if(board->cells[x_board][y_board].player==EMPTY){
		return 0;
	}
	x_board=x-1;//si x=0 c'est la mouise
	y_board=y-1;
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		printf("\n diag bas gauche\n");
		changer_texture_case(x_board,y_board,board,texture);
		x_board--;
		y_board--;
	}
	return 1;
}


int verif_place_diag_bd(int x, int y, Board* board,SDL_Texture * texture ){//diag bas à droite 
int x_board=x+1;//si x=7 c'est la mouise
int y_board=y+1;//si y=7 c'est la mouise

		if(board->cells[x_board][y_board].player==EMPTY || board->cells[x_board][y_board].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		if(x_board>7)
			return 0;
		if(y_board>7)
			return 0;
		
		x_board++;
		y_board++;
	}
	if(board->cells[x_board][y_board].player==EMPTY)
		return 0;
	x_board=x+1;//si x=7 c'est la mouise
	y_board=y+1;
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		printf("\n diag bas droite\n");
		changer_texture_case(x_board,y_board,board,texture);
		x_board++;
		y_board++;
	}
	return 1;
}
int verif_place_diag_hg(int x, int y, Board* board,SDL_Texture* texture){//diag haut gauche
int x_board=x-1;//si x=0 c'est la mouise
int y_board=y+1;//si y=7 c'est la mouise
		if(board->cells[x_board][y_board].player==EMPTY || board->cells[x_board][y_board].player==current_player->couleur){
			return 0;
		}
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		if(x_board<0)
			return 0;
		if(y_board>7)
			return 0;
		
		x_board--;
		y_board++;
	}
	if(board->cells[x_board][y_board].player==EMPTY)
		return 0;
	x_board=x-1;//si x=0 c'est la mouise
	y_board=y+1;
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		printf("\n diag haut gauche\n");
		changer_texture_case(x_board,y_board,board,texture);
		x_board--;
		y_board++;
	}
	return 1;
}
int verif_place_diag_hd(int x, int y, Board* board,SDL_Texture* texture){//diag  haut à droite
int x_board=x+1;//si x=7 c'est la mouise
int y_board=y-1;//si y=0 c'est la mouise
		if(board->cells[x_board][y_board].player==EMPTY || board->cells[x_board][y_board].player==current_player->couleur){//si la case est vide ou si c'est le joueur qui a joué
			return 0;
		}
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){//tant que la case n'est pas vide et que ce n'est pas le joueur qui a joué
		if(x_board>7)
			return 0;
		if(y_board<0)
			return 0;
		
		x_board++;
		y_board--;
	}
	if(board->cells[x_board][y_board].player==EMPTY)
		return 0;
	x_board=x+1;//si x=7 c'est la mouise
	y_board=y-1;
	while(board->cells[x_board][y_board].player!=current_player->couleur && board->cells[x_board][y_board].player!=EMPTY){
		printf("\n diagonal haut droite\n");
		changer_texture_case(x_board,y_board,board,texture);
		x_board++;
		y_board--;
	}
	return 1;
}

char placer_pion(int x, int y, SDL_Texture* texture, Board* board) {//retourne 0 si le joueur n'a pas place son pion a reste son tour sinon retourne 1
    //permet d'avoir la cellule du tableau ou l'on clique
    int cell_x = (x - board->grid_x) / board->cell_size ;
    int cell_y = (y - board->grid_y) / board->cell_size ;

    printf("\nboard->grid %d\n",board->grid_y);
    printf("\ncell_x:%d et celle_y:%d\n",cell_x,cell_y);
	
    if (cell_x < 0  ||cell_x >= BOARD_SIZE ||x<screen_width*0.19|| cell_y < 0 || cell_y >= BOARD_SIZE||y<screen_height*0.2) {
        afficher_popup(renderer,"vous etes en dehors de la grille ");
        return 0;
    }

    Cell* cell = &board->cells[cell_x][cell_y];

	if (cell->player != EMPTY) {
		afficher_popup(renderer,"case deja prise");
		return 0;
	}

    if(verif_place_horiz_d(cell_x,cell_y,board,texture)==0 && verif_place_horiz_g(cell_x,cell_y,board,texture)==0 && verif_place_verti_h(cell_x,cell_y,board,texture)==0 && verif_place_verti_b(cell_x,cell_y,board,texture)==0 
	&& verif_place_diag_bd(cell_x,cell_y, board,texture)==0 && verif_place_diag_bg(cell_x,cell_y, board,texture)==0&& verif_place_diag_hd(cell_x,cell_y, board,texture)==0&& verif_place_diag_hg(cell_x,cell_y, board,texture)==0){
	printf(" \n mauvais placement non respect regles\n ");
    return 0;
     }
	else{
		verif_place_diag_bd(cell_x,cell_y, board,texture);
		verif_place_diag_bg(cell_x,cell_y, board,texture);
		verif_place_diag_hd(cell_x,cell_y, board,texture);
		verif_place_diag_hg(cell_x,cell_y, board,texture);
		verif_place_horiz_d(cell_x,cell_y,board,texture);
		verif_place_horiz_g(cell_x,cell_y,board,texture);
		verif_place_verti_h(cell_x,cell_y,board,texture);
		verif_place_verti_b(cell_x,cell_y,board,texture);

	}



    if(current_player==joueur_blanc){
            cell->player = WHITE;
            }
	else{
            cell->player = BLACK;  
            }
    current_player->score+=1;
    printf("\n ton score est : %d \n",current_player->score);
    printf("\n ton score est : %d \n",joueur_noir->score);
    printf("\n la case est  : %d  (0=vide, 1=noir,2=blanc)\n",board->cells[2][3].player);//verifie une case en particulier

    // Afficher le pion
    SDL_Rect dest_rect = {
        board->grid_x + cell_x * board->cell_size+3,
        board->grid_y + cell_y * board->cell_size+3,
        board->cell_size-5,
        board->cell_size-5
    };
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
	printf("\n test fin placer_pion()\n");
        return 1;
}

