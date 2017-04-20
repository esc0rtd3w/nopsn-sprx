#pragma once

#include <stdio.h>

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


char* DecToString(int input);
char* HexToString(int input);


