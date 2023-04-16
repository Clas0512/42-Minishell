#ifndef LEXER_H
# define LEXER_H

typedef struct t_lex
{
    void    *main_str;
	int		*sgn_lst;
    long    d_q;
    long    s_q;
    char    last_quotes;
    long    strlen;
    size_t    word_count;
}			s_lex;

void    quotes_current_count(s_lex *info, int i);
void    word_counter(s_lex *info);
void    init_struct(s_lex *info, char *str);
char    **lexer(char *str);
int     is_rdrct(char *str, int i);
int     is_valid_dollar(s_lex *info, int i);
int		word_control_1(s_lex *info, int i);

#endif
