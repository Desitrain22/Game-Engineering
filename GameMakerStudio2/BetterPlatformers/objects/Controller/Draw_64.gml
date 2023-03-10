/// @description Insert description here
// You can write your code in this editor
/// @description Insert description here
// You can write your code in this editor

if (room == Start)
{
	draw_text(20,90,"Welcome to 'Not sponsored USA Ice Dancing Simulator'")
	draw_text(20,120,"Press Space to Start")
	draw_text(20,140,"Arrow Keys: Accelerate")
	draw_text(20,180,"Space Bar: Jump")
	draw_text(20,160,"Arrow keys only accelerate! Your velocity is constant");
	draw_text(20,220,"Don't lose control! And don't fall off the ice!");
	draw_text(20,240,"The door won't appear until you secure the key!");
	
}

else if (room == End2)		
{
	draw_text(20,60, "You lose! Press Enter to try again");
}
else if (room == End)
{
	draw_text(20,80, "Enter: Play again");
}
else
{
	draw_text(20, 100, "lives: "+ string(global.tries));
	if (!global.enemyActive)
	{
		draw_circle_color(40,160,32,c_white,c_white, false);
		
		draw_sprite_ext(Sprite8,Sprite8,40,160,1,1,360-(360*(countdown/10)),image_blend,1)
		draw_text(20, 184, string(countdown));
	}	
}