#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    int Chicken;
    int Competence;
} Player;
/*
�����ڵ�
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
/*
�������Ķ�ȡ
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
����K/Dִ�е������Ĳ���
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
            printf("\t\t���Chicken:%.3lf\n",  p->data.Chicken);
        }
        /*��pָ����һ���ڵ�*/
        p = p->next;

    }
}

/*
����Rankִ�е������Ĳ���
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
            printf("\t\t���Chicken:%.3lf\n",  p->data.Chicken);
        }
        /*��pָ����һ���ڵ�*/
        p = p->next;

    }
}
/*
����ID���е������Ĳ���
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
        printf("%lld\n", p->data.ID);
    }
    /*��i���ڵ㲻����*/
    if (!p)
        return 0;
    if (p->data.ID == key)
        *e = p->data;
    return 1;
}
/*
�������Ķ�ȡ���ؽڵ�ָ��
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
��������λ�ò���
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
��������ɾ��
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
��������ɾ����ID
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
�������Ĵ���
*/
void CreativeListHead(LinkList *L) {
    *L = (LinkList) malloc(sizeof(LinkNode));
    (*L)->next = NULL;
    LinkList p;
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
        p->data = player[i];
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

/*
�������ı���
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
        printf("���ID:%lld\n", p->data.ID);
        printf("���Rank:%d\n", p->data.Rank);
        printf("���K/D:%.1lf\n", p->data.KD);
        printf("��ҳԼ���:%%%d\n", p->data.Chicken);
        //�ƶ�cur,�Դﵽ����������Ŀ��
        p = p->next;
    }
    printf("\n\n");

}

/*
������������
*/
int getNum(LinkList *L) {
    int Num = 0;
    if (L == NULL) {
        //����������Ϊ0
        return 0;
    }
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL) {
        //����
        Num++;
        //�ƶ�cur,�Դﵽ����������Ŀ��
        p = p->next;
    }
    return Num;
}

/*
 ������Ѱ��������ǰ��
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
 * 3.��������ڵ����ڣ���Ҫ��һЩ���⴦����
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
 * ����������λ��
 */
void Exchange(LinkList L, int i, int j) {
    doExchange(L, GetElemNode(L, i), GetElemNode(L, j));
}

/*
�ļ�������д��
*/
int FileWrite(LinkList *L) {

    int num = 0;
    FILE *fp = fopen("../PlayerList.txt", "wb+");
    if (fp == NULL) {
        printf("�Ҳ����û���Ϣ");
        exit(1);
    }
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
    FILE *fp = fopen("../PlayerList.txt", "r");
    if (fp == NULL) {
        printf("�Ҳ����û���Ϣ");
        exit(1);
    }
    LinkList p = *L, pTemp;
    while (1) {
        pTemp = (LinkList) malloc(sizeof(LinkNode));
        pTemp->next = NULL;
        /*������һ���м��㣬��ʱ���棬fread��һ�β��ܾ����Ƿ����ӽ�㣬ֱ����p���ӽ�����󣬱������ǿ��ļ�ʱ����һ����㣬�������ֵ����fread������һ���ڴ���ܶ�*/
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
 * ���������Ļ�������
 */
void radix_sort(LinkList L, int s) {
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
            printf("\t\t�����䵽�˰��׸����");
        }
            break;
        case 2:{
            printf("\t\t�����䵽��������");
        }
            break;
        case 3:{
            printf("\t\t�����䵽����ŵ");
        }
            break;
        case 4:{
            printf("\t\t�����䵽��ά����");
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
            printf("\t\t������M416");
        }
            break;
        case 2:{
            printf("\t\t������Scar");
        }
            break;
        case 3:{
            printf("\t\t������SKS(29ɱ����)");
        }
            break;
        case 4:{
            printf("\t\t������Kar98");
        }
            break;
        case 5:{
            printf("\t\t������M16");
        }
            break;
        case 6:{
            printf("\t\t������P18c");
        }
            break;
        case 7:{
            printf("\t\t������VSS");
        }
            break;
        case 8:{
            printf("\t\t������ƽ�׹�");
        }
            break;
        case 9:{
            printf("\t\t������AKM");
        }
            break;
        case 10:{
            printf("\t\t������AWM");
        }
            break;
        case 11:{
            printf("\t\t������S686");
        }
            break;
    }
}
/*
 * ��������
 */
int Army(){
    srand( (unsigned)time( NULL ) );
    int n=rand() % 10;
    switch (n){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:{
            printf("\t\t����ɱ��һ������");
        }
            break;
        case 6:{
            printf("\t\t����������");
        }
            break;
        case 7:{
            printf("\t\t����������");
        }
            break;
        case 8:{
            printf("\t\t����������");
        }
            break;
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
            printf("\t\t������һ����");
        }
            break;
        case 2:{
            printf("\t\t�����˶�����");
        }
            break;
        case 3:{
            printf("\t\t������������");
        }
            break;
        case 4:{
            printf("\t\t������ԭ���Կ�");
        }
            break;
        case 5:{
            printf("\t\t�����˶���ͷ");
        }
            break;
        case 6:{
            printf("\t\t����������ͷ");
        }
            break;
        case 7:{
            printf("\t\t�����˱���");
        }
            break;
        case 8:{
            printf("\t\t�����˼��Ȱ�");
        }
            break;
        case 9:{
            printf("\t\t��������������");
        }
            break;
        case 10:{
            printf("\t\t��������������");
        }
            break;
        case 11:{
            printf("\t\t������ҽ����");
        }
            break;
    }
}

/*
 * ���ӻ�����
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
    LinkList p;
    p = *L;
    p = p->next;
    while (p != NULL&&i<=2) {
        if(abs(LoginPlayer->data.Rank-p->data.Rank)<300)
        {
            i++;
            //��ӡԪ�غ����Ӧ�ĵ�ַ
            printf("\t\t���ҵ�ƥ�����%d��",i);
            printf("\t\t���ID:%lld\n", p->data.ID);
            printf("\t\t���Rank:%d\n", p->data.Rank);
            printf("\t\t���K/D:%.3lf\n", p->data.KD);
            printf("\t\t��ҳԼ���:%%%d\n", p->data.Chicken);
        }

        //�ƶ�p,�Դﵽ����������Ŀ��
        p = p->next;
    }
    printf("\t\t��Ϸ��ʼ\n");
    Map();

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
    radix_sort(L, kind);
    switch (kind) {
        case 1: {
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
    printf("\t\t8.�������ӻ�����\n");
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

        }
            break;

        case 2:{
            int Rank;
            ElemType e;
            printf("\t\t���������Rank\n");
            scanf("%lld", &Rank);
            LinkSearchbyRank(L,Rank);

        }
            break;
        case 3:{
            int KD;
            ElemType e;
            printf("\t\t���������K/D\n");
            scanf("%lld", &KD);
            LinkSearchbyKD(L,KD);
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
        case 6:{
            long long ID;
            printf("\t\t���������ID\n");
            scanf("%lld",&ID);
            ListDeletebyID(L,ID);
            printf("\t\t���ID%lldɾ���ɹ�\n",ID);
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
        case 7:{
            int number;
            LinklistPrint(L);
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
        case 8:{
            int num;
            printf("\t\t���������ӻ����˵�����\n");
            scanf("%d",&num);
            int n;
            n=addRobot(L,num);
            printf("\t\t�ɹ�����%d��������\n",n);
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
        case 0:
            exit(0);
            break;
        default:
            printf("\t\t����������������룺\n");
    }
}

/*
ע��˵�
*/
void RegisterMenu(LinkList L) {
    long long ID;
    char pass1[20];
    char pass2[20];
    printf("***************************************\n");
    printf("           ��ӭʹ�óԼ�ƥ��ϵͳע��ģ��        \n");
    printf("***************************************\n");
    printf("\t\t��������Ҫע���ID\n");
    scanf("%lld", &ID);
    printf("\t\t�������������\n");
    scanf("%s", pass1);
    printf("���ٴ������������\n");
    scanf("%s", pass2);
    if (strcmp(pass1, pass2) == 0) {
        ElemType e;
        e.ID = ID;
        e.Chicken = 0;
        e.KD = 0;
        e.Rank = 0;
        e.Competence = 1;
        strcpy(e.password, pass1);
        printf("123");
        ListInsert(L, e);
        printf("��ϲ���");
        printf("%lld", ID);
        printf("ע��ɹ�\n");
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
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\t\t����������������룺\n");
    }
}

int main() {
    LinkList L;
    L = (LinkList) malloc(sizeof(LinkNode));
    CreativeListHead(L);
    ElemType e;
    LoginPlayer = (LinkList) malloc(sizeof(LinkNode));
    AdministratorMenu(L);
    /* printf("������д���ļ��ĸ���Ϊ��");
     printf("%d\n",FileWrite(L));*/
    /*printf("�����������ļ��ĸ���Ϊ��");
    printf("%d\n",FileRead(L));*/
    /*  LinklistPrint(L);
      printf("���������\n");
      radix_sort(L,3);
      ElemType player1;
      GetElem(L,binarySearch(L, 1,1200),&player1);
      printf("%d",player1.ID);
     */
}