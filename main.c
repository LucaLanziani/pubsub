#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "publisher_list.h"
#include "subscriber_list.h"

/*
  A couple of update functions
*/

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
    publishers_p list_of_publisher;

    publisher_p first_publisher, second_publisher, third_publisher;
  
    //instantiates a list of publisher
    publishers_list_new(&list_of_publisher);

    publisher_new(&first_publisher);
    publisher_init(first_publisher, "IPhone");
    publisher_tail_add(list_of_publisher, first_publisher);

    publisher_new(&second_publisher);
    publisher_init(second_publisher, "Android");
    publisher_tail_add(list_of_publisher, second_publisher);

    // same operations above done via a sigle function
    publisher_init_and_tail_add(list_of_publisher, &third_publisher, "Blackberry");


    //Add some subscribers to the above publisher
    publisher_create_and_add_subscriber(second_publisher, NULL, "Sub1: ", &update);
    publisher_create_and_add_subscriber(second_publisher, NULL, "Sub2: ", &update);
    publisher_create_and_add_subscriber(second_publisher, NULL, "Sub3: ", &update_test);
   
    publisher_create_and_add_subscriber(third_publisher, NULL, "foo: ", &update);
    publisher_create_and_add_subscriber(third_publisher, NULL, "bar: ", &update);
    publisher_create_and_add_subscriber(third_publisher, NULL, "foobar: ", &update_test);
   
    PSData_p data;
    ps_data_new_init_and_fill_with_string(&data,"--->Hello world");

    publisher_notify(second_publisher, data);
    
    strcpy(data->data,"Hello man\0");
    
    publisher_notify(third_publisher,data);
    
    
    //Addind a subscriber to a publisher via publisher name
    subscriber_p subscriber;
    subscriber_new(&subscriber);
    subscriber_init(subscriber, "Iphone_sub", &update);
    publisher_by_name_add_subscriber(list_of_publisher, "IPhone", subscriber);
    publisher_notify_by_name(list_of_publisher,"IPhone",data);
};

