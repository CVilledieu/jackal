#include "jackal/jackal.h"
#include <stdio.h>
#include <stdint.h>

typedef struct TestCase_t{
    uint32_t (*fnPtr)(void); fnPtr;
    char name[128];
} TestCase_t;

typedef struct TestList_t{
    TestCase_t* list;
    uint32_t length;
} TestList_t;

static inline void TestSection(TestList_t* list){
    for (int i = 0; i < list->length; i++){
    TestCase_t* test = &list->list[i];
        if(test->fnPtr){
            printf("Failed test: %s\n", test->name);
        } else {
            printf("Tested passed: %s\n", test->name);
        }
    }
    
}

int main(void){
    TestSection(TestSection_World());
}

