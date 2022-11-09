#include "internal_ft_regex.h"
#include "ft_stdlib.h"

int	ft_regcomp(ft_regex_t *restrict preg, const char *restrict pattern, int cflags)
{
	AST	tree;
	int tmp = parse_regexp(preg, &tree, pattern, cflags); // obtain the ast
	if (tmp)
		return tmp;

	preg->graph = ft_calloc(1, sizeof(finite_automaton)); // can be deterministic or not
	if (ft_list(POINTER_TYPE(FA_state), &preg->graph->states) != OK)
		return FATAL;

	tmp = get_raw_graph(cflags, &tree, preg->graph);
	destroy_tree(&tree);
	if (tmp != OK ||
		remove_all_epsilon(preg->graph) != OK ||
		powerset_construction(preg->graph) != OK ||
		make_deterministic(preg->graph) != OK)
	{
		ft_regfree(preg);
		return FT_REG_ESPACE;
	}
#ifdef REG_DEBUG
	printf("compilation finished, %zu states\n", preg->graph->states.size);
#endif
	return 0;
}
