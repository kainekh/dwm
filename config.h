/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 1;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 1;       /* vert inner gap between windows */
static const unsigned int gappoh    = 1;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 1;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=14", "JoyPixels:pixelsize=12:antialias=true:autohint=true"  };
static char dmenufont[]             = "monospace:size=14";

static char normbgcolor[]           = "#000000";
static char normfgcolor[]           = "#ffffff";
static char normbordercolor[]       = "#444444";

static char selbgcolor[]            = "#000000";
static char selfgcolor[]            = "#fff400";
static char selbordercolor[]        = "#eeeeee";

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ "St",       NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.90; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */
	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */


	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("") }, */
	{ MODKEY,				XK_grave,	spawn,	SHCMD("dmenuunicode") },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(				XK_1,		0)
	TAGKEYS(				XK_2,		1)
	TAGKEYS(				XK_3,		2)
	TAGKEYS(				XK_4,		3)
	TAGKEYS(				XK_5,		4)
	TAGKEYS(				XK_6,		5)
	TAGKEYS(				XK_7,		6)
	TAGKEYS(				XK_8,		7)
	TAGKEYS(				XK_9,		8)
	{ MODKEY,				XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,			XK_0,		tag,		{.ui = ~0 } },

	{ MODKEY,				XK_Tab,		view,		{0} },
	/* { MODKEY|ShiftMask,			XK_Tab,		spawn,		SHCMD("") }, */
	{ MODKEY|ShiftMask,			XK_q,		killclient,	{0} },
	{ MODKEY|Mod1Mask,			XK_F1,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|Mod1Mask,			XK_F2,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY|Mod1Mask,			XK_F3,		setlayout,	{.v = &layouts[2]} }, /* NULL */
	{ MODKEY|Mod1Mask,			XK_F5,		setlayout,	{.v = &layouts[3]} }, /* spiral */
	{ MODKEY|Mod1Mask,			XK_F6,		setlayout,	{.v = &layouts[4]} }, /* centeredmaster*/
	{ MODKEY|Mod1Mask,			XK_F7,		setlayout,	{.v = &layouts[5]} }, /* centeredfloatingmaster*/
	{ MODKEY|Mod1Mask,			XK_F8,		setlayout,	{.v = &layouts[6]} }, /* dwindle */
	{ MODKEY|Mod1Mask,			XK_F9,		setlayout,	{.v = &layouts[7]} }, /* deck */
	{ MODKEY|Mod1Mask,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,			XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,				XK_backslash,		view,		{0} },
	/* { MODKEY|ShiftMask,			XK_backslash,		spawn,		SHCMD("") }, */

	{ MODKEY|Mod1Mask,			XK_s,		togglesticky,	{0} },
	/* { MODKEY|ShiftMask,			XK_s,		spawn,		SHCMD("") }, */
	{ MODKEY,				XK_d,		spawn,          {.v = dmenucmd } },
	/* { MODKEY,				XK_d,		spawn,		SHCMD("") } }, */
	{ MODKEY,				XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,			XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,				XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,			XK_g,		shifttag,	{ .i = -1 } },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,				XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY,				XK_h,		setmfact,      	{.f = -0.05} },
	{ MODKEY,				XK_semicolon,	shifttag,	{ .i = +1 } },
	{ MODKEY|ShiftMask,			XK_semicolon,	shifttag,	{ .i = -1 } },
	{ MODKEY,				XK_apostrophe,	togglescratch,	{.ui = 1} },
	{ MODKEY|ShiftMask,			XK_apostrophe,	spawn,		SHCMD("") },
	{ MODKEY,				XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,			XK_Return,	togglescratch,	{.ui = 0} },

	{ MODKEY,                       	XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       	XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             	XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             	XK_period, tagmon,         {.i = +1 } },
	/* { MODKEY|ShiftMask,			XK_z,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,			XK_x,		spawn,		SHCMD("") }, */
	/* { MODKEY,				XK_c,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,			XK_c,		spawn,		SHCMD("") }, */
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY|Mod1Mask,			XK_b,		togglebar,	{0} },
	/* { MODKEY|ShiftMask,			XK_b,		spawn,		SHCMD("") }, */

	{ MODKEY,				XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,			XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,				XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,			XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,				XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },

	{ MODKEY,				XK_F12,		xrdb,		{.v = NULL } },
	{ MODKEY,				XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,			XK_space,	togglefloating,	{0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
