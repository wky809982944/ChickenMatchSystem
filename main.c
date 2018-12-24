#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define ElemType Player
#define Status int
#define ERROR 0
#define OK 1

/*玩家结构体*/
typedef struct Player {
    long long ID;
    char password[20];
    int Rank;
    double KD;
    int kill;
    int death;
    int Chicken;
    int all;
    int Competence;
} Player;
/*
链表节点
*/
Player player[100];
typedef struct LinkNode {
    //数据域
    ElemType data;
    //指针域
    struct LinkNode *next;
} LinkNode;
/*定义LinkList*/
typedef struct LinkNode *LinkList;

LinkList LoginPlayer;
void AdministratorMenu(LinkList L);
void showMenu(LinkList L);
/*
单链表的读取
*/
Status GetElem(LinkList *L, long long i, ElemType *e) {
    int j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*j为计数器*/
    j = 0;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next && j < i) {
        /*让p指向下一个节点*/
        p = p->next;
        ++j;
    }
    /*第i个节点不存在*/
    if (!p || j > i)
        return ERROR;
    /*取第i个节点的数据*/
    *e = p->data;
    return OK;
}

/*
根据K/D执行单链表的查找
*/
void LinkSearchbyKD(LinkList *L, double key) {
    int j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next) {
        if (p->data.KD == key){
            printf("\t\t玩家ID:%lld\n", p->data.ID);
            printf("\t\t玩家Rank:%d\n",  p->data.Rank);
            printf("\t\t玩家K/D:%.3lf\n",  p->data.KD);
            printf("\t\t玩家Chicken:%%%d\n",  p->data.Chicken);
        }
        /*让p指向下一个节点*/
        p = p->next;

    }
}

/*
根据Rank执行单链表的查找
*/
void LinkSearchbyRank(LinkList *L,int key) {
    int j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next) {
        if (p->data.Rank == key){
            printf("\t\t玩家ID:%lld\n", p->data.ID);
            printf("\t\t玩家Rank:%d\n",  p->data.Rank);
            printf("\t\t玩家K/D:%.3lf\n",  p->data.KD);
            printf("\t\t玩家Chicken:%%%d\n",  p->data.Chicken);
        }
        /*让p指向下一个节点*/
        p = p->next;

    }
}
/*
根据ID进行单链表的查找
*/
Status LinkSearch(LinkList *L, ElemType *e, long long key) {
    int j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next && p->data.ID != key) {
        /*让p指向下一个节点*/
        p = p->next;
    }
    /*第i个节点不存在*/
    if (!p)
        return 0;
    if (p->data.ID == key)
        *e = p->data;
    return 1;
}
/*
单链表的读取返回节点指针
*/
LinkList GetElemNode(LinkList *L, long long i) {
    int j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*j为计数器*/
    j = 0;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next && j < i) {
        /*让p指向下一个节点*/
        p = p->next;
        ++j;
    }
    /*第i个节点不存在*/
    if (!p || j > i)
        return ERROR;
    return p;
}
/*
单链表的读取按ID
*/
LinkList GetElemNodebyID(LinkList *L, long long ID) {
    long long j;
    /*声明一指针p*/
    LinkList p;
    /*让p指向链表L的第一个节点*/
    p = *L;
    /*j为计数器*/
    j = 0;
    /*p不为空且计数器j还没有等于i时，循环继续*/
    while (p->next && j !=ID) {
        /*让p指向下一个节点*/
        p = p->next;
        ++j;
    }
    /*第i个节点不存在*/
    if (!p)
        return ERROR;
    return p;
}

/*
单链表在末尾插入
*/
Status ListInsert(LinkList *L, ElemType e) {
    LinkList p, s;
    p = *L;
    while (p->next) {
        p = p->next;
    }

    /*生成新节点*/
    s = (LinkList) malloc(sizeof(LinkNode));
    s->data = e;
    /*将p的后继节点赋值给s的后继*/
    s->next = p->next;
    /*将s赋值给p的后继*/
    p->next = s;
    return OK;
}
/*
单链表按位置插入
*/
Status ListInsertNumber(LinkList *L, int i, ElemType e) {
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    /*寻找第i-1个节点*/
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    /*第i个节点不存在*/
    if (!p || j > i)
        return ERROR;
    /*生成新节点*/
    s = (LinkList) malloc(sizeof(LinkNode));
    s->data = e;
    /*将p的后继节点赋值给s的后继*/
    s->next = p->next;
    /*将s赋值给p的后继*/
    p->next = s;
    return OK;
}
/*
单链表的删除
*/
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    /*遍历寻找第i-1个节点*/
    while (p->next && j < i) {
        p = p->next;
        ++j;
    }
    /*第i个节点不存在*/
    if (!(p->next) || j > i)
        return ERROR;
    q = p->next;
    /*将q的后继赋给p的后继*/
    p->next = q->next;
    /*将q节点中的数据给p的后继*/
    *e = q->data;
    /*让系统回收此节点，释放内存*/
    free(q);
    return OK;
}

/*
单链表的删除按ID
*/
Status ListDeletebyID(LinkList *L,long long id){
    LinkList p, q;
    p = *L;
    /*遍历寻找第i-1个节点*/
    while (p->next && id!=p->next->data.ID) {
        p = p->next;
    }
    /*第i个节点不存在*/
    if (!(p->next))
        return ERROR;
    /*将q的后继赋给p的后继*/
    q = p->next;
    /*将q节点中的数据给p的后继*/
    p->next = q->next;
    /*让系统回收此节点，释放内存*/
    free(q);
}

/*
单链表的创建
*/
void CreativeListHead(LinkList L) {
    L = (LinkList) malloc(sizeof(LinkNode));
    L->next = NULL;
    /*LinkList p;
    player[1].ID = 1;
    player[1].Rank = 300;
    player[1].KD = 3.1;
    player[1].Chicken =25;
    player[2].ID = 2;
    player[2].Rank = 520;
    player[2].KD = 4;
    player[2].Chicken = 11;
    player[3].ID = 3;
    player[3].Rank = 1200;
    player[3].KD = 0.2;
    player[3].Chicken = 2;
    char pass[20] = "123456";
    strcpy(player[3].password, pass);
    player[4].ID = 4;
    player[4].Rank = 1000;
    player[4].KD = 0.1;
    player[4].Chicken = 8;
    player[5].ID = 6;
    player[5].Rank = 12;
    player[5].KD = 3.1;
    player[5].Chicken = 1;

    int i;
    for (i = 1; i <= 5; i++) {
        p = (LinkList) malloc(sizeof(LinkNode));
        p->next=NULL;
        p->data = player[i];
        p->next = L->next;
        L->next = p;
    }*/
}

/*
单链表的遍历
*/
void LinklistPrint(LinkList *L) {
    if (L == NULL) {
        //空链表无需打印
        return;
    }
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL) {
        //打印元素和其对应的地址
        printf("\t\t玩家ID:%lld\n", p->data.ID);
        printf("\t\t玩家Rank:%d\n", p->data.Rank);
        printf("\t\t玩家K/D:%.1lf\n", p->data.KD);
        printf("\t\t玩家吃鸡率:%%%d\n", p->data.Chicken);
        //移动cur,以达到遍历链表的目的
        p = p->next;
    }
    printf("\n\n");

}

/*
单链表的数量
*/
int getNum(LinkList *L) {
    int Num = 0;
    if (L == NULL) {
        //空链表个数为0
        return 0;
    }
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL) {
        //自增
        Num++;
        //移动cur,以达到遍历链表的目的
        p = p->next;
    }
    return Num;
}

/*
 单链表寻找链表的前驱
 */
LinkList findPre(LinkList *L, LinkList node) {
    LinkList p = *L;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}

/*
 * 根据两个节点的前驱，交换两个节点
 * 需要考虑的情况有：
 * 1.如果节点1和节点2相同，不需要交换
 * 2.如果其中一个节点为头节点，原则上不交换
 * 3.如果两个节点相邻，需要做一些特殊处理。
 * 4.其他情况下只需要找到节点的前驱，然后做相应的指针的调整。
 **/
void doExchange(LinkList L, LinkList node1, LinkList node2) {

    LinkList prenode1 = NULL;  //待交换节点node1的前一个节点
    LinkList postnode1 = NULL; //待交换节点node1的后一个节点
    LinkList prenode2 = NULL;  //待交换节点node2的前一个节点
    LinkList postnode2 = NULL; //待交换节点node2的后一个节点

    //头节点不交换
    if (node1 == L || node2 == L) {
        return;
    }

    //相同不需交换
    if (node1 == node2) {
        return;
    }

    prenode1 = findPre(L, node1);
    prenode2 = findPre(L, node2);
    postnode1 = node1->next;
    postnode2 = node2->next;

    //节点相邻情况处理
    if (postnode1 == node2) {
        prenode1->next = node2;
        node2->next = node1;
        node1->next = postnode2;
        return;
    }

    if (postnode2 == node1) {
        prenode2->next = node1;
        node1->next = node2;
        node2->next = postnode1;
        return;
    }

    //其他情况下，直接交换节点
    prenode1->next = node2;
    node2->next = postnode1;
    prenode2->next = node1;
    node1->next = postnode2;
}

/*
 * 链表交换按位置
 */
void Exchange(LinkList L, int i, int j) {
    doExchange(L, GetElemNode(L, i), GetElemNode(L, j));
}

/*
文件从链表写入
*/
int FileWrite(LinkList *L) {

    int num = 0;
    FILE *fp = fopen("C:\\Users\\ROG\\Desktop\\ChickenMatchSystem\\PlayerList.txt", "w+");
    /*if (fp == NULL) {
        printf("找不到用户信息");
        exit(1);
    }*/
    if (L == NULL) {
        //空链表无需写入
        return 0;
    }

    LinkList p = *L;
    p = p->next;
    while (p != NULL) {
        fwrite(p, sizeof(LinkNode), 1, fp);
        p = p->next;
        num++;
    }
    fclose(fp);
    return num;

}

/*
文件读取到链表
*/
int FileRead(LinkList *L) {
    int num = 0;
    FILE *fp = fopen("C:\\Users\\ROG\\Desktop\\ChickenMatchSystem\\PlayerList.txt", "r");
    if (fp == NULL) {
        printf("找不到用户信息");
        exit(1);
    }
    LinkList p = *L, pTemp;
    while (1) {
        pTemp = (LinkList) malloc(sizeof(LinkNode));
        pTemp->next = NULL;
        /*这里用一个中间结点，临时储存，fread读一次才能决定是否添加结点，直接用p添加结点会错误，本身就是空文件时会多出一个结点，存的垃圾值，而fread必须有一块内存才能读*/
        if ((fread(pTemp, sizeof(LinkNode), 1, fp)) != 0) {
            p->next = pTemp;
            p = p->next;
            num++;
        } else
            break;
    }
    p->next = NULL;
    free(pTemp);
    fclose(fp);
    return num;

}
/*
 * 初始化链表
 */
void Initiate(LinkNode **head)
{
    (*head)=(LinkNode*)malloc(sizeof(LinkNode));
    (*head)->next=NULL;
}
/*
 * 找到头结点
 */
LinkList GetFirstNode(LinkList *head)
{
    if(head==NULL)
    return NULL;
    else
    {
        LinkList p;
        p=*head;
        p=p->next;
        (*head)->next=p->next;
        return p;
    }
}

/*
 * 添加节点
 */
void AppendNode(LinkList head,LinkList node)
{
    if(head==NULL) return;
    else
    {
        LinkList p;
        p=head;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=node;
        node->next=NULL;
    }
}

/*
 * 重新生成链表
 */
void Total(LinkList L,LinkList head)
{
    LinkList p;
    p=L;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=head->next;
}

/*
 * 返回int类型的a^n
 */
int Power(int a,int n)
{
    int y;
    if(n==0)
        return 1;
    else
    {
        y=Power(a,n/2);
        y=y*y;
        if(n%2==1)
            y=y*a;
    }
    return y;
}

/*
 * 获得每一位的数字
 */
long long GetNum(LinkList p,int i,int k)
{
    long long data;
    switch (k){
        case 1:
            data=p->data.Rank;
            break;
        case 2:
            data=p->data.Chicken;
            break;
        case 3:
            data=p->data.ID;
    }
    long long  a;
    i--;
    a=data/Power(10,i);
    return a%10;
}

/*
 * 基于链表的基数排序
 * 第二个形参表示参加排序的整数最大位数一共有count位数字
 */
void radix_sort(LinkList *head,int count,int kind)
{
    LinkList p[10],q;
    long long i,j,k;

    for(j=1;j<=count;j++)
    {
        //十个头结点初始化
        for(i=0;i<10;i++)
        {
            Initiate(&p[i]);
        }
        //链表从头到尾扫描，并将扫描到的节点脱离链表。
        while((*head)->next!=NULL)
        {
            q=GetFirstNode(head);

            k=GetNum(q,j,kind); //取得链表节点第j位的元素值k
            AppendNode(p[k],q);
            //将该节点连接到10个链表相应的位置
        }
        //将10个链表从0-9依次连接到head节点后面
        for(i=0;i<10;i++)
        {
            Total(*head,p[i]);
        }
    }

    for(i=0;i<10;i++)
    {
        free(p[i]);
    }


}

/*
 * 基于链表的冒泡排序
 */
void bubble_sort(LinkList L, int s) {
    int i, j, k, temp;
    int num = getNum(L);
    switch (s) {
        case 1: {
            Player p1;
            Player p2;
            for (i = 1; i <= num; i++) {
                for (j = i + 1; j <= num; j++) {

                    GetElem(L, i, &p1);
                    GetElem(L, j, &p2);
                    if (p1.Rank < p2.Rank) {

                        Exchange(L, i, j);
                    }
                }
            }
        }
            break;
        case 2: {
            Player p1;
            Player p2;
            for (i = 1; i <= num; i++) {
                for (j = i + 1; j <= num; j++) {

                    GetElem(L, i, &p1);
                    GetElem(L, j, &p2);
                    if (p1.KD < p2.KD) {

                        Exchange(L, i, j);
                    }
                }
            }
        }

            break;
        case 3: {
            Player p1;
            Player p2;
            for (i = 1; i <= num; i++) {
                for (j = i + 1; j <= num; j++) {

                    GetElem(L, i, &p1);
                    GetElem(L, j, &p2);
                    if (p1.Chicken < p2.Chicken) {

                        Exchange(L, i, j);
                    }
                }
            }
        }
            break;

    }

}
/*
 * 游戏地图
 */
void Map(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 4;
    switch (n){
        case 1:{
            printf("\t\t您降落到了艾伦格机场\n");
        }
            break;
        case 2:{
            printf("\t\t您降落到了米拉玛\n");
        }
            break;
        case 3:{
            printf("\t\t您降落到了萨诺\n");
        }
            break;
        case 4:{
            printf("\t\t您降落到了维寒迪\n");
        }
            break;
    }
}
/*
 * 枪械
 */
void Gun(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 11;
    switch (n){
        case 1:{
            printf("\t\t您捡到了M416\n");
        }
            break;
        case 2:{
            printf("\t\t您捡到了Scar\n");
        }
            break;
        case 3:{
            printf("\t\t您捡到了SKS(29杀神器)\n");
        }
            break;
        case 4:{
            printf("\t\t您捡到了Kar98\n");
        }
            break;
        case 5:{
            printf("\t\t您捡到了M16\n");
        }
            break;
        case 6:{
            printf("\t\t您捡到了P18c\n");
        }
            break;
        case 7:{
            printf("\t\t您捡到了VSS\n");
        }
            break;
        case 8:{
            printf("\t\t您捡到了平底锅\n");
        }
            break;
        case 9:{
            printf("\t\t您捡到了AKM\n");
        }
            break;
        case 10:{
            printf("\t\t您捡到了AWM\n");
        }
            break;
        case 11:{
            printf("\t\t您捡到了S686\n");
        }
            break;
    }
}
/*
 * 遭遇敌人
 */
double Army(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 12;
    switch (n){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:{
            printf("\t\t您击杀了一名敌人\n");
            return 1;
        }
        case 6:{
            printf("\t\t您开车跑了\n");
            return -1;
        }
        case 7:
        case 8:{
            printf("\t\t您被毒死了\n");
            return -1;
        }
        case 9:
        case 10:
        case 11:
        case 12:{
            printf("\t\t您被击杀了\n");
            return -1;
        }
    }
}
/*
 * 防具
 */
void Armor(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 11;
    switch (n){
        case 1:{
            printf("\t\t您捡到了一级甲\n");
        }
            break;
        case 2:{
            printf("\t\t您捡到了二级甲\n");
        }
            break;
        case 3:{
            printf("\t\t您捡到了三级甲\n");
        }
            break;
        case 4:{
            printf("\t\t您捡到了原谅脑壳\n");
        }
            break;
        case 5:{
            printf("\t\t您捡到了二级头\n");
        }
            break;
        case 6:{
            printf("\t\t您捡到了三级头\n");
        }
            break;
        case 7:{
            printf("\t\t您捡到了绷带\n");
        }
            break;
        case 8:{
            printf("\t\t您捡到了急救包\n");
        }
            break;
        case 9:{
            printf("\t\t您捡到了能量饮料\n");
        }
            break;
        case 10:{
            printf("\t\t您捡到了肾上腺素\n");
        }
            break;
        case 11:{
            printf("\t\t您捡到了医疗箱\n");
        }
            break;
    }
}

/*
 * 添加机器人
 */
int addRobot(LinkList *L,int num){
    int i;
    int n=0;
    srand( (unsigned)time( NULL ) );
    for(i=1;i<=num;i++){
        ElemType e;
        e.ID=rand() % 1000;
        e.Rank=rand()%5000;
        e.KD=(rand()%100)*0.1;
        e.Chicken=rand()%100;
        ListInsert(L,e);
        n++;
    }
    return n;
}

/*
 * 吃鸡匹配
 */
void ChickenMatch(LinkList *L){
    int i=0;
    int alive=1;
    double kill=0;
    int Rank=100;
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL&&i<10) {
        if(abs(LoginPlayer->data.Rank-p->data.Rank)<300)
        {
            i++;
            //打印元素和其对应的地址
            printf("\t\t已找到匹配玩家%d号\n",i);
            printf("\t\t玩家ID:%lld\n", p->data.ID);
            printf("\t\t玩家Rank:%d\n", p->data.Rank);
            printf("\t\t玩家K/D:%.3lf\n", p->data.KD);
            printf("\t\t玩家吃鸡率:%%%d\n", p->data.Chicken);
        }

        //移动p,以达到遍历链表的目的
        p = p->next;
    }
    printf("\t\t游戏开始\n\n\n\n");
    Map();
    srand( (unsigned)time( NULL ) );
    for (i = 0; i < 4; i++) {
        int k=rand()%10;
        switch (k){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            {
                int x=Army();
                if(x==-1){
                    alive=0;
                    goto here;
                }
                kill+=x;
            }
                break;
            case 6:
            case 7:
            case 8:
            {
                Gun();
            }
                break;
            case 9:
            case 10:
            case 11:
            {
                Armor();
            }
                break;
        }
        Rank-=25;
    }
    if(alive){
        printf("\t\t本局游戏您一共击杀%.0lf\n",kill);
        printf("\t\t大吉大利今晚吃鸡\n");
        LinkList p;
        p = (LinkList) malloc(sizeof(LinkNode));
        p=GetElemNode(L,LoginPlayer->data.ID);
        LoginPlayer->data.Rank+=25;
        LoginPlayer->data.KD+=kill/(1+LoginPlayer->data.KD);
        LoginPlayer->data.Chicken++;
        p->data=LoginPlayer->data;
    }
    if(!alive)
    {
        here:
        printf("\t\t本局游戏您一共击杀%.0lf\n",kill);
        printf("\t\t再接再厉下次吃鸡\n");
        LinkList p;
        p = (LinkList) malloc(sizeof(LinkNode));
        p=GetElemNode(L,LoginPlayer->data.ID);
        switch (Rank){
            case 100:
            {
                LoginPlayer->data.Rank-=30;
            }
                break;
            case 75:
            {
                LoginPlayer->data.Rank-=20;
            }
                break;
            case 50:
            {
                LoginPlayer->data.Rank-=10;
            }
                break;
            case 25:{
                LoginPlayer->data.Rank+=10;
            }
                break;
        }
        LoginPlayer->data.KD-=kill/(1+LoginPlayer->data.KD);
        LoginPlayer->data.Chicken--;
        p->data=LoginPlayer->data;
    }
    printf("\t\t游戏结束\n");
    int number;
    printf("\t\t1.返回上一级主界面\n");
    printf("\t\t0.退出\n");
    scanf("%d",&number);
    switch (number){
        case 1:{
            AdministratorMenu(L);
        }
            break;
        case 0:{
            exit(0);
        }
    }
    printf("\n\n");

}
/*
 * 二分查找
 */
long long binarySearch(LinkList L, int kind, int key) {
    long long low = 0;
    long long high = getNum(L) - 1;
    switch (kind) {
        case 1: {
            radix_sort(L, 10,1);
            while (low <= high) {
                long long mid = (low + high) / 2;
                ElemType midVal;
                GetElem(L, mid, &midVal);
                if (midVal.Rank < key)
                    low = mid + 1;
                else if (midVal.Rank > key)
                    high = mid - 1;
                else
                    return mid;
            }
            return -1;
        }
            break;
        case 2: {
            bubble_sort(L,2);
            while (low <= high) {
                long long mid = (low + high) / 2;
                ElemType midVal;
                GetElem(L, mid, &midVal);
                if (midVal.KD < key)
                    low = mid + 1;
                else if (midVal.KD > key)
                    high = mid - 1;
                else
                    return mid;
            }
            return -1;
        }
            break;
        case 3: {
            while (low <= high) {
                radix_sort(L, 10,2);
                long long mid = (low + high) / 2;
                ElemType midVal;
                GetElem(L, mid, &midVal);
                if (midVal.Chicken < key)
                    low = mid + 1;
                else if (midVal.Chicken > key)
                    high = mid - 1;
                else
                    return mid;
            }
            return -1;
        }
            break;
        case 4:{
            radix_sort(L, 10,3);
            while (low <= high) {
                long long mid = (low + high) / 2;
                ElemType midVal;
                GetElem(L, mid, &midVal);
                if (midVal.ID < key)
                    low = mid + 1;
                else if (midVal.ID > key)
                    high = mid - 1;
                else
                    return mid;
            }
            return -1;
        }
            break;
    }

}

/*
管理员菜单
*/
void AdministratorMenu(LinkList L){
    int number;
    printf("***************************************\n");
    printf("          吃鸡匹配系统管理员菜单模块        \n");
    printf("***************************************\n");
    printf("\t\t1.按玩家ID查询\n");
    printf("\t\t2.按玩家总评分查询\n");
    printf("\t\t3.按玩家K/D查询功能\n");
    printf("\t\t4.玩家匹配\n");
    printf("\t\t5.新增玩家信息\n");
    printf("\t\t6.删除玩家信息\n");
    printf("\t\t7.查看所有玩家信息\n");
    printf("\t\t8.批量添加机器人\n");
    printf("\t\t9.保存到文件后退出匹配系统\n");
    printf("\t\t0.退出匹配系统\n");
    printf("******************END******************\n");
    scanf("%d", &number);
    switch (number) {
        case 1: {
            long long ID;
            ElemType e;
            printf("\t\t请输入玩家ID\n");
            scanf("%lld", &ID);
            binarySearch(L,4,ID);
            GetElem(L,ID,&e);
            printf("\t玩家ID:%lld\n", e.ID);
            printf("\t玩家Rank:%d\n", e.Rank);
            printf("\t玩家K/D:%.3lf\n", e.KD);
            printf("\t玩家吃鸡率:%d\n", e.Chicken);
            int number;
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d",&number);
            switch (number){
                case 1:{
                    AdministratorMenu(L);
                }
                    break;
                case 2:{
                    FileWrite(L);
                }
                    break;
                case 0:{
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
        }
            break;

        case 2:{
            int Rank;
            ElemType e;
            printf("\t\t请输入玩家Rank\n");
            scanf("%lld", &Rank);
            binarySearch(L,1,Rank);
            GetElem(L,Rank,&e);
            printf("\t玩家ID:%lld\n", e.ID);
            printf("\t玩家Rank:%d\n", e.Rank);
            printf("\t玩家K/D:%.3lf\n", e.KD);
            printf("\t玩家吃鸡率:%d\n", e.Chicken);
            int number;
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d",&number);
            switch (number){
                case 1:{
                    AdministratorMenu(L);
                }
                    break;
                case 2:{
                    FileWrite(L);
                }
                    break;
                case 0:{
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
        }
            break;
        case 3:{
            int KD;
            ElemType e;
            printf("\t\t请输入玩家K/D\n");
            scanf("%lld", &KD);
            binarySearch(L,2,KD);
            GetElem(L,KD,&e);
            printf("\t玩家ID:%lld\n", e.ID);
            printf("\t玩家Rank:%d\n", e.Rank);
            printf("\t玩家K/D:%.3lf\n", e.KD);
            printf("\t玩家吃鸡率:%d\n", e.Chicken);
            int number;
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d", &number);
            switch (number) {
                case 1: {
                    AdministratorMenu(L);
                }
                    break;
                case 2: {
                    FileWrite(L);
                }
                    break;
                case 0: {
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
        }
            break;
        case 4:{
            ChickenMatch(L);
            int number;
            printf("\t\t1.返回上一级主界面\n");
            printf("\t\t0.退出\n");
            scanf("%d",&number);
            switch (number){
                case 1:{
                    AdministratorMenu(L);
                }
                    break;
                case 0:{
                    exit(0);
                }
            }

        }
            break;
        case 5:{
            ElemType e;
            char password[20];
            printf("\t\t请输入玩家ID\n");
            scanf("%lld",&e.ID);
            printf("\t\t请输入玩家密码\n");
            scanf("%s",password);
            strcpy(e.password,password);
            printf("\t\t请输入玩家Rank\n");
            scanf("%d",&e.Rank);
            printf("\t\t请输入玩家K/D\n");
            scanf("%lf",&e.KD);
            printf("\t\t请输入玩家吃鸡概率\n");
            scanf("%d",&e.Chicken);
            ListInsert(L,e);
            printf("\t\t玩家ID%lld创建成功\n",e.ID);

        }
            break;
        case 6: {
            long long ID;
            printf("\t\t请输入玩家ID\n");
            scanf("%lld", &ID);
            ListDeletebyID(L, ID);
            printf("\t\t玩家ID%lld删除成功\n", ID);
            int number;
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d", &number);
            switch (number) {
                case 1: {
                    AdministratorMenu(L);
                }
                    break;
                case 2: {
                    FileWrite(L);
                }
                    break;
                case 0: {
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
        }
            break;
        case 7: {
            int number;
            LinklistPrint(L);
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d", &number);
            switch (number) {
                case 1: {
                    AdministratorMenu(L);
                }
                    break;
                case 2: {
                    FileWrite(L);
                }
                    break;
                case 0: {
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
        }
            break;
        case 8:{
            int num;
            printf("\t\t请输入添加机器人的数量\n");
            scanf("%d",&num);
            int n;
            n=addRobot(L,num);
            printf("\t\t成功添加%d个机器人\n",n);
            int number;
            printf("\t\t1.返回上一级菜单\n");
            printf("\t\t2.保存到文件后退出\n");
            printf("\t\t0.直接退出\n");
            scanf("%d",&number);
            switch (number){
                case 1:{
                    AdministratorMenu(L);
                }
                    break;
                case 2:{
                    FileWrite(L);
                }
                    break;
                case 0:{
                    exit(0);
                }
                default:
                    printf("\t\t输入错误，请重新输入：\n");
            }
    }
            break;
        case 9:{
            FileWrite(L);
        }
            break;
}
}

/*
注册菜单
*/
void RegisterMenu(LinkList L) {
    long long ID;
    ElemType check;
    char pass1[20];
    char pass2[20];
    printf("***************************************\n");
    printf("           欢迎使用吃鸡匹配系统注册模块        \n");
    printf("***************************************\n");
    printf("\t\t请输入你要注册的ID（数字）\n");
    scanf("%lld", &ID);
    LinkSearch(L,&check,ID);
    if(ID==check.ID){
        printf("\t\t用户名已存在，请重新注册\n");
        RegisterMenu(L);
    }
    printf("\t\t请输入你的密码\n");
    scanf("%s", pass1);
    printf("\t\t请再次输入你的密码\n");
    scanf("%s", pass2);
    if (strcmp(pass1, pass2) == 0) {
        ElemType e;
        e.ID = ID;
        e.Chicken = 0;
        e.KD = 0;
        e.Rank = 800;
        e.Competence = 1;
        strcpy(e.password, pass1);
        ListInsert(L, e);
        printf("恭喜玩家");
        printf("%lld", ID);
        printf("注册成功\n");
        sleep(200);
        showMenu(L);
    }
}

/*
登录菜单
*/
void LoginMenu(LinkList L) {
    long long ID;
    char pass[20];
    printf("***************************************\n");
    printf("           欢迎使用吃鸡匹配系统登录模块        \n");
    printf("***************************************\n");
    printf("\t\t请输入你要登录的ID\n");
    scanf("%lld", &ID);
    printf("\t\t请输入你的密码\n");
    scanf("%s", pass);
    ElemType e;
    LinkSearch(L, &e, ID);
    if (strcmp(pass, e.password) == 0) {
        printf("\t\t恭喜玩家");
        printf("%lld\n", ID);
        printf("\t\t登录成功\n");
        LoginPlayer->data=e;
        AdministratorMenu(L);
    } else {
        printf("\t\t登录失败");
        printf("\t\t请重新输入ID和密码");
        sleep(300);
        LoginMenu(L);
    }
}

/*
主界面方法
*/
void showMenu(LinkList L) {
    int number;
    printf("***************************************\n");
    printf("           欢迎使用吃鸡匹配系统        \n");
    printf("***************************************\n");
    printf("\t\t1、登录\n");
    printf("\t\t2、注册\n");
    printf("\t\t0、退出\n");
    printf("******************END******************\n");
    scanf("%d", &number);
    switch (number) {
        case 1:
            LoginMenu(L);
            break;
        case 2:
            RegisterMenu(L);
            showMenu(L);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\t\t输入错误，请重新输入：\n");
    }
}
/*
 * 退出函数
 */
void Exit(LinkList L){
    int number;
    printf("\t\t1.返回上一级菜单\n");
    printf("\t\t2.保存到文件后退出\n");
    printf("\t\t0.直接退出\n");
    scanf("%d",&number);
    switch (number){
        case 1:{
            AdministratorMenu(L);
        }
            break;
        case 2:{
            FileWrite(L);
        }
            break;
        case 0:{
            exit(0);
        }
        default:
            printf("\t\t输入错误，请重新输入：\n");
    }
}
int main() {
    LinkList L;
    L = (LinkList) malloc(sizeof(LinkNode));
    CreativeListHead(L);
    FileRead(L);
    ElemType e;
    LoginPlayer = (LinkList) malloc(sizeof(LinkNode));
    showMenu(L);

}
