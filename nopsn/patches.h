#pragma once

#include <stdio.h>

#include "nopsn.h"
#include "system.h"
#include "timer.h"

using namespace std;

// A few basic instructions
int nop = 0x60000000;
u64 bytes_false = 0x66616C7365;
u64 bytes_true = 0x747275650D;

// Virtual In-Memory Address Base
int offset_base = 0x00010000;


int offset_cid_NPEB02210 = 0x0026E7B1;// Blockbuster
int offset_cid_NPUP10042 = 0x00651EEF;// TuneIn Radio
int offset_cid_NPUP10028 = 0x01059278;// YouTube


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




//char* GetCID(int format)
char* GetCID()
{

	for (int i; i < 9; i++)
	{
		contentID_hex[i] = *(char*)(offset_cid_NPUP10028 + i);
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
	// Blockbuster
	cmp = cstrcmp(cid, "NPEB02210");
	if (cmp)
	{
		app currentApp = 
		{
			"Blockbuster",
			"NPEB02210",
			"4E5045423032323130",
			0x01059278,
			0x60000000,
			0x002B3B90,
			0x002CB578,
			0x0026C628,
			0x0026C684
		};

		// Read Current Values
		//memTemp[0] = *(int*)NPEB02210_a[0];

		// Set App Info In Memory
		appName = currentApp.name;
		appTOC = currentApp.toc;

		// Apply Patches
		//sleep(waitPatch);
		//WriteInt(NPEB02210_a[0], bytes_false);

		cmp = false;
	}

	// TuneIn Radio
	cmp = cstrcmp(cid, "NPUP10042");
	if (cmp)
	{
		app currentApp = 
		{
			"TuneIn Radio",
			"NPUP10042",
			"4E5055503130303432",
			0x00000000,
			0x00000000,
			0x00000000,
			0x0076E790,
			0x00000000,
			0x00000000
		};

		// Read Current Values
		//memTemp[0] = *(int*)NPUP10042_a[0];
		//memTemp[1] = *(int*)NPUP10042_a[1];
		//memTemp[2] = *(int*)NPUP10042_a[2];

		// Set App Info In Memory
		appName = currentApp.name;
		appTOC = currentApp.toc;

		// Apply Patches
		//sleep(waitPatch);
		//WriteInt(NPUP10042_a[0], nop);
		//WriteInt(NPUP10042_a[1], nop);
		//WriteInt(NPUP10042_a[2], nop);

		cmp = false;
	}
	
	// YouTube
	// NPEB01229 and NPJB00286 also share the same NPUP10028 ID.
	cmp = cstrcmp(cid, "NPUP10028");
	if (cmp)
	{
		app currentApp = 
		{
			"YouTube",
			"NPUP10028",
			"4E5055503130303238",
			0x00065F30,
			0x60000000,
			0x00000000,
			0x012A27F8,
			0x00000000,
			0x00000000
		};

		// Read Current Values
		//memTemp[0] = *(int*)NPUP10028_a[0];

		// Set App Info In Memory
		appName = currentApp.name;
		appTOC = currentApp.toc;
		
		// Apply Patches
		sleep(waitPatch);
		WriteInt(currentApp.patch_offset, currentApp.patch_bytes);

		cmp = false;

	}

}


