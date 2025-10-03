/* scdos.h - Linux/WSL replacement for old DOS SCDOS header */

#ifndef SCDOS_H
#define SCDOS_H

#include <unistd.h>     /* for getcwd, chdir */
#include <dirent.h>     /* for directory handling */
#include <sys/stat.h>   /* for stat */
#include <limits.h>     /* for PATH_MAX */
#include <stdlib.h>     /* for malloc, free */
#include <string.h>     /* for strcpy, strncpy */
#include <stdint.h>     /* for fixed-width types */

/* --------------------------------------------------------------------
   PATH HANDLING
   -------------------------------------------------------------------- */

#ifndef MAXPATH
#define MAXPATH PATH_MAX
#endif

#ifndef MAXDRIVE
#define MAXDRIVE 3
#endif

#ifndef MAXDIR
#define MAXDIR 1024
#endif

#ifndef MAXFILE
#define MAXFILE 256
#endif

#ifndef MAXEXT
#define MAXEXT 256
#endif

/* Fake drive number (Linux has none) */
static inline int getdisk(void) { return 0; }
static inline void setdisk(int d) { (void)d; }

/* --------------------------------------------------------------------
   MEMORY PEEK/POKE STUBS
   These were used for direct memory access in DOS.
   On Linux we just no-op them or emulate safely.
   -------------------------------------------------------------------- */

#define poke(seg, off, val)   ((void)0)
#define pokeb(seg, off, val)  ((void)0)
#define peek(seg, off)        (0)
#define peekb(seg, off)       (0)

/* --------------------------------------------------------------------
   CURSOR + VIDEO MODE STUBS
   Old BIOS interrupt based. We stub these for now.
   -------------------------------------------------------------------- */

static inline void Set25(void) {}
static inline void Set43(void) {}
static inline void Set50(void) {}
static inline int isEGA(void) { return 0; }
static inline int isVGA(void) { return 1; }  /* assume VGA text */

/* --------------------------------------------------------------------
   FILE SPLIT/MERGE (DOS to POSIX shim)
   -------------------------------------------------------------------- */

static inline void fnsplit(const char *path, char *drive,
                           char *dir, char *fname, char *ext)
{
    if (drive) drive[0] = '\0'; /* no drives in Linux */
    if (dir)   strncpy(dir, path, MAXDIR);
    if (fname) fname[0] = '\0';
    if (ext)   ext[0] = '\0';
}

static inline void fnmerge(char *path, const char *drive,
                           const char *dir, const char *fname,
                           const char *ext)
{
    (void)drive;
    snprintf(path, MAXPATH, "%s/%s%s", dir ? dir : "",
             fname ? fname : "", ext ? ext : "");
}

/* --------------------------------------------------------------------
   DIRECTORY ENUMERATION (replacement for findfirst/findnext)
   -------------------------------------------------------------------- */

struct ffblk {
    char ff_name[MAXPATH];
    unsigned long ff_fsize;
    unsigned ff_attrib;
};

#define FA_DIREC  0x10
#define FA_RDONLY 0x01
#define FA_HIDDEN 0x02
#define FA_SYSTEM 0x04
#define FA_ARCH   0x20

/* Simple findfirst/findnext wrapper around opendir/readdir */
static DIR * __df_dir = NULL;

static inline int findfirst(const char *path, struct ffblk *ff, int attrib)
{
    (void)attrib;
    if (__df_dir) { closedir(__df_dir); __df_dir = NULL; }

    __df_dir = opendir(path);
    if (!__df_dir) return -1;

    struct dirent *de = readdir(__df_dir);
    if (!de) return -1;

    strncpy(ff->ff_name, de->d_name, MAXPATH);
    ff->ff_fsize = 0;
    ff->ff_attrib = 0;
    return 0;
}

static inline int findnext(struct ffblk *ff)
{
    if (!__df_dir) return -1;

    struct dirent *de = readdir(__df_dir);
    if (!de) return -1;

    strncpy(ff->ff_name, de->d_name, MAXPATH);
    ff->ff_fsize = 0;
    ff->ff_attrib = 0;
    return 0;
}

/* --------------------------------------------------------------------
   KEYBOARD + BIOS STUBS
   -------------------------------------------------------------------- */

#define bioskey(x) (0)

/* --------------------------------------------------------------------
   COMPATIBILITY WITH ORIGINAL
   -------------------------------------------------------------------- */

#define ff_name   ff_name
#define ff_fsize  ff_fsize
#define ff_attrib ff_attrib

#endif /* SCDOS_H */
