#include "world.h"
#include "helpers.h"
#include "character.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;
/**
 * Constructing the World object loading a maze from the supplied file.
 *
 * filename - File from which the maze should be read.
 * TileWidth - Width of each tile
 * TileHeight - Height of each tile
 */
World::World(string filename, int tileWidth, int tileHeight)
    : food(0), points(0), ready(true), pacman(0,0,Pacman)
{
	ifstream f(filename);
	if(!f.is_open())
		throw runtime_error("Couldn't open maze file " + filename);
	// Code to read in the file...
	f>>rows;
	f>>cols;
	char currTile;
	for (int i=0; i<rows; i++)
	{
		vector<Tile> temp;
		maze.push_back (temp);
		for(int j=0; j<cols; j++)
		{
//			Tile tempTile=makeTile(i*tileWidth,j*tileHeight,Wall);
//			f >>currTile;
			if (j!=0)
			{
//				f>>noskipws;
				f>>currTile;
//				f>>skipws;
			}
			else
			{
				f>>skipws;
				f>>currTile;
				f>>noskipws;
			}
			switch (currTile)
			{
				case 'x':
	//				tempTile=makeTile(i*tileWidth,j*tileHeight,Wall);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Wall));
					break;
				case ' ':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Blank);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
					break;
				case '.':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Food);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Food));
					food++;
					break;
				case '0':
					{
//						tempTile=makeTile(i,j,Blank);
						maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
//						Character tempPacman(i,j,Pacman);
//						pacman=makeTile(i*tileWidth,j*tileHeight,Blank);
//						pacman=Character(int i, int j, Pacman);
						pacman.x=j*tileWidth;
						pacman.y=i*tileHeight;
						(pacman.uTile).x=j*tileWidth;
						(pacman.uTile).y=i*tileHeight;
						(pacman.dTile).x=j*tileWidth;
						(pacman.dTile).y=i*tileHeight;
						(pacman.rTile).x=j*tileWidth;
						(pacman.rTile).y=i*tileHeight;
						(pacman.lTile).x=j*tileWidth;
						(pacman.lTile).y=i*tileHeight;
					}
					break;
				case '1':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Blank);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
					break;
				case '2':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Blank);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
					break;
				case '3':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Blank);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
					break;
				case '4':
//					tempTile=makeTile(i*tileWidth,j*tileHeight,Blank);
					maze[i].push_back(makeTile(j*tileWidth,i*tileHeight,Blank));
					break;
			}
//			maze[i].push_back(tempTile);
		}
	}            
}

/**
 * Renders the World to the ::sdlRenderer buffer.
 * It calls the respective render functions on each tile first.
 * Following this, it calls the pacman and ghost objects to render
 * them above the background.
 * frame [optional] An optional frame number to pass to the objects to handle animation.
 */
void World::render(Texture *t, int frame)
{
	for (int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			maze[i][j].render(t, frame);
		}
	}
	pacman.render(t,frame);
	if (food==0)
	{
		Tile gameOver(72,100,{{8,12},{15,12}},Blank,5,1);
		gameOver.render(t,frame);
	}
}

/**
 * This function is responsible for advancing the game state.
 * Pacman and the ghosts should be moved (if possible). If pacman is
 * captured by a ghost pacman.dead should be set to true. If pacman eats
 * a food pellet the relevant totals should be updated.
 *
 * @return The same value as World::ready, indicating whether the game is finished.
 */
bool World::UpdateWorld()
{
	SDL_Rect nextPos=pacman.getNextPosition();
	
//	int countj=0;
//	int counti=0;
	for (vector<Tile>& i : maze)
	{
		for (Tile& j : i)
		{
//				j.myType=Food;
//				cout << "aaaaaaaa\t" <<j.myType << "\t" << j.x << "\t" << j.y << endl;

			SDL_Rect temp = {j.x,j.y,j.w,j.h};
			if (collision(nextPos, temp, 3,2)==true && j.myType==Wall)
			{				
				return ready;
			}
			else if (collision(nextPos, temp, 5,5)==true && j.myType==Food)
			{
				points++;
				food--;
				j.myType=Blank;
				j.myFrames={{1,4}};
				cout << "\tscore: \t" << points /*<< "\tfood\t"<<food <<"\ttype\t"<<j.myType <<"\tmazeij\t"<<maze[counti][countj].myType*/<< endl;
				goto movement;
			}
//			countj++;
		}
//		counti++;
	}
	
	movement:

		pacman.x=nextPos.x;
		pacman.y=nextPos.y;
		(pacman.uTile).x=nextPos.x;
		(pacman.uTile).y=nextPos.y;
		(pacman.dTile).x=nextPos.x;
		(pacman.dTile).y=nextPos.y;
		(pacman.rTile).x=nextPos.x;
		(pacman.rTile).y=nextPos.y;
		(pacman.lTile).x=nextPos.x;
		(pacman.lTile).y=nextPos.y;

		if (food==0)
		{
			cout<<"all food eaten"<<endl;
			
		}
		return ready;
}
