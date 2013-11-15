//********************************************************
//           by yang chao (wantnon) 
//			 2013-10-20
//			 blog: http://350479720.qzone.qq.com
//********************************************************

#ifndef HelloWorld_SceneNode_h
#define HelloWorld_SceneNode_h
#include "cocos2d.h"

#include<iostream>
#include<map>
using namespace std;
#include "indexVBO.h"
#include "mymath.h"
using namespace cocos2d;
//if program1 and program2 have a uniform variable with the same name, the two variable's uniform ID (GLint) may be different. 
//so safe way is let each shader program hold his own uniform IDs.
class CGLProgramWithMyUnifos{
	CCGLProgram*program;
public:
	map<string,GLint> myUnifoMap;
    CGLProgramWithMyUnifos(){
		program=NULL;
	}
	virtual ~CGLProgramWithMyUnifos(){
		program->release();
	}
    void setProgram(CCGLProgram*_program){
        if(program){
            program->release();
        }
        program=_program;
        program->retain();
    }
    CCGLProgram*getProgram(){
        return program;
    }

};
class SceneNode : public CCSprite{
public:
	SceneNode() {
        step_s=0;
        step_t=0;
        texHeightMap=NULL;
        light2DPos=CCPoint(0,0);
        ambientMaterial.init(1, 1, 1, 1);
        diffuseMaterial.init(1, 1, 1, 1);
        ambientLight.init(1, 1, 1, 1);
        diffuseLight.init(1, 1, 1, 1);
        
    }
	virtual ~SceneNode() {
        texHeightMap->release();
    }
	bool init(string colorTexFileName,string heightMapTexFileName) ;
	void draw() ;
    void setLight2DPos(CCPoint pos){light2DPos=pos;}
    void setAmbientLight(Cv4 ambient){ambientLight=ambient;}
    void setDiffuseLight(Cv4 diffuse){diffuseLight=diffuse;}
private:
	
	CGLProgramWithMyUnifos program_renderRipple;

	
	float step_s,step_t;
    CCTexture2D* texHeightMap;
    
    CCSize winSize;//equals to designResolutionSize
    CCSize screenSize;//real screen size of simulator/device
    
    CCPoint light2DPos;
    
    Cv4 ambientMaterial;
    Cv4 diffuseMaterial;
    
    Cv4 ambientLight;
    Cv4 diffuseLight;











};
#endif
