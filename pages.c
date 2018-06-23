#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"

char xBuff[30];
char yBuff[30];

void pageOne()
{
  sprintf(xBuff, "X: %d", touchLocation.x);
  sprintf(yBuff, "Y: %d", touchLocation.y);
  renderText(xBuff, regularText, whiteColor);
  render(70, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
  renderText(yBuff, regularText, whiteColor);
  render(70, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
 
}

