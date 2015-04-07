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
    Body->setVelocity(Vec2(-500, 0));
}
void UserPaddle::moveRight( )
{
    Body->setVelocity(Vec2(500, 0));
}
void UserPaddle::Stop( )
{
    Body->setVelocity(Vec2(0, 0));
}