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

#include "gramdisk.h"

module_param(gramdisk_sectors, unsigned long, GRAMDISK_DEFAULT_SECTORS);
MODULE_PARM_DESC(gramdisk_sectors,"Configure number sectors of GPU Ramdisk");
module_param(gramdisk_size, unsigned long, GRAMDISK_DEFAULT_SIZE);
MODULE_PARM_DESC(gramdisk_size,"Configure size sector of GPU Ramdisk");

module_init(gramdisk_init);
module_exit(gramdisk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(VERSION_STR);
MODULE_INFO(Copyright, COPYRIGHT);
