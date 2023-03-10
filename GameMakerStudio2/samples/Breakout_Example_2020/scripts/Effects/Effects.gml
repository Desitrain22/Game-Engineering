function Shake_Screen(_amt, _dur)
{
	obj_screenshake.shake_timer = _dur;
	obj_screenshake.shake_amt = _amt;
}

function Spawn_Particles(_x, _y, _num)
{
	for (var i = 0; i < _num; i++)
	{
		instance_create_depth(_x, _y, 0, obj_particle);
	}
}