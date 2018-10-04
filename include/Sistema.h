#ifndef __SISTEMA_H
#define __SISTEMA_H

#include <SDL.h>
#include "Shapes.h"
#include "Massa.h"

#define M 1.0
#define K_LINHA 10

#define N_MASSES 4

typedef struct {
	Massa massas[N_MASSES];

	int y0;
	int width;
} Sistema;

void initSistema (Sistema *sis, int width, int y0, int ys[N_MASSES]);

void updateSistema (Sistema *sis, double delta_t);

void drawSistema (SDL_Renderer *ren, Sistema *sis);

#endif /* __SISTEMA_H */