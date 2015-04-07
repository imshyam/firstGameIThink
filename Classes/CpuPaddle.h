#ifndef __CPU_PADDLE_H__
#define __CPU_PADDLE_H__

#include "cocos2d.h"

class CpuPaddle
{
public:
    CpuPaddle( cocos2d::Layer *layer );
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *cpuPaddle;
    
    
};

#endif // __CPU_PADDLE_H__