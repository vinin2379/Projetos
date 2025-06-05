/**
 * @file main.c
 * @author Prof. Dr. David Buzatto
 * @brief Main function and logic for the game. Simplified template for game
 * development in C using Raylib (https://www.raylib.com/).
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*---------------------------------------------
 * Library headers.
 *-------------------------------------------*/
#include "raylib/raylib.h"
//#include "raylib/raymath.h"

/*---------------------------------------------
 * Project headers.
 *-------------------------------------------*/


/*---------------------------------------------
 * Macros. 
 *-------------------------------------------*/

 const int MAX = 100;
/*--------------------------------------------
 * Constants. 
 *------------------------------------------*/


/*---------------------------------------------
 * Custom types (enums, structs, unions, etc.)
 *-------------------------------------------*/

typedef struct Bolinha{

    float x;
    float y;
    float raio;

    float vx;
    float vy;

    float atrito;
    float elasticidade;
    
    bool arrastando;

    float xante;
    float yante;

}Bolinha;

/*---------------------------------------------
 * Global variables.
 *-------------------------------------------*/

Bolinha bolinha;
float GRAVIDADE = 100;

Bolinha bolinhas[100];
int quantidade = 0;

/*---------------------------------------------
 * Function prototypes. 
 *-------------------------------------------*/
/**
 * @brief Reads user input and updates the state of the game.
 * 
 * 
 */
void update( float delta );



/**
 * @brief Draws the state of the game.
 */
void draw( void );

/**
 * @brief Game entry point.
 */
int main( void ) {

    // local variables and initial user input

    // antialiasing
    SetConfigFlags( FLAG_MSAA_4X_HINT );

    // creates a new window 800 pixels wide and 450 pixels high
    InitWindow( 1200, 900, "Ball Game" );

    // init audio device only if your game uses sounds
    //InitAudioDevice();

    // FPS: frames per second
    SetTargetFPS( 60 );    

    // you must load game resources here

    bolinha.x = GetScreenWidth()/2;
    bolinha.y = GetScreenHeight()/2;
    bolinha.raio = 50;

    bolinha.vx = 700;
    bolinha.vy = 400;

    bolinha.atrito = 0.99;
    bolinha.elasticidade = 0.9;

    bolinha.arrastando = false;

    

    // game loop
    while ( !WindowShouldClose() ) {
        update( GetFrameTime() );
        draw();
    }

    // you should unload game resources here

    
    // close audio device only if your game uses sounds
    //CloseAudioDevice();
    CloseWindow();

    return 0;

}

void update( float delta ) {

    DrawFPS(20,20);

    if(IsKeyPressed(KEY_R)){

        bolinha.raio = 50;
        GRAVIDADE = 100;

    }

    if(IsKeyDown(KEY_A)){

        bolinha.vx = bolinha.vx - 400;

    }

    if(IsKeyDown(KEY_D)){

        bolinha.vx = bolinha.vx + 400;

    }

    if(IsKeyPressed(KEY_G)){

        GRAVIDADE = -100;

    }

    if(IsKeyPressed(KEY_SPACE)){

        // bolinha.vx = bolinha.vx + 100;
        bolinha.vy = bolinha.vy - 4000;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        float c1 = GetMouseX() - bolinha.x;
        float c2 = GetMouseY() - bolinha.y;
        float h = c1*c1 + c2*c2;

        if(h <= bolinha.raio * bolinha.raio){

            bolinha.arrastando = true;

            

        

        }

    }else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

        bolinha.arrastando = false;

        

    }   

    if(bolinha.arrastando){

        if(IsKeyDown(KEY_F)){
           
            bolinha.raio++;
        
        }

        bolinha.x = GetMouseX();
        bolinha.y = GetMouseY();

        bolinha.vx = ((bolinha.x - bolinha.xante) / delta) * 1.2;
        bolinha.vy = ((bolinha.y - bolinha.yante) / delta) *1.2;

        bolinha.xante = bolinha.x;
        bolinha.yante = bolinha.y;
        

    }else{

        bolinha.x = bolinha.x + bolinha.vx * delta;
        bolinha.y = bolinha.y + bolinha.vy * delta;

        if(bolinha.y + bolinha.raio >= GetScreenHeight()){

            bolinha.y = GetScreenHeight() - bolinha.raio;

            bolinha.vy = -bolinha.vy * bolinha.elasticidade;

        }else if(bolinha.y - bolinha.raio < 0){

            bolinha.y = bolinha.raio;

            bolinha.vy = -bolinha.vy * bolinha.elasticidade;

        }

        if(bolinha.x + bolinha.raio >= GetScreenWidth()){

            bolinha.x = GetScreenWidth() - bolinha.raio;

            bolinha.vx = -bolinha.vx* bolinha.elasticidade;


        }else if(bolinha.x - bolinha.raio < 0){

            bolinha.x = bolinha.raio;

            bolinha.vx = -bolinha.vx * bolinha.elasticidade;

        }

        bolinha.vx = bolinha.vx * bolinha.atrito;
        bolinha.vy = bolinha.vy * bolinha.atrito + GRAVIDADE;

    }
}

void draw( void ) {

    BeginDrawing();
    ClearBackground( WHITE );

    DrawCircle(bolinha.x,bolinha.y,bolinha.raio,PURPLE);

    EndDrawing();

}


