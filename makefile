CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf


coasterCAM:  main.o graphics_sdl.o pages.o 
	$(CC) -o coasterCAM main.o graphics_sdl.o pages.o -I. $(LIBS) $(DEPS)

.PHONY:clean

clean:
	find . -name "*.o" -type f -delete
	
                                      
