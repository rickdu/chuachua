#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "Block.h"

using namespace cocos2d;

//�̳���CCTMXTIledMap
class GameMap : public cocos2d::CCTMXTiledMap
{
	//ֻ����������ȡ��ͼ��
	CC_PROPERTY_READONLY(CCTMXLayer*, floorLayer, FloorLayer);
	CC_PROPERTY_READONLY(CCTMXLayer*, blocksLayer, BlocksLayer);
public:
	GameMap(void);
	~GameMap(void);
	//��̬��������������GameMapʵ��
	static GameMap* gameMapWithTMXFile(const char *tmxFile);
	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	CCPoint tileCoordForPosition(CCPoint position);
	CCPoint positionForTileCoord(CCPoint tileCoord);
	//void showEnemyHitEffect(CCPoint tileCoord);
	
	//��ŵ�ͼ�ϵķ���
	CCArray *blockArray;
	//CCMutableArray<Enemy*> *enemyArray;
	//CCMutableDictionary<int, Teleport*> *teleportDict;
	//CCMutableDictionary<int, NPC*> *npcDict;
protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();
	//��ʼ����������
	void initBlocks();
	//���·��鶯��
	void GameMap::updateBlockAnimation(float dt);
	//������ͼ����������
	void enableAnitiAliasForEachLayer();
	};

#endif