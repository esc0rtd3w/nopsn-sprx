#pragma once

#include "nopsn.h"
#include "system.h"


// A few basic instructions
int nop = 0x60000000;

// Virtual In-Memory Address Base
int offset_base = 0x00010000;

// 4 Bytes (NPUP, NPUO, NPEB, NPEA, NPHA)
int offset_cid_region = 0x01059278;

// 5 Bytes For Number ID
int offset_cid_number = 0x0105927C;



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


const char* GetCID()
{
	for (int i; i < 9; i++)
	{
		contentID_hex[i] = *(char*)(offset_cid_region + i);
	}

	sleep(200);

	char buffer[32];
	sprintf(buffer, "%X%X%X%X%X%X%X%X%X", contentID_hex[0], contentID_hex[1], contentID_hex[2], contentID_hex[3], contentID_hex[4], contentID_hex[5], contentID_hex[6], contentID_hex[7], contentID_hex[8]);
	return buffer;
}


void GetPatchValues(int cid)
{
	switch (cid)
	{
		case NPUP10042:
		memTemp[0] = *(int*)NPUP10042_a[0];
		memTemp[1] = *(int*)NPUP10042_a[1];
		memTemp[2] = *(int*)NPUP10042_a[2];
		isTuneInRadio = true;
		appName = "TuneIn Radio";
		contentID = "NPUP10042";
		break;

		case NPUP10028:
		memTemp[0] = *(int*)NPUP10028_a[0];
		isYouTube = true;
		appName = "YouTube";
		contentID = "NPUP10028";
		break;

		case NPEB01229:
		memTemp[0] = *(int*)NPEB01229_a[0];
		isYouTube = true;
		appName = "YouTube";
		contentID = "NPEB01229";
		break;

		case NPJB00286:
		memTemp[0] = *(int*)NPJB00286_a[0];
		isYouTube = true;
		appName = "YouTube";
		contentID = "NPJB00286";
		break;
	}
}



// NoPSN Main Patch Function
void Patch(int cid)
{
	// Check Content ID
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


int GetTOC(int cid)
{
	int toc;

	// Check Content ID
	switch (cid) {

		// TuneIn Radio
		case NPUP10042:
			toc = 0x0076E790;
			break;

		// YouTube
		case NPUP10028:
			toc = 0x012A27F8;
			break;
		case NPEB01229:
			toc = 0x012A27F8;
			break;
		case NPJB00286:
			toc = 0x012A27F8;
			break;

		default:
			break;
	};


	return toc;
}


