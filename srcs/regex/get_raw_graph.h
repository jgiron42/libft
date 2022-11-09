#ifndef LIBFT_GET_RAW_GRAPH_H
#define LIBFT_GET_RAW_GRAPH_H
#include "internal_ft_regex.h"

status		get_graph_dispatch(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);

status	get_graph_dot(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_range(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_end(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_begin(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_class(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_equivalence(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_char(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);

status	get_graph_sub(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_repeated(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_kleene(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);
status	get_graph_pipe(int cflags, reg_node *node, container *state_list, FA_state *before, FA_state *after);

typedef status	(*graph_builder)(int cflags, reg_node *, container *, FA_state *, FA_state *);

static const graph_builder graph_builder_map[] = {
		[REG_SUB] = get_graph_sub,
		[REG_CHAR] = get_graph_char,
		[REG_DOT] = get_graph_dot,
		[REG_RANGE] = get_graph_range,
		[REG_END] = get_graph_end,
		[REG_BEGIN] = get_graph_begin,
#if (defined(WHITELIST) && defined(FT_USE_ISWCTYPE))
		[REG_CLASS] = get_graph_class,
#endif
#if (defined(WHITELIST) && defined(FT_USE_STRCOLL))
		[REG_EQUIVALENCE] = get_graph_equivalence,
#endif

		[REG_PIPE] = get_graph_pipe,
		[REG_BRACKET] = get_graph_pipe,
		[REG_REPEATED] = get_graph_repeated,
		[REG_KLEENE] = get_graph_kleene,
};

#endif
