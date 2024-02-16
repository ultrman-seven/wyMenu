#ifndef __WY_MENU_HPP__
#define __WY_MENU_HPP__

#include "stdint.h"
#include "stack.hpp"
namespace menu
{
    typedef struct
    {
        union
        {
            const char *caption_c;
            char *caption_t;
        };
        void (*mid)(void);
        void (*left)(void);
        void (*right)(void);
    } MenuTypedef;

    class Menu
    {
    private:
        void (*screenCleanFunction)(void) = nullptr;
        void (*screenPrintFunction)(char *) = nullptr;
        void (*screenPrintFocusFunction)(char *) = nullptr;
        uint8_t currentChoose = 0;
        bool checkUnitFunction(MenuTypedef *m);
        char strTmp[64];
        union
        {
            float valBuf_f[10];
            int32_t valBuf_i32[10];
        };
        wyADT::Stack<MenuTypedef *> menuStack;

    public:
        Menu() = default;
        // Menu(void (*clean)(void), void (*print)(char *), genO::ChooseLine *c);
        Menu(void (*clean)(void), void (*print)(char *), void (*printFocus)(char *));

        void up(void);
        void down(void);
        void left(void);
        void right(void);
        void mid(void);
        void show(void);

        void operator=(MenuTypedef *unit);
    };

#define MENU_Same_Option_Unit(__Menu_Cap, __Menu_Function)            \
    {                                                                 \
        __Menu_Cap, __Menu_Function, __Menu_Function, __Menu_Function \
    }

#define MENU_END                           \
    {                                      \
        nullptr, nullptr, nullptr, nullptr \
    }

#define MENU_Go_Back                                                       \
    {                                                                      \
        "go back", (void (*)(void))1, (void (*)(void))1, (void (*)(void))1 \
    }

#define Menu_Goto_Next(__Menu_Cap, __Menu_Unit)                                                 \
    {                                                                                           \
        __Menu_Cap, (void (*)(void))2, (void (*)(void))2, (void (*)(void))(uint32_t)__Menu_Unit \
    }
} // namespace menu


#endif /* __WY_MENU_HPP__ */
