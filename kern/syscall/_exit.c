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
#include <thread.h>
#include "autoconf.h"  // for pseudoconfig

void exit(int);

void _exit(int code) {
	struct thread *cur_t;
	
	cur_t = curthread;
	cur_t->exit_code = code;
	thread_exit();
	return;
}
	
