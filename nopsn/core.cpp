#pragma once

#include "includes.h"
#include "types.h"



s32 write_process(u64 ea, const void * data, u32 size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (u64)data);
	return_to_user_prog(int32_t);
}


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






