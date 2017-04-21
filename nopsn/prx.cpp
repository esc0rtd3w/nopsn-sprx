// Original code reference: http://www.nextgenupdate.com/forums/ps3-mods-cheats/749680-how-make-sprx-read-write-memory.html


// NoPSN SPRX

// esc0rtd3w 2017

// http://www.psx-place.com/threads/tutorial-psn-bypass-techniques-and-setting-up-development-debugging-environment.13287



#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include "core.h"
#include "dialog.h"
#include "includes.h"
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
	// While Thread Is Open
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
			
			// Stuff Below Will Run Once
			if (seenPatchMessage == 0)
			{
				// Wait For App To Load???
				sleep(200);
			
				// Get ContentID as String
				contentID = GetCID();

				// We like sleepy time ;)
				sleep(100);

				// Run Main No PSN Patch
				Patch(contentID);

				// Print Debug Message
				PrintDebugStats(SHORT);
				
				// Increase counter so this only runs once
				seenPatchMessage++;

			}// End of seenPatchMessage RunOnce


			// Run Stuff Here While Looping


		  }// End of IsTimerReady

	}// End of For(;;) Loop
	


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

	}// End of Thread Not Closed
		   
    sys_ppu_thread_exit();


}// End of NoPSN Thread


// NoAds Main Thread
void thread_noads(uint64_t arg)
{		
	// While Thread Is Open
	while (!threadClosed)
	{

	for (;;)
	{

      if (isTimerReady())
      {
		  // Exiting Thread Until We Have Something To Put Here!!!
		  sleep(200);
          sys_ppu_thread_exit();

      }// End of IsTimerReady

	}// End of For(;;) Loop
	

	// Run Stuff Here While Looping
	sleep(200);

	}// End of Thread Not Closed

    sys_ppu_thread_exit();


}// End of NoPSN Thread





extern "C" int _nopsn_main_prx_entry(void)
{
	// Test Message
	//cellMsgDialogOpen2(0, "This Is A Test", 0, 0, 0);
	
	// Create NoPSN Thread
	create_thread(thread_nopsn, 0x4AA, 0x6000, "NoPSN___MAIN");

	// Create NoAds Thread
	create_thread(thread_noads, 0x4AB, 0x6000, "NoPSN___AD_REMOVAL");

    return SYS_PRX_RESIDENT;
}


extern "C" int stop(void)
{
	//Kill your thread
	//Unhook your functions by restoring first 4 instructions
	threadClosed = true;
	return SYS_PRX_STOP_OK;
}