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

#include <ncurses.h>
#include <string>
#include <sstream>
#include <string.h>
#include "dialogBox.h"

int DialogBox::quickMake(const char* p_text,int p_x,int p_y,int p_width,bool p_attention){

    //Error checking
    if (p_x < 0 || p_y < 0){ return -1; }

    //Set options
    DialogBox::options(p_x, p_y, p_width, p_attention);

    //Draw screen
    DialogBox::make(p_text);

    return 0;
}


int DialogBox::options(int p_x,int p_y,int p_width,bool p_attention){

    //Check for invalid inputs
    if (p_x < 0 || p_y < 0){ return -1; }

    //Set values
    x = p_x;
    y = p_y;
    originalWidth = p_width;
    attention = p_attention;

    return 0;
}


int DialogBox::make(const char* p_text){

    //Declare local variables.

    //User-changable vars.
    const char * splitChar = "_"; //Character to split lines on.

    //Misc. vars.
    int count = 0;
    long keyPress = 0;

    //Vars for the line-splitting.
    int splitCounter = 0;
    int longestLine = 0;
    char * splitBuffer;
    std::string splitTextArray[35];

    //End declaration of local variables.

    /****************************************************************************************/

    #ifdef _WIN32
    //Error on strings that are too long.
    if ((strlen(p_csvTitles)+1) >= 9001){ return -1; }
    char textCharArray[9001];
    #else
    char textCharArray[strlen(p_text)+1];
    #endif

    //No need for strncpy due to the definition of the array based on the size of the string.
    //Maybe do something about this for le winblows?
    strcpy(textCharArray,p_text);

    splitBuffer = strtok(textCharArray,splitChar);

    while(splitBuffer != NULL){

        //Save the titles into the array
        splitTextArray[splitCounter] = splitBuffer;
        splitCounter++;

        //Calculate the longest word for the width of things.
        if(strlen(splitBuffer) > longestLine ){ longestLine = strlen(splitBuffer); }

        //Quit before an overflow.
        if(splitCounter >= 34){ break; }

        splitBuffer = strtok(NULL,splitChar);
    }

    /*****************************************************************************************/

    if(hasInitialized == false){

        if (originalWidth < 3){

            //Set the "tight" width.
            width = longestLine + 2;
        }
        else{

            //Use the passed width.
            width = originalWidth;
        }

        dialogBoxWindow = newwin(splitCounter+2, width, y, x); //Create the window
        wborder(dialogBoxWindow, charSide, charSide, charTop, charTop, charCorner, charCorner, charCorner, charCorner); //Put the border on

        //Init options
        keypad(dialogBoxWindow, TRUE);
        curs_set(0);

        hasInitialized = true;
    }

    //Draw the text
    count = 0;
    while(count < splitCounter){
        mvwprintw(dialogBoxWindow,count+1,1,splitTextArray[count].c_str());
        count++;
    }

    //Magick here, causes the text to show up :o
    wrefresh(dialogBoxWindow);

    //If attention == true; Wait for enter press
    if (attention == true){
        while (keyPress != 32){ //10 is enter, use OR to add more keypresses
            keyPress = wgetch(dialogBoxWindow);
        }
    }

    //Cleans it if you use the function again.
    keyPress = 0;

    //Allow cleaning.
    justCleaned = false;

    //If attention == false, exit.
    return 0;
}


int DialogBox::make(int p_number){

    //Create conversion string
    std::string stringConversion;
    std::stringstream stringStreamConverter;

    //Convert int to string
    stringStreamConverter << p_number;
    stringConversion = stringStreamConverter.str();

    //Call make with the string
    //.c_str(); will convert from string to const char*
    return DialogBox::make(stringConversion.c_str());
}


void DialogBox::update(){

    //Update window, bringing it to front.
    wrefresh(dialogBoxWindow);
}


void DialogBox::clean(){

    //Error if we try to clean twice in a row.
    if(justCleaned == true){ return; }

    //Clear window.
    wclear(dialogBoxWindow);
    wrefresh(dialogBoxWindow);
    delwin(dialogBoxWindow);

    //Reset a few vars.
    hasInitialized = false;
    justCleaned = true;
}


int DialogBox::title(const char* p_title){

    //Declare local variables.
    int titleLength;
    //End variable declaration.

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

