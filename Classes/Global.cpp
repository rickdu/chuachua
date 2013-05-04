#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{

}

Global::~Global(void)
{
	gameMap = NULL;
	gameScene = NULL;
}