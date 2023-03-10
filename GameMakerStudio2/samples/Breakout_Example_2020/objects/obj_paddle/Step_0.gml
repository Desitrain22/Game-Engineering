/// @description Insert description here
// You can write your code in this editor

if !global.GAME_BEGIN{
	if keyboard_check_pressed(vk_space){
		global.GAME_BEGIN = true
		instance_create_depth(x,y-32,0,obj_ball)
	}
}


if keyboard_check(vk_right){
	xspd = mspd	
	image_xscale = lerp(image_xscale, 1.3, .1);
	image_yscale = lerp(image_yscale, 0.7, .5);
}
if keyboard_check(vk_left){
	xspd = -mspd
	image_xscale = lerp(image_xscale, 1.3, .1);
	image_yscale = lerp(image_yscale, 0.7, .5);
}

if (!keyboard_check(vk_right) and !keyboard_check(vk_left)){
	xspd = 0
	image_xscale = lerp(image_xscale, 1, .1);
	image_yscale = lerp(image_yscale, 1, .1);
}

MoveCollide()

