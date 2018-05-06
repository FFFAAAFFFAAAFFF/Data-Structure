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
    printf("\n��ʱ�Ķ���ʽΪ:");
    if (p==NULL) {
        printf("��!\n");
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
        printf("\n��������ϵ��,Ϊ0�����:");
        scanf("%f",&a);
        if (a==0) break;
        printf("\n�������Ĵ���:");
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
    else printf("\n�ö���ʽ��%d����!\n",n);
}

void Copypolyn(LinkList &La,LinkList Lb){//��Lb������La��
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

void Subpolyn(LinkList La,LinkList Lb,LinkList &Lc){//��La����Lb����Lc��
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

int MaxExpn(LinkList L){//����ʽ��������,���ڸ�������ʽ�ĳ���
    struct polynomial *p=L->next;
    if (p==NULL) return 0;
    while (p->next!=NULL) p=p->next;
    return p->expn;
}

float LastCoef(LinkList L){//����ʽ���һ���ϵ��,���ڸ�������ʽ�ĳ���
    struct polynomial *p=L->next;
    if (p==NULL) return 0;
    while (p->next!=NULL) p=p->next;
    return p->coef;
}

void DiviPolyn(LinkList La,LinkList Lb,LinkList &Lc,LinkList &Ld){//��La����Lb���̷���Lc,��������Ld
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

void DiffPolyn(LinkList La,LinkList &Lb){//��La �󵼺�Ľ������Lb ��
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

void IntePolyn(LinkList La,LinkList &Lb){//��La �������ֺ�Ľ������Lb��, c=0
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
        printf("|�˵�:                             |\n");
        printf("|0.�˳�                            |\n");
        printf("|1.��������ʽ                      |\n");
        printf("|2.��ʾ����ʽ                      |\n");
        printf("|3.���ƶ���ʽ                      |\n");
        printf("|4.���                            |\n");
        printf("|5.���                            |\n");
        printf("|6.��ֵ                            |\n");
        printf("|7.���ٶ���ʽ                      |\n");
        printf("|8.��ն���ʽ                      |\n");
        printf("|9.�޸Ķ���ʽ                      |\n");
        printf("|__________ ����Ϊ������ __________|\n");
        printf("|10.����ʽ�˷�                     |\n");
        printf("|11.����ʽ����                     |\n");
        printf("|12.����ʽ��                     |\n");
        printf("|13.����ʽ����                     |\n");
        printf("|__________________________________|\n");
        scanf("%d",&i);
        switch(i){
            case 0:exit(0);
            case 1:
//                system("cls");
                printf("\n\n����Ҫ��������ʽ�����,��1-10,����0�˳�\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1) {
                    printf("\n�������!\n");
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
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                break;
            case 3:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("���뱻���ƵĶ���ʽ�ı��,Ϊ0�˳�:\n");
                scanf("%d",&u);
                if (u==0) break;
                if (u>N||u<1||!P[u-1]){
                    printf("\n�������!\n");
                    break;
                }
                printf("������Ҫ�������Ķ���ʽ���,Ϊ0�˳�\n");
                scanf("%d",&v);
                if (v==0) break;
                if (v>N||v<1){
                    printf("\n�������!\n");
                    break;
                }
                if (u==v) break;
                if (P[v-1]&&(P[v-1]->next)){
                    printf("�������Ķ���ʽ�洢�ز�Ϊ��,ȷ��������?����0�˳�\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[v-1]);
                Copypolyn(P[v-1],P[u-1]);
                break;
            case 4:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("��������͵���ʽ���,�����κ�һ��Ϊ0�˳�:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u>N||u<1||v>N||v<1||!P[v-1]||!P[u-1]){
                    printf("\n�������!\n");
                    break;
                }
                printf("������ͽ���洢�����:\n");
                scanf("%d",&n);
                if (n==u||n==v){
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (n>N||n<1){
                    printf("\n�������!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("�ö���ʽ��Ϊ��,��ͽ�����ԭ����ֵ,ȷ��ִ����?����0��ִ��\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                ADDpolyn(P[u-1],P[v-1],P[n-1]);
                printf("��ʱ��͵Ľ��Ϊ:\n");
                printpolyn(P[n-1]);
                break;
            case 5:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("������������ʽ���,������ļ�ȥ�������,����0�˳�:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u>N||u<1||v>N||v<1||!P[u-1]||!P[v-1]){
                    printf("\n�������!\n");
                    break;
                }
                printf("����������洢�����:\n");
                scanf("%d",&n);
                if (n>N||n<1){
                    printf("\n�������!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("��ʱ���Ĵ洢�ض���ʽ��Ϊ��,������ԭ����ֵ,ȷ��ִ��������0��ִ��\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                Subpolyn(P[u-1],P[v-1],P[n-1]);
                printf("��ʱ���Ľ��Ϊ:\n");
                printpolyn(P[n-1]);
                break;
            case 6:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d�Ŷ���ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("\n��������ֵ�Ķ���ʽ���,Ϊ0�˳�:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1||!P[n-1]){
                    printf("\n�������\n");
                    break;
                }
                printf("\n�����Ա�����ֵ\n");
                scanf("%lf",&x);
                printf("�����ֵΪ%lf",Value(P[n-1],x));
                break;
            case 7:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("\n������Ҫ���ٵĶ���ʽ�����,Ϊ0�˳�:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1){
                    printf("\n�������!\n");
                    break;
                }
                DestroyPolyn(P[n-1]);
                break;
            case 8:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("\n������Ҫ��յĶ���ʽ���,Ϊ0�˳�\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1){
                    printf("\n�������\n");
                    break;
                }
                ClearPolyn(P[n-1]);
                break;
            case 9:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("\n������Ҫ�޸ĵĶ���ʽ�����,Ϊ0�˳�:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n>N||n<1||!P[n-1]){
                    printf("\n�������\n");
                    break;
                }
                for (;;){
//                    system("cls");
                    printpolyn(P[n-1]);
                    printf("\n������Ҫ�޸ķ�ʽǰ�����:\n");
                    printf("______________________\n");
                    printf("|0.�˳�              |\n");
                    printf("|1.���ӻ����ĳ���ֵ|\n");
                    printf("|2.ɾ��ĳЩ��        |\n");
                    printf("|____________________|\n");
                    scanf("%d",&j);
                    if (j==0) break;
                    switch (j){
                        case 1:
                            printf("\n�������޸ĵ������:\n");
                            scanf("%d",&b);
                            printf("\n��������ݴ������ӻ���ٵ�ϵ��:\n");
                            scanf("%f",&a);
                            OrderInsert(P[n-1],a,b);
                            break;
                        case 2:
                            printf("\n������ɾ���������\n");
                            scanf("%d",&m);
                            DeletePolyn(P[n-1],m);
                            break;
                    }
                }
                break;
            case 10:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("����������Ķ���ʽ�����,Ϊ0�˳�:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u<1||u>N||v<1||v>N||!P[u-1]||!P[v-1]) {
                    printf("�������!\n");
                    break;
                }
                printf("������Ĵ洢�ص����,Ϊ0�˳�\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("�������!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("�洢�صĶ���ʽ��Ϊ��,ȷ������������0�˳�:\n");
                    scanf("%d",&m);
                    if (m==0) break;
                }
                InitPolyn(P[n-1]);
                MultiPolyn(P[u-1],P[v-1],P[n-1]);
                printf("��ʱ�Ķ���ʽ�Ļ�Ϊ:\n");
                printpolyn(P[n-1]);
                break;
            case 11:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("���������̵Ķ���ʽ�����,������ĳ��Ժ������,Ϊ0�˳�:\n");
                scanf("%d%d",&u,&v);
                if (u*v==0) break;
                if (u<1||u>N||v<1||v>N||!P[u-1]||!P[v-1]||!P[v-1]->next) {
                    printf("�������!\n");
                    break;
                }
                printf("�����̵Ĵ洢�ص����,Ϊ0�˳�\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("�������!\n");
                    break;
                }
                if (n==u||n==v){
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (P[n-1]&&(P[n-1]->next)){
                    printf("�洢�صĶ���ʽ��Ϊ��,ȷ��������,����0�˳�:\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                printf("���������Ĵ洢�����,Ϊ0�˳�:\n");
                scanf("%d",&m);
                if (P[m-1]&&(P[m-1]->next)){
                    printf("�洢�صĶ���ʽ��Ϊ��,ȷ�ϼ�����,����0�˳�:\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[n-1]);
                InitPolyn(P[m-1]);
                DiviPolyn(P[u-1],P[v-1],P[n-1],P[m-1]);
                printf("��ʱ�Ķ���ʽ����Ϊ:\n");
                printpolyn(P[n-1]);
                printf("��ʱ�Ķ���ʽ������Ϊ:\n");
                printpolyn(P[m-1]);
                break;
            case 12:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("�������󵼵Ķ���ʽ���,Ϊ0�˳�:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("�������!\n");
                    break;
                }
                if (!P[n-1]||!(P[n-1]->next)){
                    printf("��ѡ��Ķ���ʽ������!\n");
                    break;
                }
                printf("�����󵼵Ľ���洢��,Ϊ0�˳�:\n");
                scanf("%d",&m);
                if (m==0) break;
                if (m>N||m<1){
                    printf("�������!\n");
                    break;
                }
                if (m==n){
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (P[m-1]&&(P[m-1]->next)){
                    printf("��ѡ��Ĵ洢�ز�Ϊ��,ȷ��������ԭ���Ľ��,ȷ�ϼ�����?����0�˳�\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[m-1]);
                DiffPolyn(P[n-1],P[m-1]);
                break;
            case 13:
//                system("cls");
                for (j=0;j<N;j++){
                    printf("\n��%d������ʽΪ:\n",j+1);
                    if (!P[j]) printf("δ�����ö���ʽ!\n");
                    else printpolyn(P[j]);
                }
                printf("����������ֵĶ���ʽ�����,Ϊ0�˳�:\n");
                scanf("%d",&n);
                if (n==0) break;
                if (n<1||n>N){
                    printf("�������!\n");
                    break;
                }
                if (!P[n-1]||!(P[n-1])){
                    printf("����Ķ���ʽ���������!\n");
                    break;
                }
                printf("��������ֵĽ���洢��,Ϊ0�˳�:\n");
                scanf("%d",&m);
                if (m==0) break;
                if (m<1||m>N){
                    printf("�������!\n");
                    break;
                }
                if (m==n) {
                    printf("�벻Ҫ��������!\n");
                    break;
                }
                if (P[m-1]&&(P[m-1]->next)){
                    printf("��ѡ��Ĵ洢�ز�Ϊ��,ȷ��������ԭ���Ľ��,ȷ�ϼ�����?����0�˳�\n");
                    scanf("%d",&j);
                    if (j==0) break;
                }
                InitPolyn(P[m-1]);
                IntePolyn(P[n-1],P[m-1]);
                break;
        }
    }
}
