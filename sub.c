//
//  sub.c
//  LargeInteger
//
//  Created by 原山赳幸 on 2019/06/10.
//  Copyright © 2019 Takeyuki. All rights reserved.
//

#include "sub.h"
#include "main.h"

//a-b =c
int sub8_t(mpv8_t *a, mpv8_t *b, mpv8_t *c, int din, int base){
    int i = 0;
    long long s = 0;
    int d = 0;
    int getSigna = getSign8_t(a);
    int getSignb = getSign8_t(b);
    mpv8_t absab;
    
    //aが正でbが負
    if(getSigna == 1 && getSignb == -1){
        getAbs8_t(b, &absab);
        add8_t(a, &absab, c, 0, base);
        return 0;
    }
    //aが負でbが正
    if(getSigna == -1 && getSignb == 1){
        getAbs8_t(a, &absab);
        add8_t(&absab, b, c, 0, base);
        setSign8_t(c, -1);
        return 0;
    }
    //aが負でbも負
    if(getSigna == -1 && getSignb == -1){
        getAbs8_t(b, &absab);
        add8_t(a, &absab, c, 0, base);
        return 0;
    }
    
    if(numComp8_t(a, b) == -1){
        sub8_t(b, a, c, 0, base);
        setSign8_t(c, -1);
        return 0;
    }
    
    d = din;
    for(i=0; i<DIGIT; i++){
        s = a->n[i] - b->n[i] + d;
        if(s < 0){
            c->n[i] = base + s;
            d = -1;
        }else{
            c->n[i] = s;
            d = 0;
        }
    }
    return d;
}

//a-b =c
int sub(mpv_t *a, mpv_t *b, mpv_t *c, int din, int base){
    int i = 0;
    long long s = 0;
    int d = 0;
    int getSigna = getSign(a);
    int getSignb = getSign(b);
    mpv_t absab;
    
    //aが正でbが負
    if(getSigna == 1 && getSignb == -1){
        getAbs(b, &absab);
        add(a, &absab, c, 0, base);
        return 0;
    }
    //aが負でbが正
    if(getSigna == -1 && getSignb == 1){
        getAbs(a, &absab);
        add(&absab, b, c, 0, base);
        setSign(c, -1);
        return 0;
    }
    //aが負でbも負
    if(getSigna == -1 && getSignb == -1){
        getAbs(b, &absab);
        add(a, &absab, c, 0, base);
        return 0;
    }
    
    if(numComp(a, b) == -1){
        sub(b, a, c, 0, base);
        setSign(c, -1);
        return 0;
    }
    
    d = din;
    for(i=0; i<DIGIT; i++){
        s = a->n[i] - b->n[i] + d;
        if(s < 0){
            c->n[i] = base + s;
            d = -1;
        }else{
            c->n[i] = s;
            d = 0;
        }
    }
    return d;
}

//a-b =c, a > -1, b > -1
/*
int Knuth_multiple_sub(uint16_t a[], uint16_t b[], int32_t c[], int base, int size){
    int i = 0;
    long long s = 0;
    int d = 0;
    
    if(KNUTH_numComp(a, b, size) == -1){
        Knuth_multiple_sub(b, a, c, base, size);
        int32_setSign(c, -1, size);
        return 0;
    }
    
    for(i=0; i<size; i++){
        s = a[i] - b[i] + d;
        if(s < 0){
            c[i] = base + s;
            d = -1;
        }else{
            c[i] = s;
            d = 0;
        }
    }
    return 0;
}
 */
