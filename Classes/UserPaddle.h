#ifndef __USER_PADDLE_H__
#define __USER_PADDLE_H__

#include "cocos2d.h"

class UserPaddle
{
public:
    UserPaddle( cocos2d::Layer *layer );

    void moveLeft( );
    void moveRight( );
    void Stop( );
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *usrPaddle;
    cocos2d::PhysicsBody *Body;
    
    
};

#endif // __USER_PADDLE_H__