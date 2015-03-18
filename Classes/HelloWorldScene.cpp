#include "HelloWorldScene.h"

USING_NS_CC;

class DrawLine : public Layer{
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated){
    DrawPrimitives::drawLine( Point(0, 0), Point(100, 100) );
    DrawPrimitives::setDrawColor4B(150, 150, 100, 255);
    }
};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Score Player 1 : ", "fonts/Marker Felt.ttf", 40);
    label->setColor(ccc3(0,0,0));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/4,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto label1 = Label::createWithTTF("Score Player 2 : ", "fonts/Marker Felt.ttf", 40);
    label1->setColor(ccc3(0,0,0));
    // position the label on the center of the screen
    label1->setPosition(Vec2(origin.x + (3*visibleSize.width/4),
                            origin.y + visibleSize.height - label1->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label1, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("ball.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    auto moveBy = MoveBy::create(2, Vec2(visibleSize.width/2 + origin.x,origin.y));
    sprite->runAction(moveBy);
    
    auto sprite1 = Sprite::create("platform.png");

    // position the sprite on the center of the screen
    sprite1->setPosition(Vec2(visibleSize.width/4 + origin.x, origin.y));
    sprite1->setAnchorPoint(Vec2(0.5, 0));
    // add the sprite as a child to this layer
    this->addChild(sprite1, 0);

    auto sprite2 = Sprite::create("platform.png");
    sprite2->setAnchorPoint(Vec2(0.5, 0));
    // position the sprite on the center of the screen
    sprite2->setPosition(Vec2((3*visibleSize.width/4) + origin.x, + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite2, 0);

    //drawing line
    auto drawline = new DrawLine();
    addChild(drawline);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
