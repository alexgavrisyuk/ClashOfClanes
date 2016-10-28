#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace cocos2d;

class GameScene;

class Factory : public GraphicComponent
{
public:
	Factory(){};
	~Factory(){};

	virtual void Update(GameScene& scene) = 0;
};

#endif