#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#define N 10
#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef struct polynomial{
    float coef;
    int expn;
    struct polynomial* next;
}LNode,*LinkList;

void InitPolyn(LinkList &L){
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
}

void OrderInsert(LinkList &L,float a,int b){
    struct polynomial *p,*q;
    p=(struct polynomial*)malloc(sizeof(struct polynomial));
    q=L;
    p->expn=b;
    p->coef=a;
    while(q->next!=NULL&&p->expn>q->next->expn) q=q->next;
    if (q->next==NULL||p->expn<q->next->expn){
        p->next=q->next;
        q->next=p;
    }
    else{
        if (q->next->coef+p->coef==0)q->next=q->next->next;
        else q->next->coef=q->next->coef+p->coef;
        free(p);
    }
}

void printpolyn(LinkList L){
    struct polynomial *p=L->next;
    printf("\n此时的多项式为:");
    if (p==NULL) {
        printf("空!\n");
        p=L;
    }
    else if (p->expn==0) printf("%.2f",p->coef);
    else printf("%.2fx^%d",p->coef,p->expn);
    while (p->next!=NULL){
        p=p->next;
        if (p->coef>0) printf("+%.2fx^%d",p->coef,p->expn);
        else printf("%.2fx^%d",p->coef,p->expn);
    }
    printf("\n");
}

void CreatePolyn(LinkList &L){
    float a;
    int b;
    for (;;){
        printf("\n输入该项的系数,为0则结束:");
        scanf("%f",&a);
        if (a==0) break;
        printf("\n输入该项的次数:");
        scanf("%d",&b);
        OrderInsert(L,a,b);
    }
    printpolyn(L);
}

void DestroyPolyn(LinkList &L){
    struct polynomial *p,*q;
    p=L->next;
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    L=NULL;
}

void ClearPolyn(LinkList &L){
    struct polynomial *p,*q;
    p=L->next;
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    L->next=NULL;
}

void DeletePolyn(LinkList &L,int n){
    struct polynomial *p=L->next,*q=L;
    while (p!=NULL&&p->expn!=n) {
        q=p;
        p=p->next;
    }
    if (p!=NULL){
        q->next=p->next;
        free(p);
    }
    else printf("\n该多项式无%d次幂!\n",n);
}

void Copypolyn(LinkList &La,LinkList Lb){//将Lb复制至La中
    struct polynomial *p,*q,*s;
    s=Lb->next;
    q=La;
    while (s!=NULL){
        p=(struct polynomial*)malloc(sizeof(struct polynomial));
        p->coef=s->coef;
        p->expn=s->expn;
        q->next=p;
        s=s->next;
        q=q->next;
    }
    q->next=NULL;
}

void ADDpolyn(LinkList La,LinkList Lb,LinkList &Lc){
    struct polynomial *p,*q,*r,*s;
    p=La->next;
    q=Lb->next;
    r=Lc;
    while (p!=NULL&&q!=NULL){
        s=(struct polynomial*)malloc(sizeof(struct polynomial));
        if(p->expn==q->expn){
            if (p->coef+q->coef==0) {
                p=p->next;
                q=q->next;
                continue;
            }
            else {
                s->coef=p->coef+q->coef;
                s->expn=p->expn;
                p=p->next;
                q=q->next;
            }
        }
        else if (p->expn>q->expn){
            s->coef=q->coef;
            s->expn=q->expn;
            q=q->next;
        }
        else {
            s->coef=p->coef;
            s->expn=p->expn;
            p=p->next;
        }
        r->next=s;
        r=r->next;
    }
    if (p!=NULL) {
        while (p!=NULL){
            s=(struct polynomial*)malloc(sizeof(struct polynomial));
            s->coef=p->coef;
            s->expn=p->expn;
            r->next=s;
            r=r->next;
            p=p->next;
        }
        r->next=NULL;
    }
    else {
        while (q!=NULL){
            s=(struct polynomial*)malloc(sizeof(struct polynomial));
            s->coef=q->coef;
            s->expn=q->expn;
            r->next=s;
            r=r->next;
            q=q->next;
        }
        r->next=NULL;
    }
}

void Subpolyn(LinkList La,LinkList Lb,LinkList &Lc){//将La减掉Lb放在Lc中
    struct polynomial *p,*q,*r,*s;
    p=La->next;
    q=Lb->next;
    r=Lc;
    while (p!=NULL&&q!=NULL){
        s=(struct polynomial*)malloc(sizeof(struct polynomial));
        if(p->expn==q->expn){
            if (p->coef-q->coef==0) {
                p=p->next;
                q=q->next;
                continue;
            }
            else {
                s->coef=p->coef-q->coef;
                s->expn=p->expn;
                p=p->next;
                q=q->next;
            }
        }
        else if (p->expn>q->expn){
            s->coef=-q->coef;
            s->expn=q->expn;
            q=q->next;
        }
        else {
            s->coef=p->coef;
            s->expn=p->expn;
            p=p->next;
        }
        r->next=s;
        r=r->next;
    }
    if (p!=NULL) {
        while (p!=NULL){
            s=(struct polynomial*)malloc(sizeof(struct polynomial));
            s->coef=p->coef;
            s->expn=p->expn;
            r->next=s;
            r=r->next;
            p=p->next;
        }
        r->next=NULL;
    }
    else {
        while (q!=NULL){
            s=(struct polynomial*)malloc(sizeof(struct polynomial));
            s->coef=-q->coef;
            s->expn=q->expn;
            r->next=s;
            r=r->next;
            q=q->next;
        }
        r->next=NULL;
    }
}

int LengthPolyn(LinkList L){
    struct polynomial *p=L->next;
    int n=0;
    while (p!=NULL){
        p=p->next;
        n++;
    }
    return n;
}

double Value(LinkList L,double x){
    struct polynomial *p=L->next;
    double sum=0;
    while (p!=NULL){
        sum=sum+(p->coef)*pow(x,p->expn);
        p=p->next;
    }
    return sum;
}

void MultiPolyn(LinkList La,LinkList Lb,LinkList &Lc){
    struct polynomial *p,*q;
    int b;
    float a;
    p=La->next;
    q=Lb->next;
    while (p!=NULL){
        while (q!=NULL){
            a=p->coef*q->coef;
            b=p->expn+q->expn;
            OrderInsert(Lc,a,b);
            q=q->next;
        }
        q=Lb->next;
        p=p->next;
    }
}

int MaxExpn(LinkList L){//多项式的最大次数,用于辅助多项式的除法
    struct polynomial *p=L->next;
    if (p==NULL) return 0;
    while (p->next!=NULL) p=p->next;
    return p->expn;
}

float LastCoef(LinkList L){//多项式最后一项的系数,用于辅助多项式的除法
    struct polynomial *p=L->next;
    if (p==NULL) return 0;
    while (p->next!=NULL) p=p->next;
    return p->coef;
}

void DiviPolyn(LinkList La,LinkList Lb,LinkList &Lc,LinkList &Ld){//将La除以Lb的商放在Lc,余数放在Ld
    struct polynomial *p,*q;
    LinkList L;
    InitPolyn(L);
    int b;
    float a;
    Copypolyn(Ld,La);
    while (MaxExpn(Lb)<=MaxExpn(Ld)){
        b=MaxExpn(Ld)-MaxExpn(Lb);
        a=LastCoef(Ld)/LastCoef(Lb);
        OrderInsert(Lc,a,b);
        ClearPolyn(L);
        MultiPolyn(Lb,Lc,L);
        Subpolyn(La,L,Ld);
    }
}

void DiffPolyn(LinkList La,LinkList &Lb){//将La 求导后的结果放在Lb 中
    struct polynomial *p=La->next;
    int b;
    float a;
    while (p!=NULL){
        if (p->expn==0){
            p=p->next;
            continue;
        }
        a=p->expn*p->coef;
        b=p->expn-1;
        OrderInsert(Lb,a,b);
        p=p->next;
    }
}

void IntePolyn(LinkList La,LinkList &Lb){//将La 不定积分后的结果放在Lb中, c=0
    struct polynomial *p=La->next;
    int b;
    float a;
    while (p!=NULL){
        a=p->coef/(p->expn+1);
        b=p->expn+1;
        OrderInsert(Lb,a,b);
        p=p->next;
    }
}

int main(){
    LinkList P[N];
    int i,j,n,m,u,v;
    float a;
    int b;
    double x;
    for (i=0;i<10;i++) P[i]=NULL;
    for (;;){
        printf("\n___________________________________\n");
        printf("|菜单:                             |\n");
        printf("|0.退出                            |\n");
        printf("|1.创建多项式                      |\n");
        printf("|2.显示多项式                      |\n");
        printf("|3.复制多项式                      |\n");
        printf("|4.求和                            |\n");
        printf("|5.求差                            |\n");
        printf("|6.求值                            |\n");
        printf("|7.销毁多项式                      |\n");
        printf("|8.清空多项式                      |\n");
        printf("|9.修改多项式                      |\n");
        printf("|__________ 以下为附加项 __________|\n");
        printf("|10.多项式乘法                     |\n");
        printf("|11.多项式除法                     |\n");
        printf("|12.多项式求导                     |\n");
        printf("|13.多项式积分                     |\n");
        printf("|__________________________________|\n");
        scanf("%d",&i);
        switch(i){
            case 0:exit(0);
            case 1:
//                system("cls");
                printf("\n\n输入要创建多项式的序号,限1-10,输入0退出\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1) {
                    printf("\n输入错误!\n");
                    break;
                }
                else {
                    InitPolyn(P[n-1]);
                    CreatePolyn(P[n-1]);
                }
                break;
            case 2:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                break;
            case 3:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入被复制的多项式的编号,为0退出:\n");
                scanf("%d",&u);
                if (u==0) break;
                if (u>N||u<1||!P[u-1]){
                    printf("\n输入错误!\n");
                    break;
                }
                printf("输入所要复制至的多项式编号,为0退出\n");
                scanf("%d",&v);
                if (v==0) break;
                if (v>N||v<1){
                    printf("\n输入错误!\n");
                    break;
                }
                if (u==v) break;
                if (P[v-1]&&(P[v-1]->next)){
                    printf("复制至的多项式存储地不为空,确定继续吗?输入0退出\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[v-1]);
                Copypolyn(P[v-1],P[u-1]);
                break;
            case 4:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求和的两式序号,输入任何一个为0退出:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u>N||u<1||v>N||v<1||!P[v-1]||!P[u-1]){
                    printf("\n输入错误!\n");
                    break;
                }
                printf("输入求和结果存储地序号:\n");
                scanf("%d",&n);
                if (n==u||n==v){
                    printf("请不要这样先生!\n");
                    break;
                }
                if (n>N||n<1){
                    printf("\n输入错误!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("该多项式不为空,求和将覆盖原来的值,确定执行吗?输入0不执行\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                ADDpolyn(P[u-1],P[v-1],P[n-1]);
                printf("此时求和的结果为:\n");
                printpolyn(P[n-1]);
                break;
            case 5:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求差的两式序号,先输入的减去后输入的,输入0退出:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u>N||u<1||v>N||v<1||!P[u-1]||!P[v-1]){
                    printf("\n输入错误!\n");
                    break;
                }
                printf("输入求差结果存储地序号:\n");
                scanf("%d",&n);
                if (n>N||n<1){
                    printf("\n输入错误!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("请不要这样先生!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("此时求差的存储地多项式不为空,求差将覆盖原来的值,确定执行吗？输入0不执行\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                Subpolyn(P[u-1],P[v-1],P[n-1]);
                printf("此时求差的结果为:\n");
                printpolyn(P[n-1]);
                break;
            case 6:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d号多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("\n输入需求值的多项式序号,为0退出:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1||!P[n-1]){
                    printf("\n输入错误\n");
                    break;
                }
                printf("\n输入自变量的值\n");
                scanf("%lf",&x);
                printf("所求的值为%lf",Value(P[n-1],x));
                break;
            case 7:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("\n输入需要销毁的多项式的序号,为0退出:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1){
                    printf("\n输入错误!\n");
                    break;
                }
                DestroyPolyn(P[n-1]);
                break;
            case 8:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("\n输入需要清空的多项式序号,为0退出\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1){
                    printf("\n输入错误\n");
                    break;
                }
                ClearPolyn(P[n-1]);
                break;
            case 9:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("\n输入需要修改的多项式的序号,为0退出:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1||!P[n-1]){
                    printf("\n输入错误\n");
                    break;
                }
                for (;;){
//                    system("cls");
                    printpolyn(P[n-1]);
                    printf("\n输入需要修改方式前的序号:\n");
                    printf("______________________\n");
                    printf("|0.退出              |\n");
                    printf("|1.增加或减少某项的值|\n");
                    printf("|2.删除某些项        |\n");
                    printf("|____________________|\n");
                    scanf("%d",&j);
                    if (j==0) break;
                    switch (j){
                        case 1:
                            printf("\n输入需修改的项的幂:\n");
                            scanf("%d",&b);
                            printf("\n输入需该幂次需增加或减少的系数:\n");
                            scanf("%f",&a);
                            OrderInsert(P[n-1],a,b);
                            break;
                        case 2:
                            printf("\n输入需删除的项的幂\n");
                            scanf("%d",&m);
                            DeletePolyn(P[n-1],m);
                            break;
                    }
                }
                break;
            case 10:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求积的多项式的序号,为0退出:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u<1||u>N||v<1||v>N||!P[u-1]||!P[v-1]) {
                    printf("输入错误!\n");
                    break;
                }
                printf("输入积的存储地的序号,为0退出\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("输入错误!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("请不要这样先生!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("存储地的多项式不为空,确定继续吗，输入0退出:\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                MultiPolyn(P[u-1],P[v-1],P[n-1]);
                printf("此时的多项式的积为:\n");
                printpolyn(P[n-1]);
                break;
            case 11:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求商的多项式的序号,先输入的除以后输入的,为0退出:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u<1||u>N||v<1||v>N||!P[u-1]||!P[v-1]||!P[v-1]->next) {
                    printf("输入错误!\n");
                    break;
                }
                printf("输入商的存储地的序号,为0退出\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("输入错误!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("请不要这样先生!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("存储地的多项式不为空,确定继续吗,输入0退出:\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                printf("输入余数的存储地序号,为0退出:\n");
                scanf("%d",&m);
                if (P[m-1]&&(P[m-1]->next)){
                    printf("存储地的多项式不为空,确认继续吗,输入0退出:\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[n-1]);
                InitPolyn(P[m-1]);
                DiviPolyn(P[u-1],P[v-1],P[n-1],P[m-1]);
                printf("此时的多项式的商为:\n");
                printpolyn(P[n-1]);
                printf("此时的多项式的余数为:\n");
                printpolyn(P[m-1]);
                break;
            case 12:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求导的多项式序号,为0退出:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("输入错误!\n");
                    break;
                }
                if (!P[n-1]||!(P[n-1]->next)){
                    printf("所选择的多项式不可求导!\n");
                    break;
                }
                printf("输入求导的结果存储地,为0退出:\n");
                scanf("%d",&m);
                if (m==0) break;
                if (m>N||m<1){
                    printf("输入错误!\n");
                    break;
                }
                if (m==n){
                    printf("请不要这样先生!\n");
                    break;
                }
                if (P[m-1]&&(P[m-1]->next)){
                    printf("所选择的存储地不为空,确定将覆盖原来的结果,确认继续吗?输入0退出\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[m-1]);
                DiffPolyn(P[n-1],P[m-1]);
                break;
            case 13:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n第%d个多项式为:\n",j+1);
                    if (!P[j]) printf("未创建该多项式!\n");
                    else printpolyn(P[j]);
                }
                printf("输入需求积分的多项式的序号,为0退出:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("输入错误!\n");
                    break;
                }
                if (!P[n-1]||!(P[n-1])){
                    printf("输入的多项式不可求积分!\n");
                    break;
                }
                printf("输入求积分的结果存储地,为0退出:\n");
                scanf("%d",&m);
                if (m==0) break;
                if (m<1||m>N){
                    printf("输入错误!\n");
                    break;
                }
                if (m==n) {
                    printf("请不要这样先生!\n");
                    break;
                }
                if (P[m-1]&&(P[m-1]->next)){
                    printf("所选择的存储地不为空,确定将覆盖原来的结果,确认继续吗?输入0退出\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[m-1]);
                IntePolyn(P[n-1],P[m-1]);
                break;
        }
    }
}
