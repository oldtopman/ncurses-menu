/*
    ncurses-menu. A simpler, faster ncurses menu library.
    Copyright (C) 2012-2015  oldtopman

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

#include <ncurses.h>
#ifndef DIALOGBOX_H_INCLUDED
#define DIALOGBOX_H_INCLUDED

class DialogBox{
    private:
    bool hasInitialized;
    bool attention;
    bool justCleaned;
    int x,y;
    int width,originalWidth;
    char charCorner, charSide, charTop;

    WINDOW* dialogBoxWindow;

    public:
    int quickMake(const char* p_text,int p_x,int p_y,int p_width,bool p_attention);
    int options(int p_x,int p_y,int p_width,bool p_attention);
    int make(const char* p_text);
    int make(int p_number);
    int title(const char* p_title);
    void update();
    void clean();

    DialogBox()
    :hasInitialized(false),
    attention(false),
    justCleaned(true),
    x(0),
    y(0),
    width(0),
    originalWidth(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),

    dialogBoxWindow()
    {}
};


#endif // DIALOGBOX_H_INCLUDED
