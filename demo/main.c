#include "stdlib.h"
#include "menu.h"
#include "stdio.h"
#include "conio.h"
MenuUnit fooMenu[] = {
    {"foo menu name 1", NULL, NULL, NULL},
    {"foo menu name 2", NULL, NULL, NULL},
    {"foo menu name 3", NULL, NULL, NULL},
    {"foo menu name 4", NULL, NULL, NULL},
    {"foo menu name 5", NULL, NULL, NULL},
    MenuGoToNextUnit(fooMenu, "wyWy"),
    MenuGoBackUnit,
    MenuEnd};

void pcLeft(void)
{
    system("cls");
    printf("you pressed the left key!");
}
void pcRight(void)
{
    system("cls");
    printf("you pressed the Right key!");
}

MenuUnit mainMenu[] = {
    {.caption = "aaa", .left = pcLeft, .right = pcRight, .mid = NULL},
    MenuGoToNextUnit(fooMenu, "wyWy"),
    {.caption = "ccc", .left = NULL, .mid = NULL, .right = NULL},
    MenuEnd};

void pcPrintCaption(char *s)
{
    printf(" %s\n", s);
}
void pcPrintFocus(char *s)
{
    printf(">%s\n", s);
}
void pcClear(void)
{
    system("cls");
}

int main(int argc, char const *argv[])
{
    menuCore menu;
    menu.print = pcPrintCaption;
    menu.printFocus = pcPrintFocus;
    menu.screenClear = pcClear;

    menuInit(&menu, mainMenu, 5);

    int ch;
    while ((ch = _getch()) != 0x1B) /* Press ESC to quit... */
    {
        ch = _getch();
        switch (ch)
        {
        case 72:
            menuUp(&menu);
            break;
        case 80:
            menuDown(&menu);
            break;
        case 75:
            menuLeft(&menu);
            break;
        case 77:
            menuRight(&menu);
            break;
        default:
            break;
        }
    }

    return 0;
}
