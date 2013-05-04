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

//��̬��������������GameMapʵ��
GameMap* GameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//newһ������
	GameMap *pRet = new GameMap();
	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{
		//���ö����init����
		pRet->extraInit();
		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//TliedMap����ĳ�ʼ������
void GameMap::extraInit()
{
	//��������ͼ����������
	enableAnitiAliasForEachLayer();
	//��ʼ���������
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
	// ���·��鶯��
	//schedule(schedule_selector(GameMap::updateBlockAnimation), 0.2f);
}

void GameMap::updateBlockAnimation(float dt)
{
	CCObject *it;
	//�����������з��������
	CCARRAY_FOREACH(blockArray, it) {
		Block *b = dynamic_cast<Block*>(it);
		int gid = blocksLayer->tileGIDAt(b->position);
		CCLog("gid: %sd", gid);
		//blocksLayer->setTileGID(gid, b->position);
	}
	//for (iter = enemyArray->begin(); iter != enemyArray->end(); ++iter) {
	//	enemy = *iter;
	//	if (enemy != NULL) {
	//		//��ȡ���ﵱǰ��ͼ��ID
	//		int gid = enemyLayer->tileGIDAt(enemy->position);
	//		//������ﱻɾ���ˣ���Ҫ������enemyArray��Ҳɾ��
	//		if (gid == 0)
	//		{
	//			needRemove = enemy;
	//			continue;
	//		}
	//		gid++;
	//		//�����һ��ͼ��ID ��ʼͼ��ID
	//		if (gid - enemy->startGID > 3) {
	//			gid = enemy->startGID;
	//		}
	//		//�����������µ�ͼ��
	//		enemyLayer->setTileGID(gid, enemy->position);
	//	}
	//}
	//ɾ��������Ĺ���
	//if (needRemove != NULL) {
	//	enemyArray->removeObject(needRemove, true);
	//}
}

void GameMap::enableAnitiAliasForEachLayer()
{
	CCArray * pChildrenArray = this->getChildren();
	CCSpriteBatchNode* child = NULL;
	CCObject* pObject = NULL;
	//����Tilemap������ͼ��
	CCARRAY_FOREACH(pChildrenArray, pObject)
	{
		child = (CCSpriteBatchNode*)pObject;
		if(!child)
			break;
		//��ͼ��������������
		child->getTexture()->setAntiAliasTexParameters();
	}
}

//��cocos2d-x����ת��ΪTilemap����
CCPoint GameMap::tileCoordForPosition(CCPoint position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return ccp(x, y);
}

//��Tilemap����ת��Ϊcocos2d-x����
CCPoint GameMap::positionForTileCoord(CCPoint tileCoord)
{
	CCPoint pos =  ccp((tileCoord.x * this->getTileSize().width),
		((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}

//���صذ��
CCTMXLayer* GameMap::getFloorLayer()
{
	return floorLayer;
}
//���ط����
CCTMXLayer* GameMap::getBlocksLayer()
{
	return blocksLayer;
}
