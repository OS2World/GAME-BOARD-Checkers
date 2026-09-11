/*------------------------------------
   CHECKERS.H header file, Version 1.0
  ------------------------------------*/

          /* Common constants */

#define BLACK                       0
#define WHITE                       1
#define NORM                        0
#define KING                        1

#define LEVEL_SIMPLE                0
#define LEVEL_BEGINNER              1
#define LEVEL_INTERMEDIATE          2
#define LEVEL_ADVANCED              3

          /* Structure for representing board */

typedef struct
     {
     ULONG ulBlack ;
     ULONG ulWhite ;
     ULONG ulKing ;
     }
     BOARD ;

typedef BOARD *PBOARD ;

#define CKR_BOARD_DEFINED

          /* Structure for a new game */

typedef struct
     {
     BOARD brd ;
     HWND  hwndBlack ;
     HWND  hwndWhite ;
     HWND  hwndBoard ;
     HWND  hwndJudge ;
     HWND  hwndClient ;
     SHORT sBottom ;
     SHORT sLevel ;
     }
     NEWGAME ;

typedef NEWGAME *PNEWGAME ;

typedef struct
     {
     BOARD brd ;
     SHORT sColor ;
     SHORT sLevel ;
     }
     GAMEDLG ;

typedef GAMEDLG *PGAMEDLG ;

typedef struct
     {
     BOARD brd ;
     SHORT sBottom ;
     }
     SETUPDLG ;

typedef SETUPDLG *PSETUPDLG ;

          /* Resource ID */

#define ID_RESOURCE                 1

          /* Pointer IDs */

#define IDP_UPHAND                  2
#define IDP_DNHAND                  3

          /* Game menu (100-199) */

#define IDM_SUBMENU_GAME         1000
#define IDM_NEW                   101
#define IDM_PAUSE                 102
#define IDM_QUIT_GAME             103
#define IDM_EXIT                  104

          /* Options menu (200-299) */

#define IDM_SUBMENU_OPTS          200
#define IDM_SUBMENU_COLORS        210
#define IDM_COLOR_BACKGROUND      201
#define IDM_COLOR_BLACK_SQUARE    202
#define IDM_COLOR_WHITE_SQUARE    203
#define IDM_COLOR_BLACK_PIECE     204
#define IDM_COLOR_WHITE_PIECE     205
#define IDM_COLOR_STANDARD        206
#define IDM_SAVEONEXIT            207
#define IDM_FRAME                 209

          /* Language submenu (300-399) */

#define IDM_SUBMENU_LANG          350
#define IDM_LANG_EN               301
#define IDM_LANG_ES               302
#define IDM_LANG_NL               303
#define IDM_LANG_DE               304
#define IDM_LANG_FR               305
#define IDM_LANG_IT               306

          /* Help menu (900-999) */

#define IDM_SUBMENU_HELP          900
#define IDM_ABOUT                 999

          /* Dialog Box IDs */

#define IDD_NEWGAME_DLG             1
#define IDD_ABOUT_DLG               2
#define IDD_COLOR_DLG               3
#define IDD_SETUP_DLG               4

#define IDD_HEADING                10
#define IDD_COLOR                  20

#define IDD_BLACK                 100
#define IDD_WHITE                 101

#define IDD_SIMPLE                110
#define IDD_BEGINNER              111
#define IDD_INTERMEDIATE          112
#define IDD_ADVANCED              113

#define IDD_SETUP                 120
#define IDD_BOTTOM                121
#define IDD_TOP                   122

#define IDD_NEWGAME_TITLE         150
#define IDD_COLOR_GROUP           151
#define IDD_LEVEL_GROUP           152

          /* User-Defined Messages */

#define WM_NEW_GAME                     (WM_USER +  1)
#define WM_TELL_BOARD_COLOR_DIALOG      (WM_USER + 10)
#define WM_TELL_BOARD_STANDARD_COLORS   (WM_USER + 11)
#define WM_JUDGE_SAYS_MAKE_MOVE         (WM_USER + 20)
#define WM_JUDGE_SAYS_SHOW_HOURGLASS    (WM_USER + 30)
#define WM_JUDGE_SAYS_SHOW_ARROW        (WM_USER + 31)
#define WM_JUDGE_SAYS_MOVE_PIECE        (WM_USER + 32)
#define WM_JUDGE_SAYS_KING_PIECE        (WM_USER + 33)
#define WM_JUDGE_SAYS_REMOVE_PIECE      (WM_USER + 34)
#define WM_QUERY_JUDGE_CURRENT_BOARD    (WM_USER + 40)
#define WM_QUERY_JUDGE_PICKUP_PIECE     (WM_USER + 41)
#define WM_QUERY_JUDGE_IF_KING          (WM_USER + 42)
#define WM_QUERY_JUDGE_PUTDOWN_PIECE    (WM_USER + 43)
#define WM_QUERY_JUDGE_CONTINUE_MOVE    (WM_USER + 44)
#define WM_TELL_JUDGE_BOARD_MOVE_ENDED  (WM_USER + 45)
#define WM_TELL_JUDGE_PIECE_MOVED       (WM_USER + 46)
#define WM_TELL_JUDGE_STRAT_MOVE_ENDED  (WM_USER + 50)
#define WM_TELL_CLIENT_GAME_OVER        (WM_USER + 60)
#define WM_TELL_CLIENT_NO_MEMORY        (WM_USER + 70)
