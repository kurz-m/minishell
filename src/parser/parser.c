#include "minishell.h"

t_cmd	*parsepipe(t_cmd *cmd, t_dlist *head)
{
	while(((t_token *)head->content)->type != TOKEN_EOF)
	{
		if (((t_token *)head->content)->type == TOKEN_PIPE)
		{
				pipe = (t_pipecmd){
					.type = PIPE,
					.left = NULL,
					.right = NULL
				};
		}
		head = head->next;
	}
}

t_cmd	*ft_parser(t_lexer *lexer)
{
	t_dlist	*head;
	t_cmd	*tree_head;

	head = lexer->token_list;
	tree_head = NULL;
	while(((t_token *)head->content)->type != TOKEN_EOF)
	{
		// search for pipe
		tree_head = parsepipe(tree_head, head)
		// search for redirect
		head = head->next;
	}
}
