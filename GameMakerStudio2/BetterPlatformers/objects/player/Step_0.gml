/// @description Insert description here
// You can write your code in this editor
var hmove = keyboard_check(vk_right) - keyboard_check(vk_left);


if (place_meeting(x,y, Goal) && !global.key)
{
	room_goto_next();
}

if(place_meeting(x,y, Enemy) && global.enemyActive)
{
	x = 200;
	y = 553;
	xspd = 0;
	yspd = 0;
	global.tries -= 1;
	global.key = true;
	if (global.tries == 0)
	{
		room_goto(0);
	}
}


if ((x < 0 || x > 1400) || ((y < 0) || (y > 800)))
{
	x = 200;
	y = 553;
	xspd = 0;
	yspd = 0;
	global.tries -= 1;
	global.key = true;
	if (global.tries == 0)
	{
		room_goto(0);
	}
	
}


var onGround = place_meeting(x, y+1, wall);

if (onGround)
{
	if (keyboard_check_pressed(vk_space))
	{
		yspd = -jump_str;
		IceParticles(x,y, 100);
	}
	
	//now, give an illusion of stretching forward in movement
	if keyboard_check(vk_right){
	spriteXscale = lerp(spriteXscale, 1.3, .1);
	IceParticles(x,y, 1);
	}
	if keyboard_check(vk_left){
	spriteXscale = lerp(spriteXscale, -1.3, .1);
	IceParticles(x,y, 1);
	}

	if (!keyboard_check(vk_right) and !keyboard_check(vk_left)){
	spriteXscale = lerp(spriteXscale, sign(spriteXscale), .1);
	
	}
	//now, we can only accelerate on the ground!
	xspd += hmove * accel;
	xspd = clamp(xspd, -max_spd, max_spd);
	
}

yspd += grav;


do_movement();