// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1989-2016 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

// ----------------------------------------------------------------------------
//      /usr/include/time.h
// ----------------------------------------------------------------------------
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

// ----------------------------------------------------------------------------
//      /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
// ----------------------------------------------------------------------------
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

// ----------------------------------------------------------------------------
//      /usr/include/pthread.h
// ----------------------------------------------------------------------------
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct {
	int __val[2];
} __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void *__timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h

typedef long unsigned int size_t;
// /usr/include/time.h

typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
struct timespec {
	__time_t tv_sec;
	__syscall_slong_t tv_nsec;
};
struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long int __tm_gmtoff;
	const char *__tm_zone;
};
struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};
struct sigevent;
extern clock_t clock(void);
extern time_t time(time_t * __timer);
extern double difftime(time_t __time1, time_t __time0);
extern time_t mktime(struct tm *__tp);
extern size_t strftime(char *__s, size_t __maxsize, const char *__format, const struct tm *__tp);
extern char *strptime(const char *__s, const char *__fmt, struct tm *__tp);
extern struct tm *gmtime(const time_t * __timer);
extern struct tm *localtime(const time_t * __timer);
extern struct tm *gmtime_r(const time_t * __timer, struct tm *__tp);
extern struct tm *localtime_r(const time_t * __timer, struct tm *__tp);
extern char *asctime(const struct tm *__tp);
extern char *ctime(const time_t * __timer);
extern char *asctime_r(const struct tm *__tp, char *__buf);
extern char *ctime_r(const time_t * __timer, char *__buf);
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];
extern void tzset(void);
extern int daylight;
extern long int timezone;
extern int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining);
extern int clock_getres(clockid_t __clock_id, struct timespec *__res);
extern int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
extern int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
extern int timer_create(clockid_t __clock_id, struct sigevent *__evp, timer_t * __timerid);
extern int timer_delete(timer_t __timerid);
extern int timer_settime(timer_t __timerid, int __flags, const struct itimerspec *__value, struct itimerspec *__ovalue);
extern int timer_gettime(timer_t __timerid, struct itimerspec *__value);
extern int timer_getoverrun(timer_t __timerid);
extern int getdate_err;
extern struct tm *getdate(const char *__string);
// /usr/include/x86_64-linux-gnu/bits/sched.h

struct sched_param {
	int __sched_priority;
};
struct __sched_param {
	int __sched_priority;
};
typedef unsigned long int __cpu_mask;
typedef struct {
	__cpu_mask __bits[16ul];
} cpu_set_t;
extern int __sched_cpucount(size_t __setsize, const cpu_set_t * __setp);
extern cpu_set_t *__sched_cpualloc(size_t __count);
extern void __sched_cpufree(cpu_set_t * __set);
// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h

typedef unsigned long int pthread_t;
union pthread_attr_t {
	char __size[56];
	long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_list {
	struct __pthread_internal_list *__prev;
	struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union {
	struct __pthread_mutex_s {
		int __lock;
		unsigned int __count;
		int __owner;
		unsigned int __nusers;
		int __kind;
		short __spins;
		short __elision;
		__pthread_list_t __list;
	} __data;
	char __size[40];
	long int __align;
} pthread_mutex_t;
typedef union {
	char __size[4];
	int __align;
} pthread_mutexattr_t;
typedef union {
	struct {
		int __lock;
		unsigned int __futex;
		unsigned long long int __total_seq;
		unsigned long long int __wakeup_seq;
		unsigned long long int __woken_seq;
		void *__mutex;
		unsigned int __nwaiters;
		unsigned int __broadcast_seq;
	} __data;
	char __size[48];
	long long int __align;
} pthread_cond_t;
typedef union {
	char __size[4];
	int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union {
	struct {
		int __lock;
		unsigned int __nr_readers;
		unsigned int __readers_wakeup;
		unsigned int __writer_wakeup;
		unsigned int __nr_readers_queued;
		unsigned int __nr_writers_queued;
		int __writer;
		int __shared;
		signed char __rwelision;
		unsigned char __pad1[7];
		unsigned long int __pad2;
		unsigned int __flags;
	} __data;
	char __size[56];
	long int __align;
} pthread_rwlock_t;
typedef union {
	char __size[8];
	long int __align;
} pthread_rwlockattr_t;
// /usr/include/pthread.h

enum { PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED };
enum { PTHREAD_MUTEX_TIMED_NP, PTHREAD_MUTEX_RECURSIVE_NP, PTHREAD_MUTEX_ERRORCHECK_NP, PTHREAD_MUTEX_ADAPTIVE_NP, PTHREAD_MUTEX_NORMAL = 0, PTHREAD_MUTEX_RECURSIVE = 1, PTHREAD_MUTEX_ERRORCHECK = 2, PTHREAD_MUTEX_DEFAULT = 0 };
enum { PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT };
enum { PTHREAD_RWLOCK_PREFER_READER_NP, PTHREAD_RWLOCK_PREFER_WRITER_NP, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP, PTHREAD_RWLOCK_DEFAULT_NP = 0 };
enum { PTHREAD_INHERIT_SCHED, PTHREAD_EXPLICIT_SCHED };
enum { PTHREAD_SCOPE_SYSTEM, PTHREAD_SCOPE_PROCESS };
enum { PTHREAD_PROCESS_PRIVATE, PTHREAD_PROCESS_SHARED };
struct _pthread_cleanup_buffer {
	void (*__routine) (void *);
	void *__arg;
	int __canceltype;
	struct _pthread_cleanup_buffer *__prev;
};
enum { PTHREAD_CANCEL_ENABLE, PTHREAD_CANCEL_DISABLE };
enum { PTHREAD_CANCEL_DEFERRED, PTHREAD_CANCEL_ASYNCHRONOUS };
extern int pthread_create(pthread_t * __newthread, const pthread_attr_t * __attr, void *(*__start_routine) (void *), void *__arg);
extern void pthread_exit(void *__retval);
extern int pthread_join(pthread_t __th, void **__thread_return);
extern int pthread_detach(pthread_t __th);
extern pthread_t pthread_self(void);
extern int pthread_equal(pthread_t __thread1, pthread_t __thread2);
extern int pthread_attr_init(pthread_attr_t * __attr);
extern int pthread_attr_destroy(pthread_attr_t * __attr);
extern int pthread_attr_getdetachstate(const pthread_attr_t * __attr, int *__detachstate);
extern int pthread_attr_setdetachstate(pthread_attr_t * __attr, int __detachstate);
extern int pthread_attr_getguardsize(const pthread_attr_t * __attr, size_t * __guardsize);
extern int pthread_attr_setguardsize(pthread_attr_t * __attr, size_t __guardsize);
extern int pthread_attr_getschedparam(const pthread_attr_t * __attr, struct sched_param *__param);
extern int pthread_attr_setschedparam(pthread_attr_t * __attr, const struct sched_param *__param);
extern int pthread_attr_getschedpolicy(const pthread_attr_t * __attr, int *__policy);
extern int pthread_attr_setschedpolicy(pthread_attr_t * __attr, int __policy);
extern int pthread_attr_getinheritsched(const pthread_attr_t * __attr, int *__inherit);
extern int pthread_attr_setinheritsched(pthread_attr_t * __attr, int __inherit);
extern int pthread_attr_getscope(const pthread_attr_t * __attr, int *__scope);
extern int pthread_attr_setscope(pthread_attr_t * __attr, int __scope);
extern int pthread_attr_getstackaddr(const pthread_attr_t * __attr, void **__stackaddr);
extern int pthread_attr_setstackaddr(pthread_attr_t * __attr, void *__stackaddr);
extern int pthread_attr_getstacksize(const pthread_attr_t * __attr, size_t * __stacksize);
extern int pthread_attr_setstacksize(pthread_attr_t * __attr, size_t __stacksize);
extern int pthread_setschedparam(pthread_t __target_thread, int __policy, const struct sched_param *__param);
extern int pthread_getschedparam(pthread_t __target_thread, int *__policy, struct sched_param *__param);
extern int pthread_setschedprio(pthread_t __target_thread, int __prio);
extern int pthread_getconcurrency(void);
extern int pthread_setconcurrency(int __level);
extern int pthread_once(pthread_once_t * __once_control, void (*__init_routine) (void));
extern int pthread_setcancelstate(int __state, int *__oldstate);
extern int pthread_setcanceltype(int __type, int *__oldtype);
extern int pthread_cancel(pthread_t __th);
extern void pthread_testcancel(void);
typedef struct {
	struct {
		__jmp_buf __cancel_jmp_buf;
		int __mask_was_saved;
	} __cancel_jmp_buf[1];
	void *__pad[4];
} __pthread_unwind_buf_t;
struct __pthread_cleanup_frame {
	void (*__cancel_routine) (void *);
	void *__cancel_arg;
	int __do_it;
	int __cancel_type;
};
extern void __pthread_register_cancel(__pthread_unwind_buf_t * __buf);
extern void __pthread_unregister_cancel(__pthread_unwind_buf_t * __buf);
extern void __pthread_unwind_next(__pthread_unwind_buf_t * __buf);
struct __jmp_buf_tag;
extern int __sigsetjmp(struct __jmp_buf_tag *__env, int __savemask);
extern int pthread_mutex_init(pthread_mutex_t * __mutex, const pthread_mutexattr_t * __mutexattr);
extern int pthread_mutex_destroy(pthread_mutex_t * __mutex);
extern int pthread_mutex_trylock(pthread_mutex_t * __mutex);
extern int pthread_mutex_lock(pthread_mutex_t * __mutex);
extern int pthread_mutex_unlock(pthread_mutex_t * __mutex);
extern int pthread_mutex_getprioceiling(const pthread_mutex_t * __mutex, int *__prioceiling);
extern int pthread_mutex_setprioceiling(pthread_mutex_t * __mutex, int __prioceiling, int *__old_ceiling);
extern int pthread_mutexattr_init(pthread_mutexattr_t * __attr);
extern int pthread_mutexattr_destroy(pthread_mutexattr_t * __attr);
extern int pthread_mutexattr_getpshared(const pthread_mutexattr_t * __attr, int *__pshared);
extern int pthread_mutexattr_setpshared(pthread_mutexattr_t * __attr, int __pshared);
extern int pthread_mutexattr_gettype(const pthread_mutexattr_t * __attr, int *__kind);
extern int pthread_mutexattr_settype(pthread_mutexattr_t * __attr, int __kind);
extern int pthread_mutexattr_getprotocol(const pthread_mutexattr_t * __attr, int *__protocol);
extern int pthread_mutexattr_setprotocol(pthread_mutexattr_t * __attr, int __protocol);
extern int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t * __attr, int *__prioceiling);
extern int pthread_mutexattr_setprioceiling(pthread_mutexattr_t * __attr, int __prioceiling);
extern int pthread_rwlock_init(pthread_rwlock_t * __rwlock, const pthread_rwlockattr_t * __attr);
extern int pthread_rwlock_destroy(pthread_rwlock_t * __rwlock);
extern int pthread_rwlock_rdlock(pthread_rwlock_t * __rwlock);
extern int pthread_rwlock_tryrdlock(pthread_rwlock_t * __rwlock);
extern int pthread_rwlock_wrlock(pthread_rwlock_t * __rwlock);
extern int pthread_rwlock_trywrlock(pthread_rwlock_t * __rwlock);
extern int pthread_rwlock_unlock(pthread_rwlock_t * __rwlock);
extern int pthread_rwlockattr_init(pthread_rwlockattr_t * __attr);
extern int pthread_rwlockattr_destroy(pthread_rwlockattr_t * __attr);
extern int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t * __attr, int *__pshared);
extern int pthread_rwlockattr_setpshared(pthread_rwlockattr_t * __attr, int __pshared);
extern int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t * __attr, int *__pref);
extern int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t * __attr, int __pref);
extern int pthread_cond_init(pthread_cond_t * __cond, const pthread_condattr_t * __cond_attr);
extern int pthread_cond_destroy(pthread_cond_t * __cond);
extern int pthread_cond_signal(pthread_cond_t * __cond);
extern int pthread_cond_broadcast(pthread_cond_t * __cond);
extern int pthread_cond_wait(pthread_cond_t * __cond, pthread_mutex_t * __mutex);
extern int pthread_cond_timedwait(pthread_cond_t * __cond, pthread_mutex_t * __mutex, const struct timespec *__abstime);
extern int pthread_condattr_init(pthread_condattr_t * __attr);
extern int pthread_condattr_destroy(pthread_condattr_t * __attr);
extern int pthread_condattr_getpshared(const pthread_condattr_t * __attr, int *__pshared);
extern int pthread_condattr_setpshared(pthread_condattr_t * __attr, int __pshared);
extern int pthread_key_create(pthread_key_t * __key, void (*__destr_function) (void *));
extern int pthread_key_delete(pthread_key_t __key);
extern void *pthread_getspecific(pthread_key_t __key);
extern int pthread_setspecific(pthread_key_t __key, const void *__pointer);
extern int pthread_atfork(void (*__prepare) (void), void (*__parent) (void), void (*__child) (void));

// /usr/include/time.h 

#define __isleap(year) ( ( year ) % 4 == 0 && ( ( year ) % 100 != 0 || ( year ) % 400 == 0 ) )

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) ( __extension__ ( { const __cpu_mask * __arr1 = ( cpusetp1 ) -> __bits ; const __cpu_mask * __arr2 = ( cpusetp2 ) -> __bits ; size_t __imax = ( setsize ) / sizeof ( __cpu_mask ) ; size_t __i ; for ( __i = 0 ; __i < __imax ; ++ __i ) if ( __arr1 [ __i ] != __arr2 [ __i ] ) break ; __i == __imax ; } ) )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED_

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_COND_T (48)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define SCHED_RR (2)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U64_TYPE unsigned long int

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_ISSET_S(cpu, setsize, cpusetp) ( __extension__ ( { size_t __cpu = ( cpu ) ; __cpu / 8 < ( setsize ) ? ( ( ( ( const __cpu_mask * ) ( ( cpusetp ) -> __bits ) ) [ __CPUELT ( __cpu ) ] & __CPUMASK ( __cpu ) ) ) != 0 : 0 ; } ) )

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_RWLOCKATTR_T (8)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZET_
#define ___int_size_t_h

// /usr/include/pthread.h 

#define PTHREAD_CANCEL_DEFERRED PTHREAD_CANCEL_DEFERRED

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define NULL ( ( void * ) 0 )

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __have_pthread_attr_t (1)
#define __SIZEOF_PTHREAD_CONDATTR_T (4)

// /usr/include/pthread.h 

#define PTHREAD_SCOPE_SYSTEM PTHREAD_SCOPE_SYSTEM

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_CLR_S(cpu, setsize, cpusetp) ( __extension__ ( { size_t __cpu = ( cpu ) ; __cpu / 8 < ( setsize ) ? ( ( ( __cpu_mask * ) ( ( cpusetp ) -> __bits ) ) [ __CPUELT ( __cpu ) ] &= ~ __CPUMASK ( __cpu ) ) : 0 ; } ) )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T

// /usr/include/pthread.h 

#define pthread_cleanup_push(routine, arg) do { __pthread_unwind_buf_t __cancel_buf ; void ( * __cancel_routine ) ( void * ) = ( routine ) ; void * __cancel_arg = ( arg ) ; int __not_first_call = __sigsetjmp ( ( struct __jmp_buf_tag * ) ( void * ) __cancel_buf . __cancel_jmp_buf , 0 ) ; if ( __glibc_unlikely ( __not_first_call ) ) { __cancel_routine ( __cancel_arg ) ; __pthread_unwind_next ( & __cancel_buf ) ; } __pthread_register_cancel ( & __cancel_buf ) ; do {

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPUELT(cpu) ( ( cpu ) / __NCPUBITS )

// /usr/include/pthread.h 

#define PTHREAD_PROCESS_PRIVATE PTHREAD_PROCESS_PRIVATE

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S64_TYPE long int

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_SET_S(cpu, setsize, cpusetp) ( __extension__ ( { size_t __cpu = ( cpu ) ; __cpu / 8 < ( setsize ) ? ( ( ( __cpu_mask * ) ( ( cpusetp ) -> __bits ) ) [ __CPUELT ( __cpu ) ] |= __CPUMASK ( __cpu ) ) : 0 ; } ) )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DECLARED

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __PTHREAD_MUTEX_HAVE_PREV (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONG32_TYPE unsigned int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __size_t__

// /usr/include/pthread.h 

#define PTHREAD_INHERIT_SCHED PTHREAD_INHERIT_SCHED

// /usr/include/time.h 

#define __clockid_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define SCHED_FIFO (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _GCC_SIZE_T

// /usr/include/pthread.h 

#define PTHREAD_PROCESS_SHARED PTHREAD_PROCESS_SHARED
#define pthread_cleanup_pop(execute) do { } while ( 0 ) ; } while ( 0 ) ; __pthread_unregister_cancel ( & __cancel_buf ) ; if ( execute ) __cancel_routine ( __cancel_arg ) ; } while ( 0 )

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __NCPUBITS ( 8 * sizeof ( __cpu_mask ) )

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __PTHREAD_RWLOCK_INT_FLAGS_SHARED (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __ULONGWORD_TYPE unsigned long int

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_COUNT_S(setsize, cpusetp) __sched_cpucount ( setsize , cpusetp )

// /usr/include/pthread.h 

#define PTHREAD_MUTEX_INITIALIZER { { 0 , 0 , 0 , 0 , 0 , __PTHREAD_SPINS , { 0 , 0 } } }

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SYS_SIZE_T_H

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_MUTEXATTR_T (4)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SQUAD_TYPE long int

// /usr/include/pthread.h 

#define PTHREAD_CANCELED ( ( void * ) - 1 )

// /usr/include/time.h 

#define __time_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __PTHREAD_RWLOCK_ELISION_EXTRA 0 , { 0 , 0 , 0 , 0 , 0 , 0 , 0 }

// /usr/include/pthread.h 

#define PTHREAD_SCOPE_PROCESS PTHREAD_SCOPE_PROCESS

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SWORD_TYPE long int

// /usr/include/time.h 

#define __timer_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_BARRIER_T (32)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_FREE(cpuset) __sched_cpufree ( cpuset )

// /usr/include/pthread.h 

#define PTHREAD_RWLOCK_INITIALIZER { { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , __PTHREAD_RWLOCK_ELISION_EXTRA , 0 , 0 } }
#define __cleanup_fct_attribute

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_ATTR_T (56)
#define _BITS_PTHREADTYPES_H (1)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define SCHED_OTHER (0)

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_MUTEX_T (40)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S32_TYPE int

// /usr/include/pthread.h 

#define PTHREAD_CREATE_DETACHED PTHREAD_CREATE_DETACHED

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_ALLOC_SIZE(count) ( ( ( ( count ) + __NCPUBITS - 1 ) / __NCPUBITS ) * sizeof ( __cpu_mask ) )

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __S16_TYPE short int

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_BARRIERATTR_T (4)

// /usr/include/pthread.h 

#define PTHREAD_ONCE_INIT (0)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __defined_schedparam (1)

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U16_TYPE unsigned short int

// /usr/include/pthread.h 

#define PTHREAD_COND_INITIALIZER { { 0 , 0 , 0 , 0 , 0 , ( void * ) 0 , 0 , 0 } }

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONG32_TYPE int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T__

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UWORD_TYPE unsigned long int
#define _BITS_TYPES_H (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_

// /usr/include/time.h 

#define __timespec_defined (1)

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __SIZEOF_PTHREAD_RWLOCK_T (56)

// /usr/include/time.h 

#define __clock_t_defined (1)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_ZERO_S(setsize, cpusetp) do { size_t __i ; size_t __imax = ( setsize ) / sizeof ( __cpu_mask ) ; __cpu_mask * __bits = ( cpusetp ) -> __bits ; for ( __i = 0 ; __i < __imax ; ++ __i ) __bits [ __i ] = 0 ; } while ( 0 )
#define __cpu_set_t_defined

// /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h 

#define __PTHREAD_SPINS 0 , 0

// /usr/include/pthread.h 

#define PTHREAD_CANCEL_ENABLE PTHREAD_CANCEL_ENABLE

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __UQUAD_TYPE unsigned long int

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE_

// /usr/include/time.h 

#define _TIME_H (1)

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_SETSIZE (1024)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _BSD_SIZE_T_DEFINED_

// /usr/include/pthread.h 

#define PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_JOINABLE
#define PTHREAD_EXPLICIT_SCHED PTHREAD_EXPLICIT_SCHED

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPUMASK(cpu) ( ( __cpu_mask ) 1 << ( ( cpu ) % __NCPUBITS ) )

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _SIZE_T_DEFINED

// /usr/include/pthread.h 

#define PTHREAD_CANCEL_ASYNCHRONOUS PTHREAD_CANCEL_ASYNCHRONOUS

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __U32_TYPE unsigned int

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_ALLOC(count) __sched_cpualloc ( count )

// /usr/include/pthread.h 

#define _PTHREAD_H (1)

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define _T_SIZE

// /usr/include/pthread.h 

#define PTHREAD_CANCEL_DISABLE PTHREAD_CANCEL_DISABLE

// /usr/lib/gcc/x86_64-linux-gnu/6/include/stddef.h 

#define __SIZE_T
#define _BSD_SIZE_T_

// /usr/include/x86_64-linux-gnu/bits/types.h 

#define __SLONGWORD_TYPE long int

// /usr/include/x86_64-linux-gnu/bits/sched.h 

#define __CPU_OP_S(setsize, destset, srcset1, srcset2, op) ( __extension__ ( { cpu_set_t * __dest = ( destset ) ; const __cpu_mask * __arr1 = ( srcset1 ) -> __bits ; const __cpu_mask * __arr2 = ( srcset2 ) -> __bits ; size_t __imax = ( setsize ) / sizeof ( __cpu_mask ) ; size_t __i ; for ( __i = 0 ; __i < __imax ; ++ __i ) ( ( __cpu_mask * ) __dest -> __bits ) [ __i ] = __arr1 [ __i ] op __arr2 [ __i ] ; __dest ; } ) )
