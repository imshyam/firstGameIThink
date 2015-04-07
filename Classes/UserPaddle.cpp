#include "UserPaddle.h"
#include "Config.h"

USING_NS_CC;

UserPaddle::UserPaddle( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    usrPaddle = Sprite::create( "platform.png" );
    usrPaddle->setPosition( Vec2(visibleSize.width/2 + origin.x,(visibleSize.height*1)/20 + origin.y) );
    usrPaddle->setAnchorPoint(Point(0.5, 0));
    
    Body = PhysicsBody::createBox(Size(usrPaddle->getContentSize().width ,
                        usrPaddle->getContentSize().height ),
                        PhysicsMaterial(2.0f, 1, 0));
    Body->setGravityEnable(false);
    Body->setCollisionBitmask( USER_P_COLLISION_BITMASK );
    Body->setContactTestBitmask( true );
    
    usrPaddle->setPhysicsBody( Body );
    
    layer->addChild( usrPaddle, 100 );
    
}
void UserPaddle::moveLeft( )
{
    user_paddle_velocity_x = user_paddle_velocity_min_x;

    Body->setVelocity(Vec2(user_paddle_velocity_x, 0));
}
void UserPaddle::moveRight( )
{
    user_paddle_velocity_x = user_paddle_velocity_max_x;

    Body->setVelocity(Vec2(user_paddle_velocity_x, 0));
}
void UserPaddle::Stop( )
{
    user_paddle_velocity_x = 0;
    
    Body->setVelocity(Vec2(0, 0));
}