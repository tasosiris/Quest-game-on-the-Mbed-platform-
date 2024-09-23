//=================================================================
// The speech class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "speech.h"

#include "globals.h"
#include "hardware.h"
#include "graphics.h"

///////////////////////////////
//Static function declarations
///////////////////////////////
/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();


/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);


///////////////////////////////
//Drawing function declarations
///////////////////////////////


//***
// HINT: for this function and below: Check out the ULCD demo in the docs to see what
// uLCD methods you can use to draw graphics 

//Link: https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/
//***


void draw_speech_bubble()
{
    //****************
    // TODO: Implement
    //****************
    
    //1. Draw a speech bubble at the bottom of the screen 
    // Hint: You can stack ULCD rectangles to make a border
    uLCD.rectangle(0, 93, 127, 115, 0x00FF00);
    uLCD.filled_rectangle(1, 94, 126, 114, BLACK); 
}

void erase_speech_bubble()
{
    //****************
    // TODO: Implement
    //****************
    
    //1. Erase the speech bubble at the bottom of the screen
    // Hint: You can overwrite the bubble with a empty (black) one
    uLCD.filled_rectangle(0, 93, 127, 115, BLACK);
    draw_border();
}

void draw_speech_line(const char* line, int which)
{
    //****************
    // TODO: Implement
    //****************
    //1. Set the location which line of text will go the uLCD
    // Hint: Change the y coordinate based on which line (top or bottom)

    //2. For each character in the text, write it to uLCD
    // for (int i = 0; line[i] && i < 17; i++) //We can simplify by limiting each line to 17 char
    // {
    //     //TODO: Write the character
    //     wait_ms(30); 
    // }
    uLCD.text_string((char*) line, 1, 12 + which, FONT_5X7, 0xFFC300);
}

void speech_bubble_wait()
{
    //****************
    // TODO: Implement
    //****************
    
    // 1. Keep waiting until the action button is pressed 
    //   Hint: What type of loop can we use to stay until a condition is met?
        GameInputs in;

    Timer c; c.start();

    // Get inputs and display a flashing button
    // while waiting for action button to be pressed
    do {
        Timer time; 
        time.start();

        // Read the time duration since the last button press
        int dc = c.read_ms();

        // Check if the duration is greater than 1000 milliseconds
        if (dc > 2600) {
            // If so, draw a filled circle and reset the timer
            uLCD.filled_circle(120, 114, 3, DGREY);
            c.reset();
        }
        // If the duration is between 500 and 1000 milliseconds
        else if (dc > 1500)
            // Draw a filled circle with a different color
            uLCD.filled_circle(120, 114, 3, LGREY);

        // Read inputs (not shown in the provided code)
        in = read_inputs();

        time.stop();
        // Calculate the elapsed time since the timer started
        int dt = time.read_ms();
        
        // If the elapsed time is less than 100 milliseconds, wait for the remaining time
        if (dt < 1600) wait_ms(1600 - dt);

    // Continue the loop while button b1 is pressed
    } while (in.b1);


}

void speech(const char* line1, const char* line2)
{
    //****************
    // TODO: Implement
    //****************
    // 1. Place the two lines into an array of lines
    // 2. Pass in to long_speech with the corresponding number of lines
    // Draw the speech bubble on the display
    draw_speech_bubble();

    // Draw the first line of text in the speech bubble at the top
    draw_speech_line(line1, TOP);

    // Draw the second line of text in the speech bubble at the bottom
    draw_speech_line(line2, BOTTOM);

    // Wait for user interaction or a specific event related to the speech bubble
    speech_bubble_wait();

    // Erase the speech bubble and its contents from the display
    erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{

    //****************
    // TODO: Implement
    //****************

    //1. Create a speech bubble

    //2. For each lines, display only two lines at a time
    //   If two lines are displayed, make sure to wait (call the wait function)

    //3. Erase the speech bubble when you are done
    // Initialize a loop counter variable
    int i;

    // Determine the length of the iteration based on whether 'n' is odd or even
    // If 'n' is odd, set 'length' to 'n-1'; otherwise, set it to 'n'
    int length = (n % 2) ? n-1 : n;

    // Iterate over the speech lines, incrementing the loop counter by 2 in each iteration
    for(i = 0; i < length; i++)
        // Call the 'speech' function with pairs of lines, i and i+1
        speech(lines[i++], lines[i]);

    // Check if 'length' is equal to 'n-1', indicating that 'n' is odd
    if(length == n-1)
    // If 'n' is odd, call the 'speech' function with the last line and an empty string
        speech(lines[n-1], "");

}

