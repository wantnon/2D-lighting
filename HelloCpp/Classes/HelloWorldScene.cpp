#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "SceneNode.h"
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 /*   /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
*/
    /////////////////////////////
    // 3. add your codes below...
    CCDirector::sharedDirector()->setDisplayStats(true);
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    //enable touch
	setTouchEnabled( true );
    //light2D
    light2D=new Clight2D();
    light2D->initWithFile("light.png");
    light2D->setPosition(ccp(winSize.width/3, winSize.height/3*2));
    this->addChild(light2D,100);
    light2D->release();
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("light ", "Arial", 30);
        light2D->addChild(pLabel);
        pLabel->setPosition(ccp(light2D->getContentSize().width/2, light2D->getContentSize().height+pLabel->getContentSize().height/2));
    }
    light2D->setVisible(false);
    //sceneNode, sprite using 2D light
	SceneNode*sceneNode=new SceneNode();
	sceneNode->init("fish.png","fish_height.png");
	sceneNode->setPosition(ccp(winSize.width/2,winSize.height/2));
    sceneNode->setAnchorPoint(ccp(0.5,0.5));
    sceneNode->setDiffuseLight(light2D->diffuse);
    sceneNode->setAmbientLight(light2D->ambient);
    sceneNode->setLight2DPos(light2D->getPosition());
	this->addChild(sceneNode);
    sceneNode->setVisible(light2D->isVisible());
    pSceneNode=sceneNode;
    sceneNode->release();
    
    //sprite not using 2D light
    spriteSimple=CCSprite::create();
    spriteSimple->initWithFile("fish.png");
    spriteSimple->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(spriteSimple);
    spriteSimple->setVisible(!light2D->isVisible());
    
    //ui node
    uiNode_lighting=CCNode::create();
    this->addChild(uiNode_lighting);
    uiNode_lighting->setVisible(light2D->isVisible());
    if(light2D->isVisible()){
        uiNode_lighting->setPosition(ccp(0, 0));
    }else{
        uiNode_lighting->setPosition(ccp(INFINITY, INFINITY));
    }
    
    
    //----light diffuse sliders
    {
        vector<CCControlSlider**> ppSliderList;
        ppSliderList.push_back(&m_pSliderCtl1);
        ppSliderList.push_back(&m_pSliderCtl2);
        ppSliderList.push_back(&m_pSliderCtl3);
        vector<float> initValueList;
        initValueList.push_back(light2D->diffuse.v[0]);
        initValueList.push_back(light2D->diffuse.v[1]);
        initValueList.push_back(light2D->diffuse.v[2]);
        vector<float*> initValueVarList;
        initValueVarList.push_back(&m_initValue1);
        initValueVarList.push_back(&m_initValue2);
        initValueVarList.push_back(&m_initValue3);
        vector<string> titleList;
        titleList.push_back("R ");
        titleList.push_back("G ");
        titleList.push_back("B ");
        vector<SEL_CCControlHandler> pSelectorList;
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction1));
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction2));
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction3));
        //title
        CCLabelTTF* pLabel = CCLabelTTF::create("light diffuse ", "Arial", 30);
        pLabel->setAnchorPoint(ccp(0,0.5));
        uiNode_lighting->addChild(pLabel, 1);
        for(int i=0;i<(int)ppSliderList.size();i++){
            CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
            slider->setAnchorPoint(ccp(0.5f, 0.5f));
            slider->setMinimumValue(0.0f); // Sets the min value of range
            slider->setMaximumValue(1.0f); // Sets the max value of range
            *initValueVarList[i]=initValueList[i];
            slider->setValue(initValueList[i]);
            slider->addTargetWithActionForControlEvents(this, pSelectorList[i], CCControlEventValueChanged);
            uiNode_lighting->addChild(slider,100);
            *ppSliderList[i]=slider;
            //title
            CCLabelTTF* pLabel = CCLabelTTF::create(titleList[i].c_str(), "Arial", 30);
            pLabel->setPosition(slider->getPosition()+ccp(-pLabel->getContentSize().width/2,slider->getContentSize().height/2));
            slider->addChild(pLabel, 1);
        }
        //positions
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize sliderSize = (*ppSliderList[0])->getContentSize();
        CCPoint leftUpPos=ccp(screenSize.width / 2-sliderSize.width-30, screenSize.height / 4);
        pLabel->setPosition(leftUpPos-ccp(0,-pLabel->getContentSize().height/2));
        (*ppSliderList[0])->setPosition(pLabel->getPosition()+ccp(sliderSize.width/2,-pLabel->getContentSize().height/2-sliderSize.height/2));
        (*ppSliderList[1])->setPosition((*ppSliderList[0])->getPosition()+ccp(0,-sliderSize.height));
        (*ppSliderList[2])->setPosition((*ppSliderList[1])->getPosition()+ccp(0,-sliderSize.height));
        
    }
    //----light ambient sliders
    {
        vector<CCControlSlider**> ppSliderList;
        ppSliderList.push_back(&m_pSliderCtl1a);
        ppSliderList.push_back(&m_pSliderCtl2a);
        ppSliderList.push_back(&m_pSliderCtl3a);
        vector<float> initValueList;
        initValueList.push_back(light2D->ambient.v[0]);
        initValueList.push_back(light2D->ambient.v[1]);
        initValueList.push_back(light2D->ambient.v[2]);
        vector<float*> initValueVarList;
        initValueVarList.push_back(&m_initValue1a);
        initValueVarList.push_back(&m_initValue2a);
        initValueVarList.push_back(&m_initValue3a);
        vector<string> titleList;
        titleList.push_back("R ");
        titleList.push_back("G ");
        titleList.push_back("B ");
        vector<SEL_CCControlHandler> pSelectorList;
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction1a));
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction2a));
        pSelectorList.push_back(cccontrol_selector(HelloWorld::sliderAction3a));
        //title
        CCLabelTTF* pLabel = CCLabelTTF::create("light ambient ", "Arial", 30);
        pLabel->setAnchorPoint(ccp(0,0.5));
        uiNode_lighting->addChild(pLabel, 1);
        for(int i=0;i<(int)ppSliderList.size();i++){
            CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
            slider->setAnchorPoint(ccp(0.5f, 0.5f));
            slider->setMinimumValue(0.0f); // Sets the min value of range
            slider->setMaximumValue(1.0f); // Sets the max value of range
            *initValueVarList[i]=initValueList[i];
            slider->setValue(initValueList[i]);
            slider->addTargetWithActionForControlEvents(this, pSelectorList[i], CCControlEventValueChanged);
            uiNode_lighting->addChild(slider,100);
            *ppSliderList[i]=slider;
            //title
            CCLabelTTF* pLabel = CCLabelTTF::create(titleList[i].c_str(), "Arial", 30);
            pLabel->setPosition(slider->getPosition()+ccp(-pLabel->getContentSize().width/2,slider->getContentSize().height/2));
            slider->addChild(pLabel, 1);
        }
        //positions
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize sliderSize = (*ppSliderList[0])->getContentSize();
        CCPoint leftUpPos=ccp(screenSize.width / 2+30, screenSize.height / 4);
        pLabel->setPosition(leftUpPos-ccp(0,-pLabel->getContentSize().height/2));
        (*ppSliderList[0])->setPosition(pLabel->getPosition()+ccp(sliderSize.width/2,-pLabel->getContentSize().height/2-sliderSize.height/2));
        (*ppSliderList[1])->setPosition((*ppSliderList[0])->getPosition()+ccp(0,-sliderSize.height));
        (*ppSliderList[2])->setPosition((*ppSliderList[1])->getPosition()+ccp(0,-sliderSize.height));
        
    }


	
    //reset control button
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        cocos2d::extension::CCScale9Sprite* btnUp=cocos2d::extension::CCScale9Sprite::create("button.png");
        cocos2d::extension::CCScale9Sprite* btnDn=cocos2d::extension::CCScale9Sprite::create("button_dn.png");
        CCLabelTTF*title=CCLabelTTF::create("reset", "Helvetica", 30);
        cocos2d::extension::CCControlButton* controlButton=cocos2d::extension::CCControlButton::create(title, btnUp);
        controlButton->setBackgroundSpriteForState(btnDn,cocos2d::extension::CCControlStateHighlighted);
        controlButton->setPreferredSize(CCSize(80,80));
        controlButton->setPosition(ccp(m_pSliderCtl1a->getPositionX()+m_pSliderCtl1a->getContentSize().width/2+controlButton->getContentSize().width/2+30,
                                       screenSize.height / 4-controlButton->getContentSize().height/2));
        controlButton->addTargetWithActionForControlEvents(this, (cocos2d::extension::SEL_CCControlHandler)(&HelloWorld::resetSliders), cocos2d::extension::CCControlEventTouchDown);
        uiNode_lighting->addChild(controlButton);
        controlButton->setVisible(true);
        m_controlButton=controlButton;
    }
    
    //----menu0
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLabelTTF* pLabel0 = CCLabelTTF::create("no lighting", "Arial", 25);
        CCLabelTTF* pLabel1 = CCLabelTTF::create("lighting", "Arial", 25);
        
        pMenuItem0 = CCMenuItemImage::create("btn.png","btn_dn.png",this,menu_selector(HelloWorld::menu0Callback));
        pMenuItem0->setPosition(CCPointZero);
        pMenuItem0->addChild(pLabel0,10);
        pLabel0->setPosition(ccp(pMenuItem0->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
        
        pMenuItem1 = CCMenuItemImage::create("btn.png","btn_dn.png",this,menu_selector(HelloWorld::menu1Callback));
        pMenuItem1->setPosition(pMenuItem0->getPosition()-ccp(0,pMenuItem0->getContentSize().height));
        pMenuItem1->addChild(pLabel1,10);
        pLabel1->setPosition(ccp(pMenuItem1->getContentSize().width/2,pMenuItem1->getContentSize().height/2));
        
        pMenu0 = CCMenu::create(pMenuItem0, pMenuItem1,NULL);
        pMenu0->setPosition(ccp(screenSize.width*(3.0/4), screenSize.height*(3.0/4)));
        this->addChild(pMenu0, 1);
        
        checkPic = CCSprite::create();
        checkPic->initWithFile("check.png");
        checkPic->setPosition(ccp(pMenuItem0->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
        if(light2D->isVisible()==false){
            pMenuItem0->addChild(checkPic);
        }else{
            pMenuItem1->addChild(checkPic);
        }

        
        
        
    }

    
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by yang chao (wantnon) 2013-11-14", "Arial", 30);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-60));
        this->addChild(pLabel, 1);
    }

    // add a label shows "Hello World"
    // create and initialize a label
 
    CCLabelTTF* pLabel = CCLabelTTF::create("2D lighting", "Arial", 45);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    //add a empty sprite to avoid CCLabelTTF show a block rect
    CCSprite* sprite=CCSprite::create();
    this->addChild(sprite,0);
  
    
    // add "HelloWorld" splash screen"
/*    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    */
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::menu0Callback(CCObject* pSender){
    checkPic->retain();
    checkPic->removeFromParentAndCleanup(false);
    pMenuItem0->addChild(checkPic);
    checkPic->release();
    checkPic->setPosition(ccp(pMenuItem0->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
    //
    pSceneNode->setVisible(false);
    spriteSimple->setVisible(true);
    uiNode_lighting->setVisible(false);
    uiNode_lighting->setPosition(ccp(INFINITY,INFINITY));
    light2D->setVisible(false);
    
    
    
}

void HelloWorld::menu1Callback(CCObject* pSender){
    checkPic->retain();
    checkPic->removeFromParentAndCleanup(false);
    pMenuItem1->addChild(checkPic);
    checkPic->release();
    checkPic->setPosition(ccp(pMenuItem1->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem1->getContentSize().height/2));
    //
    pSceneNode->setVisible(true);
    spriteSimple->setVisible(false);
    uiNode_lighting->setVisible(true);
    uiNode_lighting->setPosition(ccp(0,0));
    light2D->setVisible(true);
    
}

void HelloWorld::sliderAction1(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->diffuse.v[0]=value;
    pSceneNode->setDiffuseLight(light2D->diffuse);
    light2D->setColor(ccc3(light2D->diffuse.v[0]*255, light2D->diffuse.v[1]*255, light2D->diffuse.v[2]*255));
}
void HelloWorld::sliderAction2(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->diffuse.v[1]=value;
    pSceneNode->setDiffuseLight(light2D->diffuse);
    light2D->setColor(ccc3(light2D->diffuse.v[0]*255, light2D->diffuse.v[1]*255, light2D->diffuse.v[2]*255));
    
}
void HelloWorld::sliderAction3(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->diffuse.v[2]=value;
    pSceneNode->setDiffuseLight(light2D->diffuse);
    light2D->setColor(ccc3(light2D->diffuse.v[0]*255, light2D->diffuse.v[1]*255, light2D->diffuse.v[2]*255));
    
}


void HelloWorld::sliderAction1a(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->ambient.v[0]=value;
    pSceneNode->setAmbientLight(light2D->ambient);
}
void HelloWorld::sliderAction2a(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->ambient.v[1]=value;
    pSceneNode->setAmbientLight(light2D->ambient);
}
void HelloWorld::sliderAction3a(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    light2D->ambient.v[2]=value;
    pSceneNode->setAmbientLight(light2D->ambient);
}
void HelloWorld::resetSliders(CCObject *senderz, cocos2d::extension::CCControlEvent controlEvent){
    vector<CCControlSlider*> pSliderList;
    pSliderList.push_back(m_pSliderCtl1);
    pSliderList.push_back(m_pSliderCtl2);
    pSliderList.push_back(m_pSliderCtl3);
    pSliderList.push_back(m_pSliderCtl1a);
    pSliderList.push_back(m_pSliderCtl2a);
    pSliderList.push_back(m_pSliderCtl3a);
    vector<float> initValueList;
    initValueList.push_back(m_initValue1);
    initValueList.push_back(m_initValue2);
    initValueList.push_back(m_initValue3);
    initValueList.push_back(m_initValue1a);
    initValueList.push_back(m_initValue2a);
    initValueList.push_back(m_initValue3a);
    for(int i=0;i<(int)pSliderList.size();i++){
        pSliderList[i]->setValue(initValueList[i]);
    }
    light2D->diffuse.init(m_initValue1, m_initValue2, m_initValue3, 1);
    light2D->ambient.init(m_initValue1a, m_initValue2a, m_initValue3a, 1);
}



void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        if(light2D->isVisible()){
            light2D->setPosition(loc_GLSpace);
            pSceneNode->setLight2DPos(light2D->convertToWorldSpaceAR(ccp(0,0)));
        }
        
    }
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        if(light2D->isVisible()){
            light2D->setPosition(loc_GLSpace);
            pSceneNode->setLight2DPos(light2D->convertToWorldSpaceAR(ccp(0,0)));
        }
		
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        if(light2D->isVisible()){
            light2D->setPosition(loc_GLSpace);
            pSceneNode->setLight2DPos(light2D->convertToWorldSpaceAR(ccp(0,0)));
        }
    }
}
