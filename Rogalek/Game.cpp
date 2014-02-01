#include <vector>
#include <iostream>
#include "Game.h"
#include "Graphics.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

ResourceManager<Sprite> SpriteManager;
Graphics GraphicsManager;
std::vector<int> sprite_Handles;

void gameLoop()
{
	sprite_Handles.push_back(SpriteManager.Add("ground.png"));
	sprite_Handles.push_back(SpriteManager.Add("player.png"));

	GraphicsManager.DrawSprite("ground.png",0,0,0, SpriteManager);

	al_flip_display();
	al_rest(2.0);
	cleanUp();
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
			//std::cout << SpriteManager[*i]->ToString() << std::endl;
	}
}