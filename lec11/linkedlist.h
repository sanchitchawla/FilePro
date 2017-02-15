# define SUCCESS_LL 0
# define NULL_LIST_LL 1
# define NULL_DATA_LL 2
# define EMPTY_LIST_LL 3


typedef struct node_t{
  void* data;
  struct node_t* next;
}node;

typedef struct{
  node* head;
  node* tail;
  int count;
} linkedlist;

int initList(linkedlist* l);
int insertFront(linkedlist* l, void *data);
int removeFront(linkedlist* l, void **data);
int insertBack(linkedlist* l, void *data);
int removeBack(linkedlist* l, void **data);
int destroyList(linkedlist *l);