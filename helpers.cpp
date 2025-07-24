#include "helpers.h"
#include "tile.h"

using namespace std;

/**
 * @brief makeTile Creates a Tile based on the TileType
 *  x X Window co-ordinate in pixels.
 *  y Y Window co-ordinate in pixels.
 
 */
Tile makeTile(int x, int y, TileType t, Direction dir)
{
		switch(t){
		case Wall:
			return Tile(x, y, {{7,16}},t,1,1);
		case Food:
			return Tile(x, y, {{10,1}},t,1,1);
		case Blank:
			return Tile(x, y, {{1,4}},t,1,1);
		case Pacman:
			switch(dir){
				case Up:
					return Tile(x,y, {{3,1},{3,2},{3,1},{3,3}},t,1,1);
				case Left:
					return Tile(x,y, {{1,1},{1,2},{1,1},{1,3}},t,1,1);
				case Down:
					return Tile(x,y, {{4,1},{4,2},{4,1},{4,3}},t,1,1);
//				case Right:
				default:
					return Tile(x,y, {{2,1},{2,2},{2,1},{2,3}},t,1,1);
			}
		case MrsPacman:
			switch(dir){
				case Up:
					return Tile(x,y, {{3,5},{3,6},{3,5},{3,7}},t,1,1);
				case Left:
					return Tile(x,y, {{1,5},{1,6},{1,5},{1,7}},t,1,1);
				case Down:
					return Tile(x,y, {{4,5},{4,6},{4,5},{4,7}},t,1,1);
//				case Right:
				default:
					return Tile(x,y, {{2,5},{2,6},{2,5},{2,7}},t,1,1);
			}
		
		
	}
}

bool collision(SDL_Rect a, SDL_Rect b, int a_off, int b_off)
{
	// If A finishs above B - No Collision
	if (a.y-a.h*Tile::tileHeight+a_off>=b.y-b_off)
	{
		return false;
	}

	// If A starts below B - No Collision
	if (a.y-a_off<=b.y-b.h*Tile::tileHeight+b_off)
	{
		return false;
	}

	// If the right of A is left of B - No Collision
	if (a.x+a.w*Tile::tileWidth-a_off<=b.x+b_off)
	{
		return false;
	}

	// If the left of A is right of B - No Collision
	if (a.x+a_off>=b.x+b.w*Tile::tileWidth-b_off)
	{
		return false;
	}

	// If we get here there must be an overlap - Collision
	return true;
}


vector<Tile> getTestTiles()
{
    vector<Tile> testTiles;
    testTiles.push_back(makeTile(0 ,0,Pacman, Up));
    testTiles.push_back(makeTile(20,0,Pacman, Down));
    testTiles.push_back(makeTile(40,0,Pacman, Left));
    testTiles.push_back(makeTile(60,0,Pacman, Right));

    testTiles.push_back(makeTile(0 ,20,MrsPacman, Up));
    testTiles.push_back(makeTile(20,20,MrsPacman, Down));
    testTiles.push_back(makeTile(40,20,MrsPacman, Left));
    testTiles.push_back(makeTile(60,20,MrsPacman, Right));

    testTiles.push_back(makeTile(0 ,40,Wall));
    testTiles.push_back(makeTile(20,40,Blank));
    testTiles.push_back(makeTile(40,40,Food));

    int lastY = 40;
    for(TileType t : {GhostR, GhostY, GhostP, GhostB}){
        lastY += 20;
        testTiles.push_back(makeTile(0 ,lastY,t, Up));
        testTiles.push_back(makeTile(20,lastY,t, Down));
        testTiles.push_back(makeTile(40,lastY,t, Left));
        testTiles.push_back(makeTile(60,lastY,t, Right));
    }
    return testTiles;
}
