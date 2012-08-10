/*
Please note that all of the variables used in quickMake are shadowed.
I was inexperienced and had no idea.
They are mostly used in the other functions, so quickMenu will no longer be updated.
*/

#include <string>
#include <ncurses.h>
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu{
    private:
    int menuChoice, menuHeight, intEscape, intx, inty, intOptions, intCounter, intControl, intActive, intLastActive, intWidth, intArea, intValue;
    long longChar;
    char charCorner, charSide, charTop;
    WINDOW* menuWindow;

    public:
    int quickMake(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5,int intWidth,int intx,int inty,int intOptions);
    int options(int p_intOptions, int p_intx, int p_inty, int p_intWidth);
    int make(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5);
    int value();
    void clean();

    Menu()
    :menuChoice(0),
    menuHeight(0),
    intEscape(0),
    intx(0),
    inty(0),
    intOptions(0),
    intCounter(1),
    intControl(0),
    intActive(1),
    intLastActive(1),
    intWidth(15),
    intArea(0),
    intValue(0),
    longChar(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),
    menuWindow(newwin(menuHeight, intWidth, inty, intx))
    {}
};


#endif // MENU_H_INCLUDED
