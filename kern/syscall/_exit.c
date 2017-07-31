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
	struct proc* cur_p;
	cur_p = curthread->t_proc;
	cur_p->exit_code = code;
	V(cur_p->sem);
	thread_exit();
	return;
}
	
