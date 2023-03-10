
num_rocks = 8;


for (var i = 0; i < num_rocks; i+=1){
	instance_create_depth(random_range(0,room_width), random_range(-room_height, 0), 0, obj_rock);
}