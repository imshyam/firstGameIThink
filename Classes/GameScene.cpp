#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

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
    edgeBody->setCollisionBitmask(1);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    
    //theme song
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("theme.mp3");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("theme.mp3", true);


    //sprites

    auto sprite = Sprite::create("platform.png");

    // position the sprite 
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height*1)/20 + origin.y));
    sprite->setAnchorPoint(Point(0.5, 0));
    //physics body
    auto physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width ,
                        sprite->getContentSize().height ),
                        PhysicsMaterial(0, 1, 0));
    physicsBody->setDynamic(false);
    physicsBody->setGravityEnable(false);
    //sprite to physics body
    sprite->setPhysicsBody(physicsBody);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    auto sprite1 = Sprite::create("platformu.png");

    // position the sprite
    sprite1->setPosition(Vec2(visibleSize.width/2 + origin.x, (visibleSize.height*19)/20 + origin.y));
    sprite1->setAnchorPoint(Point(0.5, 1));
    //physics body
    auto physicsBody1 = PhysicsBody::createBox(Size(sprite1->getContentSize().width ,
                        sprite1->getContentSize().height ),
                        PhysicsMaterial(1.0f, 1, 0));
    physicsBody1->setGravityEnable(false);
    physicsBody->setDynamic(false);
    //collision
    physicsBody1->setCollisionBitmask(3);
    physicsBody1->setContactTestBitmask(true);
    physicsBody1->setVelocity(Vec2(500, 0));
    //sprite to physics body
    sprite1->setPhysicsBody(physicsBody1);
    // add the sprite as a child to this layer
    this->addChild(sprite1, 0);



    auto sprite2 = Sprite::create("ball.png");

    // position the sprite
    sprite2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //physics body
    auto physicsBody2 = PhysicsBody::createCircle(sprite2->getContentSize().width /2,
                        PhysicsMaterial(0, 1, 0));
    physicsBody2->setVelocity(Vec2(500, 500));
    physicsBody2->setGravityEnable(false);
    //collision
    physicsBody2->setCollisionBitmask(2);
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
    physicsBody4->setCollisionBitmask(4);
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
    CCLOG("Touched at x = %f , y = %f", touch->getLocation().x, touch->getLocation().y);
    return 0;
}
void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("Touch Moved at x = %f , y = %f", touch->getLocation().x, touch->getLocation().y);
}
void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("Touch Ended at x = %f , y = %f", touch->getLocation().x, touch->getLocation().y);
}
bool Game::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // check if the bodies have collided
    if ( ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
        CCLOG("wall and ball");
        // auto scene = GameOver::createScene();
        // Director::getInstance()->pushScene(scene);
        // CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        return true;
    }
    else if ( ( 3 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask() ) || ( 4 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
    {
        CCLOG("platform and boundary Right");
        a->setVelocity(Vec2(-500, 0));
        b->setVelocity(Vec2(-500, 0));
        return false;
    }
    else if ( ( 3 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
    {
        CCLOG("platform and boundary Left");
        a->setVelocity(Vec2(500, 0));
        b->setVelocity(Vec2(500, 0));
        return false;
    }
    else if ( ( 3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || ( 2 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
    {
        CCLOG("platform and ball");
        // auto scene = GameOver::createScene();
        // Director::getInstance()->pushScene(scene);
        // CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        return true;
    }
    
}
