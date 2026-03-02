#include "frame.h"





void InitFrameData(Frame_t* frameData){
    InitMapMesh(frameData->map);
    InitEntityMesh(frameData->entity);
}