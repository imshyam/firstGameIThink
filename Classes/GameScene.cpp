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


    visibleSize = Director::getInstance()->getVisibleSize();
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
    //Game ending Sprites

    //upper boundary
    auto sprite1 = Sprite::create("loser.png");
    sprite1->setAnchorPoint(Point(0.5, 1));
    // position the sprite
    sprite1->setPosition(Vec2( visibleSize.width/2 + origin.x, visibleSize.height + origin.y));

    //physics body
    auto physicsBody1 = PhysicsBody::createBox(Size(sprite1->getContentSize().width ,
                        sprite1->getContentSize().height ),
                        PhysicsMaterial(0, 1, 0));
    physicsBody1->setDynamic(false);
    physicsBody1->setGravityEnable(false);
    //collision
    physicsBody1->setCollisionBitmask(7);
    physicsBody1->setContactTestBitmask(true);
    //sprite to physics body
    sprite1->setPhysicsBody(physicsBody1);
    // add the sprite as a child to this layer
    this->addChild(sprite1, 0);

    //lower boundary
    auto sprite2 = Sprite::create("loser.png");
    sprite2->setAnchorPoint(Point(0.5, 0));
    // position the sprite
    sprite2->setPosition(Vec2( visibleSize.width/2 + origin.x, origin.y));

    //physics body
    auto physicsBody2 = PhysicsBody::createBox(Size(sprite2->getContentSize().width ,
                        sprite2->getContentSize().height ),
                        PhysicsMaterial(0, 1, 0));
    physicsBody2->setDynamic(false);
    physicsBody2->setGravityEnable(false);
    //collision
    physicsBody2->setCollisionBitmask(8);
    physicsBody2->setContactTestBitmask(true);
    //sprite to physics body
    sprite2->setPhysicsBody(physicsBody2);
    // add the sprite as a child to this layer
    this->addChild(sprite2, 0);

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

    //Show score
    scoreCpu=0;
    scoreUser=0;

    __String *tempCpu = __String::createWithFormat( "%i", scoreCpu );
    __String *tempUser = __String::createWithFormat( "%i", scoreUser );

    scoreLabelCpu = Label::createWithTTF(tempCpu->getCString(), "fonts/pixel font.ttf", 400);
    scoreLabelCpu->setColor(Color3B( 19, 79, 92));
    scoreLabelCpu->setPosition(Vec2(visibleSize.width*.10 + origin.x, visibleSize.height*.90 + origin.y));
    this->addChild(scoreLabelCpu,1000);

    scoreLabelUser = Label::createWithTTF(tempUser->getCString(), "fonts/pixel font.ttf", 400);
    scoreLabelUser->setColor(Color3B( 19, 79, 92));
    scoreLabelUser->setPosition(Vec2(visibleSize.width*.10 + origin.x, visibleSize.height*.10 + origin.y));
    this->addChild(scoreLabelUser,1000);

    //pause button
    auto menu_item_1 = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(Game::Pause, this));
    menu_item_1->setPosition(Point(visibleSize.width*.90 , (visibleSize.height*.90) ));

    auto menu = Menu::create(menu_item_1, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu,1000);

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
void Game::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    auto scene = Pause::createScene();
    Director::getInstance()->pushScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Game::Pause( cocos2d::Ref *pSender )
{
    auto scene = Pause::createScene();
    Director::getInstance()->pushScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if( gamePaused ){
        ball->startAgain();
        cpuPaddle->startAgain();
        gamePaused = false;
    }
    if( touch->getLocation().x<=visibleSize.width/2 && notTouchedLeft ){
        userPaddle->moveLeft();
        notTouchedRight = true;
        // CCLOG("Left");
    }
    else if( touch->getLocation().x>visibleSize.width/2 && notTouchedRight ){
        userPaddle->moveRight();
        notTouchedLeft = true;
        // CCLOG("Right");
    }
    return true;
}
void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    if( touch->getLocation().x<=visibleSize.width/2 && notTouchedLeft ){
        userPaddle->moveLeft();
        notTouchedRight = true;
        // CCLOG("Left");
    }
    else if( touch->getLocation().x>visibleSize.width/2 && notTouchedRight ){
        userPaddle->moveRight();
        notTouchedLeft = true;
        // CCLOG("Right");
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
    //cpu lost
    if ( ( BALL_COLLISION_BITMASK == a->getCollisionBitmask( ) && 7 == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == b->getCollisionBitmask( ) && 7 == a->getCollisionBitmask() ) )
    {
        CCLOG("CPU Lost");
        scoreUser++;
        __String *tempUser = __String::createWithFormat( "%i", scoreUser );
        scoreLabelUser->setString(tempUser->getCString());
        //reset value
        gamePaused = true;
        ball_velocity_x = ball_velocity_x_initial;
        ball_velocity_y = ball_velocity_y_initial;
        if(scoreUser == 5){
            userWon=true;
            gamePaused = false;
            auto scene = GameOver::createScene();
            Director::getInstance()->pushScene(scene);
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            return true;
        }
        //again
        else {
            ball->again();
            cpuPaddle->again();
        }
    }
    //user lost
    else if ( ( BALL_COLLISION_BITMASK == a->getCollisionBitmask( ) && 8 == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == b->getCollisionBitmask( ) && 8 == a->getCollisionBitmask() ) )
    {
        CCLOG("User Lost");
        scoreCpu++;
        __String *tempCpu = __String::createWithFormat( "%i", scoreCpu );
        scoreLabelCpu->setString(tempCpu->getCString());
        //reset value
        gamePaused = true;
        ball_velocity_x = ball_velocity_x_initial;
        ball_velocity_y = ball_velocity_y_initial;
        if(scoreCpu == 5){
            gamePaused = false;
            auto scene = GameOver::createScene();
            Director::getInstance()->pushScene(scene);
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            return true;
        }
        //again
        else {
            ball->again();
            cpuPaddle->again();
        }
    }
    else if ( ( CPU_P_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("cpuPaddle and boundary Right");
        cpuPaddle->Stop( );
        return false;
    }
    else if ( ( CPU_P_COLLISION_BITMASK == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("cpuPaddle and boundary Left");
        cpuPaddle->Stop( );
        return false;
    }else if ( ( USER_P_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("UserPaddle and boundary Right");
        userPaddle->Stop( );
        notTouchedRight = false;
        return false;
    }
    else if ( ( USER_P_COLLISION_BITMASK == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("UserPaddle and boundary Left");
        userPaddle->Stop( );
        notTouchedLeft = false;
        return false;
    }
    else if ( ( BALL_COLLISION_BITMASK  == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("ball and boundary Right");
        ball->leftRight();
        cpuPaddle->changeVelocity( );
        return false;
    }
    else if ( ( BALL_COLLISION_BITMASK  == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("ball and boundary Left");
        ball->leftRight();
        cpuPaddle->changeVelocity( );
        return false;
    }
    else if ( ( CPU_P_COLLISION_BITMASK == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == a->getCollisionBitmask() && CPU_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("cpuPaddle and ball");
        ball->cpuPaddleResponce( );
        return false;
    }
    else if ( ( USER_P_COLLISION_BITMASK == a->getCollisionBitmask() && BALL_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BALL_COLLISION_BITMASK == a->getCollisionBitmask() && USER_P_COLLISION_BITMASK == b->getCollisionBitmask() ) )
    {
        // CCLOG("userPaddle and ball");
        ball->changeVelocity( );
        cpuPaddle->changeVelocity( );
        return false;
    }
    
}
