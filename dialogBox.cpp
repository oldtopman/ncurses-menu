#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dialogBox.h"
#include "menu.h"

/*
    int quickMake(const char* p_text,int p_x,int p_y,int p_width,bool p_attention);
    int options(int p_x,int p_y,int p_width,bool p_attention);
    int make(const char* p_text);
    void clean();
*/

int DialogBox::quickMake(const char* p_text,int p_x,int p_y,int p_width,bool p_attention){

    //Error checking
    if (p_x < 0 || p_y < 0 || p_width < 2){ return -1; }

    //Set options
    DialogBox::options(p_x, p_y, p_width, p_attention);

    //Draw screen
    DialogBox::make(p_text);

    return 0;
}


int DialogBox::options(int p_x,int p_y,int p_width,bool p_attention){

    //Check for invalid inputs
    if (p_x < 0 || p_y < 0 || p_width < 2){ return -1; }

    //Set values
    x = p_x;
    y = p_y;
    width = p_width;
    attention = p_attention;

    return 0;
}


int DialogBox::make(const char* p_text){

    dialogBoxWindow = newwin(3, width, y, x); //Create the window
    wborder(dialogBoxWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on

    //Init options
    keypad(dialogBoxWindow, TRUE);
	curs_set(0);

    //Draw text
    mvwprintw(dialogBoxWindow, 1, 1, p_text);
    wrefresh(dialogBoxWindow);

    //If attention == true; Wait for enter press
    if (attention == true){

        while (keyPress != 10){ //10 is enter, use OR to add more keypresses
            keyPress = wgetch(dialogBoxWindow);
        }
    }

    //If attention == false, exit.
    return 0;
}


void DialogBox::update(){

    //Update window, bringing it to front.
    wrefresh(dialogBoxWindow);
}


void DialogBox::clean(){

    //Code taken from menu.h
    //area needs to be set, so it's set manually.
    area = (width*3);


    box(dialogBoxWindow, ' ', ' ');
    wborder(dialogBoxWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    mvwprintw(dialogBoxWindow, 0, 0, " ");
    while (area > 0) {
        wprintw(dialogBoxWindow, " ");
        area--;
    }
    wrefresh(dialogBoxWindow);
    delwin(dialogBoxWindow);
}


