
#include "struct.h"



static int currentChannel = -1;
static bool isPlaying = false;
void son() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
     
    }

    // Initialiser SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
   
    }

    // Jouer le son et obtenir le canal de lecture
   playAndStop("son/ambiance.wav");



}



void playAndStop(const char *filename) {
    static Mix_Chunk *son = NULL;
    
    if (!isPlaying) {
        // Charger le fichier audio WAV s'il n'a pas été chargé
        if (!son) {
            son = Mix_LoadWAV(filename);
            if (!son) {
                printf("Erreur lors du chargement du fichier audio: %s\n", Mix_GetError());
                return;
            }
        }

        // Jouer le son
        currentChannel = Mix_PlayChannel(-1, son, 0);
        if (currentChannel == -1) {
            printf("Erreur lors de la lecture du fichier audio: %s\n", Mix_GetError());
            return;
        }
        Mix_Volume(currentChannel, 15);
        isPlaying = true;
    } else {
        // Arrêter le son
        Mix_HaltChannel(currentChannel);
        isPlaying = false;
    }
}
void playSound(const char *filename) {
    Mix_Chunk *son = NULL;

    // Charger le fichier audio WAV
    son = Mix_LoadWAV(filename);
    if (!son) {
        printf("Erreur lors du chargement du fichier audio: %s\n", Mix_GetError());
        return;
    }

    // Jouer le son sur un canal libre
    int channel = Mix_PlayChannel(-1, son, 0);
    if (channel == -1) {
        printf("Erreur lors de la lecture du fichier audio: %s\n", Mix_GetError());
        Mix_FreeChunk(son);
        return;
    }

    Mix_Volume(channel, 128);
}