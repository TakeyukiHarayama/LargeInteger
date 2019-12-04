#include "division.h"
#include "add.h"
#include "sub.h"

int nlz8(uint8_t x){
    int n = 0;
    
    if(x == 0){return 8;}
    if(x <= 0b00001111){
        n += 4;
        x = x << 4;
    }
    if(x <= 0b00111111){
        n += 2;
        x = x << 2;
    }
    if(x <= 0b01111111){
        n += 1;
    }
    return n;
}

int nlz16(uint16_t x){
    int n = 0;
    
    if(x == 0){return 16;}
    if(x <= 0b0000000011111111){
        n += 8;
        x = x << 8;
    }
    if(x <= 0b0000111111111111){
        n += 4;
        x = x << 4;
    }
    if(x <= 0b0011111111111111){
        n += 2;
        x = x << 2;
    }
    if(x <= 0b0111111111111111){
        n += 1;
    }
    return n;
}

int KNUTH_div8_t(mpv8_t *u, mpv8_t *v, mpv8_t *q, mpv8_t *r, int const m, int const n, int  base){
    int i, j, d;
	int din = 0;
    bool borrowflag = false;
    uint16_t uhat, qhat, rhat, s, k;
    mpv8_t vn, un, vhat, um, uhathat;
    
    clearByZero8_t(q);
    clearByZero8_t(r);
    clearByZero8_t(&vn);
    clearByZero8_t(&un);
    clearByZero8_t(&vhat);
    clearByZero8_t(&um);
    clearByZero8_t(&uhathat);
    
    if(n > m || m > G_MAIN_DIGIT){
        printf("KNUTH division n>m error!\n");
        exit(1);
    }
    if(n == 0 || m == 0){return 0;}
    if(n == 1){
        k = 0;
        for(j=m-1; j>=0; j--){
            q->n[j] = (k * base +u->n[j]) / v->n[0];
            k = (k * base + u->n[j]) - q->n[j] * v->n[0];
        }
        if(r != NULL){r->n[0] = k;}
        return 0;
    }
   
	/*Step D1********************************************************/
    d = nlz8(v->n[n-1]);
    vn.n[0] = (v->n[0] << d) & 0x00FF;
    for(i=1; i<n; i++){
        vn.n[i]=(v->n[i] << d & 0x00FF) + (v->n[i-1] >> (8-d));
    }
    un.n[0] = (u->n[0] << d) & 0x00FF;
    for(i=1; i<m+1; i++){
        un.n[i]=(u->n[i] << d & 0x00FF) + (u->n[i-1] >> (8-d));
    }

	/*Step D2 and D3*************************************************/
    for (j=m-n; j>=0; j--) {
        uhat = un.n[j+n] * base + un.n[j+n-1];
        qhat = uhat / vn.n[n-1];
        rhat = uhat % vn.n[n-1];
        borrowflag = false;
        while(qhat >= base || (qhat * vn.n[n-2] > base * rhat + un.n[j+n-2])){
            qhat = qhat -1;
            rhat = rhat + vn.n[n-1];
            if(rhat >= base){break;}
        }
	/*Step D4********************************************************/
        k=0;
        for(i=0; i<n+1; i++){
            //set vhat <- vn * qhat
            s = vn.n[i] * qhat + k;
            if(i >= n){s = k;}
            k = s / base;
            vhat.n[i] = s % base;
            //set um <- un
            um.n[i] = un.n[i+j];
        }
        //uhathat <- um - vhat
        if(sub8_t(&um, &vhat, &uhathat, din, base)){
            printf("KNUTH division sub error!\n");
            exit(1);
        }
        if(getSign8_t(&uhathat) == G_MAIN_NEGATIVE){
            setInt8_t(&um, pow(base,n+1), base);
            add8_t(&uhathat, &um, &uhathat, din, base);
            borrowflag = true;
        }
	/*Step D5********************************************************/
        q->n[j] = qhat;
	/*Step D6********************************************************/
        if(borrowflag){
            q->n[j] = q->n[j] - 1;
            copympv8_t(&vn, &vhat);
            add8_t(&uhathat, &vhat, &uhathat, din, base);
        }
        for(i=0; i<n+1; i++){
            un.n[i+j] = uhathat.n[i];
        }
    }
	/*Step D8********************************************************/
    for(i=0; i<n; i++){
        r->n[i] = ((un.n[i] >> d) & 0x00FF) | ((un.n[i+1] << (8-d)) & 0x00FF);
    }
    
    return 0;
}

int KNUTH_div(mpv_t *u, mpv_t *v, mpv_t *q, mpv_t *r, int const m, int const n, int  base){
    int i, j, d;
	int din = 0;
    bool borrowflag = false;
    uint32_t uhat, qhat, rhat, s, k;
    mpv_t vn, un, vhat, um, uhathat;
    
    clearByZero(q);
    clearByZero(r);
    clearByZero(&vn);
    clearByZero(&un);
    clearByZero(&vhat);
    clearByZero(&um);
    clearByZero(&uhathat);
    
    if(n > m || m > G_MAIN_DIGIT){
        printf("KNUTH division n>m error!\n");
        exit(1);
    }
    if(n == 0 || m == 0){return 0;}
    if(n == 1){
        k = 0;
        for(j=m-1; j>=0; j--){
            q->n[j] = (k * base +u->n[j]) / v->n[0];
            k = (k * base + u->n[j]) - q->n[j] * v->n[0];
        }
        if(r != NULL){r->n[0] = k;}
        return 0;
    }
    
    d = nlz16(v->n[n-1]);
    vn.n[0] = (v->n[0] << d) & 0x0000FFFF;
    for(i=1; i<n; i++){
        vn.n[i]=(v->n[i] << d & 0x0000FFFF) + (v->n[i-1] >> (16-d));
    }
    un.n[0] = (u->n[0] << d) & 0x0000FFFF;
    for(i=1; i<m; i++){
        un.n[i]=(u->n[i] << d & 0x0000FFFF) + (u->n[i-1] >> (16-d));
    }
    for (j=m-n; j>=0; j--) {
        uhat = un.n[j+n] * base + un.n[j+n-1];
        qhat = uhat / vn.n[n-1];
        rhat = uhat % vn.n[n-1];
        borrowflag = false;
        while(qhat >= base || (qhat * vn.n[n-2] > base * rhat + un.n[j+n-2])){
            qhat = qhat -1;
            rhat = rhat + vn.n[n-1];
            if(rhat >= base){break;}
        }
        k=0;
        for(i=0; i<n+1; i++){
            //set vhat <- vn * qhat
            s = vn.n[i] * qhat + k;
            if(i >= n-1){s = k;}
            k = s / base;
            vhat.n[i] = s % base;
            //set um <- un
            um.n[i] = un.n[i+j];
        }
        //uhathat <- um - vhat
        if(sub(&um, &vhat, &uhathat, din, base)){
            printf("KNUTH division sub error!\n");
            exit(1);
        }
        if(getSign(&uhathat) == G_MAIN_NEGATIVE){
            setInt(&um, pow(base,n+1), base);
            add(&uhathat, &um, &uhathat, din, base);
            borrowflag = true;
        }
        q->n[j] = qhat;
        if(borrowflag){
            q->n[j] = q->n[j] - 1;
            copympv_t(&vn, &vhat);
            vhat.n[n-1] = 0;
            add(&uhathat, &vhat, &uhathat, din, base);
        }
        for(i=0; i<n+1; i++){
            un.n[i+j] = uhathat.n[i];
        }
    }
    for(i=0; i<m; i++){
        un.n[i]=(u->n[i] >> d & 0x0000FFFF) + (u->n[i+1] << (16-d));
    }
    un.n[0] = (u->n[0] >> d) & 0x0000FFFF;
    
    return 0;
}
