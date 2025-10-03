// include/dflat/window.h
#ifndef DFLAT_WINDOW_H
#define DFLAT_WINDOW_H


#include <dflat/rect.h>
#include <dflat/window.h>
#include <dflat/menu.h>
#include <dflat/rect.h>
#include <dflat/keys.h>
#include <dflat/dialbox.h>

#include <dflat/system.h>     // BOOL, TRUE, FALSE
#include <dflat/classdef.h>   // CLASS enum
#include <dflat/dflatmsg.h>   // MESSAGE, PARAM, message constants
#include <dflat/rect.h>       // RECT struct
#include <dflat/window.h>     // WINDOW struct and functions

// Other framework headers
#include <dflat/menu.h>
#include <dflat/keys.h>
#include <dflat/dialbox.h>
#include <dflat/helpbox.h>
#include <dflat/htree.h>
#include <dflat/config.h>
#include <dflat/commands.h>
#include <dflat/classes.h>
#include <dflat/scdos.h>
#include <dflat/video.h>

// also define BOOL if not defined
#ifndef BOOL
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#endif

#endif // DFLAT_WINDOW_H
