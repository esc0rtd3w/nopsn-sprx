#pragma once

// Original Source: https://pastebin.com/x6dTz0bC


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cell/http.h>
#include <netex/net.h>



#define HTTP_POOL_SIZE      (64 * 1024)
#define HTTP_POOL_BUFFER 0x2110000	// change this to an address with a free size of 0x10000 bytes ! This one is for ghosts 1.14
static char r_buffer[0x6000];	//MAX is 0x6000



void memCpy(void * destination, const void * source, size_t num);

void memFree(char* ptr, int len);

int strCmp(const char* str1, const char* str2);

void SendRequest(char* url,  char* retBuffer, int bufMaxLen);


