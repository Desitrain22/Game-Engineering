/// @description Insert description here
// You can write your code in this editor

mspd += grav;
y += mspd;


//reset rock
if (y >= room_height){

	y = 0;
	mspd = 0;
	x = random_range(0, room_width);
	SCORE += 1;
	
}