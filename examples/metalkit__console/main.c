/* -*- Mode: C; c-basic-offset: 3 -*- */

#include "types.h"
#include "console_vga.h"
#include "intr.h"
#include "keyboard.h"

volatile uint32 count = 0;

fastcall void
kbHandler(KeyEvent *event)
{
   if (!event->pressed) {
      return;
   }
   if (event->key == 0 || event->key >= 0x80) {
      return;
   }

   Console_WriteChar(event->key);
   Console_Flush();
}

 int __main(){return 0;}
extern int main(void) asm("main");

int main(void)
{
   ConsoleVGA_Init();
   Intr_Init();
   Intr_SetFaultHandlers(Console_UnhandledFault);
   Keyboard_Init();
   Keyboard_SetHandler(kbHandler);

   while (1) {
      Intr_Halt();
   }

   return 0;
}
