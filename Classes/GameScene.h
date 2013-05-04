#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMap.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCLayer
{
public:

	GameScene(void);
	~GameScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene *playNewGame();
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

protected:
	GameMap *map;

};

#endif  // __GAME_SCENE_H__