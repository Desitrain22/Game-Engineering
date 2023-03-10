if (room == rm_game){
	
	draw_text(20,20, "SCORE: " + string(SCORE));
	draw_text(120,20, "LIVES: " + string(LIVES));
} else if (room == rm_end){
	
	draw_set_halign(fa_center);
	draw_text(room_width/2, room_height/2, "NICE JOB!!! YOU DODGED " + string(SCORE) + " ROCKS!!!");	
	draw_set_halign(fa_left);
}