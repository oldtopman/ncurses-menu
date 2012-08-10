/*
Please note that all of the variables used in quickMake are shadowed.
I was inexperienced and had no idea.
They are mostly used in the other functions, so quickMenu will no longer be updated.
*/

#include <string>
#include <ncurses.h>
#ifndef DIALOGBOX_H_INCLUDED
#define DIALOGBOX_H_INCLUDED

class DialogBox{
    private:
    bool attention;
    int x,y,width;
    long keyPress;
    char charCorner, charSide, charTop;

    WINDOW* dialogBoxWindow;

    public:
    int quickMake(const char* p_text,int p_x,int p_y,int p_width,bool p_attention);
    int options(int p_x,int p_y,int p_width,bool p_attention);
    int make(const char* p_text);
    void update();
    void clean();

    DialogBox()
    :attention(false),
    x(0),
    y(0),
    width(0),
    keyPress(0),
    charCorner('+'),
    charSide('|'),
    charTop('-'),

    dialogBoxWindow()
    {}
};


#endif // DIALOGBOX_H_INCLUDED
