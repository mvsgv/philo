/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:07:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 17:06:25 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//the goal is to create a short main code to control the error returns
// of the function from malloc as well as from the pthread fucntions

// EINVAL -> The function received an invalid argument.
// EDEADLK -> A deadlock condition was detected when trying to acquire a lock.
// EBUSY -> The requested resource is busy and cannot be used.
// ENOMEN -> Insufficient memory available for allocation.
// EPERM -> 

//The declaration void *(*foo)(void *) is a pointer
// to a function that takes a void * argument and returns a void *
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(sizeof(bytes));
	if (ret == NULL)
		ft_exit_error ("Error with the malloc");
	return (ret);
}

static	void	handle_mutex_errors(int status, t_opcode opcode)
{
	 if (status == 0)
	 	return ;
	else if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		ft_exit_error("The value specified by mutex in invalid.");
	else if (EINVAL == status && opcode == INIT)
		ft_exit_error("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		ft_exit_error("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (EPERM == status)
		ft_exit_error("Mutex not owned by the calling thread.");
	else if (ENOMEM == status)
		ft_exit_error("Insufficient memory available for allocation.");
	else if (EBUSY == status)
		ft_exit_error("The requested resource is busy and cannot be used.");	
}

static void		handle_pthread_errors(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		ft_exit_error("No resources to create another thread");
	else if (EINVAL == status && (opcode == DETACH || opcode == JOIN))
		ft_exit_error("The implementation has detected that the value specified "
		" by thread does not refer to a joinable thread.");
	else if (EINVAL == status && (opcode== CREATE))
		ft_exit_error("The value specified by attr is invalid.");
	else if (ESRCH == status)
		ft_exit_error("No thread could be found corresponding to that specified "
			"by the given thread ID, thread.");
	else if (EPERM == status)
		ft_exit_error("The caller does not have appropriate permission");
	else if (EDEADLK == status)
		ft_exit_error("A deadlock was detected or the value of"
			"thread specifies the calling thread");
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_errors(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_errors(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_errors(pthread_mutex_destroy(mutex), opcode);
	else 
		ft_exit_error("Wrong opcode for mutex");
}
void	safe_thread(pthread_t *thread, void *(*foo)(void*),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_pthread_errors(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_pthread_errors(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_pthread_errors(pthread_detach(*thread), opcode);
	else 
		ft_exit_error("Wrong opcode for handle_thread:"
			" use <CREATE> <JOIN> <DETACH>");
}

