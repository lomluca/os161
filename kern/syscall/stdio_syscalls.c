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
#include <device.h>
#include <syscall.h>
#include <test.h>
#include <version.h>
#include "autoconf.h"  // for pseudoconfig

int sys_write(char*, int);
int sys_read(char*, int);

int sys_write(char* buf, int count) {
	int i = 0;
	
	for(i = 0; i < count; i++) {
		kprintf("%c", buf[i]);
	}
	return 0;
}

int sys_read(char* buf, int count) {

	kgets(buf, count);
	return 0;
}
