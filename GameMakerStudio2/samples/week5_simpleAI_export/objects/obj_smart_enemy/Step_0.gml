/// @description Insert description here
// You can write your code in this editor

// Inherit the parent event
event_inherited();

//turn around if we would fall off a ledge
if (!position_meeting(x + (sprite_width/2), y + 4, obj_wall) or !position_meeting(x - (sprite_width/2), y + 4, obj_wall)){
	//turn around
	hmove = -hmove;
	xspd = -xspd;
}