/*
** free.c for free in /home/dell-a_f/tentative_final
** 
** Made by florian dell-aiera
** Login   <dell-a_f@epitech.net>
** 
** Started on  Sat Feb  9 20:13:31 2013 florian dell-aiera
** Last update Sun Feb 10 01:00:40 2013 ghais
*/

#include		"malloc.h"

void                    fusion_link(t_malloc *tmp)
{
  t_malloc              *tmp2;
  size_t                sav;

  tmp2 = NULL;
  if (tmp->next && tmp->next->isFree == 1 && tmp->next->next)
    {
      tmp->size += tmp->next->size + SIZE;
      tmp->next->next->prev = tmp;
      tmp->next = tmp->next->next;
      if (!tmp->next)
        last = tmp;
    }
  tmp2 = last;
  if (tmp2 && tmp2->isFree == 1 && tmp2->prev && tmp2->prev->isFree == 1)
    {
      tmp2->prev->size += tmp2->size + SIZE;
      tmp2->prev->next = NULL;
      last = tmp2->prev;
    }
}

void			free(void *ptr)
{
  t_malloc		*tmp;
  int			a = 0;

  pthread_mutex_lock(&lock[0]);
  tmp = list;
  if (ptr == NULL || !tmp)
    {
      pthread_mutex_unlock(&lock[0]);
      return ;
    }
  while (tmp && tmp->next && TMP != ptr)
    tmp = tmp->next;
  if (TMP != ptr)
    {
      size_link = 0;
      pthread_mutex_unlock(&lock[0]);
      return ;
    }
  tmp->isFree = 1;
  size_link = tmp->size;
  fusion_link(tmp);
  pthread_mutex_unlock(&lock[0]);
  return ;
}

void			show_alloc_mem()
{
  t_malloc			*tmp;

  tmp = list;
  printf("break : %p\n", sbrk(0));
  while (tmp)
    {
      printf("%p - %p : %ld octets \n", TMP, TMP + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}
