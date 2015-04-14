#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "HighScene.h"
#include "sqlite3.h"

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

//creation of table
result = sqlite3_exec(pDB, "CREATE TABLE SCORES("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "RESULT           TEXT    NOT NULL," \
         "VALUE          TEXT    NOT NULL);",NULL,NULL,&errMsg);
if(result != SQLITE_OK)
    CCLOG("CREATE TABLE FAIL %d, Msg: %s",result,errMsg);
else 
    CCLOG("result of table creation %d",result);
//inseration
sqlite3_exec(pDB, 
         "INSERT INTO SCORES (ID,NAME,RESULT,VALUE) "  \
         "VALUES(1,'Beginner','Never Won','0-5' ); "\
         "INSERT INTO SCORES (ID,NAME,RESULT,VALUE) "  \
         "VALUES(2,'Intermediate','Never Won','0-5' ); "\
         "INSERT INTO SCORES (ID,NAME,RESULT,VALUE) "  \
         "VALUES(3,'Pro','Never Won','0-5' ); ", NULL, NULL, &errMsg);

if(result != SQLITE_OK)
    CCLOG("CREATE TABLE FAIL %d, Msg: %s",result,errMsg);
else 
    CCLOG("result of inseration %d",result);

// //update
// char *str = "UPDATE SCORES set VALUE = '4-5' where ID=1; ";
// sqlite3_exec(pDB, str, NULL, NULL, &errMsg);

// if(result != SQLITE_OK)
//     CCLOG("CREATE TABLE FAIL %d, Msg: %s",result,errMsg);
// else 
//     CCLOG("result of update %d",result);

// //select
// sqlite3_stmt *ppStmt1;
// CCString *number;
// CCString *name;
// CCString *value;
// result=sqlite3_prepare_v2(pDB,"select * from SCORES", -1, &ppStmt1, NULL);
// CCLOG("result of selection %d",result);
// for (;;) {
//     CCLOG("inside for");
//     result = sqlite3_step(ppStmt1);
//     if (result == SQLITE_DONE){
//         CCLOG("inside SQLITE_DONE");
//         break;
//     }
//     if (result != SQLITE_ROW) {
//         CCLOG("error: %s!\n", sqlite3_errmsg(pDB));
//         break;
//     }
//     number=CCString::create((const char*)sqlite3_column_text(ppStmt1, 0));
//     name=CCString::create((const char*)sqlite3_column_text(ppStmt1, 1));
//     value=CCString::create((const char*)sqlite3_column_text(ppStmt1, 2));
//     CCLOG("ID : %s, Name : %s, Value : %s ",number->getCString(),name->getCString(),value->getCString());
// }





//------------------------------------------------------------------------------------------------------------------



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