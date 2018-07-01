#include <stdio.h>
#include "graphics_sdl.h"

void rectangle(double x, double y, double w, double h);
int program = 1;
FILE *fp;
int cycle;
int i;
int j;
double it;
double y;
int k;
int dir = 0;
int main()
{
  
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
   
  #ifdef LUKA
  fp = fopen("/home/luka/coasterCAM/data/output.gcode", "w");
  #endif
  
  #ifdef LASER
  fp = fopen("/home/laser/coasterCAM/data/output.gcode", "w");
  #endif
  fprintf(fp, "G90\n");  
  fprintf(fp, "F8000\n");
  fprintf(fp, "M3 S0\n");
  
 
  it = 0;
  fprintf(fp, "S1000\n"); 
  /* FRAME */
 /*
  rectangle(0, 0, 100, 10); /1/
  it = 0; 
  rectangle(99, 10, 10, 990); /1/
  it = 0;
  rectangle(0, 99.9, 99, 10); /1/
  it = 0;
  rectangle(0, 99.9, 1, 990); /1/
  it = 0;
*/
  
  rectangle(0, 0, 100, 1000); 

  it = 0;
  fprintf(fp, "S0\n");
   

  fprintf(fp, "M5 S0\n");
  fprintf(fp, "G0 X0 Y0\n");
  return 1;
}

void rectangle(double x, double y, double w, double h) /* (x&y&w 100 = 10cm) (height 1000 = 10cm)*/
{ 
  fprintf(fp, "G0 X%0.2f Y%.2f\n", x, y);
  for(i = 0; i < h; i++)
  {
    fprintf(fp, "S1000\n");
    
    if(dir==0)
    {
      fprintf(fp, "G1 X%0.2f Y%.2f\n", x+w, y+it);
      fprintf(fp, "G1 X%0.2f Y%.2f\n", x+w, y+it+0.1); 
      it = it + 0.1;
      dir = 1;
    }
    else
    {
      fprintf(fp, "G1 X%0.2f Y%.2f\n", x, y+it);
      fprintf(fp, "G1 X%0.2f Y%.2f\n", x, y+it+0.1);
      it = it + 0.1;
      dir = 0;
    }

  } 
  fprintf(fp, "S0\n");  
}

 
  /*  FREE FORM
  for(i = 1; i < 1921; i++)
  {
    for(j = 1; j < 1081; j++)
    {
      if(coord[i][j] == 1)
      {
         fprintf(fp, "G1 X%.2f Y%.2f\n", ((double)i/10), ((double)j/10)); 
         fprintf(fp, "S255\n");

      }
      

    }
  }*/
