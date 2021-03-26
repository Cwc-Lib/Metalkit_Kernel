/*  -== Xternal ==-
 *
 *  Utility and functions that rely on external libs for common usage
 *
 *  @autors
 *   - Maeiky
 *  
 * Copyright (c) 2021 - V·Liance
 *
 * The contents of this file are subject to the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * If a copy of the Apache License Version 2.0 was not distributed with this file,
 * You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.html
 *
*/
#include "xIO.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> //va_list //va_start //va_end

#ifdef D_Platform_Windows
	//#include <windows.h>
	imp_std void Sleep(uint32_t _millisecond); //-lKernel32
#endif

fn void _Sleep(uint32_t _millisecond){
	#ifdef D_Platform_Windows
		Sleep(_millisecond); //-lKernel32
	#endif
}

fn void _exit_FAILURE(){
	//abort();
	exit(EXIT_FAILURE);//GDB: Place a breakpoint here to get the callstack
}
fn void _exit_SUCCESS(){
	exit(EXIT_SUCCESS);
}
//inline __cdecl  int gzx_printf(const char *format, ...){
__attribute__((fastcall)) void Console_WriteString(const char *str);
fn int _printf(const char*_format, ...){
/*
	  va_list _arg;
	  
	  va_start( _arg, _format );
	  int _ret = vprintf(  _format, _arg );
	  
	  va_end( _arg );
	  
	  Console_WriteString("111111111PRINT!");
	  
	  fflush(stdout);*/
	
	//TODO optimise & size check
	char BUFFER[4096] = {0};
	int ret = 0;
	va_list arg;
	va_start (arg, _format);
		 ret = vsprintf (BUFFER, _format, arg);
	va_end (arg);

	  Console_WriteString(BUFFER);
	  
	  return ret;
}

fn int err_printf(const char*_format, ...){
	  
	  Console_WriteString("err_printf!");
	va_list _arg;

	va_start( _arg, _format );
#ifdef D_REDIRECT_STDERR
	int _ret = vprintf( _format, _arg );
#else
	int _ret = vfprintf(stderr, _format, _arg );
#endif
	va_end( _arg );

	fflush(stderr);
	return _ret;
}

#ifdef D_Platform_Android
	#include <android/log.h>
	#define  gzx_android_log_print  __android_log_print
#endif
