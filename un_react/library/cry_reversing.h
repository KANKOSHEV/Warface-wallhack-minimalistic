#pragma once
#include "cry_reversing_tools.h"

void create_silhouettes()
{
	i_system_global* m_global = i_system_global::singleton();
	if (!is_valid_ptr(m_global))
		return;

	i_game_frame_work* m_game_framework = i_game_frame_work::singleton();
	if (!is_valid_ptr(m_game_framework))
		return;

	i_entity_system* m_entity_system = m_global->get_entity_system();
	if (!is_valid_ptr(m_entity_system))
		return;

	i_actor_system* m_actor_system = m_game_framework->get_actor_system();
	if (!is_valid_ptr(m_actor_system))
		return;

	i_actor* m_actor;
	if (m_game_framework->get_client_actor(&m_actor))
	{
		i_entity_it* p_entity_iteartor = m_entity_system->get_entity_iterator();
		while (i_entity* p_entity = p_entity_iteartor->entity_next())
		{
			if (i_actor* p_actor = m_actor_system->get_actor(p_entity->get_entity_id()))
			{
				if (!elimination_team(p_actor, m_actor))
					continue;

				set_silhouettes(p_actor->get_entity()->get_proxy(e_entity_proxy::entity_proxy_render), 1.f, 0.30f, 0.f, 0.f);
			}
		}
	}
}
