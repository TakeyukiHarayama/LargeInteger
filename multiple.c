#include "multiple.h"
#include "add.h"
#include "sign.h"
#include "clear.h"

// a + b = c, n : length of b, m : length of a, base : basempv8_t
int BasecaseMultiply(mpv8_t *a, mpv8_t *b, mpv8_t *c, int m, int n, int base){
    int i, j;
    int din = 0;
    uint64_t d = 0;
    uint64_t s = 0;
    int getSigna = getSign8_t(a);
    int getSignb = getSign8_t(b);
    mpv8_t absa, absb, chat;
    
    clearByZero8_t(&chat);
    if(m+n > G_MAIN_DIGIT){
        printf("result is overflow!!\n");
        exit(1);
    }
    //aが正でbが負の場合
    if(getSigna == G_MAIN_POSITIVE && getSignb == G_MAIN_NEGATIVE){
        getAbs8_t(b, &absb);
        BasecaseMultiply(a, &absb, c, m, n, base);
        setSign8_t(c, G_MAIN_NEGATIVE);
        return 0;
    }
    //aが負でbが正の場合
    if(getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_POSITIVE){
        getAbs8_t(a, &absa);
        BasecaseMultiply(&absa, b, c, m, n, base);
        setSign8_t(c, G_MAIN_NEGATIVE);
        return 0;
    }
    //aが負でbも負の場合
    if(getSigna == G_MAIN_NEGATIVE && getSignb == G_MAIN_NEGATIVE){
        getAbs8_t(a, &absa);
        getAbs8_t(b, &absb);
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
        add8_t(c, &chat, c, din, base);
        clearByZero8_t(&chat);
    }
    return 0;
}
