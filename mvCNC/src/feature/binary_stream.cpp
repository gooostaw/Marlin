/**
 * Modern Vintage CNC Firmware
*/

#include "../inc/mvCNCConfigPre.h"

#if ENABLED(BINARY_FILE_TRANSFER)

#include "../sd/cardreader.h"
#include "binary_stream.h"

char* SDFileTransferProtocol::Packet::Open::data = nullptr;
size_t SDFileTransferProtocol::data_waiting, SDFileTransferProtocol::transfer_timeout, SDFileTransferProtocol::idle_timeout;
bool SDFileTransferProtocol::transfer_active, SDFileTransferProtocol::dummy_transfer, SDFileTransferProtocol::compression;

BinaryStream binaryStream[NUM_SERIAL];

#endif
