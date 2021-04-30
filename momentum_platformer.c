
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


#define A_LIST(name)\
const unsigned char name[][32] = {\

#define A_END };

// define a 2x2 metasprite
#define A_METASPRITE_O(code,pal)\
{\
        0,      0,      (code)+0,   pal, \
        8,      0,      (code)+1,   pal, \
        0,      8,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
        128}

// define a 2x2 metasprite, flipped horizontally
#define A_METASPRITE_O_FH(code,pal)\
{\
        8,      0,      (code)+0,   (pal)|OAM_FLIP_H, \
        0,      0,      (code)+1,   (pal)|OAM_FLIP_H, \
        8,      8,      (code)+2,   (pal)|OAM_FLIP_H, \
        0,      8,      (code)+3,   (pal)|OAM_FLIP_H, \
        128}

// define a 2x3 metasprite
#define A_METASPRITE_B(code,pal)\
{\
        0,      0,      (code)+0,   pal, \
        8,      0,      (code)+1,   pal, \
        0,      8,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
        0,      16,      (code)+4,   pal, \
        8,      16,      (code)+5,   pal, \
        128}

// define a 2x3 metasprite, flipped horizontally
#define A_METASPRITE_B_FH(code,pal)\
{\
        8,      0,      (code)+0,   (pal)|OAM_FLIP_H, \
        0,      0,      (code)+1,   (pal)|OAM_FLIP_H, \
        8,      8,      (code)+2,   (pal)|OAM_FLIP_H, \
        0,      8,      (code)+3,   (pal)|OAM_FLIP_H, \
        8,      16,     (code)+4,   (pal)|OAM_FLIP_H, \
        0,      16,     (code)+5,   (pal)|OAM_FLIP_H, \
        128}
/*
A_LIST(plr_sprite)
A_METASPRITE_B(0x0, 0),
A_METASPRITE_B_FH(0x0, 0)
A_END*/

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

struct bullet{
  int x;
  int y;
  int dir;
};

struct squidEnemy{
  int x;
  int y;
  bool alive;
  struct bullet bull;
};

byte next;
int xpos = 50, ypos = 600;
int scrollx, scrollmin, scrollmax;
byte pdir = 0;
byte pshot = 0;
byte pmov = 0;
int pfall = 0;
char sliding = 0;
struct bullet shots[3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
//both screens collision data 32*30 * 2 / 4 tiles per byte
struct squidEnemy enemies[3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};

void setScrollBounds(int minx, int maxx){
  while(minx > 512){
    minx -= 512;
    maxx -= 512;
    scrollx -= 2048;
  }
  scrollmin = minx;
  scrollmax = maxx;
}


byte move(int dx, int dy){
  byte ret = 0;
  if(!checkMove(xpos>>2, ypos>>2, scrollx>>2, 0, dy>>1, sliding))
    ypos += dy;
  else{
    if(pfall > 0){
       pfall-=4;
      if(pfall < 4)
        pfall = 2;
    }
    else
       pfall+=4;
  }
  if(dx < 0){
    if(!checkMove(xpos>>2, ypos>>2, scrollx>>2, dx, 0, sliding)){
      if(xpos + dx > 24){
        if((xpos < 256 && (scrollx > (scrollmin<<1)))){
          shots[0].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          shots[1].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          shots[2].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[0].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[1].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[2].x -= ((scrollx+dx)>>2) - (scrollx>>2);
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
          shots[0].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          shots[1].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          shots[2].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[0].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[1].x -= ((scrollx+dx)>>2) - (scrollx>>2);
          enemies[2].x -= ((scrollx+dx)>>2) - (scrollx>>2);
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

void main(void) {
  char pad;	// controller flags
  byte cycle = 0; //gets incremeted every loop, used for spacing things out on certain frames
  int speed = 0;
  int sprIdx = 0;
  int i = 0;
  // 32-character array for string-building
  char str[32];
  // clear string array
  memset(str, 0, sizeof(str));
  
  enemies[0].alive = true;
  enemies[0].x = 100;
  enemies[0].y = 100;
  
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
    	move(-10 - speed>>1, pfall);
    	pdir = 1;
      	pmov = 3;
    }
    else if(pad&PAD_RIGHT){
    	move(10 + speed>>1, pfall);
  	pdir = 0;
      	pmov = 3;
    }
    else if (sliding){
      	pmov = 3;
      	if(pdir)
      	  move(-10 - speed>>1, pfall);
        else
      	  move(10 + speed>>1, pfall);
    }else {
      move(0, pfall);
      pmov = 0;
    }
    if((pad&PAD_B)&&!pshot){
      pshot = 16;
      i = 0;
      while (i<3 && shots[i].dir){
      	i++;
      }
      if(i < 4){
        i = i%3;
        shots[i].dir = 4*(-(pdir<<1)+1);
        shots[i].x = (xpos>>2)+ (14*(-(pdir<<1)+1))+6;
        shots[i].y = (ypos>>2)+5;
        if(sliding){
          shots[i].x += (8*pdir);
          shots[i].y += 8;
        }
      }
    }
    sprIdx = pdir*6 + (pmov&(cycle>>3)) + (pmov&2) + (pshot&&!pmov);
    if(checkJump(xpos>>2, ypos>>2, scrollx>>2)){
      if(!(sliding) && (cycle&16) && speed > 0)
        speed--;
      if(pad&PAD_A){
        if(pad&PAD_DOWN && sliding<2){
          sliding = 32;
        	sprIdx = 14+pdir;
          if(speed < 6)
            speed+=3;
        }else if(sliding<16){
  	  pfall = -14-speed;
          sliding = 0;
      	}
      } 
    } else{
    	sprIdx = 12+pdir;
      	sliding = 0;
    }
    if (sliding)
    	sprIdx = 14+pdir;
    scroll(scrollx>>2, 16);
    next = 0;
    next = oam_meta_spr((xpos>>2)-1, ypos>>2, next, plr_sprite[sprIdx]);
    cycle++;
    if(pshot)
      pshot--;
    pfall++;
    if(pfall > 14 && (cycle & 16) && (speed < 8))
       speed++;
    if(sliding > 0)
    	sliding--;
    i = 0;
    while(i<3){
      if(enemies[i].alive)
      	next = oam_meta_spr(enemies[i].x, enemies[i].y, next, float_squid[(cycle&24)>>3]);
      i++;
    }
    i = 0;
    while(i<3){
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
    if(next != 0)
       oam_hide_rest(next);
    ppu_wait_frame();
  }
}
