#ifndef __WY_ADT_STACK_HPP_
#define __WY_ADT_STACK_HPP_

#ifdef __WyADT_UseMalloc
#include "stdlib.h"
#define __WyADT_StackGetMem(_WyADT_Typename) (_WyADT_Typename *)malloc(sizeof(_WyADT_Typename))
#define __WyADT_StackGetArrayMem(_WyADT_Typename, _WyADT_Len) (_WyADT_Typename *)malloc(sizeof(_WyADT_Typename) * _WyADT_Len)
#define __WyADT_StackDeleteMem(_WyADT_valptr) free(_WyADT_valptr)
#define __WyADT_StackDeleteArrayMem(_WyADT_valptr) free(_WyADT_valptr)
#elif defined __WyADT_UseNew
#define __WyADT_StackGetMem(_WyADT_Typename) new _WyADT_Typename
#define __WyADT_StackGetArrayMem(_WyADT_Typename, _WyADT_Len) new _WyADT_Typename[_WyADT_Len]
#define __WyADT_StackDeleteMem(_WyADT_valptr) delete _WyADT_valptr
#define __WyADT_StackDeleteArrayMem(_WyADT_valptr) delete[] _WyADT_valptr
#else
#define __WyADT_StackGetMem(_WyADT_Typename) static_cast<_WyADT_Typename*>(operator new(sizeof(_WyADT_Typename)))
#define __WyADT_StackGetArrayMem(_WyADT_Typename, _WyADT_Len) static_cast<_WyADT_Typename*>(operator new(sizeof(_WyADT_Typename) * _WyADT_Len))
#define __WyADT_StackDeleteMem(_WyADT_valptr) operator delete(_WyADT_valptr)
#define __WyADT_StackDeleteArrayMem(_WyADT_valptr) operator delete(_WyADT_valptr)
#endif

namespace wyADT
{
    template <typename T>
    class Stack
    {
    private:
        struct stackChainNode
        {
            T val;
            stackChainNode *next;
        } *head;
        T emptyValue; // https://chat.openai.com/share/7bb1fb8d-b657-481d-b536-b9f91258001a

    public:
        Stack();
        Stack(const T &errVal);
        ~Stack();
        void push(const T &val);
        T pop();
        T top();
        Stack<T> &operator>>(T &n);
        Stack<T> &operator<<(const T &v);
        bool isEmpty(void);
        void clean(void);
    };

    template <typename T>
    class StackArray
    {
    private:
        T *arr;
        unsigned int cnt;
        unsigned int maxLen;
        T emptyValue;

    public:
        StackArray(unsigned int len);
        StackArray(unsigned int len, const T &errVal);
        ~StackArray();

        void push(T &val);
        T pop();
        T top();
        StackArray<T> &operator>>(T &n);
        StackArray<T> &operator<<(const T &v);
        bool isEmpty(void);
        void clean(void);
    };

    template <typename T>
    StackArray<T>::StackArray(unsigned int len)
    {
        this->arr = __WyADT_StackGetArrayMem(T, len);
        this->cnt = 0;
        this->maxLen = len;
    }
    template <typename T>
    StackArray<T>::StackArray(unsigned int len, const T &errVal)
    {
        this->arr = __WyADT_StackGetArrayMem(T, len);
        this->cnt = 0;
        this->maxLen = len;
        this->emptyValue = errVal;
    }

    template <typename T>
    StackArray<T>::~StackArray()
    {
        __WyADT_StackDeleteArrayMem(this->arr);
    }

    template <typename T>
    T StackArray<T>::pop()
    {
        if (this->cnt)
            return this->arr[--this->cnt];
        return this->emptyValue;
    }

    template <typename T>
    void StackArray<T>::push(T &val)
    {
        if (this->cnt < this->maxLen)
            this->arr[this->cnt++] = val;
    }

    template <typename T>
    void StackArray<T>::clean(void)
    {
        this->cnt = 0;
    }

    template <typename T>
    StackArray<T> &StackArray<T>::operator<<(const T &val)
    {
        if (this->cnt < this->maxLen)
            this->arr[this->cnt++] = val;
        return *this;
    }

    template <typename T>
    StackArray<T> &StackArray<T>::operator>>(T &val)
    {
        val = (this->cnt) ? this->arr[--this->cnt] : this->emptyValue;
        return *this;
    }

    template <typename T>
    bool StackArray<T>::isEmpty(void)
    {
        return !(this->cnt);
    }

    template <typename T>
    T StackArray<T>::top(void)
    {
        return this->arr[this->cnt];
    }

    template <typename T>
    Stack<T>::Stack()
    {
        this->head = nullptr;
    }

    template <typename T>
    Stack<T>::Stack(const T &val)
    {
        // this->head = __WyADT_StackGetMem(stackChainNode);
        // this->head->next = nullptr;
        // this->head->val = val;
        this->emptyValue = val;
        this->head = nullptr;
    }

    template <typename T>
    void Stack<T>::clean(void)
    {
        stackChainNode *n;
        while (this->head != nullptr)
        {
            n = this->head->next;
            // free(this->head);
            __WyADT_StackDeleteMem(this->head);
            this->head = n;
        }
    }

    template <typename T>
    Stack<T>::~Stack()
    {
        this->clean();
    }

    template <typename T>
    void Stack<T>::push(const T &val)
    {
        if (this->head == nullptr)
        {
            // this->head = (stackChainNode *)malloc(sizeof(stackChainNode));
            this->head = __WyADT_StackGetMem(stackChainNode);
            this->head->next = nullptr;
            this->head->val = val;
        }
        else
        {
            stackChainNode *n = this->head;
            // this->head = (stackChainNode *)malloc(sizeof(stackChainNode));
            this->head = __WyADT_StackGetMem(stackChainNode);
            this->head->next = n;
            this->head->val = val;
        }
    }

    template <typename T>
    T Stack<T>::pop()
    {
        if (this->head != nullptr)
        {
            T r;
            stackChainNode *n = this->head;
            r = this->head->val;
            this->head = this->head->next;
            // free(n);
            __WyADT_StackDeleteMem(n);
            return r;
        }
        return this->emptyValue;
    }

    template <typename T>
    bool Stack<T>::isEmpty(void)
    {
        return this->head == nullptr;
    }

    template <typename T>
    T Stack<T>::top()
    {
        if (this->head != nullptr)
            return this->head->val;
        return this->emptyValue;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator>>(T &n)
    {
        n = this->pop();
        return *this;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator<<(const T &v)
    {
        this->push(v);
        return *this;
    }
} // namespace wyADT

#endif //__WY_ADT_STACK_HPP_
