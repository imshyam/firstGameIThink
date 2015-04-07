#include "CpuPaddle.h"
#include "Config.h"

USING_NS_CC;

CpuPaddle::CpuPaddle( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    cpuPaddle = Sprite::create( "platformu.png" );
    cpuPaddle->setPosition( Vec2(visibleSize.width/2 + origin.x, (visibleSize.height*19)/20 + origin.y) );
    cpuPaddle->setAnchorPoint(Point(0.5, 1));
    
    auto Body = PhysicsBody::createBox(Size(cpuPaddle->getContentSize().width ,
                        cpuPaddle->getContentSize().height ),
                        PhysicsMaterial(2.0f, 1, 0));
    Body->setGravityEnable(false);
    Body->setCollisionBitmask( CPU_P_COLLISION_BITMASK );
    Body->setContactTestBitmask( true );
    Body->setVelocity(Vec2(-500, 0));
    
    cpuPaddle->setPhysicsBody( Body );
    
    layer->addChild( cpuPaddle, 100 );
    
}
