/// @description Insert description here
// You can write your code in this editor
//turn around if we would fall off a ledge

visible = global.enemyActive;

if ((!position_meeting(x + (sprite_width)-32, y+64, wall) or !position_meeting(x+32 , y+64, wall))){
	//turn around
	xspd = -xspd;
}

if (xbump){
	xbump = false;
	xspd = sign(xspd) * -2;
}

yspd += grav;
do_movement();