// Script assets have changed for v2.3.0 see
// https://help.yoyogames.com/hc/en-us/articles/360005277377 for more information
function IceParticles(_x, _y, _num){
	for (var i = 0; i < _num; i++)
	{
		instance_create_depth(_x, _y, 0, ice_particle);
	}
}