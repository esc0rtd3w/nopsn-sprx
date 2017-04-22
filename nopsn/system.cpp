#pragma once


#include "includes.h"
#include "system.h"
#include "types.h"




void sleep(usecond_t time) 
{
	sys_timer_usleep(time * 1000);
}

/*
int console_write(const char * s)
{ 
	uint32_t len;
	system_call_4(403, 0, (uint64_t) s, 32, (uint64_t) &len);
	return_to_user_prog(int);
}
*/


int sys_process_get_status(sys_pid_t pid)
{
	system_call_1(4, pid);
	return_to_user_prog(int);
}



// Directly Read From Memory
u32 ReadMemU32(u32 address)
{
	system_call_1(6, address);
	//std::reverse(mem, mem + 4);
	//return *(UINT32*)read;
	return_to_user_prog(int);
}


// 1=power,2=status or 3=disk
int sys_sm_request_led(int led_id, uint8_t led_action)
{
	system_call_2(385, led_id, led_action);
	return_to_user_prog(int);
}

// (STATUS),2 (POWER)(red, green, red+green combined: looks like yellow);
// 0,1,2,3 (off,on,blink fast, blink slow) 
int sys_sm_control_led(uint8_t led_id, uint8_t led_action)
{ 
	system_call_2(386, led_id, led_action);
	return_to_user_prog(int);
}

int ControlLED(uint8_t led, uint8_t action)
{
	sys_sm_control_led(led, action);
	return 0;
}


u64 GetParamSFO(uint8_t buffer)
{
    //system_call_2(30, sys_process_getpid(), buffer);
	//return_to_user_prog(u64);
}


void GetProcessNumberOfObjects(u32 pid, size_t* count)
{
	//sys_process_get_number_of_object(pid, count);
	//return_to_user_prog(int);
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




// Get Temperatures
// 0=CELL/1=RSX
u64 sys_game_get_temperature(u32 _dev, u32 *_temp)
{
	system_call_2(383, (u64)_dev, (u64)_temp);
	return_to_user_prog(u64);
}


u32 GetTempCell(int unit)
{
	u32 tempCell=0;

	switch (unit)
	{

		// Celcius
		case 0:
			sys_game_get_temperature(0, &tempCell);
			tempCell=tempCell>>24;
			break;
		// Farenheit
		case 1:
			sys_game_get_temperature(0, &tempCell);
			tempCell=tempCell>>24;
			tempCell=int(1.8f*(float)tempCell+32.f);
			break;

		default:
			break;
	}

	return tempCell;
}

u32 GetTempRSX(int unit)
{
	u32 tempRSX=0;

	switch (unit)
	{

		// Celcius
		case 0:
			sys_game_get_temperature(1, &tempRSX);
			tempRSX=tempRSX>>24;
			break;
		// Farenheit
		case 1:
			sys_game_get_temperature(1, &tempRSX);
			tempRSX=tempRSX>>24;
			tempRSX=int(1.8f*(float)tempRSX+32.f);
			break;

		default:
			break;
	}

	return tempRSX;
}


char* DecToString(int input)
{
	char* newByte;
	
	if (input == 48){ newByte = "0"; }
	if (input == 49){ newByte = "1"; }
	if (input == 50){ newByte = "2"; }
	if (input == 51){ newByte = "3"; }
	if (input == 52){ newByte = "4"; }
	if (input == 53){ newByte = "5"; }
	if (input == 54){ newByte = "6"; }
	if (input == 55){ newByte = "7"; }
	if (input == 56){ newByte = "8"; }
	if (input == 57){ newByte = "9"; }
	if (input == 65){ newByte = "A"; }
	if (input == 66){ newByte = "B"; }
	if (input == 67){ newByte = "C"; }
	if (input == 68){ newByte = "D"; }
	if (input == 69){ newByte = "E"; }
	if (input == 70){ newByte = "F"; }
	if (input == 71){ newByte = "G"; }
	if (input == 72){ newByte = "H"; }
	if (input == 73){ newByte = "I"; }
	if (input == 74){ newByte = "J"; }
	if (input == 75){ newByte = "K"; }
	if (input == 76){ newByte = "L"; }
	if (input == 77){ newByte = "M"; }
	if (input == 78){ newByte = "N"; }
	if (input == 79){ newByte = "O"; }
	if (input == 80){ newByte = "P"; }
	if (input == 81){ newByte = "Q"; }
	if (input == 82){ newByte = "R"; }
	if (input == 83){ newByte = "S"; }
	if (input == 84){ newByte = "T"; }
	if (input == 85){ newByte = "U"; }
	if (input == 86){ newByte = "V"; }
	if (input == 87){ newByte = "W"; }
	if (input == 88){ newByte = "X"; }
	if (input == 89){ newByte = "Y"; }
	if (input == 90){ newByte = "Z"; }

	return newByte;
}


char* HexToString(int input)
{
	char* newByte;
	
	if (input == 0x30){ newByte = "0"; }
	if (input == 0x31){ newByte = "1"; }
	if (input == 0x32){ newByte = "2"; }
	if (input == 0x33){ newByte = "3"; }
	if (input == 0x34){ newByte = "4"; }
	if (input == 0x35){ newByte = "5"; }
	if (input == 0x36){ newByte = "6"; }
	if (input == 0x37){ newByte = "7"; }
	if (input == 0x38){ newByte = "8"; }
	if (input == 0x39){ newByte = "9"; }
	if (input == 0x41){ newByte = "A"; }
	if (input == 0x42){ newByte = "B"; }
	if (input == 0x43){ newByte = "C"; }
	if (input == 0x44){ newByte = "D"; }
	if (input == 0x45){ newByte = "E"; }
	if (input == 0x46){ newByte = "F"; }
	if (input == 0x47){ newByte = "G"; }
	if (input == 0x48){ newByte = "H"; }
	if (input == 0x49){ newByte = "I"; }
	if (input == 0x4A){ newByte = "J"; }
	if (input == 0x4B){ newByte = "K"; }
	if (input == 0x4C){ newByte = "L"; }
	if (input == 0x4D){ newByte = "M"; }
	if (input == 0x4E){ newByte = "N"; }
	if (input == 0x4F){ newByte = "O"; }
	if (input == 0x50){ newByte = "P"; }
	if (input == 0x51){ newByte = "Q"; }
	if (input == 0x52){ newByte = "R"; }
	if (input == 0x53){ newByte = "S"; }
	if (input == 0x54){ newByte = "T"; }
	if (input == 0x55){ newByte = "U"; }
	if (input == 0x56){ newByte = "V"; }
	if (input == 0x57){ newByte = "W"; }
	if (input == 0x58){ newByte = "X"; }
	if (input == 0x59){ newByte = "Y"; }
	if (input == 0x5A){ newByte = "Z"; }

	return newByte;
}





