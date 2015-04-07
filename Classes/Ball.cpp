#include "Ball.h"
#include "Config.h"

USING_NS_CC;

Ball::Ball( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    movingBall = Sprite::create( "ball.png" );
    movingBall->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    Body = PhysicsBody::createCircle( movingBall->getContentSize( ).width / 2, PhysicsMaterial(0, 1, 0) );
    Body->setVelocity(Vec2(ball_velocity_x, ball_velocity_y));
    Body->setGravityEnable(false);
    Body->setCollisionBitmask( BALL_COLLISION_BITMASK );
    Body->setContactTestBitmask( true );
    
    movingBall->setPhysicsBody( Body );
    
    layer->addChild( movingBall, 100 );
}

void Ball::cpuPaddleResponce( )
{
    Body->setVelocity(Vec2(ball_velocity_x, -ball_velocity_y));
}
void Ball::userPaddleResponce( )
{
    Body->setVelocity(Vec2(ball_velocity_x, ball_velocity_y));
}
void Ball::changeVelocity( )
{
    ball_velocity_x += user_paddle_velocity_x/8;
    CCLOG("ball velocity : %d",ball_velocity_x);
    CCLOG("user paddle velocity : %d",user_paddle_velocity_x);
    if ( ball_velocity_x <= ball_velocity_min_x ){
        Body->setVelocity( Vec2( ball_velocity_min_x, ball_velocity_y ) );
    }
    else if ( ball_velocity_x > cpu_paddle_min_velocity_x && ball_velocity_x <= ball_velocity_max_x ){
        Body->setVelocity( Vec2( ball_velocity_x, ball_velocity_y ) );
    }
    else{
        Body->setVelocity( Vec2( ball_velocity_max_x, ball_velocity_y ) );
    }
}