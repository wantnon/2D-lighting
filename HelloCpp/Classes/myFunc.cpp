//
//  myFunc.cpp
//  HelloCpp
//
//  Created by apple on 13-10-26.
//
//

#include "myFunc.h"
#include "support/ccUtils.cpp"//if we use #include "support/ccUtils.cpp", in vs2010 cause linking error "unsolved external symbol".

CCTexture2D* createCCTexture2DWithSize(const CCSize&size,CCTexture2DPixelFormat eFormat,
                                       float r=0,float g=0,float b=0,float a=0)//r,g,b,a are range form 0 to 1
{
    //the code below is copied from CCRenderTexture::initWithWidthAndHeight, with some modification.
    CCTexture2D* pTexture=NULL;
    void *data = NULL;
    do{
        int w = (int)(size.width * CC_CONTENT_SCALE_FACTOR());
        int h = (int)(size.height * CC_CONTENT_SCALE_FACTOR());
        
        // textures must be power of two squared
        unsigned int powW = 0;
        unsigned int powH = 0;
        
        if (CCConfiguration::sharedConfiguration()->supportsNPOT())
        {
            powW = w;
            powH = h;
        }
        else
        {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }
        
        data = malloc((int)(powW * powH * 4));
        CC_BREAK_IF(! data);
        
        memset(data, 0, (int)(powW * powH * 4));
        
        //fill data with color value
        int _r=r*255;
        int _g=g*255;
        int _b=b*255;
        int _a=a*255;
        for(int i=0;i<powH;i++){
            for(int j=0;j<powW;j++){
                ((char*)data)[(i*powW+j)*4+0]=_r;
                ((char*)data)[(i*powW+j)*4+1]=_g;
                ((char*)data)[(i*powW+j)*4+2]=_b;
                ((char*)data)[(i*powW+j)*4+3]=_a;
            }
        }
        
        pTexture = new CCTexture2D();
        if (pTexture)
        {
            pTexture->initWithData(data, eFormat, powW, powH, CCSizeMake((float)w, (float)h));
        }
    }while (0);
    return pTexture;

}