// Code generated by running "go generate". DO NOT EDIT.

// +build ignore

	typedef unsigned long XID ;
typedef unsigned long Mask ;
typedef unsigned long Atom ;
typedef unsigned long VisualID ;
typedef unsigned long Time ;
typedef XID Window ;
typedef XID Drawable ;
typedef XID Font ;
typedef XID Pixmap ;
typedef XID Cursor ;
typedef XID Colormap ;
typedef XID GContext ;
typedef XID KeySym ;
typedef unsigned char KeyCode ;


// /usr/include/X11/X.h 

#define GrabSuccess (0)
#define ButtonReleaseMask (8l)
#define UnmapGravity (0)
#define Success (0)
#define ColormapUninstalled (0)
#define GXandReverse (2)
#define Button3MotionMask (1024l)
#define BadCursor (6)
#define X_PROTOCOL (11)
#define Button4Mask (2048)
#define SelectionClear (29)
#define DontPreferBlanking (0)
#define MappingNotify (34)
#define GrabFrozen (4)
#define MappingFailed (2)
#define Expose (12)
#define SouthEastGravity (9)
#define ColormapInstalled (1)
#define TileShape (1)
#define AnyKey (0l)
#define ScreenSaverReset (0)
#define GCTileStipYOrigin (8192l)
#define RetainPermanent (1)
#define SetModeDelete (1)
#define DisableScreenInterval (0)
#define HostInsert (0)
#define FontLeftToRight (0)
#define GXclear (0)
#define StaticColor (2)
#define FontRightToLeft (1)
#define ExposureMask (32768l)
#define FillOpaqueStippled (3)
#define ScreenSaverActive (1)
#define ResizeRedirectMask (262144l)
#define Button2MotionMask (512l)
#define SelectionRequest (30)
#define CenterGravity (5)
#define FamilyInternet (0)
#define VisibilityNotify (15)
#define CWBackPixmap (1l)
#define Convex (2)
#define GCTileStipXOrigin (4096l)
#define ButtonPressMask (4l)
#define CWDontPropagate (4096l)
#define FocusChangeMask (2097152l)
#define NotifyNonlinearVirtual (4)
#define _XTYPEDEF_XID 
#define CWWidth (4)
#define CWBorderPixel (8l)
#define MappingBusy (1)
#define BadValue (2)
#define DoGreen (2)
#define VisibilityFullyObscured (2)
#define KeymapStateMask (16384l)
#define GXand (1)
#define VisibilityPartiallyObscured (1)
#define LeaveNotify (8)
#define PropModePrepend (1)
#define LineDoubleDash (2)
#define NotifyHint (1)
#define CWHeight (8)
#define PseudoColor (3)
#define EnterNotify (7)
#define LockMapIndex (1)
#define GrabModeAsync (1)
#define YSorted (1)
#define NotifyNonlinear (3)
#define _XTYPEDEF_FONT 
#define ColormapChangeMask (8388608l)
#define CWY (2)
#define CWBorderPixmap (4l)
#define TrueColor (4)
#define IsViewable (2)
#define InputFocus (1l)
#define KeyPressMask (1l)
#define IsUnviewable (1)
#define CWWinGravity (32l)
#define MSBFirst (1)
#define CoordModeOrigin (0)
#define GXnor (8)
#define StippleShape (2)
#define PointerRoot (1l)
#define GCLineStyle (32l)
#define KBLed (16l)
#define YXBanded (3)
#define GCForeground (4l)
#define ShiftMapIndex (0)
#define NotUseful (0)
#define MappingPointer (2)
#define Nonconvex (1)
#define CWX (1)
#define Mod4Mask (64)
#define AsyncPointer (0)
#define ButtonPress (4)
#define Mod1Mask (8)
#define Button4MotionMask (2048l)
#define BadRequest (1)
#define BadWindow (3)
#define GXandInverted (4)
#define LowerHighest (1)
#define AllocNone (0)
#define GCClipYOrigin (262144l)
#define MapNotify (19)
#define AutoRepeatModeDefault (2)
#define BadLength (16)
#define GCGraphicsExposures (65536l)
#define RevertToPointerRoot ( int ) PointerRoot
#define ClientMessage (33)
#define ConfigureNotify (22)
#define DontAllowExposures (0)
#define CapProjecting (3)
#define GCJoinStyle (128l)
#define CWSaveUnder (1024l)
#define FocusOut (10)
#define LedModeOn (1)
#define CursorShape (0)
#define CirculateNotify (26)
#define GCDashList (2097152l)
#define SubstructureNotifyMask (524288l)
#define RevertToNone ( int ) None
#define PointerMotionHintMask (128l)
#define FirstExtensionError (128)
#define X_PROTOCOL_REVISION (0)
#define ForgetGravity (0)
#define EvenOddRule (0)
#define GCArcMode (4194304l)
#define None (0l)
#define SyncBoth (7)
#define NorthEastGravity (3)
#define NotifyPointerRoot (6)
#define InputOnly (2)
#define PointerMotionMask (64l)
#define JoinBevel (2)
#define AutoRepeatModeOn (1)
#define XYPixmap (1)
#define RevertToParent (2)
#define GXnoop (5)
#define CWSibling (32)
#define Mod4MapIndex (6)
#define GCClipXOrigin (131072l)
#define KBLedMode (32l)
#define Button1Mask (256)
#define NotifyInferior (2)
#define Button5Mask (4096)
#define CoordModePrevious (1)
#define NotifyAncestor (0)
#define GCFont (16384l)
#define NotifyNormal (0)
#define DestroyAll (0)
#define CWEventMask (2048l)
#define GXor (7)
#define StaticGray (0)
#define BadGC (13)
#define SyncKeyboard (4)
#define Button1 (1)
#define MapRequest (20)
#define DoBlue (4)
#define GCFillRule (512l)
#define XYBitmap (0)
#define DefaultExposures (2)
#define Button2 (2)
#define AnyPropertyType (0l)
#define BadIDChoice (14)
#define BadAccess (10)
#define Mod2MapIndex (4)
#define DoRed (1)
#define IsUnmapped (0)
#define ColormapNotify (32)
#define CurrentTime (0l)
#define SouthWestGravity (7)
#define ReplayPointer (2)
#define Button3 (3)
#define KeyReleaseMask (2l)
#define LineOnOffDash (1)
#define NotifyWhileGrabbed (3)
#define Button5MotionMask (4096l)
#define AsyncKeyboard (3)
#define GrabModeSync (0)
#define GXset (15)
#define PropertyNewValue (0)
#define Button4 (4)
#define BadAtom (5)
#define GCClipMask (524288l)
#define MappingModifier (0)
#define BadPixmap (4)
#define ReparentNotify (21)
#define RaiseLowest (0)
#define MappingSuccess (0)
#define ButtonMotionMask (8192l)
#define PlaceOnBottom (1)
#define X_H 
#define UnmapNotify (18)
#define KBBellDuration (8l)
#define EastGravity (6)
#define GXnand (14)
#define Button5 (5)
#define LineSolid (0)
#define KBAutoRepeatMode (128l)
#define CopyFromParent (0l)
#define CapRound (2)
#define MappingKeyboard (1)
#define AllTemporary (0l)
#define NotifyGrab (1)
#define KeymapNotify (11)
#define CapNotLast (0)
#define VisibilityUnobscured (0)
#define DisableScreenSaver (0)
#define GCLineWidth (16l)
#define EnterWindowMask (16l)
#define ArcChord (0)
#define NotifyDetailNone (7)
#define FocusIn (9)
#define ButtonRelease (5)
#define Opposite (4)
#define NoExpose (14)
#define WhenMapped (1)
#define WestGravity (4)
#define CWColormap (8192l)
#define ConfigureRequest (23)
#define StaticGravity (10)
#define EnableAccess (1)
#define KeyRelease (3)
#define BadImplementation (17)
#define Button1MotionMask (256l)
#define _XTYPEDEF_MASK 
#define GrabNotViewable (3)
#define Mod5MapIndex (7)
#define SubstructureRedirectMask (1048576l)
#define DirectColor (5)
#define AnyModifier (32768)
#define GCSubwindowMode (32768l)
#define PropertyChangeMask (4194304l)
#define SyncPointer (1)
#define CWBorderWidth (16)
#define AutoRepeatModeOff (0)
#define GXinvert (10)
#define CWBitGravity (16l)
#define JoinRound (1)
#define ParentRelative (1l)
#define GCDashOffset (1048576l)
#define NotifyVirtual (1)
#define FamilyInternet6 (6)
#define GXxor (6)
#define CirculateRequest (27)
#define GXorInverted (13)
#define LASTEvent (36)
#define LeaveWindowMask (32l)
#define CWStackMode (64)
#define BadAlloc (11)
#define AlreadyGrabbed (1)
#define ShiftMask (1)
#define RetainTemporary (2)
#define WindingRule (1)
#define NorthGravity (2)
#define ArcPieSlice (1)
#define OwnerGrabButtonMask (16777216l)
#define GCBackground (8l)
#define YXSorted (2)
#define AsyncBoth (6)
#define GXequiv (9)
#define CWCursor (16384l)
#define ReplayKeyboard (5)
#define InputOutput (1)
#define Mod5Mask (128)
#define LSBFirst (0)
#define KBKey (64l)
#define GCTile (1024l)
#define KBKeyClickPercent (1l)
#define CapButt (1)
#define ClipByChildren (0)
#define GCFillStyle (256l)
#define HostDelete (1)
#define PointerWindow (0l)
#define VisibilityChangeMask (65536l)
#define Above (0)
#define AllocAll (1)
#define BottomIf (3)
#define NoSymbol (0l)
#define CWOverrideRedirect (512l)
#define GravityNotify (24)
#define LedModeOff (0)
#define PlaceOnTop (0)
#define FamilyServerInterpreted (5)
#define Mod2Mask (16)
#define ResizeRequest (25)
#define Below (1)
#define DisableAccess (0)
#define GXcopy (3)
#define FamilyChaos (2)
#define Always (2)
#define DefaultBlanking (2)
#define PropertyDelete (1)
#define GXcopyInverted (12)
#define IncludeInferiors (1)
#define CreateNotify (16)
#define NoEventMask (0l)
#define ControlMask (4)
#define Complex (0)
#define CWBackingPlanes (128l)
#define GCLastBit (22)
#define GCStipple (2048l)
#define Mod3Mask (32)
#define BadColor (12)
#define BadFont (7)
#define KBBellPitch (4l)
#define Unsorted (0)
#define GraphicsExpose (13)
#define Button3Mask (1024)
#define AnyButton (0l)
#define KeyPress (2)
#define BadName (15)
#define GenericEvent (35)
#define GXorReverse (11)
#define ZPixmap (2)
#define SelectionNotify (31)
#define PropModeAppend (2)
#define SetModeInsert (0)
#define LastExtensionError (255)
#define GCFunction (1l)
#define Button2Mask (512)
#define PropertyNotify (28)
#define MotionNotify (6)
#define CWBackPixel (2l)
#define SouthGravity (8)
#define GrayScale (1)
#define GCCapStyle (64l)
#define AllowExposures (1)
#define BadMatch (8)
#define FillSolid (0)
#define GCPlaneMask (2l)
#define TopIf (2)
#define Mod1MapIndex (3)
#define StructureNotifyMask (131072l)
#define KBBellPercent (2l)
#define ControlMapIndex (2)
#define PropModeReplace (0)
#define CWBackingStore (64l)
#define DestroyNotify (17)
#define FamilyDECnet (1)
#define Mod3MapIndex (5)
#define FillTiled (1)
#define GrabInvalidTime (2)
#define FontChange (255)
#define JoinMiter (0)
#define BadDrawable (9)
#define FillStippled (2)
#define NotifyUngrab (2)
#define NotifyPointer (5)
#define LockMask (2)
#define NorthWestGravity (1)
#define _XTYPEDEF_ATOM 
#define CWBackingPixel (256l)
#define PreferBlanking (1)
