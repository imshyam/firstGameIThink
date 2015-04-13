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
    
    Body = PhysicsBody::createBox(Size(cpuPaddle->getContentSize().width ,
                        cpuPaddle->getContentSize().height ),
                        PhysicsMaterial(2.0f, 1, 0));
    Body->setGravityEnable(false);
    Body->setVelocity( Vec2( ball_velocity_x, 0 ) );
    Body->setCollisionBitmask( CPU_P_COLLISION_BITMASK );
    Body->setContactTestBitmask( true );
    // Body->setVelocity(Vec2(-500, 0));
    
    cpuPaddle->setPhysicsBody( Body );
    
    layer->addChild( cpuPaddle, 100 );
    
}
void CpuPaddle::changeVelocity( )
{
    if ( ball_velocity_x <= cpu_paddle_min_velocity_x ){
        Body->setVelocity( Vec2( cpu_paddle_min_velocity_x, 0 ) );
    }
    else if ( ball_velocity_x > cpu_paddle_min_velocity_x && ball_velocity_x <= cpu_paddle_max_velocity_x ){
        Body->setVelocity( Vec2( ball_velocity_x, 0 ) );
    }
    else{
        Body->setVelocity( Vec2( cpu_paddle_max_velocity_x, 0 ) );
    }
}
void CpuPaddle::Stop( )
{
    Body->setVelocity( Vec2( 0, 0 ) );
}
void CpuPaddle::again( ){
    Body->setVelocity(Vec2(0,0));
    auto moveTo = MoveTo::create(0, Vec2(visibleSize.width/2 + origin.x, (visibleSize.height*19)/20 + origin.y) );
    cpuPaddle->runAction(moveTo);
}
void CpuPaddle::startAgain( )
{
    Body->setVelocity(Vec2(ball_velocity_x, 0));
}
