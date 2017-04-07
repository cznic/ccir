// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

// ----------------------------------------------------------------------------
//      /usr/include/signal.h
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

#define _SIGSET_H_types (1)
typedef int __sig_atomic_t;
#define _SIGSET_NWORDS ( 1024 / ( 8 * sizeof ( unsigned long int ) ) )
typedef struct {
	unsigned long int __val[16l];
} __sigset_t;
#define _SIGSET_H_fns (1)
#define _EXTERN_INLINE __extern_inline
#define __sigmask(sig) ( ( ( unsigned long int ) 1 ) << ( ( ( sig ) - 1 ) % ( 8 * sizeof ( unsigned long int ) ) ) )
#define __sigword(sig) ( ( ( sig ) - 1 ) / ( 8 * sizeof ( unsigned long int ) ) )
extern int __sigismember(__sigset_t *, int);
extern int __sigaddset(__sigset_t *, int);
extern int __sigdelset(__sigset_t *, int);
#define _SIGNAL_H
#define __sig_atomic_t_defined
typedef __sig_atomic_t sig_atomic_t;
typedef void (*__sighandler_t) (int);
extern __sighandler_t __sysv_signal(int __sig, __sighandler_t __handler);
#define signal __sysv_signal
extern int raise(int __sig);
extern int __libc_current_sigrtmin(void);
extern int __libc_current_sigrtmax(void);
#define SIG_ERR (-1)
#define SIG_DFL ( ( __sighandler_t ) 0 )
#define SIG_IGN ( ( __sighandler_t ) 1 )
#define SIGHUP (1)
#define SIGINT (2)
#define SIGQUIT (3)
#define SIGILL (4)
#define SIGTRAP (5)
#define SIGABRT (6)
#define SIGIOT (6)
#define SIGBUS (7)
#define SIGFPE (8)
#define SIGKILL (9)
#define SIGUSR1 (10)
#define SIGSEGV (11)
#define SIGUSR2 (12)
#define SIGPIPE (13)
#define SIGALRM (14)
#define SIGTERM (15)
#define SIGSTKFLT (16)
#define SIGCLD SIGCHLD
#define SIGCHLD (17)
#define SIGCONT (18)
#define SIGSTOP (19)
#define SIGTSTP (20)
#define SIGTTIN (21)
#define SIGTTOU (22)
#define SIGURG (23)
#define SIGXCPU (24)
#define SIGXFSZ (25)
#define SIGVTALRM (26)
#define SIGPROF (27)
#define SIGWINCH (28)
#define SIGPOLL SIGIO
#define SIGIO (29)
#define SIGPWR (30)
#define SIGSYS (31)
#define SIGUNUSED (31)
#define _NSIG (65)
#define SIGRTMIN ( __libc_current_sigrtmin ( ) )
#define SIGRTMAX ( __libc_current_sigrtmax ( ) )
#define __SIGRTMIN (32)
#define __SIGRTMAX (64)
