/* ========================================================================== */
/*                                                                            */
/*   gramdisk.h                                                               */
/*   (c) 2015 Juraj Puchký - Devtech                                          */
/*                                                                            */
/*   Header file for GPU Ram disk                                             */
/*                                                                            */
/* ========================================================================== */


#ifndef _GPU_RAMDISK_
#define _GPU_RAMDISK_

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>

#define DEVICE_NAME 			"gram"
#define VERSION_STR 			"0.1"
#define COPYRIGHT				  "Copyright (c) 2013 Juraj Puchký - Devtech"
#define DRIVER_AUTHOR 		"Juraj Puchký - Devtech <sjurajpuchky@seznam.cz>"
#define DRIVER_DESC				"Ramdisk driver for NVIDIA GPU cards with DDR3-5 support, specialy to usage in case high prio swap drive."
#define BPS 					512
#define GRAMDISK_MAJOR_NUMBER 			2
#define GRAMDISK_MINOR_NUMBER 			1
#define GRAMDISK_MINOR_NUMBER_START_AT 	0
// 64MB
#define GRAMDISK_DEFAULT_SIZE    1024
#define GRAMDISK_DEFAULT_SECTORS 1024*64
#define GRAMDISK_DEFAULT_MODE	1

// Macros

// Predefine global variables
static void           *gramdisk_data;
static DEFINE_SPINLOCK(gramdisk_lock);
struct request_queue  *gramdisk_rq;
static struct gendisk *gramdisk_device;

// Default parameters
static int           gram_major_number = MAJOR_NUMBER;
static unsigned short gramdisk_size = GRAMDISK_DEFUALT_SIZE;
static unsigned short gramdisk_sectors = GRAMDISK_DEFUALT_SECTORS;
static int 			     gramdisk_mode = DEFAULT_MODE;

// Predefine functions
static int __init gramdisk_init(void);
static void __exit gramdisk_exit(void);
static void gramdisk_request(struct request_queue *rq);

static struct block_device_operations gramdisk_device_fops = {
  .owner = THIS_MODULE,      
  .ioctl = gramdisk_ioctl_fn,
};

#endif
