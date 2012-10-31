#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int Menu::quickMake(const char* p_csvTitles,int intx,int inty,int p_height){

    //Invalid input detection
    if ( intx < 0 || inty < 0 ){return -1;}

    //Set options.
    Menu::options(intx, inty,p_height);

    //Draw menu
    Menu::make(p_csvTitles);

    //Return value
    return Menu::value();
}


int Menu::options(int p_intx, int p_inty,int p_height){

    //Invalid input detection
    if (p_intx < 0 || p_inty < 0){return -1;}

    //Set variables
    intx = p_intx;
    inty = p_inty;
    optionsHeight = p_height;

    //Mark options as set.
    hasOptioned = true;

    //Nothing else to do
    return 0;
}


int Menu::make(const char* p_csvTitles){

    //Error if options not set.
    if(hasOptioned == false){
        return -1;
    }

    //Error if already made.
    if(hasMade == true){
        return -1;
    }
    else{
        hasMade = true;
    }

    //Load scrolling menu if applicable.
    if (optionsHeight > 3){
        return Menu::scrollMake(p_csvTitles);
    }

    //Calculate the titles and etc.
    //Initialized here due to varying size.
    /*
    This causes prolems with certain systems.
    Removed on windows.
    */
    #ifdef _WIN32
    //Error on strings that are too long.
    if ((strlen(p_csvTitles)+1) >= 9001){ return -1; }
    char csvTitlesString[9001];
    #else
    char csvTitlesString[strlen(p_csvTitles)+1];
    #endif

    //No need for strncpy due to the definition of the array based on the size of the string.
    //Maybe do something about this for le winblows?
    strcpy(csvTitlesString,p_csvTitles);

    titleBuffer = strtok(csvTitlesString,",");

    while(titleBuffer != NULL){

        //Save the titles into the array
        titleArray[titleCount] = titleBuffer;
        titleCount++;

        //Calculate the longest word for the width of things.
        if(strlen(titleBuffer) > longestWord ){ longestWord = strlen(titleBuffer); }

        //Quit before an overflow.
        if(titleCount >= 34){ break; }

        titleBuffer = strtok(NULL,",");
    }

    intWidth = longestWord + 5;

    intOptions = titleCount;

    menuHeight = titleCount+2; //This contols the absolute menu height

    intArea = intWidth*menuHeight; //Calculate total area for cleanup program

    menuWindow = newwin(menuHeight, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen
	curs_set(0); //Turn off hte blinking cursor >:U

    mvwprintw(menuWindow, intActive, intWidth-3, "<="); // Print the starting arrow

    while(optionsCounter < titleCount){
        mvwprintw(menuWindow, optionsCounter + 1, 1, titleArray[optionsCounter]);
        wrefresh(menuWindow);
        optionsCounter++;
    }
    wrefresh(menuWindow); //Draw the screen

    while(true){
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

        if (longChar == ' '){ //Here's the code to return the correct number
            intValue = intActive;
            return intActive;
        }
    }
    return -1;
}


int Menu::scrollMake(const char* p_csvTitles){

    //Calculate the titles and etc.
    //Initialized here due to varying size.
    /*
    This causes prolems with certain systems.
    Removed on windows.
    */
    #ifdef _WIN32
    //Error on strings that are too long.
    if ((strlen(p_csvTitles)+1) >= 9001){ return -1; }
    char csvTitlesString[9001];
    #else
    char csvTitlesString[strlen(p_csvTitles)+1];
    #endif

    //No need for strncpy due to the definition of the array based on the size of the string.
    strcpy(csvTitlesString,p_csvTitles);

    titleBuffer = strtok(csvTitlesString,",");

    while(titleBuffer != NULL){

        //Save the titles into the array
        titleArray[titleCount] = titleBuffer;
        titleCount++;

        //Calculate the longest word for the width of things.
        if(strlen(titleBuffer) > longestWord ){ longestWord = strlen(titleBuffer); }

        //Quit before an overflow.
        if(titleCount >= 34){ break; }

        titleBuffer = strtok(NULL,",");
    }

    intWidth = longestWord + 5;

    intOptions = titleCount;

    menuHeight = optionsHeight; //This contols the absolute menu height

    menuWindow = newwin(menuHeight, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen
	curs_set(0); //Turn off hte blinking cursor >:U
	wrefresh(menuWindow);
	intArea = intWidth*menuHeight; //Calculate total area for cleanup program

    while(optionsCounter < (optionsHeight - 2)){
        mvwprintw(menuWindow, optionsCounter + 1, 1, titleArray[optionsCounter]);
        wrefresh(menuWindow);
        optionsCounter++;
    }

    while(true){

        //Clean out the menu.
        /*
        optionsCounter = 1;
        while(optionsCounter < (optionsHeight - 2)){
            mvwprintw(menuWindow,optionsCounter,1," ");
            clearOptionsCounter = 1; //This allows for easy comparison
            while(clearOptionsCounter < longestWord){
                wprintw(menuWindow," ");
                clearOptionsCounter++;
                wrefresh(menuWindow);
            }
            optionsCounter++;
            wrefresh(menuWindow);
        }
        */
        wclear(menuWindow);
        wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
        wrefresh(menuWindow);

        //Draw the titles
        optionsCounter = 1;
        while((optionsCounter) <= (optionsHeight - 2)){
            mvwprintw(menuWindow, optionsCounter, 1, titleArray[(optionsCounter - 1) + offset]);
            optionsCounter++;
            wrefresh(menuWindow);
        }

        //Draw the arrow.
        mvwprintw(menuWindow, intActive, intWidth-3, "<=");

        //Check for keypresses.
        longChar = wgetch(menuWindow);

        //Clear the arrow
        mvwprintw(menuWindow, intActive, intWidth-3, "  ");

        if(longChar == KEY_UP){
            if (intActive > 1){ //Endstop code
                intActive--;
            }
            else if (offset > 0){ //Scroll code
                offset--;
            }
        }

        if(longChar == KEY_DOWN){
            if (intActive < (optionsHeight - 2)){ //Endstop code
                intActive++;
            }
            else if (offset < (titleCount - optionsHeight + 2)){ //Scroll code
                offset++;
            }
        }

        if(longChar == ' '){
            //Store the number for the value calculation.
            intValue = intActive;
            return intActive;
        }

    }

    //We shouldn't be here :o
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

    hasMade = false; //Defines whether or not the screen exists
    menuHeight = 0; //Defines the height of the menu.
    //intx = 0; //Defines X coordinates of the upper left corner of the menu.
    //inty = 0; //Defines Y coordinates of the upper left corner of the menu.
    intOptions = 0; //Defines the number of options in the menu.
    intActive = 1; //Resets cursor position. Remove to activate cursor position memory.
    intWidth = 15; //Sets width of the screen
    intArea = 0; //Area of screen, used in the clearing of it.
    titleCount = 0; //Sets number of titles in the screen
    optionsCounter = 0; //Tracks the number of options we've created.
    longestWord = 0; //Sets the width of the screen based on the longest word.
    longChar = 0; //The keypress when scrolling up and down in menus.

    //OPTIONAL VARIABLE ASSIGNMENTS
    //Comment these to disable the described function
    intLastActive = 1; //Keeps previous cursor position.
    offset = 0; //Keeps current scrolling position in the menu.
}

