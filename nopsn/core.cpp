#pragma once

#include "includes.h"
#include "types.h"


using namespace std;


s32 write_process(u64 ea, const void * data, u32 size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (u64)data);
	return_to_user_prog(int32_t);
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

/*
float intArray[100];
float* ReadInt(int address, int length)
{
    for (int i = 0; i < length; i++)
    {
        intArray[i] =  *(int*)(address + (i * 0x04));
    }
    return intArray;
}
*/

int ReadInt32(int Address)
{
	return *(int*)Address;
}


float floatArray[100];
float* ReadFloat(int address, int length)
{
    for (int i = 0; i < length; i++)
    {
        floatArray[i] =  *(float*)(address + (i * 0x04));
    }
    return floatArray;
}


char byteArray[100];
char* ReadBytes(int address, int length)
{
	for (int i = 0; i < length; i++)
    {
        byteArray[i] =  *(char*)(address + (i));
    }
    return byteArray;
}


char returnRead[100];
char* ReadString(int address)
{
	memset(&returnRead[0], 0, sizeof(returnRead));
	int strlength = 100;
	char* StrBytes = ReadBytes(address, strlength);
	for (int i = 0; i < strlength; i++)
	{
		if (StrBytes[i] != 0x00)
			returnRead[i] = StrBytes[i];
	else
		break;
}
return returnRead;
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

/*
void WriteInt(int address, int* input, int length)
{
    for (int i = 0; i < length; i++)
    {
        *(int*)(intArray + (i * 0x04)) = input[i];
    }
}
*/

void WriteInt32(int Address, int Input)
{
	*(int*)Address = Input;
}


void WriteFloat(int address, float* input, int length)
{
	for (int i = 0; i < length; i++)
	{
		*(float*)(address + (i * 4)) = input[i];
	}
}


void WriteBytes(int address, char* input, int length)
{
    for (int i = 0; i < length; i++)
    {
        *(char*)(address + (i)) = input[i];
    }
}


void WriteString(int address, char* string)
{
	int FreeMem = 0x1D00000;
	int strlength = strlen(string);
	char* strpointer = *(char**)FreeMem = string;
	char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
	WriteBytes(address, StrBytes, strlength);
}




