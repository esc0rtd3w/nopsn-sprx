#pragma once

#include "includes.h"
#include "types.h"


int TOC;

int UNK_TEXT_1 = 0x009AAE9C;

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



