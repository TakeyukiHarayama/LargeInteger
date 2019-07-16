//
//  multiple.c
//  LargeInteger
//
//  Created by 原山赳幸 on 2019/06/10.
//  Copyright © 2019 Takeyuki. All rights reserved.
//

#include "multiple.h"
#include "main.h"

// a + b = c, n : length of b, m : length of a, base : basempv_t
int BasecaseMultiply(mpv_t *a, mpv_t *b, mpv_t *c, int m, int n, int base){
    int i, j;
    int din = 0;
    uint64_t d = 0;
    uint64_t s = 0;
    int getSigna = getSign(a);
    int getSignb = getSign(b);
    mpv_t absa, absb, chat;
    
    clearByZero(&chat);
    if(m+n > DIGIT){
        printf("result is overflow!!\n");
        exit(1);
    }
    //aが正でbが負の場合
    if(getSigna == 1 && getSignb == -1){
        getAbs(b, &absb);
        BasecaseMultiply(a, &absb, c, m, n, base);
        setSign(c, -1);
        return 0;
    }
    //aが負でbが正の場合
    if(getSigna == -1 && getSignb == 1){
        getAbs(a, &absa);
        BasecaseMultiply(&absa, b, c, m, n, base);
        setSign(c, -1);
        return 0;
    }
    //aが負でbも負の場合
    if(getSigna == -1 && getSignb == -1){
        getAbs(a, &absa);
        getAbs(b, &absb);
        BasecaseMultiply(&absa, &absb, c, m, n, base);
        return 0;
    }
    
    //c = A * b_0
    for(i=0; i<m+1; i++){
        s = a->n[i] * b->n[0] + d;
        d = s / base;
        c->n[i] = s % base;
    }
    for(j=1; j<n; j++){
        //chat = B^j(A * b_j)
        d = 0;
        for(i=0; i<m+1; i++){
            s = a->n[i] * b->n[j] + d;
            d = s / base;
            chat.n[i + j] = s % base;
        }
        //c = c + chat
        add(c, &chat, c, din, base);
        clearByZero(&chat);
    }
    return 0;
}
