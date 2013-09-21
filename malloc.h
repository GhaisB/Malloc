#ifndef			__MALLOC_H__
#define			__MALLOC_H__


#include		<pthread.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		<sys/resource.h>

typedef	struct			__attribute__((packed))s_malloc
{
  struct	s_malloc	*next;
  struct	s_malloc	*prev;
  size_t			size;
  char				isFree;
}				t_malloc;

#define	SIZE	sizeof(t_malloc)
#define	TMP	(void *)tmp + SIZE
#define	LIST	(void *)list + SIZE
#define	NEW	(void *)new + SIZE
#define	INIT	PTHREAD_MUTEX_INITIALIZER	

extern pthread_mutex_t lock[2];

extern t_malloc		*list;
extern t_malloc		*last;
extern size_t	       	size_link;

void			free(void *ptr);
void			*malloc(size_t size);

#endif
