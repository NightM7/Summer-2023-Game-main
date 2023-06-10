#include "movement.hpp"

#include <iostream>
#include <raylib.h>

/// bird movement ///

int a = 0;

float gravity=3.0f;

struct bird{
        float position=GetScreenHeight()/2.0f-79;

        void update(){
            position+=gravity;
            gravity+=0.05f;
        };

        void flap(){
            position -=3*gravity;
            gravity=3.0f;
        };
    
    };
bird fbf;

void birdJump(){
    if(IsKeyPressed(KEY_SPACE)||(a>=1 && a<=35)){
            fbf.flap();
            a++;
            fbf.position +=1+a/10;
        }
        else
            if(fbf.position<GetScreenHeight()-140){
                fbf.update();
                a=0;
            }
}

/// pipe movement ///

struct pipe{
    float x_pos =GetRenderWidth();
    const float speed =3;
    int h1=GetRandomValue(150,500);
    int h2=780-h1-230;
    void reset(){
        x_pos=GetRenderWidth();
    }
    void move(){
        x_pos-=speed;
    }
};
pipe wall;

void pipe_movement(){
    wall.move();
    if(wall.x_pos<=-100){
        wall.reset();
    wall.h1=GetRandomValue(150,500);
    wall.h2=780-wall.h1-230;
    }   
}

/// drawings ///

void drawing(){
    Texture2D fb_flap=LoadTexture("./resources//flappy-bird-flaps.png");
    Texture2D fb = LoadTexture("./resources/flappy-bird.png");// fb = flappy bird
    DrawTexture(fb, GetRenderWidth() / 4 - 104, fbf.position, WHITE);
    DrawRectangle(wall.x_pos,GetScreenHeight()-wall.h1,100,wall.h1,BLACK);
    DrawRectangle(wall.x_pos,1,100,wall.h2,BLACK);
    if(IsKeyPressed(KEY_SPACE)||(a>=1 && a<=28))
        DrawTexture(fb_flap, GetRenderWidth() / 4 - 104, fbf.position, WHITE);
    //  Texture2D pill1 =LoadTexture("./resources/pillar-2.1.png");
    //  DrawTexture(pill1,GetScreenWidth()/2,GetScreenHeight()/2,WHITE);
}
