//
//  light2D.h
//  HelloCpp
//
//  Created by apple on 13-11-13.
//
//

#ifndef __HelloCpp__light2D__
#define __HelloCpp__light2D__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "mymath.h"
class Clight2D:public CCSprite
{
public:

    Clight2D(){
        diffuse.init(1, 1, 1, 1);
        ambient.init(0.2, 0.2, 0.2, 1);
    }
    Cv4 diffuse;
    Cv4 ambient;
    

};
#endif /* defined(__HelloCpp__light2D__) */
