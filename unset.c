/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:33:45 by lybey             #+#    #+#             */
/*   Updated: 2024/11/08 22:54:13 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp	*search_envp(t_envp *envp, char *key)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if ((ft_len_mini(key) == ft_len_mini(tmp->key)) && !ft_strncmp(tmp->key,
				key, ft_len_mini(key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_free_unset(t_envp *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
/*

EXEMPLE 1:
	env = [
		USER=MOHA
		TEST=AVION
		FUN=MAISON
	]

	unset USER

	on rentre dans le premier if car la variable a unset est la premiere variable de l'env

	tmp pointe sur USER
	on fait avancer la liste chainee ENV de 1
	donc env = [ 
		TEST=AVION
		FUN=MAISON
	]
	on free tmp donc on free le mailon USER

EXEMPLE 2:
	env = [
		ORDINATEUR=ECRAN
		MINISHELL=FOUTU
		SMOOTH=OPERATOR
		SINTHU=SANTOS
		KHALID=HERO
	]

	unset SINTHU

	on rentre pas dans le premier if car la variable a unset n'est pas la premiere variable de l'environnement
	
	tmp pointe sur MINISHELL
	on boucle tant que tmp->key n'est pas egal a SINTHU
	prev pointera donc sur SMOOTH a la fin de la boucle

	on rentre dans le if d'apres car TMP == SINTHU
	on dit que le prev (donc SMOOTH) pointera sur le maillon apres SINTHU (donc KHALID)
	puis on free TMP car tmp pointe sur SINTHU
*/

void	ft_delone_unset(t_envp **env, char *key)
{
	t_envp	*tmp;
	t_envp	*prev;

	// garder le prev
	prev = *env;

	// si le premier maillon est la variable a unset
	if (env && !ft_strcmp((*env)->key, key))
	{
		// on garde le premier pointeur sur l'env
		tmp = (*env);

		// on fait avancer l'env de un maillon
		(*env) = (*env)->next;

		// on supprime la variable a unset
		ft_free_unset(tmp);
		free(key);
		return ;
	}

	// on met tmp sur la 2ieme variable de l'env
	tmp = (*env)->next;

	// on boucle jusqua cquon trouve la key
	while (tmp && ft_strcmp(tmp->key, key))
	{
		// on stocke le precedent
		prev = prev->next;

		// on avance de 1 a chaque tour de boucle
		tmp = tmp->next;
	}

	// si jamais on est tombe sur la variable a unset dans l;env
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		// on dit que le precedent pointe sur celui d'apres
		prev->next = tmp->next;

		// on free le maillon a unset
		ft_free_unset(tmp);
	}
}



void	unset_loop(char **cmd, t_envp *envp, int nb_cmd)
{
	// t_envp	*to_unset;
	// t_envp	*tmp;
	int		i;

	i = 1;
	(void)nb_cmd;
	while (cmd[i])
	{
		ft_delone_unset(&envp, cmd[i++]);
		// tmp = envp;
		// to_unset = search_envp(envp, cmd[i]);
		// i++;
		// if (!to_unset)
		// 	continue ;
		// if (tmp == to_unset)
		// 	*envp = *envp->next;
		// while (tmp && tmp != to_unset)
		// {
		// 	if (tmp->next && tmp->next == to_unset)
		// 	{
		// 		if (to_unset->next)
		// 			tmp->next = to_unset->next;
		// 		else
		// 			tmp->next = NULL;
		// 		free(envp->key);
		// 		free(envp->value);
		// 		free(to_unset);
		// 		break ;
		// 	}
		// 	tmp = tmp->next;
		// }
	}
}

int	ft_unset(char **cmd, t_envp *envp)
{
	int nb_cmd;

	nb_cmd = arg_len(cmd);
	if (nb_cmd < 2)
		return (printf("no variable to be deleted\n"), 0);
	else
		unset_loop(cmd, envp, nb_cmd);
	return (0);
}

// export a=a?
// puis
// unset a
// ls
// quand tu lances lenvironnement se met mal a jour 