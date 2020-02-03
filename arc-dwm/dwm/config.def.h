/* See LICENSE file for copyright and license details. */


#include "push.c"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char buttonbar[]       = "        ";
static const char *fonts[]          = { "Sans:size=8" };
static const char dmenufont[]       = "Sans:size=8";
static const char col_gray1[]       = "#2B2E37";
static const char col_gray2[]       = "#252730";
static const char col_gray3[]       = "#eeeeee";
static const char col_gray4[]       = "#dddddd";
static const char col_cyan[]        = "#4084D6";
static const unsigned int baralpha = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray1 },
	[SchemeSel]  = { col_cyan, col_gray2, col_gray2  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { " Main", " Web", " Net", " Doc", " Term", " Media", " Desk" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      			instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Pinta",     			NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "firefox",  			NULL,       NULL,       1 << 1,       1,             0,           -1 },
	{ "Google-chrome",		NULL,       NULL,       1 << 1,       1,             0,           -1 },
        { "mupen64plus",                NULL,       NULL,       1 << 5,       1,             0,           -1 },
        { "retroarch",                  NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "Terminal",     		NULL,       NULL,       1 << 4,       1,             0,           -1 },
	{ "root-terminal",     		NULL,       NULL,       1 << 4,       1,             0,           -1 },
	{ "sqlmap-shell",     		NULL,       NULL,       1 << 4,       1,             0,           -1 },
	{ "st-256color",     		NULL,       NULL,       0 << 0,       1,             1,           -1 },
	{ "SimpleScreenRecorder",  	NULL,       NULL,       1 << 6,       1,             1,           -1 },
	{ "Telegram",  			NULL,       NULL,       1 << 0,       1,             0,           -1 },
	{ "deadbeef",  			NULL,       NULL,       1 << 0,       1,             0,           -1 },
	{ "Tor Browser",                NULL,       NULL,       1 << 2,       1,             0,           -1 },
        { "Transmission",               NULL,       NULL,       1 << 2,       1,             0,           -1 },
	{ "Leafpad",  			NULL,       NULL,       1 << 3,       1,             0,           -1 },
	{ "Epdfview",  			NULL,       NULL,       1 << 3,       1,             0,           -1 },
	{ "ffplay",  			NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "VirtualBox Manager",		NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "VirtualBox Machine",		NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "VirtualBox", 		NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "qemu-system-x86_64",		NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "Qemu-system-x86_64",		NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "mednafen",  			NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "feh",  			NULL,       NULL,       1 << 5,       1,             0,           -1 },
	{ "Sxiv",                       NULL,       NULL,       1 << 5,       1,             1,           -1 },
	{ "qt5ct",  			NULL,       NULL,       1 << 6,       1,             1,           -1 },
	{ "Lxappearance",		NULL,       NULL,       1 << 6,       1,             1,           -1 },
	{ "Engrampa",			NULL,       NULL,       0 << 0,       1,             1,           -1 },
        { "Mate-screenshot",            NULL,       NULL,       0 << 0,       1,             1,           -1 },
        { "Lxtask",			NULL,       NULL,       0 << 0,       1,             1,           -1 },
	{ "aft-linux-qt",  		NULL,       NULL,       1 << 6,       1,             1,           -1 },
	{ "Pavucontrol",	        NULL,       NULL,       0 << 0,       1,             1,           -1 },
        { "SmartTerm",                  NULL,       NULL,       0 << 0,       1,             1,           -1 },
        { "ROX-Filer",                  NULL,       NULL,       0 << 0,       1,             0,           -1 },
        { "dosbox",                     NULL,       NULL,       1 << 5,       0,             0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


static const Layout layouts[] = {
	/* symbol      arrange function */
	{ "Tile",      tile },              /* first entry is default */
	{ "Float",     NULL },    	    /* no layout function means floating behavior */
	{ "Monocle",   monocle },
};


/* key definitions */
#define XF86MonBrightnessDown			0x1008ff03
#define XF86MonBrightnessUp			0x1008ff02
#define XF86AudioMute				0x1008ff12
#define XF86AudioLowerVolume			0x1008ff11
#define XF86AudioRaiseVolume			0x1008ff13
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";               /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] =              { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-p", "run", NULL };
static const char *termcmd[] =               { "terminal", NULL }; /* change me to any terminal you want */
static const char *ffox[]  =                 { "firefox", NULL };
static const char *file[]  =                 { "rox", NULL };
static const char *deadbeef[]  =             { "deadbeef", NULL };
static const char *telegram[]  =             { "/opt/Telegram/Telegram", NULL };
static const char *morc[] =                  { "dwmenu", NULL };
static const char *sessmgr[] =               { "session-manager", NULL }; 
static const char *nwmgr[] =                 { "nwmgr", NULL };
static const char *connman[] =               { "st-arc", "-t", "Connman", "-e", "connmanctl", NULL };
static const char *vup[] =                   { "pactl", "set-sink-volume", "0", "+5%", NULL }; /* use it with Pulseaudio */
static const char *vdown[] =                 { "pactl", "set-sink-volume", "0", "-5%", NULL }; /* use it with Pulseaudio */
//static const char *vup[]   =                 { "amixer", "set", "Master", "3+",     NULL }; /* use it with Alsa-Utils */
//static const char *vdown[] =                 { "amixer", "set", "Master", "3-",     NULL }; /* use it with Alsa-Utils */
static const char *scrsht[] =                { "screenshot", NULL };
static const char *smart[] =                 { "smart-terminal", NULL }; /* if you set a terminal with a class "SmartTerm" dwm with treat as a foating window */
static const char *leafpad[] =               { "leafpad", NULL };
static const char *wpaper[] =                { "wallpaper", NULL };
static const char *susp[] =                  { "slock", "systemctl", "suspend", "-i", NULL };
static const char *reboot[] =                { "systemctl", "reboot", NULL };
static const char *python[] =                { "python-shell", NULL };
static const char *mtp[] =                   { "mtp", NULL };
static const char *task[] =                  { "lxtask", NULL };
static const char *plus_w[] =                { "wrm", "plus_w", NULL };
static const char *minus_w[] =               { "wrm", "minus_w", NULL };
static const char *plus_h[] =                { "wrm", "plus_h", NULL };
static const char *minus_h[] =               { "wrm", "minus_h", NULL };
static const char *up[] =                    { "wrm", "up", NULL };
static const char *down[] =                  { "wrm", "down", NULL };
static const char *left[] =                  { "wrm", "left", NULL };
static const char *right[] =                 { "wrm", "right", NULL };
static const char *next[] =                  { "tag", "next", NULL };
static const char *prev[] =                  { "tag", "prev", NULL };
static const char *rooterm[] =               { "root-terminal", NULL };
static const char *alt_gr[]  =               { "alt_gr", NULL };
static const char *lock[]  =                 { "lock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XK_Pause,  spawn,          {.v = lock } },
        { 0,                            XK_Print,  spawn,          {.v = scrsht } },
        { Mod5Mask,                     XK_Delete, spawn,          {.v = task } },
        { Mod5Mask,                     XK_l,      spawn,          {.v = leafpad } },
        { Mod5Mask|ShiftMask,           XK_Return, spawn,          {.v = rooterm } },
        { Mod1Mask|ControlMask,         XK_t,      spawn,          {.v = smart } },
	{ Mod5Mask,           		XK_p,      spawn,          {.v = dmenucmd } },
	{ Mod5Mask|ShiftMask,           XK_p,      spawn,          {.v = python } },
	{ Mod5Mask,                     XK_Return, spawn,          {.v = termcmd } },
        { Mod5Mask, 		        XK_f,      spawn,          {.v = ffox } },
	{ Mod5Mask,                     XK_a,      spawn,          {.v = mtp } },
	{ Mod5Mask,                     XK_r,      spawn,          {.v = file } },
	{ Mod5Mask,                     XK_d,      spawn,      	   {.v = deadbeef } },
        { Mod5Mask,                     XK_t,      spawn,          {.v = telegram} },
        { Mod5Mask,                     XK_n,      spawn,          {.v = connman} },
        { Mod5Mask,                     XK_F9,     spawn,          {.v = susp} },
        { Mod5Mask,                     XK_F5,     spawn,          {.v = reboot} },
	{ Mod1Mask,             	XK_w,      spawn,          {.v = wpaper } },
	{ Mod5Mask,                     XK_Up,     spawn,          {.v = up } },
	{ Mod5Mask,                     XK_Down,   spawn,          {.v = down } },
	{ Mod5Mask,                     XK_Left,   spawn,          {.v = left } },
	{ Mod5Mask,                     XK_Right,  spawn,          {.v = right } },
	{ Mod5Mask|ShiftMask,           XK_Up,     spawn,          {.v = minus_h } },
	{ Mod5Mask|ShiftMask,           XK_Down,   spawn,          {.v = plus_h } },
	{ Mod5Mask|ShiftMask,           XK_Left,   spawn,          {.v = minus_w } },
	{ Mod5Mask|ShiftMask,           XK_Right,  spawn,          {.v = plus_w } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_s,      pushdown,       {0} },
    	{ MODKEY|ShiftMask,             XK_w,      pushup,         {0} },
	{ MODKEY,                       XK_s,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_w,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_a,      setmfact,       {.f = -0.05} },
        { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_a,      incnmaster,     {.i = +1 } },
        { Mod5Mask,                     XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_space,  togglefloating, {0} },
	{ Mod5Mask,                     XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ Mod5Mask,                     XK_comma,  focusmon,       {.i = -1 } },
	{ Mod5Mask,                     XK_period, focusmon,       {.i = +1 } },
	{ Mod5Mask|ShiftMask,           XK_comma,  tagmon,         {.i = -1 } },
	{ Mod5Mask|ShiftMask,           XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,		        XK_x,      spawn,          {.v = morc} },
	{ MODKEY,                       XK_q,      spawn,          {.v = prev} },
	{ MODKEY,                       XK_e,      spawn,          {.v = next} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
        { MODKEY,                       XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
        { ClkButton,		0,		Button1,	spawn,		{.v = morc } },
	{ ClkButton,            0,              Button2,        spawn,          {.v = alt_gr } },
        { ClkButton,            0,              Button3,        spawn,          {.v = sessmgr } },
        { ClkButton,            0,              Button4,        incnmaster,     {.i = +1 } },
        { ClkButton,            0,              Button5,        incnmaster,     {.i = -1 } },
        { ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button4,        pushup,         {.i = -1 } },
	{ ClkLtSymbol,          0,              Button5,      	pushdown,       {.i = +1 } },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = -1 } },
        { ClkWinTitle,          0,              Button5,        focusstack,     {.i = +1 } },
        { ClkWinTitle,          0,              Button2,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button1,	movemouse,      {0} },
        { ClkWinTitle,          0,              Button3,        resizemouse,    {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
        { ClkStatusText,        0,              Button1,        spawn,          {.v = nwmgr } },
        { ClkStatusText,        0,              Button3,        spawn,          {.v = nwmgr } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = vup } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = vdown } },
	{ ClkClientWin,         Mod5Mask,       Button1,        movemouse,      {0} },
	{ ClkClientWin,         Mod5Mask,       Button2,        killclient,     {0} },
	{ ClkClientWin,         Mod5Mask,       Button3,        resizemouse,    {0} },
	{ ClkClientWin,         Mod5Mask,       Button4,        togglefloating, {0} },
	{ ClkClientWin,         Mod5Mask,       Button5,        togglefloating, {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button2,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button3,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
        { ClkTagBar,            0,              Button4,        spawn,		{.v = prev } },
	{ ClkTagBar,            0,              Button5,        spawn,		{.v = next } },
        { ClkRootWin,           0,              Button1,        movemouse,      {0} },
        { ClkRootWin,           0,              Button3,        resizemouse,    {0} },
        { ClkRootWin,           0,              Button2,        killclient,     {0} },
        { ClkRootWin,           0,              Button4,        focusstack,     {.i = -1 } },
	{ ClkRootWin,           0,              Button5,        focusstack,     {.i = +1 } },
};

