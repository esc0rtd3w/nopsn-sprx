// Original code reference: http://www.nextgenupdate.com/forums/ps3-mods-cheats/749680-how-make-sprx-read-write-memory.html


// NoPSN SPRX

// esc0rtd3w 2017

// http://www.psx-place.com/threads/tutorial-psn-bypass-techniques-and-setting-up-development-debugging-environment.13287



#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include "cell.h"
#include "core.h"
#include "dialog.h"
#include "messages.h"
#include "natives.h"
#include "patches.h"
#include "system.h"
#include "timer.h"

using namespace std;
using namespace Dialog;



// Create Thread Function
sys_ppu_thread_t id;

sys_ppu_thread_t create_thread(void (*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{	
	if(sys_ppu_thread_create(&id, entry, 0, priority , stacksize, 0, threadname) != CELL_OK)
	{
		//console_write("Thread creation failed\n");	
	}
	else
	{
		//console_write("Thread created\n");	
	}	
    return id;
}

// Module Info [name, attribute, major, minor]
SYS_MODULE_INFO( nopsn, 0, 0, 1);

// Module Start [funcname]
SYS_MODULE_START( _nopsn_main_prx_entry );

// Declare Library?? [libname, attribute, stubfile]
SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );

// Export Library Functions?? [funcname, libname]
SYS_LIB_EXPORT( _nopsn_export_function, LIBNAME );
SYS_LIB_EXPORT( _noads_export_function, LIBNAME );


// NoPSN Export Function
extern "C" int _nopsn_export_function(void)
{
    return CELL_OK;
}

// NoAds Export Function
extern "C" int _noads_export_function(void)
{
    return CELL_OK;
}


bool threadClosed = false;

// NoPSN Main Thread
void thread_nopsn(uint64_t arg)
{		

	while (!threadClosed)
	{
		
		// Writing To Memory
		// 1 byte - *(char*)0x0000000 = 0x01; //Yes this is literately how you write the memory in C++.
		// 2 bytes - *(short*)0x00000000 = 0x01;
		// 3 bytes - *(float*)0x00000000 = 0x01;
		// 4 bytes - *(int*)0x00000000 = 0x01;
		// 8 bytes - *(double*)0x00000000 = 0x01;

		int seenPatchMessage = 0;

		for (;;)
		{
		  if (isTimerReady())
		  {

			if (seenPatchMessage == 0)
			{

				//PrintToXMB("YouTube NoPSN Patch Successfully Applied");

				//sys_spu_elf_get_information();

				//int buf;

				

				// Fahrenheit
				//tempCell=int(1.8f*(float)temp+32.f);
				//tempRSX=int(1.8f*(float)temp+32.f);

				char pid[255];
				//sprintf(pid, "---[ NoPSN SPRX Debug Stats Output ]---\n\n\nTOC: %X\n\nProcess Name: %s\n\nProcess ID: %X     On Stack?: [%X]\n\nParent Process ID: %X     On Stack?: [%X]\n\nPPU GUID: %X\n\n", GetTOC(NPUP10028), (char*)sys_process_get_id(sys_process_getpid(), (u32*)500, 500, (size_t*)500), sys_process_getpid(), sys_process_is_stack((const void*)sys_process_getpid()), sys_process_getppid(), sys_process_is_stack((const void*)sys_process_getppid()), sys_process_get_ppu_guid());
				sprintf(pid, "---[ NoPSN SPRX Debug Stats Output ]---\n\n\nTOC: %X\n\nProcess Name: %s\n\nProcess ID: %X     On Stack?: [%X]\n\nParent Process ID: %X     On Stack?: [%X]\n\nPPU GUID: %X\n\nCell Temp: [%i C]     RSX Temp [%i C]\n\n", GetTOC(NPUP10028), "", sys_process_getpid(), sys_process_is_stack((const void*)sys_process_getpid()), sys_process_getppid(), sys_process_is_stack((const void*)sys_process_getppid()), sys_process_get_ppu_guid(), GetTempCell(), GetTempRSX());
				PrintToXMB(pid);
				
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

				
				seenPatchMessage++;

			}

			



			// TuneIn Radio
			//sleep(waitPatch);
			//Patch(NPUP10042);

			// YouTube
			//GetTOC(NPUP10028);
			//GetTOC(NPEB01229);
			//GetTOC(NPJB00286);

			sleep(waitPatch);
			Patch(NPUP10028);
			Patch(NPEB01229);
			Patch(NPJB00286);
			
			//YouTube::UNK_TEXT_1("", 0, 0, 0, 0);
			
			
		  }
	}
	


	/* 
	// Reading From Memory
	// 1 byte - *(char*)0x0000000;
	// 2 bytes - *(short*)0x00000000;
	// 3 bytes - *(float*)0x00000000;
	// 4 bytes - *(int*)0x00000000;
	// 8 bytes - *(double*)0x00000000;

	for (;;)
	{
      if (InGame())
      {
           sleep(5000);

           if (*(char*)0x1786418 == 63)
           {
				*(char*)0x1786418 = 0x40;
           }
           else 
           { 
			   *(char*)0x1786418 = 0x3F; //Obviously this wouldn't work because it would turn it on and off every 5 seconds
		   }
      }
	}
	*/

	sleep(200);

	}
		   
    sys_ppu_thread_exit();


}


// NoAds Main Thread
void thread_noads(uint64_t arg)
{		
	while (!threadClosed)
	{

	for (;;)
	{
      if (isTimerReady())
      {
		  sleep(200);
          sys_ppu_thread_exit();
      }
	}
	



	sleep(200);

	}

    sys_ppu_thread_exit();


}





extern "C" int _nopsn_main_prx_entry(void)
{
	// Test Message
	//cellMsgDialogOpen2(0, "This Is A Test", 0, 0, 0);
	
	// Create NoPSN Thread
	create_thread(thread_nopsn, 0x4AA, 0x6000, "NoPSN___MAIN");

	// Create NoAds Thread
	create_thread(thread_noads, 0x4AB, 0x6000, "NoPSN___AD_REMOVAL");
	return 0;

    return SYS_PRX_RESIDENT;
}


extern "C" int stop(void)
{
	//Kill your thread
	//Unhook your functions by restoring first 4 instructions
	threadClosed = true;
	return SYS_PRX_STOP_OK;
}