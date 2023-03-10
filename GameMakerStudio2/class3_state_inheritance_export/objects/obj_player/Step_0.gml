/// @description runs every frame

if (!dead){
	//make the player move to the right
	if (keyboard_check(vk_right)) {
		//x = x + mspd;
		x += mspd;
	} 

	if (keyboard_check(vk_left)){
		x -= mspd;
	}

	if (keyboard_check(vk_up)){
		y -= mspd;
	}

	if (keyboard_check(vk_down)){
		y += mspd;
	}


	if (place_meeting(x,y,obj_rock)){
		//store rock we hit as variable in case we need it
		//var hit_rock = instance_place(x, y, obj_rock);

		dead = true;
		dead_timer = dead_timer_max;
	
	}



	//detect if character off screen
	if (x < 0) {
		x = 0;	
	} else if (x > room_width){
		x = room_width;	
	}

	if (y < 0){
		y = 0;	
	} else if (y > room_height){
		y = room_height;	
	}

} else {
	dead_timer --;
	if (dead_timer <= 0){
		//respawn / reset
		LIVES -= 1;
		
		if (LIVES <= 0){
			room_goto(rm_end);	
			LIVES = 3;
		}
		
		dead = false;	
		x = room_width/2;
		y = room_height * .75;
		
		//code inside these brackets will be run *from the rock*
		with (obj_rock){
			y = random_range(-200, 0);
			mspd = 0;
			x = random_range(0, room_width);	
		}
		
	}
}