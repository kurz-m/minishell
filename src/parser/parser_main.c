#include "minishell.h"

static t_cmd	*parse_redirect(t_cmd *cmd, t_dlist **tok, t_main *sh)
{
	while (check_redirect(get_token_type(*tok)) == TRUE)
	{
		if (check_arguments(get_token_type((*tok)->next)) == FALSE)
			perror("missing file");
		cmd = select_redirect(cmd, tok, sh->env);
		if (NULL == *tok)
			perror("add something about EOF");
	}
	return (cmd);
}

char	*connect_tokens(t_dlist **list, char **env)
{
	char	*expand;
	t_token	*tok;

	expand = expand_token(get_token(*list), env);
	tok = get_token(*list);
	if (check_tok_connection(tok) == FALSE)
	{
		*list = (*list)->next;
		return (expand);
	}
	*list = (*list)->next;
	while (get_token_type(*list) & (TOKEN_WORD | TOKEN_DQUOTE | TOKEN_QUOTE))
	{
		tok = get_token(*list);
		expand = ft_strjoinfree(expand, expand_token(tok, env), 'B');
		if (check_tok_connection(tok) == FALSE)
		{
			*list = (*list)->next;
			return (expand);
		}
		*list = (*list)->next;
	}
	return (expand);
}

static t_cmd	*parse_execution(t_dlist **tok, t_main *sh)
{
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	ret = execcmd(sh);
	cmd = (t_execcmd *)ret;
	ret = parse_redirect(ret, tok, sh);
	argc = 0;
	while (check_metachars(get_token_type(*tok)) == FALSE)
	{
		if (get_token_type(*tok) == TOKEN_EOF)
			break ;
		if (check_arguments(get_token_type(*tok)) == FALSE)
			perror("Add some error handling if this is wrong");
		cmd->argv[argc] = connect_tokens(tok, sh->env);
		++argc;
		if (argc >= MAXARGS)
			perror("too many input arguments for the command");
		ret = parse_redirect(ret, tok, sh);
	}
	cmd->argv[argc] = NULL;
	return (ret);
}

static t_cmd	*parse_pipe(t_dlist **tok, t_main *sh)
{
	t_cmd		*cmd;

	cmd = parse_execution(tok, sh);
	if (get_token_type(*tok) == TOKEN_PIPE)
	{
		*tok = (*tok)->next;
		cmd = pipecmd(cmd, parse_pipe(tok, sh));
	}
	return (cmd);
}

t_cmd	*parse_command(t_dlist **tok, t_main *sh)
{
	t_dlist		*keep;
	t_cmd		*cmd;

	keep = *tok;
	cmd = parse_pipe(tok, sh);
	if (get_token_type(*tok) != TOKEN_EOF)
		perror("Did not finish parsing error");
	return (cmd);
}