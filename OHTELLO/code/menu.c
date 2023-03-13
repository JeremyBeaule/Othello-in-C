#include "struct.h"
// Fonction pour afficher le menu
int afficher_menu(SDL_Renderer* renderer) {
    //charger la police
TTF_Font* font = TTF_OpenFont("image/ASMAN.TTF", 24); 
  /// Charger l'image à partir d'une image png'
SDL_Surface* surface = IMG_Load("image/fond.png");
// Créer une surface de texte
SDL_Color couleur_texte = {0,0,0}; // Blanc
SDL_Surface* surface_texte1 = TTF_RenderText_Solid(font, "choix 1", couleur_texte);
SDL_Surface* surface_texte2 = TTF_RenderText_Solid(font, "choix 2", couleur_texte);
SDL_Surface* surface_texte3 = TTF_RenderText_Solid(font, "choix 3", couleur_texte);

// Créer une texture à partir de la surface de texte
SDL_Texture* texture_texte1 = SDL_CreateTextureFromSurface(renderer, surface_texte1);
SDL_Texture* texture_texte2 = SDL_CreateTextureFromSurface(renderer, surface_texte2);
SDL_Texture* texture_texte3 = SDL_CreateTextureFromSurface(renderer, surface_texte3);
// Créer une texture à partir de la surface de l'image
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
// Libérer la surface de texte (nous n'en avons plus besoin)
SDL_FreeSurface(surface_texte1);
SDL_FreeSurface(surface_texte2);
SDL_FreeSurface(surface_texte3);
// Libérer la surface de l'image (nous n'en avons plus besoin)
SDL_FreeSurface(surface);





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
          if (x >= 100 && x <= 200 && y >= 100 && y <= 150) {
            printf("\n eofeaonvzovnzkju \n");
            return 1;
          }
          if (x >= 100 && x <= 200 && y >= 200 && y <= 250) {
            return 2; // Appel de la fonction pour le choix 2
          }
          if (x >= 100 && x <= 200 && y >= 300 && y <= 350) {
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
    SDL_Rect rect_choix1 = { 100, 100, 100, 50 };
    SDL_Rect rect_choix2 = { 100, 200, 100, 50 };
    SDL_Rect rect_choix3 = { 100, 300, 100, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
//Copy Blend Mode
SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

// Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)
SDL_RenderCopy(renderer, texture, NULL, &rect);

//Choice 1
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
SDL_RenderFillRect(renderer, &rect_choix1);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderDrawRect(renderer, &rect_choix1);

//Choice 2
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
SDL_RenderFillRect(renderer, &rect_choix2);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderDrawRect(renderer, &rect_choix2);

//Choice 3
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
SDL_RenderFillRect(renderer, &rect_choix3);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderDrawRect(renderer, &rect_choix3);
// Afficher la texture de texte sur les 3 boutons
SDL_RenderCopy(renderer, texture_texte1, NULL, &rect_choix1);
SDL_RenderCopy(renderer, texture_texte2, NULL, &rect_choix2);
SDL_RenderCopy(renderer, texture_texte3, NULL, &rect_choix3);
//Update Screen
SDL_RenderPresent(renderer);
}

// Free resources
SDL_DestroyTexture(texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);

//Quit SDL
SDL_Quit();
return 0;
}