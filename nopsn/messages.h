#pragma once

#include "core.h"
#include "dialog.h"
#include "includes.h"
#include "natives.h"
#include "patches.h"
#include "system.h"
#include "types.h"

using namespace Dialog;



void PrintToXMB(char* text)
{
	msgdialog_mode = MODE_STRING_OK;
	Show(text);

	/*
	msgdialog_mode = MODE_STRING_YESNO;
	ShowYESNO("Apply NoPSN Patch Now?");

	while(!Finished)
	{
		//
	}

	bool ret = YESNO; 
				
	End();
	*/
}


void PrintDebugStats(int type)
{
	char debug_stats[400];

	switch (type)
	{
		case SHORT:
			sprintf(debug_stats, "---[ NoPSN SPRX Debug Stats Output ]---\n\n\nCurrent App: %s [%s]\n\nTOC: %X\n\nProcess ID: %X\n\nParent Process ID: %X\n\nPPU GUID: %X\n\n", appName, GetCID(), toc, sys_process_getpid(), sys_process_getppid(), sys_process_get_ppu_guid());
			break;

		case LONG:
			sprintf(debug_stats, "---[ NoPSN SPRX Debug Stats Output ]---\n\n\nCurrent App: %s [%s]\n\nStatus [%X]\n\nTOC: %X\n\nProcess ID: %X     On Stack?: [%X]\n\nParent Process ID: %X     On Stack?: [%X]\n\nPPU GUID: %X\n\nCell Temp: [%i C]     RSX Temp [%i C]\n\n", appName, GetCID(), sys_process_get_status(sys_process_getpid()), toc, sys_process_getpid(), sys_process_is_stack((const void*)sys_process_getpid()), sys_process_getppid(), sys_process_is_stack((const void*)sys_process_getppid()), sys_process_get_ppu_guid(), GetTempCell(0), GetTempRSX(0));
			break;

		default:
			break;
	}

	PrintToXMB(debug_stats);
}
