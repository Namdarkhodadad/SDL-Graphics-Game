#include <iostream>
#include<fstream>
#include<sstream>
#include<ostream>
#include<string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfx.h>
#include <math.h>
#include <SDL2/SDL_audio.h>
#include <windows.h>
//Ali Nikkhah
//Namdar Khodadad
using namespace std;
void ColorWindow(SDL_Renderer *Renderer, int R, int G, int B);
void DrawRect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void DrawEllipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void print_one_digit(SDL_Renderer *renderer,int X,int Y,int R,int Re,int G,int B);
void Fillbackground(SDL_Renderer *Renderer, int backg);
void Drawball(SDL_Renderer *Renderer, int ball);
void Drawplatform(SDL_Renderer *Renderer);
void menugoup(SDL_Renderer *Renderer);
void menugodown(SDL_Renderer *Renderer);
void showmenu(SDL_Renderer *Renderer);
void optiongoup(SDL_Renderer *Renderer);
void optiongodown(SDL_Renderer *Renderer);
void showoption(SDL_Renderer *Renderer);
//Define
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
SDL_Texture* scoreboard;
int counter=0;
int n=0;
int BallR=35;
int PlatformL=200;
int PlatformH=20;
int PlatformX=525;
int PlatformY=770;
double BallX=double(PlatformX+PlatformL/2-BallR/2);
double BallY=double(PlatformY-BallR);
int backg=1;
int ball=2;
int mousex,mousex1;
int mousey,mousey1;
double Vx=0.1;
double Vy=-0.1;
struct bricks{
int type;
int x;
int y;
};
int sight=1;
int level1=1;
////nahayi
int main( int argc, char * argv[] )
{
    int score =0;
    int ilevel=2;
    int live_s=3;
    int damage=ilevel;
    //////////male save game////////////////
    fstream textinput;
    string esm;
    cout<<"PLEASE ENTER YOUR NAME"<<endl;
    cin>>esm;
    string name2=esm;
    esm=esm+".txt";
    textinput.open(esm.c_str());
    if (textinput.is_open())
    {
        cout<<"GAME HISTORY:"<<endl;
        ostringstream h;
        string text;
        h<<textinput.rdbuf();
        text =h.str();
        cout<<name2<<endl<<text<<endl;
        //////////////////
         string name1=name2+"scr.txt";
            fstream textinput1;
            textinput1.open(name1.c_str());
            ostringstream y;
            string texti;
            y<<textinput1.rdbuf();
            texti =y.str();
    string t[3][5];
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=4;j++)
        {
            t[i][j]="";
        }
    }
    int j=0,p=0;
    for(int i=0;i<texti.length();i++)
    {
        if(texti[i]=='$')
        {
            p++;
            j=-1;
        }
        if(texti[i]!='#'&&texti[i]!='$')
        {
            t[j][p]=t[j][p]+texti[i];
        }
        else
        {
           j++;
        }
    }
     //////////////////////
        cout<<"WHICH GAME WOULD YOU LIKE TO PLAY?"<<endl;
        int vaz;
//        int live_s;
//        int score;
//        int ilevel;
        stringstream kk0,kk1,kk2;
        cin>>vaz;
        switch(vaz)
        {
    case 1:
        kk0<<t[0][0];
        kk1<<t[1][0];
        kk2<<t[2][0];
        kk2>>live_s;
        kk1>>ilevel;
        kk0>>score;
        break;
    case 2:
        kk0<<t[0][1];
        kk1<<t[1][1];
        kk2<<t[2][1];
        kk2>>live_s;
        kk1>>ilevel;
        kk0>>score;
        break;
    case 3:
        kk0<<t[0][2];
        kk1<<t[1][2];
        kk2<<t[2][2];
        kk2>>live_s;
        kk1>>ilevel;
        kk0>>score;
        break;
    case 4:
        kk0<<t[0][3];
        kk1<<t[1][3];
        kk2<<t[2][3];
        kk2>>live_s;
        kk1>>ilevel;
        kk0>>score;
        break;
    case 5:
        kk0<<t[0][4];
        kk1<<t[1][4];
        kk2<<t[2][4];
        kk2>>live_s;
        kk1>>ilevel;
        kk0>>score;
        break;
        }
        cout<<score<<" "<<ilevel<<" "<<live_s<<endl;
      cout<<"starting game"<<endl;
    }
    else
    {
        string newname=name2+"scr.txt";
        string newtext="0#1#3$0#1#3$0#1#3$0#1#3$0#1#3";
        ofstream outfile(newname.c_str());
        outfile<<newtext;
        outfile.close();
        string newname1=name2+".txt";
        string newtext1="";
        ofstream outfile2(newname1.c_str());
        outfile2<<newtext1;
        outfile2.close();
        cout<<"LET'S START A NEW GAME!"<<endl;
    }
    /////////////////////////////////
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1200, 800, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    Fillbackground(m_renderer,backg);
    SDL_RenderPresent(m_renderer);
    int menu=0,menux=320,menuy=0;
    showmenu(m_renderer);
      SDL_Event *event=new SDL_Event();
      while(1)
      {
       event->type=0;
       SDL_PollEvent(event);
       if(event->type==SDL_MOUSEBUTTONDOWN)
       {
           mousex=event->motion.x;
           mousey=event->motion.y;
       }
           if(mousex>=550&&mousex<=710&&mousey>=390&&mousey<=435&&menu==0)
           {
               //start
               menugoup(m_renderer);
               menu=1;
               Drawball(m_renderer,ball);
               Drawplatform(m_renderer);
               SDL_RenderPresent(m_renderer);

               ////////////////
               SDL_Init(SDL_INIT_AUDIO);
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
//////////////////
        int i=25;
    int j=20;
   struct bricks brick[6][12];
    for(int y=0;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=(rand()%ilevel);
                          if(brick[x][y].type==0)
             {
                 if(rand()%4==0)
                 {
                              brick[x][y].type=-1;
                 }
                 else if(rand()%5 ==0){
                                     brick[x][y].type=0;
                 }
                 else{
                                                         brick[x][y].type=1;
                 }
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
    //////////////////////
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
                                                                                                                                                                                                                 scoreboard=IMG_LoadTexture(m_renderer,"scoreboard.bmp");
    switch(backg)
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
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(backg==3)
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
                        if(brick[x][y].type==-1){
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250),0,1);
                    }
                    else if(backg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250),1);
                    }
                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
                    SDL_Rect Textr_bomb;
    Textr_bomb.x= brick[x][y].x+55;
    Textr_bomb.y=brick[x][y].y;
    Textr_bomb.w=40;
    Textr_bomb.h=40;
    SDL_RenderCopy(m_renderer,bomb,NULL,&Textr_bomb);
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
    int n=ilevel-1;
    int digit=0;
    int cpy=n;
    while(cpy>0)
    {
        cpy/=10;
        digit++;
    }
    int x=170;
    int y=5;
    while(digit>0)
    {
        int tmp=((n/int(pow(10,digit-1)))%10);
        switch (tmp)
        {
        case 1:
                SDL_Rect Textr_1;
    Textr_1.x=x;
    Textr_1.y=y;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);
break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=x;
    Textr_2.y=y;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=x;
    Textr_3.y=y;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
                    case 4:
    SDL_Rect Textr_4;
    Textr_4.x=x;
    Textr_4.y=y;
    Textr_4.w=11;
    Textr_4.h=17;
    SDL_RenderCopy(m_renderer,No4,NULL,&Textr_4);
    break;
                    case 5:
    SDL_Rect Textr_5;
    Textr_5.x=x;
    Textr_5.y=y;
    Textr_5.w=11;
    Textr_5.h=17;
    SDL_RenderCopy(m_renderer,No5,NULL,&Textr_5);
    break;
                    case 6:
    SDL_Rect Textr_6;
    Textr_6.x=x;
    Textr_6.y=y;
    Textr_6.w=11;
    Textr_6.h=17;
    SDL_RenderCopy(m_renderer,No6,NULL,&Textr_6);
    break;
                    case 7:
    SDL_Rect Textr_7;
    Textr_7.x=x;
    Textr_7.y=y;
    Textr_7.w=11;
    Textr_7.h=17;
    SDL_RenderCopy(m_renderer,No7,NULL,&Textr_7);
    break;
                    case 8:
    SDL_Rect Textr_8;
    Textr_8.x=x;
    Textr_8.y=y;
    Textr_8.w=11;
    Textr_8.h=17;
    SDL_RenderCopy(m_renderer,No8,NULL,&Textr_8);
    break;
                    case 9:
    SDL_Rect Textr_9;
    Textr_9.x=x;
    Textr_9.y=y;
    Textr_9.w=11;
    Textr_9.h=17;
    SDL_RenderCopy(m_renderer,No9,NULL,&Textr_9);
    break;
                    case 0:
    SDL_Rect Textr_0;
    Textr_0.x=x;
    Textr_0.y=y;
    Textr_0.w=11;
    Textr_0.h=17;
    SDL_RenderCopy(m_renderer,No0,NULL,&Textr_0);
    break;
        }
        digit--;
        x+=12;
    }


        SDL_RenderPresent(m_renderer);
                SDL_Event *event = new SDL_Event();
const Uint8 *state =SDL_GetKeyboardState(NULL);
while(!state[SDL_SCANCODE_SPACE])
{
    SDL_PollEvent(event);
}

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
            if(brick[x][y].type>0){
     if(BallY<=brick[x][y].y+40&&BallY>=brick[x][y].y)
     {
         if(BallX>=brick[x][y].x-BallR-1&&BallX<=brick[x][y].x+150)
         {
                                             int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
             Vy=-Vy;
             int d=damage;
             int s=brick[x][y].type;
             if(ilevel>=3)
             {
                                     damage=d-s;
             }
             else{damage=d-s;}

                                      brick[x][y].type=s-d;
             if(brick[x][y].type<=0)
             {
                 brick[x][y].type=0;
                 score+=ilevel;
             }

             if(damage<=0)
             {
                 if(Vy<0)
                 {
                               Vy-=0.02;
                 }
                 else{
                                           Vy+=0.02;
                 }

    POINT mouse;
    GetCursorPos(&mouse);
     PlatformX=mouse.x-500;
BallX=PlatformX+PlatformL/2-BallR/2;
BallY=PlatformY-BallR;
                 ilevel++;
                 damage=ilevel;
                          sight+=1;
                          if(sight>=13)
                          {
                              bool isfucked=1;
                              for(int ii=0;ii<6;ii++)
                              {
                                  if(brick[ii][12].type>0)
                                  {
                                      isfucked=0;
                                  }
                              }
                              if(!isfucked){
    //avvalin int tu voroodi tabe score,bad level,bad lives//
       string name1=name2+"scr.txt";
            fstream textinput1;
            textinput1.open(name1.c_str());
            ostringstream y;
            string texti;
            y<<textinput1.rdbuf();
            texti =y.str();
    string t[3][5];
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=4;j++)
        {
            t[i][j]="";
        }
    }
    int j=0,p=0;
    for(int i=0;i<texti.length();i++)
    {
        if(texti[i]=='$')
        {
            p++;
            j=-1;
        }
        if(texti[i]!='#'&&texti[i]!='$')
        {
            t[j][p]=t[j][p]+texti[i];
        }
        else
        {
           j++;
        }
    }
          int z,c;
          int xx;
          z=score;
          xx=ilevel;
          c=live_s;
          stringstream ss0,ss1,ss2;
          ss0<<z;
          ss1<<xx;
          ss2<<c;
          string temp0,temp1,temp2;
          ss0>>temp0;
          ss1>>temp1;
          ss2>>temp2;
          for(int f=4;f>0;f--)
          {
             t[0][f]=t[0][f-1];
             t[1][f]=t[1][f-1];
             t[2][f]=t[2][f-1];
          }
          t[0][0]=temp0;
          t[1][0]=temp1;
          t[2][0]=temp2;
texti="";
    texti=t[0][0]+'#'+t[1][0]+'#'+t[2][0];
    string texti1="GAME 1= "+t[0][0];
    for(int q=1;q<=4;q++)
    {
        stringstream boom;
        boom<<q+1;
        string boom1;
        boom>>boom1;
        texti=texti+'$'+t[0][q]+'#'+t[1][q]+'#'+t[2][q];
        texti1=texti1+"||||"+"GAME "+boom1+"= "+t[0][q];
    }
        ofstream outfile(name1.c_str());
        outfile<<texti;
        outfile.close();
        ofstream outfile1(esm.c_str());
        outfile1<<texti1;
        outfile1.close();
                                                return 0;}
                              else{
                                sight =1;
                              }
                          }
                              for(int y=sight-1;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=rand()%ilevel;
             if(rand()%20==0)
             {
                              brick[x][y].type=0;
             }
                          if(brick[x][y].type==0)
             {
                 if(rand()%2==0)
                 {
                              brick[x][y].type=-1;
                 }
                 else if(rand()%5==0){
                                     brick[x][y].type=1;
                 }
                 else{  brick[x][y].type=0;}
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

            else if(brick[x][y].type==-1)
{
     if(BallY<=brick[x][y].y+40&&BallY>=brick[x][y].y)
     {
         if(BallX>=brick[x][y].x-BallR-1&&BallX<=brick[x][y].x+150)
         {
                                             int hit=SDL_QueueAudio(deviceId,wavBuffer,wavLength);
                SDL_PauseAudioDevice(deviceId,0);
             Vy=-Vy;
                          int d=damage;
             int s=ilevel;

                                     damage=d-s;

             for(int u=0;u<6;u++)
             {
                 brick[u][y].type=0;
             }
                  if(brick[x][y].type<=0)
             {
                 brick[x][y].type=0;
                 score+=ilevel;

             }

             if(damage<=0)
             {
                 if(Vy<0)
                 {
                               Vy-=0.02;
                 }
                 else{
                                           Vy+=0.02;
                 }

    POINT mouse;
    GetCursorPos(&mouse);


     PlatformX=mouse.x-500;

BallX=PlatformX+PlatformL/2-BallR/2;
BallY=PlatformY-BallR;

                 ilevel++;
                 damage=ilevel;
                          sight+=1;
                          if(sight>=13)
                          {
                              bool isfucked=1;
                              for(int ii=0;ii<6;ii++)
                              {
                                  if(brick[sight][ii].type>0)
                                  {
                                      isfucked=0;
                                  }
                              }
                              if(!isfucked){

    //avvalin int tu voroodi tabe score,bad level,bad lives//
       string name1=name2+"scr.txt";
            fstream textinput1;
            textinput1.open(name1.c_str());
            ostringstream y;
            string texti;
            y<<textinput1.rdbuf();
            texti =y.str();
    string t[3][5];
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=4;j++)
        {
            t[i][j]="";
        }
    }
    int j=0,p=0;
    for(int i=0;i<texti.length();i++)
    {
        if(texti[i]=='$')
        {
            p++;
            j=-1;
        }
        if(texti[i]!='#'&&texti[i]!='$')
        {
            t[j][p]=t[j][p]+texti[i];
        }
        else
        {
           j++;
        }
    }
          int z,c;
          int xx;
          z=score;
          xx=ilevel;
          c=live_s;
          stringstream ss0,ss1,ss2;
          ss0<<z;
          ss1<<xx;
          ss2<<c;
          string temp0,temp1,temp2;
          ss0>>temp0;
          ss1>>temp1;
          ss2>>temp2;
          for(int f=4;f>0;f--)
          {
             t[0][f]=t[0][f-1];
             t[1][f]=t[1][f-1];
             t[2][f]=t[2][f-1];
          }
          t[0][0]=temp0;
          t[1][0]=temp1;
          t[2][0]=temp2;
texti="";
    texti=t[0][0]+'#'+t[1][0]+'#'+t[2][0];
    string texti1="GAME 1= "+t[0][0];
    for(int q=1;q<=4;q++)
    {
        stringstream boom;
        boom<<q+1;
        string boom1;
        boom>>boom1;
        texti=texti+'$'+t[0][q]+'#'+t[1][q]+'#'+t[2][q];
        texti1=texti1+"||||"+"GAME "+boom1+"= "+t[0][q];
    }
        ofstream outfile(name1.c_str());
        outfile<<texti;
        outfile.close();
        ofstream outfile1(esm.c_str());
        outfile1<<texti1;
        outfile1.close();
//                                                                                  void save(m_renderer,score,level,lives,name2,esm);
                                        return 0;}

                          }
                              for(int y=sight-1;y<12;y++)
    {
        for(int x=0;x<6;x++)
        {
             brick[x][y].type=rand()%ilevel;
             if(rand()%20==0)
             {
                              brick[x][y].type=0;
             }
                          if(brick[x][y].type==0)
             {
                 if(rand()%6==0)
                 {
                              brick[x][y].type=-1;
                 }
                 else{
                                     brick[x][y].type=0;
                 }
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

         }}
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
                           if((BallX>=PlatformX-BallR-1)&&(BallX<=PlatformX+PlatformL+BallR+1))
            {
                int hitplatform=SDL_QueueAudio(deviceId3,wavBuffer3,wavLength3);
                SDL_PauseAudioDevice(deviceId3,0);
                Vy=-Vy;
                Vx=((BallX+BallR/2-PlatformX-PlatformL/2)*2/PlatformL)*0.1;
            }


            else
                {
                if(live_s>1)
                {
                        POINT mouse;
    GetCursorPos(&mouse);

     PlatformX=mouse.x-500;

BallX=PlatformX+PlatformL/2-BallR/2;
BallY=PlatformY-BallR;

                        SDL_Rect Textr_pltfrm;
                    live_s--;
                    isrunnin=1;
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
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(backg==3)
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

    int n=ilevel-1;
    int digit=0;
    int cpy=n;
    while(cpy>0)
    {
        cpy/=10;
        digit++;
    }
    int x=170;
    int y=5;
    while(digit>0)
    {
        int tmp=((n/int(pow(10,digit-1)))%10);
        switch (tmp)
        {
        case 1:
                SDL_Rect Textr_1;
    Textr_1.x=x;
    Textr_1.y=y;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);
break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=x;
    Textr_2.y=y;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=x;
    Textr_3.y=y;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
                    case 4:
    SDL_Rect Textr_4;
    Textr_4.x=x;
    Textr_4.y=y;
    Textr_4.w=11;
    Textr_4.h=17;
    SDL_RenderCopy(m_renderer,No4,NULL,&Textr_4);
    break;
                    case 5:
    SDL_Rect Textr_5;
    Textr_5.x=x;
    Textr_5.y=y;
    Textr_5.w=11;
    Textr_5.h=17;
    SDL_RenderCopy(m_renderer,No5,NULL,&Textr_5);
    break;
                    case 6:
    SDL_Rect Textr_6;
    Textr_6.x=x;
    Textr_6.y=y;
    Textr_6.w=11;
    Textr_6.h=17;
    SDL_RenderCopy(m_renderer,No6,NULL,&Textr_6);
    break;
                    case 7:
    SDL_Rect Textr_7;
    Textr_7.x=x;
    Textr_7.y=y;
    Textr_7.w=11;
    Textr_7.h=17;
    SDL_RenderCopy(m_renderer,No7,NULL,&Textr_7);
    break;
                    case 8:
    SDL_Rect Textr_8;
    Textr_8.x=x;
    Textr_8.y=y;
    Textr_8.w=11;
    Textr_8.h=17;
    SDL_RenderCopy(m_renderer,No8,NULL,&Textr_8);
    break;
                    case 9:
    SDL_Rect Textr_9;
    Textr_9.x=x;
    Textr_9.y=y;
    Textr_9.w=11;
    Textr_9.h=17;
    SDL_RenderCopy(m_renderer,No9,NULL,&Textr_9);
    break;
                    case 0:
    SDL_Rect Textr_0;
    Textr_0.x=x;
    Textr_0.y=y;
    Textr_0.w=11;
    Textr_0.h=17;
    SDL_RenderCopy(m_renderer,No0,NULL,&Textr_0);
    break;
        }
        digit--;
        x+=12;
    }
        SDL_Rect Textr_scoreboard;
    Textr_scoreboard.x=475;
    Textr_scoreboard.y=0+originy;
    Textr_scoreboard.w=250;
    Textr_scoreboard.h=110;
    SDL_RenderCopy(m_renderer,scoreboard,NULL,&Textr_scoreboard);

     n=score;
     digit=0;
     cpy=n;
    while(cpy>0)
    {
        cpy/=10;
        digit++;
    }
     x=475+25;
     y=35;
    while(digit>0)
    {
        int tmp=((n/int(pow(10,digit-1)))%10);
        switch (tmp)
        {
        case 1:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
break;
            case 2:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                case 3:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 4:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 5:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 6:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 7:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 8:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 9:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 0:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
        }
        digit--;
        x+=75;
    }
/////
    //avvalin int tu voroodi tabe score,bad level,bad lives//
       string name1=name2+"scr.txt";
            fstream textinput1;
            textinput1.open(name1.c_str());
            ostringstream yy;
            string texti;
            yy<<textinput1.rdbuf();
            texti =yy.str();
    string t[3][5];
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=4;j++)
        {
            t[i][j]="";
        }
    }
    int j=0,p=0;
    for(int i=0;i<texti.length();i++)
    {
        if(texti[i]=='$')
        {
            p++;
            j=-1;
        }
        if(texti[i]!='#'&&texti[i]!='$')
        {
            t[j][p]=t[j][p]+texti[i];
        }
        else
        {
           j++;
        }
    }
          int z,c;
          int xx;
          z=score;
          xx=ilevel;
          c=live_s;
          stringstream ss0,ss1,ss2;
          ss0<<z;
          ss1<<xx;
          ss2<<c;
          string temp0,temp1,temp2;
          ss0>>temp0;
          ss1>>temp1;
          ss2>>temp2;
          for(int f=4;f>0;f--)
          {
             t[0][f]=t[0][f-1];
             t[1][f]=t[1][f-1];
             t[2][f]=t[2][f-1];
          }
          t[0][0]=temp0;
          t[1][0]=temp1;
          t[2][0]=temp2;
texti="";
    texti=t[0][0]+'#'+t[1][0]+'#'+t[2][0];
    string texti1="GAME 1= "+t[0][0];
    for(int q=1;q<=4;q++)
    {
        stringstream boom;
        boom<<q+1;
        string boom1;
        boom>>boom1;
        texti=texti+'$'+t[0][q]+'#'+t[1][q]+'#'+t[2][q];
        texti1=texti1+"||||"+"GAME "+boom1+"= "+t[0][q];
    }
        ofstream outfile(name1.c_str());
        outfile<<texti;
        outfile.close();
        ofstream outfile1(esm.c_str());
        outfile1<<texti1;
        outfile1.close();
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
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(backg==3)
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
                                    if(brick[x][y].type==-1){
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250),0,1);
                    }
                    else if(backg==3)
                    {
                          DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,0,double(250),1);
                    }
                SDL_Rect Textr_brick;
    Textr_brick.x= brick[x][y].x;
    Textr_brick.y=brick[x][y].y;
    Textr_brick.w=150;
    Textr_brick.h=40;
    SDL_RenderCopy(m_renderer,img_brick,NULL,&Textr_brick);
                    SDL_Rect Textr_bomb;
    Textr_bomb.x= brick[x][y].x+55;
    Textr_bomb.y=brick[x][y].y;
    Textr_bomb.w=40;
    Textr_bomb.h=40;
    SDL_RenderCopy(m_renderer,bomb,NULL,&Textr_bomb);
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
    int n=ilevel-1;
    int digit=0;
    int cpy=n;
    while(cpy>0)
    {
        cpy/=10;
        digit++;
    }
    int x=170;
    int y=5;
    while(digit>0)
    {
        int tmp=((n/int(pow(10,digit-1)))%10);
        switch (tmp)
        {
        case 1:
                SDL_Rect Textr_1;
    Textr_1.x=x;
    Textr_1.y=y;
    Textr_1.w=7;
    Textr_1.h=17;
    SDL_RenderCopy(m_renderer,No1,NULL,&Textr_1);
break;
            case 2:
    SDL_Rect Textr_2;
    Textr_2.x=x;
    Textr_2.y=y;
    Textr_2.w=11;
    Textr_2.h=17;
    SDL_RenderCopy(m_renderer,No2,NULL,&Textr_2);
    break;
                case 3:
    SDL_Rect Textr_3;
    Textr_3.x=x;
    Textr_3.y=y;
    Textr_3.w=11;
    Textr_3.h=17;
    SDL_RenderCopy(m_renderer,No3,NULL,&Textr_3);
    break;
                    case 4:
    SDL_Rect Textr_4;
    Textr_4.x=x;
    Textr_4.y=y;
    Textr_4.w=11;
    Textr_4.h=17;
    SDL_RenderCopy(m_renderer,No4,NULL,&Textr_4);
    break;
                    case 5:
    SDL_Rect Textr_5;
    Textr_5.x=x;
    Textr_5.y=y;
    Textr_5.w=11;
    Textr_5.h=17;
    SDL_RenderCopy(m_renderer,No5,NULL,&Textr_5);
    break;
                    case 6:
    SDL_Rect Textr_6;
    Textr_6.x=x;
    Textr_6.y=y;
    Textr_6.w=11;
    Textr_6.h=17;
    SDL_RenderCopy(m_renderer,No6,NULL,&Textr_6);
    break;
                    case 7:
    SDL_Rect Textr_7;
    Textr_7.x=x;
    Textr_7.y=y;
    Textr_7.w=11;
    Textr_7.h=17;
    SDL_RenderCopy(m_renderer,No7,NULL,&Textr_7);
    break;
                    case 8:
    SDL_Rect Textr_8;
    Textr_8.x=x;
    Textr_8.y=y;
    Textr_8.w=11;
    Textr_8.h=17;
    SDL_RenderCopy(m_renderer,No8,NULL,&Textr_8);
    break;
                    case 9:
    SDL_Rect Textr_9;
    Textr_9.x=x;
    Textr_9.y=y;
    Textr_9.w=11;
    Textr_9.h=17;
    SDL_RenderCopy(m_renderer,No9,NULL,&Textr_9);
    break;
                    case 0:
    SDL_Rect Textr_0;
    Textr_0.x=x;
    Textr_0.y=y;
    Textr_0.w=11;
    Textr_0.h=17;
    SDL_RenderCopy(m_renderer,No0,NULL,&Textr_0);
    break;
        }
        digit--;
        x+=12;
    }

    //Presenting
        SDL_RenderPresent(m_renderer);
            //Presenting
        }
//        SDL_Delay(1);
}
else
    {
    POINT mouse;
    GetCursorPos(&mouse);
     PlatformX=mouse.x-500;
//                if(state[SDL_SCANCODE_LEFT])
//            {
//                PlatformX-=40;
//            }
//            if(state[SDL_SCANCODE_RIGHT])
//            {
//                PlatformX+=40;
//            }
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
                    if(backg==1)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,double(250*brick[x][y].type/ilevel),0,0,1);
                    }
                    else if(backg==2)
                    {
                                            DrawRect(m_renderer,brick[x][y].x,brick[x][y].y,150,40,0,double(250*brick[x][y].type/ilevel),0,1);
                    }
                    else if(backg==3)
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
    SDL_Rect Textr_scoreboard;
    Textr_scoreboard.x=475;
    Textr_scoreboard.y=0+originy;
    Textr_scoreboard.w=250;
    Textr_scoreboard.h=110;
    SDL_RenderCopy(m_renderer,scoreboard,NULL,&Textr_scoreboard);

     n=score;
     digit=0;
     cpy=n;
    while(cpy>0)
    {
        cpy/=10;
        digit++;
    }
    int x=475+25;
    int y=35;
    while(digit>0)
    {
        int tmp=((n/int(pow(10,digit-1)))%10);
        switch (tmp)
        {
        case 1:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
break;
            case 2:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                case 3:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 4:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 5:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 6:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 7:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 8:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 9:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
                    case 0:
print_one_digit(m_renderer,x,y+originy,tmp,250,0,0);
    break;
        }
        digit--;
        x+=75;
    }
/////


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
           //options
           if(mousex>=550&&mousex<=710&&mousey>=450&&mousey<=495&&menu==0)
           {
                menugoup(m_renderer);
                menu=1;
                optiongodown(m_renderer);
                SDL_Event *e=new SDL_Event();
      while(e->type!=SDL_KEYDOWN&&menu!=2)
      {
       e->type=0;
       SDL_PollEvent(e);
       if(e->type==SDL_MOUSEBUTTONDOWN)
       {
           mousex1=e->motion.x;
           mousey1=e->motion.y;
           cout<<mousex1<<" "<<mousey1<<" ";
           if(menu==1)
              {
                  //back
                  if(mousex1>=375&&mousex1<=415&&mousey1>=375&&mousey1<=415)
                  {
                      menu=2;
                  }
                  //ball option
                   if(mousex1>=550&&mousex1<=600&&mousey1>=380&&mousey1<=425)
                   {
                       ball=1;
                       //cout<<1<<" ";
                   }
                   if(mousex1>=630&&mousex1<=675&&mousey1>=380&&mousey1<=425)
                   {
                       ball=2;
                       //cout<<2<<" ";
                   }
                   if(mousex1>=710&&mousex1<=765&&mousey1>=380&&mousey1<=425)
                   {
                       ball=3;
                       //cout<<3<<" ";
                   }
                   //background option
                   if(mousex1>=610&&mousex1<=660&&mousey1>=445&&mousey1<=490)
                   {
                       backg=3;
                   }
                   if(mousex1>=680&&mousex1<=725&&mousey1>=445&&mousey1<=490)
                   {
                       backg=1;
                   }
                   if(mousex1>=750&&mousex1<=795&&mousey1>=445&&mousey1<=490)
                   {
                       backg=2;
                   }
                   //level option
                   if(mousex1>=560&&mousex1<=595&&mousey1>=530&&mousey1<=555)
                   {
                       level1=1;
                       BallR=40;
                       PlatformL=220;
                       Vy=-0.1;
                       Vx=0.1;
                   }
                   if(mousex1>=605&&mousex1<=650&&mousey1>=515&&mousey1<=555)
                   {
                       level1=2;
                       BallR=35;
                       PlatformL=200;
                       Vy=-0.12;
                       Vx=0.12;
                   }
                   if(mousex1>=665&&mousex1<=715&&mousey1>=515&&mousey1<=560)
                   {
                       level1=3;
                       BallR=30;
                       PlatformL=180;
                       Vy=-0.15;
                       Vx=0.15;
                   }
                   showoption(m_renderer);
              }
       }
      }
             if(menu==2)
              {
                  optiongoup(m_renderer);
                  menugodown(m_renderer);
                  menu=0;
                  mousex=-10000;
                  mousey=-10000;
              }
       }
         //exit
           if(mousex>=550&&mousex<=710&&mousey>=510&&mousey<=565)
           {
                SDL_DestroyWindow( m_window );
                SDL_DestroyRenderer( m_renderer );
                IMG_Quit();
                SDL_Quit();
                return 0;
           }
      }
        }
























//Functions
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
void DrawEllipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{
    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
    if(fill_boolian==0)
        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

}
void ColorWindow(SDL_Renderer *Renderer, int R, int G, int B)
{
    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );
    SDL_RenderClear( Renderer );
}

void Drawball(SDL_Renderer *Renderer, int ball)
{
switch(ball){
case 1:
    SDL_Texture *img;
    img =IMG_LoadTexture(Renderer,"FootBall.bmp");
    int w,h;
    SDL_QueryTexture(img,NULL,NULL,&w,&h);
    SDL_Rect textr;
    textr.x=BallX;
    textr.y=BallY;
    textr.w=BallR;
    textr.h=BallR;
    SDL_RenderCopy(Renderer,img,NULL,&textr);
    break;
case 2:
    img =IMG_LoadTexture(Renderer,"BasketBall.bmp");
        SDL_QueryTexture(img,NULL,NULL,&w,&h);
    textr.x=BallX;
    textr.y=BallY;
    textr.w=BallR;
    textr.h=BallR;
    SDL_RenderCopy(Renderer,img,NULL,&textr);
    break;
case 3:
        img =IMG_LoadTexture(Renderer,"BaseBall.bmp");
        SDL_QueryTexture(img,NULL,NULL,&w,&h);
    textr.x=BallX;
    textr.y=BallY;
    textr.w=BallR;
    textr.h=BallR;
    SDL_RenderCopy(Renderer,img,NULL,&textr);
    break;
    }
}
void Fillbackground(SDL_Renderer *Renderer, int backg)
{
        switch (backg){
    case 3:
            SDL_Rect textr_bg;
    SDL_Texture *backg;
    int bg_w,bg_h;
    int w_bg,h_bg;
    backg =IMG_LoadTexture(Renderer,"blue.jpg");
    SDL_QueryTexture(backg,NULL,NULL,&w_bg,&h_bg);
    textr_bg.x=0;
    textr_bg.y=0;
    textr_bg.w=1200;
    textr_bg.h=800;
    SDL_RenderCopy(Renderer,backg,NULL,&textr_bg);
    break;
    case 2:
    backg =IMG_LoadTexture(Renderer,"green.jpg");
    SDL_QueryTexture(backg,NULL,NULL,&w_bg,&h_bg);
    textr_bg.x=0;
    textr_bg.y=0;
    textr_bg.w=1200;
    textr_bg.h=800;
        SDL_RenderCopy(Renderer,backg,NULL,&textr_bg);
    break;
    case 1:
    backg =IMG_LoadTexture(Renderer,"red.jpg");
    SDL_QueryTexture(backg,NULL,NULL,&w_bg,&h_bg);
    textr_bg.x=0;
    textr_bg.y=0;
    textr_bg.w=1200;
    textr_bg.h=800;
        SDL_RenderCopy(Renderer,backg,NULL,&textr_bg);
    break;
    }
}

void Drawplatform(SDL_Renderer *Renderer)
{
    SDL_Texture *platform;
    int w,h;
    platform =IMG_LoadTexture(Renderer,"platform.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=PlatformX;
    textrP.y=PlatformY;
    textrP.w=PlatformL;
    textrP.h=PlatformH;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);
}

void menugoup(SDL_Renderer *Renderer)
{
    int menux=320,menuy=0;
    for(menuy=0;menuy>=-600;menuy=menuy-60)
{
        SDL_Texture *platform;
    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"startmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+280;
    textrP.w=352;
    textrP.h=267;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"optionmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+345;
    textrP.w=352;
    textrP.h=262;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"exitmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+410;
    textrP.w=352;
    textrP.h=193;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);
    SDL_RenderPresent(Renderer);
    Fillbackground(Renderer,backg);
}
}
void menugodown(SDL_Renderer *Renderer)
{
    int menux=320,menuy=-600;
    for(menuy=-600;menuy<=0;menuy=menuy+60)
{
    SDL_Texture *platform;
    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"startmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+280;
    textrP.w=352;
    textrP.h=267;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"optionmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+345;
    textrP.w=352;
    textrP.h=262;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"exitmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+410;
    textrP.w=352;
    textrP.h=193;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);
    SDL_RenderPresent(Renderer);
    Fillbackground(Renderer,backg);
}
}
void showmenu(SDL_Renderer *Renderer)
{
    int menux=320,menuy=0;
    SDL_Texture *platform;
    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"startmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+280;
    textrP.w=352;
    textrP.h=267;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"optionmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+345;
    textrP.w=352;
    textrP.h=262;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"exitmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+410;
    textrP.w=352;
    textrP.h=193;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);
    SDL_RenderPresent(Renderer);
}
void optiongoup(SDL_Renderer *Renderer)
{
    int menux=320,menuy=0;
    for(menuy=0;menuy>=-600;menuy=menuy-60)
{
    Fillbackground(Renderer,backg);
    SDL_Texture *platform;

    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"back.png");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+50;
    textrP.y=menuy+370;
    textrP.w=50;
    textrP.h=50;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


     platform =IMG_LoadTexture(Renderer,"BALL.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+400;
    textrP.w=60;
    textrP.h=26;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

   platform =IMG_LoadTexture(Renderer,"football1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+230;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

       platform =IMG_LoadTexture(Renderer,"basketball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+310;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"baseball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+390;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"background.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+465;
    textrP.w=146;
    textrP.h=30;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundblue.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+290;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundred.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+360;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundgreen.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+430;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


    platform =IMG_LoadTexture(Renderer,"level.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+535;
    textrP.w=63;
    textrP.h=27;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+250;
    textrP.y=menuy+535;
    textrP.w=16;
    textrP.h=16;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level2.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+300;
    textrP.y=menuy+515;
    textrP.w=16;
    textrP.h=36;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level3.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+350;
    textrP.y=menuy+517;
    textrP.w=40;
    textrP.h=34;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    SDL_RenderPresent(Renderer);
}
}
void showoption(SDL_Renderer *Renderer)
{
    int menux=320,menuy=0;
    Fillbackground(Renderer,backg);
    SDL_Texture *platform;

    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"back.png");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+50;
    textrP.y=menuy+370;
    textrP.w=50;
    textrP.h=50;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


     platform =IMG_LoadTexture(Renderer,"BALL.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+400;
    textrP.w=60;
    textrP.h=26;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

   platform =IMG_LoadTexture(Renderer,"football1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+230;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

       platform =IMG_LoadTexture(Renderer,"basketball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+310;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"baseball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+390;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"background.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+465;
    textrP.w=146;
    textrP.h=30;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundblue.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+290;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundred.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+360;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundgreen.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+430;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


    platform =IMG_LoadTexture(Renderer,"level.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+535;
    textrP.w=63;
    textrP.h=27;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+250;
    textrP.y=menuy+535;
    textrP.w=16;
    textrP.h=16;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level2.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+300;
    textrP.y=menuy+515;
    textrP.w=16;
    textrP.h=36;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level3.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+350;
    textrP.y=menuy+517;
    textrP.w=40;
    textrP.h=34;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    SDL_RenderPresent(Renderer);
}
void optiongodown(SDL_Renderer *Renderer)
{
    int menux=320,menuy=-600;
    for(menuy=-600;menuy<=0;menuy=menuy+60)
{
    Fillbackground(Renderer,backg);
    SDL_Texture *platform;

    int w,h;
    platform =IMG_LoadTexture(Renderer,"choobmenu.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    SDL_Rect textrP;
    textrP.x=menux;
    textrP.y=menuy;
    textrP.w=598;
    textrP.h=608;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"back.png");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+50;
    textrP.y=menuy+370;
    textrP.w=50;
    textrP.h=50;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


     platform =IMG_LoadTexture(Renderer,"BALL.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+400;
    textrP.w=60;
    textrP.h=26;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

   platform =IMG_LoadTexture(Renderer,"football1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+230;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

       platform =IMG_LoadTexture(Renderer,"basketball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+310;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"baseball1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+390;
    textrP.y=menuy+380;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"background.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+465;
    textrP.w=146;
    textrP.h=30;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundblue.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+290;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundred.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+360;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"backgroundgreen.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+430;
    textrP.y=menuy+445;
    textrP.w=48;
    textrP.h=48;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);


    platform =IMG_LoadTexture(Renderer,"level.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+130;
    textrP.y=menuy+535;
    textrP.w=63;
    textrP.h=27;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level1.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+250;
    textrP.y=menuy+535;
    textrP.w=16;
    textrP.h=16;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level2.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+300;
    textrP.y=menuy+515;
    textrP.w=16;
    textrP.h=36;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    platform =IMG_LoadTexture(Renderer,"level3.bmp");
    SDL_QueryTexture(platform,NULL,NULL,&w,&h);
    textrP.x=menux+350;
    textrP.y=menuy+517;
    textrP.w=40;
    textrP.h=34;
    SDL_RenderCopy(Renderer,platform,NULL,&textrP);

    SDL_RenderPresent(Renderer);
}
}
void print_one_digit(SDL_Renderer *renderer,int X,int Y,int R,int Re,int G,int B){
    if (R==0) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+40,Re,G,B,200);
    }
    if (R==1) {
        aalineRGBA(renderer, X+17, Y+40, X+17, Y+10,Re,G,B,200);
    }
    if (R==2) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+5, Y+40,Re,G,B,200);
    }
    if (R==3) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+40,Re,G,B,200);
    }
    if (R==4) {
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+20,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+20, X+30, Y+20,Re,G,B,200);
    }
    if (R==5) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+25, X+30, Y+40,Re,G,B,200);
    }
    if (R==6) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+25, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+40,Re,G,B,200);
    }
    if (R==7) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+10, X+5, Y+40,Re,G,B,200);
    }
    if (R==8) {
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+25, X+30, Y+25,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+40, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+40,Re,G,B,200);
    }
    if (R==9) {
        aalineRGBA(renderer, X+30, Y+10, X+30, Y+40,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+5, Y+20,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+20, X+30, Y+20,Re,G,B,200);
        aalineRGBA(renderer, X+5, Y+10, X+30, Y+10,Re,G,B,200);
    }

}
