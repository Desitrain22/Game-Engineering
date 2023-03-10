



if room == Room2
{
	draw_text(room_width/2 - 64, room_height/2, "Game Over");
	draw_text(room_width/2 - 64, room_height/2 + 20, "Score: " + string(global.userScore));	
	draw_text(room_width/2 - 64, room_height/2 + 80,"Press Enter to try again");
}

else if (room == Start)
{
	draw_text(room_width/2 - 64, room_height/2 + 20, "Arrow Keys: Move");
	draw_text(room_width/2 - 64, room_height/2 + 40, "Space: Flap");
	draw_text(room_width/2 - 64, room_height/2 + 60, "Press Space to start");
	draw_text(room_width/2 - 64, room_height/2 + 80, "Press R to restart");	
	draw_set_font(Font2);
}
else
{
	if global.numEnemies == 0
	{
		draw_text(room_width/2, room_height/2, "Round " + string(state));
		if (alarm[3] == -1)
		{
			alarm[3] = 120;
		}
	}
	draw_text(448-64-64, 736, "Lives: ");
	for (var i=0; i < global.playerLives;i++)
	{
		draw_sprite(lifeSprite, noone,400+(i * 17),758);
	}
	
	draw_text(room_width - 300, 20, "Press R to restart");	
}