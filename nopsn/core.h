#pragma once

#include "includes.h"
#include "types.h"


// For Addresses
int TOC;

// For Patch Info
int toc;


int UNK_TEXT_1 = 0x009AAE9C;


// Memory Related
int addrTemp[] = {0x00000000};
int memTemp[] = {0x00000000};
char* appName = "";
char* contentID = "";
int contentID_hex[9];
//u8 paramSFO;

// Used For Debug Stats
const int SHORT = 0;
const int LONG = 1;


struct opd_s
{
	int32_t sub;
	int32_t toc;
};

struct timeval_32 {
	u32 tv_sec;
	s32 tv_usec;
};


s32 write_process(u64 ea, const void * data, u32 size);

void WriteInt(int address, int value);
void WriteInt32(int Address, int Input);
void WriteFloat(int address, float* input, int length);
void WriteBytes(int address, char* input, int length);
void WriteString(int address, char* string);

int* ReadInt(int address, int length);
int ReadInt32(int Address);
float* ReadFloat(int address, int length);
char* ReadBytes(int address, int length);
char* ReadString(int address);

