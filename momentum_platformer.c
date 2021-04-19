
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
0x0F, 0x14, 0x22, 0x00, // sprite palette 1
0x30, 0x30, 0x31, 0x00, // sprite palette 2
0x30, 0x30, 0x30, // sprite palette 3
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


byte next;
int xpos = 50, ypos = 167;
int scrollx, scrollmin, scrollmax;
byte pdir = 0;
byte pshot = 0;
byte pmov = 0;

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
  ypos += dy;
  if(dx < 0){
    if(xpos + dx > 24){
      if((xpos < 256 && (scrollx > (scrollmin<<1))))
        scrollx += dx;
      else
        xpos += dx;
    } else
    	ret |= 1;
    
  }
  else if (dx > 0){
    if(xpos + dx < 928){
      if((xpos > 400 && (scrollx < (scrollmax<<1))))
        scrollx += dx;
      else
        xpos += dx;
    } else
    ret |= 2;
  }
  return ret;
}

void main(void) {
  char pad;	// controller flags
  int x = 64; // player X val
  int sx = 0;
  byte cycle = 0; //gets incremeted every loop, used for spacing things out on certain frames
  int speed = 6;
  // 32-character array for string-building
  char str[32];
  // clear string array
  memset(str, 0, sizeof(str));
  
  // write text to name table
  vram_fill(0xc1,32);
  vram_adr(NTADR_A(0,0));
  vram_write(ArchRoom, 960);
  vram_adr(NTADR_B(0,0));
  vram_write(PlatformRoom, 960);
  setup_graphics();
  setScrollBounds(0, 512);
  
  // infinite loop
  while (1){
    // poll controller
    pad = pad_poll(1);
    if(pad&PAD_LEFT){
    	move(-speed, 0);
    	pdir = 6;
      	pmov = 3;
    }
    else if(pad&PAD_RIGHT){
    	move(speed, 0);
  	pdir = 0;
      	pmov = 3;
    }
    else{
      pmov = 0;
    }
    if((pad&PAD_A)&&!pshot)
      pshot = 6;
    scroll(scrollx>>2, 0);
    next = 0;
    next = oam_meta_spr((xpos>>2)-1, ypos, next, plr_sprite[pdir + (pmov&(cycle>>3)) + (pmov&2) + (pshot&&!pmov)]);
    if(next != 0)
       oam_hide_rest(next);
    cycle++;
    if(pshot)
      pshot--;
    ppu_wait_frame();
  }
}
