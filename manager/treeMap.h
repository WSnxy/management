#ifndef  __H_TREEMAP_
#define  __H_TREEMAP_
#include"dyArray.h"
/*
  基于BST（二叉查找树）的TreeMap（）
*/
typedef struct bstree {
	char* key;
	void* value;//data
	struct bstree* lchild;
	struct bstree* rchild;
}TreeMap;

typedef int status;
//通过key查找
TreeMap* search_TreeMap(TreeMap* target, const char* key);//target传入一棵树
//添加key-value
status insert_TreeMap(TreeMap* target, void* value, const char* key);
//删除
status delete_TreeMap(TreeMap** target, const char* key);
//释放整棵树的内存空间
void free_TreeMap(TreeMap* target);
//获取所有的key
DynamicArray* getKeys_TreeMap(TreeMap* target);
//获取TreeMap存储的数量
int size_TreeMap(TreeMap* target);
//获取所有的值
DynamicArray* getValues_TreeMap(TreeMap* target);
//创建TreeMap
TreeMap*  creat_TreeMap(const char* key, void* value);
#endif 
