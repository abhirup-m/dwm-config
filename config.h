/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Roboto Mono:size=14" };
static const char dmenufont[]       = "Roboto Mono-14";
static const char col_darkgray[]       = "#2D2D2D";
static const char col_lightgray[]       = "#4D4D4D";
static const char col_palewhite[]       = "#DCDCDC";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_palewhite, col_darkgray,  col_palewhite},
	[SchemeSel]  = { col_palewhite, col_darkgray,  col_palewhite},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask    switchtotag   isfloating   monitor */
	{ "Google-chrome-beta",       NULL,       NULL,       1 << 0,       1,			0,           -1 },
	{ "Caja",         NULL,       NULL,       1 << 1,       1,			0,           -1 },
	{ "st-256color",    NULL,       NULL,       1 << 2,       1,			0,           -1 },
	{ "Editor",       NULL,       NULL,       1 << 3,       1,			0,           -1 },
	{ "Evince",       NULL,       NULL,       1 << 4 ,      1,			1,           -1 },
	{ "Inkscape",     NULL,       NULL,       1 << 5 ,      1,			0,           -1 },
	{ "float-term",   NULL,       NULL,       0 ,           0,			1,           -1 },
	{ "Celluloid",    NULL,       NULL,       0 ,           0,			1,           -1 },
	{ "Lxappearance", NULL,       NULL,       0 ,           0,			1,           -1 },
	{ "Gpick", 		  NULL,       NULL,       0 ,           0,			1,           -1 },
	{ "Gpicview", 	  NULL,       NULL,       0 ,           0,			1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-f", "-i", "-l", "20", "-fn", dmenufont, "-sb", col_lightgray, "-sf", col_palewhite, "-nb", col_darkgray, "-nf", col_palewhite, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webcmd[]  = { "google-chrome-beta", NULL };
static const char *explorercmd[]  = { "caja", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *logoutcmd[]  =  { "killall", "xinit", NULL };
static const char *lightupcmd[]  =  { "brightnessctl", "set", "100+", NULL };
static const char *lightdowncmd[]  =  { "brightnessctl", "set", "100-", NULL };
static const char *volumeupcmd[]  =  { "amixer", "set", "Master", "5%+", NULL };
static const char *volumedowncmd[]  =  { "amixer", "set", "Master", "5%-", NULL };
static const char *rebootcmd[]  =  { "systemctl", "reboot", "-i", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = explorercmd } },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("st -c Editor nvim")},
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = logoutcmd } },
	{ MODKEY|ShiftMask,             XK_equal,  spawn,          {.v = lightupcmd } },
	{ MODKEY|ShiftMask,             XK_minus,  spawn,          {.v = lightdowncmd } },
	{ MODKEY|ControlMask,           XK_equal,  spawn,          {.v = volumeupcmd } },
	{ MODKEY|ControlMask,           XK_minus,  spawn,          {.v = volumedowncmd } },
	{ MODKEY|ShiftMask,           	XK_y,      spawn,          {.v = rebootcmd } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_comma,  setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_period, setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_slash,  setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

