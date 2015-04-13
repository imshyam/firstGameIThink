#include "GameOverScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Config.h"
#include "HighScene.h"

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

    //menu
    auto menu_item_1 = MenuItemImage::create("main.png", "mainc.png", CC_CALLBACK_1(GameOver::GoToHome, this));
    auto menu_item_2 = MenuItemImage::create("retry.png", "retryc.png", CC_CALLBACK_1(GameOver::GoToGame, this));
    auto menu_item_3 = MenuItemImage::create("hs.png", "hsc.png", CC_CALLBACK_1(GameOver::GoToHS, this));

    menu_item_1->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 3 ));
    menu_item_3->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 2 ));
    menu_item_2->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 1 ));

    auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    auto winner = Label::createWithTTF("", "fonts/arial.ttf", 200);
    winner->setColor(Color3B( 255, 255, 255));
    winner->setPosition(Vec2(visibleSize.width*.50 + origin.x, visibleSize.height*.90 + origin.y));
    this->addChild(winner,1000);
    if(userWon){
        winner->setString("You Won");
    }
    else
        winner->setString("CPU Won");

    this->setKeypadEnabled(true);
    return true;
}
void GameOver::GoToGame(cocos2d::Ref *pSender){

    auto scene = Game::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void GameOver::GoToHome(cocos2d::Ref *pSender){

    auto scene = HelloWorld::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void GameOver::GoToHS(cocos2d::Ref *pSender){
    auto scene = HS::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void GameOver::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    auto scene = HelloWorld::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}