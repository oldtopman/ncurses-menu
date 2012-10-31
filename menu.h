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
    bool hasMade, hasOptioned;
    int menuHeight, intx, inty, intOptions, intActive, intLastActive, intWidth, intArea, intValue, titleCount, optionsCounter, clearOptionsCounter, optionsHeight, offset;
    unsigned int longestWord;
    long longChar;
    char charCorner, charSide, charTop;

    char * titleArray[35];
    WINDOW* menuWindow;
    char * titleBuffer;

    int scrollMake(const char* p_csvTitles);

    public:
    int quickMake(const char* p_csvTitles,int intx,int inty,int p_height);
    int options(int p_intx, int p_inty, int p_height);
    int make(const char* p_csvTitles);
    //scrollMake goes here, a private function.
    int value();
    void clean();


    Menu()
    :hasMade(false),
    hasOptioned(false),
    menuHeight(0),
    intx(0),
    inty(0),
    intOptions(0),
    intActive(1),
    intLastActive(1),
    intWidth(15),
    intArea(0),
    intValue(0),
    titleCount(0),
    optionsCounter(0),
    clearOptionsCounter(0),
    optionsHeight(0),
    offset(0),
    longestWord(0),
    longChar(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),
    menuWindow(newwin(menuHeight, intWidth, inty, intx)),
    titleBuffer()
    {}
};


#endif // MENU_H_INCLUDED
