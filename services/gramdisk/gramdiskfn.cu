/* ========================================================================== */
/*                                                                            */
/*   gramdiskfn.cu                                                            */
/*   (c) 2015 Juraj Puchky - Devtech                                          */
/*                                                                            */
/*   Common CUDA functions for GPU Ramdisk                                    */
/*                                                                            */
/* ========================================================================== */


#include "gramdisk.h"
#include <cuda.h>

  
static void gramdisk_request(struct request_queue *rq) 
{
    void *addr;
    struct request *req;
    int   len;
	
    while ((req = elv_next_request(rq)) != NULL) {
     if (blk_fs_request(req)) {  
     addr = gramdisk_data + (req->sector << 9);
	   len = req->current_nr_sectors << 9;
       switch(rq_data_dir(req)) {
        case WRITE:
         if(cudaMemcpy(addr,req->buffer,len,cudaMemcpyHostToDevice) == cudaSuccess) {
         } else {
           printk("Cannot write a sector");
         }
        break;
        case READ:
         if(cudaMemcpy(req->buffer,addr,len,cudaMemcpyDeviceToHost) == cudaSuccess) {
         } else {
           printk("Cannot read a sector");
         }
        break;
        default:
          printk("Unsupported command");
      }
     }
    }
}

// Init module
static int __init gramdisk_init(void)
{

  if(cudaMalloc(&gramdisk_data, gramdisk_size) == cudaSuccess) 
  {
    gramdisk_rq = blk_init_queue ( gramdisk_request, &gramdisk_lock);
    // Register block device major number
    if(register_blkdev(GRAMDISK_MAJOR_NUMBER,GRAMDISK_DEVICE_NAME)<=0) 
    {
       printk("Cannot register block device");
    } else {
       // Configure disk, set max sectors
       blk_queue_max_sectors (gramdisk_rq, gramdisk_sectors);
       // Configure disk, set size of sector
       blk_queue_hardsect_size (gramdisk_rq, gramdisk_size);
       // Alocate disk, set number of minor
       gramdisk_device = alloc_disk(GRAMDISK_MINOR_NUMBER);
       // Setup disk
       set_capacity(gramdisk_device, gramdisk_sectors*gramdisk_size);
       gramdisk_device->queue  = gramdisk_rq;
       gramdisk_device->major  = GRAMDISK_MAJOR_NUMBER;
       gramdisk_device->first_minor = 0;
       sprintf(gramdisk_device->disk_name, GRAMDISK_DEVICE_NAME);

        // Add the gendisk
        add_disk(gramdisk_device);       
    }     
  } else {
    printk("Cannot alloc memory on GPU");
  }
}

// Exit module
static void __exit gramdisk_exit(void)
{
    if(cudaFree(&gramdisk_data) == cudaSuccess) {
      blk_cleanup_queue(gramdisk_rq); 
    } else {
      printk("Cannot release memory on GPU");      
      
    }
}