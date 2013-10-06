#include "psp.h"

extern int os9x_language;
extern const char *os9x_btn_positive_str;
extern const char *os9x_btn_negative_str;

#define MSG_BTN_POSITIVE "\x81\x0B"
#define MSG_BTN_NEGATIVE "\x81\x0E"

#define MSG_TOTAL_ENTRIES 304
typedef struct {
	int msg_id;
	char *msg;
	int len;  // MSG_DEFAULT : to use default
		  // >=0 : wait for len frames, 
		  //  -1 : wait for a confirmation before closing dialog
		  //  -2 : yes/no dialog
} t_err_entry;

t_err_entry s9xTYL_msg_en[MSG_TOTAL_ENTRIES]= {
//english
	//error
	{ERR_OUT_OF_MEM,"Out of memory",60},
	{ERR_READ_MEMSTICK,"Error reading memstick.\nPlease verify it (using a PC card reader), it may be corrupted.",60},

	{ERR_INIT_SNES,"Cannot init snes, memory issue",2*60},
	{ERR_LOADING_ROM,"Error while loading rom",60*2},
	{ERR_INIT_GFX,"Cannot initialize graphics",60*2},

	{ERR_CANNOT_ALLOC_MEM,"Cannot allocate memory",30},

	{ERR_USB_STARTING_USBBUS,"Error starting USB Bus driver (0x%08X)\n",0},
	{ERR_USB_STARTING_USBMASS,"Error starting USB Mass Storage driver (0x%08X)\n",0},
	{ERR_USB_SETTING_CAPACITY,"Error setting capacity with USB Mass Storage driver (0x%08X)\n",0},
	//confirm
	{ASK_EXIT,"Exit Snes9XTYL ?",-2},
	{ASK_DELETE,"Delete file ?",-2},
	{ASK_SAVEDIR,"The save directory is not found.\n"
		"To make the directory in the directory where this emulator is, Press " SJIS_CIRCLE  "\n"
		"To make the directory in SAVEDATA directory, Press " SJIS_CROSS "\n",
		0},
	//info
	{INFO_USB_ON,"USB activated",30},
	{INFO_USB_OFF,"USB disabled",30},
	{INFO_DELETING,"Deleting...",0},
	{INFO_EXITING,"Exiting, please wait...",0},
	//filer
	{FILER_STATUS_CANEXIT1,MSG_BTN_POSITIVE " RUN " SJIS_SQUARE " RUN default settings  " SJIS_STAR "  " MSG_BTN_NEGATIVE " TO GAME  "  SJIS_STAR "  " SJIS_TRIANGLE " %s  "  SJIS_STAR "  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT ", to browse",0},
	{FILER_STATUS_NOEXIT1,MSG_BTN_POSITIVE " RUN " SJIS_SQUARE " RUN default settings  "  SJIS_STAR "  " SJIS_TRIANGLE " %s          " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT ", to browse list",0},
	{FILER_STATUS_CANEXIT2,MSG_BTN_POSITIVE " RUN " MSG_BTN_NEGATIVE "BACK TO GAME " SJIS_TRIANGLE " %s  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT ", to browse list",0},
	{FILER_STATUS_NOEXIT2,MSG_BTN_POSITIVE " RUN " SJIS_TRIANGLE " %s                  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT ", to browse list",0},

	{FILER_STATUS_PARDIR, "Parent dir.", 0},

	{FILER_TITLE, "[" EMUNAME_VERSION "] - Choose a file", 0},
	
	{FILER_HELP_WINDOW1,"Press START to switch between",0},
	{FILER_HELP_WINDOW2,"NORMAL and NETPLAY mode.",0},
#ifdef FW3X
	{FILER_HELP_WINDOW3," ",0},
#ifdef HOME_HOOK
	{FILER_HELP_WINDOW4,"Press HOME to exit.",0},
#else
    {FILER_HELP_WINDOW4,"Press L+R to exit.",0},
#endif
#else
#ifdef HOME_HOOK
    {FILER_HELP_WINDOW3,"Press HOME to exit.",0},
#else
    {FILER_HELP_WINDOW3,"Press L+R to exit.",0},
#endif
	{FILER_HELP_WINDOW4,"Press R to switch USB on/off.",0},
#endif


	{FILER_HELP_WINDOW5,"Press SELECT to delete file.",0},

	{FILE_IPS_APPLYING,"Found IPS patch : %s\nSize is : %dKo\nApplying ....",0},
	{FILE_IPS_PATCHSUCCESS,"IPS Patch applied successfully",0},
	
	{MENU_STATUS_GENERIC_MSG1,"Press " MSG_BTN_NEGATIVE " to return",0},
	{MENU_STATUS_GENERIC_NEEDRELOAD,"Changes may require a RELOAD to take effect",0},
	{MENU_STATUS_GENERIC_NEEDRESET,"Changes may require a RESET to take effect",0},
	{MENU_STATUS_GENERIC_FREERAM,"Free RAM : %dKo",0},
	{MENU_STATUS_GENERIC_CHANGEMUSIC,"SELECT to change music",0},

	{MENU_TITLE_GENERIC_BAT,"%02d%c%02d Bat.:%s%s%s%02d%%%s Tmp.%dC",0},
	{MENU_TITLE_GENERIC_BAT_TIME,"(%02dh%02dm)",0},
	{MENU_TITLE_GENERIC_BAT_PLG,"Plg.",0},
	{MENU_TITLE_GENERIC_BAT_CHRG,"Chrg.",0},
	{MENU_TITLE_GENERIC_BAT_LOW,"Low!",0},

	{MENU_CHANGE_VALUE,"  ,   change value",0},
	{MENU_CHANGE_VALUE_WITH_FAST,"  ,   change value -  ,  fast",0},
	{MENU_CANCEL_VALIDATE,"  ,   cancel   -      validate",0},
	{MENU_DEFAULT_VALUE,"   default value",0},
	{MENU_YES,"yes",0},
	{MENU_NO,"no",0},
	{MENU_NOT_IMPLEMENTED,"Not yet implemented.\n\n",0},

	{MENU_SOUND_MODE_NOTEMUL,"not emulated",0},
	{MENU_SOUND_MODE_EMULOFF,"emulated, no output",0},
	{MENU_SOUND_MODE_EMULON,"emulated, output",0},

	{MENU_STATE_CHOOSEDEL,"Choose a slot to DELETE",0},
	{MENU_STATE_CHOOSELOAD,"Choose a slot to LOAD",0},
	{MENU_STATE_CHOOSESAVE,"Choose a slot to SAVE",0},
	{MENU_STATE_FREESLOT,"FREE",0},
	{MENU_STATE_SCANNING,"Scanning used slots...",0},


	{ERR_INIT_OSK,"cannot init OSK",20},
	{ERR_ADD_CODE,"Cannot add cheat code, too many already enterred!",60},

	{MENU_CHEATS_ENTERGF,"Enter a GoldFinger code",0},
	{MENU_CHEATS_ENTERPAR,"Enter a Pro Action Replay code",0},
	{MENU_CHEATS_ENTERGG,"Enter a Game Genie code",0},
	{MENU_CHEATS_ENTERRAW,"Enter a RAW code\nFormat is ADDRESS - NEW VALUE",0},
	{MENU_CHEATS_CONFIRMREMALL,"Remove all codes ?",-2},
	{MENU_CHEATS_ENTERNAME,"Enter Name",0},
	{MENU_CHEATS_PREVPAGE,"L - Prev. Page",0},
	{MENU_CHEATS_NEXTPAGE,"R - Next Page",0},

	{MENU_STATE_CONFIRMLOAD,"Current game progress will be lost.\nContinue ?",-2},
	{MENU_STATE_CONFIRMDELETE,"Delete current state ?",-2},
	{MENU_STATE_CONFIRMSAVE,"Overwrite current savestate ?",-2},
	{MENU_STATE_ISLOADING,"Loading state...",10},
	{MENU_STATE_ISSAVING,"Saving state...",10},
	{MENU_STATE_ISDELETING,"Deleting...",10},
	{MENU_STATE_ISIMPORTING,"Importing state...",10},
	{MENU_STATE_ISEXPORTINGS9X,"Exporting SNES9X state...",10},
	{MENU_STATE_NOSTATE,"No state available...",10},
	{MENU_STATE_AUTOSAVETIMER,"every %dmin.",0},
	{MENU_STATE_AUTOSAVETIMER_OFF,"off",0},
	{MENU_STATE_WARNING_LOWBAT,"Battery is low.\nIf PSP turns off while saving, Memory Stick may be broken.\nContinue?",-2},
	{MENU_GAME_SAVINGDEFAULTSETTINGS,"Saving current settings as default profile",30},
	{MENU_GAME_CONFIRMRESET,"Reset Snes ?",-2},
	{MENU_MISC_SAVINGJPEG,"Saving JPEG snapshot...",10},

	{MENU_MISC_BGMUSIC_RAND,"Play randomly",0},
	{MENU_MISC_BGMUSIC_ORDER,"Play in order",0},

	{MENU_MISC_BGMUSIC_UNKNOWN,"unknown",0},
	{MENU_MISC_BGMUSIC_GAMETITLE,"Playing : ",0},
	{MENU_MISC_BGMUSIC_TITLE,"Title : ",0},
	{MENU_MISC_BGMUSIC_AUTHOR,"Author : ",0},


	// GAME
	{MENU_ICONS_GAME,"GAME",0},
	{MENU_ICONS_GAME_RESET,"Reset SNES",0},
	{MENU_ICONS_GAME_NEW,"Load new game",0},
	{MENU_ICONS_GAME_DEFAULTSETTINGS,"Make Settings DEFAULT",0},
	{MENU_ICONS_GAME_DEFAULTSETTINGS_HELP,"Make current settings the default\nfor all roms when no specific\none exists",0},		
	{MENU_ICONS_GAME_EXIT,"Exit Snes9xTYL",0},
	// LOAD/SAVE
	{MENU_ICONS_LOADSAVE,"LOAD/SAVE",0},
	{MENU_ICONS_LOADSAVE_LOADSTATE,"Load state",0},
	{MENU_ICONS_LOADSAVE_LOADSTATE_HELP,"Load a previously saved state.\nSavestate is like a snapshot\nof the snes state, everything\nis saved.",0},		
	{MENU_ICONS_LOADSAVE_SAVESTATE,"Save state",0},
	{MENU_ICONS_LOADSAVE_SAVESTATE_HELP,"Save state",0},
	{MENU_ICONS_LOADSAVE_DELETESTATE,"Delete state",0},
	{MENU_ICONS_LOADSAVE_DELETESTATE_HELP,"Delete state",0},
	{MENU_ICONS_LOADSAVE_IMPORTSTATE,"Import state",0},
	{MENU_ICONS_LOADSAVE_IMPORTSTATE_HELP,"Import a state from a previous\nversion or from uosnes9x.",0},

	{MENU_ICONS_LOADSAVE_EXPORTS9XSTATE,"Export SNES9X state",0},
	{MENU_ICONS_LOADSAVE_EXPORTS9XSTATE_HELP,"Export a state using SNES9X format.",0},

	{MENU_ICONS_LOADSAVE_AUTOSAVETIMER,"Autosavestate timer",0},
	{MENU_ICONS_LOADSAVE_AUTOSAVETIMER_HELP,"Allows to have an auto\nsavestate performed regularly.",0},
	{MENU_ICONS_LOADSAVE_AUTOSRAM,"Autosave updated SRAM",0},
	{MENU_ICONS_LOADSAVE_AUTOSRAM_HELP,"Allows to have SRAM saved\nafter each change.",0},
	// CONTROLS
	{MENU_ICONS_CONTROLS,"CONTROLS",0},
	{MENU_ICONS_CONTROLS_REDEFINE,"Redefine",0},
	{MENU_ICONS_CONTROLS_REDEFINE_HELP,"Redefine buttons mapping.",0},
	{MENU_ICONS_CONTROLS_INPUT,"Emulated input",0},
	{MENU_ICONS_CONTROLS_INPUT_HELP,"Choose current active\nsnes controller.",0},

	{MENU_CONTROLS_INPUT,"Joypad #%d",0},
	{MENU_CONTROLS_INPUT_PRESS,"Press a button for %s",0},
	{MENU_CONTROLS_INPUT_NOFORMENU,"No button defined for MENU Access!\nPlease choose one",30},
#ifdef HOME_HOOK
	{MENU_CONTROLS_INPUT_DEFAULT,"Choose a default profile : \n\n"\
				SJIS_CROSS " - Default, SNES pad mapped to PSP pad.\n\n"\
				SJIS_CIRCLE " - Default, SNES pad mapped to PSP stick.\n\n"\
				SJIS_SQUARE " - Default, SNES pad mapped to PSP pad&stick.\n\n"\
				SJIS_TRIANGLE " Cancel\n",0},
#else
	{MENU_CONTROLS_INPUT_DEFAULT,"Choose a default profile : \n\n"\
				SJIS_CROSS " - Default, SNES pad mapped to PSP pad. GUI on stick left.\n\n"\
				SJIS_CIRCLE " - Default, SNES pad mapped to PSP stick. GUI on pad left.\n\n"\
				SJIS_SQUARE " - Default, SNES pad mapped to PSP pad&stick. GUI on LTrg.+RTrg.\n\n"\
				SJIS_TRIANGLE " Cancel\n",0},
#endif

	{MENU_STATUS_CONTROLS_INPUT,MSG_BTN_POSITIVE " Detect mode   " SJIS_STAR "  " MSG_BTN_NEGATIVE " Menu  ",0},
	{MENU_STATUS_CONTROLS_INPUT_0,SJIS_STAR "  " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value  " SJIS_STAR "  SELECT default profiles",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_0,SJIS_STAR "      " SJIS_TRIANGLE " Help       " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_1,SJIS_STAR "     " SJIS_TRIANGLE "   Help      " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_2,SJIS_STAR "    " SJIS_TRIANGLE "     Help     " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_3,SJIS_STAR "   " SJIS_TRIANGLE "       Help    " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value",0},

	{MENU_TITLE_CONTROLS_INPUT,"[" EMUNAME_VERSION "] - Inputs Config",0},

	// VIDEO OPTIONS
	{MENU_ICONS_VIDEO,"VIDEO",0},
	{MENU_ICONS_VIDEO_MODE,"Video mode",0},
	{MENU_ICONS_VIDEO_MODE_HELP,"Change the aspect ratio\n4:3 is adviced",0},
	{MENU_ICONS_VIDEO_ENGINE,"Engine",0},
	{MENU_ICONS_VIDEO_ENGINE_HELP,"Hardware accelerated mode\nis not always the fastest",0},
	{MENU_ICONS_VIDEO_SLIMITONOFF,"Speed limit switch",0},
	{MENU_ICONS_VIDEO_SLIMITONOFF_HELP,"Turn on to limit the speed\nof the game.",0},
	{MENU_ICONS_VIDEO_SLIMITVALUE,"Speed limit fps",0},
	{MENU_ICONS_VIDEO_SLIMITVALUE_HELP,"Only used if speed limit\nhas been turned on.",0},
	{MENU_ICONS_VIDEO_FSKIP,"Frameskip",0},
	{MENU_ICONS_VIDEO_FSKIP_HELP,"Choose a fixed value if you\nhave some sprites\ndisappearing.",0},
	{MENU_ICONS_VIDEO_SMOOTHING,"Smoothing",0},
	{MENU_ICONS_VIDEO_SMOOTHING_HELP,"Should be on since it costs\nnothing.",0},
	{MENU_ICONS_VIDEO_VSYNC,"VSync",0},
	{MENU_ICONS_VIDEO_VSYNC_HELP,"This costs lots of fps\nand should be turned off.",0},
	{MENU_ICONS_VIDEO_PALASNTSC,"Render PAL as NTSC",0},
	{MENU_ICONS_VIDEO_PALASNTSC_HELP,"Force PAL games to be emulated\nlike NTSC ones : 224 lines\ninstead of 240.",0},
	{MENU_ICONS_VIDEO_GAMMA,"Gamma correction",0},
	{MENU_ICONS_VIDEO_GAMMA_HELP,"Allows brighter rendering",0},
	{MENU_ICONS_VIDEO_SCRCALIB,"Screen calibration",0},	
	{MENU_ICONS_VIDEO_SCRCALIB_HELP,"Help to get rid of the nasty\nblack borders.",0},
	{MENU_ICONS_VIDEO_SHOWFPS,"Show FPS",0},
	{MENU_ICONS_VIDEO_SHOWFPS_HELP,"First line is emulated frames\nSecond one is real fps.",0},

	{MENU_VIDEO_MODE_1_1,"1:1",0},
	{MENU_VIDEO_MODE_ZOOM_FIT,"zoom fit",0},
	{MENU_VIDEO_MODE_ZOOM_4_3RD,"zoom 4/3",0},
	{MENU_VIDEO_MODE_ZOOM_WIDE,"zoom wide",0},
	{MENU_VIDEO_MODE_FULLSCREEN,"fullscreen",0},
	{MENU_VIDEO_MODE_FULLSCREEN_CLIPPED,"fullscreen clipped",0},
	{MENU_VIDEO_ENGINE_APPROX,"approx. software",0},
	{MENU_VIDEO_ENGINE_ACCUR,"accur. software",0},
	{MENU_VIDEO_ENGINE_ACCEL,"PSP accelerated",0},
	{MENU_VIDEO_ENGINE_ACCEL_ACCUR,"PSP accel. + accur. soft.",0},
	{MENU_VIDEO_ENGINE_ACCEL_APPROX,"PSP accel. + approx. soft.",0},
	{MENU_VIDEO_SLIMITVALUE_AUTO,"AUTO (detect PAL/NTSC)",0},
	{MENU_VIDEO_FSKIP_MODE_AUTO,"auto change below %d",0},
	{MENU_VIDEO_FSKIP_CHANGEAUTO_AUTO,"   auto change below set value",0},
	{MENU_VIDEO_FSKIP_CHANGEAUTO_FIXED,"   fixed",0},

	{MENU_STATUS_VIDEO_SCRCALIB,"PAD : SCREEN POSITION  " SJIS_STAR "  ANALOG STICK : SCREEN SIZE  " SJIS_STAR "  " SJIS_TRIANGLE " default  " SJIS_STAR "  " MSG_BTN_NEGATIVE " Exit",0},

	// SOUND OPTIONS
	{MENU_ICONS_SOUND,"SOUND",0},
	{MENU_ICONS_SOUND_MODE,"Sound mode",0},
	{MENU_ICONS_SOUND_MODE_HELP,"not emulated is the fastest\nbut some games won't run.",0},
	{MENU_ICONS_SOUND_FREQ,"Output frequency",0},
	{MENU_ICONS_SOUND_FREQ_HELP,"The lower the faster\nThe higher the best sound quality",0},
	{MENU_ICONS_SOUND_APURATIO,"APU Cycles ratio",0},
	{MENU_ICONS_SOUND_APURATIO_HELP,"For advanced users knowing\nwhat they do.",0},
	// MISC OPTIONS
	{MENU_ICONS_MISC,"MISC",0},
	{MENU_ICONS_MISC_FILEVIEWER,"View file",0},
	{MENU_ICONS_MISC_FILEVIEWER_HELP,"Minimalist file viewer",0},
	{MENU_ICONS_MISC_PSPCLOCK,"PSP Clockspeed",0},
	{MENU_ICONS_MISC_PSPCLOCK_HELP,"value>222Mhz is NOT overclocking\nit's safe but battery runs out\nfaster",0},
	{MENU_ICONS_MISC_HACKDEBUG,"Hack/debug menu",0},
	{MENU_ICONS_MISC_HACKDEBUG_HELP,"For advanced users.\nHelp to tune the rendering and\ngain some speed.",0},
	{MENU_ICONS_MISC_SNAPSHOT,"Snapshot",0},
	{MENU_ICONS_MISC_SNAPSHOT_HELP,"Take a snapshot of the current\ngame screen.\nUsed in file browser.",0},
	{MENU_ICONS_MISC_SWAPBG,"Swap BG",0},
	{MENU_ICONS_MISC_SWAPBG_HELP,"Swap BG from the DATA/logo.zip\nfile.",0},
	{MENU_ICONS_MISC_BGMUSIC,"Menu background music",0},
	{MENU_ICONS_MISC_BGMUSIC_HELP,"Menu background music requires\nmake PSP running at 300Mhz\nMusic are from DATA/music.zip file.\nSPC format only.",0},
	{MENU_ICONS_MISC_BGFX,"Menu background fx",0},
	{MENU_ICONS_MISC_BGFX_HELP,"Nice FX from PS2DEV spline sample.",0},
	{MENU_ICONS_MISC_PADBEEP,"Pad beep",0},
	{MENU_ICONS_MISC_PADBEEP_HELP,"The beep sounds when browsing\nmenu and files.",0},
	{MENU_ICONS_MISC_AUTOSTART,"Last ROM Auto-Start",0},
	{MENU_ICONS_MISC_AUTOSTART_HELP,"If you set to [yes],the ROM\nwhich was loaded at last\n will start automatically\nwhen the emulator started.",0},
	{MENU_ICONS_MISC_OSK,"OSK",0},
	{MENU_ICONS_MISC_OSK_HELP,"OSK is On-Screen Keyboard.\nDanzeff OSK is useful\nfor typing alphabet on PSP\nSCE's official OSK is useful\nfor typing Japanese or on PS Vita.",0},

	{MENU_MUSIC_SWAPBG_NODATA,"No Data",0},
	{MENU_MISC_SWAPBG_RAND,"   Random",0},

	{MENU_MISC_OSK_DANZEFF,"Danzeff",0},
	{MENU_MISC_OSK_OFFICIAL,"Official",0},

	{MENU_STATUS_MISC_HACKDEBUG,MSG_BTN_NEGATIVE " Main Menu   ",0},
	{MENU_STATUS_MISC_HACKDEBUG_FUNC,MSG_BTN_POSITIVE " OK     " SJIS_STAR "    " MSG_BTN_NEGATIVE " Main Menu   ",0},
	{MENU_STATUS_MISC_HACKDEBUG_0,SJIS_STAR "    " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value"},

	{MENU_STATUS_MISC_HACKDEBUG_HELP_0,SJIS_STAR "      " SJIS_TRIANGLE " Help       " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_1,SJIS_STAR "     " SJIS_TRIANGLE "   Help      " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_2,SJIS_STAR "    " SJIS_TRIANGLE "     Help     " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_3,SJIS_STAR "   " SJIS_TRIANGLE "       Help    " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " Select " SJIS_LEFT "," SJIS_RIGHT " Change value"},

	{MENU_TITLE_MISC_HACKDEBUG,"[" EMUNAME_VERSION "] - Menu",0},

	// CHEATS
	{MENU_ICONS_CHEATS,"CHEATS",0},
	{MENU_ICONS_CHEATS_ADDRAW,"Add a RAW code",0},
	{MENU_ICONS_CHEATS_ADDRAW_HELP,"Add a RAW code",0},
	{MENU_ICONS_CHEATS_ADDGG,"Add a Game Genie code",0},
	{MENU_ICONS_CHEATS_ADDGG_HELP,"Add a Game Genie code",0},
	{MENU_ICONS_CHEATS_ADDPAR,"Add a Pro Action Replay code",0},
	{MENU_ICONS_CHEATS_ADDPAR_HELP,"Add a Pro Action Replay code",0},
	{MENU_ICONS_CHEATS_ADDGF,"Add a GoldFinger code",0},
	{MENU_ICONS_CHEATS_ADDGF_HELP,"Add a GoldFinger code",0},
	{MENU_ICONS_CHEATS_DISABLE,"Disable code",0},
	{MENU_ICONS_CHEATS_DISABLE_HELP,"Disable code",0},
	{MENU_ICONS_CHEATS_DISABLEALL,"Disable all codes",0},
	{MENU_ICONS_CHEATS_DISABLEALL_HELP,"Disable all codes",0},
	{MENU_ICONS_CHEATS_ENABLE,"Enable code",0},
	{MENU_ICONS_CHEATS_ENABLE_HELP,"Enable code",0},
	{MENU_ICONS_CHEATS_ENABLEALL,"Enable all codes",0},
	{MENU_ICONS_CHEATS_ENABLEALL_HELP,"Enable all codes",0},
	{MENU_ICONS_CHEATS_REMOVE,"Remove code",0},
	{MENU_ICONS_CHEATS_REMOVE_HELP,"Remove code",0},
	{MENU_ICONS_CHEATS_REMOVEALL,"Remove all codes",0},
	{MENU_ICONS_CHEATS_REMOVEALL_HELP,"Remove all codes",0},
	// ABOUT
	{MENU_ICONS_ABOUT,"ABOUT",0},
	{MENU_ICONS_ABOUT_CREDITS,"Credits",0},
	{MENU_ICONS_ABOUT_VERSION,"Version infos",0},

	{MENU_ABOUT_VERSION_TIMESTAMP,"Build on %s",0},
	{MENU_ABOUT_VERSION_GCCVER,"With GCC %s",0},

	//Others
	// Adhoc
	{ADHOC_CONNECTING,"Connecting...\n",0},
	{ADHOC_SELECTORRETURN,"Select a server to connect to, or triangle to return",0},
	{ADHOC_WAITING,"Waiting for %s to accept the connection\nTo cancel press O\n",0},
	{ADHOC_REQUESTED,"%s has requested a connection\nTo accept the connection press X, to cancel press O\n",0},
	{ADHOC_CONNECTED,"Connected",0},
	{ADHOC_STATE,"  connection state %d of 1\n",0},
	{ADHOC_UNKNOWNCOMMAND,"Unknown command %02X !",0},
	{ADHOC_SYNCLOST_SERVER,"SERVER Lost sync : resync!!!",20},
	{ADHOC_SYNCLOST_CLIENT,"CLIENT Lost sync : resync!!!",20},
	{ADHOC_CLOSING,"closing connection",60},
	{ADHOC_DRIVERLOAD_ERR,"Net driver load error",60*2},
	{ADHOC_INIT_ERR,"Issue with init adhoc game\n",60},
	{ADHOC_LOST_CONNECTION,"Lost connection!",60},
	{ADHOC_CORRUPTED_PKT,"corrupted pkt",0},
	{ADHOC_STATE_SIZE,"state size : %d",0},
	{ADHOC_FILE_ERR_RECEIVING,"file error while receiving state!",60*1},
	{ADHOC_FILE_ERR_SENDING,"file error while sending state!",60*1},
	{ADHOC_STILL,"still : %d",0},
	{ADHOC_WAITING_OTHER,"Waiting for other player\n\nPress " SJIS_TRIANGLE " to close connection and quit netplay\n",10},
	{ADHOC_NETWORKERR_1,"network error 1",60*1},
	{ADHOC_CANNOTFIND,"cannot find save state!",60},
	{ADHOC_FLUSHING,"flushing network, please wait a few seconds",10},
	// LOAD/SAVE
	{LOADSAVE_AUTOSAVETIMER,"Autosaving...",0},
	{LOADSAVE_EXPORTS9XSTATE,"Found a snes9xTYL file",0},
	// VIDEO
	{VIDEO_ENGINE_APPROX,"Simple mode : accurate software",30},
	{VIDEO_ENGINE_ACCUR,"Simple mode : approx. software",30},
	{VIDEO_ENGINE_ACCEL,"Simple mode : PSP accelerated",30},
	{VIDEO_ENGINE_ACCEL_ACCUR,"Mixed modes : PSP accelerated + accurate software",30},
	{VIDEO_ENGINE_ACCEL_APPROX,"Mixed modes : PSP accelerated + approx. software",30},
	{VIDEO_FSKIP_AUTO,"Frameskip : AUTO",0},
	{VIDEO_FSKIP_MANUAL,"Frameskip : %d",0},
	// Scroll Message
	{SCROLL_TITLE,"   ,   to move -  ,  for fast mode",0},
	{SCROLL_STATUS_0,"Line %d/%d  -  Page %d/%d",0},
	{SCROLL_STATUS_1,"   exit,        help  ",0},
	{SCROLL_HELP,"Snes9xTYL - fileviewer\n\n" SJIS_TRIANGLE " Find, then " MSG_BTN_POSITIVE " Find next, " SJIS_SQUARE " Find previous\n" \
						SJIS_UP "," SJIS_DOWN " scroll text, L,R scroll faster\n" MSG_BTN_NEGATIVE " exit\n\nLast position is keeped if same file is reopened.\nHowever it will be reset if another file is opened.\n\n" \
						"Press " MSG_BTN_NEGATIVE,0},
	{SCROLL_SEARCHING,"Searching...",0},
	{SCROLL_STRNOTFOUND,"String not found!",30},
	{SCROLL_DISCLAIMER,"Disclaimer",0},
	{SCROLL_OSK_DESC,"Enter String to find",0},
	//Settings
	{SETTINGS_NOTCOMPLETE,"!!Settings file not complete!!\n\nProbably coming from a previous version.\n\nNew settings will be set with default values",60*3},
	{SETTINGS_NOTFOUND,"No settings found, using default",10},
	{SETTINGS_FORCING_DEFAULT,"Forcing default settings",10},
	{SETTINGS_IGNORED,"ini file from a previous incompatible version, ignored!",20},
	{SETTINGS_FOUND,"Settings found!\n\n""%s""",0},
	{SETTINGS_DIFF,"ini file from a different version.",20},
	//Others
	{APU_DEBUGGING,"APU DEBUGGING",10},
	{BGMUSIC_PLAYING,"Playing spc file...",0},
	{FOUND_SRAM,"Found an SRAM file",60},
	{CANCEL,"CANCEL",0},
	{INPUTBOX_OK,"\n\n      Close",0},
#ifdef ME_SOUND
	{BAT_ISLOW,"Battery is low, saving is now disabled (SRAM,states and settings).\n\nThis window will close in 3 seconds.",60*3},
#else
	{BAT_ISLOW,"Battery is low, saving is now disabled (SRAM,states and settings).\n\nYou can still put your PSP in sleep mode and charge battery later.\n\nThis window will close in 3 seconds.",60*3},
#endif
	{CONV_DONE,"conversion done",30},
	{ROM_LIED,"ROM lied about its type! Trying again.",30},
	{LOADING_ROM,"Loading %dKo...",0},
	{TYPE,"Type",0},
	{MODE,"Mode",0},
	{COMPANY,"Company",0},
#ifdef _BSX_151_
	{SRAM_NOTFOUND,"The SRAM file wasn't found: BS-X.srm was read instead.",30},
	{SRAM_BSX_NOTFOUND,"The SRAM file wasn't found, BS-X.srm wasn't found either.",30},
#endif
	{CORRUPT,"Corrupt",0},
	{ROM_ONLY,"ROM only",0},
	{EXTENDING,"Extending",30},
	{EXTENDING_TARGET,"Extending target from %d to %d\n",0},
	{INIT_OSK,"Initializing OSK...",0}
};

t_err_entry s9xTYL_msg_ja[MSG_TOTAL_ENTRIES]= {
//japanese
	//error
	{ERR_OUT_OF_MEM,"�������O�ł��B",60},
	{ERR_READ_MEMSTICK,"�������[�X�e�B�b�N�̓ǂݍ��݂ŃG���[���������܂����B\n�������[�X�e�B�b�N���m�F���Ă��������B\n(PC�̃J�[�h���[�_�[���g���Ă�������)\n�������[�X�e�B�b�N���j�����Ă���\\��������܂��B",60},

	{ERR_INIT_SNES,"�������̖���SFC���������ł��܂���",2*60},
	{ERR_LOADING_ROM,"ROM�ǂݍ��݃G���[",60*2},
	{ERR_INIT_GFX,"�O���t�B�b�N�X���������ł��܂���",60*2},

	{ERR_CANNOT_ALLOC_MEM,"�����������蓖�Ă��܂���",30},

	{ERR_USB_STARTING_USBBUS,"USB�o�X�h���C�o�J�n�G���[ (0x%08X)\n",0},
	{ERR_USB_STARTING_USBMASS,"USB��e�ʋL�����u�h���C�o�J�n�G���[ (0x%08X)\n",0},
	{ERR_USB_SETTING_CAPACITY,"USB��e�ʋL�����u�h���C�o�e�ʐݒ�G���[ (0x%08X)\n",0},
	//confirm
	{ASK_EXIT,"Snes9XTYL���I�����܂���?",-2},
	{ASK_DELETE,"�t�@�C�����폜���܂���?",-2},
	{ASK_SAVEDIR,"�Z�[�u�f�B���N�g����������܂���B\n"
		"���̃G�~�����[�^�[������f�B���N�g���ɍ쐬����ɂ�" SJIS_CIRCLE "�{�^���������Ă��������B\n"
		"SAVEDATA�f�B���N�g���ɍ쐬����ɂ�" SJIS_CROSS "�{�^���������Ă��������B\n",
		0},
	//info
	{INFO_USB_ON,"USB���L��������܂���",30},
	{INFO_USB_OFF,"USB������������܂���",30},
	{INFO_DELETING,"�폜���Ă��܂�...",0},
	{INFO_EXITING,"�I�����Ă��܂��B���΂炭���҂���������...",0},
	//filer
	{FILER_STATUS_CANEXIT1,MSG_BTN_POSITIVE " ���s " SJIS_SQUARE " �W���ݒ�Ŏ��s  " SJIS_STAR "  " MSG_BTN_NEGATIVE " �Q�[���ɖ߂�  "  SJIS_STAR "  " SJIS_TRIANGLE " %s  "  SJIS_STAR "  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT " �ړ�",0},
	{FILER_STATUS_NOEXIT1,MSG_BTN_POSITIVE " ���s " SJIS_SQUARE " �W���ݒ�Ŏ��s  "  SJIS_STAR "  " SJIS_TRIANGLE " %s          " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT " ���X�g���ړ�",0},
	{FILER_STATUS_CANEXIT2,MSG_BTN_POSITIVE " ���s " MSG_BTN_NEGATIVE "�Q�[���ɖ߂� " SJIS_TRIANGLE " %s  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT " ���X�g���ړ�",0},
	{FILER_STATUS_NOEXIT2,MSG_BTN_POSITIVE " ���s " SJIS_TRIANGLE " %s                  " SJIS_UP "," SJIS_DOWN "," SJIS_LEFT "," SJIS_RIGHT " ���X�g���ړ�",0},

	{FILER_STATUS_PARDIR, "���", 0},

	{FILER_TITLE, "[" EMUNAME_VERSION "] - �t�@�C���I��", 0},
	
	{FILER_HELP_WINDOW1,"�W���ƒʐM�ΐ탂�[�h��؂�ւ���",0},
	{FILER_HELP_WINDOW2,"�ɂ�START�������Ă�������",0},
#ifdef FW3X
	{FILER_HELP_WINDOW3," ",0},
#ifdef HOME_HOOK
	{FILER_HELP_WINDOW4,"�I������ɂ�HOME�������Ă�������",0},
#else
	{FILER_HELP_WINDOW4,"�I������ɂ�L+R�������Ă�������",0},
#endif
#else
#ifdef HOME_HOOK
	{FILER_HELP_WINDOW3,"�I������ɂ�HOME�������Ă�������",0},
#else
	{FILER_HELP_WINDOW3,"�I������ɂ�L+R�������Ă�������",0},
#endif
	{FILER_HELP_WINDOW4,"USB�ݵ̐؂�ւ���R�������Ă�������",0},
#endif


	{FILER_HELP_WINDOW5,"�폜����ɂ�SELECT�������Ă�������",0},

	{FILE_IPS_APPLYING,"IPS�p�b�`��������܂��� : %s\n�T�C�Y : %dKo\n�K�p���Ă��܂�....",0},
	{FILE_IPS_PATCHSUCCESS,"IPS�p�b�`�̓K�p�ɐ������܂���",0},

	{MENU_STATUS_GENERIC_MSG1,"�߂�ɂ�" MSG_BTN_NEGATIVE "�������Ă�������",0},
	{MENU_STATUS_GENERIC_NEEDRELOAD,"�ύX��K�p����ɂ͍ēǂݍ��݂��K�v��������܂���",0},
	{MENU_STATUS_GENERIC_NEEDRESET,"�ύX��K�p����ɂ̓��Z�b�g���K�v��������܂���",0},
	{MENU_STATUS_GENERIC_FREERAM,"�󂫃����� : %dKo",0},
	{MENU_STATUS_GENERIC_CHANGEMUSIC,"���y��ς���ɂ�SELECT�{�^�����A",0},

	{MENU_TITLE_GENERIC_BAT,"%02d%c%02d �d�r:%s%s%s�c��%02d%%%s ���x.%d��",0},
	{MENU_TITLE_GENERIC_BAT_TIME,"(%02d����%02d��)",0},
	{MENU_TITLE_GENERIC_BAT_PLG,"AC.",0},
	{MENU_TITLE_GENERIC_BAT_CHRG,"�[�d��.",0},
	{MENU_TITLE_GENERIC_BAT_LOW,"�c�ʒቺ.",0},

	{MENU_CHANGE_VALUE,"  ,   �l��ύX",0},
	{MENU_CHANGE_VALUE_WITH_FAST,"  ,   �l��ύX   -    ,  ����",0},
	{MENU_CANCEL_VALIDATE,"  ,   �L�����Z�� -    �K�p",0},
	{MENU_DEFAULT_VALUE,"   �W���l",0},
	{MENU_YES,"�͂�",0},
	{MENU_NO,"������",0},
	{MENU_NOT_IMPLEMENTED,"�܂���������Ă��܂���B\n\n",0},

	{MENU_SOUND_MODE_NOTEMUL,"�G�~�����[�g���Ȃ�",0},
	{MENU_SOUND_MODE_EMULOFF,"�G�~�����[�g���邪�o�͂��Ȃ�",0},
	{MENU_SOUND_MODE_EMULON,"�G�~�����[�g���A�o�͂���",0},
	
	{MENU_STATE_CHOOSEDEL,"�폜����X���b�g��I��ł�������",0},
	{MENU_STATE_CHOOSELOAD,"�ǂݍ��ރX���b�g��I��ł�������",0},
	{MENU_STATE_CHOOSESAVE,"�ۑ�����X���b�g��I��ł�������",0},
	{MENU_STATE_FREESLOT,"��",0},
	{MENU_STATE_SCANNING,"�g�p�ς݃X���b�g�𒲂ׂĂ��܂�...",0},


	{ERR_INIT_OSK,"OSK���������ł��܂���",20},
	{ERR_ADD_CODE,"�`�[�g�R�[�h��ǉ��ł��܂���B���ɓ��͂���Ă���R�[�h���������܂��B",60},

	{MENU_CHEATS_ENTERGF,"GoldFinger�R�[�h����͂��Ă�������",0},
	{MENU_CHEATS_ENTERPAR,"�v���A�N�V�������v���C�R�[�h����͂��Ă�������",0},
	{MENU_CHEATS_ENTERGG,"Game Genie�R�[�h����͂��Ă�������",0},
	{MENU_CHEATS_ENTERRAW,"RAW�R�[�h����͂��Ă�������\n���� : �A�h���X - �V�����l",0},
	{MENU_CHEATS_ENTERNAME,"���O����͂��Ă�������",0},
	{MENU_CHEATS_CONFIRMREMALL,"���ׂẴR�[�h���폜���܂���?",-2},
	{MENU_CHEATS_PREVPAGE,"L - �O�̃y�[�W",0},
	{MENU_CHEATS_NEXTPAGE,"R - ���̃y�[�W",0},

	{MENU_STATE_CONFIRMLOAD,"���݂̃Q�[���i�s�������܂��B\n���s���܂���?",-2},
	{MENU_STATE_CONFIRMDELETE,"���̃X�e�[�g�Z�[�u���폜���܂���?",-2},
	{MENU_STATE_CONFIRMSAVE,"���̃X�e�[�g�Z�[�u�ɏ㏑�����܂���?",-2},
	{MENU_STATE_ISSAVING,"�X�e�[�g�Z�[�u���Ă��܂�...",10},
	{MENU_STATE_ISLOADING,"��Ԃ�ǂݍ���ł��܂�...",10},
	{MENU_STATE_ISDELETING,"�폜���Ă��܂�...",10},
	{MENU_STATE_ISIMPORTING,"�X�e�[�g�Z�[�u���C���|�[�g���Ă��܂�...",10},
	{MENU_STATE_ISEXPORTINGS9X,"SNES9X�X�e�[�g�Z�[�u���G�N�X�|�[�g���Ă��܂�...",10},
	{MENU_STATE_NOSTATE,"�g�p�\\�ȃX�e�[�g�Z�[�u������܂���",10},
	{MENU_STATE_AUTOSAVETIMER,"%d����",0},
	{MENU_STATE_AUTOSAVETIMER_OFF,"�I�t",0},
	{MENU_STATE_WARNING_LOWBAT,"�d�r�c�ʂ��ቺ���Ă��܂��B\n�Z�[�u���ɓd�����؂��ƃ������[�X�e�B�b�N���j������\\��������܂��B\n���s���܂���?",-2},
	{MENU_GAME_SAVINGDEFAULTSETTINGS,"���݂̐ݒ��W���ݒ�Ƃ��ĕۑ����Ă��܂�",30},
	{MENU_GAME_CONFIRMRESET,"SFC�����Z�b�g���܂���?",-2},
	{MENU_MISC_SAVINGJPEG,"JPEG�X�i�b�v�V���b�g��ۑ����Ă��܂�...",10},

	{MENU_MISC_BGMUSIC_RAND,"�����_���ɍĐ�",0},
	{MENU_MISC_BGMUSIC_ORDER,"���ɍĐ�",0},

	{MENU_MISC_BGMUSIC_UNKNOWN,"�s��",0},
	{MENU_MISC_BGMUSIC_GAMETITLE,"�Q�[�� : ",0},
	{MENU_MISC_BGMUSIC_TITLE,"�薼 : ",0},
	{MENU_MISC_BGMUSIC_AUTHOR,"��� : ",0},


	// GAME
	{MENU_ICONS_GAME,"�Q�[��",0},
	{MENU_ICONS_GAME_RESET,"SFC�����Z�b�g����",0},
	{MENU_ICONS_GAME_NEW,"�V�����Q�[����ǂݍ���",0},
	{MENU_ICONS_GAME_DEFAULTSETTINGS,"�W���ݒ���쐬����",0},
	{MENU_ICONS_GAME_DEFAULTSETTINGS_HELP,"���݂̐ݒ����ʂɐݒ�t�@�C�����Ȃ�\n�S�Ă�ROM�Ɏg����W���ݒ�Ƃ���\n�ۑ����܂��B",0},
	{MENU_ICONS_GAME_EXIT,"Snes9xTYL���I������",0},
	// LOAD/SAVE
	{MENU_ICONS_LOADSAVE,"���[�h/�Z�[�u",0},
	{MENU_ICONS_LOADSAVE_LOADSTATE,"�X�e�[�g���[�h",0},
	{MENU_ICONS_LOADSAVE_LOADSTATE_HELP,"�ȑO�ۑ������X�e�[�g�Z�[�u��\n�ǂݍ��݂܂��B�X�e�[�g�Z�[�u��SFC\n�̏�Ԃ̃X�i�b�v�V���b�g�̂悤��\n���̂ŁA���ׂĕۑ�����܂��B",0},
	{MENU_ICONS_LOADSAVE_SAVESTATE,"�X�e�[�g�Z�[�u",0},
	{MENU_ICONS_LOADSAVE_SAVESTATE_HELP,"�X�e�[�g�Z�[�u���܂��B",0},
	{MENU_ICONS_LOADSAVE_DELETESTATE,"�X�e�[�g�Z�[�u���폜",0},
	{MENU_ICONS_LOADSAVE_DELETESTATE_HELP,"�X�e�[�g�Z�[�u�̃Z�[�u�f�[�^��\n�폜���܂��B",0},	
	{MENU_ICONS_LOADSAVE_IMPORTSTATE,"�X�e�[�g�Z�[�u���C���|�[�g",0},
	{MENU_ICONS_LOADSAVE_IMPORTSTATE_HELP,"uosnes9x��ȑO�̃o�[�W��������\n�X�e�[�g�Z�[�u�̃Z�[�u�f�[�^��\n�C���|�[�g���܂��B",0},

	{MENU_ICONS_LOADSAVE_EXPORTS9XSTATE,"SNES9X�̃X�e�[�g�Z�[�u�ɃG�N�X�|�[�g",0},
	{MENU_ICONS_LOADSAVE_EXPORTS9XSTATE_HELP,"SNES9X�t�H�[�}�b�g���g����\n�X�e�[�g�Z�[�u�̃Z�[�u�f�[�^��\n�G�N�X�|�[�g���܂��B",0},	

	{MENU_ICONS_LOADSAVE_AUTOSAVETIMER,"�I�[�g�X�e�[�g�Z�[�u�^�C�}�[",0},
	{MENU_ICONS_LOADSAVE_AUTOSAVETIMER_HELP,"����I�ɃI�[�g�X�e�[�g�Z�[�u��\n�����܂��B",0},
	{MENU_ICONS_LOADSAVE_AUTOSRAM,"SRAM�X�V���ɃI�[�g�Z�[�u����",0},
	{MENU_ICONS_LOADSAVE_AUTOSRAM_HELP,"�ύX���s���邽�т�SRAM��\n�ۑ������悤�ɂ��܂��B",0},
	// CONTROLS
	{MENU_ICONS_CONTROLS,"�R���g���[��",0},
	{MENU_ICONS_CONTROLS_REDEFINE,"�Đݒ�",0},
	{MENU_ICONS_CONTROLS_REDEFINE_HELP,"�{�^�����蓖�Ă��Đݒ肵�܂��B",0},
	{MENU_ICONS_CONTROLS_INPUT,"�G�~�����[�g�����R���g���[��",0},
	{MENU_ICONS_CONTROLS_INPUT_HELP,"���ݗL���ɂ���SFC�R���g���[����\n�I��ł��������B",0},

	{MENU_CONTROLS_INPUT,"�R���g���[�� %d",0},
	{MENU_CONTROLS_INPUT_PRESS,"%s�Ɋ��蓖�Ă�{�^���������Ă�������",0},
	{MENU_CONTROLS_INPUT_NOFORMENU,"���j���[�ɃA�N�Z�X���邽�߂ɐݒ肳�ꂽ�{�^������܂���B\n�{�^����I��ł��������B",30},
#ifdef HOME_HOOK
	{MENU_CONTROLS_INPUT_DEFAULT,"�W���v���t�@�C����I�����Ă�������\n\n"\
				SJIS_CROSS " - �W��, SFC�̏\\���{�^����PSP�̏\\���{�^���Ɋ��蓖�Ă��܂��B\n\n"\
				SJIS_CIRCLE " - �W��, SFC�̏\\���{�^����PSP�̃A�i���O�X�e�B�b�N�Ɋ��蓖�Ă��܂��B\n\n"\
				SJIS_SQUARE " - �W��, SFC�̏\\���{�^����PSP�̏\\���{�^���ƃA�i���O�X�e�B�b�N�Ɋ��蓖�Ă��܂��B\n\n"\
				SJIS_TRIANGLE " �L�����Z��\n",0},
#else
	{MENU_CONTROLS_INPUT_DEFAULT,"�W���v���t�@�C����I�����Ă�������\n\n"\
				SJIS_CROSS " - �W��, SFC�̏\\���{�^����PSP�̏\\���{�^���Ɋ��蓖�Ă��܂��B\n���j���[�̓A�i���O�X�e�B�b�N���Ɋ��蓖�Ă܂��B\n\n"\
				SJIS_CIRCLE " - �W��, SFC�̏\\���{�^����PSP�̃A�i���O�X�e�B�b�N�Ɋ��蓖�Ă��܂��B\n���j���[�͏\\���{�^�����Ɋ��蓖�Ă܂��B\n\n"\
				SJIS_SQUARE " - Default, SFC�̏\\���{�^����PSP�̏\\���{�^���ƃA�i���O�X�e�B�b�N�Ɋ��蓖�Ă��܂��B\n���j���[��L+R�g���K�[�Ɋ��蓖�Ă܂��B\n\n"\
				SJIS_TRIANGLE " �L�����Z��\n",0},
#endif

	{MENU_STATUS_CONTROLS_INPUT,MSG_BTN_POSITIVE " ���o���[�h   " SJIS_STAR "  " MSG_BTN_NEGATIVE " ���j���[  ",0},
	{MENU_STATUS_CONTROLS_INPUT_0,SJIS_STAR "  " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX  " SJIS_STAR "  SELECT �W���ݒ�",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_0,SJIS_STAR "      " SJIS_TRIANGLE " �w���v       " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_1,SJIS_STAR "     " SJIS_TRIANGLE "   �w���v      " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_2,SJIS_STAR "    " SJIS_TRIANGLE "     �w���v     " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX",0},
	{MENU_STATUS_CONTROLS_INPUT_HELP_3,SJIS_STAR "   " SJIS_TRIANGLE "       �w���v    " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX",0},

	{MENU_TITLE_CONTROLS_INPUT,"[" EMUNAME_VERSION "] - ���͐ݒ�",0},

	// VIDEO OPTIONS
	{MENU_ICONS_VIDEO,"�r�f�I",0},
	{MENU_ICONS_VIDEO_MODE,"�o�̓��[�h",0},
	{MENU_ICONS_VIDEO_MODE_HELP,"�A�X�y�N�g���ύX���܂��B\n4:3�����E����܂��B",0},
	{MENU_ICONS_VIDEO_ENGINE,"�G���W��",0},
	{MENU_ICONS_VIDEO_ENGINE_HELP,"�n�[�h�E�F�A�N�Z�����[�g���[�h��\n�����ő��Ȃ킯�ł͂���܂���B",0},
	{MENU_ICONS_VIDEO_SLIMITONOFF,"���x�����؂�ւ�",0},
	{MENU_ICONS_VIDEO_SLIMITONOFF_HELP,"�Q�[���̑��x�𐧌�����ɂ�\n�I���ɂ��Ă��������B",0},
	{MENU_ICONS_VIDEO_SLIMITVALUE,"FPS���x����",0},
	{MENU_ICONS_VIDEO_SLIMITVALUE_HELP,"���x�������I���̂Ƃ��̂�\n�g���܂��B",0},
	{MENU_ICONS_VIDEO_FSKIP,"�t���[���X�L�b�v",0},
	{MENU_ICONS_VIDEO_FSKIP_HELP,"�\\������Ȃ��X�v���C�g������ꍇ��\n�Œ�l��I��ł��������B",0},
	{MENU_ICONS_VIDEO_SMOOTHING,"�X���[�V���O",0},
	{MENU_ICONS_VIDEO_SMOOTHING_HELP,"�����]���ɂ��Ȃ��Ƃ��̂�\n�I���ɂ��ׂ��ł��B",0},
	{MENU_ICONS_VIDEO_VSYNC,"��������",0},
	{MENU_ICONS_VIDEO_VSYNC_HELP,"����͑�����FPS���]���ɂ���̂�\n�I�t�ɂ��ׂ��ł��B",0},
	{MENU_ICONS_VIDEO_PALASNTSC,"PAL��NTSC�Ƃ��ĕ`�悷��",0},
	{MENU_ICONS_VIDEO_PALASNTSC_HELP,"PAL�̃Q�[����240�{�̐����𑜓x��\n�����224�{�ɂ���NTSC�̂��̂̂悤��\n�G�~�����[�g����悤�������܂��B",0},		
	{MENU_ICONS_VIDEO_GAMMA,"�K���}�␳",0},
	{MENU_ICONS_VIDEO_GAMMA_HELP,"��薾��߂ȕ`��������܂��B",0},
	{MENU_ICONS_VIDEO_SCRCALIB,"��ʈʒu�␳",0},
	{MENU_ICONS_VIDEO_SCRCALIB_HELP,"�ז��ȍ����g����菜���̂�\n�𗧂��܂��B",0},
	{MENU_ICONS_VIDEO_SHOWFPS,"FPS�\\��",0},
	{MENU_ICONS_VIDEO_SHOWFPS_HELP,"1�s�ڂ̓G�~�����[�g�����\n�t���[������\\�����܂��B\n2�s�ڂ͖{����FPS��\\�����܂��B",0},

	{MENU_VIDEO_MODE_1_1,"���{",0},
	{MENU_VIDEO_MODE_ZOOM_FIT,"��ʂɍ��킹�Ċg��",0},
	{MENU_VIDEO_MODE_ZOOM_4_3RD,"4/3�{",0},
	{MENU_VIDEO_MODE_ZOOM_WIDE,"���C�h�Ɋg��",0},
	{MENU_VIDEO_MODE_FULLSCREEN,"�S��ʕ\\��",0},
	{MENU_VIDEO_MODE_FULLSCREEN_CLIPPED,"�ꕔ��؂����đS��ʕ\\��",0},
	{MENU_VIDEO_ENGINE_APPROX,"�قڐ��m�ȃ\\�t�g�E�F�A�`��",0},
	{MENU_VIDEO_ENGINE_ACCUR,"���m�ȃ\\�t�g�E�F�A�`��",0},
	{MENU_VIDEO_ENGINE_ACCEL,"PSP�A�N�Z�����[�^",0},
	{MENU_VIDEO_ENGINE_ACCEL_ACCUR,"PSP����ڰ�+���m�ȿ�ĳ���`��",0},
	{MENU_VIDEO_ENGINE_ACCEL_APPROX,"PSP����ڰ�+�قڐ��m�ȿ�ĳ���`��",0},
	{MENU_VIDEO_SLIMITVALUE_AUTO,"���� (PAL/NTSC�𔻕ʂ���)",0},
	{MENU_VIDEO_FSKIP_MODE_AUTO,"%d�ȉ��Ŏ����I�ɕύX",0},
	{MENU_VIDEO_FSKIP_CHANGEAUTO_AUTO,"   �ݒ�l�ȉ��Ŏ����I�ɕύX",0},
	{MENU_VIDEO_FSKIP_CHANGEAUTO_FIXED,"   �Œ�",0},

	{MENU_STATUS_VIDEO_SCRCALIB,"�\\���{�^�� : ��ʈʒu  " SJIS_STAR "  �A�i���O�X�e�B�b�N : ��ʃT�C�Y  " SJIS_STAR "  " SJIS_TRIANGLE " �W��  " SJIS_STAR "  " MSG_BTN_NEGATIVE " �I��",0},

	// SOUND OPTIONS
	{MENU_ICONS_SOUND,"����",0},
	{MENU_ICONS_SOUND_MODE,"�T�E���h���[�h",0},
	{MENU_ICONS_SOUND_MODE_HELP,"�G�~�����[�g���Ȃ��̂��ő��ł���\n�������̃Q�[���͓��삵�܂���B",0},
	{MENU_ICONS_SOUND_FREQ,"�o�͎��g��",0},
	{MENU_ICONS_SOUND_FREQ_HELP,"�Ⴂ�ق��������Ȃ�܂��B\n�����ق����������悭�Ȃ�܂��B",0},
	{MENU_ICONS_SOUND_APURATIO,"APU������",0},
	{MENU_ICONS_SOUND_APURATIO_HELP,"���ꂪ�������邩�m���Ă���\n���x�ȃ��[�U�[�����ł��B",0},
	// MISC OPTIONS
	{MENU_ICONS_MISC,"���̑�",0},
	{MENU_ICONS_MISC_FILEVIEWER,"�t�@�C���\\��",0},
	{MENU_ICONS_MISC_FILEVIEWER_HELP,"�ȒP�ȃt�@�C���r���[���[�ł��B",0},
	{MENU_ICONS_MISC_PSPCLOCK,"PSP�N���b�N���x",0},	
	{MENU_ICONS_MISC_PSPCLOCK_HELP,"222MHz�ȏ�̓I�[�o�[�N���b�N�ł�\n����܂���B\n���S�ł����d�r�𑬂�����܂��B",0},
	{MENU_ICONS_MISC_HACKDEBUG,"�n�b�N/�f�o�b�O���j���[",0},
	{MENU_ICONS_MISC_HACKDEBUG_HELP,"���x�ȃ��[�U�[�����ł��B\n�`��𒲐����ăX�s�[�h��\n����̂ɖ𗧂��܂��B",0},
	{MENU_ICONS_MISC_SNAPSHOT,"�X�i�b�v�V���b�g",0},
	{MENU_ICONS_MISC_SNAPSHOT_HELP,"���݂̃Q�[���̉�ʂ�\n�X�i�b�v�V���b�g���B��܂��B\n�t�@�C���ꗗ�Ŏg���܂��B",0},
	{MENU_ICONS_MISC_SWAPBG,"�w�i�؂�ւ�",0},
	{MENU_ICONS_MISC_SWAPBG_HELP,"DATA/logo.zip����\n�w�i��\\�����܂��B",0},
	{MENU_ICONS_MISC_BGMUSIC,"���j���[BGM",0},
	{MENU_ICONS_MISC_BGMUSIC_HELP,"���j���[BGM��PSP��300MHz��\n���삳����K�v������܂��B\n���y��DATA/music.zip����Đ����܂��B\nSPC�t�H�[�}�b�g�݂̂ł��B",0},
	{MENU_ICONS_MISC_BGFX,"���j���[�o�b�N�O���E���hCG",0},
	{MENU_ICONS_MISC_BGFX_HELP,"PS2DEV spline sample�̑f�G��CG�ł��B",0},
	{MENU_ICONS_MISC_PADBEEP,"�p�b�h�r�[�v",0},
	{MENU_ICONS_MISC_PADBEEP_HELP,"�r�[�v�������j���[��t�@�C���ꗗ��\n�ړ����Ă���Ƃ��ɖ�܂��B",0},
	{MENU_ICONS_MISC_AUTOSTART,"�Ō�ɋN������ROM�������N������",0},
	{MENU_ICONS_MISC_AUTOSTART_HELP,"�u�͂��v�ɂ���ƁA�G�~�����[�^�[��\n�N�������Ƃ��Ɏ����I��\n�Ō�ɋN������ROM���N�����܂��B",0},
	{MENU_ICONS_MISC_OSK,"OSK",0},
	{MENU_ICONS_MISC_OSK_HELP,"OSK�Ƃ͉�ʏ�̃L�[�{�[�h�̂��Ƃł��B\nDanzeff OSK�̓A���t�@�x�b�g��PSP��\n���͂���ۂɍœK�ł��B\nSCE����OSK�͓��{���ePSP��\n���͂���ۂɍœK�ł��B",0},

	{MENU_MUSIC_SWAPBG_NODATA,"�f�[�^������܂���",0},
	{MENU_MISC_SWAPBG_RAND,"   �����_��",0},

	{MENU_MISC_OSK_DANZEFF,"Danzeff",0},
	{MENU_MISC_OSK_OFFICIAL,"����",0},

	{MENU_STATUS_MISC_HACKDEBUG,MSG_BTN_NEGATIVE " ���C�����j���[   ",0},
	{MENU_STATUS_MISC_HACKDEBUG_FUNC,MSG_BTN_POSITIVE " OK     " SJIS_STAR "    " MSG_BTN_NEGATIVE " ���C�����j���[   ",0},
	{MENU_STATUS_MISC_HACKDEBUG_0,SJIS_STAR "    " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_0,SJIS_STAR "      " SJIS_TRIANGLE " �w���v       " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_1,SJIS_STAR "     " SJIS_TRIANGLE "   �w���v      " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_2,SJIS_STAR "    " SJIS_TRIANGLE "     �w���v     " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX"},
	{MENU_STATUS_MISC_HACKDEBUG_HELP_3,SJIS_STAR "   " SJIS_TRIANGLE "       �w���v    " SJIS_STAR "      " SJIS_UP "," SJIS_DOWN " �I�� " SJIS_LEFT "," SJIS_RIGHT " �l��ύX"},

	{MENU_TITLE_MISC_HACKDEBUG,"[" EMUNAME_VERSION "] - ���j���[",0},

	// CHEATS
	{MENU_ICONS_CHEATS,"�`�[�g",0},
	{MENU_ICONS_CHEATS_ADDRAW,"RAW�R�[�h�ǉ�",0},
	{MENU_ICONS_CHEATS_ADDRAW_HELP,"RAW�R�[�h��ǉ����܂��B",0},
	{MENU_ICONS_CHEATS_ADDGG,"Game Genie�R�[�h�ǉ�",0},
	{MENU_ICONS_CHEATS_ADDGG_HELP,"Game Genie�R�[�h��ǉ����܂��B",0},
	{MENU_ICONS_CHEATS_ADDPAR,"�v���A�N�V�������v���C�R�[�h�ǉ�",0},
	{MENU_ICONS_CHEATS_ADDPAR_HELP,"�v���A�N�V�������v���C�R�[�h��\n�ǉ����܂��B",0},
	{MENU_ICONS_CHEATS_ADDGF,"GoldFinger�R�[�h�ǉ�",0},
	{MENU_ICONS_CHEATS_ADDGF_HELP,"GoldFinger�R�[�h��ǉ����܂��B",0},
	{MENU_ICONS_CHEATS_DISABLE,"�R�[�h������",0},
	{MENU_ICONS_CHEATS_DISABLE_HELP,"�R�[�h�𖳌������܂��B",0},
	{MENU_ICONS_CHEATS_DISABLEALL,"�S�R�[�h������",0},
	{MENU_ICONS_CHEATS_DISABLEALL_HELP,"�S�ẴR�[�h�𖳌������܂��B",0},
	{MENU_ICONS_CHEATS_ENABLE,"�R�[�h�L����",0},
	{MENU_ICONS_CHEATS_ENABLE_HELP,"�R�[�h��L���ɂ��܂��B",0},
	{MENU_ICONS_CHEATS_ENABLEALL,"�S�R�[�h�L����",0},
	{MENU_ICONS_CHEATS_ENABLEALL_HELP,"�S�ẴR�[�h��L�������܂��B",0},
	{MENU_ICONS_CHEATS_REMOVE,"�R�[�h�폜",0},
	{MENU_ICONS_CHEATS_REMOVE_HELP,"�R�[�h���폜���܂��B",0},
	{MENU_ICONS_CHEATS_REMOVEALL,"�S�R�[�h�폜",0},
	{MENU_ICONS_CHEATS_REMOVEALL_HELP,"�S�ẴR�[�h���폜���܂��B",0},
	// ABOUT
	{MENU_ICONS_ABOUT,"���̃\\�t�g�ɂ���",0},
	{MENU_ICONS_ABOUT_CREDITS,"�N���W�b�g",0},
	{MENU_ICONS_ABOUT_VERSION,"�o�[�W�������",0},

	{MENU_ABOUT_VERSION_TIMESTAMP,"�r���h���� : %s",0},
	{MENU_ABOUT_VERSION_GCCVER,"�g�p����GCC : %s",0},

	//Others
	// Adhoc
	{ADHOC_CONNECTING,"�ڑ����Ă��܂�...\n",0},
	{ADHOC_SELECTORRETURN,"�ڑ�����T�[�o�[��I�Ԃ�," SJIS_TRIANGLE "�{�^���Ŗ߂��Ă��������B",0},
	{ADHOC_WAITING,"%s���ڑ������F����̂�҂��Ă��܂��B\n�L�����Z������ɂ�" MSG_BTN_POSITIVE "�{�^���������Ă��������B\n",0},
	{ADHOC_REQUESTED,"%s���ڑ���v�����Ă��܂��B\n�ڑ������F����ɂ�" MSG_BTN_NEGATIVE "�{�^����,�L�����Z������ɂ�" MSG_BTN_POSITIVE "�{�^���������Ă��������B\n",0},
	{ADHOC_CONNECTED,"�ڑ����܂���",0},
	{ADHOC_STATE,"  �ڑ��� %d/1\n",0},
	{ADHOC_UNKNOWNCOMMAND,"�s���ȃR�}���h %02X �ł��B",0},
	{ADHOC_SYNCLOST_SERVER,"�T�[�o�[�������s : �ē������܂�",20},
	{ADHOC_SYNCLOST_CLIENT,"�N���C�A���g�������s : �ē������܂�",20},
	{ADHOC_CLOSING,"�ڑ�����Ă��܂�",60},
	{ADHOC_DRIVERLOAD_ERR,"�l�b�g�h���C�o�ǂݍ��݃G���[",60*2},
	{ADHOC_INIT_ERR,"�A�h�z�b�N�Q�[���̏������ɖ�肪�������܂���\n",60},
	{ADHOC_LOST_CONNECTION,"�ڑ��������܂���",60},
	{ADHOC_CORRUPTED_PKT,"�j�������p�P�b�g",0},
	{ADHOC_STATE_SIZE,"�X�e�[�g�f�[�^�T�C�Y : %d",0},
	{ADHOC_FILE_ERR_RECEIVING,"�X�e�[�g�t�@�C����M�G���[",60*1},
	{ADHOC_FILE_ERR_SENDING,"�X�e�[�g�t�@�C�����M�G���[",60*1},
	{ADHOC_STILL,"�c�� : %d",0},
	{ADHOC_WAITING_OTHER,"���̃v���C���[��҂��Ă��܂�\n\n�ڑ�����ʐM�ΐ����߂�ɂ�" SJIS_TRIANGLE "�{�^���������Ă�������\n",10},
	{ADHOC_NETWORKERR_1,"�l�b�g���[�N�G���[1",60*1},
	{ADHOC_CANNOTFIND,"�X�e�[�g�Z�[�u��������܂���",60},
	{ADHOC_FLUSHING,"�l�b�g���[�N���������Ă��܂��B���΂炭���҂����������B",10},
	// LOAD/SAVE
	{LOADSAVE_AUTOSAVETIMER,"�����Z�[�u���Ă��܂�...",0},
	{LOADSAVE_EXPORTS9XSTATE,"snes9xTYL�t�@�C����������܂���",0},
	// VIDEO
	{VIDEO_ENGINE_APPROX,"�P�ꃂ�[�h : �قڐ��m�ȃ\\�t�g�E�F�A�`��",30},
	{VIDEO_ENGINE_ACCUR,"�P�ꃂ�[�h : ���m�ȃ\\�t�g�E�F�A�`��",30},
	{VIDEO_ENGINE_ACCEL,"�P�ꃂ�[�h : PSP�A�N�Z�����[�^",30},
	{VIDEO_ENGINE_ACCEL_ACCUR,"�������[�h : PSP�A�N�Z�����[�^ + ���m�ȃ\\�t�g�E�F�A�`��",30},
	{VIDEO_ENGINE_ACCEL_APPROX,"�������[�h : PSP�A�N�Z�����[�^ + �قڐ��m�ȃ\\�t�g�E�F�A�`��",30},
	{VIDEO_FSKIP_AUTO,"�t���[���X�L�b�v : ����",0},
	{VIDEO_FSKIP_MANUAL,"�t���[���X�L�b�v : %d",0},
	// Scroll Message
	{SCROLL_TITLE,"   ,    �ړ�   -  ,  ����         ",0},
	{SCROLL_STATUS_0,"%d/%d�s��  -  %d/%d�y�[�W",0},
	{SCROLL_STATUS_1,"   �I��,        �w���v",0},
	{SCROLL_HELP,"Snes9xTYL - �t�@�C���r���[���[\n\n" SJIS_TRIANGLE "�{�^���Ō�����,���̌�" MSG_BTN_POSITIVE "�{�^���Ŏ�������," SJIS_SQUARE "�{�^���őO���������܂��B\n" \
			SJIS_UP "," SJIS_DOWN "�{�^���ŕ��͂��X�N���[����, L,R�{�^���ł�葁���X�N���[�����܂��B\n" MSG_BTN_NEGATIVE "�ŏI�����܂��B\n\n�Ō�̈ʒu�͓����t�@�C�����J�����Έێ�����܂��B\n�������ق��̃t�@�C�����J���ƌ��ɖ߂�܂��B\n\n" \
			MSG_BTN_NEGATIVE "�{�^���������Ă�������",0},
	{SCROLL_SEARCHING,"�������Ă��܂�...",0},
	{SCROLL_STRNOTFOUND,"������͌�����܂���ł���",30},
	{SCROLL_DISCLAIMER,"�Ɛӎ���",0},
	{SCROLL_OSK_DESC,"�������镶�������͂��Ă�������",0},
	//Settings
	{SETTINGS_NOTCOMPLETE,"���ݒ�t�@�C�������S�ł͂���܂���\n\n�ȑO�̃o�[�W�����̂��̂̉\\��������܂��B\n\n�V�����ݒ肪�W���l�Őݒ肳��܂��B",60*3},
	{SETTINGS_NOTFOUND,"�ݒ肪������܂���B�W���ݒ���g���܂��B",10},
	{SETTINGS_FORCING_DEFAULT,"�����I�ɕW���ݒ���g�p���Ă��܂�",10},
	{SETTINGS_IGNORED,"�ȑO�̌݊����̂Ȃ��o�[�W������INI�t�@�C���ł��B�t�@�C���͖�������܂����B",20},
	{SETTINGS_FOUND,"�ݒ肪������܂���\n\n""%s""",0},
	{SETTINGS_DIFF,"�قȂ�o�[�W������INI�t�@�C���ł��B",20},
	//Others
	{APU_DEBUGGING,"APU�f�o�b�O",10},
	{BGMUSIC_PLAYING,"SPC�t�@�C�����Đ����Ă��܂�...",0},
	{FOUND_SRAM,"SRAM�t�@�C����������܂���",60},
	{CANCEL,"�L�����Z��",0},
	{INPUTBOX_OK,"\n\n      ����",0},
#ifdef ME_SOUND
	{BAT_ISLOW,"�d�r�c�ʂ��ቺ���Ă��邽�߁A����SRAM��ݒ�̕ۑ��A�X�e�[�g�Z�[�u�������ɂ���Ă��܂��B\n\n���̉�ʂ�3�b�ŕ��܂��B",60*3},
#else
	{BAT_ISLOW,"�d�r�c�ʂ��ቺ���Ă��邽�߁A����SRAM��ݒ�̕ۑ��A�X�e�[�g�Z�[�u�������ɂ���Ă��܂��B\n\nPSP���X���[�v���[�h�ɂ��Ă��Ƃŏ[�d���邱�Ƃ��ł��܂��B\n\n���̉�ʂ�3�b�ŕ��܂��B",60*3},
#endif
	{CONV_DONE,"�ϊ�����",30},
	{ROM_LIED,"ROM����Ԉ�����^�C�v�̏����擾���܂����B�Ď��s���܂��B",30},
	{LOADING_ROM,"%dKo�ǂݍ���ł��܂�...",0},
	{TYPE,"�^�C�v",0},
	{MODE,"���[�h",0},
	{COMPANY,"������",0},
#ifdef _BSX_151_
	{SRAM_NOTFOUND,"SRAM�t�@�C����������܂���ł����BBS-X.srm������ɓǂݍ��܂�܂��B",30},
	{SRAM_BSX_NOTFOUND,"SRAM�t�@�C���������炸�ABS-X.srm��������܂���ł����B",30},
#endif
	{CORRUPT,"�s��",0},
	{ROM_ONLY,"ROM�̂�",0},
	{EXTENDING,"�K�p�͈͂��g�債�Ă��܂�",30},
	{EXTENDING_TARGET,"�K�p�͈͂�%d����%d�Ɋg�債�Ă��܂�\n",0},
	{INIT_OSK,"OSK�����������Ă��܂�...",0}
};

////////////////////////////////////////////////////////////////////////////////////////
// psp_msg_string
// -------------- 
//		input : message id
//		output : string
//		comments : return the asked string in current language
////////////////////////////////////////////////////////////////////////////////////////
char *psp_msg_string(int num) {
	char *p;
	char *src = (char *)"unknown string";
	int msg_num=0;
	if (os9x_language == PSP_SYSTEMPARAM_LANGUAGE_JAPANESE)
		while (msg_num<MSG_TOTAL_ENTRIES) {
			if (num==s9xTYL_msg_ja[msg_num].msg_id) src = (char *)s9xTYL_msg_ja[msg_num].msg;
			msg_num++;
		}
	else
		while (msg_num<MSG_TOTAL_ENTRIES) {
			if (num==s9xTYL_msg_en[msg_num].msg_id) src = (char *)s9xTYL_msg_en[msg_num].msg;
			msg_num++;
		}

	for (p = src; *p; p++)
		switch(*p) {
			case 0x0B:
				*p = os9x_btn_positive_str[1];
				break;
			case 0x0E:
				*p = os9x_btn_negative_str[1];
				break;
		}

	return src;
}

////////////////////////////////////////////////////////////////////////////////////////
// psp_msg
// -------------- 
//		input : message id, display length
//		output : none
//		comments : show the message in current language.
//							 len allow display length value and special dialog selection
//							 ("yes/no" box or "ok" box).
////////////////////////////////////////////////////////////////////////////////////////
int psp_msg(int num,int len) {
	char *p = (char *)"unknown string";
	int msg_num=0;

	if (os9x_language == PSP_SYSTEMPARAM_LANGUAGE_JAPANESE)
		while (msg_num<MSG_TOTAL_ENTRIES) {
			if (num==s9xTYL_msg_ja[msg_num].msg_id) {
				p = (char *)s9xTYL_msg_ja[msg_num].msg;
				break;
			}
			msg_num++;
		}
	else
		while (msg_num<MSG_TOTAL_ENTRIES) {
			if (num==s9xTYL_msg_en[msg_num].msg_id) {
				p = (char *)s9xTYL_msg_en[msg_num].msg;
				break;
			}
			msg_num++;
		}

	while (*p) {
		switch(*p) {
			case 0x0B:
				*p = os9x_btn_positive_str[1];
				break;
			case 0x0E:
				*p = os9x_btn_negative_str[1];
				break;
			}
		p++;
	}

	if (msg_num==MSG_TOTAL_ENTRIES) return 0;

	if (os9x_language == PSP_SYSTEMPARAM_LANGUAGE_JAPANESE) {
		if (len==MSG_DEFAULT)	len=s9xTYL_msg_ja[msg_num].len;
		if (len>=0)	msgBoxLines(s9xTYL_msg_ja[msg_num].msg,s9xTYL_msg_ja[msg_num].len);
		else if (len==-1) inputBoxOK(s9xTYL_msg_ja[msg_num].msg);
		else if (len==-2) return inputBox(s9xTYL_msg_ja[msg_num].msg);
	}
	else {
		if (len==MSG_DEFAULT)	len=s9xTYL_msg_en[msg_num].len;
		if (len>=0)	msgBoxLines(s9xTYL_msg_en[msg_num].msg,s9xTYL_msg_en[msg_num].len);
		else if (len==-1) inputBoxOK(s9xTYL_msg_en[msg_num].msg);
		else if (len==-2) return inputBox(s9xTYL_msg_en[msg_num].msg);
	}

	return 0;
}

