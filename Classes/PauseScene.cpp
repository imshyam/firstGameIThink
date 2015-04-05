#include "PauseScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}

Scene* Pause::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Pause::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Pause::init()
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

    //menu
    auto menu_item_1 = MenuItemImage::create("main.png", "mainc.png", CC_CALLBACK_1(Pause::ToMainMenu, this));
    auto menu_item_2 = MenuItemImage::create("resu.png", "resuc.png", CC_CALLBACK_1(Pause::ToGame, this));
    
    menu_item_1->setPosition(Point(visibleSize.width/2 , (visibleSize.height/3)*2 ));
    menu_item_2->setPosition(Point(visibleSize.width/2 , (visibleSize.height/3)*1 ));
    
    auto menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    this->setKeypadEnabled(true);
    return true;
}
void Pause::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{    
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

    Director::getInstance()->popScene();
}
void Pause::ToMainMenu(cocos2d::Ref *pSender){

    auto scene = HelloWorld::createScene();

    Director::getInstance()->replaceScene(scene);
}
void Pause::ToGame(cocos2d::Ref *pSender){

    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

    Director::getInstance()->popScene();
}