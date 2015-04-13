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
    ball_velocity_y = -ball_velocity_y;
    Body->setVelocity(Vec2(ball_velocity_x, ball_velocity_y));
}
void Ball::again( )
{
    Body->setVelocity(Vec2(0,0));
    auto moveTo = MoveTo::create(0, Point(visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y));
    movingBall->runAction(moveTo);
}
void Ball::startAgain( )
{
    Body->setVelocity(Vec2(ball_velocity_x, ball_velocity_y));
}
void Ball::changeVelocity( )
{
    ball_velocity_y = -ball_velocity_y;
    // CCLOG("pre ball velocity : %d",ball_velocity_x);
    ball_velocity_x += user_paddle_velocity_x/10;
    // CCLOG("middle ball velocity : %d",ball_velocity_x);
    if ( ball_velocity_x <= ball_velocity_min_x ){
        ball_velocity_x = ball_velocity_min_x;
    }
    else if(ball_velocity_x >= ball_velocity_max_x){
        ball_velocity_x = ball_velocity_max_x;
    }
    // CCLOG("post ball velocity : %d",ball_velocity_x);
    Body->setVelocity( Vec2( ball_velocity_x, ball_velocity_y ) );
}
void Ball::leftRight( )
{
    ball_velocity_x = -ball_velocity_x;
    // CCLOG("ball velocity x: %d and y : %d", ball_velocity_x, ball_velocity_y);
    Body->setVelocity( Vec2( ball_velocity_x, ball_velocity_y ) );
}