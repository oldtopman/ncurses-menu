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
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include "dialogBox.h"
#include "menu.h"


int Menu::quickMake(const char* p_csvTitles,const char * p_csvToolTip,int p_intx,int p_inty,int p_height){

    //Open up the error checking.
    int error;

    //Pass the options.
    error = Menu::toolTip(p_csvToolTip);
    if(error < 0){ return error; }

    return Menu::quickMake(p_csvTitles,p_intx,p_inty,p_height);
}


int Menu::quickMake(const char* p_csvTitles,int p_intx,int p_inty,int p_height){

    //Invalid input detection
    if ( p_intx < 0 || p_inty < 0 ){return -1;}

    //Set options.
    Menu::options(p_intx, p_inty,p_height);

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


int Menu::make(const char * p_csvTitles, const char * p_csvToolTip){

    //Error handling.
    int error;

    //Pass along the options.
    error = Menu::toolTip(p_csvToolTip);
    if(error < 0){ return error; }
    else{ return Menu::make(p_csvTitles); }
}


int Menu::make(const char* p_csvTitles){

    //Declare local variables.
    int counter = 0;
    int intOptions = 0;
    int intLastActive = 0;
    int intWidth = 0;
    int titleCount = 0;
    int longestWord = 0;
    long longChar = 0;
    char * titleBuffer;
    //End declaration of local variables.

    //Error if options not set.
    if(hasOptioned == false){
        return -1;
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
        titleArrayString[titleCount] = titleBuffer;
        titleCount++;

        //Prevent unsigned-signed comparison.
        int titleBufferLength = strlen(titleBuffer);

        //Calculate the longest word for the width of things.
        if(titleBufferLength > longestWord ){ longestWord = titleBufferLength; }

        //Quit before an overflow.
        if(titleCount >= 34){ break; }

        titleBuffer = strtok(NULL,",");
    }

    intWidth = longestWord + 5;

    intOptions = titleCount;

    //Set the options for the toolTipDbox.
    if(hasToolTips == true){

        //Draw it just to the right of the menu.
        toolTipDbox.options(intx+intWidth+1,inty,0,0);
    }

    menuWindow = newwin(titleCount+2, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen
	curs_set(0); //Turn off the blinking cursor >:U

	//Correct intActive if the number of titles is wrong.
	if(intActive > titleCount){ intActive = 1; }

    mvwprintw(menuWindow, intActive, intWidth-3, "<="); // Print the starting arrow

    //Print the starting tooltip if we have one.
    if (hasToolTips == true && toolTipCount >= intActive){
        toolTipDbox.make(toolTipArrayString[intActive-1].c_str());
    }

    counter = 0;
    while(counter < titleCount){
        mvwprintw(menuWindow, counter + 1, 1, titleArrayString[counter].c_str());
        wrefresh(menuWindow);
        counter++;
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

        //Draw the tooltip (if applicable).
        if (hasToolTips == true){
            toolTipDbox.clean();

            //If we have a toolTip for that option, show it.
            if (toolTipCount >= intActive){
                toolTipDbox.make(toolTipArrayString[intActive-1].c_str());
            }
        }
    }
    return -1;
}


int Menu::toolTip(const char* p_csvToolTip){

    //Declare local variables.
    toolTipCount = 0;
    int longestToolTip = 0;
    char * toolTipBuffer;
    //End declaration of local variables.

    //Error on strings that are too short.
    if(strlen(p_csvToolTip) < 3) { return -1; }

    //Quit if it's disabled.
    if(enableToolTips == false){
        return 0;
    }

    #ifdef _WIN32
    //Error on strings that are too long.
    if ((strlen(p_csvToolTip)+1) >= 9001){ return -1; }
    char csvToolTipString[9001];
    #else
    char csvToolTipString[strlen(p_csvToolTip)+1];
    #endif

    //No need for strncpy due to the definition of the array based on the size of the string.
    //Maybe do something about this for le winblows?
    strcpy(csvToolTipString,p_csvToolTip);

    toolTipBuffer = strtok(csvToolTipString,",");

    while(toolTipBuffer != NULL){

        //Save the titles into the array
        toolTipArrayString[toolTipCount] = toolTipBuffer;
        toolTipCount++;

        //Prevent unsigned-signed comparison.
        int toolTipBufferLength = strlen(toolTipBuffer);

        //Calculate the longest word for the width of things.
        if(toolTipBufferLength > longestToolTip ){ longestToolTip = toolTipBufferLength; }

        //Quit before an overflow.
        if(toolTipCount >= 34){ return -1; }

        toolTipBuffer = strtok(NULL,",");
    }

    //Close up.
    hasToolTips = true;
    return 0;
}


int Menu::scrollMake(const char* p_csvTitles){

    //Declare local variables.
    int counter = 0;
    int intOptions = 0;
    int intLastActive = 0;
    int intWidth = 0;
    int offset = 0;
    int titleCount = 0;
    int longestWord = 0;
    long longChar = 0;
    char * titleBuffer;
    //End declaration of local variables.

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
        titleArrayString[titleCount] = titleBuffer;
        titleCount++;

        //Prevent signed-unsigned comparison.
        int titleBufferLength = strlen(titleBuffer);

        //Calculate the longest word for the width of things.
        if(titleBufferLength > longestWord ){ longestWord = titleBufferLength; }

        //Quit before an overflow.
        if(titleCount >= 34){ break; }

        titleBuffer = strtok(NULL,",");
    }

    intWidth = longestWord + 5;

    intOptions = titleCount;

    //Set the options for the toolTipDbox.
    if(hasToolTips == true){

        //Draw it just to the right of the menu.
        toolTipDbox.options(intx+intWidth+1,inty,0,0);
    }

    menuWindow = newwin(optionsHeight, intWidth, inty, intx); //Create the window
    wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
    keypad(menuWindow, TRUE); //Init options for the screen
	curs_set(0); //Turn off hte blinking cursor >:U
        wrefresh(menuWindow);
    //Calculate offsets and active numbers.
    while(intActive >= (titleCount - optionsHeight - 1)){
        offset++;
        intActive--;
    }


    while(true){

        //Clean out the menu.
        wclear(menuWindow);
        wborder(menuWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on
        wrefresh(menuWindow);

        //Draw the titles
        counter = 1;
        while((counter) <= (optionsHeight - 2)){
            mvwprintw(menuWindow, counter, 1, titleArrayString[(counter - 1) + offset].c_str());
            counter++;
            wrefresh(menuWindow);
        }

        //Draw the arrow.
        mvwprintw(menuWindow, intActive, intWidth-3, "<=");

        //Draw the toolTip (if applicable)
        if (hasToolTips == true){
            toolTipDbox.clean();
            toolTipDbox.make(toolTipArrayString[intActive+offset-1].c_str());
        }

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
            //Calculate the value that needs to be returned.
            intActive += offset;
            
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


int Menu::value(int p_value){
    intValue = p_value;
    return 0;
}


void Menu::clean(){
    wclear(menuWindow);
    wrefresh(menuWindow);
    delwin(menuWindow);

    //Clear toolTipDbox id applicable.
    if (hasToolTips == true){
        toolTipDbox.clean();
    }

    if (rememberPosition == false){ intActive = 1;} //Resets cursor position on deletion. Adjust defaults in initialization list.
    hasToolTips = false; //Clean out the toolTip bool.
}


int Menu::disableToolTips(bool p_enableToolTips){

    //Remember whether to enable/disable tooltips.
    //Invert due to function name.
    enableToolTips = !p_enableToolTips;
    return 0;
}


int Menu::remember(bool p_rememberPosition){

    //Record the memory on or off.
    rememberPosition = p_rememberPosition;
    return 0;
}

