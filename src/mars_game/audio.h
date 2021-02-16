#include "amio_lib.h"
#include "conio.h"

typedef struct
{
    SIGNAL drums;
    long int ridx;
    float volume;
    float pan;
    char message[20];
}
USERDATA;
