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
	//��Ϸ��ͼ��
	//GameLayer *gameLayer;
	//ControlLayer *controlLayer;
	//��Ϸ��ͼ
	GameMap *gameMap;
	//Ŀ���ͼ�Ĳ���
	int currentLevel;
};

#define sGlobal Global::instance()

enum {
	zGameLayer = 1,
};
#endif