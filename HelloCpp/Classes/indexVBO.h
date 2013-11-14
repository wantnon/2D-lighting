//********************************************************
//           by yang chao (wantnon)
//           2013-10-20
//			 blog: http://350479720.qzone.qq.com
//********************************************************
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
class CindexVBO :public CCObject
{
public:
	GLuint posBuffer ;
    GLuint texCoordBuffer ;
    GLuint indexBuffer ;
	int m_indexArrayLen;
	int m_posArrayLen;
	int m_texCoordArrayLen;
	CindexVBO(){
		posBuffer=0 ;
		texCoordBuffer=0 ;
		indexBuffer=0 ;
		m_indexArrayLen=0;
	    m_posArrayLen=0;
	    m_texCoordArrayLen=0;
	}
	virtual ~CindexVBO(){
		glDeleteBuffers(1, &posBuffer) ;
		glDeleteBuffers(1, &texCoordBuffer) ;
		glDeleteBuffers(1, &indexBuffer) ;
    
	}
	static void enableAttribArrays(){
		glEnableVertexAttribArray(kCCVertexAttrib_Position);
		glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
	}
	static void bindTexture(GLenum textureAttachPoint,GLuint texture){
		glActiveTexture(textureAttachPoint) ;
        ccGLBindTexture2D(texture) ;
	}
	void genBuffers(){
		if(posBuffer==0)glGenBuffers(1, &posBuffer);
		if(texCoordBuffer==0)glGenBuffers(1, &texCoordBuffer);
		if(indexBuffer==0)glGenBuffers(1, &indexBuffer);
	}
	void submitPos(const float posArray[],const int posArrayLen,GLenum usage){
		m_posArrayLen=posArrayLen;
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_posArrayLen*sizeof(float), posArray, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void submitTexCoord(const float texCoordArray[],const int texCoordArrayLen,GLenum usage){
		m_texCoordArrayLen=texCoordArrayLen;
	    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, texCoordArrayLen*sizeof(float), texCoordArray, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void submitIndex(const int indexArray[],const int indexArrayLen,GLenum usage){
		m_indexArrayLen=indexArrayLen;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArrayLen*sizeof(int), indexArray, usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void setPointers(){
		//set position format
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//set texCoord format
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void draw(GLenum mode){
	   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	   glDrawElements(mode, m_indexArrayLen, GL_UNSIGNED_INT, 0) ;
	   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

};