#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node
{
    const void * data;
    Node * next;
    Node * prev;
};

struct List
 {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List *orden = (List *) malloc(sizeof(List));
  orden->head = NULL;
  orden->tail = NULL;
   return orden;
}

void * firstList(List * list)
{
  if (list->head != NULL)
  {
    list->current = list->head;
    return (void *)list->head->data;
  }
    return NULL;
}

void * nextList(List * list)
{
  if (list->current != NULL && list->current->next != NULL)
  {
    list->current = list->current->next;
    return (void*) list->current->data;
  }
  return NULL;
}

void * lastList(List * list) 
{
  if(list->tail != NULL)
  {
    list->current = list->tail;
    return (void*) list->tail->data;
  }
    return NULL;
}

void * prevList(List * list)
{
  if(list->current != NULL && list->current->prev != NULL)
  {
    list->current = list->current->prev;
    return (void*) list->current->data;
  }
    return NULL;
}

void pushFront(List * list, const void * data)
{
   Node *nuevoDato = createNode(data);
   if(list->head != NULL)
   {
     list->head->prev = nuevoDato;
     nuevoDato->next = list->head;
     list->head = nuevoDato;
     list->current = nuevoDato;
   }
   else 
   {
     list->head = nuevoDato;
     list->tail = nuevoDato;
     list->current = list->head;
   }
}

void pushBack(List * list, const void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data)
{
  if(list == NULL || data== NULL) return;
  Node *nuevoDato = createNode(data);
  if(list->head != NULL)
  {
    if(list->current == list->head)
    {
      if(list->tail != NULL)
      {
        nuevoDato->next = list->head->next;
      }
      list->head->next = nuevoDato;
      nuevoDato->prev = list->head;
    }
    else if (list->current == list->tail)
    {
      nuevoDato->prev = list->tail;
      list->tail->next = nuevoDato;
      list->tail = nuevoDato;
    }
    else 
    {
      list->current->next->prev = nuevoDato;
      nuevoDato->next = list->current->next;
      list->current->next = nuevoDato;
      nuevoDato->prev = list->current;
      list->current = nuevoDato;
    }
  }
  else 
  {
    list->head = nuevoDato;
    list->tail = nuevoDato;
    list->current = list->head;
  }

  
}
void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list)
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  Node * guardar = list->current;
   if(list == NULL) return NULL;
   //Verificamos si el current esta al final si es asi entonces al current le asignamos el anterior y borramos el ultimo
   if(list->current == list->tail)
   {
     list->tail = list->current->prev;
     list->tail->next = NULL;
   }
    //Verificamos si el current esta al inicio si es asi entonces al current le asignamos el siguiente y borramos el dato que estaba al principio
   else if(list->current == list->head)
   {
      list->head = list->current->next;
      list->head->prev = NULL;
   }
   else
   {
     //Como borramos el anterior al current debemos hacer que apunte al siguiente 
     list->current->prev->next = list->current->next;
     //Como borramos el siguiente al current debemos hacer que apunte al anterior
     list->current->next->prev =list->current->prev;
   }
   return (void *) guardar->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}