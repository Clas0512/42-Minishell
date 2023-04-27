#include "minishell.h"

void    tokenize_q_str(t_lex *info, int wd, char flag)
{
    info->flags[wd] = flag;
    info->b = 0;
}
