

#include "SceneNode.h"
#include <iostream>
#include <map>
#include "support/ccUtils.h"
#include "myFunc.h"
using namespace cocos2d ;
using namespace std ;


bool SceneNode::init(string colorTexFileName,string heightMapTexFileName)
{
    this->cocos2d::CCSprite::initWithFile(colorTexFileName.c_str());

    //set projection is 2D (default is 3D). if use 3D projection, projection error accumulation may cause ripple effect mess.
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //get screenSize
    //screenSize is the real size of simulator/device screen
    screenSize=CCEGLView::sharedOpenGLView()->getFrameSize();
    CCLOG("screenSize:%f,%f",screenSize.width,screenSize.height);
    //get winSize
    //winSize is equals to designResolutionSize. we only need to writting code based on designResolutionSize (and forget the real screenSize).
    winSize=CCDirector::sharedDirector()->getWinSize();
    CCLOG("winSize:%f,%f",winSize.width,winSize.height);
	//texHeightMap
    texHeightMap = CCTextureCache::sharedTextureCache()->addImage(heightMapTexFileName.c_str());
    CCSize texHeightMapSize=texHeightMap->getContentSize();
    CCLOG("texHeightMapSize:%f,%f",texHeightMapSize.width,texHeightMapSize.height);
    //use texSize to calculate step_s and step_t
    step_s=1.0/texHeightMapSize.width;
	step_t=1.0/texHeightMapSize.height;
    //renderRipple shader
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("lighting2D.fsh").c_str())->getCString();
		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        //bind attribute
		pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        //link  (must after bindAttribute)
		pProgram->link();
        //get cocos2d-x build-in uniforms
		pProgram->updateUniforms();
        //get my own uniforms
		map<string,GLint> myUnifoMap;
        myUnifoMap["texHeightMap"] = glGetUniformLocation(pProgram->getProgram(),"texHeightMap");
        myUnifoMap["step_s"] = glGetUniformLocation(pProgram->getProgram(),"step_s");
        myUnifoMap["step_t"] = glGetUniformLocation(pProgram->getProgram(),"step_t");
        myUnifoMap["light2DInTexSpace"] = glGetUniformLocation(pProgram->getProgram(),"light2DInTexSpace");
        myUnifoMap["diffuseMaterial"] = glGetUniformLocation(pProgram->getProgram(),"diffuseMaterial");
        myUnifoMap["ambientMaterial"] = glGetUniformLocation(pProgram->getProgram(),"ambientMaterial");
        myUnifoMap["diffuseLight"] = glGetUniformLocation(pProgram->getProgram(),"diffuseLight");
        myUnifoMap["ambientLight"] = glGetUniformLocation(pProgram->getProgram(),"ambientLight");
        //make program_renderRipple
        program_renderRipple.myUnifoMap=myUnifoMap;
        program_renderRipple.setProgram(pProgram);
        //program can be released
        pProgram->release();
        //check gl error
		CHECK_GL_ERROR_DEBUG();
	}
	//check gl error
	CHECK_GL_ERROR_DEBUG();

	return true ;
}

void SceneNode::draw()
{
    //change shader
    this->setShaderProgram(program_renderRipple.getProgram());
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    //pass values for my own uniforms
    glUniform1f(program_renderRipple.myUnifoMap["step_s"],step_s);
    glUniform1f(program_renderRipple.myUnifoMap["step_t"],step_t);
    CCPoint light2DInTexSpace; //light2D position in texture space
    {
        //tansform light2DPos to texture space
        CCPoint lightPosInWorld=light2DPos;
        //in sprite's local space, origin always at the left down corner, no matter what the anchorPoint is.
        //see:http://user.qzone.qq.com/350479720/blog/1384482833
        CCPoint texLeftUpPosInWorld=this->convertToWorldSpace(ccp(0,this->getContentSize().height));
        CCPoint texLeftUpPosToLightPos=lightPosInWorld-texLeftUpPosInWorld;
        light2DInTexSpace=CCPoint(texLeftUpPosToLightPos.x/this->getContentSize().width,
                                  texLeftUpPosToLightPos.y/this->getContentSize().height);
        light2DInTexSpace.y=-light2DInTexSpace.y;
        
    }//get lightPosInTexSpace
    float light2DInTexSpace_c[2]={light2DInTexSpace.x,light2DInTexSpace.y};
    glUniform2fv(program_renderRipple.myUnifoMap["light2DInTexSpace"],1,light2DInTexSpace_c);
    glUniform4fv(program_renderRipple.myUnifoMap["diffuseMaterial"],1,diffuseMaterial.v);
    glUniform4fv(program_renderRipple.myUnifoMap["ambientMaterial"],1,ambientMaterial.v);
    glUniform4fv(program_renderRipple.myUnifoMap["diffuseLight"],1,diffuseLight.v);
    glUniform4fv(program_renderRipple.myUnifoMap["ambientLight"],1,ambientLight.v);
    //pass texture attach point id to sampler uniform
    glUniform1i(program_renderRipple.myUnifoMap["texHeightMap"],1);
    //attach texture to texture attach point
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texHeightMap->getName());
    glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
    //cal CCSprite::draw
    CCSprite::draw();
}
