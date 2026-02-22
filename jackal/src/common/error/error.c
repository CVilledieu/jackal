#include "error.h"
#include <stdio.h>
#include <stdlib.h>

// Keeping error handling simple for now
// But implementing where needed for quicker refactor time
void SoftError(char* msg){
    printf("Error: %s\n", msg);
}

void CritErr(char* msg, char* details){
    printf("Critical error: %s,\n Additional details: %s\n", msg, details);
    exit(-1);
}