#ifndef LANG_H
#define LANG_H

#define LANG_EN    0
#define LANG_ES    1
#define LANG_NL    2
#define LANG_DE    3
#define LANG_FR    4
#define LANG_IT    5
#define LANG_COUNT 6

enum {
    STR_MENU_GAME = 0,
    STR_MENU_NEW,
    STR_MENU_PAUSE,
    STR_MENU_QUIT,
    STR_MENU_EXIT,
    STR_MENU_OPTIONS,
    STR_MENU_COLORS,
    STR_MENU_CLRBKG,
    STR_MENU_CLRBLKSQ,
    STR_MENU_CLRWHTSQ,
    STR_MENU_CLRBLKPC,
    STR_MENU_CLRWHTPC,
    STR_MENU_CLRSTD,
    STR_MENU_LANGUAGE,
    STR_MENU_SAVEONEXIT,
    STR_MENU_FRAME,
    STR_MENU_HELP,
    STR_MENU_ABOUT,
    /* NewGame dialog */
    STR_DLG_START_NEW_GAME,
    STR_DLG_COLOR,
    STR_DLG_LEVEL,
    STR_DLG_BLACK,
    STR_DLG_WHITE,
    STR_DLG_SIMPLE,
    STR_DLG_BEGINNER,
    STR_DLG_INTERMEDIATE,
    STR_DLG_ADVANCED,
    STR_DLG_OK,
    STR_DLG_CANCEL,
    STR_DLG_SETUP,
    STR_COUNT
};

extern int current_lang;
extern const char *lang_strings[LANG_COUNT][STR_COUNT];
#define tr(id) ((char*)lang_strings[current_lang][(id)])

#endif /* LANG_H */
