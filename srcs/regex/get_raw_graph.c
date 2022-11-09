#include "get_raw_graph.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
#include <string.h>

// Terminals:

status	get_graph_char(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list;
	if (cflags & FT_REG_ICASE)
		return create_link(&before->nd.ascii[ft_toupper(node->_char)], after);
	else
		return create_link(&before->nd.ascii[node->_char], after);
}

status	get_graph_equivalence(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list;
	for (int i = 0; i < 256; i++) { // todo: whitelist
		if (((cflags & FT_REG_ICASE && !strcoll((char[2]) {(char) ft_toupper((char) i), 0}, (char[2]) {node->equivalence_class, 0})) ||
			!strcoll((char[2]) {(char) ft_toupper((char) i), 0}, (char[2]) {node->equivalence_class, 0})) &&
			create_link(&before->nd.ascii[i], after) != OK)
			return FATAL;
	}
	return OK;
}

status	get_graph_class(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list;
	if (cflags & FT_REG_ICASE) {
		for (int i = 0; i < 256; i++)
			if ((iswctype((char) i, node->char_class) ||
				 iswctype(ft_toupper((char) i), node->char_class)) &&
				create_link(&before->nd.ascii[i], after) != OK)
				return FATAL;
	}
	else
		for (int i = 0; i < 256; i++)
			if (iswctype((char) i, node->char_class) &&
				create_link(&before->nd.ascii[i], after) != OK)
				return FATAL;
	return OK;
}

status	get_graph_begin(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list; (void)node; (void)cflags;
	return create_link(&before->nd.ascii[FT_RE_BEGIN], after);
}

status	get_graph_end(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list; (void)node; (void)cflags;
	return create_link(&before->nd.ascii[FT_RE_END], after);
}

status	get_graph_range(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list;
	if (cflags & FT_REG_ICASE) {
		for (int i = node->range.begin; i <= node->range.end; i++)
			if (create_link(&before->nd.ascii[ft_toupper((char) i)], after) != OK)
				return FATAL;
	}
	else
		for (int i = node->range.begin; i <= node->range.end; i++)
			if (create_link(&before->nd.ascii[i], after) != OK)
				return FATAL;
	return OK;
}

status	get_graph_dot(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	(void)state_list; (void)node;
	if (cflags & FT_REG_ICASE) {
		for (int i = 0; i < 256; i++)
			if (create_link(&before->nd.ascii[ft_toupper((char) i)], after) != OK)
				return FATAL;
	}
	else
		for (int i = 0; i < 256; i++)
			if (create_link(&before->nd.ascii[i], after) != OK)
				return FATAL;
	return OK;
}

// Non-terminals:

status	get_graph_sub(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	if (node->sub.size == 0) // empty expr
		return create_link(&before->nd.epsilon, after);

	size_t i = 0;
	for_in(it, node->sub)
	{
		FA_state *new_state;
		if (i != node->sub.size - 1)
			new_state = get_new_state(state_list);
		else
			new_state = after;
		if (!new_state ||
			get_graph_dispatch(cflags, it.metadata.dereference(&it), state_list, before, new_state) != OK)
			return FATAL;
		before = new_state;
		i++;
	}
	return OK;
}

status	get_graph_pipe(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	for_in(it, node->sub)
		if (get_graph_dispatch(cflags, it.metadata.dereference(&it), state_list, before, after) != OK)
			return FATAL;
	return OK;
}

status	get_graph_kleene(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	FA_state *state = get_new_state(state_list);

	if (!state ||
		get_graph_dispatch(cflags, node->kleene, state_list, state, state) != OK ||
		create_link(&before->nd.epsilon, state) != OK ||
		create_link(&state->nd.epsilon, after) != OK)
		return FATAL;
	return OK;
}

status	get_graph_repeated(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	if (node->repeated.max == 0) // empty
		return create_link(&before->nd.epsilon, after);

	int i;
	// mandatory part:
	for (i = 1; i <= node->repeated.min; i++)
	{
		FA_state *new_state;
		if (i != node->repeated.max)
			new_state = get_new_state(state_list);
		else
			new_state = after;
		if (get_graph_dispatch(cflags, node->repeated.tok, state_list, before, new_state) != OK)
			return FATAL;
		before = new_state;
	}

	// optional part:
	if (node->repeated.max == FT_RE_DUP_INF) // kleene
	{
		if (create_link(&before->nd.epsilon, after) != OK)
			return FATAL;
		if (get_graph_dispatch(cflags, node->repeated.tok, state_list, before, before) != OK)
			return FATAL;
	}
	else
		for (; i <= node->repeated.max; i++)
		{
			FA_state *new_state;
			if (i != node->repeated.max)
				new_state = get_new_state(state_list);
			else
				new_state = after;
			if (create_link(&before->nd.epsilon, after) != OK)
				return FATAL;
			if (get_graph_dispatch(cflags, node->repeated.tok, state_list, before, new_state) != OK)
				return FATAL;
			before = new_state;
		}
	return OK;
}

status get_graph_dispatch(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after)
{
	return graph_builder_map[node->type](cflags, node, state_list, before, after);
}

status	get_raw_graph(int cflags, AST *tree, finite_automaton *raw_graph)
{
	raw_graph->begin = get_new_state(&raw_graph->states);
	raw_graph->begin->link_to = 1;
	raw_graph->end = get_new_state(&raw_graph->states);
	raw_graph->end->accept = true;
	return get_graph_dispatch(cflags, tree->root, &raw_graph->states, raw_graph->begin, raw_graph->end);
}
