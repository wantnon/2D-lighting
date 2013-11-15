#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SceneNode.h"
#include "light2D.h"

using namespace cocos2d;
using namespace cocos2d::extension;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
public:
    CCNode* uiNode_lighting;
public:
    //touch
	virtual void ccTouchesBegan(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
public:
    cocos2d::extension::CCControlButton* m_controlButton;
    void resetSliders(CCObject *senderz, cocos2d::extension::CCControlEvent controlEvent);
public:
    CCControlSlider* m_pSliderCtl;
    void sliderAction(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue;
    //slider1
    CCControlSlider* m_pSliderCtl1;
    void sliderAction1(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue1;
	//slider2
	CCControlSlider* m_pSliderCtl2;
    void sliderAction2(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue2;
    //slider3
    CCControlSlider* m_pSliderCtl3;
    void sliderAction3(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue3;
    
    //slider1a
    CCControlSlider* m_pSliderCtl1a;
    void sliderAction1a(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue1a;
	//slider2a
	CCControlSlider* m_pSliderCtl2a;
    void sliderAction2a(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue2a;
    //slider3a
    CCControlSlider* m_pSliderCtl3a;
    void sliderAction3a(CCObject* sender, CCControlEvent controlEvent);
    float m_initValue3a;
public:
    //menu0
    CCMenu* pMenu0;
    CCMenuItemImage *pMenuItem0;
    CCMenuItemImage *pMenuItem1;
    void menu0Callback(CCObject* pSender);
    void menu1Callback(CCObject* pSender);
    CCSprite*checkPic;
public:
    SceneNode*pSceneNode;
    CCSprite* spriteSimple;
    Clight2D*light2D;
};

#endif // __HELLOWORLD_SCENE_H__
