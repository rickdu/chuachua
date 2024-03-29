#include "GameScene.h"
#include "Global.h"
#include "GameMap.h"

using namespace cocos2d;


GameScene::GameScene(void)
{
	sGlobal->gameScene = this;
}

GameScene::~GameScene(void)
{
}

CCScene* GameScene::playNewGame()
{
	//TODO: start new game here

    CCScene * scene = NULL;
    do 
    {
		//新游戏，当前地图层数为0
		sGlobal->currentLevel = 0;

        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
		char temp[20];
		sprintf(temp, "%d.tmx", 0);
		map = GameMap::gameMapWithTMXFile(temp);
		this->addChild(map, zGameLayer, zGameLayer);

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right corner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20,
									CCDirector::sharedDirector()->getWinSize().height - 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        //// 2. Add a label shows "Hello World".

        //// Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("to be continued...", "Arial", 24);
        //CC_BREAK_IF(! pLabel);

        //// Get window size and place the label upper. 
        //CCSize size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        //// Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);

        //// 3. Add add a splash screen as the background, show the cocos2d splash image.
        //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        //CC_BREAK_IF(! pSprite);

        //// Place the sprite on the center of the screen
        //pSprite->setPosition(ccp(size.width/2, size.height/2));

        //// Add the sprite to HelloWorld layer as a child layer.
        //this->addChild(pSprite, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

