#pragma once

#include "cell.h"
#include "types.h"



void sleep(usecond_t time) ;

//int console_write(const char * s);

u32 ReadMemU32(u32 address);


// 0=CELL/1=RSX
u64 sys_game_get_temperature(u32 _dev, u32 *_temp);
u32 GetTempCell(int unit);
u32 GetTempRSX(int unit);

/*
int sys_process_get_status(sys_pid_t pid);
*/

// 1=power,2=status or 3=disk
int sys_sm_request_led(int led_id, uint8_t led_action);
int sys_sm_control_led(uint8_t led_id, uint8_t led_action);
int ControlLED(uint8_t led, uint8_t action);

int sys_process_get_status(sys_pid_t pid);

s32 sys_process_get_paramsfo();

void GetProcessNumberOfObjects(u32 pid, size_t count);

/*
int Memcpy(void* destination, const void* source, size_t size);
*/

bool cstrcmp(const char* s1, const char* s2);


int sys_ppu_thread_exit();


void printf(int n,...);

//va (short version of sprintf) :
void* va(int n,...);






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
char * ReadHex(char * read, int start, int len, char * buf, int bufSize);



