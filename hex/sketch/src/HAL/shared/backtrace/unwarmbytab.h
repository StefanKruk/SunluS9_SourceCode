#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/shared/backtrace/unwarmbytab.h"
/***************************************************************************
 * ARM Stack Unwinder, Michael.McTernan.2001@cs.bris.ac.uk
 * Updated, adapted and several bug fixes on 2018 by Eduardo José Tagle
 *
 * This program is PUBLIC DOMAIN.
 * This means that there is no copyright and anyone is able to take a copy
 * for free and use it as they wish, with or without modifications, and in
 * any context, commerically or otherwise. The only limitation is that I
 * don't guarantee that the software is fit for any purpose or accept any
 * liability for its use or misuse - this software is without warranty.
 ***************************************************************************
 * File Description: Interface to the memory tracking sub-system.
 **************************************************************************/

#pragma once

#include "unwarm.h"

typedef struct {
  uint32_t vrs[16];
  uint32_t current; /* Address of current byte */
  int remaining;
  int byte;
} UnwTabState;

typedef struct {
  uint32_t addr_offset;
  uint32_t insn;
} UnwTabEntry;

UnwResult UnwindByTableStart(UnwindFrame* frame, const UnwindCallbacks *cb, void *data);
