#ifndef  __H_TREEMAP_
#define  __H_TREEMAP_
#include"dyArray.h"
/*
  ����BST���������������TreeMap����
*/
typedef struct bstree {
	char* key;
	void* value;//data
	struct bstree* lchild;
	struct bstree* rchild;
}TreeMap;

typedef int status;
//ͨ��key����
TreeMap* search_TreeMap(TreeMap* target, const char* key);//target����һ����
//���key-value
status insert_TreeMap(TreeMap* target, void* value, const char* key);
//ɾ��
status delete_TreeMap(TreeMap** target, const char* key);
//�ͷ����������ڴ�ռ�
void free_TreeMap(TreeMap* target);
//��ȡ���е�key
DynamicArray* getKeys_TreeMap(TreeMap* target);
//��ȡTreeMap�洢������
int size_TreeMap(TreeMap* target);
//��ȡ���е�ֵ
DynamicArray* getValues_TreeMap(TreeMap* target);
//����TreeMap
TreeMap*  creat_TreeMap(const char* key, void* value);
#endif 
