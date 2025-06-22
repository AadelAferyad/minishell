#include <collector.h>


int	main(void)
{
	char	**s;

	head = NULL;
	s = safe_malloc(sizeof(char *) * 4);
	for (int i = 0; i < 4; i++)
	{
		s[i] = safe_malloc(sizeof(char) * 5);
		ft_strlcpy(s[i], "hello", 5);
	}
	printf("%p\n%p\n", s, s[0]);
	for (int i = 0; i < 4; i++)
	{
		ft_putstr_fd(s[i], 1);
		ft_putchar_fd('\n', 1);
		free_collector_one(s[i]);
	}
	free_collector_one(s);
	/*free_collector_one(s[i]);*/
	return (0);
}
