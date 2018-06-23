#include <stdio.h>
#include "graphics_sdl.h"

int program = 1;

int main()
{
  FILE *fp;

  int cycle;
  int i;
  int j;
  printf("MAIN\n");
  init();
  initVars();
  renderBackground();
  
  click = 0;
  while(program == 1)
  {
    
    touchUpdate();
    renderContent();
    SDL_RenderPresent(renderer); 
  
    
    cycle++;
  }
   

  fp = fopen("/home/luka/coasterCAM/data/output.gcode", "w");
  fprintf(fp, "G90\n");  
  fprintf(fp, "F3000\n");
  fprintf(fp, "M3 S0\n");
  for(i = 1; i < 1921; i++)
  {
    for(j = 1; j < 1081; j++)
    {
      if(coord[i][j] == 1)
      {
         fprintf(fp, "X%.2f Y%.2f\n", (double)(i/10), (double)(j/10)); 
         fprintf(fp, "S255\n");
      }
    }
  }
  fprintf(fp, "M5 S0\n");
  fprintf(fp, "X0 Y0\n");
  return 1;
}



