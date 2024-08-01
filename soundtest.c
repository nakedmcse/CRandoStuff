// Sound testing
#include<stdio.h>
#include<SDL2/SDL.h>

int main(void) {
    SDL_AudioDeviceID audioId;
    SDL_AudioSpec wavSpec;
    Uint32 fireLen = 0;
    Uint8 *fireBuffer = NULL;

    SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    SDL_LoadWAV("fire.wav", &wavSpec, &fireBuffer, &fireLen);
    audioId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    SDL_QueueAudio(audioId, fireBuffer, fireLen);
    SDL_PauseAudioDevice(audioId, 0);
    SDL_Delay(5000);

    SDL_CloseAudioDevice(audioId);
    SDL_FreeWAV(fireBuffer);
    SDL_Quit();
    return 0;
}