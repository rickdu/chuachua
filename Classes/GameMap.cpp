#include "GameMap.h"
#include "Global.h"
#include "cocos2d.h"
#include "block.h"

GameMap::GameMap(void)
{
	sGlobal->gameMap = this;
}

GameMap::~GameMap(void)
{
	this->unscheduleAllSelectors();
	//CC_SAFE_RELEASE(enemyArray)
	//CC_SAFE_RELEASE(npcDict)
	//CC_SAFE_RELEASE(teleportDict)
}

//静态方法，用于生成GameMap实例
GameMap* GameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//new一个对象
	GameMap *pRet = new GameMap();
	//调用init方法
	if (pRet->initWithTMXFile(tmxFile))
	{
		//调用额外的init方法
		pRet->extraInit();
		//将实例放入autorelease池，统一由引擎控制对象的生命周期
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//TliedMap额外的初始化方法
void GameMap::extraInit()
{
	//开启各个图层的纹理抗锯齿
	enableAnitiAliasForEachLayer();
	//初始化各层对象
	floorLayer = this->layerNamed("floor");
	blocksLayer = this->layerNamed("blocks");

	initBlocks();
}

void GameMap::initBlocks()
{
	blockArray = CCArray::create();
	
	CCSize s = blocksLayer->getLayerSize();
	CCLog("block layer size: %f,%f", s.width, s.height);
	
	for(int x = 0; x < int(s.width); x++) {
		for(int y = 0; y < int(s.height); y++) {
			if(rand() % 100 > 50) {
				Block* b = new Block(rand() % 3);
				b->position = ccp(x, y);
				b->startGID = blocksLayer->tileGIDAt(ccp(x, y));
				blockArray->addObject(b);
				CCLog("block(%d,%d) -> %d", x, y, rand() % 3);
			}
		}
	}
	// 更新方块动画
	//schedule(schedule_selector(GameMap::updateBlockAnimation), 0.2f);
}

void GameMap::updateBlockAnimation(float dt)
{
	CCObject *it;
	//遍历保存所有方块的数组
	CCARRAY_FOREACH(blockArray, it) {
		Block *b = dynamic_cast<Block*>(it);
		int gid = blocksLayer->tileGIDAt(b->position);
		CCLog("gid: %sd", gid);
		//blocksLayer->setTileGID(gid, b->position);
	}
	//for (iter = enemyArray->begin(); iter != enemyArray->end(); ++iter) {
	//	enemy = *iter;
	//	if (enemy != NULL) {
	//		//获取怪物当前的图块ID
	//		int gid = enemyLayer->tileGIDAt(enemy->position);
	//		//如果怪物被删除了，需要把它在enemyArray中也删除
	//		if (gid == 0)
	//		{
	//			needRemove = enemy;
	//			continue;
	//		}
	//		gid++;
	//		//如果下一个图块ID 起始图块ID
	//		if (gid - enemy->startGID > 3) {
	//			gid = enemy->startGID;
	//		}
	//		//给怪物设置新的图块
	//		enemyLayer->setTileGID(gid, enemy->position);
	//	}
	//}
	//删除被消灭的怪物
	//if (needRemove != NULL) {
	//	enemyArray->removeObject(needRemove, true);
	//}
}

void GameMap::enableAnitiAliasForEachLayer()
{
	CCArray * pChildrenArray = this->getChildren();
	CCSpriteBatchNode* child = NULL;
	CCObject* pObject = NULL;
	//遍历Tilemap的所有图层
	CCARRAY_FOREACH(pChildrenArray, pObject)
	{
		child = (CCSpriteBatchNode*)pObject;
		if(!child)
			break;
		//给图层的纹理开启抗锯齿
		child->getTexture()->setAntiAliasTexParameters();
	}
}

//从cocos2d-x坐标转换为Tilemap坐标
CCPoint GameMap::tileCoordForPosition(CCPoint position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return ccp(x, y);
}

//从Tilemap坐标转换为cocos2d-x坐标
CCPoint GameMap::positionForTileCoord(CCPoint tileCoord)
{
	CCPoint pos =  ccp((tileCoord.x * this->getTileSize().width),
		((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}

//返回地板层
CCTMXLayer* GameMap::getFloorLayer()
{
	return floorLayer;
}
//返回方块层
CCTMXLayer* GameMap::getBlocksLayer()
{
	return blocksLayer;
}
