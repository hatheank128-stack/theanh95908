#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct    {
    	char hoten[30];
    	int masv;
    	float d1, d2, d3;
}Data;
typedef struct tagNode    {
    	Data infor;
    	struct tagNode *next, *prev;	
}Node;
typedef struct    {
    	Node *pHead;  
    	Node *pTail;
    	int spt;
}LList;						
/////////////////////////////////////
void initList(LList *L)
    {
    	L->pHead = NULL;
    	L->pTail = NULL;
    	L->spt = 0;
    }
/////////////////////////////////////
int emptyList(LList L)
 {
    	return (L.spt == 0); 
}
/////////////////////////////////////
void insert_Head(LList *L, Data x)
    {
    	Node *pp;
    	pp = (Node*) malloc(sizeof(Node));
    	pp->infor = x;
    	pp->next = NULL;
		pp->prev = NULL;		
    	if(emptyList(*L)){
    			L->pHead = pp;
    			L->pTail = pp;
    		}  	
        else {
    		L->pHead->prev = pp;
			pp->next = L->pHead;
    		L->pHead = pp;
    		}
    	L->spt++;
    }
///////////////////////////////////////
void nhap(Data *x){
    printf("Nhap ma sv: ");
    scanf("%d", &(x->masv));
    if(x->masv > 0){
        printf("Nhap ten sv: ");
        scanf("%s", (x->hoten));
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}
void in(Data x){
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n", 
            x.hoten, x.masv, x.d1, x.d2, x.d3);
}
void processList(LList L){
    Node *pp = L.pHead;
    while( pp != NULL ){
        	in(pp->infor);
        	pp = pp->next;
    	}
}
/////////////////////////////////////////
void insert_After(LList *L, Node *q, Data x){
	Node *pp;
	if(NULL == q) return;
	else{
		pp = (Node*) malloc(sizeof(Node));
		pp->infor = x;
		pp->next = q->next;
		q->next->prev = pp;
		q->next = pp;
		pp->prev = q;
		if(q == L->pTail) L->pTail = pp;
		L->spt++;
	}
}

void insert_Tail(LList *L, Data x){
	Node *pp;
	pp = (Node*) malloc(sizeof(Node));
	pp->infor = x;
	pp->next = NULL;
	pp->prev = NULL;			
	if (emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else{
		L->pTail->next = pp;
		pp->prev = L->pTail;		
		L->pTail = pp;
	}
	L->spt++;
}

void del_Head(LList *L){
	Node *pp;
	if(emptyList(*L)) return;
	else{
		pp = L->pHead;
		L->pHead = pp->next;
		if(L->pHead != NULL) L->pHead->prev = NULL;
		free(pp);
		L->spt--;
		if(L->pHead == NULL) L->pTail = NULL;
	}
}

void del_After(LList *L, Node *q){
	Node *pp;
	if(NULL==q) return;
	else{
		pp = q->next;
		q->next = pp->next;
		if (pp->next != NULL) pp->next->prev = q;
		free(pp);
		L->spt--;
		if (q->next == NULL) L->pTail = q;
	}
}

void del_K(LList *L, char name[30]){
	Node *pp=L->pHead, *q;
	while(pp !=NULL && !strstr(pp->infor.hoten, name)){
		q=pp;
		pp=pp->next;		
	}
	if(NULL==pp) return;
	else{
		if(pp==L->pHead) del_Head(L);
		else del_After(L, q);
	}
}

Node *search(LList L, char name[30]){
	Node *pp = L.pHead;
	while (pp != NULL && !strstr(pp->infor.hoten, name))
		pp = pp->next;		
	return pp;
}

void tach(LList L, LList *L1, LList *L2){
	initList(L1);
	initList(L2);
	Node *pp = L.pHead;
	while (pp != NULL){
		if(pp->infor.d1>8 || pp->infor.d2>8 || pp->infor.d3>8)
			insert_Head(L1, pp->infor);
		else
			insert_Head(L2, pp->infor);
		pp=pp->next;			
	}
}

int main(){
    LList L;
	int kt = 0;
	int ma;
	Node* q = NULL;
	char name[30];
	Data x;
	initList(&L);
	do{
	    printf("\nChuong trinh lam viec voi DSLK kep SV\n");
	    printf("\n1: Them nut vao dau danh sach");
	    printf("\n2: Them nut vao cuoi danh sach");
	    printf("\n3: Them nut vao sau mot nut khac trong danh sach");
	    printf("\n4: Xoa nut o dau danh sach");
	    printf("\n5: Xoa theo ten trong danh sach");
	    printf("\n6: Xoa nut sau mot nut khac trong danh sach");
	    printf("\n7: Tim theo ten trong danh sach");
	    printf("\n8: Tach danh sach thanh nhieu danh sach");
	    printf("\n9: Duyet ds");
	    printf("\n0: Thoat");
	    printf("\nMoi ban chon: ");
	    int chon;
	    scanf("%d", &chon);
	    switch(chon){
	        case 1: 
	            printf("Nhap thong tin sv can them\n");
	            nhap(&x);
	            if(x.masv > 0) 
                	insert_Head(&L, x);
            	break;
            case 2:	
	            printf("Nhap thong tin sv can them\n");
	            nhap(&x);
	            if(x.masv > 0) 
                	insert_Tail(&L, x);
            	break;
            case 3:
	            printf("Nhap ma SV: ");
				scanf("%d", &ma);
                q = L.pHead;
				while (q != NULL && q->infor.masv != ma){
					q = q->next;
				}
				printf("Nhap thong tin sv can them\n");
                nhap(&x);
                if (q != NULL && x.masv > 0) 
					insert_After(&L, q, x);
            	break;
            case 4: 
                del_Head(&L);
                break;
            case 5: 
                printf("Nhap ten can xoa: ");
    			scanf("%s", name);
    			del_K(&L, name);
                break;
            case 6: 
                printf("Nhap ma SV: ");
                scanf("%d", &ma);
                q = L.pHead;
                while (q != NULL && q->infor.masv != ma) {
                    q = q->next;
                }
                if (q != NULL && q->next != NULL)
                    del_After(&L, q);
                break;
            case 7: 
                printf("Nhap ten sv can tim: ");
                scanf("%s", name);
                q = search(L, name);
                if (q != NULL) {
                    in(q->infor);
                } else {
                    printf("Khong tim thay sv");
                }
                break;
            case 8: 
                LList L1, L2;
    			tach(L, &L1, &L2);
    			printf("Danh sach L1\n");
    			processList(L1);
    			printf("Danh sach L2\n");
    			processList(L2);
                break;
            case 9: 
                processList(L);
                break;    
            case 0: 
                printf("Bye bye\n");
	            kt = 1;
	            break;
        }
	}while(kt==0); 
}
