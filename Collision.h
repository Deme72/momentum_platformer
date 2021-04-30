
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
unsigned char CollisionBank[480];