/*
========= DEKAS
========= Realizacija studento nr. 1812983 (Programų sistemos, 1 k., 1 gr., 2 pogr.)
========= 2019 m.
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEQUE_H
#define DEQUE_H
#include <stdbool.h> // prideda bool, true, false

/*Deko tipas deque*/
typedef struct deque_struct deque;

/*Pakeiskite šią eilutę į typedef X deque_val_type,
kur X yra kintamųjų, kuriuos naudosite dirbdami su deku, tipas*/
typedef bool deque_val_type;

/*================== FUNKCIJOS DARBUI SU DEKU ===========================*/
// Sukuria tučią deką
deque * deque_alloc();

// Ištrina deką
void deque_free(deque *d);

// Patikrina, ar dekas tuščias
bool deque_is_empty(deque *d);

// Patikrina, ar dekas pilnas
bool deque_is_full(deque *d);

// Įterpia elementą į deko pradžią
void deque_push_front(deque *d, deque_val_type v);

// Įterpia elementą į deko pabaigą
void deque_push_back(deque *d, deque_val_type v);

// Išima elementą iš deko pradžios
deque_val_type deque_pop_front(deque *d);

// Išima elementą iš deko pabaigos
deque_val_type deque_pop_back(deque *d);

// Grąžina elementą, esantį deko pradžioje
deque_val_type deque_peek_front(deque *d);

// Grąžina elementą, esantį deko pabaigoje
deque_val_type deque_peek_back(deque *d);

// Grąžina, kiek elementų yra deke
int deque_length(deque *d);

#endif
#ifdef __cplusplus

#endif
}
