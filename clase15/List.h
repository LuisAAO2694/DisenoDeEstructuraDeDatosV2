/*
 * List.h
 *
 *  Created on: 13 oct 2026
 *      Author: diego.gilbert
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

typedef void* Type;
typedef struct strList* List;
typedef void (*freeFunc) (void*);
typedef struct strNode* Iterator;

List list_create(freeFunc f);
void list_destroy(List l);
int list_size(List l);
void list_add(List l, Type e);
Type list_get(List l, int i);
void list_set(List l, Type e, int i);
Type list_remove(List l, int i);
void list_insert(List l, Type e, int i);


Iterator list_begin(List l);
Iterator list_end(List l);
bool list_hasNext (Iterator it); 
bool list_hasPrior(Iterator it);
Iterator list_next (Iterator it);
Iterator list_prior(Iterator it);
Type list_data(Iterator it);


#endif /* LIST_H_ */
