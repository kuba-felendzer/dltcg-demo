/*
Game Engine functions (current name: DogeGame Engine)
=====================================================
By LividPhysics | Started 12-10-2020
*/

#include "C:\raylib\raylib\src\raylib.h"
#include <stdio.h>
#include <string.h>
#define WIDTH 800
#define HEIGHT 450

//////////////////////////////////
// Rendering-related Functions  //
//////////////////////////////////

/**
* loadCustomImg :: Turns an Image path into a texture
*
* @param impath   the string form of the image's path
* @param resize_x the width of the texture
* @param resize_y the height of the texture
* @return         a texture that can then be drawn to the screen
*/
Texture2D loadCustomImg(char *impath, int resize_x, int resize_y) {    
    Image im = LoadImage(impath);
    ImageResize(&im, resize_x, resize_y);
    
    Texture2D texture = LoadTextureFromImage(im);
    UnloadImage(im);
    
    return texture;
    // to draw the following texture with drawTexture()
}


///////////////////////////////////
//  Card Structures and Methods  //
///////////////////////////////////
 /*
struct Move {
    char *name;  // the name of the move, ie "Card used NAME!"
    char *desc;  // the description of the move, ie "MOVE: Deal X damage, if this attack is used against..."
    int type;    // the move's type, ie "Deal 5 damage, inflicting TYPE". look at https://docs.google.com/spreadsheets/d/1JekVGpTdOGwYFCYANbqJ8nemaiENefHI/edit#gid=17398169 for more info
};
*/

typedef struct {
    char *path;        // the full image path to the image of the card
    Texture2D texture; // the texture of the card, generated with loadCustomImg()
    Texture2D seltex;  // the texture of the card when it is selected (usually a red fringe)
    int id;   // the id of the card
    char *title;       // the title of the card, ie "TITLE used MOVE!";
    // struct Move m1;    // the first move (top) the card can make
    // struct Move m2;    // the second move (bottom) the car can make
    char *desc;        // the description of the card (bottom text)
    int atk;           // attacking power (top left number, sword icon)
    int def;           // defending power (bottom right, heart icon)
} Card;

/* this structure can be utilized by calling loadCustomImg:
Card card; card.texture = loadCustomImg(card.path, 150, 200);
*/

int card_counter = 0;

/**
 * MakeCard :: Automates the creation of card objects
 * 
 * @param path  the path of the image the card uses ]
 * @param title the title of the card on the images ]
 * @param desc  the description of the card         ] These data points are gathered from the .png file of the image
 * @param atk   the attacking power of the card     ]
 * @param def   the defending power of the card     ]
 * @return      a card object that is prroperly filled out
 * @see         none
 */

Card MakeCard(char *path, char *title, char *desc, int atk, int def) {
    // to create: texture, id
    Texture2D tex = loadCustomImg(path, 120, 180);
    Texture2D stex = loadCustomImg(path, 120, 180);
    card_counter++;
    Card out = {path, tex, stex, card_counter, title, desc, atk, def};
    return out;
}

/**
 * DrawCard :: Draws the specified card object
 * @param c      the card actually being drawn
 * @param x      the x position where the card should be drawn
 * @param y      the y position where the card should be drawn
 * @param center whether the (x,y) denotes the top-left corner or the center of the card
 * @return       none
 * @see          a card on the screen
 */

// TODO :: Scaling of cards as an option in DrawCard()
void DrawCard(Card *c, int x, int y, bool center /*, float scale */) {
    // cards in a 12:25 ratio, texture size of 120:180 (ratio 2:3)
    if(center) {
        DrawTexture(c -> texture, x - 60, y - 90, RAYWHITE);
    } else {
        DrawTexture(c -> texture, x, y, RAYWHITE);
    }

}

///////////////////////////
// IGC-related Functions //
///////////////////////////

/**
* DrawICG :: Draw the in-game console (IGC)
* 
* @param text the text to be drawn on the console
* @return     none
* @see        a console on the screen
*/
void DrawIGC(char *text) { // draw the in-game console (IGC)
    // Draws the rectangle the IGC is in
    DrawRectangleGradientH(15, HEIGHT - 100, WIDTH - 30, 85, GRAY, LIGHTGRAY);
    DrawRectangleLines(15, HEIGHT - 100, WIDTH - 30, 85, DARKGRAY);
    // Draw the text passed
    DrawText(text, 25, HEIGHT - 80, 20, RAYWHITE);
}

////////////////
// Pause Menu //
////////////////

/**
 * DrawPauseMenu :: Draw the pause menu
 * 
 * @return none
 * @see    a pause menu
 */

void DrawPauseMenu() {
    // bounding box
    DrawRectangle( 10, 10, 320, 70, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines( 10, 10, 320, 70, BLUE);
    // list controls
    DrawText("Keyboard Controls:", 20, 20, 10, BLACK);
    DrawText("- Press Q to enter/exit this menu", 40, 40, 10, DARKGRAY);
    DrawText("- Press ESC to exit the game", 40, 60, 10, DARKGRAY);
 // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
 // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
 // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
}

/////////////
// Buttons //
/////////////

int id_counter = 0;

typedef struct {
    Rectangle rec;  // the bounding box of the button
    Color color;    // drawn color
    Color bcolor;   // default color
    Color hcolor;   // hover color, when the mouse is hovering
    Color ccolor;   // click color, when the mouse is clicking    
    int button_id;  // the unique button id
    char * text;    // the text on the button
    // void (*button_func)(void);  // the function that is called when the button is clicked
} Button;

/**
 * UpdateButton :: Update a button, called in the update section of main()
 * This method checks whether the button in question (obj) is being pressed or clicked and acts accordingly
 * 
 * @param obj the button to be updated
 * @return    none
 * @see       potential changes in the button's state
 */

void UpdateButton(Button *obj) {
    if (CheckCollisionPointRec(GetMousePosition(), obj -> rec)) { // if the mouse pointer is in the button's bounding box
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { // if the left mouse button is being clicked
            obj  -> color = obj  -> ccolor;          // show the clicking color
            // obj -> *button_func();
        } else obj  -> color = obj  -> hcolor;       // otherwise, show the hover color
    } else { 
        obj  -> color = obj  -> bcolor; 
    }       // if the mouse pointer is not above it, show the base color              
}

/**
 * isPressed :: Returns true if the button is being pressed
 * 
 * @param obj the Button being checked
 * @return    true if the button is pressed, false otherwise
 * @see       none
 */

bool isPressed(Button *obj) {
    if (CheckCollisionPointRec(GetMousePosition(), obj -> rec)) { // if the mouse pointer is in the button's bounding box
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { // if the left mouse button is being clicked
            return true;
        }
    }
    return false;
}

/**
 * isHovered :: Returns true if the button is being hovered over
 * 
 * @param obj the Button being checked
 * @return    true if the Button is being hovered over, false otherwise
 * @see       none
 */

bool isHovered(Button *obj) {
    if (CheckCollisionPointRec(GetMousePosition(), obj -> rec)) { // if the mouse pointer is in the button's bounding box
        return true;
    }
    return false;
}

/**
 * MakeButton :: Create a button object
 * This method is meant to make creating a button object easier
 * and allows for assignment of unique ids automatically
 * 
 * @param rec    the bounding box of the button itself
 * @param bcolor the default color that button defaults to
 * @param hcolor the color shown when the button is hovered over
 * @param ccolor the color shown when the button is clicked
 * @return       a button object
 * @see          none
 */

Button MakeButton(Rectangle rec, Color color, char * text) {
    Button b = { rec, Fade(color, .5f), Fade(color, .5f), Fade(color, .75f), color, id_counter, text};
    id_counter++;
    return b;
}

/**
 * DrawButton :: Draw a Button on the screen
 * 
 * @param button the button object being drawn
 * @return       none
 * @see          a button on the screen
 */

void DrawButton(Button button) {
    DrawRectangleRec(button.rec, button.color);
    int text_w = MeasureText(button.text, 20);
    int text_x = (button.rec.width - text_w) / 2;
    int fontsize = 20;
    DrawText(button.text, button.rec.x + text_x, (button.rec.y + button.rec.height / 2) - (fontsize / 2), fontsize, RAYWHITE);
}