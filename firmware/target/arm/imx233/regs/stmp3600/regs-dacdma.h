/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * This file was automatically generated by headergen, DO NOT EDIT it.
 * headergen version: 2.1.7
 * XML versions: stmp3600:2.3.0
 *
 * Copyright (C) 2013 by Amaury Pouly
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#ifndef __HEADERGEN__STMP3600__DACDMA__H__
#define __HEADERGEN__STMP3600__DACDMA__H__

#define REGS_DACDMA_BASE (0x8004c000)

#define REGS_DACDMA_VERSION "2.3.0"

/**
 * Register: HW_DACDMA_CTRL
 * Address: 0
 * SCT: yes
*/
#define HW_DACDMA_CTRL              (*(volatile unsigned long *)(REGS_DACDMA_BASE + 0x0 + 0x0))
#define HW_DACDMA_CTRL_SET          (*(volatile unsigned long *)(REGS_DACDMA_BASE + 0x0 + 0x4))
#define HW_DACDMA_CTRL_CLR          (*(volatile unsigned long *)(REGS_DACDMA_BASE + 0x0 + 0x8))
#define HW_DACDMA_CTRL_TOG          (*(volatile unsigned long *)(REGS_DACDMA_BASE + 0x0 + 0xc))
#define BP_DACDMA_CTRL_SFTRST       31
#define BM_DACDMA_CTRL_SFTRST       0x80000000
#define BF_DACDMA_CTRL_SFTRST(v)    (((v) << 31) & 0x80000000)
#define BP_DACDMA_CTRL_CLKGATE      30
#define BM_DACDMA_CTRL_CLKGATE      0x40000000
#define BF_DACDMA_CTRL_CLKGATE(v)   (((v) << 30) & 0x40000000)
#define BP_DACDMA_CTRL_RUN          0
#define BM_DACDMA_CTRL_RUN          0x1
#define BF_DACDMA_CTRL_RUN(v)       (((v) << 0) & 0x1)

/**
 * Register: HW_DACDMA_DATA
 * Address: 0x80
 * SCT: no
*/
#define HW_DACDMA_DATA          (*(volatile unsigned long *)(REGS_DACDMA_BASE + 0x80))
#define BP_DACDMA_DATA_HIGH     16
#define BM_DACDMA_DATA_HIGH     0xffff0000
#define BF_DACDMA_DATA_HIGH(v)  (((v) << 16) & 0xffff0000)
#define BP_DACDMA_DATA_LOW      0
#define BM_DACDMA_DATA_LOW      0xffff
#define BF_DACDMA_DATA_LOW(v)   (((v) << 0) & 0xffff)

#endif /* __HEADERGEN__STMP3600__DACDMA__H__ */