#include "GameOverScene.h"
#include "GameScene.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    //there are 4 fields .1 for opcity ,3 for color.
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 255) )) {
        return false;
    }


    //physics and screen boundary
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     auto Label = Label::createWithTTF("GameOver", "fonts/pixel font.ttf", 400);
    Label->setColor(Color3B( 19, 79, 92));
    Label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(Label);


    this->setKeypadEnabled(true);
    return true;
}
void GameOver::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    Director::getInstance()->end();
}