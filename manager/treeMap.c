#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dyArray.h"
typedef int status; //执行状态 0成功 -1失败

typedef struct bstree {
	char* key;//id号 
	void* value;//产品
	struct bstree* lchild;
	struct bstree* rchild;
}TreeMap;
//创建树
 TreeMap*  creat_TreeMap(const char* key,void* value) {
	TreeMap* obj = (TreeMap*)malloc(sizeof(TreeMap));
	obj->key = key;
	obj->value = value;
	obj->lchild = NULL;
	obj->rchild = NULL;
	return obj;
}
/*
查找
*/
 //目标节点
//父节点
 //当前查找节点
 //作用域容易丢失，把父节点取出来，也表示当前节点，二级指针
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
//自己使用
TreeMap* search_TreeMap(TreeMap* target, const char* key) {
	TreeMap* ff = NULL;
	TreeMap* pp = NULL;
	search2TreeMap(target,key,&ff,&pp);
	return pp;
}
//调用起来好调用，第三个为了好用，相当于为了方便使用
/*
插入
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
//获取总节点数
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
 删除
*/
status delete_TreeMap(TreeMap** target, const char* key) {
	
	if (NULL == *target||NULL==key)return -1;
	TreeMap* p = NULL;
	TreeMap* temp = NULL;
	TreeMap* last = NULL;
	TreeMap* f=NULL;
	if (search2TreeMap(*target, key, &f, &p) == 0) {
		if (NULL != p->lchild&&NULL == p->rchild) {//被删除的节点只有左子树
			temp = p->lchild;
			p->key = temp->key;
			p->value = temp->value;
			p->lchild = temp->lchild;
			p->rchild = temp->rchild;
			free(temp);
			return 0;
		}
		else if (NULL == p->lchild&&NULL != p->rchild) {//被删除的节点只有右子树
			temp = p->rchild;
			p->key = temp->key;
			p->value = temp->value;
			p->lchild = temp->lchild;
			p->rchild = temp->rchild;
			free(temp);
			return 0;
		}
		else if(NULL==p->lchild&&NULL==p->rchild)//左右子树都没有
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
	
		else { //被删除的节点左右子树都有
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
//获取keys    // 中序遍历，获取keys
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
//获取values，中序遍历，存入动态数组
static void getValues(TreeMap* target, DynamicArray* values, int* pos){
	if (NULL == target)return;
	getValues(target->lchild,values,pos);
	insert_DynamicArray(values,target->value,(*pos)++);
	getValues(target->rchild,values,pos);
}

//方便调用
DynamicArray* getValues_TreeMap(TreeMap* target) {
	int pos = 0;
	DynamicArray* values = init_DynamicArray(20);
	getValues(target, values, &pos);
	return values;
}

//释放BST
void free_TreeMap(TreeMap* target) {
	if (NULL == target)return;
	free_TreeMap(target->lchild);//释放左子树
	free_TreeMap(target->rchild);//释放右子树
	free(target);//释放根节点
}

//正则表达式作用，就是为了方便校验格式