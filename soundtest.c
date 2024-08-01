// Sound testing
#include<stdio.h>
#include<SDL2/SDL.h>

SDL_AudioDeviceID initAudio(Uint8 **buffer, Uint32 *len) {
    SDL_AudioSpec wavSpec;

    SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    SDL_LoadWAV("fire.wav", &wavSpec, buffer, len);
    return SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

int main(void) {
    SDL_AudioDeviceID audioId;
    Uint32 fireLen = 0;
    Uint8 *fireBuffer = NULL;

    audioId = initAudio(&fireBuffer, &fireLen);

    SDL_QueueAudio(audioId, fireBuffer, fireLen);
    SDL_PauseAudioDevice(audioId, 0);
    SDL_Delay(5000);

    SDL_CloseAudioDevice(audioId);
    SDL_FreeWAV(fireBuffer);
    SDL_Quit();
    return 0;
}