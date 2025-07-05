/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:42:43 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/29 23:44:07 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{ 
	int c;
	
	while((c=fgetc(f))!=EOF && isspace(c));
	if(c==EOF)
		return -1;
	ungetc(c, f);
	return 0;
}


int match_char(FILE *f, char c)
{
	int x=fgetc(f);

	if(x==EOF)
		return -1;
	if(x!=c)
	{
		ungetc(x, f);
		return 0;
	}
	return 1;
}


int scan_char(FILE *f, va_list ap)
{
	int c;
	char *x=va_arg(ap, char *);
	
	c=fgetc(f);
	if(c==EOF)
		return -1;
	*x= (char)c;
	return 1;
}


int scan_int(FILE *f, va_list ap)
{
	int i=0;
	int c=0;
	int s=1;
	int flag=0;
	int *n=va_arg(ap, int *);
	
	while((c=fgetc(f))!=EOF && isspace(c));
	if(c==EOF)
		return -1;
	if(c=='+' || c== '-')
	{
		if(c=='-')
			s*=-1;
		c=fgetc(f);
	}
	if(c==EOF)
		return -1;
	while(c!=EOF && isdigit(c))
	{
		i=(i*10)+(c -'0');
		c=fgetc(f);
		flag=1;
	}
	if(c!= EOF)
		ungetc(c, f);
	if(flag==0)
		return 0;
	(*n) = i * s;
	return 1;
}


int scan_string(FILE *f, va_list ap)
{
	int c;
	int i=0;
	char *t=va_arg(ap, char *);
	
	while((c=fgetc(f))!=EOF && isspace(c));
	if(c==EOF)
		return -1;
	while(c!=EOF && !isspace(c))
	{
		t[i]=(char)c;
		i++;
		c=fgetc(f);
	}
	t[i]='\0';
	if(c!=EOF)
		ungetc(c, f);
	if(i>0)
		return 1;
	return 0;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
    va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main()
{
	int n;
	
	int i=0;
	char c='!';
	char t[100];
		
	n=ft_scanf("%s a%d", t, &i);
	
	printf("\n c : %c \n i : %d \n s : %s\n",c , i , t);
	printf("\t> R : %d<\n", n);

	
	
	// n=scanf("%s a%d", t, &i);

	// printf("\n c : %c \n i : %d \n s : %s\n",c , i , t);
	// printf("\t> R : %d<\n", n);


}

