#ifndef ADC9D8F9_C29B_4623_8407_8DE33F28F7F6
#define ADC9D8F9_C29B_4623_8407_8DE33F28F7F6

typedef struct __MENU_UNIT_STRUCT MenuUnit;
struct __MENU_UNIT_STRUCT
{
    char *caption;
    union
    {
        void (*left)(void);
        unsigned int id;
    };
    union
    {
        void (*mid)(void);
        MenuUnit *nextMenu;
        int *val;
    };
    union
    {
        void (*right)(void);
        char *varName;
    };
};

struct __menuChainNode
{
    MenuUnit *val;
    struct __menuChainNode *next;
};

typedef struct
{
    unsigned int maxDisplayLine;
    unsigned int currentFocusLine;
    struct __menuChainNode *__node;
    void (*print)(char *);
    void (*printFocus)(char *);
    void (*screenClear)(void);
} menuCore;

#define __Menu_Variable_Max 10
// extern MenuUnit menuVariablePage[__Menu_Variable_Max];

void menuInit(menuCore *core, MenuUnit *m, unsigned int maxDisplayLine);

void menuShow(menuCore *core);
void menuGotoNewPage(menuCore *core, MenuUnit *m);
void menuGoBack(menuCore *core);

void menuUp(menuCore *core);
void menuDown(menuCore *core);

void menuLeft(menuCore *core);
void menuRight(menuCore *core);

#define __Menu_Id_Go_Back 1
#define __Menu_Id_Go_To_Next 2
#define __Menu_Id_Variable 3
#define __Menu_Id_End 4

#define MenuGoBackUnit                           \
    {                                            \
        "go back", __Menu_Id_Go_Back, NULL, NULL \
    }

#define MenuGoToNextUnit(_menuUnit, _menuName)           \
    {                                                    \
        _menuName, __Menu_Id_Go_To_Next, _menuUnit, NULL \
    }

// #define MenuVariable(varAddress) {}

#define MenuEnd                                \
    {                                          \
        NULL, __Menu_Id_End, NULL, NULL \
    }

#define MenuSameOptionUnit(_menuName, _menuCallback)           \
    {                                                          \
        _menuName, _menuCallback, _menuCallback, _menuCallback \
    }

#define MenuNormalUnit(_menuName, _menuCallback1, _menuCallback2, _menuCallback3) \
    {                                                                             \
        _menuName, _menuCallback1, _menuCallback2, _menuCallback3                 \
    }
#endif /* ADC9D8F9_C29B_4623_8407_8DE33F28F7F6 */
