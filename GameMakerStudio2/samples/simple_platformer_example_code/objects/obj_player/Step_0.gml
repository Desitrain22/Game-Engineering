//apply gravity
yspd += grav;


//zero out xspd by default
xspd = 0;

//check keyboard to move horizontally
if (keyboard_check(ord("D")) or keyboard_check(vk_right)){
	xspd = 5;
}

if (keyboard_check(ord("A"))){
	xspd = -5;
}


//////// stop the player when it touches a wall
// check if the player touches a wall
// zero out yspd
// put the player back on top of the platform

if (yspd > 0 and place_meeting(x, y+1, obj_wall)){
	yspd = 0;
	var hit_plat = instance_place(x,y+1,obj_wall);
	y = hit_plat.y - hit_plat.sprite_height/2;
	grounded = true;
} else {
	grounded = false
}

//allow me to jump if i'm on the ground
if (grounded and keyboard_check_pressed(vk_space)){
	yspd = -10;	
}

//let me move horizontally if there's no wall in the way
if (not place_meeting(x + xspd, y, obj_wall)){
	x += xspd;
}

//apply y movement
y += yspd;



