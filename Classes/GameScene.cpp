#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Config.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}    

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Game::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    //there are 4 fields .1 for opcity ,3 for color.
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) )) {
        return false;
    }


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //physics and screen boundary

    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 3 );
    //collision
    edgeBody->setCollisionBitmask(GROUND_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    
    //theme song
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("theme.mp3");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("theme.mp3", true);

    userPaddle = new UserPaddle ( this );

    cpuPaddle = new CpuPaddle ( this );

    ball = new Ball( this );

    //bound walls
    auto sprite3 = Sprite::create("bound.png");
    sprite3->setAnchorPoint(Point(1, 0.5));
    // position the sprite
    sprite3->setPosition(Vec2( origin.x, visibleSize.height/2 + origin.y));

    //physics body
    auto physicsBody3 = PhysicsBody::createBox(Size(sprite3->getContentSize().width ,
                        sprite3->getContentSize().height ),
                        PhysicsMaterial(0, 1, 0));
    physicsBody3->setDynamic(false);
    physicsBody3->setGravityEnable(false);
    //collision
    physicsBody3->setCollisionBitmask(5);
    physicsBody3->setContactTestBitmask(true);
    //sprite to physics body
    sprite3->setPhysicsBody(physicsBody3);
    // add the sprite as a child to this layer
    this->addChild(sprite3, 0);

     auto sprite4 = Sprite::create("bound.png");
    sprite4->setAnchorPoint(Point(0, 0.5));
    // position the sprite
    sprite4->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height/2 + origin.y));

    //physics body
    auto physicsBody4 = PhysicsBody::createBox(Size(sprite4->getContentSize().width ,
                        sprite4->getContentSize().height ),
                        PhysicsMaterial(0, 1, 0));
    physicsBody4->setDynamic(false);
    physicsBody4->setGravityEnable(false);
    //collision
    physicsBody4->setCollisionBitmask(6);
    physicsBody4->setContactTestBitmask(true);
    //sprite to physics body
    sprite4->setPhysicsBody(physicsBody4);
    // add the sprite as a child to this layer
    this->addChild(sprite4, 0);



    //TouchEvents Listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //contact Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->setKeypadEnabled(true);
    return true;
}

void Game::GoToPauseScene(cocos2d::Ref *pSender)
{

}
void Game::GoToGameOverScene(cocos2d::Ref *pSender)
{

}
void Game::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    auto scene = Pause::createScene();
    Director::getInstance()->pushScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if( touch->getLocation().x<=900 && notTouchedLeft ){
        userPaddle->moveLeft();
        notTouchedRight = true;
        CCLOG("Left");
    }
    else if( touch->getLocation().x>900 && notTouchedRight ){
        userPaddle->moveRight();
        notTouchedLeft = true;
        CCLOG("Right");
    }
    return true;
}
void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    if( touch->getLocation().x<=900 && notTouchedLeft ){
        userPaddle->moveLeft();
        notTouchedRight = true;
        CCLOG("Left");
    }
    else if( touch->getLocation().x>900 && notTouchedRight ){
        userPaddle->moveRight();
        notTouchedLeft = true;
        CCLOG("Right");
    }
}
void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    userPaddle->Stop( );
}
bool Game::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // check if the bodies have collided
    if ( ( BALL_COLLISION_BITMASK == a->getCollisionBitmask( ) && GROUND_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == b->getCollisionBitmask( ) && GROUND_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        CCLOG("wall and ball");
        // auto scene = GameOver::createScene();
        // Director::getInstance()->pushScene(scene);
        // CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        return true;
    }
    else if ( ( CPU_P_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("cpuPaddle and boundary Right");
        a->setVelocity(Vec2(-500, 0));
        b->setVelocity(Vec2(-500, 0));
        return false;
    }
    else if ( ( CPU_P_COLLISION_BITMASK == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("cpuPaddle and boundary Left");
        a->setVelocity(Vec2(500, 0));
        b->setVelocity(Vec2(500, 0));
        return false;
    }else if ( ( USER_P_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("UserPaddle and boundary Right");
        userPaddle->Stop( );
        notTouchedRight = false;
        return false;
    }
    else if ( ( USER_P_COLLISION_BITMASK == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("UserPaddle and boundary Left");
        userPaddle->Stop( );
        notTouchedLeft = false;
        return false;
    }
    else if ( ( BALL_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("ball and boundary Right");
        return true;
    }
    else if ( ( BALL_COLLISION_BITMASK  == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("ball and boundary Left");
        return true;
    }
    else if ( ( CPU_P_COLLISION_BITMASK == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("cpuPaddle and ball");
        // auto scene = GameOver::createScene();
        // Director::getInstance()->pushScene(scene);
        // CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        return true;
    }
    else if ( ( USER_P_COLLISION_BITMASK == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        CCLOG("userPaddle and ball");
        // auto scene = GameOver::createScene();
        // Director::getInstance()->pushScene(scene);
        // CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        return true;
    }
    
}
