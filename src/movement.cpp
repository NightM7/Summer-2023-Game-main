#include "movement.hpp"
#include "mainMenu.hpp"

#include <iostream>
#include <raylib.h>

                                                    /////////////////////
                                                    /// bird movement ///
                                                    /////////////////////

int a = 0;
int b =0;
float gravity=3.0f;

struct bird{
        Vector2 position ={1280 / 4.0f - 104,780/2.0f-79};
        float radius=45;
        Vector2 sabilizer ={65,80};
        void update(){
            position.y+=gravity;
            gravity+=0.05f;
        };

        void flap(){
            position.y -=3*gravity;
            gravity=3.0f;
        };
    
    };
bird fbf;
bird hb;
void birdJump(){
    if(IsKeyPressed(KEY_SPACE)||(a>=1 && a<=35)){
            fbf.flap();
            a++;
            fbf.position.y +=1+a/10;
        }
        else
            if(fbf.position.y<GetScreenHeight()-140){
                fbf.update();
                a=0;
            }
}
void update_hb(){
    hb.position.y=fbf.position.y+hb.sabilizer.y;
    hb.position.x=fbf.position.x+hb.sabilizer.x;
}

                                                    /////////////////////
                                                    /// pipe movement ///
                                                    /////////////////////

struct pipe{
    float h1=GetRandomValue(150,500);
    float h2=780-h1-230;
    float y1=780-h1;
    float y2=1;
    float x_pos =1380.0f;
    const float speed =5;
    
    Vector2 pos_bottom = {x_pos,y1};
    Vector2 pos_up ={x_pos,y2};
    Vector2 size_bottom ={100,h1};
    Vector2 size_up ={100,h2};
    

    void reset(){
        x_pos=GetRenderWidth();
    }
    
    void update(){
        pos_bottom.x=x_pos;
        pos_up.x=x_pos;
        size_bottom.y=h1;
        size_up.y=h2;
        pos_bottom.y=780-h1;
        pos_up.y=y2;
    }

    void move(){
        x_pos-=speed;
    }

    void create() {        
        DrawRectangleRec(getlower_pipe(), BLACK);
        DrawRectangleRec(getupper_pipe(), BLACK);
    }

    Rectangle getlower_pipe(){
        return Rectangle {pos_bottom.x,pos_bottom.y,size_bottom.x,size_bottom.y};
    }
    Rectangle getupper_pipe(){
        return Rectangle {pos_up.x,pos_up.y,size_up.x,size_up.y};
    }
    void movement(){
        update();
        create();
        move();
        if(x_pos<=-100){
                reset();
                h1=GetRandomValue(150,500);
                h2=780-h1-230;
                update();
        }
    }
};
pipe wall;
pipe wall2;
void pipe_movement(){
    wall.movement(); 
    if(b==1||wall.x_pos==GetScreenWidth()/2){
        wall2.movement();   
        b=1;
    }
}

void collision(){
    bool game_over=false;
    if(CheckCollisionCircleRec(hb.position,hb.radius,wall.getlower_pipe()) || CheckCollisionCircleRec(hb.position,hb.radius,wall.getupper_pipe())){
        game_over=true;
    }
      if(CheckCollisionCircleRec(hb.position,hb.radius,wall2.getlower_pipe()) || CheckCollisionCircleRec(hb.position,hb.radius,wall2.getupper_pipe())){
        game_over=true;
    }
    if(game_over){
       ///////////////////////
       //////game over///////
       /////////////////////
    }
}


                                                    ////////////////
                                                    /// drawings ///
                                                    ////////////////

Texture2D returntxt(Texture2D pill1){
    return pill1;
}
void drawing(){
    Texture2D fb_flap=LoadTexture("./resources//flappy-bird-flaps.png");
    Texture2D fb = LoadTexture("./resources/flappy-bird.png");// fb = flappy bird
    //Texture2D pill1 =LoadTexture("./resources/pillar-2.1.png");
    DrawTextureEx(fb,fbf.position,1.0,0.75, WHITE);
    DrawCircleV(hb.position,hb.radius,PINK);
    if(IsKeyPressed(KEY_SPACE)||(a>=1 && a<=28)){
        DrawTextureEx(fb_flap,fbf.position,1.0,0.75, WHITE);
    }
    //DrawTextureV(pill1,wall2.pos_up,WHITE);
}

//   Texture2D pill1 =LoadTexture("./resources/pillar-2.1.png");
//   DrawTexture(pill1,1,1,WHITE);
