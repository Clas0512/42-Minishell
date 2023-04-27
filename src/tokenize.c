#include "minishell.h"

// void    check_path(t_lex *info, char *line, int i)
// {
//     if (ft_strcmp((line + i), "$path", 5) == 0 || ft_strcmp((line + i), "$PATH", 5) == 0)
//     {

//     }
// }

void    tokenize_q_str(t_lex *info, int wd, char flag)
{
    info->flags[wd] = flag;
    info->b = 0;
}
