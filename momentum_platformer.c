
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

A_LIST(plr_sprite)
A_METASPRITE_B(0x80, 0),
A_METASPRITE_B_FH(0x80, 0)
A_END

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] =
{
0x0F, // screen color (b)
// m, c, w, null
0x0C, 0x1C, 0x2C, 0x00, // background palette 0
0x1C, 0x20, 0x2C, 0x00, // background palette 1
0x00, 0x1A, 0x20, 0x00, // background palette 2
  
0x01, 0x13, 0x41, 0x00, // sprite palette 0
0x0F, 0x24, 0x23, 0x00, // sprite palette 1
0x36, 0x21, 0x19, 0x00, // sprite palette 2
0x1D, 0x37, 0x2B, // sprite palette 3
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
  
  // set NMI handler
  set_vram_update(updbuf);
}


byte next;


 // generally before game loop (in main)
// main function, run after console reset
void main(void) {
  char pad;	// controller flags
  byte x = 10; // player X val
  int sx = 0;
  byte panim = 0;
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
  
  // infinite loop
  while (1){
    // poll controller
    pad = pad_poll(1);
    if(pad&PAD_LEFT){
    	panim = 1;
      	if(x > 8){
          if((x < 32 && (sx > 0)))
            sx -= 1;
          else
    	    x -= 1;
        }
    }
    else if(pad&PAD_RIGHT){
    	panim = 0;
      	if(x < 232){
          if((x > 100))
            sx += 1;
          else
    	    x += 1;
        }
    }
    scroll(sx, 0);
    next = 0;
    next = oam_meta_spr(x, 167, next, plr_sprite[panim]);
    if(next != 0)
       oam_hide_rest(next);
    ppu_wait_frame();
  }
}
