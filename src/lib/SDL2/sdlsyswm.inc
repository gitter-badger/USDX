// from sdl_syswm.h

{$IFDEF WINDOWS}
   {$DEFINE SDL_VIDEO_DRIVER_WINDOWS}
{$ENDIF}

{$IF DEFINED (LINUX) OR DEFINED(UNIX)}
   {$DEFINE SDL_VIDEO_DRIVER_X11}
{$IFEND}

{$IFDEF DARWIN}
   {$DEFINE SDL_VIDEO_DRIVER_COCOA}
{$ENDIF}

{**
 *  These are the various supported windowing subsystems
 *}
Type
   TSDL_SYSWM_TYPE = (
      SDL_SYSWM_UNKNOWN,
      SDL_SYSWM_WINDOWS,
      SDL_SYSWM_X11,
      SDL_SYSWM_DIRECTFB,
      SDL_SYSWM_COCOA,
      SDL_SYSWM_UIKIT,
      SDL_SYSWM_WAYLAND, // Since SDL 2.0.2
      SDL_SYSWM_MIR,     // Since SDL 2.0.2
      SDL_SYSWM_WINRT,   // Since SDL 2.0.3
      SDL_SYSWM_ANDROID  // Planned for SDL 2.0.4
   );

/// sdl_syswm.h uses anonymous structs, declared right in SDL_SysWMmsg.
/// Since Pascal does not allow this, we workaround by introducing named types
/// before the proper TSDL_SysWMmsg definition.
{$IFDEF SDL_VIDEO_DRIVER_WINDOWS}
   __SYSWM_WINDOWS = record
      hwnd:   HWND;   {**< The window for the message }
      msg:     uInt;   {**< The type of message *}
      wParam: WPARAM; {**< WORD message parameter *}
      lParam: LPARAM; {**< WORD message parameter *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_X11}
   __SYSWM_X11 = record
      event: {$IFDEF FPC} TXEvent {$ELSE} XEvent {$ENDIF};
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_DIRECTFB}
   __SYSWM_DIRECTFB = record
      event: DFBEvent;
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_COCOA}
   __SYSWM_COCOA = record
      (* No Cocoa window events yet *)
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_UIKIT}
   __SYSWM_UIKIT = record
      (* No UIKit window events yet *)
   end;
{$ENDIF}

{**
 *  The custom event structure.
 *}
   PSDL_SysWMmsg = ^TSDL_SysWMmsg;
   TSDL_SysWMmsg = record
      version: TSDL_version;
      Case subsystem: TSDL_SYSWM_TYPE of
         (* Cannot have empty record case *)
         SDL_SYSWM_UNKNOWN: (dummy: sInt32);
         {$IFDEF SDL_VIDEO_DRIVER_WINDOWS}
            SDL_SYSWM_WINDOWS: (win: __SYSWM_WINDOWS);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_X11}
            SDL_SYSWM_X11: (x11: __SYSWM_X11);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_DIRECTFB}  
            SDL_SYSWM_DIRECTFB: (dfb: __SYSWM_DIRECTFB); 
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_COCOA}  
            SDL_SYSWM_COCOA: (cocoa: __SYSWM_COCOA);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_UIKIT}
            SDL_SYSWM_UIKIT: (uikit: __SYSWM_UIKIT);
         {$ENDIF}
   end;

/// Once again, sdl_syswm.h uses anonymous structs, declared right in SDL_SysWMinfo.
/// We workaround by introducing named types before the proper TSDL_SysWMinfo definition.
{$IFDEF SDL_VIDEO_DRIVER_WINDOWS}
   __WMINFO_WINDOWS = record
      window: HWND; {**< The window handle *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_WINRT} // Since SDL 2.0.3
   __WMINFO_WINRT = record
      window: IInspectable;      {**< The WinRT CoreWindow *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_X11}
   __WMINFO_X11 = record
      display: PDisplay;  {**< The X11 display *}
      window: TWindow;     {**< The X11 window *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_DIRECTFB}
   __WMINFO_DFB = record
      dfb:     IDirectFB;         {**< The directfb main interface *}
      window:  IDirectFBWindow;   {**< The directfb window handle *}
      surface: IDirectFBSurface;  {**< The directfb client surface *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_COCOA}
   __WMINFO_COCOA = record
      window: NSWindow;           {* The Cocoa window *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_UIKIT}
   __WMINFO_UIKIT = record
      window: UIWindow;   {* The UIKit window *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_WAYLAND} // Since SDL 2.0.2
   __WMINFO_WAYLAND = record
      display: wl_display;             {**< Wayland display *}
      surface: wl_surface;             {**< Wayland surface *}
      shell_surface: wl_shell_surface; {**< Wayland shell_surface (window manager handle) *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_MIR} // Since SDL 2.0.2
   __WMINFO_MIR = record
      connection: PMirConnection; {**< Mir display server connection *}
      surface: PMirSurface;       {**< Mir surface *}
   end;
{$ENDIF}
{$IFDEF SDL_VIDEO_DRIVER_ANDROID} // Planned for SDL 2.0.4
   __WMINFO_ANDROID = record
      window : PANativeWindow;
      surface: PEGLSurface;
   end;
{$ENDIF}

{**
 *  The custom window manager information structure.
 *
 *  When this structure is returned, it holds information about which
 *  low level system it is using, and will be one of SDL_SYSWM_TYPE.
 *}
   PSDL_SysWMinfo = ^TSDL_SysWMinfo;
   TSDL_SysWMinfo = record
      version: TSDL_version;
      Case subsystem: TSDL_SYSWM_TYPE of
         (* Cannot have empty record case *)
         SDL_SYSWM_UNKNOWN: (dummy: sInt32);
         {$IFDEF SDL_VIDEO_DRIVER_WINDOWS}
            SDL_SYSWM_WINDOWS: (win : __WMINFO_WINDOWS);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_WINRT}
            SDL_SYSWM_WINRT: (winrt : __WMINFO_WINRT);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_X11}
            SDL_SYSWM_X11: (x11 : __WMINFO_X11);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_DIRECTFB}
            SDL_SYSWM_DIRECTFB: (dfb : __WMINFO_DFB);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_COCOA}
            SDL_SYSWM_COCOA: (cocoa : __WMINFO_COCOA);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_UIKIT}
            SDL_SYSWM_UIKIT: (uikit : __WMINFO_UIKIT);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_WAYLAND}
            SDL_SYSWM_WAYLAND: (wl : __WMINFO_WAYLAND);
         {$ENDIF}
         {$IFDEF SDL_VIDEO_DRIVER_MIR}
            SDL_SYSWM_MIR: (mir : __WMINFO_MIR);
         {$ENDIF}
   end;

{* Function prototypes *}
(**
 *  \brief This function allows access to driver-dependent window information.
 *
 *  \param window The window about which information is being requested
 *  \param info This structure must be initialized with the SDL version, and is
 *              then filled in with information about the given window.
 *
 *  \return SDL_TRUE if the function is implemented and the version member of
 *          the \c info struct is valid, SDL_FALSE otherwise.
 *
 *  You typically use this function like this:
 *  \code
 *  SDL_SysWMinfo info;
 *  SDL_VERSION(&info.version);
 *  if ( SDL_GetWindowWMInfo(window, &info) ) { ... }
 *  \endcode
 *)
Function SDL_GetWindowWMInfo(window:PSDL_Window; info : PSDL_SysWMinfo):TSDL_bool; cdecl;
   external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetWindowWMInfo' {$ENDIF} {$ENDIF};
