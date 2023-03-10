/// @description runs once when the object is born
// use it to initialize variables

mspd = 5;

//go to start position
x = room_width/2;
y = room_height * .75;

dead = false;

dead_timer = 0;
dead_timer_max = 2 * room_speed;