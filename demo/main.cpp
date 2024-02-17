#include "menu.hpp"
#include "stdio.h"
#include "conio.h"

menu::Menu<4>::MenuUnit mainMenu[] = {
    {"foo", {nullptr, nullptr, nullptr, nullptr}},
    {"bar", {nullptr, nullptr, nullptr, nullptr}},
    MENU_END};

int main(int argc, char const *argv[])
{
    menu::Menu<4> m([]() { system("cls"); },
                    [](char *s) { printf(" %s\n", s); },
                    [](char *s) { printf(">%s\n", s); },
                    5);

    m.loadMainMenu(mainMenu);

        int ch;
    while ((ch = _getch()) != 0x1B) /* Press ESC to quit... */
    {
        ch = _getch();
        switch (ch)
        {
        case 72:
            m.up();
            break;
        case 80:
            m.down();
            break;
        case 75:
            m.keys(0);
            break;
        case 77:
            m.keys(1);
            break;
        default:
            break;
        }
    }
    return 0;
}
