/// @description Insert description here
// You can write your code in this editor
number_rocks = 10;

for (var i=0; i < number_rocks; i++)
{
	instance_create_depth(random_range(0,room_width),0,0, Rock);
}