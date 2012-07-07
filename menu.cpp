/*

This is a menu-generating tool designedto be used with ncurses.
The arguments to be passed to make are:
Menu.make("title1","title2","title3","title4","title5",intEscape, intx, inty, intOptions);
If intEscape is 0, then you have to choose an option.
If intEscape is more than 0, you will be able to close the menu taking no action.
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

int Menu::make(const char* title1, const char* title2, const char* title3, const char* title4, const char* title5,int intEscape,int intx,int inty,int intOptions){

    if (intOptions <= 0){
        return -1; //Return an error if invalid number of options selected
    }

    menuHeight = intOptions+2; //This contols the absolute menu height, pending some adjustments

    menuWindow = newwin(menuHeight, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen

    mvwprintw(menuWindow, inty+intActive, intx+intWidth-3, "<="); // Print the starting arrow

    //Print out the titles
    if (intOptions >= 1){
        mvwprintw(menuWindow, inty+intCounter, intx+1, title1);
        intCounter++;
    }

    if (intOptions >= 2){
        mvwprintw(menuWindow, inty+intCounter, intx+1, title2);
        intCounter++;
    }

    if (intOptions >= 3){
        mvwprintw(menuWindow, inty+intCounter, intx+1, title3);
        intCounter++;
    }

    if (intOptions >= 4){
        mvwprintw(menuWindow, inty+intCounter, intx+1, title4);
        intCounter++;
    }

    if (intOptions >= 5){
        mvwprintw(menuWindow, inty+intCounter, intx+1, title5);
        intCounter++;
    }


    wrefresh(menuWindow); //Draw the screen

    while(intControl != 1){
        longChar = wgetch(menuWindow); //Get the keypress

        if (intEscape == 1 && longChar == 27){ //If intEscape is set, add escape option with escape key
            intControl = 1;
        }

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

        mvwprintw(menuWindow, inty+intLastActive, intx+intWidth-3, "  "); //Clear out the old cursor
        mvwprintw(menuWindow, inty+intActive, intx+intWidth-3, "<="); //Draw and refresh the cursor
        wrefresh(menuWindow);

        if (longChar == 10){ //Here's the code to return the correct number
            return intActive;
        }
    }

    while(true){}

    return -1;
}


void Menu::clean(){
    box(menuWindow, ' ', ' ');
    wborder(menuWindow, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(menuWindow);
    delwin(menuWindow);
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
