#pragma once

#include <stdio.h>

#include "nopsn.h"
#include "system.h"
#include "timer.h"

using namespace std;

// A few basic instructions
int nop = 0x60000000;

// Virtual In-Memory Address Base
int offset_base = 0x00010000;

// 4 Bytes (NPEA, NPEB, NPHA, NPUO, NPUP)
int offset_cid_region = 0x01059278;

// 5 Bytes For Number ID
int offset_cid_number = 0x0105927C;


const int HEX = 0;
const int STRING = 1;

bool cmp = false;


// List of Regions
enum Region
{
	NPEA,
	NPEB,
	NPHA,
	NPUO,
	NPUP,
};

// List of all PSN Apps by NAME
enum Name
{
	tunein_radio,
	youtube,
};


// List of all PSN Apps by CONTENT_ID
enum ContentID
{
	NPUP10028,// YouTube
	NPUP10042,// TuneIn Radio
	NPEB01831,// TuneIn Radio
	NPEB01229,// YouTube
	NPJB00286,// YouTube
};


//char* GetCID(int format)
char* GetCID()
{
	
	for (int i; i < 9; i++)
	{
		contentID_hex[i] = *(char*)(offset_cid_region + i);
	}

	sleep(200);
	
	char buffer[32];
	sprintf(buffer, "%c%c%c%c%c%c%c%c%c", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);

	/*
	switch (format)
	{
		case HEX:
			sprintf(buffer, "%X%X%X%X%X%X%X%X%X", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);
			break;
		
		case STRING:
			sprintf(buffer, "%c%c%c%c%c%c%c%c%c", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);
			break;

		default:
			break;
	}
	*/
	
	return buffer;
}


// NoPSN Main Patch Function
//void Patch(char* cid, bool active)
void Patch(char* cid)
{
	cmp = cstrcmp(cid, "NPUP10042");
	if (cmp)
	{
		memTemp[0] = *(int*)NPUP10042_a[0];
		sleep(200);
		memTemp[1] = *(int*)NPUP10042_a[1];
		sleep(200);
		memTemp[2] = *(int*)NPUP10042_a[2];
		sleep(200);
		appName = "TuneIn Radio";
		toc = 0x0076E790;

		sleep(waitPatch);
		WriteMemoryDirect(NPUP10042_a[0], nop);
		sleep(500);
		WriteMemoryDirect(NPUP10042_a[1], nop);
		sleep(500);
		WriteMemoryDirect(NPUP10042_a[2], nop);

		cmp = false;
	}
	
	// NPEB01229 and NPJB00286 also share the same NPUP10028 ID.
	cmp = cstrcmp(cid, "NPUP10028");
	if (cmp)
	{
		memTemp[0] = *(int*)NPUP10028_a[0];
		sleep(200);
		appName = "YouTube";
		toc = 0x012A27F8;
		
		sleep(waitPatch);
		WriteMemoryDirect(NPUP10028_a[0], nop);

		cmp = false;

	}

}


