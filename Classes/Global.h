#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Singleton.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameScene;
class GameMap;
//class ControlLayer;

class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	GameScene *gameScene;
	//游戏主图层
	//GameLayer *gameLayer;
	//ControlLayer *controlLayer;
	//游戏地图
	GameMap *gameMap;
	//目标地图的层数
	int currentLevel;
};

#define sGlobal Global::instance()

enum {
	zGameLayer = 1,
};
#endif