#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <SDL2/SDL_audio.h>
//Ali Nikkhah
//Namdar Khodadad
using namespace std;
SDL_Texture* img_bckg;
SDL_Texture* img_pltfrm;
SDL_Texture* img_ball;
SDL_Texture* bar;
SDL_Texture* lives;
SDL_Texture* level;
SDL_Texture* No1;
SDL_Texture* No2;
SDL_Texture* No3;
SDL_Texture* No4;
SDL_Texture* No5;
SDL_Texture* No6;
SDL_Texture* No7;
SDL_Texture* No8;
SDL_Texture* No9;
SDL_Texture* No0;
SDL_Texture* GetReady;
SDL_Texture* Pause;
SDL_Texture* img_brick;
SDL_Texture* bomb;
int counter=0;
int n=0;
int BallR=35;
int PlatformL=200;
int PlatformH=20;
int PlatformX=525;
int PlatformY=770;
double BallX=double(PlatformX+PlatformL/2-BallR/2);
double BallY=double(PlatformY-BallR);
int bckg=2;
int ball=2;
int live_s=3;
double Vx=0.1;
double Vy=-0.1;
struct bricks{
int type;
/*
0 for void;
1 to level for bricks;
-1 for bomb;
-2 for heal;
-3 for xp;
-4 for solid;
-5 for platform +;
-6 for platform -;
-7 for fire ball;
*/
int x;
int y;
};
int ilevel=2;
int sight=1;
int damage=ilevel;
void DrawRect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
int main( int argc, char * argv[] )
{

    /*
    IF LOAD WAS FALSE::
    */

    int i=25;
    int j=20;
   struct bricks brick[6][12];
    for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=rand()%ilevel;
                          if(brick[x][y].type==0)
             {
                 brick[x][y].type=1;
             }
             brick [x][y].x=i;
             brick[x][y].y=j;
            i+=200;
        }
        i=25;
        j+=60;
    }
            for(int y=sight;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=0;
        }

    }
    int num_bombs=0;
    for(int i=0;i<num_bombs;i++)
    {
        int x=rand()%6-1;
        int y=rand()%12-1;
        brick[x][y].type=-2;
    }


    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Init( SDL_flags );
    //
    SDL_Init(SDL_INIT_AUDIO);
    //
    SDL_CreateWindowAndRenderer( 1200, 800, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    //
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV("TestAudio.wav",&wavSpec,&wavBuffer,&wavLength);
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL,0,&wavSpec,NULL,0);
    //
        SDL_AudioSpec wavSpec3;
    Uint32 wavLength3;
    Uint8 *wavBuffer3;
    SDL_LoadWAV("HitPlatform.wav",&wavSpec3,&wavBuffer3,&wavLength3);
    SDL_AudioDeviceID deviceId3 = SDL_OpenAudioDevice(NULL,0,&wavSpec3,NULL,0);
    //
        SDL_AudioSpec wavSpec2;
    Uint32 wavLength2;
    Uint8 *wavBuffer2;
    SDL_LoadWAV("YouFucked.wav",&wavSpec2,&wavBuffer2,&wavLength2);
    SDL_AudioDeviceID deviceId2 = SDL_OpenAudioDevice(NULL,0,&wavSpec2,NULL,0);
    //
    //Loading Textures
    bar=IMG_LoadTexture(m_renderer,"BarBackground.bmp");
    lives=IMG_LoadTexture(m_renderer,"lives.bmp");
        GetReady=IMG_LoadTexture(m_renderer,"getready.bmp");
        level=IMG_LoadTexture(m_renderer,"Level 2.bmp");
                No1=IMG_LoadTexture(m_renderer,"1.bmp");
                                No2=IMG_LoadTexture(m_renderer,"2.bmp");
                                                No3=IMG_LoadTexture(m_renderer,"3.bmp");
                                                                No4=IMG_LoadTexture(m_renderer,"4.bmp");
                                                                                No5=IMG_LoadTexture(m_renderer,"5.bmp");
                                                                                                No6=IMG_LoadTexture(m_renderer,"6.bmp");
                                                                                                                No7=IMG_LoadTexture(m_renderer,"7.bmp");
                                                                                                                                No8=IMG_LoadTexture(m_renderer,"8.bmp");
                                                                                                                                                No9=IMG_LoadTexture(m_renderer,"9.bmp");
                                                                                                                                                                No0=IMG_LoadTexture(m_renderer,"0.bmp");
                                                                                                                                                                                     Pause=IMG_LoadTexture(m_renderer,"pause.bmp");
                                                                                                                                                                                                  img_brick=IMG_LoadTexture(m_renderer,"BrickTransparent.bmp");
                                                                                                                                                                                                           bomb=IMG_LoadTexture(m_renderer,"bomb.bmp");

    switch(bckg)
    {
    case 1:
            img_bckg=IMG_LoadTexture(m_renderer,"red.jpg");
            break;
    case 2:
            img_bckg=IMG_LoadTexture(m_renderer,"green.jpg");
            break;
    case 3:
            img_bckg=IMG_LoadTexture(m_renderer,"blue.jpg");
            break;
    }
        switch(ball)
    {
    case 1:
    img_ball=IMG_LoadTexture(m_renderer,"FootBall.bmp");
            break;
    case 2:
    img_ball=IMG_LoadTexture(m_renderer,"BasketBall.bmp");
            break;
    case 3:
    img_ball=IMG_LoadTexture(m_renderer,"BaseBall.bmp");
            break;
    }
    img_pltfrm=IMG_LoadTexture(m_renderer,"platform.bmp");
    //Loading Background
    SDL_Rect Textr_bckg;
    Textr_bckg.x=0;
    Textr_bckg.y=0;
    Textr_bckg.w=1200;
    Textr_bckg.h=800;
    SDL_RenderCopy(m_renderer,img_bckg,NULL,&Textr_bckg);
    SDL_RenderPresent(m_renderer);
    //Loading Background
        //Loading Ball
    SDL_Rect Textr_ball;
    Textr_ball.x=BallX;
    Textr_ball.y=BallY;
    Textr_ball.w=BallR;
    Textr_ball.h=BallR;
    SDL_RenderCopy(m_renderer,img_ball,NULL,&Textr_ball);
    //Loading Ball
    //Loading Platform
    SDL_Rect Textr_pltfrm;
    Textr_pltfrm.x=PlatformX;
    Textr_pltfrm.y=PlatformY;
    Textr_pltfrm.w=PlatformL;
    Textr_pltfrm.h=PlatformH;
    SDL_RenderCopy(m_renderer,img_pltfrm,NULL,&Textr_pltfrm);
    //Loading Platform

            for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
            if(brick[x][y].type>0){
                    if(bckg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(bckg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(bckg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250*brick[x][y].type/ilevel),1);
                    }
                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
            }
        }
    }


        SDL_Rect Textr_bar;
    Textr_bar.x=0;
    Textr_bar.y=0;
    Textr_bar.w=228;
    Textr_bar.h=30;
    SDL_RenderCopy(m_renderer,bar,NULL,&Textr_bar);

        SDL_Rect Textr_lives;
    Textr_lives.x=0;
    Textr_lives.y=3;
    Textr_lives.w=45;
    Textr_lives.h=23;
    SDL_RenderCopy(m_renderer,lives,NULL,&Textr_lives);


        SDL_Rect Textr_level;
    Textr_level.x=100;
    Textr_level.y=3;
    Textr_level.w=47;
    Textr_level.h=23;
    SDL_RenderCopy(m_renderer,level,NULL,&Textr_level);


    switch(live_s)
    {
        case 1:

    SDL_Rect Textr_1;
    Textr_1.x=47;
    Textr_1.y=3;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);

    break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=47;
    Textr_2.y=3;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=47;
    Textr_3.y=3;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
    }




        SDL_RenderPresent(m_renderer);
                SDL_Event *event = new SDL_Event();
const Uint8 *state =SDL_GetKeyboardState(NULL);
while(!state[SDL_SCANCODE_SPACE])
{
    SDL_PollEvent(event);
}



            ///



bool isrunnin=1;
    while(isrunnin)
    {
    if(!state[SDL_SCANCODE_ESCAPE])
        {

if(!SDL_PollEvent(event)){
        if(!(BallX>0)&&(BallX<1200-BallR)&&(BallY<PlatformY-BallR)&&(BallY>0))
        {
            isrunnin=0;
        }
        else
        {
            //Setting Changes
            BallX+=Vx;
            BallY+=Vy;
            if(BallY<=1)
            {
                                int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
                Vy=-Vy;
            }


        for(int y=0;y<sight;y++)
    {
        for(int x=0;x<6;x++)
        {
            if(brick[x][y].type!=0){
     if(BallY<=brick[x][y].y+40&&BallY>=brick[x][y].y)
     {
         if(BallX>=brick[x][y].x-BallR-1&&BallX<=brick[x][y].x+150)
         {
                                             int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
             Vy=-Vy;
             int d=damage;
             int s=brick[x][y].type;
                          damage=d-s;
                                      brick[x][y].type=s-d;
             if(brick[x][y].type<=0)
             {
                 brick[x][y].type=0;
             }
             if(damage<=0)
             {
                 SDL_Delay(1);
                                      PlatformX=525;
PlatformY=770;
BallX=PlatformX+PlatformL/2-BallR/2;
BallY=PlatformY-BallR;
                 ilevel++;
                 damage=ilevel;
                                  cout<<ilevel<<"\t"<<damage<<endl;
                          sight+=1;
                              for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=rand()%ilevel;
             if(brick[x][y].type==0)
             {
                 brick[x][y].type=1;
             }
        }
    }
        for(int y=sight;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=0;
        }

    }
             }
         }
     }
            }
        }

    }
 if(BallX<=1)
            {
                                int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
                Vx=-Vx;
            }
            if(BallX>=-BallR+1200-1)
            {
                int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
                Vx=-Vx;
            }
            if((BallY>=740))
            {
                           if((BallX>=PlatformX+5-BallR)&&(BallX<=PlatformX+PlatformL-5+BallR))
            {
                int hitplatform=SDL_QueueAudio(deviceId3,wavBuffer3,wavLength3);
                SDL_PauseAudioDevice(deviceId3,0);
                Vy=-Vy;
                if(counter%2==0){
                Vx+=double((rand()%100)/1000.000000);}
                else{
                     Vx-=double((rand()%100)/1000.000000);
                }
            }


            else
                {
                if(live_s>1)
                {
                        SDL_Rect Textr_pltfrm;
                    live_s--;
                    isrunnin=1;
                     PlatformX=525;
PlatformY=770;
BallX=PlatformX+PlatformL/2-BallR/2;
BallY=PlatformY-BallR;
int originy=-608;
        SDL_Texture *p;
    int w,h;
    p =IMG_LoadTexture(m_renderer,"choobmenu.bmp");
while(originy<=0)
{
    originy++;
        //Loading Background
    SDL_Rect Textr_bckg;
    Textr_bckg.x=0;
    Textr_bckg.y=0;
    Textr_bckg.w=1200;
    Textr_bckg.h=800;
    SDL_RenderCopy(m_renderer,img_bckg,NULL,&Textr_bckg);

    //Loading Background
        //Loading Ball
    SDL_Rect Textr_ball;
    Textr_ball.x=BallX;
    Textr_ball.y=BallY;
    Textr_ball.w=BallR;
    Textr_ball.h=BallR;
    SDL_RenderCopy(m_renderer,img_ball,NULL,&Textr_ball);
    //Loading Ball
    //Loading Platform
    SDL_Rect Textr_pltfrm;
    Textr_pltfrm.x=PlatformX;
    Textr_pltfrm.y=PlatformY;
    Textr_pltfrm.w=PlatformL;
    Textr_pltfrm.h=PlatformH;
    SDL_RenderCopy(m_renderer,img_pltfrm,NULL,&Textr_pltfrm);
    //Loading Platform

            for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
            if(brick[x][y].type!=0){
                    if(bckg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(bckg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(bckg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250*brick[x][y].type/ilevel),1);
                    }
                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
            }

        }
    }
    SDL_QueryTexture(p,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=280;
    textrP.y=originy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(m_renderer,p,NULL,&textrP);
                    SDL_Rect Textr_pause;
    Textr_pause.x=470;
    Textr_pause.y=440+originy;
    Textr_pause.w=216;
    Textr_pause.h=90;
    SDL_RenderCopy(m_renderer,Pause,NULL,&Textr_pause);

        SDL_Rect Textr_bar;
    Textr_bar.x=0;
    Textr_bar.y=0;
    Textr_bar.w=228;
    Textr_bar.h=30;
    SDL_RenderCopy(m_renderer,bar,NULL,&Textr_bar);

        SDL_Rect Textr_lives;
    Textr_lives.x=0;
    Textr_lives.y=3;
    Textr_lives.w=45;
    Textr_lives.h=23;
    SDL_RenderCopy(m_renderer,lives,NULL,&Textr_lives);


        SDL_Rect Textr_level;
    Textr_level.x=100;
    Textr_level.y=3;
    Textr_level.w=47;
    Textr_level.h=23;
    SDL_RenderCopy(m_renderer,level,NULL,&Textr_level);


    switch(live_s)
    {
        case 1:

    SDL_Rect Textr_1;
    Textr_1.x=47;
    Textr_1.y=3;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);

    break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=47;
    Textr_2.y=3;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=47;
    Textr_3.y=3;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
    }


    SDL_RenderPresent(m_renderer);
    SDL_Delay(1);
}

    while(!state[SDL_SCANCODE_SPACE])
{
    SDL_PollEvent(event);
}

                }
                else if(live_s<=1){isrunnin=0;}
                }
            }






                //Loading Background
    SDL_Rect Textr_bckg;
    Textr_bckg.x=0;
    Textr_bckg.y=0;
    Textr_bckg.w=1200;
    Textr_bckg.h=800;
    SDL_RenderCopy(m_renderer,img_bckg,NULL,&Textr_bckg);
    //Loading Background
    //Loading Ball
    SDL_Rect Textr_ball;
    Textr_ball.x=BallX;
    Textr_ball.y=BallY;
    Textr_ball.w=BallR;
    Textr_ball.h=BallR;
    SDL_RenderCopy(m_renderer,img_ball,NULL,&Textr_ball);
    //Loading Ball
        //Loading Platform
    SDL_Rect Textr_pltfrm;
    Textr_pltfrm.x=PlatformX;
    Textr_pltfrm.y=PlatformY;
    Textr_pltfrm.w=PlatformL;
    Textr_pltfrm.h=PlatformH;
    SDL_RenderCopy(m_renderer,img_pltfrm,NULL,&Textr_pltfrm);
    //Loading Platform

            for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
            if(brick[x][y].type>0){
                    if(bckg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(bckg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(bckg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250*brick[x][y].type/ilevel),1);
                    }

                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
            }

        }
    }





        SDL_Rect Textr_bar;
    Textr_bar.x=0;
    Textr_bar.y=0;
    Textr_bar.w=228;
    Textr_bar.h=30;
    SDL_RenderCopy(m_renderer,bar,NULL,&Textr_bar);

        SDL_Rect Textr_lives;
    Textr_lives.x=0;
    Textr_lives.y=3;
    Textr_lives.w=45;
    Textr_lives.h=23;
    SDL_RenderCopy(m_renderer,lives,NULL,&Textr_lives);


        SDL_Rect Textr_level;
    Textr_level.x=100;
    Textr_level.y=3;
    Textr_level.w=47;
    Textr_level.h=23;
    SDL_RenderCopy(m_renderer,level,NULL,&Textr_level);


    switch(live_s)
    {
        case 1:

    SDL_Rect Textr_1;
    Textr_1.x=47;
    Textr_1.y=3;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);

    break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=47;
    Textr_2.y=3;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=47;
    Textr_3.y=3;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
    }


    //Presenting
        SDL_RenderPresent(m_renderer);
            //Presenting
        }
//        SDL_Delay(1);
}



else
    {










                if(state[SDL_SCANCODE_LEFT])
            {
                PlatformX-=40;
            }
            if(state[SDL_SCANCODE_RIGHT])
            {
                PlatformX+=40;
            }
}
        }
        else{

int originy=-608;
        SDL_Texture *p;
    int w,h;
    p =IMG_LoadTexture(m_renderer,"choobmenu.bmp");
while(originy<=0)
{
    originy++;
        //Loading Background
    SDL_Rect Textr_bckg;
    Textr_bckg.x=0;
    Textr_bckg.y=0;
    Textr_bckg.w=1200;
    Textr_bckg.h=800;
    SDL_RenderCopy(m_renderer,img_bckg,NULL,&Textr_bckg);
    //Loading Background
        //Loading Ball
    SDL_Rect Textr_ball;
    Textr_ball.x=BallX;
    Textr_ball.y=BallY;
    Textr_ball.w=BallR;
    Textr_ball.h=BallR;
    SDL_RenderCopy(m_renderer,img_ball,NULL,&Textr_ball);
    //Loading Ball
    //Loading Platform
    SDL_Rect Textr_pltfrm;
    Textr_pltfrm.x=PlatformX;
    Textr_pltfrm.y=PlatformY;
    Textr_pltfrm.w=PlatformL;
    Textr_pltfrm.h=PlatformH;
    SDL_RenderCopy(m_renderer,img_pltfrm,NULL,&Textr_pltfrm);
    //Loading Platform

            for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
            if(brick[x][y].type!=0){
                    if(bckg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(bckg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(bckg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250*brick[x][y].type/ilevel),1);
                    }
                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
            }

        }
    }
    SDL_QueryTexture(p,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=280;
    textrP.y=originy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(m_renderer,p,NULL,&textrP);
                    SDL_Rect Textr_pause;
    Textr_pause.x=470;
    Textr_pause.y=440+originy;
    Textr_pause.w=216;
    Textr_pause.h=90;
    SDL_RenderCopy(m_renderer,Pause,NULL,&Textr_pause);

        SDL_Rect Textr_bar;
    Textr_bar.x=0;
    Textr_bar.y=0;
    Textr_bar.w=228;
    Textr_bar.h=30;
    SDL_RenderCopy(m_renderer,bar,NULL,&Textr_bar);

        SDL_Rect Textr_lives;
    Textr_lives.x=0;
    Textr_lives.y=3;
    Textr_lives.w=45;
    Textr_lives.h=23;
    SDL_RenderCopy(m_renderer,lives,NULL,&Textr_lives);


        SDL_Rect Textr_level;
    Textr_level.x=100;
    Textr_level.y=3;
    Textr_level.w=47;
    Textr_level.h=23;
    SDL_RenderCopy(m_renderer,level,NULL,&Textr_level);


    switch(live_s)
    {
        case 1:

    SDL_Rect Textr_1;
    Textr_1.x=47;
    Textr_1.y=3;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);

    break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=47;
    Textr_2.y=3;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=47;
    Textr_3.y=3;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
    }


    SDL_RenderPresent(m_renderer);
    SDL_Delay(1);
}


        while(!state[SDL_SCANCODE_SPACE])
        {
            SDL_PollEvent(event);

        }

       }





    }
    //Destory
                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                IMG_Quit();
                SDL_Quit();
                return 0;
    //Destory
}
void DrawRect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)
    SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);

}
