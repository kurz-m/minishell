#include "minishell.h"

static char	*check_whole_env(char **env, char *name)
{
	char	**check;

	if (*name != '$')
		return (ft_strdup(name));
	check = env;
	while (NULL != *check)
	{
		if (check_env_variable(*check, name + 1) == TRUE)
			return (ft_strdup(*check + ft_strlen_c(*check, '=') + 1));
		++check;
	}
	return (ft_strdup(""));
}

static char	*create_expanded_string(t_list *run, char **env)
{
	char	*expand;
	char	*add;
	char	*key;

	expand = ft_strdup("");
	while (run)
	{
		key = run->content;
		if (ft_strlen(key) <= 2)
			add = expand_special(key);
		else
			add = check_whole_env(env, key);
		expand = ft_strjoinfree(expand, add, 'B');
		key = NULL;
		run = run->next;
	}
	return (expand);
}

char	*expand_token(t_token *tok, char **env)
{
	char	*input;
	int		amount;
	t_list	*keylist;
	char	*expand;

	input = ft_strndup(tok->value, tok->len);
	if (tok->type == TOKEN_QUOTE)
		return (input);
	keylist = create_keylist(input);
	expand = create_expanded_string(keylist, env);
	adv_free(&input);
	ft_lstclear(&keylist, &free);
	return (expand);
}