#ifndef DATAGEN_H
#define DATAGEN_H

#include <stdint.h>

typedef enum DataGenStatus {
    DG_Ok,
    DG_Err_InvalidSize,
    DG_Err_NullPtr
} DataGenStatus_t;

DataGenStatus_t FillArray(uint8_t* arr, int size);

int GetMaxDataSize();

#endif