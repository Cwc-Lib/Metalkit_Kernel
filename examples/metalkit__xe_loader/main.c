/* -*- Mode: C; c-basic-offset: 3 -*-
 *
 * Metalkit example: How to include compressed data files,
 * and decompress them using the 'puff' module.
 */

#include "types.h"
#include "console_vga.h"
#include "datafile.h"
#include "intr.h"
//#include "XE-Loader.h"
#include "XE/XE.h"


DECLARE_DATAFILE(myFile, sample_txt);

static char output_buffer[64*1024];


void fputc(){
	
}
void fputs(){
	
}

void cpc_Creer_Contexte(){
	
}

void cpc_Obtenir_Zone_Contexte(){
	
}

void cpc_Blitter(){
	
}
void dl_iterate_phdr(){
	
}
void __sched_getscheduler(){
	
}
void __sched_getparam(){
	
}
void sched_get_priority_max(){
	
}
void sched_get_priority_min(){
	
}
void __sched_setscheduler(){
	
}





int
main(void)
{
   uint32 len;

   ConsoleVGA_Init();
   Intr_Init();
   Intr_SetFaultHandlers(Console_UnhandledFault);


	Xe_Load("Test.exe");
	
	_printl("Finish");
	
   //len = DataFile_Decompress(myFile, output_buffer, sizeof output_buffer);
   //output_buffer[len] = '\0';
   //Console_WriteString(output_buffer);
   
   //Direct load
   //Console_WriteString(myFile->ptr);
   Console_Flush();

   return 0;
}
