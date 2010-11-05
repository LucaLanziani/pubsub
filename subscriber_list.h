/* 
 * File:   subscriber_list.h
 * Author: mosca
 *
 * Created on 31 agosto 2010, 16.05
 */

#ifndef SUBSCRIBER_LIST_H
#define	SUBSCRIBER_LIST_H

#include "ps_types.h"

#define MAX_SUBSCRIBER_NAME_LENGHT 15

typedef char subscriber_name[MAX_SUBSCRIBER_NAME_LENGHT];

struct subscriber {
    subscriber_name name;
    update_fun update;
    struct subscriber* next;
    struct subscriber* prev;
};

typedef struct subscriber subscriber_t;
typedef subscriber_t* subscriber_p;

typedef struct subscribers {
    subscriber_p head;
    subscriber_p pointer;
    subscriber_p tail;
    int reverse;
} subscribers_t;

typedef subscribers_t* subscribers_p;

#endif  /*SUBSCRIBER_LIST_H_ */


PSErrors subscribers_list_new(subscribers_p*);

PSErrors subscriber_new(subscriber_p *);

PSErrors subscriber_init(subscriber_p, subscriber_name name, update_fun);

PSErrors subscriber_tail_add(subscribers_p, subscriber_p);
PSErrors subscriber_head_add(subscribers_p, subscriber_p);
PSErrors subscriber_delete(subscribers_p, subscriber_p);
PSErrors subscribers_delete(subscribers_p);

PSErrors subscriber_next(subscribers_p, subscriber_p, subscriber_p*);
PSErrors subscriber_prev(subscribers_p, subscriber_p, subscriber_p*);
PSErrors subscribers_head(subscribers_p, subscriber_p *);
PSErrors subscribers_tail(subscribers_p, subscriber_p *);

PSErrors subscriber_next_on_subscribers(subscribers_p, subscriber_p*);

int subscribers_is_reverse(subscribers_p);
PSErrors subscribers_reverse(subscribers_p);


//if the third parameter is NULL it return only true or false
PSErrors subscribers_by_name_find(subscribers_p, subscriber_name, subscriber_p *);
PSErrors subscriber_by_name_delete(subscribers_p, subscriber_name);


