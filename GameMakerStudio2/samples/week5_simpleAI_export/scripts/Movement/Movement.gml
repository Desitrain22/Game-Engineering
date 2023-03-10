// Script assets have changed for v2.3.0 see
// https://help.yoyogames.com/hc/en-us/articles/360005277377 for more information
function init_movement(){
	//data
	on_ground = false;
	x_bump = false;
	hmove = 0;
	xspd = 0;
	yspd = 0;
	
	accel = .2;
	decel = .1;
	grav = .1;
	
	max_spd = 2;
	
	jump_str = 10;
}

function do_movement(){
	
	//apply acceleration based on input
	xspd += hmove * accel;
	
	//decelerate if no press
	if (hmove == 0){
		xspd -= decel * sign(xspd);
		if (abs(xspd) <= decel){
			xspd = 0;	
		}
	}

	//constrain xspd to max
	xspd = clamp(xspd, -max_spd, max_spd);

	//apply gravity
	yspd += grav;
	
	
	//check if we are standing on the ground
	on_ground = place_meeting(x, y + 1, obj_wall);
	
	
	//LEVEL 2
	//here we loop through *each possible pixel of movement* every frame.
	for (var i = 0; i < abs(xspd); i++){
		if (not place_meeting(x + sign(xspd), y, obj_wall)){
			x += sign(xspd);
		} else {
			x_bump = true;
			break;
		}
	}
	
	for (var i = 0; i < abs(yspd); i++){
		if (not place_meeting(x, y  + sign(yspd), obj_wall)){
			y += sign(yspd);
		} else {
			yspd = 0;	
			break;
		}
	}
	
	
	
	/*//BASIC 
	//move if there isn't a wall there
	if (not place_meeting(x + xspd, y, obj_wall)){
		x += xspd;
	} else {
		xspd = 0;	
	}
	
	if (not place_meeting (x, y + yspd, obj_wall)){
		y += yspd;
	} else {
		yspd = 0;	
	}
	*/
}