#include "LevelScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}

Scene* Level::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Level::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level::init()
{
    //////////////////////////////
    // 1. super init first
    //there are 4 fields .1 for opcity ,3 for color.
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) )) {
        return false;
    }


    //physics and screen boundary
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto Label = Label::createWithTTF("Levels", "fonts/pixel font.ttf", 400);
    Label->setColor(Color3B( 19, 79, 92));
    Label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(Label);

    this->setKeypadEnabled(true);
    return true;
}
void Level::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    Director::getInstance()->popScene();
}