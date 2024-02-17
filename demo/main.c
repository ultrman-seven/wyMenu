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
    MenuGoToNextUnit(fooMenu, "enter yourself"),
    MenuGoBackUnit,
    MenuEnd};

void pcLeft(void)
{
    system("cls");
    printf("you pressed the left key!\n");
    printf("up or down to back to the menu");
}
void pcRight(void)
{
    system("cls");
    printf("you pressed the Right key!\n");
    printf("up or down to back to the menu");
}
void pcMid(void)
{
    system("cls");
    printf("you pressed the Enter key!\n");
    printf("up or down to back to the menu");
}

int a = 100;
MenuUnit mainMenu[] = {
    {.caption = "aaa", .left = pcLeft, .right = pcRight, .mid = pcMid},
    MenuGoToNextUnit(fooMenu, "just a new menu"),
    {.caption = "ccc", .left = NULL, .mid = NULL, .right = NULL},
    {.caption = "value of 'a'", .id = __Menu_Id_Variable, .val = &a},
    MenuEnd};

void pcPrintCaption(char *s)
{
    printf("  %s\n", s);
}
void pcPrintFocus(char *s)
{
    printf(">>%s\n", s);
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
        if (ch == 13) // enter
        {
            menuMid(&menu);
            continue;
        }
        ch = _getch();
        switch (ch)
        {
        case 72: // arrow Up
            menuUp(&menu);
            break;
        case 80: // arrow Down
            menuDown(&menu);
            break;
        case 75: // arrow Left
            menuLeft(&menu);
            break;
        case 77: // arrow Right
            menuRight(&menu);
            break;
        default:
            break;
        }
    }

    return 0;
}
