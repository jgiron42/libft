#ifndef LIBFT_CONTAINERS_H
#define LIBFT_CONTAINERS_H
#include <unistd.h>
#include <wchar.h>
# include "ft_def.h"

typedef enum {
	FT_VECTOR,
	FT_BST,
	FT_LIST,
	FT_BHEAP
}		container_type;

typedef void*  data_type;

typedef enum {
	FT_SEQUENCE_CONTAINER,
	FT_ASSOCIATIVE_CONTAINER,
}	container_interface_type;

struct s_container;
typedef struct s_type_metadata {
	container_interface_type interface_type;
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
	data_type 	*(*reference)(void* this);
	union {
		struct {
			struct s_iterator	(*begin)(struct s_container *);
			struct s_iterator	(*end)(struct s_container *);
			void				(*clear)(struct s_container *this);
			struct s_iterator	(*erase_one)(struct s_container *this, struct s_iterator it);
			struct s_iterator	(*erase_range)(struct s_container *this, struct s_iterator begin, struct s_iterator end);
			union {
				struct {
					status	(*push_front)(struct s_container *, data_type);
					status	(*push_back)(struct s_container *, data_type);
					status	(*push_front_ptr)(struct s_container *, data_type*);
					status	(*push_back_ptr)(struct s_container *, data_type*);
					void	(*pop_front)(struct s_container *);
					void	(*pop_back)(struct s_container *);
					status	(*insert_range)(struct s_container *this, struct s_iterator pos, struct s_iterator begin, struct s_iterator end);
					status	(*insert_count)(struct s_container *this, struct s_iterator pos, data_type val, size_t count);
					status	(*insert_val)(struct s_container *this, struct s_iterator pos, data_type val);
				} sequence;
				struct {
					struct s_iterator (*insert)(struct s_container *, data_type);
					struct s_iterator (*erase)(struct s_container *, data_type);
					struct s_iterator (*find)(struct s_container *, data_type);
				} associative;
			};
		} container;
	};
	size_t size;
}	type_metadata;

typedef struct s_bst_node {
	struct s_bst_node *right;
	struct s_bst_node *left;
	struct s_bst_node *parent;
	union {
		enum {
			FT_RB_RED,
			FT_RB_BLACK,
		}	color;
		char balance_factor;
	};
	data_type data;
}			bst_node;

typedef struct s_list_node {
	data_type data;
	struct s_list_node *next;
	struct s_list_node *prev;
}	list_node;

struct s_iterator;

typedef struct s_container {
	container_type	type;
	bool			init : 1;
	type_metadata	value_type_metadata;
	type_metadata	metadata;
	size_t			size;
	int				value_type_size;
	union {
		struct {
			char *data;
			size_t capacity;
			int align;
		} vector;
		struct {
			char	*data;
			size_t	capacity;
		}	string;
		struct {
			list_node past_the_end;
		}	list;
		struct {
			bst_node *first;
			bst_node *last;
			bst_node past_the_end;
			enum {
				SIMPLE = 0,
				RED_BLACK,
				AVL
			}			type;
			bool		multi : 1; // true if multiset
		}	bst;
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
			bst_node	*current;
		}	bst;
	};
}		iterator;

#define for_in(it, cont) for (iterator it = (cont).begin(&(cont)), end = (cont).end(&(cont)); (it).metadata.compare((it).metadata, (void *) &(it), (void *) &end); (it).metadata.increment(&(it)))
// cursed macro but gives a cool way to iterate over a container (for_val_in(data_type val, cont) { ... })
#define for_val_in(val, cont) for (iterator cursed_it = (cont).begin(&(cont)), end = (cont).end(&(cont)); (cursed_it).metadata.compare((cursed_it).metadata, (void *) &(cursed_it), (void *) &end); (cursed_it).metadata.increment(&(cursed_it))) for(int cursed = 0; cursed==0;) for(val = cursed_it.metadata.dereference(&cursed_it);cursed==0;cursed++)

// generic:

void	ft_pop_front(container *this);
void	ft_pop_back(container *this);
status	ft_push_front(container *this, data_type data);
status	ft_push_back(container *this, data_type data);
iterator	ft_erase_range(container *this, iterator begin, iterator end);
iterator	ft_find(container *this, data_type val);
iterator	ft_erase_val(container *this, data_type val);
int			ft_compare(container *l, container *r);

status	pointer_assign(type_metadata prop,  void *dst, const void *src);
status	pointer_copy(type_metadata prop,  void *dst,  const void *src);
void	pointer_destructor(type_metadata prop,  void *ptr);
status	pointer_constructor(type_metadata prop,  void *ptr);
int	pointer_compare(type_metadata prop, void *l, void *r);

#define POINTER_TYPE(pointed_type) ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &pointer_compare, .size = sizeof( pointed_type )})

status	cstring_constructor(type_metadata prop,  void *ptr);
void	cstring_destructor(type_metadata prop,  void *ptr);
status	cstring_copy(type_metadata prop,  void *dst, const void *src);
status	cstring_assign(type_metadata prop,  void *dst, const void *src);
int		cstring_compare(type_metadata prop, void *l, void *r);

#define CSTRING_TYPE ((type_metadata){.constructor = &cstring_constructor, .destructor = &cstring_destructor, .copy = &cstring_copy, .assign = &cstring_assign, .compare = &cstring_compare, .size = sizeof( char * )})

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

status ft_vector(type_metadata type_metadata, void *dst);
data_type ft_vector_iterator_dereference(void *it);
int	ft_vector_iterator_compare(type_metadata prop, void *l, void *r);
void ft_vector_pop_front(container *this);
void ft_vector_pop_back(container *this);
status ft_vector_push_front(container *this, data_type data);
status ft_vector_push_back(container *this, data_type data);
iterator	ft_vector_erase_one(container *this, iterator it);
iterator	ft_vector_erase_range(container *this, iterator begin, iterator end);
status	ft_vector_insert_range(container *this, iterator pos, iterator begin, iterator end);
status	ft_vector_insert_count(container *this, iterator pos, data_type val, size_t count);
status	ft_vector_insert_val(container *this, iterator pos, data_type val);
status	ft_vector_expand(container *dst, size_t count_more);
iterator ft_vector_end(container *this);
iterator ft_vector_begin(container *this);
void	ft_vector_destructor(container *this);
void	ft_vector_destructor_wrapper(type_metadata meta, void *container);
void	ft_vector_clear(container *this);
status ft_vector_copy(struct s_type_metadata meta, void *dst, const void *src);
status ft_vector(type_metadata meta, void *dst);
status ft_vector_default(type_metadata metadata, void *dst);
data_type ft_vector_at(container const *this, size_t pos);
data_type *ft_vector_at_ptr(const container *this, size_t pos);
data_type ft_vector_back(container *this);
data_type ft_vector_front(container *this);

status	ft_vector_insert_ptr(container *this, iterator pos, data_type *val);
status ft_vector_push_back_ptr(container *this, data_type *data);
status ft_vector_push_front_ptr(container *this, data_type *data);

void *ft_vector_iterator_add(void *it, ssize_t to_add);
void		*ft_vector_iterator_decrement(void *it);
void		*ft_vector_iterator_increment(void *it);
data_type	ft_vector_iterator_dereference(void *it);
data_type	*ft_vector_iterator_reference(void *it);
int			ft_vector_iterator_compare(type_metadata prop, void *l, void *r);

#define FT_VECTOR_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_vector_iterator_compare, .increment = &ft_vector_iterator_increment, .decrement = &ft_vector_iterator_decrement, .dereference = &ft_vector_iterator_dereference, .reference = &ft_vector_iterator_reference, .add = &ft_vector_iterator_add, .size = sizeof( iterator )})

// buffer
status ft_buffer(void *dst, char *buf, size_t size, size_t cap);
status ft_buffer_assign(container *this, char *buf, size_t size);

// string
status ft_string(void *dst, char *str);
char	*ft_string_c_str(container *this);
status	ft_string_append(container *this, char *str);
void	ft_string_clear(container *this);
size_t ft_string_size(const container *src);
status ft_string_push_back(container *this, data_type data);
void ft_string_pop_back(container *this);

status path_pop(container *this);
status path_push(container *this, char *component);

#define FT_STRING_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_string_iterator_compare, .increment = &ft_string_iterator_increment, .decrement = &ft_string_iterator_decrement, .dereference = &ft_string_iterator_dereference, .add = &ft_string_iterator_add, .size = sizeof( iterator )})

// list

status		ft_list_default(type_metadata metadata, void *dst);
status		ft_list(type_metadata meta, void *dst);
status		ft_list_copy(struct s_type_metadata meta, void *dst, const void *src);
void		ft_list_destructor(container *this);
void	ft_list_destructor_wrapper(type_metadata meta, void *container);
iterator	ft_list_begin(container *this);
iterator	ft_list_end(container *this);
void		ft_list_clear(container *this);
status		ft_list_insert_val(container *this, iterator pos, data_type val);
status		ft_list_insert_range(container *this, iterator pos, iterator begin, iterator end);
iterator	ft_list_erase_one(container *this, iterator it);
iterator	ft_list_erase_range(container *this, iterator begin, iterator end);
data_type	*ft_list_back(container *this);
data_type	*ft_list_front(container *this);

int			ft_list_iterator_compare(type_metadata prop, void *l, void *r);
data_type	ft_list_iterator_dereference(void *it);
void		*ft_list_iterator_increment(void *it);
void		*ft_list_iterator_decrement(void *it);


#define FT_LIST_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_list_iterator_compare, .increment = &ft_list_iterator_increment, .decrement = &ft_list_iterator_decrement, .dereference = &ft_list_iterator_dereference, .size = sizeof( iterator )})

// bst

iterator	ft_bst_find(container *this, data_type key);
//iterator	ft_bst_find_recurse(container *this, bst_node *current, data_type key);
void		ft_bst_destructor(container *this);
void		ft_bst_destructor_wrapper(type_metadata meta, void *container);
void		ft_bst_clear(container *this);
status		ft_bst_copy(struct s_type_metadata meta, void *dst, const void *src);
int			ft_bst_compare(type_metadata prop, void *l, void *r);
iterator	ft_bst_end(container *this);
iterator	ft_bst_begin(container *this);
status		ft_bst(type_metadata value, void *dst);
status		ft_bst_default(type_metadata metadata, void *dst);
iterator	ft_bst_insert_val(container *this, data_type val);
iterator	ft_bst_insert_ptr(container *this, data_type *val);
status		ft_bst_insert_range(container *this, iterator begin, iterator end);
iterator	ft_bst_erase_one(container *this, iterator it);

int			ft_bst_iterator_compare(type_metadata prop, void *l, void *r);
data_type	ft_bst_iterator_dereference(void *it);
data_type	*ft_bst_iterator_reference(void *it);
void		*ft_bst_iterator_increment(void *it);
void		*ft_bst_iterator_decrement(void *it);
data_type	ft_bst_iterator_get_key(void *it);

#define FT_BST_ITERATOR ((type_metadata){.constructor = &pointer_constructor, .destructor = &pointer_destructor, .copy = &pointer_copy, .assign = &pointer_assign, .compare = &ft_bst_iterator_compare, .increment = &ft_bst_iterator_increment, .decrement = &ft_bst_iterator_decrement, .dereference = &ft_bst_iterator_dereference, .reference = &ft_bst_iterator_reference, .size = sizeof( iterator )})

status		ft_bheap(type_metadata meta, void *dst);
data_type	ft_bheap_top(container *this);
status		ft_bheap_push(container *this, data_type data);
status		ft_bheap_push_ptr(container *this, data_type *data);
void		ft_bheap_pop(container *this);

extern const type_metadata meta[];

#endif
