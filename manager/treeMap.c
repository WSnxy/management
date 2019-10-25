#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dyArray.h"
typedef int status; //ִ��״̬ 0�ɹ� -1ʧ��

typedef struct bstree {
	char* key;//id�� 
	void* value;//��Ʒ
	struct bstree* lchild;
	struct bstree* rchild;
}TreeMap;
//������
 TreeMap*  creat_TreeMap(const char* key,void* value) {
	TreeMap* obj = (TreeMap*)malloc(sizeof(TreeMap));
	obj->key = key;
	obj->value = value;
	obj->lchild = NULL;
	obj->rchild = NULL;
	return obj;
}
/*
����
*/
 //Ŀ��ڵ�
//���ڵ�
 //��ǰ���ҽڵ�
 //���������׶�ʧ���Ѹ��ڵ�ȡ������Ҳ��ʾ��ǰ�ڵ㣬����ָ��
static status searchBST(TreeMap* target, const char* key, TreeMap* f, TreeMap** p,TreeMap** ff) {
	if (NULL == target||NULL==key) {
		*ff = f;
		return -1;
	}
	int i = strcmp(target->key, key);
	if (i == 0) {
		*p = target;
		*ff = f;
		return 0;
	}
	if (i ==1)return searchBST(target->lchild,key,target,p,ff);
	if (i ==-1)return searchBST(target->rchild,key,target,p,ff);
}
static status search2TreeMap(TreeMap* target, const char* key, TreeMap** ff, TreeMap** p) {
 	return searchBST(target,key,NULL,p,ff);
}
//�Լ�ʹ��
TreeMap* search_TreeMap(TreeMap* target, const char* key) {
	TreeMap* ff = NULL;
	TreeMap* pp = NULL;
	search2TreeMap(target,key,&ff,&pp);
	return pp;
}
//���������õ��ã�������Ϊ�˺��ã��൱��Ϊ�˷���ʹ��
/*
����
*/
status insert_TreeMap(TreeMap* target, void* value, const char* key) {
	if (NULL == target || NULL == value || NULL == key)return -1;
	TreeMap* temp = NULL;
	TreeMap* pp = NULL;
	if (search2TreeMap(target, key,&temp, &pp)==-1)
	{
		TreeMap* obj = creat_TreeMap(key, value);
		int i = strcmp(temp->key, key);
		if (i == 1) temp->lchild = obj;
		if (i == -1)temp->rchild = obj;
		return 0;
	}
	return -1;
}
//��ȡ�ܽڵ���
int size_TreeMap(TreeMap* target) {
	int size = 0;
	if (NULL == target) {
		return 0;
	}
	else
	{
		size = 1 + size_TreeMap(target->lchild) + size_TreeMap(target->rchild);
	}
	return size;
}
/*
 ɾ��
*/
status delete_TreeMap(TreeMap** target, const char* key) {
	
	if (NULL == *target||NULL==key)return -1;
	TreeMap* p = NULL;
	TreeMap* temp = NULL;
	TreeMap* last = NULL;
	TreeMap* f=NULL;
	if (search2TreeMap(*target, key, &f, &p) == 0) {
		if (NULL != p->lchild&&NULL == p->rchild) {//��ɾ���Ľڵ�ֻ��������
			temp = p->lchild;
			p->key = temp->key;
			p->value = temp->value;
			p->lchild = temp->lchild;
			p->rchild = temp->rchild;
			free(temp);
			return 0;
		}
		else if (NULL == p->lchild&&NULL != p->rchild) {//��ɾ���Ľڵ�ֻ��������
			temp = p->rchild;
			p->key = temp->key;
			p->value = temp->value;
			p->lchild = temp->lchild;
			p->rchild = temp->rchild;
			free(temp);
			return 0;
		}
		else if(NULL==p->lchild&&NULL==p->rchild)//����������û��
		{
			if (NULL==f) {
				
				free(*target);
				*target = NULL;
				return 0;
			}
			if (p==f->lchild)f->lchild = NULL;
			if (p==f->rchild)f->rchild = NULL;
			free(p);
			return 0;
		}
	
		else { //��ɾ���Ľڵ�������������
			last = p;
			temp =p->lchild;
			while (temp->rchild!=NULL)
			{
				last = temp;
				temp = temp->rchild;
			}	
			if (last != p) {
				p->key = last->key;
				p->value = last->value;
				last->rchild = temp->lchild;
			}
			else {
				p->key = temp->key;
				p->value = temp->value;
				last->lchild = temp->lchild;
			}
			free(temp);
		}

	}
	return -1;
}
//��ȡkeys    // �����������ȡkeys
static void getKeys(TreeMap* target,DynamicArray* keys,int* pos) {
	if (NULL == target)return;
	 getKeys(target->lchild,keys,pos);
	 insert_DynamicArray(keys,target->key,(*pos)++);
	 getKeys(target->rchild,keys,pos);
}
DynamicArray* getKeys_TreeMap(TreeMap* target) {
	int pos = 0;
	DynamicArray* keys = init_DynamicArray(20);
	getKeys(target,keys,&pos);
	return keys;
}
//��ȡvalues��������������붯̬����
static void getValues(TreeMap* target, DynamicArray* values, int* pos){
	if (NULL == target)return;
	getValues(target->lchild,values,pos);
	insert_DynamicArray(values,target->value,(*pos)++);
	getValues(target->rchild,values,pos);
}

//�������
DynamicArray* getValues_TreeMap(TreeMap* target) {
	int pos = 0;
	DynamicArray* values = init_DynamicArray(20);
	getValues(target, values, &pos);
	return values;
}

//�ͷ�BST
void free_TreeMap(TreeMap* target) {
	if (NULL == target)return;
	free_TreeMap(target->lchild);//�ͷ�������
	free_TreeMap(target->rchild);//�ͷ�������
	free(target);//�ͷŸ��ڵ�
}

//������ʽ���ã�����Ϊ�˷���У���ʽ