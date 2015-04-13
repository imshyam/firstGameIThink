#ifndef __CPU_PADDLE_H__
#define __CPU_PADDLE_H__

#include "cocos2d.h"

class CpuPaddle
{
public:
    CpuPaddle( cocos2d::Layer *layer );
    void changeVelocity( );
    void Stop( );
    void again( );
    void startAgain( );
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *cpuPaddle;
    cocos2d::PhysicsBody *Body;
    
};

#endif // __CPU_PADDLE_H__