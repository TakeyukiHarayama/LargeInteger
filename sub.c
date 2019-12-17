#include "sub.h"
#include "add.h"
#include "sign.h"
#include "comp.h"

//a-b =c
int sub8_t(mpv8_t *a, mpv8_t *b, mpv8_t *c, int din, int base){
    int i = 0;
    long long s = 0;
    int d = 0;
    int getSigna = getSign8_t(a);
    int getSignb = getSign8_t(b);
    mpv8_t absab;
    
    //aが正でbが負
    if(getSigna == G_MAIN_POSITIVE && getSignb == G_MAIN_NEGATIVE){
        getAbs8_t(b, &absab);
        add8_t(a, &absab, c, din, base);
        return 0;
    }
    //aが負でbが正
    if(getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_POSITIVE){
        getAbs8_t(a, &absab);
        add8_t(&absab, b, c, din, base);
        setSign8_t(c, G_MAIN_NEGATIVE);
        return 0;
    }
    //aが負でbも負
    if(getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_NEGATIVE){
        getAbs8_t(b, &absab);
        add8_t(a, &absab, c, din, base);
        return 0;
    }
    
    if(numComp8_t(a, b) == -1){
        sub8_t(b, a, c, din, base);
        setSign8_t(c, G_MAIN_NEGATIVE);
        return 0;
    }
    
    d = din;
    for(i=0; i<G_MAIN_DIGIT; i++){
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
