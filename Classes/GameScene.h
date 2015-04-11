#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "UserPaddle.h"
#include "CpuPaddle.h"


class Game : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(Game);

    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event );
    

    
    //TouchEvents
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

private:
    cocos2d::PhysicsWorld *sceneWorld;
    
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };

    bool onContactBegin( cocos2d::PhysicsContact &contact );

    Ball *ball;
    UserPaddle *userPaddle;
    CpuPaddle *cpuPaddle;
    
};

#endif // __GAME_SCENE_H__
