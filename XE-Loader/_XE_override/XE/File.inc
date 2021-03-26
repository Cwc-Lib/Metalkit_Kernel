 /*  -== XE-Loader ==-
 *
 *  Load [.exe .elf / .dll .so] from memory and remap functions
 *  Run your binaries on any x86 hardware
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
 * Description:
* 
* FuncTable_Impl is the ExeLoader custom implementation. 
* Main goal is to be portable which does not relying on system functions
* 
*/
//#include "types.h"
//#include "puff.h"

typedef struct DataFile {
   uint8_t *ptr;
   uint32_t size;
} DataFile;

#define DECLARE_DATAFILE(symbol, filename)          \
   extern uint8_t _binary_ ## filename ## _start[];   \
   extern uint8_t _binary_ ## filename ## _size[];    \
   static const DataFile symbol[1] = {{             \
      (uint8_t*) _binary_ ## filename ## _start,      \
      (uint32_t) _binary_ ## filename ## _size,       \
   }}


DECLARE_DATAFILE(myExe, ElieDraw_exe);

File Xe_LoadFile(const char* _sFullPath)
{

	return (File){.data=(char*)myExe->ptr, .size=myExe->size, .path=_mallocpy(_sFullPath, strlen(_sFullPath)+1, char)};
	
/*
	if(_sFullPath == 0){
		_printl("Error: No file to load.");
		return (File){};
	}

	FILE*  f = fopen((char*)_sFullPath, "rb+");
	unsigned char *result;

	if (f != NULL){
		long lSize;
		fseek (f , 0 , SEEK_END);
		lSize = ftell (f);
		rewind (f);
		size_t _nSize = lSize;

		uint8_t* _aData = _malloc(_nSize, uint8_t);
		fread(_aData, 1, _nSize, f);
		
		fclose(f);
		return (File){.data=(char*)_aData, .size=_nSize, .path=_mallocpy(_sFullPath, strlen(_sFullPath)+1, char)};
	
	
	}else{
		err_print("Error Loading File [%s] (%s)", _sFullPath, strerror(errno));
	}
	
	return (File){};*/
}

void Xe_FreeFile(File* file){
	if(!file) return;
	_free(file->data);
	_free(file->path);
}