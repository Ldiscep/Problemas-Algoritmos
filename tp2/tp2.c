#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
};
        

struct list_iter {
    list_t* list;
    node_t* curr;
};

list_t *list_new(){
   
    list_t* list = malloc(sizeof(list_t));
    if (!list) {
        return NULL;
    }
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    return list;
}

size_t list_length(const list_t *list){
    return list->size;
}

bool list_is_empty(const list_t *list){
    if(list->head == NULL) return true;
    return false;
}

bool list_insert_head(list_t *list, void *valor){

    node_t *insertion = malloc(sizeof(node_t));
    if (!insertion) return false;

    insertion->value = valor;
    insertion->next = NULL;
    insertion->prev = NULL;
    if (list->head == NULL) {
        list->head = insertion;
        list->tail = insertion;
    } else {
        insertion->next = list->head;
        list->head->prev = insertion;
        list->head = insertion;
    }
    list->size++;
    return true;
}

bool list_insert_tail(list_t *list, void *value){
    node_t*insertion=malloc(sizeof(node_t));
    if(!insertion)return false;
    insertion->value=value;
    insertion->next=NULL;
    if (list->head==NULL){
        insertion->prev = NULL;
        list->head=insertion;
        list->tail=insertion; 
        list->size++;
    }
    else{
        (list->tail)->next=insertion;
        insertion->prev = list->tail;
        list->tail=insertion;

        list->size ++;
    }

    return true;
}

void *list_peek_head(const list_t *list){

    if ((list->head)== NULL){
        return NULL;
    }
    else return (list->head)->value;
}


void *list_peek_tail(const list_t *list){
    
    if (list->head == NULL)return NULL;
    return list->tail->value;
}

void *list_pop_head(list_t *list){
    if (list->head == NULL)return NULL;

    void *value=list->head->value;
    node_t*head_anterior=list->head;
    list->head=list->head->next;
    if(list->head==NULL){
        list->tail=NULL;
    }
    else{list->head->prev=NULL;}
    list->size--;
   
    free(head_anterior);

    return value;
}

void *list_pop_tail(list_t *list){
    if (list->tail==NULL)return NULL;
    void *value=list->tail->value;
    node_t* nodo_ant=list->tail->prev;
    free(list->tail);
    list->tail=nodo_ant;
    if (nodo_ant != NULL){
    nodo_ant->next=NULL;
    }
    else{list->head=NULL;}
    list->size--;
    return value;
}

void list_destroy(list_t *list, void destroy_value(void *)) {
    while (list->head != NULL) {
        void *value = list_pop_head(list);
        if (destroy_value != NULL) {
            destroy_value(value);
        }
    }
    free(list);
}

list_iter_t *list_iter_create_head(list_t *list){

    list_iter_t*iterador= malloc(sizeof(list_iter_t));
    if(!iterador) return NULL;
    iterador->list= list;
    iterador->curr=list->head;

    return iterador;
}

list_iter_t *list_iter_create_tail(list_t *list){

    list_iter_t*iterador= malloc(sizeof(list_iter_t));
    if(!iterador) return NULL;
    iterador->list= list;
    iterador->curr=list->tail;

    return iterador;
}

bool list_iter_forward(list_iter_t *iter) {
    if (iter->curr == NULL || iter->curr->next == NULL) return false;
    iter->curr = iter->curr->next;
    return true;
}

bool list_iter_backward(list_iter_t *iter){
    if (iter->curr==NULL||iter->curr->prev== NULL)return false;
    iter->curr=(iter->curr)->prev;
    return true;
}

void *list_iter_peek_current(const list_iter_t *iter){
    if(iter->list->head==NULL)return NULL;
    return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter){
    if (iter == NULL || iter->list == NULL) return true;
    if (iter->curr == iter->list->tail) return true;
    return false;
}

bool list_iter_at_first(const list_iter_t *iter){
    if (iter == NULL || iter->list == NULL) return true;
    if (iter->curr == iter->list->head) return true;
    return false;
}

void list_iter_destroy(list_iter_t *iter) { 
    if (iter == NULL) {
        return;
    }
    free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value) {
    node_t *new = malloc(sizeof(node_t));
    if (!new) return false;

    new->value = value;

    if (iter->curr == NULL) {
        new->next = NULL;
        new->prev = NULL;
        iter->list->head = new;
        iter->list->tail = new;
        iter->curr = new;
    } else if (iter->curr->next == NULL) {
        iter->curr->next = new;
        new->prev = iter->curr;
        new->next = NULL;
        iter->list->tail = new;
    } else {
        new->prev = iter->curr;
        new->next = iter->curr->next;
        iter->curr->next->prev = new;
        iter->curr->next = new;
    }

    return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    node_t*new=malloc(sizeof(node_t));
    if(!new)return false;
    new->value=value;

    if (iter->curr==NULL){
        iter->curr=new;
        iter->curr->next=NULL;
        iter->curr->prev=NULL;
        iter->list->head=new;
        iter->list->tail=new;
    }
    else if(iter->curr->prev==NULL){
        iter->list->head=new;
        iter->curr->prev=new;
        new->prev=NULL;
        new->next=iter->curr;
    }
    else{
        iter->curr->prev->next=new;
        new->prev=iter->curr->prev;
        iter->curr->prev=new;
        new->next=iter->curr;
        
    }
    return true;
}


void *list_iter_delete(list_iter_t *iter){
    
    if (iter->list->head == NULL || iter->curr == NULL) return NULL;

    void *value = iter->curr->value;

    if (iter->curr->prev == NULL && iter->curr->next == NULL) {
        free(iter->curr);
        iter->list->head = NULL;
        iter->list->tail = NULL;
        iter->curr = NULL;
    } 
    else if (iter->curr->prev == NULL) {
        iter->list->head = iter->curr->next;
        iter->list->head->prev = NULL;
        free(iter->curr);
        iter->curr = iter->list->head;
    } 
    else if (iter->curr->next == NULL) {
        iter->list->tail = iter->curr->prev;
        iter->list->tail->next = NULL;
        free(iter->curr);
        iter->curr = iter->list->tail;
    } 
    else {
        iter->curr->prev->next = iter->curr->next;
        iter->curr->next->prev = iter->curr->prev;
        node_t *temp = iter->curr;
        iter->curr = iter->curr->next;
        free(temp);
    }

    iter->list->size--;
    return value;
}
