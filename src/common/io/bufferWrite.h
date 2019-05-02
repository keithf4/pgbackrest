/***********************************************************************************************************************************
Buffer IO Write

Write to a Buffer object using the IoWrite interface.
***********************************************************************************************************************************/
#ifndef COMMON_IO_BUFFERWRITE_H
#define COMMON_IO_BUFFERWRITE_H

#include "common/io/write.h"

/***********************************************************************************************************************************
Constructor
***********************************************************************************************************************************/
IoWrite *ioBufferWriteNew(Buffer *buffer);

#endif
