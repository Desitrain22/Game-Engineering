
//get player input
var hmove = keyboard_check(vk_right) - keyboard_check(vk_left);

//apply acceleration based on input
xspd += hmove * accel;

//constrain xspd to max
xspd = clamp(xspd, -max_spd, max_spd);

//apply gravity
yspd += grav;


//check if we are standing on the ground
var on_ground = place_meeting(x, y + 1, obj_wall);

//if so, let us jump
if (on_ground){
	if (keyboard_check_pressed(vk_space)){
		yspd = -jump_str;	
	}
}

//run all the code in our function
do_movement();