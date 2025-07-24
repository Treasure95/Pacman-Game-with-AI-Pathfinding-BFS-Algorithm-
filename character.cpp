#include "character.h"
#include "tile.h"
#include "helpers.h"


Character::Character(int myX, int myY, TileType t)
    : uTile(makeTile(myX,myY,t,Up)), dTile(makeTile(myX,myY,t,Down)), lTile(makeTile(myX,myY,t,Left)), rTile(makeTile(myX,myY,t,Right))
{
    x=myX;
    y=myY;
    dir=Up;
    
}


void Character::render(Texture *t, int frame)
{
	switch (dir){
		case Up:
			uTile.render(t,frame);
			break;
		case Down:
			dTile.render(t,frame);
			break;
		case Left:
			lTile.render(t,frame);
			break;
		case Right:
			rTile.render(t,frame);
			break;
	}
}

SDL_Rect Character::getNextPosition()
{
	SDL_Rect temp;
	switch (dir)
	{
		case Up:
		{
			temp.x = x;
			temp.y = y-5;
			temp.w = this->uTile.w;
			temp.h = this->uTile.h;
		}
		break;
		case Down:
		{
			temp.x = x;
			temp.y = y+5;
			temp.w = this->dTile.w;
			temp.h = this->dTile.h;
		}
		break;
		case Left:
		{
			temp.x = x-5;
			temp.y = y;
			temp.w = this->lTile.w;
			temp.h = this->lTile.h;
		}
		break;
		case Right:
		{
			temp.x = x+5;
			temp.y = y;
			temp.w = this->rTile.w;
			temp.h = this->rTile.h;
		}
		break;
	}
	return temp;
}
//arrows keys

void Character::handle_event(const SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjustment of the speed

        switch( e.key.keysym.sym )
        {
            case SDLK_UP:    dir = Up; break;
            case SDLK_DOWN:  dir = Down; break;
            case SDLK_LEFT:  dir = Left; break;
            case SDLK_RIGHT: dir = Right; break;
        }
    }
}
