#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball
{
public:
    Ball( cocos2d::Layer *layer );
    
    void cpuPaddleResponce( );
    void userPaddleResponce( );
    void changeVelocity( );
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *movingBall;
    cocos2d::PhysicsBody *Body;
        
};

#endif // __BALL_H__