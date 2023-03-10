/// @description Insert description here
// You can write your code in this editor

// Inherit the parent event
event_inherited();

if (x_bump){
	x_bump = false;
	
	//flip direction and keep trying to go that way
	xspd *= -1;
	hmove *= -1;
}