/*

This is a menu-generating tool designedto be used with ncurses.
The arguments to be passed to make are:
Menu.make("title1","title2","title3","title4","title5",intWidth, intx, inty, intOptions);
intWidth controls the width of the screen
intx is the location of the upper left corner on the X axis.
inty is the location of the upper left corner on the Y axis.
intOptions controls the number of menu options.

RETURNS:
Menu option selected, or -1 on error



*/

#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int Menu::quickMake(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5,int intWidth,int intx,int inty,int intOptions){

    //Invalid input detection
    if (intOptions < 1 || intx < 0 || inty < 0 || intWidth < 5){return -1;}

    //Set options.
    Menu::options(intOptions, intx, inty, intWidth);

    //Draw menu
    Menu::make(title1,title2,title3,title4,title5);

    //Return value
    return Menu::value();
}


int Menu::options(int p_intOptions, int p_intx, int p_inty, int p_intWidth){

    //Invalid input detection
    if (p_intOptions < 1 || p_intx < 0 || p_inty < 0 || p_intWidth < 5){return -1;}

    //Set variables
    intOptions = p_intOptions;
    intx = p_intx;
    inty = p_inty;
    intWidth = p_intWidth;

    //Nothing else to do
    return 0;
}


int Menu::make(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5){

    menuHeight = intOptions+2; //This contols the absolute menu height, pending some adjustments

    menuWindow = newwin(menuHeight, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen
	curs_set(0);

    mvwprintw(menuWindow, intActive, intWidth-3, "<="); // Print the starting arrow

    intArea = intWidth*menuHeight; //Calculate total area for cleanup program

    //Print out the titles
    if (intOptions >= 1){
        mvwprintw(menuWindow, intCounter, 1, title1);
        intCounter++;
    }

    if (intOptions >= 2){
        mvwprintw(menuWindow, intCounter, 1, title2);
        intCounter++;
    }

    if (intOptions >= 3){
        mvwprintw(menuWindow, intCounter, 1, title3);
        intCounter++;
    }

    if (intOptions >= 4){
        mvwprintw(menuWindow, intCounter, 1, title4);
        intCounter++;
    }

    if (intOptions >= 5){
        mvwprintw(menuWindow, intCounter, 1, title5);
        intCounter++;
    }

    wrefresh(menuWindow); //Draw the screen


    while(intControl != 1){
        longChar = wgetch(menuWindow); //Get the keypress

        if (longChar == KEY_UP){
            intLastActive = intActive; //Preserve last location for clearing it
            if (intActive > 1){ //Endstop code
                intActive--;
            }
        }

        if (longChar == KEY_DOWN){
            intLastActive = intActive;
            if (intActive < intOptions){ //Endstop code
                intActive++;
            }
        }

        mvwprintw(menuWindow, intLastActive, intWidth-3, "  "); //Clear out the old cursor
        mvwprintw(menuWindow, intActive, intWidth-3, "<="); //Draw and refresh the cursor
        wrefresh(menuWindow);

        if (longChar == 10){ //Here's the code to return the correct number
            intValue = intActive;
            return intActive;
        }
    }

    return -1;


}


int Menu::value(){
    return intValue;
}


void Menu::clean(){
    box(menuWindow, ' ', ' ');
    wborder(menuWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    mvwprintw(menuWindow, 0, 0, " ");
    while (intArea > 0) {
        wprintw(menuWindow, " ");
        intArea--;
    }
    wrefresh(menuWindow);
    delwin(menuWindow);

    intCounter = 1; //Lets a screen be made multiple times.
    intActive = 1; //Resets cursor position. Remove to activate cursor position memory.
}

/* STILL IN DEVELOPMENT, USE AT YOUR OWN RISK!

int Menu::hide(std::string cstringFileNameOption){
    cstringFileName = cstringFileNameOption;
    menuFile = fopen(cstringFileName.c_str(), "w"); //Open the file
    putwin(menuWindow, menuFile); //write the screen to the file
    fflush(menuFile);
    fclose(menuFile);

    box(menuWindow, ' ', ' '); //Clear where the screen was
    wborder(menuWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(menuWindow);
}


void Menu::restore(){
    menuFile = fopen(cstringFileName.c_str(), "r");
    getwin(menuFile, menuWindow);
    fclose(menuFile);
}
*/
