#include "menu.h"
#include "stdlib.h"
#include "stdio.h"

// stack

// stack push
inline static void __MenuPush(menuCore *core, MenuUnit *__menu_val)
{
    struct __menuChainNode *nd = (struct __menuChainNode *)malloc(sizeof(struct __menuChainNode));
    nd->next = core->__node;
    core->__node = nd;
    core->__node->val = __menu_val;
}
// stack pop
inline static MenuUnit *__MenuPop(menuCore *core)
{
    struct __menuChainNode *nd = core->__node;
    MenuUnit *val = NULL;

    if (nd != NULL)
    {
        val = nd->val;
        core->__node = nd->next;
        free(nd);
    }

    return val;
}

// stack top
inline static MenuUnit *__MenuTop(menuCore *core)
{
    if (core->__node != NULL)
        return core->__node->val;
}

void menuInit(menuCore *core, MenuUnit *m, unsigned int maxDisplayLine)
{
    core->maxDisplayLine = maxDisplayLine;
    core->currentFocusLine = 0;
    core->__node = NULL;
    menuGotoNewPage(core, m);
}

char __MenuStr[64];
void menuShow(menuCore *core)
{
    MenuUnit *m = __MenuTop(core);
    unsigned short lineCnt = 0;
    char *s;
    core->screenClear();

    if (core->currentFocusLine < core->maxDisplayLine)
    {
        while (m->id != __Menu_Id_End)
        {
            if (m->id == __Menu_Id_Variable)
            {
                sprintf(__MenuStr, "%s : %d", m->caption, *(m->val));
                s = __MenuStr;
            }
            else
                s = m->caption;
            if (lineCnt++ == core->currentFocusLine)
                core->printFocus(s);
            else
                core->print(s);
            m++;
            if (lineCnt == core->maxDisplayLine)
                break;
        }
    }
    else
    {
        lineCnt = core->currentFocusLine - core->maxDisplayLine + 1;
        while (lineCnt < core->currentFocusLine)
        {
            if (m[lineCnt].id == __Menu_Id_Variable)
            {
                sprintf(__MenuStr, "%s:%d", m[lineCnt].caption, *(m[lineCnt].val));
                s = __MenuStr;
            }
            else
                s = m[lineCnt].caption;
            core->print(s);
            lineCnt++;
        }
        if (m[core->currentFocusLine].id == __Menu_Id_Variable)
        {
            sprintf(__MenuStr, "%s:%d", m[core->currentFocusLine].caption, *(m[core->currentFocusLine].val));
            s = __MenuStr;
        }
        else
            s = m[lineCnt].caption;
        core->printFocus(s);
    }
}

void menuGotoNewPage(menuCore *core, MenuUnit *m)
{
    __MenuPush(core, m);
    core->currentFocusLine = 0;
    menuShow(core);
}

void menuGoBack(menuCore *core)
{
    __MenuPop(core);
    core->currentFocusLine = 0;
    menuShow(core);
}

void menuUp(menuCore *core)
{
    if (core->currentFocusLine)
    {
        core->currentFocusLine--;
        menuShow(core);
    }
}

void menuDown(menuCore *core)
{
    MenuUnit *m = __MenuTop(core);
    if (m[core->currentFocusLine + 1].caption != NULL)
    {
        core->currentFocusLine++;
        menuShow(core);
    }
}

#define __Menu_LEFT 0
#define __Menu_RIGHT 1
#define __Menu_MID 2
unsigned char static __MenuSpecialUnit(menuCore *core, MenuUnit *m, unsigned char MenuKey)
{
    if (m->id == __Menu_Id_Go_Back)
    {
        menuGoBack(core);
        return 0;
    }

    if (m->id == __Menu_Id_Go_To_Next)
    {
        menuGotoNewPage(core, m->nextMenu);
        return 0;
    }
    if (m->id == __Menu_Id_Variable)
    {
        if (MenuKey == __Menu_LEFT)
            // sprintf(m->caption, "%s: %d", m->varName, --*(m->val));
            --*(m->val);
        else if (MenuKey == __Menu_RIGHT)
            // sprintf(m->caption, "%s: %d", m->varName, ++*(m->val));
            ++*(m->val);
        menuShow(core);
        return 0;
    }

    // else if ()
    // {
    // }
    return 1;
}

void menuLeft(menuCore *core)
{
    MenuUnit *m = __MenuTop(core);

    if (__MenuSpecialUnit(core, m + core->currentFocusLine, __Menu_LEFT))
        if (m[core->currentFocusLine].left != NULL)
            m[core->currentFocusLine].left();
}
void menuRight(menuCore *core)
{
    MenuUnit *m = __MenuTop(core);

    if (__MenuSpecialUnit(core, m + core->currentFocusLine, __Menu_RIGHT))
        if (m[core->currentFocusLine].right != NULL)
            m[core->currentFocusLine].right();
}
void menuMid(menuCore *core)
{
    MenuUnit *m = __MenuTop(core);
    if (__MenuSpecialUnit(core, m + core->currentFocusLine, __Menu_MID))
        if (m[core->currentFocusLine].mid != NULL)
            m[core->currentFocusLine].mid();
}
