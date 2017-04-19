#pragma once

#include "includes.h"
#include "types.h"


int TOC;

int UNK_TEXT_1 = 0x009AAE9C;

// Memory Related
int addrTemp[] = {0x00000000};
int memTemp[] = {0x00000000};
char* appName = "";
char* contentID = "";
int contentID_hex[9];

// Used For Debug Stats
const int SHORT = 0;
const int LONG = 1;

// Bools for currently running app
bool isTuneInRadio = false;
bool isYouTube = false;

struct opd_s
{
	int32_t sub;
	int32_t toc;
};

struct timeval_32 {
	u32 tv_sec;
	s32 tv_usec;
};

// Directly Write To Memory
void WriteMemoryDirect(int address, int value);
