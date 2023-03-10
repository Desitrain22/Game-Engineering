
//get player input
hmove = 0;
hmove = keyboard_check(vk_right) - keyboard_check(vk_left);

//if so, let us jump
if (on_ground){
	if (keyboard_check_pressed(vk_space)){
		yspd = -jump_str;	
	}
}


//do actor stuff
event_inherited();

if (x_bump){
	x_bump = false;
	xspd = 0;
}