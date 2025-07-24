#include "tile.h"

int Tile::tileWidth = -1;
int Tile::tileHeight = -1;

/**
 *  Tile::Tile Constructs the tile object.
 *  windowX X co-ordinate (in pixels) of the top left corner for rendering.
 *  windowY Y co-ordinate (in pixels) of the top left corner for rendering.
 *  frames Vector of {row, col} co-ordinates for images in the animation.
 *  spriteWidth The width of the animation in tiles (usually 1).
 *  spriteHeight The height of the animation in tiles (usually 1).
 */
Tile::Tile(int windowX, int windowY, std::vector<std::pair<int, int> > frames, TileType t, int spriteWidth, int spriteHeight)
{
	x=windowX;
	y=windowY;
	myFrames=frames;
	myType=t;
	w=spriteWidth;
	h=spriteHeight;
}
/* *render Uses the texture object to render a frame from the current tile.
 * The Texture object to use.
 * The frame % numFrames that should be rendered.
 */
void Tile::render(Texture *t, int frame)
{
	t->render(x,y,myFrames[frame%myFrames.size()].first,myFrames[frame%myFrames.size()].second,w,h);
}
