#include "internal_ft_regex.h"

status	remove_epsilon(finite_automaton *raw_graph, FA_state *state)
{
	iterator it = state->nd.epsilon->metadata.container.begin(state->nd.epsilon);
	iterator end = state->nd.epsilon->metadata.container.end(state->nd.epsilon);
#ifdef REG_DEBUG
	printf("BEGIN epsilon %d\n", state->id);
	printf("=> %p %p %p %zu\n", &state->nd.epsilon->btree.past_the_end, it.btree.current, end.btree.current, state->nd.epsilon->size);
#endif
	while (it.metadata.compare(it.metadata, &it, &end))
	{
		FA_state *other_state = it.metadata.dereference(&it);
		if (other_state == state)
			continue;
#ifdef REG_DEBUG
		printf("state: %d, other_state: %d\n", state->id, other_state->id);
#endif
		if (other_state->nd.epsilon && remove_epsilon(raw_graph, other_state) != OK)
			return FATAL;
		for (size_t i = 0; i < (sizeof(other_state->nd.ascii) / sizeof(*other_state->nd.ascii)); i++)
		{
			if (!other_state->nd.ascii[i])
				continue;
			for_val_in(FA_state *link, *other_state->nd.ascii[i])
						if (create_link(&state->nd.ascii[i], link) != OK)
							return FATAL;
		}
		if (other_state->accept)
			state->accept = true;
		other_state->link_to--;
#ifdef REG_DEBUG
		printf("erasing link %d -> %d\n", state->id, other_state->id);
#endif
		it = ft_btree_erase_one(state->nd.epsilon, it);
#ifdef REG_DEBUG
		printf("== %p %p\n", it.btree.current, &state->nd.epsilon->btree.past_the_end);
#endif
	}
	state->nd.epsilon->destroy(state->nd.epsilon);
	free(state->nd.epsilon);
	state->nd.epsilon = NULL;
#ifdef REG_DEBUG
	printf("END epsilon\n");
#endif
	return OK;
}

status	remove_all_epsilon(finite_automaton *raw_graph)
{
#ifdef REG_DEBUG
	printf("BEFORE remove_all_epsilon\n");
	print_graph(raw_graph);
#endif
	for_in(it, raw_graph->states)
	{
		FA_state *state = it.metadata.dereference(&it);
		if (state->nd.epsilon && remove_epsilon(raw_graph, state) != OK)
			return FATAL;
	}
	remove_unused_states(raw_graph);

#ifdef REG_DEBUG
	printf("AFTER remove_all_epsilon\n");
	get_graphml(raw_graph, "after_remove_epsilon");
	print_graph(raw_graph);
#endif

	return OK;
}
