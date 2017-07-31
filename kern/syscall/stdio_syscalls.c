#include <types.h>
#include <kern/errno.h>
#include <kern/reboot.h>
#include <kern/unistd.h>
#include <lib.h>
#include <spl.h>
#include <clock.h>
#include <thread.h>
#include <proc.h>
#include <current.h>
#include <synch.h>
#include <vm.h>
#include <mainbus.h>
#include <vfs.h>
#include <uio.h>
#include <vnode.h>
#include <device.h>
#include <syscall.h>
#include <test.h>
#include <version.h>
#include "autoconf.h"  // for pseudoconfig

int sys_write(int, char*, int);
int sys_read(int, char*, int);
int sys_open(char* path, int openflags, int* fd);
int sys_close(int fd);

struct vnode* opened_file_table[13];

int sys_write(int fd, char* buf, int count) {
  struct iovec iov;
  struct uio u;
  int result;
  if ( fd < 3 ) {
	int i = 0;
	
	for(i = 0; i < count; i++) {
		kprintf("%c", buf[i]);
	}
	return 0;
  } else {

    /*uio init for a user task*/
    u.uio_iov = &iov;
    iov.iov_ubase = (userptr_t)buf;
    iov.iov_len = count;
    u.uio_iovcnt = 1;
    u.uio_offset = 0;
    u.uio_resid = count;
    u.uio_segflg = UIO_USERSPACE;
    u.uio_rw = UIO_WRITE;
    u.uio_space = curproc->p_addrspace;

    result = VOP_WRITE(opened_file_table[fd], &u);
  }
  return result;
}

int sys_read(int fd, char* buf, int count) {
  struct iovec iov;
  struct uio u;
  int result;
  if ( fd < 3 ) {
	kgets(buf, count);
	return 0;
  } else {
    /*uio init for a user task*/
    u.uio_iov = &iov;
    iov.iov_ubase = (userptr_t)buf;
    iov.iov_len = count;
    u.uio_iovcnt = 1;
    u.uio_offset = 0;
    u.uio_resid = count;
    u.uio_segflg = UIO_USERSPACE;
    u.uio_rw = UIO_READ;
    u.uio_space = curproc->p_addrspace;

    result = VOP_READ(opened_file_table[fd], &u);
  }
  return result;
}

int sys_open(char* path, int openflags, int32_t* file_descr) {
  int result, i = 2;
  struct vnode* new_file;
  result = vfs_open(path, openflags, 0, &new_file);
  while( opened_file_table[++i] != NULL);
  *file_descr = i;
  opened_file_table[i] = new_file;
  return result;
}

int sys_close(int fd) {
  vfs_close(opened_file_table[fd]);
  opened_file_table[fd] = NULL;
  return 0;
}




