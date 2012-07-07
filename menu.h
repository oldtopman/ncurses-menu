#include <string>
#include <ncurses.h>
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu{
    private:
    int menuChoice, menuHeight, intEscape, intx, inty, intOptions, intCounter, intControl, intActive, intLastActive, intWidth;
    long longChar;
    char charCorner, charSide, charTop;
    WINDOW* menuWindow;

    public:
    int make(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5,int intEscape,int intx,int inty,int intOptions);
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
    longChar(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),
    menuWindow(newwin(menuHeight, intWidth, inty, intx)),
    {}
};


#endif // MENU_H_INCLUDED