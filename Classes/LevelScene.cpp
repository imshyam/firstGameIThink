#include "LevelScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

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


   //menu
    auto menu_item_1 = MenuItemImage::create("be.png", "bec.png", CC_CALLBACK_1(Level::GoToGamePlayBe, this));
    auto menu_item_2 = MenuItemImage::create("int.png", "intc.png", CC_CALLBACK_1(Level::GoToGamePlayInt, this));
    auto menu_item_3 = MenuItemImage::create("pro.png", "proc.png", CC_CALLBACK_1(Level::GoToGamePlayPro, this));

    menu_item_1->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 3 ));
    menu_item_2->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 2 ));
    menu_item_3->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 1 ));

    auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    this->setKeypadEnabled(true);
    return true;
}
void Level::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    Director::getInstance()->popScene();
}
void Level::GoToGamePlayBe(cocos2d::Ref *pSender){

    gameType = 1;
    ball_velocity_x_initial = 800;
    ball_velocity_y_initial = 700;
    ball_velocity_x = ball_velocity_x_initial;
    ball_velocity_y = ball_velocity_y_initial;

    auto scene = Game::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void Level::GoToGamePlayInt(cocos2d::Ref *pSender){

    gameType = 2;
    ball_velocity_x_initial = 900;
    ball_velocity_y_initial = 800;
    cpu_paddle_min_velocity_x = -1100;
    cpu_paddle_max_velocity_x = 1100;
    ball_velocity_x = ball_velocity_x_initial;
    ball_velocity_y = ball_velocity_y_initial; 

    auto scene = Game::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void Level::GoToGamePlayPro(cocos2d::Ref *pSender){

    gameType = 3;
    ball_velocity_x_initial = 1000;
    ball_velocity_y_initial = 900;
    cpu_paddle_min_velocity_x = -1200;
    cpu_paddle_max_velocity_x = 1200;
    ball_velocity_x = ball_velocity_x_initial;
    ball_velocity_y = ball_velocity_y_initial;

    auto scene = Game::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}