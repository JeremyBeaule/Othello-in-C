#include "code/struct.h"


int main(int argc, char *argv[]) {
    printf("coucou");
int choix;
// tout initialiser (texture/png...)
init_All();

choix =afficher_menu(renderer); //fichier affichage.c
if (choix==1){
start(); // fichier game.c

}
return 0;
}
