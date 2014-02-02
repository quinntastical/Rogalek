#include <vector>
#include <iostream>
#include "Game.h"
#include "Consts.h"
#include "Graphics.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

ResourceManager<Sprite> SpriteManager;
Graphics GraphicsManager;
std::vector<int> sprite_Handles;

int mapArray[mapHeight][mapWidth];

void gameLoop()
{
	GraphicsManager.DrawSprite("ground.png",0,0,0, SpriteManager);

	al_flip_display();
	al_rest(2.0);
	cleanUp();
}

void loadResources()
{
	sprite_Handles.push_back(SpriteManager.Add("ground.png"));
	sprite_Handles.push_back(SpriteManager.Add("player.png"));
	sprite_Handles.push_back(SpriteManager.Add("wall.png"));
	sprite_Handles.push_back(SpriteManager.Add("closed_door.png"));
	sprite_Handles.push_back(SpriteManager.Add("open_door.png"));
}

void cleanUp()
{
	for(std::vector<int>::iterator i = sprite_Handles.begin();
		i != sprite_Handles.end(); i++)
	{
		Sprite *r = SpriteManager[*i];
		if(r != NULL)
			std::cout << "Cleaning up handle: " << SpriteManager[*i]->getHandle() << std::endl;
			SpriteManager.Remove(SpriteManager[*i]->getHandle());
	}
}
