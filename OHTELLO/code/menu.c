#include "struct.h"
// Fonction pour afficher le menu
void afficher_theme();

int afficher_menu() {

  // Charger l'image à partir d'une image png'
SDL_Surface* fond = IMG_Load("image/fond.png");

// Charger image bouton1
SDL_Surface* Bstart = IMG_Load("image/bouton-start.png");
SDL_Surface* Bt2 = IMG_Load("image/bouton-start.png");
SDL_Surface* Bt3 = IMG_Load("image/bouton-start.png");





// Créer une texture à partir de la surface de l'image
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fond);
SDL_Texture* Bstart_texture = SDL_CreateTextureFromSurface(renderer, Bstart);
SDL_Texture* Bt2_texture = SDL_CreateTextureFromSurface(renderer, Bt2);
SDL_Texture* Bt3_texture = SDL_CreateTextureFromSurface(renderer, Bt3);

// Libérer la surface de l'image (nous n'en avons plus besoin)
SDL_FreeSurface(fond);
SDL_FreeSurface(Bstart);
SDL_FreeSurface(Bt2);
SDL_FreeSurface(Bt3);



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
          if (x >= 100 && x <= 200 && y >= 500 && y <= 600) {

            
            printf("\n Bouton 1 cliqué, lancement du programme\n");

            start();


          continue;
          }
          if (x >= 360 && x <= 460 && y >= 500 && y <= 600) {
            printf("\n Bouton 2 cliqué, choix du theme\n");
            afficher_theme();
            printf("fin");
            continue;
          }
          if (x >= 640 && x <= 840 && y >= 500 && y <= 850) {
            return 3; // Appel de la fonction pour le choix 3
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
SDL_Rect rect_choix1 = { 100, 500, 100, 100 };
SDL_Rect rect_choix2 = { 360, 500, 100, 100 };
SDL_Rect rect_choix3 = { 640, 500, 100, 100 };

SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
SDL_RenderClear(renderer);


// Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)
SDL_RenderCopy(renderer, texture, NULL, &rect);
SDL_RenderCopy(renderer, Bstart_texture, NULL, &rect_choix1);
SDL_RenderCopy(renderer, Bt2_texture, NULL, &rect_choix2);
SDL_RenderCopy(renderer, Bt3_texture, NULL, &rect_choix3);
//Update Screen
SDL_RenderPresent(renderer);
}

// Free resources
SDL_DestroyTexture(texture);
SDL_DestroyTexture(Bstart_texture);
SDL_DestroyTexture(Bt2_texture);
SDL_DestroyTexture(Bt3_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);

//Quit SDL
SDL_Quit();
printf("\n le menu ce ferme\n");
return 0;
}




void afficher_theme() {
//fond coloré
SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
SDL_RenderClear(renderer);

// Charger image bouton1
SDL_Surface* quit = IMG_Load("image/quit.png");
SDL_Surface* valider = IMG_Load("image/valider.png");
SDL_Surface* suivant= IMG_Load("image/suivant.png");
SDL_Surface* precedent= IMG_Load("image/precedent.png");
SDL_Surface* plateau1 = IMG_Load("image/Game.jpg");
SDL_Surface* plateau2 = IMG_Load("image/Board.png");

// Créer une texture à partir de la surface de l'image

SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit);
SDL_Texture* valider_texture = SDL_CreateTextureFromSurface(renderer, valider);
SDL_Texture* suivant_texture = SDL_CreateTextureFromSurface(renderer, suivant);
SDL_Texture* precedent_texture = SDL_CreateTextureFromSurface(renderer, precedent);
SDL_Texture* plateau_texture1 = SDL_CreateTextureFromSurface(renderer, plateau1);
SDL_Texture* plateau_texture2 = SDL_CreateTextureFromSurface(renderer, plateau2);
SDL_Texture* plateau_texture_actuel = plateau_texture1;


// Libérer la surface de l'image (nous n'en avons plus besoin)
SDL_FreeSurface(quit);
SDL_FreeSurface(valider);
SDL_FreeSurface(suivant);
SDL_FreeSurface(precedent);
SDL_FreeSurface(plateau1);
SDL_FreeSurface(plateau2);


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
          if (x >= 350 && x <= 450 && y >= 650 && y <= 750) {
            printf("valider");
            grille_texture = plateau_texture_actuel;
            afficher_menu();
          }
          


          if (x >= 50 && x <= 150 && y >= 350 && y <= 450) {
            printf("suivant");
            if (plateau_texture_actuel == plateau_texture1){
                plateau_texture_actuel = plateau_texture2;
                }
                else{
                plateau_texture_actuel = plateau_texture1;

            } 
             // Appel de la fonction pour le choix 2
          }
          if (x >= 650 && x <= 750 && y >= 350 && y <= 450) {
            if (plateau_texture_actuel == plateau_texture1){
                plateau_texture_actuel = plateau_texture2;
                }
                else{
                plateau_texture_actuel = plateau_texture1;

            } 
            printf("precedent");
             // Appel de la fonction pour le choix 3
          }
            if (x >= 680 && x <= 780 && y >= 100 && y <= 200) {
            printf("\n Retour menu principale \n");
            afficher_menu();

          }
          break;
      }}
    }

// Effacement de l'écran
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
SDL_RenderClear(renderer);


// rectangle pour les choix
SDL_Rect valider = { 350, 650, 100, 100 };
SDL_Rect suivant = { 50, 350, 100, 100 };
SDL_Rect precedent = { 650, 350, 100, 100 };
SDL_Rect quit = { 680, 100, 100, 100 };
SDL_Rect plateau = { 300, 100, 250, 250 };


// Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)

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
SDL_DestroyTexture(plateau_texture_actuel);

printf("\n le menu des themes ce ferme\n");
}