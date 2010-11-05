/* 
 * File:   main.c
 * Author: mosca
 *
 * Created on 15 agosto 2010, 12.51
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publisher_list.h"
#include "subscriber_list.h"

/*
 * 
 */
//creo due esempi di funzioni da passare ai publisher
//potrebbero rappresentare funzioni dei vari subscriber
//ATTENZIONE TALI FUNZIONI PER CONVENZIONE DEVO RICEVERE UN PARAMETRO DI TIPO PSData_p
int update(PSData_p data) {
    if (data->DataType==char_ptr_t){
        printf("UPDATE %s\n", (char*) data->data);
        return StatusOK;
    } else return data_type_error;
};


int update_test(PSData_p data) {
    if (data->DataType==char_ptr_t){
        printf("UPDATE_TEST %s\n", (char*) data->data);
        return StatusOK;
    } else return data_type_error;
};

int main(int argc, char** argv) {
    publishers_p l_o_p;

    publisher_p I, N, T;

	//creo la lista dei publisher
    publishers_list_new(&l_o_p);
	
	//creo il publisher I
    publisher_new(&I);
	//Lo inizializzo dandogli un nome
    publisher_init(I, "IPhone");
	//Lo aggiungo alla lista l_o_p
    publisher_tail_add(l_o_p, I);

	//come sopra ma con il publisher N
    publisher_new(&N);
    publisher_init(N, "Naviga");
    publisher_tail_add(l_o_p, N);

	//Con una sola funzione creo il publisher gli assegno un nome e lo aggiungo in coda alla lista
    publisher_new_init_tail_add(l_o_p,"Naviga",&T);


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
   
	//aggiungo ad un publisher (in questo caso N) un subscriver
	//semplicemente passando il nome del subscriber e la funzione su cui riceverà le notifiche
    publisher_add_and_create_subscriber(N,"Sub1: ", &update,NULL);
    publisher_add_and_create_subscriber(N,"Sub2: ", &update,NULL);
    publisher_add_and_create_subscriber(N,"Sub3: ", &update_test,NULL); //avendo messo lo stesso nome del precedente.. non viene aggiunto alla lista
   
    publisher_add_and_create_subscriber(T,"Pippo: ", &update,NULL);
    publisher_add_and_create_subscriber(T,"Pluto: ", &update,NULL);
    publisher_add_and_create_subscriber(T,"Paperino: ", &update_test,NULL);
   
    //vanno create le funzioni per gestire la truttura PSData_t
    PSData_p data;
	ps_data_new_init_fill_with_string(&data,"--->Ciao Mondo");
/*
	data=(PSData_p)calloc(1,sizeof(PSData_t));
    data->data=(char*)calloc(25,sizeof(char));
    strcpy(data->data,"Ciao Mondo");
*/
    publisher_notify(N,data);
    PRINT_D("\nSeconda parte");
    strcpy(data->data,"Ciao Mondo1\0");
    PRINT_D("\nData=%s",(char *)data->data);
    publisher_notify(T,data);
    PRINT_D("Dovrebbero essere uguali")
    publisher_by_name_notify(l_o_p,"Naviga",data);
    PRINT_D("FINE\n");

};

