#include "internal_ft_regex.h"
#include "ft_stdlib.h"
#include "other.h"

status	get_targets(container *current, container *target_subset)
{
	for_in(it, *current) // collect all the states targeted by this entry
	{
		FA_state *other_state = it.metadata.dereference(&it);
		if (!other_state->subset)
		{
			iterator tmp = ft_btree_insert_val(target_subset, other_state);
			if (!tmp.metadata.compare(tmp.metadata, &tmp,
									  ref_of(target_subset->metadata.container.end(target_subset))))
				return FATAL;
		}
		else if (ft_btree_insert_range(target_subset, other_state->subset->begin(other_state->subset), other_state->subset->end(other_state->subset)) != OK)
			return FATAL;
	}
	return OK;
}

status	get_all_transitions(FA_state *target)
{
	for_in(it, *target->subset) // adding each transitions from target_subset to target
	{
		FA_state *sub_state = it.metadata.dereference(&it);
		if (!sub_state)
			continue;
//		printf("sub_state: %p\n", sub_state);
		for (size_t i = 0; i < (sizeof(sub_state->nd.ascii) / sizeof(*sub_state->nd.ascii)); i++)
		{
			if (!sub_state->nd.ascii[i] || !sub_state->nd.ascii[i]->size)
				continue;
			for_in(it2, *sub_state->nd.ascii[i]) {

				// do not insert link between states in the subset
//				iterator it3 = ft_btree_find(target->subset, it2.metadata.dereference(&it2));
//				if (it3.metadata.compare(it3.metadata, &it3, ref_of(target->subset->metadata.container.end(target->subset))))
//					continue;

				if (create_link(&target->nd.ascii[i], it2.metadata.dereference(&it2)) != OK)
					return FATAL;
			}
		}
	}
	return OK;
}

FA_state *find_or_create_target(finite_automaton *automaton, container *target_subset, container *subset_map)
{
	if (target_subset->size == 1)
	{
		iterator it = target_subset->begin(target_subset);
		return (it.metadata.dereference(&it));
	}

	FA_state tmp = {.id = -1, .subset = target_subset};
	iterator found_it = ft_btree_find(subset_map, &tmp);
	if (found_it.metadata.compare(found_it.metadata, &found_it, ref_of(subset_map->metadata.container.end(subset_map))))
		return found_it.metadata.dereference(&found_it);
	else
	{
		FA_state *target = get_new_state(&automaton->states);
		if (!target)
			return NULL;
		target->id = -1;
		target->subset = ft_calloc(1, sizeof(container));
		if (!target->subset)
		{
			free(target);
			return NULL;
		}
		if (ft_btree_copy(target_subset->metadata, target->subset, target_subset) != OK)
		{
			free(target->subset);
			free(target);
			return NULL;
		}
		iterator it = ft_btree_insert_val(subset_map, target);
		if (!it.metadata.compare(it.metadata, &it, ref_of(subset_map->end(subset_map))))
		{
			free(target->subset);
			free(target);
			return NULL;
		}
		for_val_in(FA_state *sub_state, *target->subset)
			target->accept |= sub_state->accept;
		if (get_all_transitions(target) != OK)
		{
			free(target->subset);
			free(target);
			return NULL;
		}
		return target;
	}
}

// this function rewrite the graph in order to make it deterministic using the powerset construction technic
// (https://en.wikipedia.org/wiki/Powerset_construction)
status	powerset_construction(finite_automaton *automaton)
{
	container	subset_map; // store pointer to states
	container	target_subset;
	status ret = OK;

	type_metadata state_meta = ATOMIC_TYPE;
	state_meta.compare = &state_compare;
	if (ft_btree(state_meta, &subset_map) != OK ||
		ft_btree(ATOMIC_TYPE, &target_subset) != OK )
		return FATAL;
	for_val_in(FA_state *state, automaton->states)
	{
		if (state->nd.epsilon && state->nd.epsilon->size > 0)
			cursed_abort("epsilon transition found in powerset_construction"); // should not be reached
#ifdef REG_DEBUG
		printf("===> %d\n", state->id);
#endif
		for (size_t i = 0; i < ARRAY_SIZE(state->nd.ascii); i++)
		{
			if (!(state->nd.ascii[i] && state->nd.ascii[i]->size > 1))
				continue;
#ifdef REG_DEBUG
			printf("%c: %zu\n", (char)i,state->nd.ascii[i]->size );
#endif
			target_subset.clear(&target_subset);
			if (get_targets(state->nd.ascii[i], &target_subset) != OK)
				goto error;
			FA_state *target = find_or_create_target(automaton, &target_subset, &subset_map);
#ifdef REG_DEBUG
			printf("%p %p\n", state, target);
#endif
			if (!target)
				goto error;

			// remove all current transitions for this entry
			for_in(it, *state->nd.ascii[i]) ((FA_state *) it.metadata.dereference(&it))->link_to--;
			state->nd.ascii[i]->clear(state->nd.ascii[i]);
#ifdef REG_DEBUG
			printf("%c: %zu\n", (char)i,state->nd.ascii[i]->size );
#endif

			if (create_link(&state->nd.ascii[i], target) != OK)
				goto error;
#ifdef REG_DEBUG
			printf("%c: %zu\n", (char)i,state->nd.ascii[i]->size );
#endif
		}
	}
#ifdef REG_DEBUG
	for_val_in(FA_state *state, automaton->states)
	{
		for (size_t i = 0; i < ARRAY_SIZE(state->nd.ascii); i++)
			if (state->nd.ascii[i])
				printf("-> %c: %zu\n", (char)i,state->nd.ascii[i]->size );
	}
#endif
	remove_unused_states(automaton);

#ifdef REG_DEBUG
	printf("AFTER powerset_construction\n");
	get_graphml(automaton, "after_powerset_construction");
	print_graph(automaton);
#endif
	end:
	subset_map.destroy(&subset_map);
	target_subset.destroy(&target_subset);
	return (ret);
	error:
	ret = FATAL;
	goto end;
}