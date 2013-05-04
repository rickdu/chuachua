#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cocos2d.h"

using namespace cocos2d;

class Block : public CCObject
{
public:
	Block(int type);
	~Block(void);
	//��������
	int block_type;
	//������TileMap�ϵķ�λ
	CCPoint position;
	//�����ʼ��ͼ��ID
	int startGID;
	//�������ֵ��е�index
	int index;
};

// supported block types
enum {
	RED = 0,
	GREEN,
	YELLOW,
};
#endif