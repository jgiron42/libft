#include "internal_ft_regex.h"

// change the data structure to the deterministic version (the graph must already be technically deterministic)
status	make_deterministic(finite_automaton *automaton)
{
#ifdef REG_DEBUG
	printf("BEFORE make_deterministic\n");
#endif
	for_val_in(FA_state *state, automaton->states)
	{
		if (state->nd.epsilon && state->nd.epsilon->size > 0)
		{
			return FATAL;
		}
		for (size_t i = 0; i < (ARRAY_SIZE(state->nd.ascii)); i++)
		{
			if (!state->nd.ascii[i])
				continue;
			else if (state->nd.ascii[i]->size > 1)
				cursed_abort("the automaton isn't deterministic");
			FA_state *ptr = NULL;
			if (state->nd.ascii[i]->size)
				ptr = ft_btree_iterator_dereference(ref_of(state->nd.ascii[i]->begin(state->nd.ascii[i])));
#ifdef REG_DEBUG
			printf("size: %zu ptr: %p %zu id: %d accept: %d\n", state->nd.ascii[i]->size, ptr, malloc_usable_size(ptr), ptr->id, ptr->accept);
#endif
			state->nd.ascii[i]->destroy(state->nd.ascii[i]);
			free(state->nd.ascii[i]);
			state->nd.ascii[i] = NULL;
			state->d.ascii[i] = ptr;
		}
	}
	automaton->deterministic = true;
#ifdef REG_DEBUG
	printf("AFTER make_deterministic\n");
	get_graphml(automaton, "after_make_deterministic");
	print_graph(automaton);
#endif
	return OK;
}