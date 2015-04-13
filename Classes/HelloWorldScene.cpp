#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "HighScene.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
bool onContactBegin(cocos2d::PhysicsContact& contact);
class DrawLine : public Layer{
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated){
    DrawPrimitives::drawLine( Point(0, 0), Point(100, 100) );
    DrawPrimitives::setDrawColor4B(150, 150, 100, 255);
    }
};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

    // add background
    auto sprite = Sprite::create("main.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


    //menu
    auto menu_item_1 = MenuItemImage::create("play.png", "playc.png", CC_CALLBACK_1(HelloWorld::GoToGamePlay, this));
    auto menu_item_2 = MenuItemImage::create("hs.png", "hsc.png", CC_CALLBACK_1(HelloWorld::Highscores, this));
    auto menu_item_3 = MenuItemImage::create("lev.png", "levc.png", CC_CALLBACK_1(HelloWorld::Levels, this));

    menu_item_1->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 3 ));
    menu_item_2->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 2 ));
    menu_item_3->setPosition(Point(visibleSize.width/2 , (visibleSize.height/4) * 1 ));

    auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);


    this->setKeypadEnabled(true);
    return true;
}

void HelloWorld::GoToGamePlay(cocos2d::Ref *pSender){

    ball_velocity_x = ball_velocity_x_initial;
    ball_velocity_y = ball_velocity_y_initial;

    auto scene = Game::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void HelloWorld::Highscores(cocos2d::Ref *pSender){
    auto scene = HS::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void HelloWorld::Levels(cocos2d::Ref *pSender){
    auto scene = Level::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(0,255,255)));
}
void HelloWorld::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    Director::getInstance()->end();
}