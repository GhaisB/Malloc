/*
** realloc.c for realloc in /home/dell-a_f/tentative_final
** 
** Made by florian dell-aiera
** Login   <dell-a_f@epitech.net>
** 
** Started on  Sat Feb  9 20:20:28 2013 florian dell-aiera
** Last update Sun Feb 10 20:26:39 2013 ghais
*/

#include		<stdlib.h>
#include		<string.h>
#include		"malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
  void			*new;

  pthread_mutex_lock(&lock[1]);
  new = malloc(size * nmemb);
  if (new)
    {
      memset(new, 0, (size * nmemb));
      pthread_mutex_unlock(&lock[1]);
      return (new);
    }
  pthread_mutex_unlock(&lock[1]);
}

void			*act_realloc(void *ptr, size_t taille)
{
  void			*copy;

  copy = NULL;
  free(ptr);
  if (size_link == 0)
    {
      pthread_mutex_unlock(&lock[1]);
      return (ptr);
    }
  copy = malloc(taille);
  copy = memcpy(copy, ptr, size_link);
  size_link = 0;
  pthread_mutex_unlock(&lock[1]);
  return (copy);
}

void			*realloc(void *ptr, size_t taille)
{
  t_malloc		*tmp;

  pthread_mutex_lock(&lock[1]);
  if (ptr == NULL)
    {
      pthread_mutex_unlock(&lock[1]);
      return (malloc(taille));
    }
  else if (taille == 0)
    free(ptr);
  else
    return (act_realloc(ptr, taille));
  pthread_mutex_unlock(&lock[1]);
  return (NULL);
}
