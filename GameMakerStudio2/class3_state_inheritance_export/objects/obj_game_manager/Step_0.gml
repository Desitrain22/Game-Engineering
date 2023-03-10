if (room == rm_start){
	
	if (keyboard_check_pressed(vk_space)){
		room_goto_next();
		SCORE = 0;
	}
	
} else if (room == rm_end){
	
	if (keyboard_check_pressed(vk_space)){
		room_goto(rm_start);
	}
	
}