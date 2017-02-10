typedef struct node_t
{
  void* data;
  struct node_t* next;
}node;

typedef struct
{
  node* head;
  node* tail;
  int count;
} slinkedlist;
