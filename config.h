/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "Hack:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005f5f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};


/* tagging */
static const char *tags[] = { "A", "O", "E", "U", "1" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "Firefox",      NULL,       NULL,       1 << 2,       0,           0 },
	{ "Google-chrome",NULL,       NULL,       1 << 2,       0,           0 },
	{ "tabbed-surf",  NULL,       "surf",     1 << 2,       0,           0 },
	{ "Slack",        NULL,       NULL,       1 << 4,       0,           0 },
	{ "as5911",       NULL,       NULL,       0 << 0,       0,           0 },
};

/* layout(s) */
static const int dirs[3]      = { DirHor, DirVer, DirVer }; /* tiling dirs */
static const float facts[3]   = { 1.1,    1.1,    1.1 };    /* tiling facts */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "<||",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define TILEKEYS(MOD,G,M,S) \
	{ MOD, XK_r, setdirs,  {.v = (int[])  { INC(G * +1),   INC(M * +1),   INC(S * +1) } } }, \
	{ MOD, XK_h, setfacts, {.v = (float[]){ INC(G * -0.1), INC(M * -0.1), INC(S * -0.1) } } }, \
	{ MOD, XK_l, setfacts, {.v = (float[]){ INC(G * +0.1), INC(M * +0.1), INC(S * +0.1) } } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,      spawn,          SHCMD("~/source/dotfiles/scripts/password-store.sh") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD("~/source/dotfiles/scripts/bookmarks-surf.sh") },
	{ ShiftMask,        		XK_Print,  spawn,          SHCMD("~/source/dotfiles/scripts/selection-screenshot.sh") },
	{ ShiftMask|ControlMask,        XK_Print,  spawn,          SHCMD("~/source/dotfiles/scripts/selection-screenshot-clipboard.sh") },
	{ 0,	        		XK_Print,  spawn,          SHCMD("~/source/dotfiles/scripts/screenshot-focused.sh") },
	{ ControlMask,	        	XK_Print,  spawn,          SHCMD("~/source/dotfiles/scripts/screenshot-focused-clipboard.sh") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_t,      setdirs,        {.v = (int[]){ DirHor, DirVer, DirVer } } },
	{ MODKEY|ControlMask,           XK_t,      setdirs,        {.v = (int[]){ DirVer, DirHor, DirHor } } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
	TILEKEYS(MODKEY,                                           1, 0, 0)
	TILEKEYS(MODKEY|ShiftMask,                                 0, 1, 0)
	TILEKEYS(MODKEY|ControlMask,                               0, 0, 1)
	TILEKEYS(MODKEY|ShiftMask|ControlMask,                     1, 1, 1)
	TAGKEYS(                        XK_a,                      0)
	TAGKEYS(                        XK_o,                      1)
	TAGKEYS(                        XK_e,                      2)
	TAGKEYS(                        XK_u,                      3)
	TAGKEYS(                        XK_1,                      4)
	TAGKEYS(                        XK_2,                      5)
	TAGKEYS(                        XK_3,                      6)
	TAGKEYS(                        XK_4,                      7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

