/*
========= DEKAS
========= Realizacija studento nr. 1812983 (Programų sistemos, 1 k., 1 gr., 2 pogr.)
========= 2019 m.
*/

#include <stdlib.h>
#include "deque.h"

struct node_struct {
	struct node_struct *next;
	struct node_struct *prev;
	deque_val_type val;
};

struct deque_struct {
	struct node_struct *head;
	struct node_struct *tail;
	int Size;
};

deque * deque_alloc() {
	deque *d = (deque*)malloc(sizeof(deque)); // prirasyta (deque*)
	if (d != NULL)
		d->head = d->tail = NULL;
	d->Size = 0;
	return d;
}

void deque_free(deque *d) {
	struct node_struct *n = d->head;
	while(d->head != NULL) {
		if (d->head == d->tail)
			d->head = d->tail = NULL;
		else
			d->head = d->head->next;
		free(n);
		n = d->head;
	}
	d->Size = 0;
}

bool deque_is_empty(deque *d) {
	return d->head == NULL;
}

bool deque_is_full(deque *d) {
	struct node_struct *n = (node_struct*)malloc(sizeof(struct node_struct)); // prirasyta (node_struct*)
	if(n == NULL) return true;
	else {
		free(n);
		return false;
	}
}

void deque_push_front(deque *d, deque_val_type v) {
	struct node_struct *n = (node_struct*)malloc(sizeof(struct node_struct)); // prirasyta (node_struct*)
	n->val = v;
	n->next = d->head;
	n->prev = NULL;
	if (d->tail == NULL) {
		d->head = d->tail = n;
	} else {
		d->head->prev = n;
		d->head = n;
	}
	d->Size++;
}

void deque_push_back(deque *d, deque_val_type v) {
	struct node_struct *n = (node_struct*)malloc(sizeof(struct node_struct)); // prirasyta (node_struct*)
	n->val = v;
	n->prev = d->tail;
	n->next = NULL;
	if (d->head == NULL) {
		d->head = d->tail = n;
	} else {
		d->tail->next = n;
		d->tail = n;
	}
	d->Size++;
}

deque_val_type deque_pop_front(deque *d) {
	deque_val_type v = d->head->val;
	struct node_struct *n = d->head;
	if (d->head == d->tail)
		d->head = d->tail = NULL;
	else
		d->head = d->head->next;
	free(n);
	d->Size--;
	return v;
}

deque_val_type deque_pop_back(deque *d) {
	deque_val_type v = d->tail->val;
	struct node_struct *n = d->tail;
	if (d->head = d->tail)
		d->head = d->tail = NULL;
	else
		d->tail = d->tail->prev;
	free(n);
	d->Size--;
	return v;
}

deque_val_type deque_peek_front(deque *d) {
	return d->head->val;
}

deque_val_type deque_peek_back(deque *d) {
	return d->tail->val;
}

int deque_length(deque *d) {
	return d->Size;
}
