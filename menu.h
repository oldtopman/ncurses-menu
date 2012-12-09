/*
    ncurses-menu. A simpler, faster ncurses menu library.
    Copyright (C) 2012  oldtopman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program in the file labeled "LICENSE.txt".
    If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <string>
#include "dialogBox.h"
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu{
    private:
    bool hasMade, hasOptioned, hasToolTips;
    int menuHeight, intx, inty, intOptions, intActive, intLastActive, intWidth, intArea, intValue, titleCount, toolTipCount, optionsCounter, clearOptionsCounter, optionsHeight, offset;
    unsigned int longestWord;
    long longChar;
    char charCorner, charSide, charTop;

    char * titleArray[35];
    std::string toolTipArrayString[35];
    WINDOW* menuWindow;
    char * titleBuffer;
    char * toolTipBuffer;
    DialogBox toolTipDbox;

    int scrollMake(const char* p_csvTitles);

    public:
    int quickMake(const char* p_csvTitles,const char * p_csvToolTip,int intx,int inty,int p_height);
    int quickMake(const char* p_csvTitles,int intx,int inty,int p_height);
    int options(int p_intx, int p_inty, int p_height);
    int make(const char * p_csvTitles, const char * p_csvToolTip);
    int make(const char* p_csvTitles);
    int toolTip(const char* p_csvToolTip);
    //scrollMake goes here, a private function.
    int value();
    void clean();


    Menu()
    :hasMade(false),
    hasOptioned(false),
    hasToolTips(false),
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
    toolTipCount(0),
    optionsCounter(0),
    clearOptionsCounter(0),
    optionsHeight(0),
    offset(0),
    longestWord(0),
    longChar(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),
    titleArray(),
    toolTipArrayString(),
    menuWindow(newwin(menuHeight, intWidth, inty, intx)),
    titleBuffer(),
    toolTipBuffer(),
    toolTipDbox()
    {
        toolTipDbox.options(0,10,20,0);
    }
};


#endif // MENU_H_INCLUDED
