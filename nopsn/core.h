#pragma once

#include <sysutil/sysutil_msgdialog.h>




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

