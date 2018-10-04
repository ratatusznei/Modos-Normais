/*
	Por:
		Fernando Henrique Ratusznei Caetano
*/

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Sistema.h"

#define FPS 60
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC / FPS)
#define DELTA_T (1.0 / FPS)

#define SCREEN_NAME "Modos normais"
#define SCREEN_W 700
#define SCREEN_H 400

int initWindow (SDL_Renderer **ren);

#define N_ARGS 4
#define USAGE "Usage: %s <Posicoes y iniciais a partir do equilibrio>\n\n"

int main (int argc, char *argv[]) {
	if (argc != N_ARGS + 1) {
		fprintf(stderr, USAGE, argv[0]);
		return 1;
	}

	Sistema *sis = malloc(sizeof(Sistema));
	int ys[4] = {
		200 - atoi(argv[0]),
		200 - atoi(argv[1]),
		200 - atoi(argv[2]),
		200 - atoi(argv[3]),
	};

	clock_t start_time;

	SDL_Renderer *ren;
	SDL_Event event;
	int quit = 0;

	if (!initWindow(&ren)) {
		fprintf(stderr, "Erro ao criar janela\n");

		SDL_Quit();
		free(sis);
		return 1;
	}

	initSistema(sis, SCREEN_W, SCREEN_H / 2, ys);

	int i = 0;
	while (!quit) {
		start_time = clock();

		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0);
		SDL_RenderClear(ren);

		updateSistema(sis, DELTA_T);
		drawSistema(ren, sis);

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}

			if (event.type == SDL_KEYDOWN) {
				SDL_Keycode key = event.key.keysym.sym;

				if (key == SDLK_q) {
					quit = 1;
				}
			}
		}

		SDL_RenderPresent(ren);
		while (clock() - start_time < CLOCKS_PER_FRAME) {
			/* wait */
		}
		printf("Tempo de simulacao: %.2lf\n", i++ * DELTA_T);
	}

	SDL_Quit();
	free(sis);
	return 0;
}

int initWindow (SDL_Renderer **ren) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(stderr, "SDL_Init");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow(
		SCREEN_NAME,
		150, 150,
		SCREEN_W, SCREEN_H,
		SDL_WINDOW_SHOWN
	);
	if (!win) {
		fprintf(stderr, "SDL_CreateWindow\n");
		SDL_Quit();
		return 1;
	}

	*ren = SDL_CreateRenderer(
		win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!*ren) {
		fprintf(stderr, "SDL_CreateRenderer\n");
		SDL_Quit();
		return 1;
	}
}
