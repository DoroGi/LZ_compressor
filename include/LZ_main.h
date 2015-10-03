#ifndef LZ_MAIN_H
#define LZ_MAIN_H

#include "compressor.h"
#include "LZ_78.h"
#include "LZ_W.h"

class Compressor;
class LZ78Compressor;
class LZWCompressor;

void ShowMenu(void);
void LaunchCompressor(int choice1);
void LaunchOperation (Compressor& Compressor, int choice2);

void ShowHelp(void);
void ShowCompressorMenu(void);

#endif // LZ_MAIN_H
