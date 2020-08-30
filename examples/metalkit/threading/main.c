/* -*- Mode: C; c-basic-offset: 3 -*-
 *
 * Pre-emptive multithreading example for Metalkit.
 *
 * This is a very simple pre-emptive multithreading kernel, with two
 * tasks. Task 1 is the bootstrap task- it sets up the kernel and
 * creates task 2, then busy-loops. Task 2 increments a counter.
 *
 * Metalkit itself doesn't include any multitasking, but it does
 * include an interrupt subsystem which knows how to save and restore
 * thread context. Its IntrContext structure can be used to
 * save/restore execution context just like setjmp/longjmp, but the
 * same structure can also be used when reading or modifying the
 * context in which an interrupt occurred.
 */

#include "types.h"
#include "console_vga.h"
#include "timer.h"
#include "intr.h"

#define STACK_SIZE 1024

struct task {
   uint32 stack[STACK_SIZE];
   IntrContext context;
   struct task *next;
};

struct task task1, task2;
struct {
   struct task *current;
   struct task *next;
   struct task *last;
} runQueue;

fastcall void
runQueue_append(struct task *t)
{
   if (runQueue.last) {
      runQueue.last->next = t;
   } else {
      runQueue.next = t;
   }
   runQueue.last = t;
}

fastcall struct task *
runQueue_pop(void)
{
   struct task *next = runQueue.next;
   runQueue.next = next->next;
   if (!runQueue.next) {
      runQueue.last = NULL;
   }
   return next;
}

fastcall void
task_init(struct task *t, IntrContextFn m)
{
   Intr_InitContext(&t->context, &t->stack[STACK_SIZE-1], m);
   Intr_Disable();
   runQueue_append(t);
   Intr_Enable();
}

void
schedulerIRQ(int vector)
{
   IntrContext *context = Intr_GetContext(vector);
   struct task *prevTask, *nextTask;

   /*
    * Decide which task to run next
    */

   prevTask = runQueue.current;
   runQueue_append(runQueue.current);
   nextTask = runQueue_pop();
   runQueue.current = nextTask;

   /*
    * Switch tasks
    */

   memcpy(&prevTask->context, context, sizeof *context);
   memcpy(context, &nextTask->context, sizeof *context);
}

void
task2_main(void)
{
   uint32 counter = 0;

   while (1) {
      counter++;

      /*
       * Disable interrupts while using the console, since it isn't re-entrant.
       */

      Intr_Disable();
      Console_Format("Task 2 (counter: %d)\n", counter);
      Console_Flush();
      Intr_Enable();
   }
}

void
task1_main(void)
{
   /*
    * This is the bootstrap task- start up the scheduler and load the
    * second task.  Our scheduler is driven by the PIT timer IRQ at
    * 100 Hz.
    */

   Timer_InitPIT(PIT_HZ / 100);
   Intr_SetMask(0, TRUE);
   Intr_SetHandler(IRQ_VECTOR(IRQ_TIMER), schedulerIRQ);

   /*
    * Create the second task. It can start running at any time now.
    */

   task_init(&task2, task2_main);

   while (1) {
      Intr_Disable();
      Console_WriteString("Task 1\n");
      Console_Flush();
      Intr_Enable();
   }
}

int
main(void)
{
   ConsoleVGA_Init();
   Intr_Init();
   Intr_SetFaultHandlers(Console_UnhandledFault);

   /*
    * Create task 1, and switch to it. We never come
    * back to main() after this.
    */

   task_init(&task1, task1_main);
   runQueue.current = runQueue_pop();
   Intr_RestoreContext(&runQueue.current->context);

   return 0;
}
