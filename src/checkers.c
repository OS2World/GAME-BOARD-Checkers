/*------------------------------------------------------------------------
   CHECKERS.C -- OS/2 Presentation Manager Checkers Program, Version 1.0
                 Original: (c) 1990, Charles Petzold
                 Microsoft Systems Journal, September 1990
                 Open Watcom port and enhancements, 2026
  ------------------------------------------------------------------------*/

#define INCL_WIN
#define INCL_PRF
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "checkers.h"
#include "lang.h"

MRESULT EXPENTRY ClientWndProc  (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY JudgeWndProc   (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY BoardWndProc   (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY StratWndProc   (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY NewGameDlgProc (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY AboutDlgProc   (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY SetupDlgProc   (HWND, ULONG, MPARAM, MPARAM) ;
MRESULT EXPENTRY SetupCntlProc  (HWND, ULONG, MPARAM, MPARAM) ;

static const CHAR szBldLevel[] =
    "@#Charles Petzold:1.1#@##1## 10 Sep 2026 21:00:00      ARCAOS:::0::::@@Checkers Game for OS/2\r\n\x1a" ;

/* ---------- Language support ----------------------------------------- */

int current_lang = LANG_EN ;

const char *lang_strings[LANG_COUNT][STR_COUNT] = {
    /* EN */
    { "~Game",
      "~New Game\tCtrl+N", "~Pause Game\tCtrl+P", "~Quit Game\tCtrl+Q", "~Exit\tCtrl+X",
      "~Options", "~Colors",
      "Window ~Background...", "~Black Square...", "~White Square...",
      "B~lack Piece...", "W~hite Piece...", "~Standard Colors",
      "~Language", "~Save Settings on Exit", "~Frame Controls\tCtrl+F",
      "~Help", "~About...",
      "Start New Game", "Color", "Level",
      "Black", "White",
      "Simple", "Beginner", "Intermediate", "Adv (BUGGY!)",
      "OK", "Cancel", "Setup..." },
    /* ES */
    { "~Juego",
      "~Nueva Partida\tCtrl+N", "~Pausa\tCtrl+P", "~Abandonar\tCtrl+Q", "~Salir\tCtrl+X",
      "~Opciones", "~Colores",
      "Fondo de ~Ventana...", "Cuadro ~Negro...", "Cuadro ~Blanco...",
      "Ficha ~Negra...", "Ficha ~Blanca...", "Colores ~Estandar",
      "~Idioma", "~Guardar Config al Salir", "~Controles Marco\tCtrl+F",
      "A~yuda", "~About...",
      "Iniciar Nueva Partida", "Color", "Nivel",
      "Negras", "Blancas",
      "Simple", "Principiante", "Intermedio", "Avanzado (FALLA!)",
      "Aceptar", "Cancelar", "Tablero..." },
    /* NL */
    { "~Spel",
      "~Nieuw Spel\tCtrl+N", "~Pauzeren\tCtrl+P", "~Stoppen\tCtrl+Q", "~Afsluiten\tCtrl+X",
      "~Opties", "~Kleuren",
      "Venster~achtergrond...", "~Zwart Vakje...", "~Wit Vakje...",
      "~Zwarte Steen...", "~Witte Steen...", "~Standaard Kleuren",
      "~Taal", "~Instellingen Opslaan", "~Kaderbesturing\tCtrl+F",
      "~Help", "~About...",
      "Nieuw Spel Starten", "Kleur", "Niveau",
      "Zwart", "Wit",
      "Simpel", "Beginner", "Gemiddeld", "Gevorderd (BUG!)",
      "OK", "Annuleren", "Opstellen..." },
    /* DE */
    { "~Spiel",
      "~Neues Spiel\tCtrl+N", "~Pause\tCtrl+P", "~Spiel Beenden\tCtrl+Q", "~Beenden\tCtrl+X",
      "~Optionen", "~Farben",
      "Fenster~hintergrund...", "~Schwarzes Feld...", "~Weisses Feld...",
      "~Schwarzer Stein...", "~Weisser Stein...", "~Standardfarben",
      "~Sprache", "~Einstellungen Speichern", "~Rahmensteuerung\tCtrl+F",
      "~Hilfe", "~About...",
      "Neues Spiel Starten", "Farbe", "Stufe",
      "Schwarz", "Weiss",
      "Einfach", "Anfanger", "Mittel", "Fortgeschritten (BUG!)",
      "OK", "Abbrechen", "Aufstellung..." },
    /* FR */
    { "~Jeu",
      "~Nouveau Jeu\tCtrl+N", "~Pause\tCtrl+P", "~Quitter la Partie\tCtrl+Q", "~Fermer\tCtrl+X",
      "~Options", "~Couleurs",
      "Arriere-plan ~Fenetre...", "Case ~Noire...", "Case ~Blanche...",
      "Piece ~Noire...", "Piece ~Blanche...", "Couleurs ~Standard",
      "~Langue", "~Sauvegarder a la Fermeture", "~Controles Cadre\tCtrl+F",
      "~Aide", "~About...",
      "Demarrer Nouvelle Partie", "Couleur", "Niveau",
      "Noir", "Blanc",
      "Simple", "Debutant", "Intermediaire", "Avance (BOGUE!)",
      "OK", "Annuler", "Configuration..." },
    /* IT */
    { "~Gioco",
      "~Nuova Partita\tCtrl+N", "~Pausa\tCtrl+P", "~Abbandona Partita\tCtrl+Q", "~Esci\tCtrl+X",
      "~Opzioni", "~Colori",
      "Sfondo ~Finestra...", "Casella ~Nera...", "Casella ~Bianca...",
      "Pedina ~Nera...", "Pedina ~Bianca...", "Colori ~Standard",
      "~Lingua", "~Salva Impostazioni all'Uscita", "~Controlli Cornice\tCtrl+F",
      "A~iuto", "~About...",
      "Avvia Nuova Partita", "Colore", "Livello",
      "Nero", "Bianco",
      "Semplice", "Principiante", "Intermedio", "Avanzato (BUG!)",
      "OK", "Annulla", "Configurazione..." }
} ;

/* ---------- Settings -------------------------------------------------- */

typedef struct {
    INT  nLang ;
    BOOL bSaveOnExit ;
} SETTINGS ;

static BOOL bSaveOnExit  = FALSE ;
static BOOL bFrameHidden = FALSE ;

/* ---------- Globals --------------------------------------------------- */

HAB  hab ;
HWND hwndObject    = NULLHANDLE ;   /* private sink for hidden frame controls */
HWND hwndTitleBar  = NULLHANDLE ;
HWND hwndSysMenu   = NULLHANDLE ;
HWND hwndFMenu     = NULLHANDLE ;
HWND hwndMinMax    = NULLHANDLE ;

/* ---------- Forward declarations -------------------------------------- */

static void load_settings (void) ;
static void save_settings (void) ;
static void set_language  (HWND hwndFrame, HWND hwndMenu, int lang) ;

/* ---------- Settings persistence -------------------------------------- */

static void load_settings (void)
{
    SETTINGS settings ;
    ULONG    ulDataSize = sizeof (settings) ;

    if (PrfQueryProfileData (HINI_USERPROFILE, "Checkers", "Settings",
                             &settings, &ulDataSize) &&
        ulDataSize == sizeof (settings))
    {
        if (settings.nLang >= LANG_EN && settings.nLang < LANG_COUNT)
            current_lang = settings.nLang ;
        bSaveOnExit = settings.bSaveOnExit ;
    }
}

static void save_settings (void)
{
    SETTINGS settings ;
    settings.nLang     = current_lang ;
    settings.bSaveOnExit = bSaveOnExit ;
    PrfWriteProfileData (HINI_USERPROFILE, "Checkers", "Settings", &settings, sizeof (settings)) ;
}

/* ---------- Language update ------------------------------------------ */

static void set_language (HWND hwndFrame, HWND hwndMenu, int lang)
{
    MENUITEM mi ;
    HWND     hwndGame, hwndOpts, hwndColors, hwndLangSub, hwndHelp ;
    int      i ;

    current_lang = lang ;

    /* Obtain submenu window handles */
    WinSendMsg (hwndMenu, MM_QUERYITEM,
                MPFROM2SHORT (IDM_SUBMENU_GAME, TRUE), MPFROMP (&mi)) ;
    hwndGame = mi.hwndSubMenu ;

    WinSendMsg (hwndMenu, MM_QUERYITEM,
                MPFROM2SHORT (IDM_SUBMENU_OPTS, TRUE), MPFROMP (&mi)) ;
    hwndOpts = mi.hwndSubMenu ;

    WinSendMsg (hwndOpts, MM_QUERYITEM,
                MPFROM2SHORT (IDM_SUBMENU_COLORS, FALSE), MPFROMP (&mi)) ;
    hwndColors = mi.hwndSubMenu ;

    WinSendMsg (hwndOpts, MM_QUERYITEM,
                MPFROM2SHORT (IDM_SUBMENU_LANG, FALSE), MPFROMP (&mi)) ;
    hwndLangSub = mi.hwndSubMenu ;

    WinSendMsg (hwndMenu, MM_QUERYITEM,
                MPFROM2SHORT (IDM_SUBMENU_HELP, TRUE), MPFROMP (&mi)) ;
    hwndHelp = mi.hwndSubMenu ;

    /* Menu bar top-level captions */
    WinSendMsg (hwndMenu, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SUBMENU_GAME), MPFROMP (tr (STR_MENU_GAME))) ;
    WinSendMsg (hwndMenu, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SUBMENU_OPTS), MPFROMP (tr (STR_MENU_OPTIONS))) ;
    WinSendMsg (hwndMenu, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SUBMENU_HELP), MPFROMP (tr (STR_MENU_HELP))) ;

    /* Game submenu items */
    WinSendMsg (hwndGame, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_NEW),       MPFROMP (tr (STR_MENU_NEW))) ;
    WinSendMsg (hwndGame, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_PAUSE),     MPFROMP (tr (STR_MENU_PAUSE))) ;
    WinSendMsg (hwndGame, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_QUIT_GAME), MPFROMP (tr (STR_MENU_QUIT))) ;
    WinSendMsg (hwndGame, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_EXIT),      MPFROMP (tr (STR_MENU_EXIT))) ;

    /* Options submenu items */
    WinSendMsg (hwndOpts, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SUBMENU_COLORS), MPFROMP (tr (STR_MENU_COLORS))) ;
    WinSendMsg (hwndOpts, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SUBMENU_LANG),   MPFROMP (tr (STR_MENU_LANGUAGE))) ;
    WinSendMsg (hwndOpts, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_SAVEONEXIT), MPFROMP (tr (STR_MENU_SAVEONEXIT))) ;
    WinSendMsg (hwndOpts, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_FRAME),      MPFROMP (tr (STR_MENU_FRAME))) ;

    /* Colors submenu items */
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_BACKGROUND),   MPFROMP (tr (STR_MENU_CLRBKG))) ;
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_BLACK_SQUARE), MPFROMP (tr (STR_MENU_CLRBLKSQ))) ;
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_WHITE_SQUARE), MPFROMP (tr (STR_MENU_CLRWHTSQ))) ;
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_BLACK_PIECE),  MPFROMP (tr (STR_MENU_CLRBLKPC))) ;
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_WHITE_PIECE),  MPFROMP (tr (STR_MENU_CLRWHTPC))) ;
    WinSendMsg (hwndColors, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_COLOR_STANDARD),     MPFROMP (tr (STR_MENU_CLRSTD))) ;

    /* Help submenu items */
    WinSendMsg (hwndHelp, MM_SETITEMTEXT,
                MPFROMSHORT (IDM_ABOUT), MPFROMP (tr (STR_MENU_ABOUT))) ;

    /* Language checkmarks (radio-style) */
    for (i = IDM_LANG_EN ; i <= IDM_LANG_IT ; i++)
        WinSendMsg (hwndLangSub, MM_SETITEMATTR,
                    MPFROM2SHORT (i, FALSE),
                    MPFROM2SHORT (MIA_CHECKED,
                                  (i == IDM_LANG_EN + lang) ? MIA_CHECKED : 0)) ;

    WinSendMsg (hwndFrame, WM_UPDATEFRAME, MPFROMLONG (FCF_MENU), NULL) ;
}

/* ---------- main ------------------------------------------------------ */

int main (void)
{
    static CHAR  szClientClass [] = "Checkers" ;
    static ULONG flFrameFlags    = FCF_TITLEBAR | FCF_SYSMENU    |
                                   FCF_SIZEBORDER | FCF_MINMAX    |
                                   FCF_TASKLIST   | FCF_MENU      |
                                   FCF_ACCELTABLE | FCF_ICON ;
    HMQ   hmq ;
    HWND  hwndFrame, hwndClient ;
    QMSG  qmsg ;
    LONG  cxScr, cyScr, cx, cy, x, y ;

    hab = WinInitialize (0) ;
    hmq = WinCreateMsgQueue (hab, 0) ;
    (void) szBldLevel ;

    load_settings () ;

    WinRegisterClass (hab, szClientClass, ClientWndProc, CS_SIZEREDRAW, 0) ;

    hwndFrame = WinCreateStdWindow (HWND_DESKTOP, 0L,
                                    &flFrameFlags, szClientClass, "Checkers",
                                    0L, 0, ID_RESOURCE, &hwndClient) ;

    /* Create private object window; save frame-control handles before any
       reparenting (same pattern as Asteroids) */
    hwndObject   = WinCreateWindow (HWND_OBJECT, WC_FRAME, " ",
                                    0L, 0, 0, 0, 0,
                                    NULLHANDLE, HWND_TOP, 2, NULL, NULL) ;
    hwndTitleBar = WinWindowFromID (hwndFrame, FID_TITLEBAR) ;
    hwndSysMenu  = WinWindowFromID (hwndFrame, FID_SYSMENU) ;
    hwndFMenu    = WinWindowFromID (hwndFrame, FID_MENU) ;
    hwndMinMax   = WinWindowFromID (hwndFrame, FID_MINMAX) ;

    cxScr = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN) ;
    cyScr = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN) ;
    cx    = 1024 ;
    cy    =  768 ;
    x     = (cxScr - cx) / 2 ;
    y     = (cyScr - cy) / 2 ;
    if (x < 0) x = 0 ;
    if (y < 0) y = 0 ;

    WinSetWindowPos (hwndFrame, HWND_TOP, x, y, cx, cy,
                     SWP_MOVE | SWP_SIZE | SWP_ACTIVATE | SWP_SHOW) ;

    while (WinGetMsg (hab, &qmsg, NULLHANDLE, 0, 0))
        WinDispatchMsg (hab, &qmsg) ;

    if (bSaveOnExit)
        save_settings () ;

    WinDestroyWindow (hwndFrame) ;
    WinDestroyMsgQueue (hmq) ;
    WinTerminate (hab) ;
    return 0 ;
}

/* ---------- ClientWndProc --------------------------------------------- */

MRESULT EXPENTRY ClientWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static CHAR    szJudgeClass  [] = "Checkers.Judge",
                   szStratClass  [] = "Checkers.Strat",
                   szBoardClass  [] = "Checkers.Board",
                   szSetupClass  [] = "Checkers.Setup",
                   *apchColor   [2] = { "Black", "White" },
                   *apchCongrats[3] = { "Congratulations!", "Sorry!", "" },
                   szBuffer    [80] ;
    static GAMEDLG gamedlg ;
    static HWND    hwndJudge, hwndStrat, hwndBoard, hwndMenu, hwndFrame ;
    static NEWGAME newgame ;
    static BOOL    bGameRunning = FALSE ;
    SHORT          sWinColor, sCongrats ;

    switch (msg)
    {
    case WM_CREATE:
        hwndFrame = WinQueryWindow (hwnd, QW_PARENT) ;

        WinRegisterClass (hab, szJudgeClass, JudgeWndProc, CS_SIZEREDRAW, 0) ;
        hwndJudge = WinCreateWindow (HWND_OBJECT, szJudgeClass, NULL,
                                     0L, 0, 0, 0, 0,
                                     hwnd, HWND_BOTTOM, 1, NULL, NULL) ;

        WinRegisterClass (hab, szStratClass, StratWndProc, CS_SIZEREDRAW, 0) ;
        hwndStrat = WinCreateWindow (HWND_OBJECT, szStratClass, NULL,
                                     0L, 0, 0, 0, 0,
                                     hwnd, HWND_BOTTOM, 1, NULL, NULL) ;

        WinRegisterClass (hab, szBoardClass, BoardWndProc, CS_SIZEREDRAW, 0) ;
        hwndBoard = WinCreateWindow (hwnd, szBoardClass, NULL,
                                     WS_VISIBLE, 0, 0, 0, 0,
                                     hwnd, HWND_BOTTOM, 2, NULL, NULL) ;

        WinRegisterClass (hab, szSetupClass, SetupCntlProc,
                          CS_SIZEREDRAW, sizeof (PSETUPDLG)) ;

        gamedlg.sColor = IDD_BLACK ;
        gamedlg.sLevel = IDD_INTERMEDIATE ;

        newgame.brd.ulBlack = 0x00000FFF ;
        newgame.brd.ulWhite = 0xFFF00000 ;
        newgame.brd.ulKing  = 0x00000000 ;

        newgame.hwndBlack  = hwndBoard ;
        newgame.hwndWhite  = hwndStrat ;
        newgame.hwndBoard  = hwndBoard ;
        newgame.hwndJudge  = hwndJudge ;
        newgame.hwndClient = hwnd ;
        newgame.sBottom    = BLACK ;
        newgame.sLevel     = LEVEL_INTERMEDIATE ;

        WinSendMsg (hwndJudge, WM_NEW_GAME, &newgame, NULL) ;
        bGameRunning = TRUE ;

        hwndMenu = WinWindowFromID (hwndFrame, FID_MENU) ;

        /* Apply loaded language and set initial checkmarks */
        set_language (hwndFrame, hwndMenu, current_lang) ;

        WinSendMsg (hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT (IDM_SAVEONEXIT, TRUE),
                    MPFROM2SHORT (MIA_CHECKED, bSaveOnExit ? MIA_CHECKED : 0)) ;

        /* Enable Quit Game since a game just started */
        WinSendMsg (hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT (IDM_QUIT_GAME, TRUE),
                    MPFROM2SHORT (MIA_DISABLED, 0)) ;
        return 0 ;

    case WM_TELL_CLIENT_GAME_OVER:
        sWinColor = SHORT1FROMMP (mp1) ;

        if (newgame.hwndBlack == hwndBoard)
            sCongrats = (sWinColor == BLACK) ? 0 : 1 ;
        else if (newgame.hwndWhite == hwndBoard)
            sCongrats = (sWinColor == WHITE) ? 0 : 1 ;
        else
            sCongrats = 2 ;

        sprintf (szBuffer, "Game over!  %s wins.  %s",
                 apchColor [sWinColor], apchCongrats [sCongrats]) ;

        WinMessageBox (HWND_DESKTOP, hwnd, szBuffer, "Checkers", 0,
                       MB_ICONEXCLAMATION | MB_OK) ;

        bGameRunning = FALSE ;
        WinSendMsg (hwndMenu, MM_SETITEMATTR,
                    MPFROM2SHORT (IDM_QUIT_GAME, TRUE),
                    MPFROM2SHORT (MIA_DISABLED, MIA_DISABLED)) ;

        WinSendMsg (hwnd, WM_COMMAND, MPFROMSHORT (IDM_NEW), NULL) ;
        return 0 ;

    case WM_SIZE:
        WinSetWindowPos (hwndBoard, NULLHANDLE, 0, 0,
                         SHORT1FROMMP (mp2), SHORT2FROMMP (mp2),
                         SWP_MOVE | SWP_SIZE) ;
        return 0 ;

    case WM_CHAR:
        return WinSendMsg (hwndBoard, WM_CHAR, mp1, mp2) ;

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case IDM_NEW:
            gamedlg.brd.ulBlack = 0 ;
            gamedlg.brd.ulWhite = 0 ;
            gamedlg.brd.ulKing  = 0 ;

            if (WinDlgBox (HWND_DESKTOP, hwnd, NewGameDlgProc,
                           0, IDD_NEWGAME_DLG, &gamedlg))
            {
                newgame.brd = gamedlg.brd ;

                if (newgame.brd.ulBlack == 0 && newgame.brd.ulWhite == 0)
                {
                    newgame.brd.ulBlack = 0x00000FFF ;
                    newgame.brd.ulWhite = 0xFFF00000 ;
                    newgame.brd.ulKing  = 0x00000000 ;
                }

                switch (gamedlg.sColor)
                {
                case IDD_BLACK:
                    newgame.hwndBlack = hwndBoard ;
                    newgame.hwndWhite = hwndStrat ;
                    newgame.sBottom   = BLACK ;
                    break ;
                case IDD_WHITE:
                    newgame.hwndBlack = hwndStrat ;
                    newgame.hwndWhite = hwndBoard ;
                    newgame.sBottom   = WHITE ;
                    break ;
                }

                newgame.sLevel = LEVEL_SIMPLE + gamedlg.sLevel - IDD_SIMPLE ;

                WinSendMsg (hwndJudge, WM_NEW_GAME, &newgame, NULL) ;
                bGameRunning = TRUE ;

                WinSendMsg (hwndMenu, MM_SETITEMATTR,
                            MPFROM2SHORT (IDM_QUIT_GAME, TRUE),
                            MPFROM2SHORT (MIA_DISABLED, 0)) ;
            }
            return 0 ;

        case IDM_PAUSE:
            /* Placeholder: pause not yet implemented */
            return 0 ;

        case IDM_QUIT_GAME:
            if (bGameRunning)
            {
                WinMessageBox (HWND_DESKTOP, hwnd,
                               "Game abandoned.", "Checkers", 0,
                               MB_INFORMATION | MB_OK) ;
                bGameRunning = FALSE ;
                WinSendMsg (hwndMenu, MM_SETITEMATTR,
                            MPFROM2SHORT (IDM_QUIT_GAME, TRUE),
                            MPFROM2SHORT (MIA_DISABLED, MIA_DISABLED)) ;
                WinSendMsg (hwnd, WM_COMMAND, MPFROMSHORT (IDM_NEW), NULL) ;
            }
            return 0 ;

        case IDM_EXIT:
            WinPostMsg (hwnd, WM_QUIT, NULL, NULL) ;
            return 0 ;

        case IDM_SAVEONEXIT:
            bSaveOnExit = !bSaveOnExit ;
            WinSendMsg (hwndMenu, MM_SETITEMATTR,
                        MPFROM2SHORT (IDM_SAVEONEXIT, TRUE),
                        MPFROM2SHORT (MIA_CHECKED, bSaveOnExit ? MIA_CHECKED : 0)) ;
            if (bSaveOnExit)
                save_settings () ;
            return 0 ;

        case IDM_FRAME:
            if (!bFrameHidden)
            {
                WinSetParent (hwndTitleBar, hwndObject, FALSE) ;
                WinSetParent (hwndSysMenu,  hwndObject, FALSE) ;
                WinSetParent (hwndFMenu,    hwndObject, FALSE) ;
                WinSetParent (hwndMinMax,   hwndObject, FALSE) ;
                WinSendMsg (hwndFrame, WM_UPDATEFRAME,
                            MPFROMLONG (FCF_TITLEBAR | FCF_SYSMENU |
                                        FCF_MINMAX   | FCF_MENU), NULL) ;
                bFrameHidden = TRUE ;
            }
            else
            {
                WinSetParent (hwndTitleBar, hwndFrame, FALSE) ;
                WinSetParent (hwndSysMenu,  hwndFrame, FALSE) ;
                WinSetParent (hwndFMenu,    hwndFrame, FALSE) ;
                WinSetParent (hwndMinMax,   hwndFrame, FALSE) ;
                WinSendMsg (hwndFrame, WM_UPDATEFRAME,
                            MPFROMLONG (FCF_TITLEBAR | FCF_SYSMENU |
                                        FCF_MINMAX   | FCF_MENU), NULL) ;
                WinInvalidateRect (hwndFrame, NULL, TRUE) ;
                hwndMenu     = hwndFMenu ;
                bFrameHidden = FALSE ;
            }
            return 0 ;

        case IDM_LANG_EN:
        case IDM_LANG_ES:
        case IDM_LANG_NL:
        case IDM_LANG_DE:
        case IDM_LANG_FR:
        case IDM_LANG_IT:
            set_language (hwndFrame, hwndMenu,
                          COMMANDMSG (&msg)->cmd - IDM_LANG_EN) ;
            return 0 ;

        case IDM_ABOUT:
            WinDlgBox (HWND_DESKTOP, hwnd, AboutDlgProc,
                       0, IDD_ABOUT_DLG, NULL) ;
            return 0 ;

        case IDM_COLOR_BACKGROUND:
        case IDM_COLOR_BLACK_SQUARE:
        case IDM_COLOR_WHITE_SQUARE:
            WinSendMsg (hwndBoard, WM_TELL_BOARD_COLOR_DIALOG,
                        MPFROMP (&COMMANDMSG (&msg)->cmd),
                        MPFROMSHORT (FALSE)) ;
            return 0 ;

        case IDM_COLOR_BLACK_PIECE:
        case IDM_COLOR_WHITE_PIECE:
            WinSendMsg (hwndBoard, WM_TELL_BOARD_COLOR_DIALOG,
                        MPFROMP (&COMMANDMSG (&msg)->cmd),
                        MPFROMSHORT (TRUE)) ;
            return 0 ;

        case IDM_COLOR_STANDARD:
            WinSendMsg (hwndBoard, WM_TELL_BOARD_STANDARD_COLORS, NULL, NULL) ;
            return 0 ;
        }
        break ;

    case WM_TELL_CLIENT_NO_MEMORY:
        WinMessageBox (HWND_DESKTOP, hwnd,
                       "Cannot allocate enough memory for analyzing "
                       "best move.  The program will be terminated.",
                       "Checkers", 0, MB_OK | MB_CRITICAL) ;
        WinPostMsg (hwnd, WM_QUIT, NULL, NULL) ;
        return 0 ;
    }

    return WinDefWindowProc (hwnd, msg, mp1, mp2) ;
}

/* ---------- NewGameDlgProc -------------------------------------------- */

MRESULT EXPENTRY NewGameDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static GAMEDLG  gamedlgLocal ;
    static PGAMEDLG pgamedlg ;
    static SETUPDLG setupdlg ;

    switch (msg)
    {
    case WM_INITDLG:
        pgamedlg    = PVOIDFROMMP (mp2) ;
        gamedlgLocal = *pgamedlg ;

        WinSetDlgItemText (hwnd, IDD_NEWGAME_TITLE, tr (STR_DLG_START_NEW_GAME)) ;
        WinSetDlgItemText (hwnd, IDD_COLOR_GROUP,   tr (STR_DLG_COLOR)) ;
        WinSetDlgItemText (hwnd, IDD_LEVEL_GROUP,   tr (STR_DLG_LEVEL)) ;
        WinSetDlgItemText (hwnd, IDD_BLACK,         tr (STR_DLG_BLACK)) ;
        WinSetDlgItemText (hwnd, IDD_WHITE,         tr (STR_DLG_WHITE)) ;
        WinSetDlgItemText (hwnd, IDD_SIMPLE,        tr (STR_DLG_SIMPLE)) ;
        WinSetDlgItemText (hwnd, IDD_BEGINNER,      tr (STR_DLG_BEGINNER)) ;
        WinSetDlgItemText (hwnd, IDD_INTERMEDIATE,  tr (STR_DLG_INTERMEDIATE)) ;
        WinSetDlgItemText (hwnd, IDD_ADVANCED,      tr (STR_DLG_ADVANCED)) ;
        WinSetDlgItemText (hwnd, DID_OK,            tr (STR_DLG_OK)) ;
        WinSetDlgItemText (hwnd, DID_CANCEL,        tr (STR_DLG_CANCEL)) ;
        WinSetDlgItemText (hwnd, IDD_SETUP,         tr (STR_DLG_SETUP)) ;

        WinSendDlgItemMsg (hwnd, gamedlgLocal.sColor, BM_SETCHECK,
                           MPFROM2SHORT (TRUE, 0), NULL) ;
        WinSendDlgItemMsg (hwnd, gamedlgLocal.sLevel, BM_SETCHECK,
                           MPFROM2SHORT (TRUE, 0), NULL) ;
        WinSetFocus (HWND_DESKTOP,
                     WinWindowFromID (hwnd, gamedlgLocal.sColor)) ;
        return MRFROMSHORT (1) ;

    case WM_CONTROL:
        switch (SHORT1FROMMP (mp1))
        {
        case IDD_BLACK:
        case IDD_WHITE:
            gamedlgLocal.sColor = SHORT1FROMMP (mp1) ;
            return 0 ;
        case IDD_SIMPLE:
        case IDD_BEGINNER:
        case IDD_INTERMEDIATE:
        case IDD_ADVANCED:
            gamedlgLocal.sLevel = SHORT1FROMMP (mp1) ;
            return 0 ;
        }
        break ;

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case DID_OK:
            pgamedlg->brd    = gamedlgLocal.brd ;
            pgamedlg->sColor = gamedlgLocal.sColor ;
            pgamedlg->sLevel = gamedlgLocal.sLevel ;
            WinDismissDlg (hwnd, TRUE) ;
            return 0 ;
        case DID_CANCEL:
            WinDismissDlg (hwnd, FALSE) ;
            return 0 ;
        case IDD_SETUP:
            setupdlg.brd    = gamedlgLocal.brd ;
            setupdlg.sBottom = (gamedlgLocal.sColor == IDD_BLACK) ? BLACK : WHITE ;
            if (WinDlgBox (HWND_DESKTOP, hwnd, SetupDlgProc,
                           0, IDD_SETUP_DLG, &setupdlg))
                gamedlgLocal.brd = setupdlg.brd ;
            return 0 ;
        }
        break ;
    }
    return WinDefDlgProc (hwnd, msg, mp1, mp2) ;
}

/* ---------- SetupDlgProc ---------------------------------------------- */

MRESULT EXPENTRY SetupDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static CHAR      *pachColor [] = { "[Black]", "[White]" } ;
    static HWND      hwndSetupCntl ;
    static PSETUPDLG psetupdlg ;
    static SETUPDLG  setupdlgLocal ;

    switch (msg)
    {
    case WM_INITDLG:
        hwndSetupCntl = WinWindowFromID (hwnd, IDD_SETUP) ;
        psetupdlg     = PVOIDFROMMP (mp2) ;
        setupdlgLocal = *psetupdlg ;

        WinSetWindowPtr (hwndSetupCntl, 0, &setupdlgLocal) ;

        WinSetDlgItemText (hwnd, IDD_TOP,
                           pachColor [psetupdlg->sBottom == BLACK ? 1 : 0]) ;
        WinSetDlgItemText (hwnd, IDD_BOTTOM,
                           pachColor [psetupdlg->sBottom == BLACK ? 0 : 1]) ;
        return 0 ;

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case DID_OK:
            psetupdlg->brd = setupdlgLocal.brd ;
            WinDismissDlg (hwnd, TRUE) ;
            return 0 ;
        case DID_CANCEL:
            WinDismissDlg (hwnd, FALSE) ;
            return 0 ;
        }
        break ;
    }
    return WinDefDlgProc (hwnd, msg, mp1, mp2) ;
}

/* ---------- AboutDlgProc ---------------------------------------------- */

MRESULT EXPENTRY AboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case DID_OK:
        case DID_CANCEL:
            WinDismissDlg (hwnd, TRUE) ;
            return 0 ;
        }
        break ;
    }
    return WinDefDlgProc (hwnd, msg, mp1, mp2) ;
}
