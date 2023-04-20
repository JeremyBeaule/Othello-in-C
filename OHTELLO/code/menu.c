#include "struct.h"
// Fonction pour afficher le menu
int afficher_theme();

void afficher_menu()
{

  // Charger l'image à partir d'une image png'
  SDL_Texture *texture = IMG_LoadTexture(renderer, "image/fond_menu.png");
  SDL_Texture *son_on_texture = IMG_LoadTexture(renderer, "image/volume.png");
  SDL_Texture *son_off_texture = IMG_LoadTexture(renderer, "image/volume_off.png");
  SDL_Texture *son_actuelle = son_on_texture;

  // Créer une texture à partir de la surface de l'image
  SDL_Texture *Bstart_texture = IMG_LoadTexture(renderer, "image/bouton-start.png");
  SDL_Texture *Bt2_texture = IMG_LoadTexture(renderer, "image/bouton-quit.png");
  SDL_Texture *Bt3_texture = IMG_LoadTexture(renderer, "image/bouton-load.png");
  SDL_Texture *Bt4_texture = IMG_LoadTexture(renderer, "image/bouton-load.png");
  SDL_Texture *Bt4_texture_2 = IMG_LoadTexture(renderer, "image/bouton-quit.png");
  SDL_Texture *Bt4_texture_3 = IMG_LoadTexture(renderer, "image/bouton-start.png");
  SDL_Texture *Bt5_texture = IMG_LoadTexture(renderer, "image/bouton-load.png");
  SDL_Texture *Bt_next = IMG_LoadTexture(renderer, "image/precedent.png");
  SDL_Texture *Nom = IMG_LoadTexture(renderer, "image/bouton-load.png");
  SDL_Texture *niveau_actuelle= Bt4_texture;
  // Récupérer les dimensions de la fenêtre
  int largeur_fenetre, hauteur_fenetre;
  SDL_GetWindowSize(window, &largeur_fenetre, &hauteur_fenetre);
  // Boucle principale du menu
  int continuer = 1;
  int choix = 6;

  SDL_Event evenement;
  while (continuer)
  {
    // Gestion des événements
    while (SDL_PollEvent(&evenement))
    {
      switch (evenement.type)
      {
      case SDL_QUIT:
        continuer = 0;
        break;
      case SDL_MOUSEBUTTONUP:
        if (evenement.button.button == SDL_BUTTON_LEFT)
        {

          // Récupération des coordonnées de la souris lors du clic
          int x = evenement.button.x;
          int y = evenement.button.y;
          //printf("Clic en (%d, %d)", x, y);
          // Vérification si le clic est sur l'un des choix
          if (x >= 275 && x <= 525 && y >= 250 && y <= 350)
          {
            printf("\n Bouton 1 cliqué, lancement du programme\n");
            
            continuer = joueurvsjoueur(0);
            continue;
          }
          if (x >= 275 && x <= 525 && y >= 350 && y <= 450)
          {
            printf("\n Bouton 2 cliqué, choix du theme\n");
            continuer = afficher_theme();
            printf("fin");
            continue;
          }
          if (x >= 275 && x <= 525 && y >= 450 && y <= 550)
          {
            printf("\n Bouton 3 cliqué, chargement de la partie\n");
            if(is_file_empty("code/enregistrement.txt")==1){
              printf(" \nle fichier est vide, lancement d'une nouvelle partie\n");
              continuer = joueurvsjoueur(0);
            }
            else{
            continuer = joueurvsjoueur(1);
            continue;
          }
          }
          if (x >= 275 && x <= 525 && y >= 550 && y <= 650)
          {
            printf("\n Bouton 4 cliqué, versus IA\n");
            printf("\n choix = %d\n",choix);
            continuer = IAvsjoueur(0,choix);
            printf("\n fin versus IA\n");
            continue;
          }
           if (x >= 275 && x <= 525 && y >= 650 && y <= 750)
          {
            printf("\n Bouton 5 cliqué, versus IA\n");
            continuer = 0;
            printf("\n fin versus IA\n");
            continue;
          }
           if (x >= 565 && x <= 665 && y >= 565 && y <= 635)
          {
            printf("\n Bouton modification niveau IA, versus IA\n"); //plus le choix est elevé plus c est facile, si choix =1 tres dur
             if (niveau_actuelle == Bt4_texture)
            {
              niveau_actuelle = Bt4_texture_2;
              choix = 4;
            }
            else if (niveau_actuelle == Bt4_texture_2)
            {
              niveau_actuelle = Bt4_texture_3;
              choix = 1;
            }
            else if (niveau_actuelle== Bt4_texture_3)
            {
              niveau_actuelle = Bt4_texture;
              choix = 6;
            }
            printf("\n fin versus IA\n");
            continue;
          }
          if (x >= 680 && x <= 760 && y >= 50 && y <= 130)
          {
            playAndStop("son/ambiance.wav");
            if (son_actuelle == son_off_texture)
            {
              son_actuelle = son_on_texture;
              
            }
            else
            {
              son_actuelle = son_off_texture;
              
            }
            continue;
          }
          break;
        }
      }
    }
    // Effacement de l'écran
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    // Définir le rectangle de destination pour l'image de fond (ici, on utilise les dimensions de la fenêtre)
    SDL_Rect rect = {0, 0, largeur_fenetre, hauteur_fenetre};

    // rectangle pour les choix
    SDL_Rect rect_choix1 = {275, 250, 250, 100};
    SDL_Rect rect_choix2 = {275, 350, 250, 100};
    SDL_Rect rect_choix3 = {275, 450, 250, 100};
    SDL_Rect rect_choix4 = {275, 550, 250, 100};
    SDL_Rect rect_choix5 = {275, 650, 250, 100};
    SDL_Rect rect_next= {550, 565, 100, 70};
    SDL_Rect rect_nom = {200, 50, 400, 200};
    SDL_Rect son = {680, 50, 80, 80};
    SDL_RenderClear(renderer);

    // Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, son_actuelle, NULL, &son);
    SDL_RenderCopy(renderer, Bstart_texture, NULL, &rect_choix1);
    SDL_RenderCopy(renderer, Bt2_texture, NULL, &rect_choix2);
    SDL_RenderCopy(renderer, Bt3_texture, NULL, &rect_choix3);
    SDL_RenderCopy(renderer, niveau_actuelle, NULL, &rect_choix4);
    SDL_RenderCopy(renderer, Bt5_texture, NULL, &rect_choix5);
    SDL_RenderCopy(renderer, Nom, NULL, &rect_nom);
    SDL_RenderCopy(renderer, Bt_next, NULL, &rect_next);

    // Update Screen
    SDL_RenderPresent(renderer);
  }
  SDL_Texture *textures[] = {
      texture,
      Bstart_texture,
      Bt2_texture,
      Bt3_texture,
      Bt4_texture,
      Bt5_texture,
      son_off_texture,
      son_on_texture,
      Bt4_texture_2,
      Bt4_texture_3,
      Nom,
  };
  int num_textures = sizeof(textures) / sizeof(SDL_Texture *);
  free_textures(textures, num_textures);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  // Quit SDL
  SDL_Quit();
  printf("\n le menu ce ferme\n");
  exit(EXIT_SUCCESS);
}


int afficher_theme()
{
  // fond coloré
  SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
  SDL_RenderClear(renderer);
  // Créer une texture à partir de la surface de l'image
  SDL_Texture *quit_texture = IMG_LoadTexture(renderer, "image/quit.png");
  SDL_Texture *valider_texture = IMG_LoadTexture(renderer, "image/valider.png");
  SDL_Texture *suivant_texture = IMG_LoadTexture(renderer, "image/suivant.png");
  SDL_Texture *precedent_texture = IMG_LoadTexture(renderer, "image/precedent.png");
  SDL_Texture *plateau_texture1 = IMG_LoadTexture(renderer, "image/choix1.png");
  SDL_Texture *plateau_texture2 = IMG_LoadTexture(renderer, "image/choix2.png");
  SDL_Texture *plateau_texture3 = IMG_LoadTexture(renderer, "image/choix3.png");
  SDL_Texture *fond_texture = IMG_LoadTexture(renderer, "image/fond_menu.png");

  SDL_Texture *plateau_texture_actuel = plateau_texture1;

  // Boucle principale du menu
  int continuer = 1;
  int choix = 1;
  SDL_Event evenement;
  while (continuer)
  {
    // Gestion des événements
    while (SDL_PollEvent(&evenement))
    {
      switch (evenement.type)
      {
      case SDL_QUIT:
        return 0;
        break;
      case SDL_MOUSEBUTTONUP:
        if (evenement.button.button == SDL_BUTTON_LEFT)
        {
          // Récupération des coordonnées de la souris lors du clic
          int x = evenement.button.x;
          int y = evenement.button.y;
          // Vérification si le clic est sur l'un des choix
          if (x >= 350 && x <= 450 && y >= 650 && y <= 750)
          {
            printf("valider");
            if (choix == 1)
            {
              grille_texture = IMG_LoadTexture(renderer, "image/Board.png");
              // contour_texture = IMG_LoadTexture(renderer, "image/contour.png");//pour le contour du jeu
              fond_board = IMG_LoadTexture(renderer, "image/fond_board.png");
              carre_grille_texture = IMG_LoadTexture(renderer, "image/carre_grille.png");
              contour_texture = IMG_LoadTexture(renderer, "image/contour_board.png");
              white_texture= IMG_LoadTexture(renderer, "image/pion_blanc.png");
              black_texture= IMG_LoadTexture(renderer, "image/pion_noir.png");
            }
            else if (choix == 2)
            {
              grille_texture = IMG_LoadTexture(renderer, "image/Board2.png");
              // contour_texture = IMG_LoadTexture(renderer, "image/contour.png");//pour le contour du jeu
              fond_board = IMG_LoadTexture(renderer, "image/fond_board2.png");
              carre_grille_texture = IMG_LoadTexture(renderer, "image/carre_grille2.png");
              contour_texture = IMG_LoadTexture(renderer, "image/contour_board2.png");
              white_texture= IMG_LoadTexture(renderer, "image/pion_jaune.png");
              black_texture= IMG_LoadTexture(renderer, "image/pion_bleu.png");
            }
            else if (choix == 3)
            {
              grille_texture = IMG_LoadTexture(renderer, "image/Board3.png");
              // contour_texture = IMG_LoadTexture(renderer, "image/contour.png");//pour le contour du jeu
              fond_board = IMG_LoadTexture(renderer, "image/fond_board3.png");
              carre_grille_texture = IMG_LoadTexture(renderer, "image/carre_grille3.png");
             
              contour_texture = IMG_LoadTexture(renderer, "image/contour_board3.png");
              white_texture= IMG_LoadTexture(renderer, "image/pion_nyan.png");
              black_texture= IMG_LoadTexture(renderer, "image/pion_uni.png");
            }
            afficher_menu();
          }

          if (x >= 75 && x <= 225 && y >= 350 && y <= 450)
          {
            printf("precedent");
            if (plateau_texture_actuel == plateau_texture3)
            {
              plateau_texture_actuel = plateau_texture2;
              choix = 2;
            }
            else if (plateau_texture_actuel == plateau_texture2)
            {
              plateau_texture_actuel = plateau_texture1;
              choix = 1;
            }
            else
            {
              plateau_texture_actuel = plateau_texture3;
              choix = 3;
            }
            // Appel de la fonction pour le choix 2
          }
          if (x >= 600 && x <= 750 && y >= 350 && y <= 450)
          {
            if (plateau_texture_actuel == plateau_texture1)
            {
              plateau_texture_actuel = plateau_texture2;
              choix = 2;
            }
            else if (plateau_texture_actuel == plateau_texture2)
            {
              plateau_texture_actuel = plateau_texture3;
              choix = 3;
            }
            else
            {
              plateau_texture_actuel = plateau_texture1;
              choix = 1;
            }
            printf("suivant");
            // Appel de la fonction pour le choix 3
          }
          if (x >= 640 && x <= 740 && y >= 70 && y <= 170)
          {
            printf("\n Retour menu principale \n");
            afficher_menu();
          }
          break;
        }
      }
    }

    SDL_RenderClear(renderer);

    // rectangle pour les choix
    SDL_Rect valider = {350, 650, 100, 100};
    SDL_Rect suivant = {75, 350, 150, 100};
    SDL_Rect precedent = {600, 350, 150, 100}; // suivant et precedent sont inversé
    SDL_Rect quit = {640, 70, 100, 100};
    SDL_Rect plateau = {235, 200, 350, 350};
    int largeur_fenetre, hauteur_fenetre;
    SDL_GetWindowSize(window, &largeur_fenetre, &hauteur_fenetre);
    SDL_Rect fond_rect = {0, 0, largeur_fenetre, hauteur_fenetre};

    // Copier la texture sur le renderer avec le rectangle de destination spécifié(affiche le png)

    SDL_RenderCopy(renderer, fond_texture, NULL, &fond_rect);
    SDL_RenderCopy(renderer, valider_texture, NULL, &valider);
    SDL_RenderCopy(renderer, suivant_texture, NULL, &suivant);
    SDL_RenderCopy(renderer, precedent_texture, NULL, &precedent);
    SDL_RenderCopy(renderer, quit_texture, NULL, &quit);
    SDL_RenderCopy(renderer, plateau_texture_actuel, NULL, &plateau);

    // Update Screen
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