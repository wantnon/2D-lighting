//
//  math.h
//  HelloCpp
//
//  Created by ck02-084 on 13-11-14.
//
//

#ifndef __HelloCpp__mymath__
#define __HelloCpp__mymath__

#include <iostream>
class Cv4{
public:
    float v[4];
    Cv4(){
        v[0]=v[1]=v[2]=v[3]=0;
    }
    Cv4(float x,float y,float z,float w){
        init(x, y, z, w);
    }
    void init(float x,float y,float z,float w){
        v[0]=x;
        v[1]=y;
        v[2]=z;
        v[3]=w;
    }
    Cv4 operator +(const Cv4&v){
        Cv4 rsv;
        rsv.v[0]=this->v[0]+v.v[0];
        rsv.v[1]=this->v[1]+v.v[1];
        rsv.v[2]=this->v[2]+v.v[2];
        rsv.v[3]=this->v[3]+v.v[3];
        return rsv;
    }
    Cv4 operator -(const Cv4&v){
        Cv4 rsv;
        rsv.v[0]=this->v[0]-v.v[0];
        rsv.v[1]=this->v[1]-v.v[1];
        rsv.v[2]=this->v[2]-v.v[2];
        rsv.v[3]=this->v[3]-v.v[3];
        return rsv;
    }
    Cv4 operator *(float k){
        Cv4 rsv;
        rsv.v[0]=this->v[0]*k;
        rsv.v[1]=this->v[1]*k;
        rsv.v[2]=this->v[2]*k;
        rsv.v[3]=this->v[3]*k;
        return rsv;
    }
};
#endif /* defined(__HelloCpp__mymath__) */
