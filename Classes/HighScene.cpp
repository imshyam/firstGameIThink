#include "HighScene.h"
#include "HelloWorldScene.h"
#include "sqlite3.h"

USING_NS_CC;
cocos2d::PhysicsWorld* m_world;
void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}

Scene* HS::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HS::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HS::init()
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
    CCLOG("\n\nresult of db making %d",result);


//select
sqlite3_stmt *ppStmt1;
CCString *number, *name, *rejult, *value;
result=sqlite3_prepare_v2(pDB,"select * from SCORES", -1, &ppStmt1, NULL);
CCLOG("result of selection %d",result);
int i=3;
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
    number=CCString::create((const char*)sqlite3_column_text(ppStmt1, 0));
    name=CCString::create((const char*)sqlite3_column_text(ppStmt1, 1));
    rejult=CCString::create((const char*)sqlite3_column_text(ppStmt1, 2));
    value=CCString::create((const char*)sqlite3_column_text(ppStmt1, 3));
    CCLOG("ID : %s, Name : %s, Value : %s ",number->getCString(),name->getCString(),value->getCString());
    __String str = number->getCString();
    str.append(". ");
    str.append(name->getCString());
    str.append("     ");
    str.append(value->getCString());
    str.append("  (");
    str.append(rejult->getCString());
    str.append(")");
    auto Label = Label::createWithTTF(str.getCString(), "fonts/pixel font.ttf", 100);
    Label->setColor(Color3B( 19, 79, 92));
    Label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*.25*i + origin.y));
    this->addChild(Label);
    i--;
   
}

//------------------------------------------------------------------------------------------------------------------


    this->setKeypadEnabled(true);
    return true;
}
void HS::onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event )
{
    Director::getInstance()->popScene();
}