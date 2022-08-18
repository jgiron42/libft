#ifndef LIBFT_CONTAINERS_H
#define LIBFT_CONTAINERS_H
#include <unistd.h>
#include "../libft.h"

typedef enum {
	FT_VECTOR,
	FT_BTREE,
	FT_LIST,
	FT_BHEAP
}		container_type;

typedef void*  data_type;

typedef struct s_type_metadata {
	status	(*constructor)(struct s_type_metadata, void *);
	void	(*destructor)(struct s_type_metadata, void *);
	status	(*assign)(struct s_type_metadata, void *dst, const void *src);
	status	(*copy)(struct s_type_metadata, void *dst, const void *src);
	int		(*compare)(struct s_type_metadata prop, void* right, void* left);
	void*	(*increment)(void* this);
	void*	(*decrement)(void* this);
	void*	(*add)(void* this, ssize_t to_add);
	ssize_t (*diff)(void* l, void *r);
	data_type 	(*dereference)(void* this);
	size_t size;
}	type_metadata;

typedef struct s_btree_node {
	data_type data;
	struct s_btree_node *right;
	struct s_btree_node *left;
	struct s_btree_node *parent;
	union {
		enum {
			FT_RB_RED,
			FT_RB_BLACK,
		}	color;
		int balance_factor;
	};
}			btree_node;

typedef struct s_list_node {
	data_type data;
	struct s_list_node *next;
	struct s_list_node *prev;
}	list_node;

struct s_iterator;

typedef struct s_container {
	container_type type;
	type_metadata value_type_metadata;
	size_t		size;
	union {
		struct {
			char	*data;
			size_t		capacity;
			int			align;
		}	vector;
		struct {
			char	*data;
			size_t	capacity;
		}	string;
		struct {
			list_node past_the_end;
		}	list;
		struct {
			btree_node *first;
			btree_node *last;
			btree_node past_the_end;
			bool		multi; // true if multiset
		}	btree;
		struct {
			btree_node *root;
			btree_node *last;
		}	bheap;
	};
	struct s_iterator	(*begin)(struct s_container *);
	struct s_iterator	(*end)(struct s_container *);
	void				(*destroy)(struct s_container *this);
	void				(*clear)(struct s_container *this);
	status				(*copy)(struct s_type_metadata meta, void *dst, const void *src);
}		container;

typedef struct s_iterator {
	container_type	container_type;
	enum {
		FT_ITERATOR,
		FT_INPUT_ITERATOR,
		FT_OUTPUT_ITERATOR,
		FT_FORWARD_ITERATOR,
		FT_BIDIRECTIONAL_ITERATOR,
		FT_RANDOM_ACCESS_ITERATOR,
	}	iterator_tag;
	type_metadata		value_type_metadata;
	type_metadata		metadata;
	union {
		struct {
			char	*current;
			int		align;
		}	vector;
		struct {
			list_node	*current;
		}	list;
		struct {
			type_metadata		key_prop;
			btree_node	*current;
		}	btree;
	};
}		iterator;

status ft_vector(type_metadata type_metadata, void *dst);

status	pointer_assign(type_metadata prop,  void *dst, const void *src);
status	pointer_copy(type_metadata prop,  void *dst,  const void *src);
void	pointer_destructor(type_metadata prop,  void *ptr);
status	pointer_constructor(type_metadata prop,  void *ptr);
int	pointer_compare(type_metadata prop, void *l, void *r);

#define POINTER_TYPE(pointed_type) ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &pointer_compare, .size = sizeof( pointed_type )})

status	atomic_assign(type_metadata prop,  void *dst, const void *src);
status	atomic_copy(type_metadata prop,  void *dst,  const void *src);
void	atomic_destructor(type_metadata prop,  void *ptr);
status	atomic_constructor(type_metadata prop,  void *ptr);
int	atomic_compare(type_metadata prop, void *l, void *r);

#define ATOMIC_TYPE ((type_metadata){.constructor = &atomic_constructor, .destructor = &atomic_destructor, .copy = &atomic_copy, .assign = &atomic_assign, .compare = &atomic_compare})

status byte_constructor(type_metadata prop,  void *ptr);
void byte_destructor(type_metadata prop,  void *ptr);
status byte_copy(type_metadata prop,  void *dst, const void *src);
status byte_assign(type_metadata prop,  void *dst, const void *src);
int	byte_compare(type_metadata prop, void *l, void *r);

#define BYTE_TYPE ((type_metadata){.constructor = &byte_constructor, .destructor = &byte_destructor, .copy = &byte_copy, .assign = &byte_assign, .compare = &byte_compare})


size_t		distance(iterator begin, iterator end);
iterator	ft_iterator_advance(iterator it, int n);


// vector
data_type ft_vector_iterator_dereference(void *it);
int	ft_vector_iterator_compare(type_metadata prop, void *l, void *r);
void ft_vector_pop_front(container *this);
void ft_vector_pop_back(container *this);
status ft_vector_push_front(container *this, data_type data);
status ft_vector_push_back(container *this, data_type data);
iterator	ft_vector_erase_one(container *this, iterator it);
iterator	ft_vector_erase_range(container *this, iterator begin, iterator end);
status	ft_vector_insert_range(container *this, iterator pos, iterator begin, iterator end);
status	ft_vector_insert_val(container *this, iterator pos, data_type val);
status	ft_vector_expand(container *dst, size_t count_more);
iterator ft_vector_end(container *this);
iterator ft_vector_begin(container *this);
void	ft_vector_destructor(container *this);
void	ft_vector_clear(container *this);
status ft_vector_copy(struct s_type_metadata meta, void *dst, const void *src);
status ft_vector(type_metadata meta, void *dst);
status ft_vector_default(type_metadata metadata, void *dst);

void *ft_vector_iterator_add(void *it, ssize_t to_add);
void		*ft_vector_iterator_decrement(void *it);
void		*ft_vector_iterator_increment(void *it);
data_type	ft_vector_iterator_dereference(void *it);
int			ft_vector_iterator_compare(type_metadata prop, void *l, void *r);

#define FT_VECTOR_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_vector_iterator_compare, .increment = &ft_vector_iterator_increment, .decrement = &ft_vector_iterator_decrement, .dereference = &ft_vector_iterator_dereference, .add = &ft_vector_iterator_add, .size = sizeof( iterator )})

// string
status ft_string(void *dst, char *str);
char	*ft_string_c_str(container *this);
status	ft_string_append(container *this, char *str);

status path_pop(container *this);
status path_push(container *this, char *component);

#define FT_STRING_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_string_iterator_compare, .increment = &ft_string_iterator_increment, .decrement = &ft_string_iterator_decrement, .dereference = &ft_string_iterator_dereference, .add = &ft_string_iterator_add, .size = sizeof( iterator )})

// list

status		ft_list_default(type_metadata metadata, void *dst);
status		ft_list(type_metadata meta, void *dst);
status		ft_list_copy(struct s_type_metadata meta, void *dst, const void *src);
void		ft_list_destructor(container *this);
iterator	ft_list_begin(container *this);
iterator	ft_list_end(container *this);
void		ft_list_clear(container *this);
status		ft_list_insert_val(container *this, iterator pos, data_type val);
status		ft_list_insert_range(container *this, iterator pos, iterator begin, iterator end);
iterator	ft_list_erase_one(container *this, iterator it);
iterator	ft_list_erase_range(container *this, iterator begin, iterator end);

int			ft_list_iterator_compare(type_metadata prop, void *l, void *r);
data_type	ft_list_iterator_dereference(void *it);
void		*ft_list_iterator_increment(void *it);
void		*ft_list_iterator_decrement(void *it);


#define FT_LIST_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_list_iterator_compare, .increment = &ft_list_iterator_increment, .decrement = &ft_list_iterator_decrement, .dereference = &ft_list_iterator_dereference, .size = sizeof( iterator )})

// btree

iterator	ft_btree_find(container *this, data_type key);
//iterator	ft_btree_find_recurse(container *this, btree_node *current, data_type key);
void		ft_btree_destructor(container *this);
void		ft_btree_clear(container *this);
status		ft_btree_copy(struct s_type_metadata meta, void *dst, const void *src);
iterator	ft_btree_end(container *this);
iterator	ft_btree_begin(container *this);
status		ft_btree(type_metadata value, void *dst);
status		ft_btree_default(type_metadata metadata, void *dst);
iterator	ft_btree_insert_val(container *this, data_type val);
void		ft_btree_erase_one(container *this, iterator *it);

int			ft_btree_iterator_compare(type_metadata prop, void *l, void *r);
data_type	ft_btree_iterator_dereference(void *it);
void		*ft_btree_iterator_increment(void *it);
void		*ft_btree_iterator_decrement(void *it);
data_type	ft_btree_iterator_get_key(void *it);

#define FT_BTREE_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_btree_iterator_compare, .increment = &ft_btree_iterator_increment, .decrement = &ft_btree_iterator_decrement, .dereference = &ft_btree_iterator_dereference, .size = sizeof( iterator )})


#endif
