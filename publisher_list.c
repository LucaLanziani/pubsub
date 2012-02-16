/*
 * publisher_list.c
 *
 *  Created on: 15/ago/2010
 *      Author: mosca
 */

#include "publisher_list.h"

PSErrors publishers_list_new(publishers_p *temp_p) {
    *temp_p = (publishers_p) calloc(1, sizeof (publishers_t));
    publishers_p temp = (*temp_p);

    temp->head = NULL;
    temp->pointer = NULL;
    temp->tail = NULL;
    temp->reverse = 0;
    return StatusOK;
};

PSErrors publisher_new(publisher_p *temp_p) {
    *temp_p = (publisher_p) calloc(1, sizeof (publisher_t));
    publisher_p temp = (*temp_p);
    memset(temp->name, 0, sizeof (temp->name));
    temp->next = NULL;
    temp->prev = NULL;
    return StatusOK;
};

PSErrors publisher_init(publisher_p p, publisher_name name) {
    if ((p == NULL) || (name == NULL)) return params_error; //check parameters
    subscribers_list_new(&p->subscribers);
    strncpy(p->name, name, MAX_PUBLISHER_NAME_LENGHT);
    if (MAX_PUBLISHER_NAME_LENGHT > 0) {
        p->name[MAX_PUBLISHER_NAME_LENGHT - 1] = '\0';
    };
    return StatusOK;
}

PSErrors publisher_new_init_tail_add(publishers_p ps,publisher_name name,publisher_p* p) {
    if ((ps == NULL) || (name == NULL)) return params_error;
    PSErrors result;
    publisher_p temp_p;
   
    if ((result=publisher_new(&temp_p))!=StatusOK) return result;

    if ((result=publisher_init(temp_p,name))!=StatusOK) return result;
 
    if (p!=NULL) *p=temp_p;
    return publisher_tail_add(ps,temp_p);
};

PSErrors publisher_tail_add(publishers_p ps, publisher_p p) {
    if ((ps == NULL) && (p == NULL)) return params_error;

    if (publishers_by_name_find(ps, p->name, NULL) == StatusOK) return duplicated_name;

    if (ps->tail == NULL) {
        ps->tail = p;
    } else {
        ps->tail->next = p;
        p->prev = ps->tail;
        ps->tail = p;
    }
    if (ps->head == NULL) {
        ps->head = p;
    }
    return StatusOK;
};

PSErrors publisher_head_add(publishers_p ps, publisher_p p) {
    if ((ps == NULL) || (p == NULL)) return params_error;

    if (publishers_by_name_find(ps, p->name, NULL) == StatusOK) return duplicated_name;

    if (ps->head == NULL) {
        ps->head = p;
    } else {
        ps->head->prev = p;
        p->next = ps->head;
        ps->head = p;
    }
    if (ps->tail==NULL) {
        ps->tail = p;
    }
    return StatusOK;
};

PSErrors publisher_delete(publishers_p ps, publisher_p p) {
    if ((ps == NULL) || (p == NULL)) return params_error;

    if (p->prev == NULL) {
        //The first element
        if (p->next == NULL) {
            //the only elemetn
            ps->head = NULL;
            ps->tail = NULL;
        } else {
            ps->head = p->next;
            p->next->prev = NULL;
        }
    } else {
        if (p->next == NULL) {
            //last element
            p->prev->next = p->next;
            ps->tail = p->prev;
        } else {

            p->prev->next = p->next;
            p->next->prev = p->prev;

        }
    }
    //free subscribers_list memory
    subscribers_delete(p->subscribers);
    free(p);
    return StatusOK;
}

PSErrors publishers_delete(publishers_p ps) {
    publisher_p temp_p, prev_p;
    publishers_head(ps, &temp_p);
    while ((temp_p != NULL)) {
        prev_p = temp_p;
        publisher_next(ps, temp_p, &temp_p);
        publisher_delete(ps, prev_p);
    }
    free(ps);
    return StatusOK;
}

PSErrors publisher_by_name_delete(publishers_p ps, publisher_name name) {
    if ((ps == NULL) || (name == NULL)) return params_error;

    publisher_p p;
    PSErrors code;
    if ((code = publishers_by_name_find(ps, name, &p)) == StatusOK) {
        return publisher_delete(ps, p);
    } else {
        return code;
    }
}

PSErrors publisher_next(publishers_p ps, publisher_p p, publisher_p *next) {
    if ((ps == NULL) || (p == NULL)) return params_error;

    if (publishers_is_reverse(ps)) {
        *next = p->prev;
    } else {
        *next = p->next;
    }
    return StatusOK;

};

PSErrors publisher_prev(publishers_p ps, publisher_p p, publisher_p *prev) {
    if ((ps == NULL) && (p == NULL)) return params_error;

    if (publishers_is_reverse(ps)) {
        *prev = p->next;
    } else {
        *prev = p->prev;
    }
    return StatusOK;
};

PSErrors publisher_next_on_publishers(publishers_p ps, publisher_p *next) {
    if (ps == NULL) return params_error;

    if (ps->pointer == NULL) {
        if (publishers_is_reverse(ps)) {
            ps->pointer = ps->tail;
        } else {
            ps->pointer = ps->head;
        }
    } else {
        publisher_next(ps, ps->pointer, &(ps->pointer));
        *next = ps->pointer;
    }
    return StatusOK;
};

PSErrors publishers_head(publishers_p ps, publisher_p *p) {
    if (ps == NULL) return params_error;
    if (publishers_is_reverse(ps)) {
        *p = ps->tail;
    } else {
        *p = ps->head;
    }
    return StatusOK;
};

PSErrors publishers_tail(publishers_p ps, publisher_p *p) {
    if (ps == NULL) return params_error;
    if (publishers_is_reverse(ps)) {
        *p = ps->head;
    } else {
        *p = ps->tail;
    }
    return StatusOK;
};

int publishers_is_reverse(publishers_p ps) {
    if (ps == NULL) return params_error;
    return ps->reverse;
};

PSErrors publishers_reverse(publishers_p ps) {
    if (ps == NULL) return params_error;
    ps->reverse = !ps->reverse;
    return StatusOK;
};

PSErrors publishers_by_name_find(publishers_p ps, publisher_name name, publisher_p *p) {
    if ((ps == NULL) || (name == NULL)) return params_error;

    if (p != NULL) *p = NULL;

    publisher_p temp_p;
    int found = 0;
    publishers_head(ps, &temp_p);
    while ((temp_p != NULL) && (!found)) {
        if (strcmp(temp_p->name, name) == 0) {
            found = 1;
            if (p != NULL) *p = temp_p;
        } else {
            publisher_next(ps, temp_p, &temp_p);
        }
    }

    if (found) {
        return StatusOK;
    } else {
        return not_found;
    }
};

PSErrors publisher_by_name_add_subscriber(publishers_p ps, publisher_name name, subscriber_p s) {
    if ((ps == NULL) || (name == NULL) || (s == NULL)) return params_error;
    publisher_p p;
    PSErrors code;
    if ((code = publishers_by_name_find(ps, name, &p)) == StatusOK) {
        return subscriber_tail_add(p->subscribers, s);
    } else {
        return code;
    }
}

PSErrors publisher_add_subscriber(publisher_p p, subscriber_p s) {
    if ((p == NULL) || (s == NULL)) return params_error;
    return subscriber_tail_add(p->subscribers, s);
}

PSErrors publisher_add_and_create_subscriber(publisher_p p,subscriber_name name,update_fun update,subscriber_p *s) {
    if ((p == NULL) || (name == NULL) || (update==NULL)) return params_error;
    PSErrors result;
    subscriber_p temp_s;
    if ((result=subscriber_new(&temp_s))!=StatusOK) return result;
    if ((result=subscriber_init(temp_s,name,update))!=StatusOK) return result;
    if (s!=NULL) *s=temp_s;
    return publisher_add_subscriber(p,temp_s);
};



PSErrors publisher_reset_pointer(publishers_p ps) {
    if ((ps == NULL)) return params_error;
    ps->pointer=NULL;
    return StatusOK;
}

PSErrors publisher_notify(publisher_p p, PSData_p d) {
    if ((p == NULL) || (d==NULL)) return params_error;
    subscriber_p temp_s;
    subscribers_head(p->subscribers,&temp_s);
    while (temp_s != NULL) {
        PRINT_D("Sono il publisher %s e sto notificando a %s",p->name,temp_s->name);
        temp_s->update(d);
        subscriber_next(p->subscribers,temp_s,&temp_s);
    }
    return StatusOK;
}

PSErrors publisher_by_name_notify(publishers_p ps, publisher_name name, PSData_p d){
    if ((ps==NULL) || (d==NULL)) return params_error;
    PSErrors result;
    publisher_p p;
    if ((result==publishers_by_name_find(ps,name,&p))!=StatusOK) return result;
    return publisher_notify(p,d);
    
};

/*
PSErrors publisher_notify_test_add_subscriber_name(publisher_p p, PSData_p d) {
    if ((p == NULL) || (d==NULL)) return params_error;
    subscriber_p temp_s;
    PSData_p temp_d;
    temp_d=(PSData_p)calloc(1,sizeof(PSData_t));
    subscribers_head(p->subscribers,&temp_s);
    while (temp_s != NULL) {
        //creo la stringa di dimensioni adatte a contenere il nome del subscriber e i dati mandati in precedenza
        temp_d->data=malloc((sizeof(d->data)+sizeof(temp_s->name)+10)*sizeof(char));
        strcat(temp_d->data,temp_s->name);
        strcat(temp_d->data," ");
        strcat(temp_d->data,d->data);
        temp_s->update(temp_d);
        subscriber_next(p->subscribers,temp_s,&temp_s);
    }
    return StatusOK;
};

PSErrors publisher_notify_test(publisher_p p) {
    subscriber_p temp_s;
    PSData_p data;
    data = (PSData_p) calloc(1, sizeof (PSData_t));
    data->data = (char*) calloc(25, sizeof (PSData_t));
    temp_s = p->subscribers->head;

    while (temp_s != NULL) {
        memset(data->data,'\0',sizeof(data->data));
        strcat(data->data, temp_s->name);
        strcat(data->data, p->name);

        temp_s->update(data);
        temp_s = temp_s->next;
    }
    return StatusOK;
}
 */