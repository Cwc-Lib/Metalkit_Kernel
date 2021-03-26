/* -*- Mode: C; c-basic-offset: 3 -*-
 *
 * Metalkit example: How to include compressed data files,
 * and decompress them using the 'puff' module.
 */

#include "types.h"
#include "console_vga.h"
#include "datafile.h"
#include "intr.h"
#include "XE-Loader.h"


DECLARE_DATAFILE(myFile, sample_txt);

static char output_buffer[64*1024];

int
main(void)
{
   uint32 len;

   ConsoleVGA_Init();
   Intr_Init();
   Intr_SetFaultHandlers(Console_UnhandledFault);
	
	Xe_LoadFile("Test.c");
	
	
   //len = DataFile_Decompress(myFile, output_buffer, sizeof output_buffer);
   //output_buffer[len] = '\0';
   //Console_WriteString(output_buffer);
   
   //Direct load
   Console_WriteString(myFile->ptr);
   Console_Flush();

   return 0;
}
