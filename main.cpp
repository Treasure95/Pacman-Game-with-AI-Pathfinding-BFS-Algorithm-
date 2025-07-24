#include <iostream>
#include <thread>
#include <chrono>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "helpers.h"
#include "character.h"
#include "world.h"

using namespace std;

int main()
{
    // SpriteSheet Filename
    string spriteFilename = SPRITEFILENAME; // Leave this line

    // Setup and Load Texture object here
    Tile::tileWidth=20;
    Tile::tileHeight=20;
    Texture myTexture;
    myTexture.loadFile(spriteFilename, Tile::tileWidth, Tile::tileHeight);
    bool quit = false;
//    Tile pm(0,0,{{1,1},{1,2},{1,1},{1,3}},Pacman,1,1);
    int frame=1;

    World myWorld(MAZEFILENAME,myTexture.tileWidth(),myTexture.tileHeight());

    myTexture.scaleGraphics(myWorld.rows, myWorld.cols);
    while(!quit){
        // Handle any SDL Events
	//  resize, clicking the close button,
        //  and process and key press events.
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			quit = true;
		}
		myTexture.handle_event(e, myWorld.rows, myWorld.cols);
		myWorld.pacman.handle_event(e);
	}
	// Update the Game State Information
	myWorld.UpdateWorld();
	SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myTexture.myWin.sdlRenderer);
	// Set background to black
	SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 0xFF);
	// Clear the renderer
	SDL_RenderClear(myTexture.myWin.sdlRenderer);
	// Render the tile
//	pm.render(&myTexture, frame);
/*	for(Character i : {myPacman,myMrsPacman,myRGhost}){
		i.render(&myTexture, frame);
	}*/
	
//	SDL_RenderPresent(myTexture.myWin.sdlRenderer);
	myWorld.render(&myTexture, frame);
	SDL_RenderPresent(myTexture.myWin.sdlRenderer);
        
	frame++;
	this_thread::sleep_for(chrono::milliseconds(75));
        
    }

    return 0;
}
