#pragma once
#include "cry_defines.h"

enum game_data : __int64
{
	a_system_global             = 0x141C19150,
	a_gameframework             = 0x141F27220,
	o_entity_system             = 0xD8,
	o_system                    = 0xE8
};

enum virtual_data : __int32
{
	f_get_entity_iterator       = 160,
	f_entity_next               = 48,
	f_get_actor                 = 120,
	f_set_hudsilhouettes_params = 352,
	f_get_proxy                 = 472,
	f_get_client_actor          = 1136
};

enum entity_data : __int32
{
	o_set_render_flags          = 0x24
};

enum actor_data : __int32
{
	o_get_entity                = 0x10,
	o_get_team_id               = 0x3E0
};

enum game_frame_work_data
{
	o_get_actor_system          = 0x4E0
};

class i_system_global
{
public:
	static i_system_global* singleton()
	{
		return *(i_system_global**)game_data::a_system_global;
	}

	i_entity_system* get_entity_system()
	{
		return (i_entity_system*)*(__int64*)((__int64)this + game_data::o_entity_system);
	}

	i_system* get_system()
	{
		return (i_system*)*(__int64*)((__int64)this + game_data::o_system);
	}
};

class i_entity_system
{
public:
	i_entity_it* get_entity_iterator()
	{
		return f_virtual<i_entity_it*(__thiscall*)(PVOID)>(this, virtual_data::f_get_entity_iterator)(this);
	}
};

class i_entity_it
{
public:
	i_entity* entity_next()
	{
		return f_virtual<i_entity*(__thiscall*)(PVOID)>(this, virtual_data::f_entity_next)(this);
	}
};

class i_actor_system
{
public:
	i_actor* get_actor(__int32 entity_id)
	{
		return f_virtual<i_actor*(__thiscall*)(PVOID, __int32)>(this, virtual_data::f_get_actor)(this, entity_id);
	}
};

class i_entity
{
public:
	__int32 get_entity_id()
	{
		return *(__int32*)((__int64)this + 0x18);
	}
	
	i_entity_proxy* get_proxy(e_entity_proxy proxy)
	{
		return f_virtual<i_entity_proxy*(__thiscall*)(PVOID, e_entity_proxy)>(this, virtual_data::f_get_proxy)(this, proxy);
	}
};

class i_entity_proxy
{
public:
	void set_render_flags(__int32 flag)
	{ 
		*(__int32*)((__int64)this + entity_data::o_set_render_flags) = flag;
	}

	void set_hudsilhouettes_params(float r, float g, float b, float a)
	{
		return f_virtual<void(__thiscall*)(PVOID, float, float, float, float)>(this, virtual_data::f_set_hudsilhouettes_params)(this, r, g, b ,a);
	}
}; 

class i_actor
{
public:
	i_entity* get_entity()
	{
		return *(i_entity**)((__int64)this + actor_data::o_get_entity);
	}

	__int32 get_team_id()
	{
		return *(__int32*)((__int64)this + actor_data::o_get_team_id);
	}
};

class i_game_frame_work
{
public:
	static i_game_frame_work* singleton()
	{
		return *(i_game_frame_work**)game_data::a_gameframework;
	}
	
	i_actor_system* get_actor_system()
	{
		return *(i_actor_system**)((__int64)this + game_frame_work_data::o_get_actor_system);
	}

	bool get_client_actor(i_actor** p_actor)
	{
		return f_virtual<bool(__thiscall*)(PVOID, i_actor**)>(this, virtual_data::f_get_client_actor)(this, p_actor);
	}
};
