/*
** malloc.c for malloc in /home/dell-a_f/projets/Malloc
** 
** Made by florian dell-aiera
** Login   <dell-a_f@epitech.net>
** 
** Started on  Tue Feb  5 18:58:52 2013 florian dell-aiera
** Last update Sun Feb 10 20:23:48 2013 ghais
*/

#include		"malloc.h"

t_malloc		*list = NULL;
t_malloc		*last = NULL;
size_t			size_link = 0;

pthread_mutex_t lock[2] = {INIT, INIT};

#define up(x)	(((((x ) - 1 ) >> 2) << 2 ) + 4)

void           *research_free_link(size_t size)
{
  t_malloc              *tmp;
  t_malloc              *perfect;

  tmp = list;
  perfect = NULL;
  while (tmp)
    {
      if (tmp->isFree == 1 && tmp->size > size)
        {
          if (!perfect || perfect->size < tmp->size)
            perfect = tmp;
        }
      tmp = tmp->next;
    }
  if (perfect)
    {
      perfect->size = size;
      perfect->isFree = 0;
      return ((void*)perfect + SIZE);
    }
  return (NULL);
}

void			*first_link(size_t size)
{
  list =  sbrk(SIZE + size);
  if (list == (void*) -1)
    return (list = NULL);
  list->prev = NULL;
  list->next = NULL;
  list->isFree = 0;
  list->size = size;
  last = list;
  return (LIST);
}

void			*create_link(size_t size)
{
  t_malloc		*tmp;
  t_malloc		*new;
  void			*addr;

  pthread_mutex_lock(&lock[0]);
  addr = NULL;
  tmp = list;
  if (!list)
    return ((pthread_mutex_unlock(&lock[0]) != 0) ? NULL : first_link(size));
  if ((addr = research_free_link(size)) != NULL)
    return ((pthread_mutex_unlock(&lock[0]) != 0) ? NULL : addr);
  new =  sbrk(SIZE + size);
  tmp = last;
  if (new == (void *) -1)
    return ((pthread_mutex_unlock(&lock[0]) != 0) ? NULL : NULL);
  new->size = size;
  new->isFree = 0;
  new->prev = tmp;
  new->next = NULL;
  last = new;
  tmp->next = new;
  pthread_mutex_unlock(&lock[0]);
  return (NEW);
}

void			*malloc(size_t size)
{
  return (create_link(size));
}
