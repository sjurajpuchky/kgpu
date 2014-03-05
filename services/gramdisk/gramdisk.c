/*
 * gramdisk.c
 *
 *  Created on: 28.12.2013
 *      Author: Juraj Puchký - Devtech <sjurajpuchky@seznam.cz>
 *      Home: http://www.devtech.cz
 *      License: GPLv2 follow GPL-COPYING file int the top-level directory.
 *      Copyright (c) 2013 Juraj Puchký - Devtech
 *      All rights reserved.
 */

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>

#include "../../kgpu/kkgpu.h"

#define DEVICE_NAME 			"gram"
#define VERSION_STR 			"0.1"
#define COPYRIGHT				"Copyright (c) 2013 Juraj Puchký - Devtech"
#define DRIVER_AUTHOR 			"Juraj Puchký - Devtech <sjurajpuchky@seznam.cz>"
#define DRIVER_DESC				"Ramdisk driver for NVIDIA GPU cards with DDR3-5 support, specialy to usage in case high prio swap drive."
#define BPS 					512
#define MAJOR_NUMBER 			2
#define MINOR_NUMBER_START_AT 	0
// 64 MB
#define DEFAULT_SIZE	2*BPS*1024*64
#define DEFAULT_MODE	1

// Macros
#define BIO_SECTOR(s) 			s->bi_sector
#define BVEC_CUR_SECTORS(bv) 	(bv->bv_len) >> 9


// Default parameters
static int gram_major_number = MAJOR_NUMBER;
static unsigned long size = DEFUALT_SIZE;
static int 			 mode = DEFAULT_MODE;

module_param(size, unsigned long, DEFAULT_SIZE);
MODULE_PARM_DESC(size," Size of GPU ramdisk in Bytes. default = 67108864 for 64 MB\n, 0 is taking all free GPU memory except 64MB reserved for others.");


static struct request_queue *gram_rq;

// Transfare fucntion
void gram_transfer(void *buf, sector_t s, int n, int d) {

	unsigned long size = n*BPS;


}

// Init module
static int __init gramdisk_init(void)
{
}

// Exit module
static void __exit gramdisk_exit(void)
{
}

module_init(gramdisk_init);
module_exit(gramdisk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(VERSION_STR);
MODULE_INFO(Copyright, COPYRIGHT);
