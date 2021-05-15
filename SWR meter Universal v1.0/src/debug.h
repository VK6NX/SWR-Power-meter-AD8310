/*
 * debug.h
 *
 *  Created on: 15Nov.,2017
 *      Author: ziss
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include "Esp32MQTTClient.h"

#if defined(MECH_DEBUG)

#define __ASSERT_USE_STDERR
#include <assert.h>

#define BUFF_SIZE 8
char __dbg_buff[BUFF_SIZE];
uint8_t __dbg_buff_ptr = 0;

#define dprintf(format, ...) printf_P(PSTR( format ), ##__VA_ARGS__)

#if defined(__AVR__)
static FILE debugout = {0};

static int debug_putchar (char c, FILE *stream) {
  if (__dbg_buff_ptr >= BUFF_SIZE) {
    icsc.send(ID_HAL100, (char) cmdDebug, __dbg_buff_ptr, &__dbg_buff[0]);
    __dbg_buff_ptr = 0;
  }
  __dbg_buff[__dbg_buff_ptr] = c;
  __dbg_buff_ptr++;
  return 1;
}

inline void debugInit() {
  fdev_setup_stream (&debugout, debug_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &debugout;
  stderr = &debugout;
}

void debugLoop() {
  if (__dbg_buff_ptr > 0) {
    icsc.send(ID_HAL100, (char) cmdDebug, __dbg_buff_ptr, &__dbg_buff[0]);
    __dbg_buff_ptr = 0;
  }
}


#else


inline void debugInit() {
}

void debugLoop() {
}

#endif

#else

inline void debugInit() {
}

inline void debugLoop() {
}

#define dprintf(format, ...)
#define assert(expression)

#endif

#endif /* DEBUG_H_ */
