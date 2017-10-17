// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

extern int *__errno_location(void);

// /usr/include/asm-generic/errno.h 

#define ENOTEMPTY (39)

// /usr/include/asm-generic/errno-base.h 

#define ENOTBLK (15)
#define EPERM (1)

// /usr/include/asm-generic/errno.h 

#define ECONNRESET (104)
#define EREMOTEIO (121)
#define EREMOTE (66)
#define ECONNABORTED (103)
#define EAFNOSUPPORT (97)
#define EUSERS (87)
#define ENODATA (61)
#define ECONNREFUSED (111)
#define ENETDOWN (100)
#define EBFONT (59)
#define ECOMM (70)
#define ENOMEDIUM (123)
#define EILSEQ (84)
#define EUCLEAN (117)
#define ELIBSCN (81)
#define ENOTRECOVERABLE (131)
#define ENOSYS (38)
#define ERFKILL (132)
#define ENONET (64)

// /usr/include/asm-generic/errno-base.h 

#define EISDIR (21)

// /usr/include/asm-generic/errno.h 

#define ENOPROTOOPT (92)
#define ENOBUFS (105)
#define ENOTSOCK (88)
#define ENOKEY (126)
#define EISNAM (120)

// /usr/include/asm-generic/errno-base.h 

#define EBUSY (16)

// /usr/include/asm-generic/errno.h 

#define ENOSTR (60)
#define ENETUNREACH (101)
#define EL3HLT (46)
#define EKEYREVOKED (128)
#define ENOMSG (42)
#define EREMCHG (78)

// /usr/include/asm-generic/errno-base.h 

#define ENOTDIR (20)

// /usr/include/asm-generic/errno.h 

#define EPROTO (71)
#define EDOTDOT (73)

// /usr/include/asm-generic/errno-base.h 

#define ENFILE (23)

// /usr/include/x86_64-linux-gnu/bits/errno.h 

#define ENOTSUP EOPNOTSUPP

// /usr/include/asm-generic/errno.h 

#define EDEADLOCK EDEADLK

// /usr/include/x86_64-linux-gnu/bits/errno.h 

#define errno ( * __errno_location ( ) )

// /usr/include/asm-generic/errno-base.h 

#define EMFILE (24)
#define EACCES (13)

// /usr/include/asm-generic/errno.h 

#define EKEYEXPIRED (127)

// /usr/include/asm-generic/errno-base.h 

#define EROFS (30)
#define ENOEXEC (8)
#define EMLINK (31)
#define EINTR (4)
#define ERANGE (34)

// /usr/include/asm-generic/errno.h 

#define ENOTUNIQ (76)

// /usr/include/asm-generic/errno-base.h 

#define EXDEV (18)
#define EFAULT (14)
#define ESRCH (3)

// /usr/include/asm-generic/errno.h 

#define EMSGSIZE (90)

// /usr/include/asm-generic/errno-base.h 

#define EPIPE (32)

// /usr/include/asm-generic/errno.h 

#define ENOLINK (67)

// /usr/include/asm-generic/errno-base.h 

#define ETXTBSY (26)

// /usr/include/asm-generic/errno.h 

#define ENETRESET (102)

// /usr/include/asm-generic/errno-base.h 

#define EEXIST (17)

// /usr/include/asm-generic/errno.h 

#define ENOSR (63)
#define ENAVAIL (119)

// /usr/include/asm-generic/errno-base.h 

#define EBADF (9)

// /usr/include/asm-generic/errno.h 

#define EHOSTUNREACH (113)
#define EHWPOISON (133)
#define EBADMSG (74)

// /usr/include/asm-generic/errno-base.h 

#define EAGAIN (11)

// /usr/include/asm-generic/errno.h 

#define EL3RST (47)
#define ENOCSI (50)
#define ERESTART (85)
#define _ASM_GENERIC_ERRNO_H
#define EKEYREJECTED (129)

// /usr/include/asm-generic/errno-base.h 

#define EFBIG (27)

// /usr/include/asm-generic/errno.h 

#define ENOTCONN (107)
#define ESTALE (116)
#define EUNATCH (49)

// /usr/include/asm-generic/errno-base.h 

#define EDOM (33)

// /usr/include/asm-generic/errno.h 

#define EADDRINUSE (98)
#define EBADR (53)
#define ELIBEXEC (83)
#define EOWNERDEAD (130)
#define EOPNOTSUPP (95)
#define EBADE (52)
#define EDQUOT (122)
#define EWOULDBLOCK EAGAIN
#define EBADRQC (56)
#define EADV (68)

// /usr/include/asm-generic/errno-base.h 

#define ENOSPC (28)
#define ENOMEM (12)

// /usr/include/asm-generic/errno.h 

#define EBADFD (77)
#define EXFULL (54)
#define ELNRNG (48)
#define EHOSTDOWN (112)
#define EISCONN (106)

// /usr/include/asm-generic/errno-base.h 

#define ENOENT (2)

// /usr/include/asm-generic/errno.h 

#define EBADSLT (57)
#define ENOANO (55)
#define ENOLCK (37)
#define ENAMETOOLONG (36)
#define EDEADLK (35)
#define EINPROGRESS (115)

// /usr/include/asm-generic/errno-base.h 

#define ESPIPE (29)

// /usr/include/asm-generic/errno.h 

#define EADDRNOTAVAIL (99)

// /usr/include/asm-generic/errno-base.h 

#define ENOTTY (25)

// /usr/include/asm-generic/errno.h 

#define ESHUTDOWN (108)

// /usr/include/asm-generic/errno-base.h 

#define ENXIO (6)

// /usr/include/asm-generic/errno.h 

#define EMEDIUMTYPE (124)
#define ELIBMAX (82)
#define ETOOMANYREFS (109)
#define EPROTONOSUPPORT (93)

// /usr/include/asm-generic/errno-base.h 

#define EIO (5)

// /usr/include/asm-generic/errno.h 

#define EPFNOSUPPORT (96)
#define ETIME (62)
#define EALREADY (114)

// /usr/include/asm-generic/errno-base.h 

#define ENODEV (19)

// /usr/include/asm-generic/errno.h 

#define ETIMEDOUT (110)
#define ENOTNAM (118)
#define ESOCKTNOSUPPORT (94)
#define ESRMNT (69)
#define EOVERFLOW (75)
#define ESTRPIPE (86)
#define EL2HLT (51)
#define EPROTOTYPE (91)
#define ENOPKG (65)
#define EIDRM (43)
#define EMULTIHOP (72)
#define ELOOP (40)

// /usr/include/asm-generic/errno-base.h 

#define ECHILD (10)
#define E2BIG (7)
#define _ASM_GENERIC_ERRNO_BASE_H

// /usr/include/asm-generic/errno.h 

#define EL2NSYNC (45)
#define ECHRNG (44)
#define EDESTADDRREQ (89)
#define ELIBBAD (80)

// /usr/include/asm-generic/errno-base.h 

#define EINVAL (22)

// /usr/include/asm-generic/errno.h 

#define ECANCELED (125)
#define ELIBACC (79)
