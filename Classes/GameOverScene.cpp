#include "GameOverScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Config.h"
#include "HighScene.h"
#include "sqlite3.h"

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

//-----------------------Database-----------------------------------------------------------------------------------

sqlite3 *pDB = NULL; //for database path
char* errMsg = NULL; //for error message
std::string sqlstr; //for sql query string
int result;
__String dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
dbPath.append("firstGameIThink.sqlite");
result = sqlite3_open(dbPath.getCString(),&pDB);
if (result != SQLITE_OK)
    CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
else 
    CCLOG("result of db making %d",result);
//select
sqlite3_stmt *ppStmt1;
CCString *value;
result=sqlite3_prepare_v2(pDB,"select * from SCORES", -1, &ppStmt1, NULL);
CCLOG("result of selection %d",result);
int i = 3;
for (;;) {
    CCLOG("inside for");
    result = sqlite3_step(ppStmt1);
    if (result == SQLITE_DONE){
        CCLOG("inside SQLITE_DONE");
        break;
    }
    if (result != SQLITE_ROW) {
        CCLOG("error: %s!\n", sqlite3_errmsg(pDB));
        break;
    }
    value=CCString::create((const char*)sqlite3_column_text(ppStmt1, 3));
    if(i == gameType){
        break;
    }
    i--;
}
std::string val = value->getCString();
//CCLOG("Value : %s ",val);
char user = val[0];
int usr = user - '0';
char cpuc = val[2];
int cpu = cpuc - '0';
// CCLOG("user : %d cpu : %d",usr,cpu);
//update
if(userWon){
    CCLOG("Tandan if");
    if( scoreCpu < cpu ){
        __String temp = "UPDATE SCORES set VALUE = '5-";
        if(scoreCpu == 1)
            temp.append("1");
        else if(scoreCpu == 2)
            temp.append("2");
        else if(scoreCpu == 3)
            temp.append("3");
        else if(scoreCpu == 4)
            temp.append("4");
        temp.append("',RESULT = 'Won' where ID=");
        if(gameType == 1)
            temp.append("1");
        if (gameType == 2)
            temp.append("2");
        if(gameType == 3)
            temp.append("3");
        temp.append("; ");
        CCLOG("%s",temp.getCString());
        sqlite3_exec(pDB,temp.getCString(), NULL, NULL, &errMsg);
    }
}
else{
    CCLOG("else score old id : %d new is : %d",usr,scoreUser);
    if( usr < 5 && scoreUser > usr ){
        CCLOG("USER less than 5.");
        __String temp = "UPDATE SCORES set VALUE = '";
        if(scoreUser == 1)
            temp.append("1");
        else if(scoreUser == 2)
            temp.append("2");
        else if(scoreUser == 3)
            temp.append("3");
        else if(scoreUser == 4)
            temp.append("4");
            
        temp.append("-5' where ID=");
        if(gameType == 1)
            temp.append("1");
        if (gameType == 2)
            temp.append("2");
        if(gameType == 3)
            temp.append("3");
        temp.append("; ");
        CCLOG("%s",temp.getCString());
        
        sqlite3_exec(pDB,temp.getCString(), NULL, NULL, &errMsg);
    }
}

if(result != SQLITE_OK)
    CCLOG("CREATE TABLE FAIL %d, Msg: %s",result,errMsg);
else 
    CCLOG("result of inseration %d",result);

//------------------------------------------------------------------------------------------------------------------


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