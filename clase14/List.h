#ifndef LIST_H_
#define LIST_H_

typedef void* Type;
typedef struct strList* List;
typedef void (*freeFunc) (void*);

List list_create(freeFunc f);
void list_destroy(List l);
int list_size(List l);
void list_add(List l, Type e);
Type list_get(List l, int i);
void list_set(List l, Type e, int i);
Type list_remove(List l, int i);
void list_insert(List l, Type e, int i);


#endif /* LIST_H_ */
