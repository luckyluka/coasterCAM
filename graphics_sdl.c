#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"



int init()    /* things needed to start sdl2 properly */
{
  int flags;
  int innited;
 
  flags = IMG_INIT_JPG|IMG_INIT_PNG;
  innited = IMG_Init(flags);
	
  if((SDL_Init(SDL_INIT_VIDEO||SDL_INIT_EVENTS)) != 0)
  {
    SDL_Log("Unable to initialize SDL:%s ", SDL_GetError());
    return 1;                                                                               
  }  

  window = SDL_CreateWindow("IT-Elektronika", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
   

  if(window == NULL)
  {
    return 1;
  }		  

  renderer = SDL_CreateRenderer(window, - 1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL)
  {
    ;
    /*printf("RENDERER IS NULL\n");*/
  }

  if((innited&flags) != flags)
  {
    
    printf("IMG_INIT: %s\n", IMG_GetError());
  }

  if(TTF_Init() != 0)
  {
    printf("TTF ERROR: %s\n", TTF_GetError());
  }

  #ifdef RPI
  smallText = TTF_OpenFont("/home/pi/coasterCAM/font/DejaVuSansMono.ttf", 30);
  if(smallText == NULL)
  {
    printf("NO FONT FOUND:%s\n", TTF_GetError());
  }
  regularText = TTF_OpenFont("/home/pi/coasterCAM/font/DejaVuSansMono.ttf", 45);
  if(regularText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  #endif
  #ifdef LUKA
  smallText = TTF_OpenFont("/home/luka/coasterCAM/font/DejaVuSansMono.ttf", 30);
  if(smallText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  regularText = TTF_OpenFont("/home/luka/coasterCAM/font/DejaVuSansMono.ttf", 45);
  if(regularText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  #endif

  return 15;
}


void initVars()
{
 /* color definitions  */
  whiteColor.r = 255;
  whiteColor.g = 255;
  whiteColor.b = 255;
  
  blackColor.r = 0;
  blackColor.g = 0;
  blackColor.b = 0;

  
}

void freeTexture(void)  
{
  if(texture != NULL)
  {
    SDL_DestroyTexture(texture);	  
    texture = NULL;
    textureWidth = 0;
    textureHeight = 0;
  }
}

void renderBackground(void)     
{
  switch(backgroundColor)
  {
    case 0:
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /*black*/
      break; 
    
  }
  SDL_RenderClear(renderer);
}

void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect renderQuad;
  renderQuad.x = x;
  renderQuad.y = y;
  renderQuad.w = textureWidth;
  renderQuad.h = textureHeight;

  if(clip != NULL)
  {
    renderQuad.w = clip -> w;
    renderQuad.h = clip -> h;
  }
  SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int renderText(const char *text, TTF_Font *textFont,  SDL_Color textColor)  
{
  SDL_Surface* textSurface;
  textSurface = TTF_RenderText_Solid(textFont, text, textColor);
  freeTexture();

  if(textSurface == NULL)
  {
    printf("Unable to render text surface! SDL Error: %s\n", SDL_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = textSurface -> w;
      textureHeight = textSurface -> h;
    }
    SDL_FreeSurface(textSurface);
  }
  return texture != NULL;
}


void renderContent()
{
  switch(page)
  {
    case 0:
      pageOne(); /* main page */
      backgroundColor = 1;
      sbarText = 0;
      break;
  }

  oldtimestamp=timestamp;
  cycleCounter++;
}

void touchUpdate()   /* handling touch events */
{
  if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    click = 1;
  }
  else if(event.type == SDL_MOUSEBUTTONUP)
  {
    click = 0;
  }
  
  if(click == 1)
  {
    coord[touchLocation.x][touchLocation.y] = 1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, touchLocation.x, touchLocation.y);
  } 


  while(SDL_PollEvent(&event) != 0 )
  {
    #ifdef RPI
    if(event.type == SDL_FINGERDOWN)  
    {
      
      timestamp = event.tfinger.timestamp;
      touchLocation.x = event.tfinger.x;
      touchLocation.y = event.tfinger.y;
    }
    #endif
    #ifdef LUKA
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      timestamp = event.button.timestamp;
      touchLocation.x = event.button.x;
      touchLocation.y = event.button.y;
      
    }
    if(event.type == SDL_MOUSEMOTION)
    {
      
      timestamp = event.button.timestamp;
      touchLocation.x = event.button.x;
      touchLocation.y = event.button.y;
    }

    else if(event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          program = 0;
          break;
      }
    }
    #endif
     
  }  
}


void saveButton(int x, int y, int w, int h, char *text)
{
  int i;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    for(i = 0; i < 10; i++)
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderDrawLine(renderer, x, y+i, (x+w), y+i);
      SDL_RenderDrawLine(renderer, (x+w+i), y, (x+w+i), (y+h)); 
      SDL_RenderDrawLine(renderer, (x+w), (y+h-i), x, (y+h-i));
      SDL_RenderDrawLine(renderer, x+i, (y+h), x+i, y);
    }


  }
  renderText(text, smallText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 


}

void renderAdmin(int x, int y, int w, int h, int curr_page, int gotoNum) 
{
  int i;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  for(i = 0; i < 5; ++i)
  {
    SDL_RenderDrawLine(renderer, x, y+i, (x+w), y+i);
    SDL_RenderDrawLine(renderer, (x+w+i), y, (x+w+i), (y+h)); 
  
    SDL_RenderDrawLine(renderer, x+i, (y+h), x+i, y);
  }
  renderText("...", regularText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2+10)), NULL, 0.0, NULL, SDL_FLIP_NONE); 

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp && cycleCounter != cycleCheck)
  {
    cycleCheck = cycleCounter;
    page = gotoNum;
    page_stage[curr_page] = 2;
  }
}


