#pragma once
#include "cry_classes.h"

bool elimination_team(i_actor* m_actor, i_actor* p_actor)
{
	return ((m_actor->get_team_id() != p_actor->get_team_id() || p_actor->get_team_id() == 0) && (p_actor != m_actor));
}

void set_silhouettes(i_entity_proxy* p_render_proxy, float r, float g, float b, float a)
{
	if (p_render_proxy)
	{
		p_render_proxy->set_render_flags(0x80018);
		p_render_proxy->set_hudsilhouettes_params(r, g, b, a);
	}
}
