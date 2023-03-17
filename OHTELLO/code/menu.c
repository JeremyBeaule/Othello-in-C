#include "struct.h"
// Fonction pour afficher le menu
int afficher_theme();

void afficher_menu() {

  // Charger l'image à partir d'une image png'
SDL_Texture* texture = IMG_LoadTexture(renderer, "image/fond_menu.png");
SDL_Texture* son_on_texture = IMG_LoadTexture(renderer, "image/volume.png");
SDL_Texture* son_off_texture = IMG_LoadTexture(renderer, "image/volume_off.png");
SDL_Texture* son_actuelle = son_on_texture;

// Créer une texture à partir de la surface de l'image
SDL_Texture* Bstart_texture = IMG_LoadTexture(renderer, "image/bouton-start.png");
SDL_Texture* Bt2_texture = IMG_LoadTexture(renderer, "image/bouton-quit.png");
SDL_Texture* Bt3_texture = IMG_LoadTexture(renderer, "image/bouton-load.png");
SDL_Texture* Bt4_texture = IMG_LoadTexture(renderer, "image/bouton-load.png");


// Récupérer les dimensions de la fenêtre
int largeur_fenetre, hauteur_fenetre;
SDL_GetWindowSize(window, &largeur_fenetre, &hauteur_fenetre);
  // Boucle principale du menu
  int continuer = 1;
  SDL_Event evenement;
  while (continuer) {
    // Gestion des événements
    while (SDL_PollEvent(&evenement)) {
      switch (evenement.type) {
        case SDL_QUIT:
          continuer = 0;
          break;
        case SDL_MOUSEBUTTONUP:
        if (evenement.button.button == SDL_BUTTON_LEFT) {
      
          // Récupération des coordonnées de la souris lors du clic
          int x = evenement.button.x;
          int y = evenement.button.y;
          // Vérification si le clic est sur l'un des choix
          if (x >= 275 && x <= 525 && y >= 250 && y <= 350) {
            printf("\n Bouton 1 cliqué, lancement du programme\n");
            start();
          continue;
          }
          if (x >= 275 && x <= 525 && y >= 375 && y <= 475) {
            printf("\n Bouton 2 cliqué, choix du theme\n");
            continuer = afficher_theme();
            printf("fin");
            continue;
          }
          if (x >= 275 && x <= 525 && y >= 500 && y <= 600) {

            start();
            continue;
          }
          if (x >= 275 && x <= 525 && y >= 625 && y <= 725) {
            return ; // Appel de la fonction pour le choix 3
          }
          if (x >= 700 && x <= 780 && y >= 700 && y <= 780) {
            if(son_actuelle == son_off_texture){
              son_actuelle = son_on_texture;
            }
            else{
              son_actuelle = son_off_texture;
            }
            continue;
          }
          break;
      }}
    }
// Effacement de l'écran
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderClear(renderer);

// Définir le rectangle de destination pour l'image de fond (ici, on utilise les dimensions de la fenêtre)
SDL_Rect rect = {0, 0, largeur_fenetre, hauteur_fenetre};

// rectangle pour les choix
SDL_Rect rect_choix1 = { 275, 250, 250, 100 };
SDL_Rect rect_choix2 = { 275, 375, 250, 100 };
SDL_Rect rect_choix3 = { 275, 500, 250, 100 };
SDL_Rect rect_choix4 = { 275, 625, 250, 100 };
SDL_Rect son = { 700, 700, 80, 80 };
SDL_RenderClear(renderer);


// Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)
SDL_RenderCopy(renderer, texture, NULL, &rect);
SDL_RenderCopy(renderer, son_actuelle, NULL, &son);
SDL_RenderCopy(renderer, Bstart_texture, NULL, &rect_choix1);
SDL_RenderCopy(renderer, Bt2_texture, NULL, &rect_choix2);
SDL_RenderCopy(renderer, Bt3_texture, NULL, &rect_choix3);
SDL_RenderCopy(renderer, Bt4_texture, NULL, &rect_choix4);

//Update Screen
SDL_RenderPresent(renderer);
}

// Free resources
SDL_DestroyTexture(texture);
SDL_DestroyTexture(Bstart_texture);
SDL_DestroyTexture(Bt2_texture);
SDL_DestroyTexture(Bt3_texture);
SDL_DestroyTexture(son_on_texture);
SDL_DestroyTexture(son_off_texture);
SDL_DestroyTexture(Bt4_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);


//Quit SDL
SDL_Quit();
printf("\n le menu ce ferme\n");
exit( EXIT_SUCCESS );
}




int afficher_theme() {
//fond coloré
SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
SDL_RenderClear(renderer);
// Créer une texture à partir de la surface de l'image
SDL_Texture* quit_texture = IMG_LoadTexture(renderer, "image/quit.png");
SDL_Texture* valider_texture = IMG_LoadTexture(renderer, "image/valider.png");
SDL_Texture* suivant_texture = IMG_LoadTexture(renderer, "image/suivant.png");
SDL_Texture* precedent_texture = IMG_LoadTexture(renderer, "image/precedent.png");
SDL_Texture* plateau_texture1 = IMG_LoadTexture(renderer, "image/Game.jpg");
SDL_Texture* plateau_texture2 = IMG_LoadTexture(renderer, "image/Board.png");
SDL_Texture* plateau_texture3 = IMG_LoadTexture(renderer, "image/Board.png");
SDL_Texture* fond_texture = IMG_LoadTexture(renderer, "image/fond_menu.png");

SDL_Texture* plateau_texture_actuel = plateau_texture1;

  // Boucle principale du menu
  int continuer = 1;
  SDL_Event evenement;
  while (continuer) {
    // Gestion des événements
    while (SDL_PollEvent(&evenement)) {
      switch (evenement.type) {
        case SDL_QUIT:
          return 0;
          break;
        case SDL_MOUSEBUTTONUP:
        if (evenement.button.button == SDL_BUTTON_LEFT) {
          // Récupération des coordonnées de la souris lors du clic
          int x = evenement.button.x;
          int y = evenement.button.y;
          // Vérification si le clic est sur l'un des choix
          if (x >= 350 && x <= 450 && y >= 650 && y <= 750) {
            printf("valider");
            grille_texture = plateau_texture_actuel; //pour le plateau de jeu
            black_texture = IMG_LoadTexture(renderer, "image/black.png");//pour la couleur de pion du jeu
            white_texture = IMG_LoadTexture(renderer, "image/white.png");//pour la couleur de pion du jeu
            contour_texture = IMG_LoadTexture(renderer, "image/contour.png");//pour le contour du jeu
            afficher_menu();
          }
          


          if (x >= 75 && x <= 225 && y >= 350 && y <= 450) {
            printf("precedent");
            if (plateau_texture_actuel == plateau_texture3){
                plateau_texture_actuel = plateau_texture2;
                }
            else if (plateau_texture_actuel == plateau_texture2){
                plateau_texture_actuel = plateau_texture1;

            }
            else {
              plateau_texture_actuel = plateau_texture3;
            }
             // Appel de la fonction pour le choix 2
          }
          if (x >= 600 && x <= 750 && y >= 350 && y <= 450) {
            if (plateau_texture_actuel == plateau_texture1){
                plateau_texture_actuel = plateau_texture2;
                }
            else if (plateau_texture_actuel == plateau_texture2){
                plateau_texture_actuel = plateau_texture3;

            }
            else {
              plateau_texture_actuel = plateau_texture1;
            }
            printf("suivant");
             // Appel de la fonction pour le choix 3
          }
            if (x >= 640 && x <= 740 && y >= 70 && y <= 170) {
            printf("\n Retour menu principale \n");
            afficher_menu();

          }
          break;
      }}
    }


SDL_RenderClear(renderer);


// rectangle pour les choix
SDL_Rect valider = { 350, 650, 100, 100 };
SDL_Rect suivant = { 75, 350, 150, 100 };
SDL_Rect precedent = { 600, 350, 150, 100 };//suivant et precedent sont inversé
SDL_Rect quit = { 640, 70, 100, 100 };
SDL_Rect plateau = { 300, 100, 250, 250 };
int largeur_fenetre, hauteur_fenetre;
SDL_GetWindowSize(window, &largeur_fenetre, &hauteur_fenetre);
SDL_Rect fond_rect = { 0, 0, largeur_fenetre, hauteur_fenetre };


// Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)

SDL_RenderCopy(renderer, fond_texture, NULL, &fond_rect);
SDL_RenderCopy(renderer, valider_texture, NULL, &valider);
SDL_RenderCopy(renderer, suivant_texture, NULL, &suivant);
SDL_RenderCopy(renderer, precedent_texture, NULL, &precedent);
SDL_RenderCopy(renderer, quit_texture, NULL, &quit);
SDL_RenderCopy(renderer, plateau_texture_actuel, NULL, &plateau);

//Update Screen
SDL_RenderPresent(renderer);
}
// Free resources
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_DestroyTexture(valider_texture);
SDL_DestroyTexture(suivant_texture);
SDL_DestroyTexture(precedent_texture);
SDL_DestroyTexture(quit_texture);
SDL_DestroyTexture(plateau_texture1);
SDL_DestroyTexture(plateau_texture2);
SDL_DestroyTexture(plateau_texture3);
SDL_DestroyTexture(plateau_texture_actuel);
SDL_DestroyTexture(fond_texture);

printf("\n le menu des themes ce ferme\n");
return 1;
}