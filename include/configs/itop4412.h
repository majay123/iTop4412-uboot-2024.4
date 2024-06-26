/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG ORIGEN (EXYNOS4210) board.
 */

#ifndef __CONFIG_ITOP4412_H
#define __CONFIG_ITOP4412_H

#include <configs/exynos4-common.h>

/* High Level Configuration Options */
#define CONFIG_EXYNOS4412		1	/* which is a EXYNOS4412 SoC */
#define CONFIG_ITOP4412			1	/* working with ORIGEN*/

/* iTop4412 has 4 bank of DRAM */
#define CFG_SYS_SDRAM_BASE			0x40000000
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE			(256 << 20)	/* 256 MB */

#define CFG_SYS_INIT_RAM_ADDR	0x40000000
#define CFG_SYS_INIT_RAM_SIZE	(256 << 20)	/* 256 MB */

/* memtest works on */
#ifndef CONFIG_SYS_LOAD_ADDR
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x00100000)
#endif

#define CONFIG_MACH_TYPE		MACH_TYPE_ITOP4412

/* USB */
#ifndef CONFIG_USB_EHCI_EXYNOS
#define CONFIG_USB_EHCI_EXYNOS
#endif

/* select serial console configuration */

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC1,115200n8\0"

#ifndef CONFIG_SYS_MEM_TOP_HIDE
#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */
#endif

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

/* MMC SPL */
#define COPY_BL2_FNPTR_ADDR     0x02020030

#define CFG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x40007000\0" \
	"rdaddr=0x48000000\0" \
	"kerneladdr=0x40007000\0" \
	"ramdiskaddr=0x48000000\0" \
	"console=ttySAC2,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"dtb_addr=0x41000000\0" \
	"dtb_name=exynos4412-itop-elite.dtb\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"bootargs=root=/dev/mmcblk1p2 rw console=ttySAC2,115200 init=/linuxrc earlyprintk\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
	"env import -t $loadaddr $filesize\0" \
    "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
    "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
    "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
	"fi;" \
	"mmc read ${loadaddr} 0x4A0 0x8000; mmc read ${dtb_addr} 0x84A0 0x80; bootm ${loadaddr} - ${dtb_addr}" \
	"load mmc ${mmcdev} ${loadaddr} uImage; load mmc ${mmcdev} ${dtb_addr} ${dtb_name}; bootm ${loadaddr} - ${dtb_addr}"



#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

#define CONFIG_SYS_MMC_ENV_DEV		0
#define RESERVE_BLOCK_SIZE		(512)
#define BL1_SIZE			(8 << 10)  /*8 K reserved for BL1*/
#define BL2_SIZE			(16 << 10) /*16 K reserved for SPL*/

#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_SPL_STACK			0x02040000
#define UBOOT_SIZE				(2 << 20)
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_TEXT_BASE + UBOOT_SIZE - 0x1000)

/* U-Boot copy size from boot Media to DRAM.*/
#define COPY_BL2_SIZE		0x80000 // 512 KB
#define BL2_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE)/512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE/512)

#endif  /* __CONFIG_H */

