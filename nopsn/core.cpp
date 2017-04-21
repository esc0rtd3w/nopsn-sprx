#pragma once

#include "includes.h"
#include "types.h"



// Write Memory
void WriteInt(int address, int value)
{
	int memoryAddress = (*(int*)address) + 4;
	{
		if (memoryAddress != 0)
		{
			*(int*)address = value;
		}
	}
}


// Read Memory
int* ReadInt(int address, int length)
{
	int buffer[32];

	for (int i = 0; i < length; i++)
	{
		buffer[i] = *(int*)(address + (i * 0x04));
	}
	return buffer;
}






