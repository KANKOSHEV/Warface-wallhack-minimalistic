class i_renderer;
class i_system;
class i_entity_system;
class i_entity_it;
class i_actor_system;
class i_actor_iterator;
class i_entity;
class i_entity_proxy;
class i_actor;
class i_game_frame_work;
class i_entity_render_proxy;

template <typename t>
t f_virtual(PVOID f_base, __int64 f_index) 
{ 
	return (*(t**)f_base)[f_index / 8];
}

template <typename t>
static bool is_valid_ptr(t* ptr)
{
	return (ptr) ? true : false;
}

enum e_entity_proxy
{
	entity_proxy_render,
	entity_proxy_physics,
	entity_proxy_script,
	entity_proxy_sound,
	entity_proxy_ai,
	entity_proxy_area,
	entity_proxy_boids,
	entity_proxy_boid_object,
	entity_proxy_camera,
	entity_proxy_flow_graph,
	entity_proxy_substitution,
	entity_proxy_trigger,
	entity_proxy_rope,
	entity_proxy_entity_node,
	entity_proxy_user,
	entity_proxy_last
};