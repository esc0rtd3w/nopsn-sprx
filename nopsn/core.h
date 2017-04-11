#pragma once

#include "cell.h"
#include "types.h"



//u64 process_id = sys_process_getpid();



struct opd_s
{
	int32_t sub;
	int32_t toc;
};


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


void sleep(usecond_t time) 
{
	sys_timer_usleep(time * 1000);
}


int console_write(const char * s)
{ 
	uint32_t len;
	system_call_4(403, 0, (uint64_t) s, 32, (uint64_t) &len);
	return_to_user_prog(int);
}

/*
int Memcpy(void* destination, const void* source, size_t size)
{
	
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}
*/

bool cstrcmp(const char* s1, const char* s2)
{
	while(*s1 && (*s1==*s2))
		s1++,s2++;
	if(*(const unsigned char*)s1-*(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}


int sys_ppu_thread_exit()
{
	system_call_1(41, 0);
	return_to_user_prog(int);
}


void printf(int n,...)
{
	void* lol;
	va_list a;
	va_start(a,n);
	lol = va_arg(a,void*);
        uint32_t len;
        system_call_4(403, 0, (uint64_t)lol, 32, (uint64_t) &len); 
	va_end(a);
}
//va (short version of sprintf) :

void* va(int n,...)
{
	void* buff;
	va_list a;
	va_start(a,n);
    buff =  va_arg(a,void*);
	va_end(a);
	return buff;
}






/*
 * Function:		ReadHex()
 * File:			main.c
 * Project:			ArtemisPS3-PRX
 * Description:		Converts a hex string into an array of bytes
 *					In cases where the len is less than 4, it will NOT (unlike ReadHexPartial) shift the value over such that something like "011" will be 0x01100000
 * Arguments:
 *	read:			buffer containing string
 *	start:			start index of conversion within buffer
 *	len:			length of hex string
 *	buf:			buffer that will store the resulting byte/char array after conversion
 *	bufSize:		allocated size of buf
 * Return:			Returns pointer to buf
 */
char * ReadHex(char * read, int start, int len, char * buf, int bufSize)
{
	for (int x = start; x < (len + start); x += 2)
	{
		buf[(x - start)/2] = (unsigned char)((((unsigned char)read[x] < 0x41) ? ((unsigned char)read[x] - 0x30) : ((unsigned char)read[x] - 0x37)) << 4) | (unsigned char)(((unsigned char)read[x+1] < 0x41) ? ((unsigned char)read[x+1] - 0x30) : ((unsigned char)read[x+1] - 0x37));
	}
	
	return buf;
}


