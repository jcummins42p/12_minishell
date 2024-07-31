/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:43:03 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/31 17:56:50 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

//	envget.c
t_envlist	*env_last(t_envlist **envlist);
t_envlist	*env_search(t_envlist **envlist, const char *search);
char		**env_get_value(t_envlist **envlist, const char *search);

//	envinit.c
int			env_new(t_envlist **envlist, const char *nparam, const char *nval);
void		env_from_str(t_envlist **envlist, char *str);
void		env_init(t_envlist **envlist, char *env[]);

//	envutils.c
void		env_print(t_envlist **envlist);
int			env_list_size(t_envlist **envlist);
void		env_string_clear(char **env);
void		env_list_clear(t_envlist **envlist);
void		env_del(t_envlist **envlist);

//	envset.c
void		env_unset_string(char **env[]);
void		env_set_string(t_envlist **envlist, char **env[]);
void		env_set(t_envlist **envlist, const char *search, const char *nval);
void		env_unset(t_envlist **envlist, const char *search);

#endif