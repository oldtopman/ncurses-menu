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

}


int DialogBox::make(const char* p_text){

}


void DialogBox::update(){

    //Update window, bringing it to front.
    wrefresh(dialogBoxWindow);
}


void DialogBox::clean(){

}


