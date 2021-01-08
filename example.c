/*
Example use of the DogeGame Engine
==================================
by LividPhysics | Starter 12-11-2020
*/

#include "raylib.h"
#include "engine.h"

#include <stdio.h>

int main() {
    // init
    // for raylib-related info see https://www.raylib.com/examples.html
    
    InitWindow(WIDTH, HEIGHT, "test e_001"); // initialize a window
    
    SetTargetFPS(60);
    
    bool paused = false;

    bool needsIGC = false;

    bool infoMenu = false;
    
 // Rectangle bounds = { WIDTH/2 - 50, HEIGHT/2 - 25, 100, 50 };
 // Button testButton = MakeButton(bounds, BLUE, LIME, RED);
    
    Rectangle b1 = {WIDTH / 4 - 50, 125, 100, 50};
    Rectangle b2 = {WIDTH / 4 - 50, 175, 100, 50};
    Rectangle b3 = {WIDTH / 4 - 50, 225, 100, 50};
    Rectangle b4 = {WIDTH / 4 - 50, 275, 100, 50};

    Button darkbutton  = MakeButton(b1, BLACK, "DARK");
    Button firebutton  = MakeButton(b2, RED,   "FIRE");
    Button waterbutton = MakeButton(b3, BLUE,  "WATER");
    Button grassbutton = MakeButton(b4, GREEN, "GRASS");
    
    Card darkcard  = MakeCard("C:\\dev\\dltcg\\res\\dark.png",  "Dark Card",  "Dark Card",  10, 10);
    Card firecard  = MakeCard("C:\\dev\\dltcg\\res\\fire.png",  "Fire Card",  "Fire Card",  10, 10);
    Card watercard = MakeCard("C:\\dev\\dltcg\\res\\water.png", "Water Card", "Water Card", 10, 10);
    Card grasscard = MakeCard("C:\\dev\\dltcg\\res\\grass.png", "Grass Card", "Grass Card", 10, 10);

    // main loop
    
    while (!WindowShouldClose()) {
        // update

        if(!paused) {
            UpdateButton(&darkbutton);
            UpdateButton(&firebutton);
            UpdateButton(&waterbutton);
            UpdateButton(&grassbutton);
        }

        if(IsKeyPressed(KEY_Q)) paused = !paused;
        if(IsKeyPressed(KEY_I)) infoMenu = !infoMenu;

        // draw
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            DrawText("DLTCG Demo", 2, HEIGHT - 10, 5, BLACK);
            
         // DrawCard(&testCard, WIDTH/2, HEIGHT/2, true);

            if(needsIGC) DrawIGC("test");
            if(paused) DrawPauseMenu();
         // if(infoMenu) DrawInfoMenu(cards);
            
         // DrawRectangleRec(testButton.rec, testButton.color);
            DrawButton(darkbutton);
            DrawButton(firebutton);
            DrawButton(waterbutton);
            DrawButton(grassbutton);

            if(!paused) {
                if(isPressed(&darkbutton))  DrawCard(&darkcard,  WIDTH/2, HEIGHT/2, true);
                if(isPressed(&firebutton))  DrawCard(&firecard,  WIDTH/2, HEIGHT/2, true);
                if(isPressed(&waterbutton)) DrawCard(&watercard, WIDTH/2, HEIGHT/2, true);
                if(isPressed(&grassbutton)) DrawCard(&grasscard, WIDTH/2, HEIGHT/2, true);
            }
            
        EndDrawing();
    }
    
    // de-init
    CloseWindow(); // WindowShouldClose() returned true, so the loop exited and the window should be closed
    
    return 0; // main is an int function in C
}