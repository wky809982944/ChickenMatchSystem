#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define ElemType Player
#define Status int
#define ERROR 0
#define OK 1

/*��ҽṹ��*/
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
����ڵ�
*/
Player player[100];
typedef struct LinkNode {
    //������
    ElemType data;
    //ָ����
    struct LinkNode *next;
} LinkNode;
/*����LinkList*/
typedef struct LinkNode *LinkList;

LinkList LoginPlayer;
void AdministratorMenu(LinkList L);
void showMenu(LinkList L);
/*
������Ķ�ȡ
*/
Status GetElem(LinkList *L, long long i, ElemType *e) {
    int j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*jΪ������*/
    j = 0;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next && j < i) {
        /*��pָ����һ���ڵ�*/
        p = p->next;
        ++j;
    }
    /*��i���ڵ㲻����*/
    if (!p || j > i)
        return ERROR;
    /*ȡ��i���ڵ������*/
    *e = p->data;
    return OK;
}

/*
����K/Dִ�е�����Ĳ���
*/
void LinkSearchbyKD(LinkList *L, double key) {
    int j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next) {
        if (p->data.KD == key){
            printf("\t\t���ID:%lld\n", p->data.ID);
            printf("\t\t���Rank:%d\n",  p->data.Rank);
            printf("\t\t���K/D:%.3lf\n",  p->data.KD);
            printf("\t\t���Chicken:%%%d\n",  p->data.Chicken);
        }
        /*��pָ����һ���ڵ�*/
        p = p->next;

    }
}

/*
����Rankִ�е�����Ĳ���
*/
void LinkSearchbyRank(LinkList *L,int key) {
    int j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next) {
        if (p->data.Rank == key){
            printf("\t\t���ID:%lld\n", p->data.ID);
            printf("\t\t���Rank:%d\n",  p->data.Rank);
            printf("\t\t���K/D:%.3lf\n",  p->data.KD);
            printf("\t\t���Chicken:%%%d\n",  p->data.Chicken);
        }
        /*��pָ����һ���ڵ�*/
        p = p->next;

    }
}
/*
����ID���е�����Ĳ���
*/
Status LinkSearch(LinkList *L, ElemType *e, long long key) {
    int j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next && p->data.ID != key) {
        /*��pָ����һ���ڵ�*/
        p = p->next;
    }
    /*��i���ڵ㲻����*/
    if (!p)
        return 0;
    if (p->data.ID == key)
        *e = p->data;
    return 1;
}
/*
������Ķ�ȡ���ؽڵ�ָ��
*/
LinkList GetElemNode(LinkList *L, long long i) {
    int j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*jΪ������*/
    j = 0;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next && j < i) {
        /*��pָ����һ���ڵ�*/
        p = p->next;
        ++j;
    }
    /*��i���ڵ㲻����*/
    if (!p || j > i)
        return ERROR;
    return p;
}
/*
������Ķ�ȡ��ID
*/
LinkList GetElemNodebyID(LinkList *L, long long ID) {
    long long j;
    /*����һָ��p*/
    LinkList p;
    /*��pָ������L�ĵ�һ���ڵ�*/
    p = *L;
    /*jΪ������*/
    j = 0;
    /*p��Ϊ���Ҽ�����j��û�е���iʱ��ѭ������*/
    while (p->next && j !=ID) {
        /*��pָ����һ���ڵ�*/
        p = p->next;
        ++j;
    }
    /*��i���ڵ㲻����*/
    if (!p)
        return ERROR;
    return p;
}

/*
��������ĩβ����
*/
Status ListInsert(LinkList *L, ElemType e) {
    LinkList p, s;
    p = *L;
    while (p->next) {
        p = p->next;
    }

    /*�����½ڵ�*/
    s = (LinkList) malloc(sizeof(LinkNode));
    s->data = e;
    /*��p�ĺ�̽ڵ㸳ֵ��s�ĺ��*/
    s->next = p->next;
    /*��s��ֵ��p�ĺ��*/
    p->next = s;
    return OK;
}
/*
������λ�ò���
*/
Status ListInsertNumber(LinkList *L, int i, ElemType e) {
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    /*Ѱ�ҵ�i-1���ڵ�*/
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    /*��i���ڵ㲻����*/
    if (!p || j > i)
        return ERROR;
    /*�����½ڵ�*/
    s = (LinkList) malloc(sizeof(LinkNode));
    s->data = e;
    /*��p�ĺ�̽ڵ㸳ֵ��s�ĺ��*/
    s->next = p->next;
    /*��s��ֵ��p�ĺ��*/
    p->next = s;
    return OK;
}
/*
�������ɾ��
*/
Status ListDelete(LinkList *L, int i, ElemType *e) {
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    /*����Ѱ�ҵ�i-1���ڵ�*/
    while (p->next && j < i) {
        p = p->next;
        ++j;
    }
    /*��i���ڵ㲻����*/
    if (!(p->next) || j > i)
        return ERROR;
    q = p->next;
    /*��q�ĺ�̸���p�ĺ��*/
    p->next = q->next;
    /*��q�ڵ��е����ݸ�p�ĺ��*/
    *e = q->data;
    /*��ϵͳ���մ˽ڵ㣬�ͷ��ڴ�*/
    free(q);
    return OK;
}

/*
�������ɾ����ID
*/
Status ListDeletebyID(LinkList *L,long long id){
    LinkList p, q;
    p = *L;
    /*����Ѱ�ҵ�i-1���ڵ�*/
    while (p->next && id!=p->next->data.ID) {
        p = p->next;
    }
    /*��i���ڵ㲻����*/
    if (!(p->next))
        return ERROR;
    /*��q�ĺ�̸���p�ĺ��*/
    q = p->next;
    /*��q�ڵ��е����ݸ�p�ĺ��*/
    p->next = q->next;
    /*��ϵͳ���մ˽ڵ㣬�ͷ��ڴ�*/
    free(q);
}

/*
������Ĵ���
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
������ı���
*/
void LinklistPrint(LinkList *L) {
    if (L == NULL) {
        //�����������ӡ
        return;
    }
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL) {
        //��ӡԪ�غ����Ӧ�ĵ�ַ
        printf("\t\t���ID:%lld\n", p->data.ID);
        printf("\t\t���Rank:%d\n", p->data.Rank);
        printf("\t\t���K/D:%.1lf\n", p->data.KD);
        printf("\t\t��ҳԼ���:%%%d\n", p->data.Chicken);
        //�ƶ�cur,�Դﵽ���������Ŀ��
        p = p->next;
    }
    printf("\n\n");

}

/*
�����������
*/
int getNum(LinkList *L) {
    int Num = 0;
    if (L == NULL) {
        //���������Ϊ0
        return 0;
    }
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL) {
        //����
        Num++;
        //�ƶ�cur,�Դﵽ���������Ŀ��
        p = p->next;
    }
    return Num;
}

/*
 ������Ѱ�������ǰ��
 */
LinkList findPre(LinkList *L, LinkList node) {
    LinkList p = *L;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}

/*
 * ���������ڵ��ǰ�������������ڵ�
 * ��Ҫ���ǵ�����У�
 * 1.����ڵ�1�ͽڵ�2��ͬ������Ҫ����
 * 2.�������һ���ڵ�Ϊͷ�ڵ㣬ԭ���ϲ�����
 * 3.��������ڵ����ڣ���Ҫ��һЩ���⴦��
 * 4.���������ֻ��Ҫ�ҵ��ڵ��ǰ����Ȼ������Ӧ��ָ��ĵ�����
 **/
void doExchange(LinkList L, LinkList node1, LinkList node2) {

    LinkList prenode1 = NULL;  //�������ڵ�node1��ǰһ���ڵ�
    LinkList postnode1 = NULL; //�������ڵ�node1�ĺ�һ���ڵ�
    LinkList prenode2 = NULL;  //�������ڵ�node2��ǰһ���ڵ�
    LinkList postnode2 = NULL; //�������ڵ�node2�ĺ�һ���ڵ�

    //ͷ�ڵ㲻����
    if (node1 == L || node2 == L) {
        return;
    }

    //��ͬ���轻��
    if (node1 == node2) {
        return;
    }

    prenode1 = findPre(L, node1);
    prenode2 = findPre(L, node2);
    postnode1 = node1->next;
    postnode2 = node2->next;

    //�ڵ������������
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

    //��������£�ֱ�ӽ����ڵ�
    prenode1->next = node2;
    node2->next = postnode1;
    prenode2->next = node1;
    node1->next = postnode2;
}

/*
 * ��������λ��
 */
void Exchange(LinkList L, int i, int j) {
    doExchange(L, GetElemNode(L, i), GetElemNode(L, j));
}

/*
�ļ�������д��
*/
int FileWrite(LinkList *L) {

    int num = 0;
    FILE *fp = fopen("C:\\Users\\ROG\\Desktop\\ChickenMatchSystem\\PlayerList.txt", "w+");
    /*if (fp == NULL) {
        printf("�Ҳ����û���Ϣ");
        exit(1);
    }*/
    if (L == NULL) {
        //����������д��
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
�ļ���ȡ������
*/
int FileRead(LinkList *L) {
    int num = 0;
    FILE *fp = fopen("C:\\Users\\ROG\\Desktop\\ChickenMatchSystem\\PlayerList.txt", "r");
    if (fp == NULL) {
        printf("�Ҳ����û���Ϣ");
        exit(1);
    }
    LinkList p = *L, pTemp;
    while (1) {
        pTemp = (LinkList) malloc(sizeof(LinkNode));
        pTemp->next = NULL;
        /*������һ���м��㣬��ʱ���棬fread��һ�β��ܾ����Ƿ���ӽ�㣬ֱ����p��ӽ�����󣬱�����ǿ��ļ�ʱ����һ����㣬�������ֵ����fread������һ���ڴ���ܶ�*/
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
 * ��ʼ������
 */
void Initiate(LinkNode **head)
{
    (*head)=(LinkNode*)malloc(sizeof(LinkNode));
    (*head)->next=NULL;
}
/*
 * �ҵ�ͷ���
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
 * ��ӽڵ�
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
 * ������������
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
 * ����int���͵�a^n
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
 * ���ÿһλ������
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
 * ��������Ļ�������
 * �ڶ����βα�ʾ�μ�������������λ��һ����countλ����
 */
void radix_sort(LinkList *head,int count,int kind)
{
    LinkList p[10],q;
    long long i,j,k;

    for(j=1;j<=count;j++)
    {
        //ʮ��ͷ����ʼ��
        for(i=0;i<10;i++)
        {
            Initiate(&p[i]);
        }
        //�����ͷ��βɨ�裬����ɨ�赽�Ľڵ���������
        while((*head)->next!=NULL)
        {
            q=GetFirstNode(head);

            k=GetNum(q,j,kind); //ȡ������ڵ��jλ��Ԫ��ֵk
            AppendNode(p[k],q);
            //���ýڵ����ӵ�10��������Ӧ��λ��
        }
        //��10�������0-9�������ӵ�head�ڵ����
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
 * ���������ð������
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
 * ��Ϸ��ͼ
 */
void Map(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 4;
    switch (n){
        case 1:{
            printf("\t\t�����䵽�˰��׸����\n");
        }
            break;
        case 2:{
            printf("\t\t�����䵽��������\n");
        }
            break;
        case 3:{
            printf("\t\t�����䵽����ŵ\n");
        }
            break;
        case 4:{
            printf("\t\t�����䵽��ά����\n");
        }
            break;
    }
}
/*
 * ǹе
 */
void Gun(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 11;
    switch (n){
        case 1:{
            printf("\t\t������M416\n");
        }
            break;
        case 2:{
            printf("\t\t������Scar\n");
        }
            break;
        case 3:{
            printf("\t\t������SKS(29ɱ����)\n");
        }
            break;
        case 4:{
            printf("\t\t������Kar98\n");
        }
            break;
        case 5:{
            printf("\t\t������M16\n");
        }
            break;
        case 6:{
            printf("\t\t������P18c\n");
        }
            break;
        case 7:{
            printf("\t\t������VSS\n");
        }
            break;
        case 8:{
            printf("\t\t������ƽ�׹�\n");
        }
            break;
        case 9:{
            printf("\t\t������AKM\n");
        }
            break;
        case 10:{
            printf("\t\t������AWM\n");
        }
            break;
        case 11:{
            printf("\t\t������S686\n");
        }
            break;
    }
}
/*
 * ��������
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
            printf("\t\t����ɱ��һ������\n");
            return 1;
        }
        case 6:{
            printf("\t\t����������\n");
            return -1;
        }
        case 7:
        case 8:{
            printf("\t\t����������\n");
            return -1;
        }
        case 9:
        case 10:
        case 11:
        case 12:{
            printf("\t\t������ɱ��\n");
            return -1;
        }
    }
}
/*
 * ����
 */
void Armor(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 11;
    switch (n){
        case 1:{
            printf("\t\t������һ����\n");
        }
            break;
        case 2:{
            printf("\t\t�����˶�����\n");
        }
            break;
        case 3:{
            printf("\t\t������������\n");
        }
            break;
        case 4:{
            printf("\t\t������ԭ���Կ�\n");
        }
            break;
        case 5:{
            printf("\t\t�����˶���ͷ\n");
        }
            break;
        case 6:{
            printf("\t\t����������ͷ\n");
        }
            break;
        case 7:{
            printf("\t\t�����˱���\n");
        }
            break;
        case 8:{
            printf("\t\t�����˼��Ȱ�\n");
        }
            break;
        case 9:{
            printf("\t\t��������������\n");
        }
            break;
        case 10:{
            printf("\t\t��������������\n");
        }
            break;
        case 11:{
            printf("\t\t������ҽ����\n");
        }
            break;
    }
}

/*
 * ��ӻ�����
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
 * �Լ�ƥ��
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
            //��ӡԪ�غ����Ӧ�ĵ�ַ
            printf("\t\t���ҵ�ƥ�����%d��\n",i);
            printf("\t\t���ID:%lld\n", p->data.ID);
            printf("\t\t���Rank:%d\n", p->data.Rank);
            printf("\t\t���K/D:%.3lf\n", p->data.KD);
            printf("\t\t��ҳԼ���:%%%d\n", p->data.Chicken);
        }

        //�ƶ�p,�Դﵽ���������Ŀ��
        p = p->next;
    }
    printf("\t\t��Ϸ��ʼ\n\n\n\n");
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
        printf("\t\t������Ϸ��һ����ɱ%.0lf\n",kill);
        printf("\t\t�󼪴�������Լ�\n");
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
        printf("\t\t������Ϸ��һ����ɱ%.0lf\n",kill);
        printf("\t\t�ٽ������´γԼ�\n");
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
    printf("\t\t��Ϸ����\n");
    int number;
    printf("\t\t1.������һ��������\n");
    printf("\t\t0.�˳�\n");
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
 * ���ֲ���
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
����Ա�˵�
*/
void AdministratorMenu(LinkList L){
    int number;
    printf("***************************************\n");
    printf("          �Լ�ƥ��ϵͳ����Ա�˵�ģ��        \n");
    printf("***************************************\n");
    printf("\t\t1.�����ID��ѯ\n");
    printf("\t\t2.����������ֲ�ѯ\n");
    printf("\t\t3.�����K/D��ѯ����\n");
    printf("\t\t4.���ƥ��\n");
    printf("\t\t5.���������Ϣ\n");
    printf("\t\t6.ɾ�������Ϣ\n");
    printf("\t\t7.�鿴���������Ϣ\n");
    printf("\t\t8.������ӻ�����\n");
    printf("\t\t9.���浽�ļ����˳�ƥ��ϵͳ\n");
    printf("\t\t0.�˳�ƥ��ϵͳ\n");
    printf("******************END******************\n");
    scanf("%d", &number);
    switch (number) {
        case 1: {
            long long ID;
            ElemType e;
            printf("\t\t���������ID\n");
            scanf("%lld", &ID);
            binarySearch(L,4,ID);
            GetElem(L,ID,&e);
            printf("\t���ID:%lld\n", e.ID);
            printf("\t���Rank:%d\n", e.Rank);
            printf("\t���K/D:%.3lf\n", e.KD);
            printf("\t��ҳԼ���:%d\n", e.Chicken);
            int number;
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
            }
        }
            break;

        case 2:{
            int Rank;
            ElemType e;
            printf("\t\t���������Rank\n");
            scanf("%lld", &Rank);
            binarySearch(L,1,Rank);
            GetElem(L,Rank,&e);
            printf("\t���ID:%lld\n", e.ID);
            printf("\t���Rank:%d\n", e.Rank);
            printf("\t���K/D:%.3lf\n", e.KD);
            printf("\t��ҳԼ���:%d\n", e.Chicken);
            int number;
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
            }
        }
            break;
        case 3:{
            int KD;
            ElemType e;
            printf("\t\t���������K/D\n");
            scanf("%lld", &KD);
            binarySearch(L,2,KD);
            GetElem(L,KD,&e);
            printf("\t���ID:%lld\n", e.ID);
            printf("\t���Rank:%d\n", e.Rank);
            printf("\t���K/D:%.3lf\n", e.KD);
            printf("\t��ҳԼ���:%d\n", e.Chicken);
            int number;
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
            }
        }
            break;
        case 4:{
            ChickenMatch(L);
            int number;
            printf("\t\t1.������һ��������\n");
            printf("\t\t0.�˳�\n");
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
            printf("\t\t���������ID\n");
            scanf("%lld",&e.ID);
            printf("\t\t�������������\n");
            scanf("%s",password);
            strcpy(e.password,password);
            printf("\t\t���������Rank\n");
            scanf("%d",&e.Rank);
            printf("\t\t���������K/D\n");
            scanf("%lf",&e.KD);
            printf("\t\t��������ҳԼ�����\n");
            scanf("%d",&e.Chicken);
            ListInsert(L,e);
            printf("\t\t���ID%lld�����ɹ�\n",e.ID);

        }
            break;
        case 6: {
            long long ID;
            printf("\t\t���������ID\n");
            scanf("%lld", &ID);
            ListDeletebyID(L, ID);
            printf("\t\t���ID%lldɾ���ɹ�\n", ID);
            int number;
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
            }
        }
            break;
        case 7: {
            int number;
            LinklistPrint(L);
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
            }
        }
            break;
        case 8:{
            int num;
            printf("\t\t��������ӻ����˵�����\n");
            scanf("%d",&num);
            int n;
            n=addRobot(L,num);
            printf("\t\t�ɹ����%d��������\n",n);
            int number;
            printf("\t\t1.������һ���˵�\n");
            printf("\t\t2.���浽�ļ����˳�\n");
            printf("\t\t0.ֱ���˳�\n");
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
                    printf("\t\t����������������룺\n");
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
ע��˵�
*/
void RegisterMenu(LinkList L) {
    long long ID;
    ElemType check;
    char pass1[20];
    char pass2[20];
    printf("***************************************\n");
    printf("           ��ӭʹ�óԼ�ƥ��ϵͳע��ģ��        \n");
    printf("***************************************\n");
    printf("\t\t��������Ҫע���ID�����֣�\n");
    scanf("%lld", &ID);
    LinkSearch(L,&check,ID);
    if(ID==check.ID){
        printf("\t\t�û����Ѵ��ڣ�������ע��\n");
        RegisterMenu(L);
    }
    printf("\t\t�������������\n");
    scanf("%s", pass1);
    printf("\t\t���ٴ������������\n");
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
        printf("��ϲ���");
        printf("%lld", ID);
        printf("ע��ɹ�\n");
        sleep(200);
        showMenu(L);
    }
}

/*
��¼�˵�
*/
void LoginMenu(LinkList L) {
    long long ID;
    char pass[20];
    printf("***************************************\n");
    printf("           ��ӭʹ�óԼ�ƥ��ϵͳ��¼ģ��        \n");
    printf("***************************************\n");
    printf("\t\t��������Ҫ��¼��ID\n");
    scanf("%lld", &ID);
    printf("\t\t�������������\n");
    scanf("%s", pass);
    ElemType e;
    LinkSearch(L, &e, ID);
    if (strcmp(pass, e.password) == 0) {
        printf("\t\t��ϲ���");
        printf("%lld\n", ID);
        printf("\t\t��¼�ɹ�\n");
        LoginPlayer->data=e;
        AdministratorMenu(L);
    } else {
        printf("\t\t��¼ʧ��");
        printf("\t\t����������ID������");
        sleep(300);
        LoginMenu(L);
    }
}

/*
�����淽��
*/
void showMenu(LinkList L) {
    int number;
    printf("***************************************\n");
    printf("           ��ӭʹ�óԼ�ƥ��ϵͳ        \n");
    printf("***************************************\n");
    printf("\t\t1����¼\n");
    printf("\t\t2��ע��\n");
    printf("\t\t0���˳�\n");
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
            printf("\t\t����������������룺\n");
    }
}
/*
 * �˳�����
 */
void Exit(LinkList L){
    int number;
    printf("\t\t1.������һ���˵�\n");
    printf("\t\t2.���浽�ļ����˳�\n");
    printf("\t\t0.ֱ���˳�\n");
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
            printf("\t\t����������������룺\n");
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
