#include <stdio.h>
#include "graphics_sdl.h"

void rectangle(int x, double y, int w, double h);
int program = 1;
FILE *fp;
int cycle;
int i;
int j;
double it;
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
  fprintf(fp, "F6000\n");
  fprintf(fp, "M3 S0\n");
 
 
  it = 0;
  fprintf(fp, "S1000\n"); 
  /* FRAME */
  rectangle(0, 100, 100, 100); /*1*/
  it = 0; 
  rectangle(90, 90, 10, 900); /*1*/
  it = 0;
  rectangle(0, 10, 90, 100); /*1*/
  it = 0;
  rectangle(0, 90, 10, 900); /*1*/
  it = 0;

  it = 0;
  fprintf(fp, "S0\n");
  
  rectangle(10, 60, 20, 200); 
  it = 0;
  rectangle(40, 90, 20, 200);
  it = 0;
  rectangle(70, 60, 20, 200);
  it = 0;
  rectangle(40, 30, 20, 200); 
  it = 0;
  rectangle(20, 70, 10, 100);
  it = 0;
  rectangle(20, 80, 10, 100);
  it = 0;
  rectangle(30, 80, 10, 100); 
  it = 0;
  rectangle(60, 80, 10, 100); 
  it = 0;
  rectangle(70, 80, 10, 100); 
  it = 0;
  rectangle(70, 70, 10, 100);
  it = 0;
  rectangle(70, 40, 10, 100);
  it = 0;
  rectangle(70, 30, 10, 100); 
  it = 0;
  rectangle(60, 30, 10, 100);
  it = 0;
  rectangle(30, 30, 10, 100);
  it = 0;
  rectangle(20, 30, 10, 100); 
  it = 0;
  rectangle(20, 40, 10, 100);
  it = 0;
  rectangle(40, 60, 20, 200);

  fprintf(fp, "M5 S0\n");
  fprintf(fp, "G0 X0 Y0\n");
  return 1;
}

void rectangle(int x, double y, int w, double h) /* (x&y&w 100 = 10cm) (height 1000 = 10cm)*/
{ 
  fprintf(fp, "G0 X%d Y%.2f\n", x, y);
  for(i = 0; i < h/2; i++)
  {
    fprintf(fp, "S1000\n");
    fprintf(fp, "G1 X%d Y%.2f\n", x+w, y-it);
    fprintf(fp, "G1 X%d Y%.2f\n", x+w, y-it- 0.1);
    fprintf(fp, "G1 X%d Y%.2f\n", x, y-it- 0.1);
    fprintf(fp, "G1 X%d Y%.2f\n", x, y-it- 0.2);
    it = it + 0.2;
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
