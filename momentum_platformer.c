
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"

#include "ArchRoom.h"
#include "PlatformRoom.h"
#include "CharSprites.h"
#include "Collision.h"

#define NES_MIRRORING 1

#define SHOT_COOLDOWN 16

#define SHOT_MAX 3

#define MIN_ALL 5
#define MAX_RUN 10
#define MAX_ALL 20
#define JMP_DIFF 8
#define JMP_MIN 14
#define SLIDE_BOOST 4

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] =
{
0x0F, // screen color (b)
// m, c, w, null
0x0C, 0x1C, 0x2C, 0x00, // background palette 0
0x2D, 0x2D, 0x2D, 0x00, // background palette 1
0x2D, 0x2D, 0x2D, 0x00, // background palette 2
  
0x2D, 0x2D, 0x2D, 0x00, // sprite palette 0
0x0F, 0x04, 0x22, 0x00, // sprite palette 1
0x21, 0x31, 0x31, 0x00, // sprite palette 2
0x0F, 0x05, 0x15, // sprite palette 3
};

int sprIdx = 0;

int i = 0;
byte cycle = 0; //gets incremeted every loop, used for spacing things out on certain frames
char pad; // controller flags
byte next;
char str[32] = {0};// 32-character array for string-building

int xpos = 50, ypos = 600, speed = MIN_ALL, pfall = 0,
scrollx, scrollmin, scrollmax;
byte pdir = 0, pmov = 0;
char sliding = 0;

struct bullet{
  int x;
  int y;
  int dir;
};

struct bullet shots[SHOT_MAX] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
byte pshottimer = 0;
byte pshotidx = 0;

struct squidEnemy{
  int x;
  int y;
  bool alive;
  struct bullet bull;
};

struct squidEnemy enemies[3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};


// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
  // turn on PPU
  ppu_on_all();
  // clear vram buffer
  vrambuf_clear();
  bank_bg(0);
  bank_spr(1);
  
  // set NMI handler
  set_vram_update(updbuf);
}

void setScrollBounds(int minx, int maxx){
  while(minx > 512){
    minx -= 512;
    maxx -= 512;
    scrollx -= 2048;
  }
  scrollmin = minx;
  scrollmax = maxx;
}

void updateSpritePos(int dx){
  i = 0;
  while(i<3){
    shots[i].x -= ((scrollx+dx)>>2) - (scrollx>>2);
    enemies[i].x -= ((scrollx+dx)>>2) - (scrollx>>2);
    i++;
  }
}

byte move(int dx, int dy){
  byte ret = 0;
  i = 0;
  if(!checkMove(xpos>>2, ypos>>2, scrollx>>2, 0, dy>>1, sliding))
    ypos += dy;
  else{
    if(pfall-JMP_DIFF > speed)
      speed = pfall-JMP_DIFF;
    while(pfall > 0){
       pfall-=8;
      if(pfall < 8){
        pfall = 0;
      	ypos += 7-(ypos&7)-1;
      }
    }
    pfall+=4;
  }
  if(dx < 0){
    if(!checkMove(xpos>>2, ypos>>2, scrollx>>2, dx, 0, sliding)){
      if(xpos + dx > 24){
        if((xpos < 256 && (scrollx > (scrollmin<<1)))){
          updateSpritePos(dx);
          scrollx += dx;
        }
        else
          xpos += dx;
      } else
        ret |= 1;
    }
  }
  else if (dx > 0){
    if(!checkMove(xpos>>2, ypos>>2, scrollx>>2, dx, 0, sliding)){
      if(xpos + dx < 928){
        if((xpos > 400 && (scrollx < (scrollmax<<1)))){
          updateSpritePos(dx);
          scrollx += dx;
        }
        else
          xpos += dx;
      } 
      else
        ret |= 2;
    }
  }
  return ret;
}

void spawnShot(){
  pshottimer = SHOT_COOLDOWN;
  
  if(shots[pshotidx].dir == 0){
    shots[pshotidx].dir = 4*(-(pdir<<1)+1);
    if(sliding){
      shots[pshotidx].x = (xpos>>2)+ (14*(-(pdir<<1)+1))+(pdir<<3) + 6;
      shots[pshotidx].y = (ypos>>2)+13;
    } else {
      shots[pshotidx].x = (xpos>>2)+ (14*(-(pdir<<1)+1))+6;
      shots[pshotidx].y = (ypos>>2)+5;
    }
    pshotidx++;
    pshotidx = pshotidx%SHOT_MAX;
  }
}

void drawShots(){
    i = 0;
    while(i<SHOT_MAX){
      if(shots[i].x <0 || shots[i].x > 255)
         shots[i].dir = 0;
      if(shots[i].dir > 0){
        next = oam_spr(shots[i].x, shots[i].y, 0X30, 1, next);
        shots[i].x += shots[i].dir;
      }
      else if (shots[i].dir < 0){
        next = oam_spr(shots[i].x, shots[i].y, 0X30, 1|OAM_FLIP_H, next);
        shots[i].x += shots[i].dir;
      }
      i++;
    }
}

void drawEnemies(){
    i = 0;
    while(i<3){
      if(enemies[i].alive)
      	next = oam_meta_spr(enemies[i].x, enemies[i].y, next, float_squid[(cycle&24)>>3]);
      i++;
    }
}

void main(void) {
  
  // write text to name table
  vram_fill(0xc1,32);
  vram_adr(NTADR_A(0,0));
  vram_write(ArchRoom, 960);
  importRoom(ArchRoom, 0);
  vram_adr(NTADR_B(0,0));
  vram_write(PlatformRoom, 960);
  importRoom(PlatformRoom, 1);
  setup_graphics();
  setScrollBounds(0, 512);
  
  // infinite loop
  while (1){
    // poll controller
    pad = pad_poll(1);
    if(pad&PAD_LEFT){
      if(sliding)
      	move(-SLIDE_BOOST - speed>>1, pfall);
      else
        move(-speed>>1, pfall);
      pdir = 1;
      pmov = 3;
    }
    else if(pad&PAD_RIGHT){
      if(sliding)
      	move(SLIDE_BOOST + speed>>1, pfall);
      else
    	move(speed>>1, pfall);
      pdir = 0;
      pmov = 3;
    }
    else if (sliding){
      	pmov = 3;
      	if(pdir)
      	  move(-SLIDE_BOOST - speed>>1, pfall);
        else
      	  move(SLIDE_BOOST + speed>>1, pfall);
    }else {
      move(0, pfall);
      pmov = 0;
    }
    if((pad&PAD_B)&&!pshottimer){
      spawnShot();
    }
    sprIdx = pdir*6 + (pmov&(cycle>>3)) + (pmov&2) + (pshottimer&&!pmov);
    if(checkJump(xpos>>2, ypos>>2, scrollx>>2)){
      if(!(sliding) && !pmov && speed > MIN_ALL)
        speed--;
      if(pmov && !sliding && ((cycle&15) == 8) && speed < MAX_RUN)
        speed++;
      if(pad&PAD_A){
        if(pad&PAD_DOWN && sliding<2){
          sliding = 32;
        	sprIdx = 14+pdir;
        }else if(sliding<16){
          if(JMP_DIFF + speed < JMP_MIN)
            pfall = -JMP_MIN;
  	  else
            pfall = -JMP_DIFF-speed;
          sliding = 0;
      	}
      } 
    } else{
    	sprIdx = 12+pdir;
      	sliding = 0;
    }
    if (sliding)
    	sprIdx = 14+pdir;
    scroll(scrollx>>2, 0);
    next = 0;
    next = oam_meta_spr((xpos>>2)-1, ypos>>2, next, plr_sprite[sprIdx]);
    cycle++;
    if(pshottimer)
      pshottimer--;
    pfall++;
    if(sliding > 0)
    	sliding--;
    drawEnemies();
    drawShots();
    if(next != 0)
       oam_hide_rest(next);
    ppu_wait_frame();
  }
}
