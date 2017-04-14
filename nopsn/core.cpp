#pragma once

#include "cell.h"
#include "types.h"



// Directly Write To Memory
void WriteMemoryDirect(int address, int value)
{
	int memoryAddress = (*(int*)address) + 4;
	{
		if (memoryAddress != 0)
		{
			*(int*)address = value;
		}
	}
}







