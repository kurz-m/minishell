#include "defines.h"
#include "signals.h"
#include "utils.h"

#define RED_PROMPT "\e[m\e[0;31m❯ \e[m"

/* `<SUMMARY>`:
 * Function for handling the SIGINT signal. SIGINT represents
 * the signal provoked by pressing ctrl+c and the exit code 130.
 * `<PARAM>`:
 * `signum`: integer represents the signal to handle.
 * Located in signal_handling.c. */
static void	termination_handler(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_set_prompt(RED_PROMPT);
	rl_on_new_line();
	rl_redisplay();
	history_set_pos(history_length);
	set_exit_status(128 + signum);
}

/* `<SUMMARY>`:
 * Generic function to invoke signal handler with the default
 * presets..
 * `<PARAM>`:
 * `sig`: integer represents the signal to handle.
 * `handler`: pointer to the handler function.
 * Located in signal_handling.c. */
static void	universal_handler(int sig, t_handler *handler)
{
	t_signal	action;

	sigemptyset(&action.sa_mask);
	action = (t_signal){
		.sa_handler = handler,
		.sa_flags = SA_RESTART | SA_SIGINFO
	};
	sigaction(sig, &action, NULL);
}

void	wait_user_signals(void)
{
	universal_handler(SIGINT, termination_handler);
	universal_handler(SIGQUIT, SIG_IGN);
}

int	user_signal_listener(t_termios *xterm)
{
	cleanup_control_character(xterm);
	universal_handler(SIGINT, termination_handler);
	universal_handler(SIGQUIT, SIG_IGN);
	return (EXIT_SUCCESS);
}

void	block_parent_handler(void)
{
	universal_handler(SIGINT, SIG_IGN);
	universal_handler(SIGQUIT, SIG_IGN);
}

void	heredoc_child_handler(void)
{
	universal_handler(SIGINT, exit_heredoc);
	universal_handler(SIGQUIT, SIG_IGN);
}
