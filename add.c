//
//  add.c
//  LargeInteger
//
//  Created by wts86 on 2019/06/03.
//  Copyright © 2019 Takeyuki. All rights reserved.
//
#include "main.h"

//a+b=c
int add8_t(mpv8_t *a, mpv8_t *b,mpv8_t *c, int din, int base){
    int i = 0;
    long long s = 0;
    int d = 0;
    int getSigna = getSign(a);
    int getSignb = getSign(b);
    bool SignFlag = true;
    mpv8_t absab;

    //aが正でbが負
    if(getSigna == 1 && getSignb == -1){
        getAbs(b, &absab);
        return sub(a, &absab ,c, 0, base);;
    }
    //aが負でbが正
    if(getSigna == -1 && getSignb == 1){
        getAbs(a, &absab);
        return sub(b, &absab ,c, 0, base);
    }
    //aが負でbも負
    if(getSigna == -1 && getSignb == -1){
        SignFlag = false;
    }
    //aが正でbも正
    if(getSigna == 1 && getSignb == 1){
        SignFlag = true;
    }
    
    d = din;
    for(i=0; i<DIGIT; i++){
        s = a->n[i] + b->n[i] + d;
        d = s / base;
        c->n[i] = s % base;
    }
    if(SignFlag == false){
        setSign(c, -1);
    }
    return d;
}

int add(mpv_t *a, mpv_t *b,mpv_t *c, int din, int base){
    int i = 0;
    long long s = 0;
    int d = 0;
    int getSigna = getSign(a);
    int getSignb = getSign(b);
    bool SignFlag = true;
    mpv_t absab;

    //aが正でbが負
    if(getSigna == 1 && getSignb == -1){
        getAbs(b, &absab);
        return sub(a, &absab ,c, 0, base);;
    }
    //aが負でbが正
    if(getSigna == -1 && getSignb == 1){
        getAbs(a, &absab);
        return sub(b, &absab ,c, 0, base);
    }
    //aが負でbも負
    if(getSigna == -1 && getSignb == -1){
        SignFlag = false;
    }
    //aが正でbも正
    if(getSigna == 1 && getSignb == 1){
        SignFlag = true;
    }
    
    d = din;
    for(i=0; i<DIGIT; i++){
        s = a->n[i] + b->n[i] + d;
        d = s / base;
        c->n[i] = s % base;
    }
    if(SignFlag == false){
        setSign(c, -1);
    }
    return d;
}
