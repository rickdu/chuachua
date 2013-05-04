#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cocos2d.h"

using namespace cocos2d;

class Block : public CCObject
{
public:
	Block(int type);
	~Block(void);
	//方块类型
	int block_type;
	//方块在TileMap上的方位
	CCPoint position;
	//方块初始的图块ID
	int startGID;
	//方块在字典中的index
	int index;
};

// supported block types
enum {
	RED = 0,
	GREEN,
	YELLOW,
};
#endif