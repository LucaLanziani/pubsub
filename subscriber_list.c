/*
 * subscriber_list.c
 *
 *  Created on: 15/ago/2010
 *      Author: mosca
 */

#include "subscriber_list.h"

PSErrors subscribers_list_new(subscribers_p *temp_p) {
    *temp_p = (subscribers_p) calloc(1, sizeof (subscribers_t));
    subscribers_p temp = (*temp_p);

    temp->head = NULL;
    temp->pointer = NULL;
    temp->tail = NULL;
    temp->reverse = 0;
    return StatusOK;
};

PSErrors subscriber_new(subscriber_p *temp_p) {
    *temp_p = (subscriber_p) calloc(1, sizeof (subscriber_t));
    subscriber_p temp = (*temp_p);
    memset(temp->name, 0, sizeof (temp->name));
    temp->update = NULL;
    temp->next = NULL;
    temp->prev = NULL;
    return StatusOK;
};

PSErrors subscriber_init(subscriber_p s, subscriber_name name, update_fun update) {
    if ((s == NULL) || (name == NULL) || (update == NULL)) return params_error; //check parameters

    strncpy(s->name, name, MAX_SUBSCRIBER_NAME_LENGHT);
    if (MAX_SUBSCRIBER_NAME_LENGHT > 0) {
        s->name[MAX_SUBSCRIBER_NAME_LENGHT - 1] = '\0';
    };
    s->update = update;
    return StatusOK;
}

PSErrors subscriber_tail_add(subscribers_p ss, subscriber_p s) {
    if ((ss == NULL) && (s == NULL)) return params_error;
    if (subscribers_by_name_find(ss, s->name, NULL) == StatusOK) return duplicated_name;

    if (ss->tail == NULL) {
        ss->tail = s;
    } else {
        ss->tail->next = s;
        s->prev = ss->tail;
        ss->tail = s;
    }
    if (ss->head == NULL) {
        ss->head = s;
    }
    return StatusOK;
};

PSErrors subscriber_head_add(subscribers_p ss, subscriber_p s) {
    if ((ss == NULL) || (s == NULL)) return params_error;

    if (subscribers_by_name_find(ss, s->name, NULL) == StatusOK) return duplicated_name;

    if (ss->head == NULL) {
        ss->head = s;
        ss->head = s;
    } else {
        s->next = ss->head;
        ss->head = s;
    }
    return StatusOK;
};

PSErrors subscriber_delete(subscribers_p ss, subscriber_p s) {
    if ((ss == NULL) || (s == NULL)) return params_error;

    if (s->prev == NULL) {
        //The first element
        if (s->next == NULL) {
            //the only elemetn
            ss->head = NULL;
            ss->tail = NULL;
        } else {
            ss->head = s->next;
            s->next->prev = NULL;
        }
    } else {
        if (s->next == NULL) {
            //last element
            s->prev->next = s->next;
            ss->tail = s->prev;
        } else {

            s->prev->next = s->next;
            s->next->prev = s->prev;

        }
    }
    //free subscribers_list memory
    free(s);
    return StatusOK;
}

PSErrors subscribers_delete(subscribers_p ss) {
    subscriber_p temp_p, prev_p;
    subscribers_head(ss, &temp_p);
    while ((temp_p != NULL)) {
        prev_p = temp_p;
        subscriber_next(ss, temp_p, &temp_p);
        subscriber_delete(ss, prev_p);
    }
    free(ss);
    return StatusOK;
}

PSErrors subscriber_by_name_delete(subscribers_p ss, subscriber_name name) {
    if ((ss == NULL) || (name == NULL)) return params_error;

    subscriber_p s;
    PSErrors code;
    if ((code = subscribers_by_name_find(ss, name, &s)) == StatusOK) {
        return subscriber_delete(ss, s);
    } else {
        return code;
    }
}

PSErrors subscriber_next(subscribers_p ss, subscriber_p s, subscriber_p *next) {
    if ((ss == NULL) || (s == NULL)) return params_error;

    if (subscribers_is_reverse(ss)) {
        *next = s->prev;
    } else {
        *next = s->next;
    }
    return StatusOK;

};

PSErrors subscriber_prev(subscribers_p ss, subscriber_p s, subscriber_p *prev) {
    if ((ss == NULL) && (s == NULL)) return params_error;

    if (subscribers_is_reverse(ss)) {
        *prev = s->next;
    } else {
        *prev = s->prev;
    }
    return StatusOK;
};

PSErrors subscriber_next_on_subscribers(subscribers_p ss, subscriber_p *next) {
    if (ss == NULL) return params_error;

    if (ss->pointer == NULL) {
        if (subscribers_is_reverse(ss)) {
            ss->pointer = ss->tail;
        } else {
            ss->pointer = ss->head;
        }
    } else {
        subscriber_next(ss, ss->pointer, &(ss->pointer));
        *next = ss->pointer;
    }
    return StatusOK;
};

PSErrors subscribers_head(subscribers_p ss, subscriber_p *s) {
    if (ss == NULL) return params_error;
    if (subscribers_is_reverse(ss)) {
        *s = ss->tail;
    } else {
        *s = ss->head;
    }
    return StatusOK;
};

PSErrors subscribers_tail(subscribers_p ss, subscriber_p *s) {
    if (ss == NULL) return params_error;
    if (subscribers_is_reverse(ss)) {
        *s = ss->head;
    } else {
        *s = ss->tail;
    }
    return StatusOK;
};

int subscribers_is_reverse(subscribers_p ss) {
    if (ss == NULL) return params_error;
    return ss->reverse;
};

PSErrors subscribers_reverse(subscribers_p ss) {
    if (ss == NULL) return params_error;
    ss->reverse = !ss->reverse;
    return StatusOK;
};

PSErrors subscribers_by_name_find(subscribers_p ss, subscriber_name name, subscriber_p *s) {
    if ((ss == NULL) || (name == NULL)) return params_error;

    if (s != NULL) {
        *s = NULL;
    };

    subscriber_p temp_p;
    int found = 0;
    subscribers_head(ss, &temp_p);
    while ((temp_p != NULL) && (!found)) {
        if (strcmp(temp_p->name, name) == 0) {
            found = 1;
            if (s != NULL) *s = temp_p;
        } else {
            subscriber_next(ss, temp_p, &temp_p);
        }
    }

    if (found) {
        return StatusOK;
    } else {
        return not_found;
    }
};


