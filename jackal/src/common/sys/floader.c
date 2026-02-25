#include "floader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX_PATH_LENGTH 260
char appRoot[MAX_PATH_LENGTH];
int pathLength = 0;

// Caller is responsible for freeing memory
uint32_t GetFileData(uint8_t** dest, const char* destDir, const char* fName){
    if (dest == NULL || fName == NULL) {
        return 0;
    }

    char fullPath[MAX_PATH_LENGTH];
    snprintf(fullPath, MAX_PATH_LENGTH, "%s%s%s", appRoot, destDir, fName);
    
    FILE* fp = fopen(fullPath, "rb");
    if(fp == NULL){
        CritErr("Unable to open file.", fullPath);
    }

    fseek(fp, 0, SEEK_END);
    uint32_t size = ftell(fp);
    rewind(fp);
    
    *dest = malloc(size + 1);
    if (*dest == NULL) {
        fclose(fp);
        return 0;
    }

    fread(*dest, 1, size, fp);
    (*dest)[size] = 0;
    fclose(fp);

    return size;
}


FILE* StreamFileData(const char* destDir, const char* fileName){
    char absPath[MAX_PATH_LENGTH];
    snprintf(absPath, MAX_PATH_LENGTH, "%s%s%s", appRoot, destDir, fileName);
    FILE* fp = fopen(absPath, "rb");
    return fp;
}


void GetPathData(void){
    // Load full app path into buffer. This includes .exe file
    #ifdef _WIN32
        GetModuleFileNameA(NULL, appRoot, MAX_PATH_LENGTH);
    #else
        readlink("/proc/self/exe", appRoot, MAX_PATH_LENGTH);
    #endif

    // Remove .exe file from path so its just the root directory
    for(int i = 0; i < MAX_PATH_LENGTH; i++){
        if(appRoot[i] == '\\' ){
            pathLength = i;
            // appPath[i] = '/';
            continue;
        } else if(appRoot[i] == '.'){
            appRoot[pathLength+1] = '\0';
            break;
        }
    }

}


