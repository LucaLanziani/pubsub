/* 
 * File:   main.c
 * Author: mosca
 *
 * Created on 15 agosto 2010, 12.51
 */

#include <stdio.h>
#include <stdlib.h>
#include "publisher_list.h"
#include "subscriber_list.h"

/*
 * 
 */

int update(PSData_p data) {
    printf("UPDATE %s\n", (char*) data->data);
};

int update_test(PSData_p data) {
    printf("UPDATE_TEST %s\n", (char*) data->data);
};

int main(int argc, char** argv) {
    publishers_p l_o_p;
    publisher_p I, N, T;


    publishers_list_new(&l_o_p);

    publisher_new(&I);
    publisher_init(I, "IPhone");
    publisher_tail_add(l_o_p, I);

    publisher_new(&N);
    publisher_init(N, "Naviga");
    publisher_tail_add(l_o_p, N);
 /*
    publisher_new(&T);
   
    publisher_init(T, "Test");
    publisher_tail_add(l_o_p, T);
*/
    PRINT_D("STO QUA");
    publisher_new_init_tail_add(l_o_p,"Naviga",&T);
    PRINT_D("T a quest punto vale %p",T);

    subscriber_p S1, S2, S3;
/*
    subscriber_new(&S1);
    subscriber_init(S1, "Sub1: ", &update);
    PRINT_D("primo test\n");
    subscriber_new(&S2);
    subscriber_init(S2, "Sub2: ", &update);
    PRINT_D("primo test\n");
    subscriber_new(&S3);
    subscriber_init(S3, "Sub3: ", &update_test);


    PRINT_D("INIZIO GLI ADD\n");
    publisher_add_subscriber(N, S1);
    publisher_add_subscriber(N, S2);
    publisher_add_subscriber(N, S3);
    PRINT_D("SECONDO ADD\n");
    publisher_add_subscriber(T, S1);
    publisher_add_subscriber(T, S2);
    publisher_add_subscriber(T, S3);
*/
    PRINT_D("non mi dire che segmenti qui...");
    publisher_add_and_create_subscriber(N,"Sub1: ", &update,NULL);
    publisher_add_and_create_subscriber(N,"Sub2: ", &update,NULL);
    publisher_add_and_create_subscriber(N,"Sub2: ", &update_test,NULL); //avendo messo lo stesso nome del precedente.. non viene aggiunto alla lista
    PRINT_D("non mi dire che segmenti qui...");
    publisher_add_and_create_subscriber(T,"Pippo: ", &update,NULL);
    publisher_add_and_create_subscriber(T,"Pluto: ", &update,NULL);
    publisher_add_and_create_subscriber(T,"Paperino: ", &update_test,NULL);
    PRINT_D("non mi dire che segmenti qui...");
    //vanno create le funzioni per gestire la truttura PSData_t
    PSData_p data;
    data=(PSData_p)calloc(1,sizeof(PSData_t));
    data->data=(char*)calloc(25,sizeof(char));
    strcpy(data->data,"Ciao Mondo");
    publisher_notify(N,data);

    PRINT_D("\nSeconda parte");
    strcpy(data->data,"Ciao Mondo1");
    publisher_notify(T,data);
    PRINT_D("Dovrebbero essere uguali")
    publisher_by_name_notify(l_o_p,"Test",data);
    PRINT_D("FINE\n");

};

