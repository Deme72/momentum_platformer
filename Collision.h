
const unsigned char CollisonSheet[64]={
	0x00, 0x00, 0x00, 0x00, //0
	0x00, 0x00, 0x00, 0x00,	//1
	0x00, 0x00, 0x00, 0x00,	//2
	0x00, 0x00, 0x00, 0x00, //3
	0x00, 0x00, 0x00, 0x00, //4
	0x00, 0x00, 0x00, 0x00, //5
	0x00, 0x00, 0x00, 0x00, //6
	0x00, 0x00, 0x00, 0x00, //7
	0x55, 0x55, 0x50, 0x00, //8
	0x00, 0x00, 0x00, 0x00, //9
	0x00, 0x00, 0x00, 0x00, //A
	0x00, 0xFF, 0xFF, 0xF0, //B
	0x00, 0x00, 0x00, 0x00, //C
	0x00, 0x00, 0x00, 0x00, //D
	0x00, 0x00, 0x00, 0x00, //E
	0x00, 0x00, 0x00, 0x00  //F
	//0-3   4-7   8-B   C-F
};

//both screens collision data 32*30 * 2 / 4 tiles per byte
unsigned char CollisionTable[2][240] = {{0}};

void importRoom(const char * in, int table){
  int i = 0;
  while(i < 960){
    unsigned char loc = in[i];
    if((i&3) == 0)
      CollisionTable[table][i>>2] = 0;
    CollisionTable[table][i>>2] |= ((CollisonSheet[loc>>2]>>(6 - ((loc&3)<<1))) & 3)<<(6 - ((i&3)<<1));
    i++;
  }
}

unsigned char getCollision(int x, int y){
  int tilenum = 0;
  int table = 0;
  if(x >= 256){
    x-= 256;
    table++;
  }
  tilenum = (x>>3) + (y>>3)*32;
  return (CollisionTable[table][tilenum>>2]>>(6 - ((tilenum&3)<<1))) & 3;
}

unsigned char checkMove(int x, int y, int scrollx, int dx, int dy, bool sliding){
  int i = 0;
  int j = 0;
  unsigned char ret = 0;
  x+=scrollx+dx;
  y+=dy;
  if (sliding){
    
    ret |= getCollision(x, y+24);
    ret |= getCollision(x+8, y+24);
    ret |= getCollision(x+16, y+24);
    ret |= getCollision(x+24, y+24);
    return ret;
  }
  if(dy<0){
    ret |= getCollision(x, y);
    ret |= getCollision(x+8, y);
    ret |= getCollision(x+16, y);
  }
  if(dx>0){
    ret |= getCollision(x+16, y+8);
    ret |= getCollision(x+16, y+16);
  } else if(dx < 0){
    ret |= getCollision(x, y+8);
    ret |= getCollision(x, y+16);
  }
  ret |= getCollision(x+16, y+24);
  ret |= getCollision(x, y+24);
  return ret;
}

unsigned char checkJump(int x, int y, int scrollx){
  unsigned char ret = 0;
  x+=scrollx;
  ret |= getCollision(x, y+30);
  ret |= getCollision(x+8, y+30);
  ret |= getCollision(x+16, y+30);
  
  return ret;
}