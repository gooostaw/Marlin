/**
 * Webber Ranch CNC Firmware
*/
#if defined(__arm__) || defined(__thumb__)

#include "backtrace.h"
#include "unwinder.h"
#include "unwmemaccess.h"

#include "../HAL_MinSerial.h"
#include <stdarg.h>

// Dump a backtrace entry
static bool UnwReportOut(void *ctx, const UnwReport *bte) {
  int *p = (int*)ctx;

  (*p)++;

  const uint32_t a = bte->address, f = bte->function;
  MinSerial::TX('#');    MinSerial::TXDec(*p);    MinSerial::TX(" : ");
  MinSerial::TX(bte->name?:"unknown");            MinSerial::TX('@');   MinSerial::TXHex(f);
  MinSerial::TX('+');    MinSerial::TXDec(a - f);
  MinSerial::TX(" PC:"); MinSerial::TXHex(a);
  MinSerial::TX('\n');
  return true;
}

#ifdef UNW_DEBUG
  void UnwPrintf(const char *format, ...) {
    char dest[256];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);
    MinSerial::TX(&dest[0]);
  }
#endif

/* Table of function pointers for passing to the unwinder */
static const UnwindCallbacks UnwCallbacks = {
  UnwReportOut,
  UnwReadW,
  UnwReadH,
  UnwReadB
  #ifdef UNW_DEBUG
   , UnwPrintf
  #endif
};

// Perform a backtrace to the serial port
void backtrace() {

  unsigned long sp = 0, lr = 0, pc = 0;

  // Capture the values of the registers to perform the traceback
  __asm__ __volatile__ (
    " mov %[lrv],lr\n"
    " mov %[spv],sp\n"
    " mov %[pcv],pc\n"
    : [spv]"+r"( sp ),
      [lrv]"+r"( lr ),
      [pcv]"+r"( pc )
    ::
  );

  backtrace_ex(sp, lr, pc);
}

void backtrace_ex(unsigned long sp, unsigned long lr, unsigned long pc) {
  UnwindFrame btf;

  // Fill the traceback structure
  btf.sp = sp;
  btf.fp = btf.sp;
  btf.lr = lr;
  btf.pc = pc | 1; // Force Thumb, as CORTEX only support it

  // Perform a backtrace
  MinSerial::TX("Backtrace:");
  int ctr = 0;
  UnwindStart(&btf, &UnwCallbacks, &ctr);
}

#else // !__arm__ && !__thumb__

void backtrace() {}

#endif // __arm__ || __thumb__
