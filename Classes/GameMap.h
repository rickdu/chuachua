#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "Block.h"

using namespace cocos2d;

//继承自CCTMXTIledMap
class GameMap : public cocos2d::CCTMXTiledMap
{
	//只读变量，获取各图层
	CC_PROPERTY_READONLY(CCTMXLayer*, floorLayer, FloorLayer);
	CC_PROPERTY_READONLY(CCTMXLayer*, blocksLayer, BlocksLayer);
public:
	GameMap(void);
	~GameMap(void);
	//静态方法，用于生成GameMap实例
	static GameMap* gameMapWithTMXFile(const char *tmxFile);
	//TiledMap和cocos2d-x坐标系相互转换的方法
	CCPoint tileCoordForPosition(CCPoint position);
	CCPoint positionForTileCoord(CCPoint tileCoord);
	//void showEnemyHitEffect(CCPoint tileCoord);
	
	//存放地图上的方块
	CCArray *blockArray;
	//CCMutableArray<Enemy*> *enemyArray;
	//CCMutableDictionary<int, Teleport*> *teleportDict;
	//CCMutableDictionary<int, NPC*> *npcDict;
protected:
	//TiledMap额外的初始化方法
	void extraInit();
	//初始化方块数组
	void initBlocks();
	//更新方块动画
	void GameMap::updateBlockAnimation(float dt);
	//开启各图层的纹理抗锯齿
	void enableAnitiAliasForEachLayer();
	};

#endif