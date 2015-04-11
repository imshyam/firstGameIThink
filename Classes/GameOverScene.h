#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
    
    void onKeyReleased( cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event );

    void GoToGame (Ref *pSender);
    void GoToHome (Ref *pSender);

private:
    cocos2d::PhysicsWorld *sceneWorld;
    
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
};

#endif // __GAME_SCENE_H__
