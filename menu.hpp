#ifndef __WY_MENU_HPP__
#define __WY_MENU_HPP__

#include "stdint.h"
#include "stack"
#include "array"

namespace menu
{
    template <unsigned int funNum>
    class Menu
    {
    public:
        typedef struct
        {
            union
            {
                const char *caption_c;
                char *caption_t;
            };
            std::array<void (*)(void), funNum> callbacks;
        } MenuUnit;

    private:
        void (*clean)(void) = nullptr;
        void (*print)(char *) = nullptr;
        void (*printFocus)(char *) = nullptr;
        // uint8_t currentChoose = 0;
        unsigned int maxDisplayLine;
        unsigned int currentFocusLine;

        bool checkUnitFunction(MenuUnit *m);
        char strTmp[64];
        union
        {
            float valBuf_f[10];
            int32_t valBuf_i32[10];
        };
        std::stack<MenuUnit *> menuStack;

    public:
        Menu() = default;
        Menu(void (*_clean)(void), void (*_print)(char *),
             void (*_printFocus)(char *), unsigned int displayLine = 4)
            : clean(_clean), print(_print), printFocus(_printFocus),
              maxDisplayLine(displayLine), currentFocusLine(0) {}

        void up(void)
        {
            if (this->currentFocusLine)
            {
                this->currentFocusLine--;
                this->show();
            }
        }
        void down(void)
        {
            if (this->menuStack.top()[this->currentFocusLine + 1].caption_c != nullptr)
            {
                this->currentFocusLine++;
                this->show();
            }
        }

        void keys(unsigned int n)
        {
            auto f = this->menuStack.top()[this->currentFocusLine].callbacks[n];
            if (f != nullptr)
                f();
        }

        void show(void)
        {
            MenuUnit *m = this->menuStack.top();
            unsigned short lineCnt = 0;
            this->clean();

            if (this->currentFocusLine < this->maxDisplayLine)
            {
                while (m->caption_t != nullptr)
                {
                    if (lineCnt++ == this->currentFocusLine)
                        this->printFocus(m->caption_t);
                    else
                        this->print(m->caption_t);
                    m++;
                    if (lineCnt == this->maxDisplayLine)
                        break;
                }
            }
            else
            {
                lineCnt = this->currentFocusLine - this->maxDisplayLine + 1;
                while (lineCnt < this->currentFocusLine)
                    this->print(m[lineCnt++].caption_t);
                this->printFocus(m[this->currentFocusLine].caption_t);
            }
        }

        void loadMainMenu(MenuUnit *unit)
        {
            this->menuStack.push(unit);
            this->show();
        }
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
