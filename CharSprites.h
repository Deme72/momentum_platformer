


//x, y, spr, flags
const unsigned char plr_sprite[][64] = {
	
  	{//Stand Right
       	1,     0,     19,   	1,  //hatcorner
       	2,     8,     20,   	1,  //glimmer
        2,      0,      0,	0,  //head
        10,      0,      1,	0,  
        2,      8,      2,   	0,  //chest
        10,      8,      3,   	0, 
        2,      16,     4,   	0,  //legs
        10,      16,     5,   	0, 
        14,     9,     6,   	0,  //gun
        128
	},
	{//Stand Shoot Right
       	1,     0,     19,   	1,  
       	2,     8,     20,   	1,  
        2,      0,      0,	0,  
        10,      0,      1,	0,  
        2,      8,      2,   	0, 
        10,      8,      3,   	0, 
        2,      16,     4,   	0, 
        10,      16,     5,   	0, 
        14,     6,     7,   	0,
        128
	},
  	{//Walk Right 1
       	2,     2,     19,   	1,  
       	3,     9,     21,   	1,  
        6,      1,      8,	0, 
        2,      9,      9,   	0, 
        10,      9,      10,   	0, 
        3,      16,     11,   	0, 
        10,      16,    15,   	0, 
        14,      8,     7,   	0,
        128
	},
  	{//Walk Right 2
       	2,     1,     19,   	1,  
       	3,     8,     21,   	1,  
        6,      0,      8,	0, 
        2,      8,      9,   	0, 
        10,      8,      10,   	0, 
        2,      15,     12,   	0, 
        10,      16,    16,   	0, 
        14,      7,     7,   	0,
        128
	},
  	{//Walk Right 3
       	2,     2,     19,   	1,  
       	3,     9,     21,   	1,  
        6,      1,      8,	0, 
        2,      9,      9,   	0, 
        10,      9,      10,   	0, 
        5,      16,     13,   	0, 
        6,      16,    17,   	0, 
        14,      8,     7,   	0,
        128
	},
  	{//Walk Right 4
       	2,     1,     19,   	1,  
       	3,     8,     21,   	1,  
        6,      0,      8,	0, 
        2,      8,      9,   	0, 
        10,      8,      10,   	0, 
        6,      16,     14,   	0, 
        5,      15,    18,   	0, 
        14,      7,     7,   	0,
        128
	},
	{//Stand Left
       	13,     0,     19,   	1|OAM_FLIP_H,  
       	12,     8,     20,   	1|OAM_FLIP_H,  
        12,      0,      0,	0|OAM_FLIP_H, 
        4,      0,      1,	0|OAM_FLIP_H, 
        12,      8,      2,   	0|OAM_FLIP_H, 
        4,      8,      3,   	0|OAM_FLIP_H, 
        12,      16,     4,   	0|OAM_FLIP_H, 
        4,      16,     5,   	0|OAM_FLIP_H, 
        0,      9,     6,   	0|OAM_FLIP_H,
        128
	},
  	{//Stand Shoot Left
       	13,     1,     19,   	1|OAM_FLIP_H,  
       	12,     8,     21,   	1|OAM_FLIP_H,  
        12,      1,      0,	0|OAM_FLIP_H, 
        4,      1,      1,	0|OAM_FLIP_H, 
        12,      8,      9,   	0|OAM_FLIP_H, 
        4,      8,      10,   	0|OAM_FLIP_H, 
        12,      16,     4,   	0|OAM_FLIP_H, 
        4,      16,     5,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 1
       	12,     2,     19,   	1|OAM_FLIP_H,  
       	11,     9,     21,   	1|OAM_FLIP_H,  
      	8,      1,      8,	0|OAM_FLIP_H,  
        12,      9,      9,   	0|OAM_FLIP_H, 
        4,      9,      10,   	0|OAM_FLIP_H, 
        10,      16,     11,   	0|OAM_FLIP_H, 
        4,      16,     15,   	0|OAM_FLIP_H, 
        0,      8,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 2
       	12,     1,     19,   	1|OAM_FLIP_H,  
       	11,     8,     21,   	1|OAM_FLIP_H,  
      	8,      0,      8,	0|OAM_FLIP_H,  
        12,      8,      9,   	0|OAM_FLIP_H, 
        4,      8,      10,   	0|OAM_FLIP_H, 
        13,      15,     12,   	0|OAM_FLIP_H, 
        4,      16,     16,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 3
       	12,     2,     19,   	1|OAM_FLIP_H,  
       	11,     9,     21,   	1|OAM_FLIP_H,  
      	8,      1,      8,	0|OAM_FLIP_H,  
        12,      9,      9,   	0|OAM_FLIP_H, 
        4,      9,      10,   	0|OAM_FLIP_H, 
        9,      16,     13,   	0|OAM_FLIP_H, 
        8,      16,     17,   	0|OAM_FLIP_H, 
        0,      8,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 4
       	12,     1,     19,   	1|OAM_FLIP_H,  
       	11,     8,     21,   	1|OAM_FLIP_H, 
      	8,      0,      8,	0|OAM_FLIP_H,  
        12,      8,      9,   	0|OAM_FLIP_H, 
        4,      8,      10,   	0|OAM_FLIP_H, 
        8,      16,     14,   	0|OAM_FLIP_H, 
        8,      15,     18,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Jump Right
       	2,     1,     19,   	1,  
       	3,     8,     21,   	1,  
        2,      14,     0x32,  	0, 
        11,      14,    0x33,  	0, 
        6,      0,      8,	0, 
        2,      8,      9,   	0, 
        10,      8,      10,   	0, 
        14,      7,     7,   	0,
        128
	},
  	{//Jump Left
       	12,     2,     19,   	1|OAM_FLIP_H,  
       	11,     9,     21,   	1|OAM_FLIP_H,  
      	8,      1,      8,	0|OAM_FLIP_H,  
        12,      14,     0x32, 	0|OAM_FLIP_H, 
        3,      14,     0x33,  	0|OAM_FLIP_H, 
        12,      9,      9,   	0|OAM_FLIP_H, 
        4,      9,      10,   	0|OAM_FLIP_H, 
        0,      8,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Slide Right
       	1,    14,     19,   	1,
        6,     13,      8,	0,  
        15,      15,      7,   	0,
        0,      16,      22,  	0, 
        8,      16,     23,   	0,
        16,      16,     24,   	0, 
        24,     16,     25,   	0,
        128},
  	{//Slide Left
       	21,    14,     19,   	1|OAM_FLIP_H,
        17,     13,      8,	0|OAM_FLIP_H,  
        10,      15,      7,   	0|OAM_FLIP_H,
        24,      16,      22,  	0|OAM_FLIP_H, 
        16,      16,     23,   	0|OAM_FLIP_H,
        8,      16,     24,   	0|OAM_FLIP_H, 
        0,     16,     25,   	0|OAM_FLIP_H,
        128}
};
const unsigned char float_squid[][32] = {
  	{ //float one
       	0,    	1,    	 38, 	2,
        8,     	1,   	 39,	2,  
        0,      9,	 40, 	0,
        8,      9,       41,	0,
        128},
  	{ //float two
       	0,    	0,    	 38, 	2,
        8,     	0,   	 39,	2,  
        0,      9,	 42, 	0,
        8,      9,       43,	0,
        128},
  	{ //float three
       	0,    	0,    	 38, 	2,
        8,     	0,   	 39,	2,  
        0,      8,	 44, 	0,
        8,      8,       45,	0,
        128},
  	{ //float four
       	0,    	1,    	 38, 	2,
        8,     	1,   	 39,	2,  
        0,      8,	 46, 	0,
        8,      8,       47,	0,
        128}
};