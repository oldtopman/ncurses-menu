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
    bool hasOptioned;
    bool hasToolTips;
    bool rememberPosition;
    int intx, inty;
    int intActive;
    int intValue;
    int optionsHeight;
    char charCorner, charSide, charTop;

    std::string titleArrayString[35];
    std::string toolTipArrayString[35];
    WINDOW* menuWindow;
    DialogBox toolTipDbox;

    int scrollMake(const char* p_csvTitles);

    public:
    Menu(const Menu&) = delete; // non-copyable
    Menu& operator=(const Menu&) = delete; // non-copy-assignable

    int remember(bool p_rememberPosition);
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
    :hasOptioned(false),
    hasToolTips(false),
    rememberPosition(false), //Default adjustment here.
    intx(0),
    inty(0),
    intActive(1),
    intValue(0),
    optionsHeight(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),
    titleArrayString(),
    toolTipArrayString(),
    menuWindow(),
    toolTipDbox()
    {
        toolTipDbox.options(0,10,20,0);
    }

    ~Menu(){
    }
};


#endif // MENU_H_INCLUDED
