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

#define MAXIMO 1000

/*--------------------------------------------
 * Constants. 
 *------------------------------------------*/

 const int PARADO = 0;
 const int JOGANDO = 1;

/*---------------------------------------------
 * Custom types (enums, structs, unions, etc.)
 *-------------------------------------------*/

typedef struct Jogador {

    Vector2 pos;
    Vector2 dim;
    float vel;
    Color cor;
    int pont;

} Jogador;

typedef struct Bola{

    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;

} Bola;



/*---------------------------------------------
 * Global variables.
 *-------------------------------------------*/

 Jogador jogador1;
 Jogador jogador2;
 Bola bola;
 Color cores;
 int quantidade = 0;
 Jogador *vezDe;

 int estado;



/*---------------------------------------------
 * Function prototypes. 
 *-------------------------------------------*/
/**
 * @brief Reads user input and updates the state of the game.
 */
void update( float delta );


/**
 * @brief Draws the state of the game.
 */
void draw( void );

void atualizarJogador( Jogador *jogador, float delta, int teclaCima, int teclaBaixo);
void desenharJogador(Jogador *jogador);
void desenharQuadra(void);
void desenharPlacar(Jogador *jogador1, Jogador *jogador2);

void desenharBola(Bola *bola);
void atualizarBola(Bola *bola, float delta);
void resolverColisao(Jogador *jogador1, Jogador *jogador2, Bola *bola);
int bateu(Bola *bola);





/**
 * @brief Game entry point.
 */
int main( void ) {

    // local variables and initial user input

    // antialiasing
    SetConfigFlags( FLAG_MSAA_4X_HINT );

    // creates a new window 800 pixels wide and 450 pixels high
    InitWindow( 800, 450, "Window Title" );

    // init audio device only if your game uses sounds
    //InitAudioDevice();

    // FPS: frames per second
    SetTargetFPS( 60 );    

    // you must load game resources here

    bola = (Bola){

        .pos = {
            .y = GetScreenHeight()/2,
            .x = GetScreenWidth()/2
        },

        .vel = {
            .x = 0,
            .y = 0
        },

        .raio = 15,

        .cor = WHITE

    };

    vezDe = &jogador2;
    estado = PARADO;

     jogador1 = (Jogador){

        .pos = {
            .x = 30,
            .y = (GetScreenHeight()/2) - 75
        },
        
        .dim = {
            .x = 30,
            .y = 150
        },

        .vel = 200,
        
        .cor = WHITE,
    
        .pont = 0
        
    };

    jogador2 = (Jogador){

        .pos = {
            .x = GetScreenWidth() - 60,
            .y = (GetScreenHeight()/2) - 75
        },
        
        .dim = {
            .x = 30,
            .y = 150
        },

        .vel = 200,

        .cor = WHITE,

        .pont = 0
    };


    

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

    atualizarJogador(&jogador1, delta, KEY_W, KEY_S);
    atualizarJogador(&jogador2, delta, KEY_UP, KEY_DOWN);

    if(estado == PARADO){

        if(IsKeyPressed(KEY_ENTER)|| IsKeyPressed(KEY_E)){

            estado = JOGANDO;

            if(vezDe == &jogador1){

                bola.vel.x = 400;
                bola.vel.y = GetRandomValue(0,1) == 0 ? 200 : -200;

            } else if(vezDe == &jogador2){

                bola.vel.x = -400;
                bola.vel.y = GetRandomValue(0,1) == 0 ? 200 : -200;

            }

        }

    }else{

        
        atualizarBola(&bola, delta);
    
        resolverColisao(&jogador1, &jogador2, &bola);
    }

}

void draw( void ) {

    DrawFPS(20,20);
    BeginDrawing();
    ClearBackground( BLACK );

    desenharQuadra();

    desenharJogador(&jogador1);
    desenharJogador(&jogador2);

    desenharPlacar(&jogador1, &jogador2);

    desenharBola(&bola);
    
    int sim = bateu(&bola);

    

    if ( sim == 5)  {
            if ( quantidade < MAXIMO ) {

                cores = (Color){
                    GetRandomValue( 0, 255 ),
                    GetRandomValue( 0, 255 ),
                    GetRandomValue( 0, 255 ),
                    255
                };

                jogador1.cor = cores;
                jogador2.cor = cores;
                bola.cor = cores;
                
                
            }
            
    }

    if(IsKeyPressed(KEY_R)){

        jogador1.pont = 0;
        jogador2.pont = 0;
        jogador1.pos.y = GetScreenHeight()/2 - (jogador1.dim.y/2);
        jogador2.pos.y = GetScreenHeight()/2 - (jogador2.dim.y/2);
        bola.pos.x = GetScreenWidth()/2;
        bola.pos.y = GetScreenHeight()/2;
        estado = PARADO;
        vezDe = &jogador2;

    }

    

    
    


    EndDrawing();

}



void atualizarJogador( Jogador *jogador, float delta, int teclaCima, int teclaBaixo){

    if(IsKeyDown(teclaCima)){

        jogador->pos.y -= jogador->vel * delta;

    }

    
    if(IsKeyDown(teclaBaixo)){

        jogador->pos.y += jogador->vel * delta;

    }



    if(jogador->pos.y < 0){

        jogador->pos.y = 0;

    }

    if(jogador->pos.y + jogador->dim.y > GetScreenHeight()){

        jogador->pos.y = GetScreenHeight() - jogador->dim.y;

    }

}

void desenharJogador(Jogador *jogador){

    DrawRectangle( jogador ->pos.x , jogador ->pos.y, jogador ->dim.x, jogador ->dim.y, jogador ->cor);

}

void desenharQuadra(void){

    int centro = GetScreenWidth()/2;
    int mLarg = 5;
    int altura = 30;

    for(int i = 0; i < 15; i += 2){

        DrawRectangle(centro - mLarg, altura * i, mLarg*2, altura, jogador1.cor);

    }

}

void desenharPlacar(Jogador *jogador1, Jogador *jogador2){

    int centro = GetScreenWidth()/2;
    int margem = 30;
    const char *pj1 =TextFormat("%d",jogador1->pont) ;
    const char *pj2 =TextFormat("%d",jogador2->pont) ;

    DrawText(
    pj1,
    centro - margem - MeasureText(pj1, 40) ,
    margem,
    40,
    jogador1->cor);
    
    DrawText(
    pj2,
    centro + margem,
    margem,
    40,
    jogador2->cor);

}


void atualizarBola(Bola *bola, float delta){

    bola->pos.x += bola->vel.x * delta;
    bola->pos.y += bola->vel.y * delta;

    if(bola->pos.x + bola->raio > GetScreenWidth()){

        jogador1.pont++;
        bola->pos.x = GetScreenWidth()/2;
        bola->pos.y = GetScreenHeight()/2;
        jogador1.pos.y = GetScreenHeight()/2 - (jogador1.dim.y/2);
        jogador2.pos.y = GetScreenHeight()/2 - (jogador2.dim.y/2);
        estado = PARADO;
        vezDe = &jogador1;

       
        
        

    }else if(bola->pos.x - bola->raio < 0){

       
        jogador2.pont++;
        bola->pos.x = GetScreenWidth()/2;
        bola->pos.y = GetScreenHeight()/2;
        jogador1.pos.y = GetScreenHeight()/2 - (jogador1.dim.y/2);
        jogador2.pos.y = GetScreenHeight()/2 - (jogador2.dim.y/2);
        estado = PARADO;
        vezDe = &jogador2;
        
    }

    if(bola->pos.y + bola->raio > GetScreenHeight()){

        bola->vel.y = -bola->vel.y;
        

    }else if(bola->pos.y - bola->raio < 0){

        bola->vel.y = -bola->vel.y;
        

    }

}

void desenharBola(Bola *bola){

    DrawCircleV(bola->pos, bola->raio, bola->cor);

}


void resolverColisao(Jogador *jogador1, Jogador *jogador2, Bola *bola){

    bool cj1 = CheckCollisionCircleRec(

        bola->pos,
        bola->raio,
        (Rectangle) {
            .x = jogador1 ->pos.x,
            .y = jogador1 ->pos.y,
            .width = jogador1->dim.x,
            .height = jogador1->dim.y
        }

    );

    bool cj2 = CheckCollisionCircleRec(

        bola->pos,
        bola->raio,
        (Rectangle) {
            .x = jogador2 ->pos.x,
            .y = jogador2 ->pos.y,
            .width = jogador2->dim.x,
            .height = jogador2->dim.y
        }

    );


    if(cj1){

        bola->pos.x = jogador1->pos.x + jogador1->dim.x + bola->raio;
        bola->vel.x = -bola->vel.x + 30;
        
        

    }

    if(cj2){

        bola->pos.x = jogador2->pos.x - bola->raio;
        bola->vel.x = -bola->vel.x - 30;

    }

}

int bateu(Bola *bola){

    if(bola->pos.x + bola->raio > GetScreenWidth()){

        return 5;

        

    }else if(bola->pos.x - bola->raio < 0){

        return 5;
        
    }

    if(bola->pos.y + bola->raio > GetScreenHeight()){

        return 5;

    }else if(bola->pos.y - bola->raio < 0){

        return 5;
        

    }

    return 0;

}
