#include "Ball.h"
#include "Config.h"

USING_NS_CC;

Ball::Ball( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    movingBall = Sprite::create( "ball.png" );
    movingBall->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    auto Body = PhysicsBody::createCircle( movingBall->getContentSize( ).width / 2, PhysicsMaterial(0, 1, 0) );
    Body->setVelocity(Vec2(-500, 500));
    Body->setGravityEnable(false);
    Body->setCollisionBitmask( BALL_COLLISION_BITMASK );
    Body->setContactTestBitmask( true );
    
    movingBall->setPhysicsBody( Body );
    
    layer->addChild( movingBall, 100 );
    
    isGoingRight = true;
}

void Ball::Direction( )
{
    if ( true == isGoingRight )
    {
        // Ball->setPositionX( visibleSize.width / 2 + origin.x );
        // Ball->setPositionY( Ball->getPositionY() - ( Ball_FALLING_SPEED * visibleSize.height ) );
    }
    else
    {
        // Ball->setPositionX( visibleSize.width / 2 + origin.x );
        // Ball->setPositionY( Ball->getPositionY() + ( Ball_FALLING_SPEED * visibleSize.height ) );
    }
}