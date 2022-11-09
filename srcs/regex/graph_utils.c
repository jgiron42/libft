#include "internal_ft_regex.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
#include "ft_strings.h"
#include "ft_stdio.h"
#include "other.h"

status	create_link(container **src, FA_state *dst)
{
	if (!*src)
	{
		*src = ft_calloc(1, sizeof(container));
		if (!*src || ft_btree(ATOMIC_TYPE, *src) != OK)
			return FATAL;
	}
	iterator it = ft_btree_insert_val(*src, dst);
	if (!it.metadata.compare(it.metadata, &it, ref_of(ft_btree_end(*src))))
	{
		free(*src);
		return FATAL;
	}
	dst->link_to++;
	return OK;
}

FA_state	*get_new_state(container *raw_graph)
{
	FA_state to_insert;
	ft_bzero(&to_insert, sizeof(to_insert));
	to_insert.id = (int)raw_graph->size;
	if (ft_push_back(raw_graph, &to_insert) != OK)
		return NULL;
#ifdef REG_DEBUG
	printf("new_state: %p\n", *(FA_state **)ft_list_back(raw_graph));
#endif
	return (*(FA_state **)ft_list_back(raw_graph));
}

// remove all unused states from an automaton
void	remove_unused_states(finite_automaton *raw_graph)
{
	FA_state *state;

	for_in(it, raw_graph->states)
	{
		state = it.metadata.dereference(&it);
		while (it.metadata.compare(it.metadata, &it, &end) && !state->link_to)
		{
			destroy_transitions(*state);
			if (state->subset)
			{
				state->subset->destroy(state->subset);
				free(state->subset);
				state->subset = NULL;
			}
			it = ft_list_erase_one(&raw_graph->states, it);
			state = it.metadata.dereference(&it);
		}
	}
}

void	destroy_transitions(FA_state state)
{
	for (size_t i = 0; i < ARRAY_SIZE(state.nd.ascii); i++)
	{
		if (state.nd.ascii[i])
		{
			state.nd.ascii[i]->destroy(state.nd.ascii[i]);
			free(state.nd.ascii[i]);
			state.nd.ascii[i] = NULL;
		}
	}
	if (state.nd.epsilon)
	{
		state.nd.epsilon->destroy(state.nd.epsilon);
		free(state.nd.epsilon);
		state.nd.epsilon = NULL;
	}
}

void	destroy_automaton(finite_automaton *automaton)
{
	if (automaton->states.init)
	{
		for_val_in(FA_state *state, automaton->states)
		{
			if (!automaton->deterministic)
				destroy_transitions(*state);
			if (state->subset)
			{
				state->subset->destroy(state->subset);
				free(state->subset);
				state->subset = NULL;
			}
		}
		automaton->states.destroy(&automaton->states);
	}
}

// print the graph in the terminal
void	print_graph(finite_automaton *automaton)
{
	for_val_in(FA_state *state, automaton->states)
	{
		if (state->id != -1)
			printf("state %d:", state->id);
		else
		{
			printf("state { ");
			bool first = true;
			for_in(it, *state->subset)
			{
				if (!first)
					printf(", ");
				printf("%d", ((FA_state *)it.metadata.dereference(&it))->id);
				first = false;
			}
			printf(" }:");
		}
		printf("%s\n links: %zu\n transitions:\n", state->accept ? " [ACCEPT]" : "", state->link_to);
		if (automaton->deterministic)
			for (size_t i = 0; i < (sizeof(state->d.ascii) / sizeof(*state->d.ascii)); i++) {
				if (!state->d.ascii[i]) continue;
				if (state->d.ascii[i]->id != -1)
					printf (" '%c'-> %d\n", (char)i, state->d.ascii[i]->id);
				else {
					printf(" '%c'-> { ", (char) i);
					bool first = true;
					for_in(it, *state->d.ascii[i]->subset)
					{
						if (!first)
							printf(", ");
						printf("%d", ((FA_state *)it.metadata.dereference(&it))->id);
						first = false;
					}
					printf(" }\n");
				}
			}
		else
		{
			for (size_t i = 0; i < (sizeof(state->nd.ascii) / sizeof(*state->nd.ascii)); i++) {
				if (!state->nd.ascii[i]) continue;
				printf(" '%c'-> [ ", (char) i);
				bool first = true;
				for_in(it, *state->nd.ascii[i]) {
					if (!first)
						printf(", ");
					printf("%d", ((FA_state *) it.metadata.dereference(&it))->id);
					first = false;
				}
				printf(" ]\n");
			}
			if (state->nd.epsilon)
			{
				printf(" epsilon -> [ ");
				bool first = true;
				for_in(it, *state->nd.epsilon) {
					if (!first)
						printf(", ");
					printf("%d", ((FA_state *) it.metadata.dereference(&it))->id);
					first = false;
				}
				printf(" ]\n");
			}
		}
	}
}

// output the graphml of the automaton in the file <name>.graphml
void	get_graphml(finite_automaton *automaton, char *name)
{
	char file_name[100];

	ft_snprintf(file_name, 100, "%s.graphml", name);

	ft_FILE *f = ft_fopen(file_name, "w+");
	printf("creating %s\n", file_name);
	ft_fprintf(f, "<graphml>\n");
	ft_fprintf(f, " <key id=\"d1\" for=\"edge\" attr.name=\"entry\" attr.type=\"string\"/>\n");
	ft_fprintf(f, " <key id=\"d2\" for=\"node\" attr.name=\"name\" attr.type=\"string\"/>\n");
	ft_fprintf(f, " <graph id=\"G\" edgedefault=\"directed\">\n");
	for_val_in(FA_state *state, automaton->states)
	{
		if (!state) continue;
		ft_fprintf(f, "  <node id=\"n%d\">%d</node>\n", state->id, state->id);
		if (automaton->deterministic)
			for (size_t i = 0; i < (sizeof(state->d.ascii) / sizeof(*state->d.ascii)); i++) {
				if (!state->d.ascii[i]) continue;
				ft_fprintf(f, "  <edge id=\"n%de%zu\" source=\"n%d\" target=\"n%d\">\n", state->id, i, state->id, state->d.ascii[i]->id);
				if (ft_isprint((int)i))
					ft_fprintf(f, "   <data key=\"d1\">%c</data>\n", (char)i);
				else
					ft_fprintf(f, "   <data key=\"d1\">%x</data>\n", (char)i);

				ft_fprintf(f, "  </edge>\n");
			}
		else
		{
			for (size_t i = 0; i < (sizeof(state->nd.ascii) / sizeof(*state->nd.ascii)); i++) {
				if (!state->nd.ascii[i]) continue;
				for_in(it, *state->nd.ascii[i]) {
					ft_fprintf(f, "  <edge id=\"n%de%zuto%d\" source=\"n%d\" target=\"n%d\">\n", state->id, i, ((FA_state *) it.metadata.dereference(&it))->id, state->id, ((FA_state *) it.metadata.dereference(&it))->id);
					if (ft_isprint((int)i))
						ft_fprintf(f, "   <data key=\"d1\">%c</data>\n", (char)i);
					else
						ft_fprintf(f, "   <data key=\"d1\">%x</data>\n", (char)i);

					ft_fprintf(f, "  </edge>\n");
				}
			}
			if (state->nd.epsilon)
			{
				for_in(it, *state->nd.epsilon) {
					ft_fprintf(f, "  <edge id=\"n%deepsilonto%d\" source=\"n%d\" target=\"n%d\">\n", state->id, ((FA_state *) it.metadata.dereference(&it))->id, state->id, ((FA_state *) it.metadata.dereference(&it))->id);
						ft_fprintf(f, "   <data key=\"d1\">epsilon</data>\n");
					ft_fprintf(f, "  </edge>\n");
				}
			}
		}
	}
	ft_fprintf(f, " </graph>\n");
	ft_fprintf(f, "</graphml>\n");
	ft_fclose(f);
}

// compare two state by their id or subset
int		state_compare(type_metadata prop, void *l, void *r)
{
	(void)prop;
	if ((*(FA_state **)l)->id != (*(FA_state **)r)->id)
		return ((*(FA_state **)l)->id - (*(FA_state **)r)->id);
	if (!(*(FA_state **)l)->subset)
		return 0;
	return ft_compare((*(FA_state **) l)->subset, (*(FA_state **) r)->subset);
}