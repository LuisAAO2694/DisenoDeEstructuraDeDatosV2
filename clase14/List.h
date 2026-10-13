#ifndef LIST_H_
#define LIST_H_

//Tipos genéricos
typedef void *Type;
typedef struct strList *List;

List list_create();
void list_destroy(List l);
int list_size(List l);
void list_add(List l, Type e);
Type list_get(List l, int i);
void list_set(List l, Type e, int i);
Type list_remove(List l, int i);
void list_insert(List l, Type e, int i);


#endif /* LIST_H_ */
