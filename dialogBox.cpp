#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "dialogBox.h"
#include "menu.h"

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

    if(hasInitialized == false){

        dialogBoxWindow = newwin(3, width, y, x); //Create the window
        wborder(dialogBoxWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on

        //Init options
        keypad(dialogBoxWindow, TRUE);
        curs_set(0);

        hasInitialized = true;
    }

    //Draw text
    mvwprintw(dialogBoxWindow, 1, 1, p_text);
    wrefresh(dialogBoxWindow);

    //If attention == true; Wait for enter press
    if (attention == true){

        while (keyPress != 32){ //10 is enter, use OR to add more keypresses
            keyPress = wgetch(dialogBoxWindow);
        }
    }

    //Cleans it if you use the function again.
    keyPress = 0;

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
    hasInitialized = false;
}


int DialogBox::makeNumber(int p_number){

    //Create conversion string
    std::string stringConversion;
    std::stringstream stringStreamConverter;

    //Convert int to string
    stringStreamConverter << p_number;
    stringConversion = stringStreamConverter.str();

    //Call make with the string
    //.c_str(); will convert from string to const char*
    DialogBox::make(stringConversion.c_str());

    return 0;
}


int DialogBox::title(const char* p_title){

    titleLength = strlen(p_title);

    //If letterCount is 0, then remove the title.
    if (titleLength < 1){
        wborder(dialogBoxWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner);
        wrefresh(dialogBoxWindow);
        return 0;
    }

    //If the screen is too narrow, abort
    if (titleLength > width){
        return -1;
    }

    //Draw the title at the center top of the screen.
    mvwprintw(dialogBoxWindow, 0, ((width-titleLength)/2), p_title);
    wrefresh(dialogBoxWindow);
    return 0;
}

