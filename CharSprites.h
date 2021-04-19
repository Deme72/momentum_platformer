


//x, y, spr, flags
const unsigned char plr_sprite[][64] = {
	
  	
  	{//Stand Right
       	1,     0,     18,   	1,  
       	2,     8,     19,   	1,  
        2,      0,      0,	0, 
        10,      0,      1,	0, 
        2,      8,      2,   	0, 
        10,      8,      3,   	0, 
        2,      16,     4,   	0, 
        10,      16,     5,   	0, 
        14,     9,     6,   	0,
        128
	},
	{//Stand Shoot Right
       	1,     1,     18,   	1,  
       	3,     8,     20,   	1,  
        2,      1,      0,	0, 
        10,      1,      1,	0, 
        2,      8,      8,   	0, 
        10,      8,      9,   	0, 
        2,      16,     4,   	0, 
        10,      16,     5,   	0, 
        14,      7,     7,   	0,
        128
	},
  	{//Walk Right 1
       	1,     2,     18,   	1,  
       	3,     9,     20,   	1,  
        2,      2,      0,	0, 
        10,      2,      1,	0, 
        2,      9,      8,   	0, 
        10,      9,      9,   	0, 
        3,      16,     10,   	0, 
        10,      16,    14,   	0, 
        14,      8,     7,   	0,
        128
	},
  	{//Walk Right 2
       	1,     1,     18,   	1,  
       	3,     8,     20,   	1,  
        2,      1,      0,	0, 
        10,      1,      1,	0, 
        2,      8,      8,   	0, 
        10,      8,      9,   	0, 
        2,      15,     11,   	0, 
        10,      16,    15,   	0, 
        14,      7,     7,   	0,
        128
	},
  	{//Walk Right 3
       	1,     2,     18,   	1,  
       	3,     9,     20,   	1,  
        2,      2,      0,	0, 
        10,      2,      1,	0, 
        2,      9,      8,   	0, 
        10,      9,      9,   	0, 
        6,      16,     12,   	0, 
        6,      16,    16,   	0, 
        14,      8,     7,   	0,
        128
	},
  	{//Walk Right 4
       	1,     1,     18,   	1,  
       	3,     8,     20,   	1,  
        2,      1,      0,	0, 
        10,      1,      1,	0, 
        2,      8,      8,   	0, 
        10,      8,      9,   	0, 
        6,      16,     13,   	0, 
        5,      15,    17,   	0, 
        14,      7,     7,   	0,
        128
	},
  
	{//Stand Left
       	13,     0,     18,   	1|OAM_FLIP_H,  
       	12,     8,     19,   	1|OAM_FLIP_H,  
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
       	13,     1,     18,   	1|OAM_FLIP_H,  
       	12,     8,     20,   	1|OAM_FLIP_H,  
        12,      1,      0,	0|OAM_FLIP_H, 
        4,      1,      1,	0|OAM_FLIP_H, 
        12,      8,      8,   	0|OAM_FLIP_H, 
        4,      8,      9,   	0|OAM_FLIP_H, 
        12,      16,     4,   	0|OAM_FLIP_H, 
        4,      16,     5,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 1
       	13,     2,     18,   	1|OAM_FLIP_H,  
       	12,     9,     20,   	1|OAM_FLIP_H,  
        12,      2,      0,	0|OAM_FLIP_H, 
        4,      2,      1,	0|OAM_FLIP_H, 
        12,      9,      8,   	0|OAM_FLIP_H, 
        4,      9,      9,   	0|OAM_FLIP_H, 
        10,      16,     10,   	0|OAM_FLIP_H, 
        4,      16,     14,   	0|OAM_FLIP_H, 
        0,      8,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 2
       	13,     1,     18,   	1|OAM_FLIP_H,  
       	12,     8,     20,   	1|OAM_FLIP_H,  
        12,      1,      0,	0|OAM_FLIP_H, 
        4,      1,      1,	0|OAM_FLIP_H, 
        12,      8,      8,   	0|OAM_FLIP_H, 
        4,      8,      9,   	0|OAM_FLIP_H, 
        13,      15,     11,   	0|OAM_FLIP_H, 
        4,      16,     15,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 3
       	13,     2,     18,   	1|OAM_FLIP_H,  
       	12,     9,     20,   	1|OAM_FLIP_H,  
        12,      2,      0,	0|OAM_FLIP_H, 
        4,      2,      1,	0|OAM_FLIP_H, 
        12,      9,      8,   	0|OAM_FLIP_H, 
        4,      9,      9,   	0|OAM_FLIP_H, 
        8,      16,     12,   	0|OAM_FLIP_H, 
        8,      16,     16,   	0|OAM_FLIP_H, 
        0,      8,     7,   	0|OAM_FLIP_H,
        128
	},
  	{//Walk Left 4
       	13,     1,     18,   	1|OAM_FLIP_H,  
       	12,     8,     20,   	1|OAM_FLIP_H,  
        12,      1,      0,	0|OAM_FLIP_H, 
        4,      1,      1,	0|OAM_FLIP_H, 
        12,      8,      8,   	0|OAM_FLIP_H, 
        4,      8,      9,   	0|OAM_FLIP_H, 
        8,      16,     13,   	0|OAM_FLIP_H, 
        8,      15,     17,   	0|OAM_FLIP_H, 
        0,      7,     7,   	0|OAM_FLIP_H,
        128
	}
};