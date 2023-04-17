#include "minishell.h"

//when cd is called this function will change the current working directory and the PWD and OLDPWD environment variables
void	changenewpwd()
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	pwd = NULL;
	oldpwd = NULL;
	tmp = NULL;
	pwd = get_pwd();
	oldpwd = get_env("PWD");
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	set_env(tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", pwd);
	set_env(tmp);
	free(tmp);
	free(pwd);
	free(oldpwd);
}

//will change the current working directory
void	change_dir(char **cdargs)
{
	char	*tmp;

	tmp = NULL;
	if (cdargs[1] == NULL)
	{
		tmp = get_env("HOME");
		if (tmp == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		chdir(tmp);
		free(tmp);
	}
	else if (cdargs[1] != NULL)
	{
		if (ft_strncmp(cdargs[1], "-", 1) == 0)
		{
			tmp = get_env("OLDPWD");
			if (tmp == NULL)
			{
				printf("minishell: cd: OLDPWD not set\n");
				return ;
			}
			chdir(tmp);
			free(tmp);
		}
		else if (ft_strncmp(cdargs[1], "~", 1) == 0)
		{
			tmp = get_env("HOME");
			if (tmp == NULL)
			{
				printf("minishell: cd: HOME not set\n");
				return ;
			}
			chdir(tmp);
			free(tmp);
		}
		else if (ft_strncmp(cdargs[1], "/", 1) == 0)
		{
			if (chdir(cdargs[1]) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
				return ;
			}
		}
		else if (ft_strncmp(cdargs[1], ".", 1) == 0)
		{
			if (chdir(cdargs[1]) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
				return ;
			}
		}
		else if (ft_strncmp(cdargs[1], "..", 2) == 0)
		{
			if (chdir(cdargs[1]) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
				return ;
			}
		}
		else
		{
			if (chdir(cdargs[1]) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", cdargs[1]);
				return ;
			}
		}
	}
	else if (cdargs[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	changenewpwd();
}
