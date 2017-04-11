#pragma once

#include "nopsn.h"


// A few basic instructions
int nop = 0x60000000;


struct PatchInfo
{
	char* name;
	char* cid;
	char* region;
	int addr;
	int value;
};


// List of Regions
enum Region
{
	us,
	eu,
	jp,
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



// NoPSN Main Patch Function
void Patch(int cid)
{
	// Check App Name
	switch (cid) {

		// TuneIn Radio
		case NPUP10042:
			WriteMemoryDirect(NPUP10042_a[0], nop);
			WriteMemoryDirect(NPUP10042_a[1], nop);
			WriteMemoryDirect(NPUP10042_a[2], nop);
			break;

		// YouTube
		case NPUP10028:
			WriteMemoryDirect(NPUP10028_a[0], nop);
			break;
		case NPEB01229:
			WriteMemoryDirect(NPEB01229_a[0], nop);
			break;
		case NPJB00286:
			WriteMemoryDirect(NPJB00286_a[0], nop);
			break;

		default:
			break;
	};

}





