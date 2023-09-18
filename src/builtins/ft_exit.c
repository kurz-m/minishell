#include "minishell.h"

static int	check_exit_argument(char *argv)
{
	if (*argv == '-' && ft_strlen(argv) == 1)
		return (2);
	++argv;
	while (*(++argv) != '\0')
	{
		if (ft_isdigit(*argv) == 0)
			return (2);
	}
	return (0);
}

static int	normalize_exit_code(int exit_code)
{
	if (exit_code >= 0)
		return (exit_code % 256);
	return (256 + (exit_code % 256));
}

int	ft_exit(t_execcmd *cmd)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->argv[1] == NULL)
		return (*get_exit_status());
	if (cmd->argv[2] != NULL)
	{
		print(2, "minishell: exit: too many arguments\n");
		return (127);
	}
	exit_code = check_exit_argument(cmd->argv[1]);
	if (exit_code == 2)
		return (exit_code);
	exit_code = normalize_exit_code(ft_atoi(cmd->argv[1]));
	return (exit_code);
}
