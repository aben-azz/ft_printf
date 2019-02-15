/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/15 21:28:23 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft/includes/libft.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// printf("|%i,%i|\n",
	// count_flags(argv[1], ft_atoi(argv[2]))[0],
	// count_flags(argv[1], ft_atoi(argv[2]))[1]);
	// get_flags(argv[1], count_flags(argv[1], 0)[1]);
	// printf("xddddddd\n");
	// t_fmt flag = format("ui", 10);
	// t_fmt *flags = malloc(sizeof(flag) * 4);
	// 		flags[0] = format("ui", 10);
	// 		flags[1] = format("ui", 10);
	// 		flags[2] = format("ui", 10);
	// printf("%d,%d,%d,%d,%d\n", flag.precision, flag.length, flag.type, flag.minimal_length, flag.options);
	// printf("XDDD\n%d,%d,%d,%d,%d\n%d,%d,%d,%d,%d\n",
	// 	flags[0].precision, flags[0].length, flags[0].type, flags[0].minimal_length, flags[0].options,
	// 	flags[1].precision, flags[1].length, flags[1].type, flags[1].minimal_length, flags[1].options);
	// printf("________________________\n");
	//get_flags(argv[1], count_flags(argv[1], ft_atoi(argv[2]))[1]);
	//int a = ft_printf("xd\n%siu\n%s\nuiui%s: int: %d,%f\n", "mdr", "PTDR PRINTF", "xd", 1888, 18.21121);
	//int a = printf("xd: % -+012.13lhhhllls\n", 12);
	//printf("a vaut %d\n", a);
	// int o = get_options(argv[1]);
	// printf("types: %d\n", get_type(argv[1]));
	// int s = get_length(argv[1]);
	// printf("L:%d\nLL:%d\nH:%d\nHH:%d\nresult:%d\n",
	// 	s == L_,

	// 	s == LL_,
	// 	s == H_,
	// 	s == HH_,
	// 	s);
	// int type = get_type(argv[1]);
	// printf("c: %d\ns: %d\np: %d\nd: %d\ni: %d\no: %d\nu: %d\nX: %d\nx: %d\n",
	//  C_ == type,
	//  S_ == type,
	//  P_ == type,
	//  D_ == type,
	//  I_ == type,
	//  O_ == type,
	//  U_ == type,
	//  X_ == type,
	//  LOWX_ == type);
	// int length = get_minimal_lengths(argv[1]);
	//int precisions = get_precision(argv[1]);
	//printf("-------------\nprecision: %d\n", precisions);
	//view_fmt(xd, count_flags(argv[1], 0)[1]);
	//view_fmt(flags, 3);
	//t_fmt flag = format(argv[1], 10);
	 // printf("L:%d\nLL:%d\nH:%d\nHH:%d\n",
	 // 	flag.length == L_,
	 // 	flag.length == LL_,
	 // 	flag.length == H_,
	 // 	flag.length == HH_);
	 // printf("c: %d\ns: %d\np: %d\nd: %d\ni: %d\no: %d\nu: %d\nX: %d\nx: %d\n",
		//  C_ == flag.type,
		//  S_ == flag.type,
		//  P_ == flag.type,
		//  D_ == flag.type,
		//  I_ == flag.type,
		//  O_ == flag.type,
		//  U_ == flag.type,
		//  X_ == flag.type,
		//  LOWX_ == flag.type);
	//t_fmt *flags = get_flags((char*)argv[1],
	//						count_flags((char*)argv[1], 0)[1]);
	//ft_repeat_char(, 1);
	//char c = 'u';
	//format_string((char)c, 7, 0, 1);
	//ft_printf("|%-05.2s|%-010c|xd\n", "test", 'x');
	//printf("|%p|\n", p);
	// char* str = malloc(100);
	//long double ff = 18.567454564564568;
	// ft_ftoa(ff, 30, str);
	// printf("|%.30f|\n",ff);
	// printf("|%s|\n", str);
	//
	// long double n = 9.1465555533234545456465456465465465;
	// long double n_ = -9.1465555533234545456465456465465465;
	// (void)n;
	// (void)n_;
	//
	//char *string = "{%0+10d}\n";
	//ft_printf(string, n);
	//printf(string, n);
	// char *string = "|%-#10.3d|%-#10.3x|%-#10.3X|%-#10.3u|%-#10.3o|%-#10.3p\n";
	// int n =  10;
	// int n_ = -10;
	// int a = ft_printf(string,n, n, n, n, n, n, n);
	// int ap = printf(string,n, n, n, n, n, n, n);
	// int b = ft_printf(string,n_, n_,n_, n_, n_, n_, n_);
	// int bp = printf(string, n_, n_,n_,n_, n_, n_, n_);
	// printf("%d == %d && %d == %d\n", a, ap, b, bp);
	// ft_printf("|%20p|\n", "xd");
	// printf("|%20p|\n", "xd");
	// // printf(string, -5);
	// ft_printf(string, 5);
	//wchar_t t = L'\u00C6';
	//wchar_t *star = L"0x26050x2605";
    //printf("\n");
	// printf("OCTAL____\n");
	    ft_printf ("printf1     :|%5o|%5.3o|%5.1o|%5.0o|%5.o|\n", 0,0,0,0,0);
		   printf ("ft_printf1  :|%5o|%5.3o|%5.1o|%5.0o|%5.o|\n\n", 0,0,0,0,0);
		//2
	    ft_printf ("printf2     :|%#5o|%#5.3o|%#5.1o|%#5.0o|%#5.o|\n", 0,0,0,0,0);
		   printf ("ft_printf2  :|%#5o|%#5.3o|%#5.1o|%#5.0o|%#5.o|\n\n", 0,0,0,0,0);
		//3
		ft_printf ("printf3     :|%-#5o|%-#5.3o|%-#5.1o|%-#5.0o|%-#5.o|\n", 0,0,0,0,0);
		   printf ("ft_printf3  :|%-#5o|%-#5.3o|%-#5.1o|%-#5.0o|%-#5.o|\n\n", 0,0,0,0,0);
		//4
		ft_printf ("printf4     :|%0#5o|%0#5.3o|%0#5.1o|%0#5.0o|%0#5.o|\n", 0,0,0,0,0);
		   printf ("ft_printf4  :|%0#5o|%0#5.3o|%0#5.1o|%0#5.0o|%0#5.o|\n\n", 0,0,0,0,0);
		//5
		ft_printf ("printf5     :|%-0#5o|%-0#5.3o|%-0#5.1o|%-0#5.0o|%-0#5.o|\n", 0,0,0,0,0);
		   printf ("ft_printf5  :|%-0#5o|%-0#5.3o|%-0#5.1o|%-0#5.0o|%-0#5.o|\n\n", 0,0,0,0,0);
	//
	// 	//HEXA\\
	//
	// 	//1
	// 	printf("HEX____\n");
	// 	printf ("printf1     :|%5x|%5.3x|%5.1x|%5.0x|%5.x|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf1  :|%5x|%5.3x|%5.1x|%5.0x|%5.x|\n\n", 0,0,0,0,0);
	// 	//2
	// 	printf ("printf2     :|%#5x|%#5.3x|%#5.1x|%#5.0x|%#5.x|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf2  :|%#5x|%#5.3x|%#5.1x|%#5.0x|%#5.x|\n\n", 0,0,0,0,0);
	// 	//3
	// 	printf ("printf3     :|%-#5x|%-#5.3x|%-#5.1x|%-#5.0x|%-#5.x|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf3  :|%-#5x|%-#5.3x|%-#5.1x|%-#5.0x|%-#5.x|\n\n", 0,0,0,0,0);
	// 	//4
	// 	printf ("printf4     :|%0#5x|%0#5.3x|%0#5.1x|%0#5.0x|%0#5.x|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf4  :|%0#5x|%0#5.3x|%0#5.1x|%0#5.0x|%0#5.x|\n\n", 0,0,0,0,0);
	// 	//5
	// 	printf ("printf5     :|%-0#5x|%-0#5.3x|%-0#5.1x|%-0#5.0x|%-0#5.x|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf5  :|%-0#5x|%-0#5.3x|%-0#5.1x|%-0#5.0x|%-0#5.x|\n\n", 0,0,0,0,0);
	//
	// 	//P\\
	//
	// 	//1
	// 	printf("POINTER____\n");
	// 	printf ("printf1     :|%7p|%7.3p|%7.1p|%7.0p|%7.p|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf1  :|%7p|%7.3p|%7.1p|%7.0p|%7.p|\n\n", 0,0,0,0,0);
	// 	//2
	// 	printf ("printf2     :|%#7p|%#7.3p|%#7.1p|%#7.0p|%#7.p|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf2  :|%#7p|%#7.3p|%#7.1p|%#7.0p|%#7.p|\n\n", 0,0,0,0,0);
	// 	//3
	// 	printf ("printf3     :|%-#7p|%-#7.3p|%-#7.1p|%-#7.0p|%-#7.p|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf3  :|%-#7p|%-#7.3p|%-#7.1p|%-#7.0p|%-#7.p|\n\n", 0,0,0,0,0);
	// 	//4
	// 	printf ("printf4     :|%0#7p|%0#7.3p|%0#7.1p|%0#7.0p|%0#7.p|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf4  :|%0#7p|%0#7.3p|%0#7.1p|%0#7.0p|%0#7.p|\n\n", 0,0,0,0,0);
	// 	//5
	// 	printf ("printf5     :|%-0#7p|%-0#7.3p|%-0#7.1p|%-0#7.0p|%-0#7.p|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf5  :|%-0#7p|%-0#7.3p|%-0#7.1p|%-0#7.0p|%-0#7.p|\n\n", 0,0,0,0,0);
	//
	//
	// 	//DECI\\
	//
	// 	//1
	// 	printf("decimal____\n");
	// 	printf ("printf1     :|%+ 5d|%+ 5.3d|%+ 5.1d|%+ 5.0d|%+ 5.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf1  :|%+ 5d|%+ 5.3d|%+ 5.1d|%+ 5.0d|%+ 5.d|\n\n", 0,0,0,0,0);
	// 	//2
	// 	printf ("printf2     :|% 5d|% 5.3d|% 5.1d|% 5.0d|% 5.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf2  :|% 5d|% 5.3d|% 5.1d|% 5.0d|% 5.d|\n\n", 0,0,0,0,0);
	// 	//3
	// 	printf ("printf3     :|%-+5d|%-+5.3d|%-+5.1d|%-+5.0d|%-+5.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf3  :|%-+5d|%-+5.3d|%-+5.1d|%-+5.0d|%-+5.d|\n\n", 0,0,0,0,0);
	// 	//4
	// 	printf ("printf4     :|%0+5d|%0+5.3d|%0+5.1d|%0+5.0d|%0+5.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf4  :|%0+5d|%0+5.3d|%0+5.1d|%0+5.0d|%0+5.d|\n\n", 0,0,0,0,0);
	// 	//5
	// 	printf ("printf5     :|%-+05d|%-+05.3d|%-+05.1d|%-+05.0d|%-+05.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf5  :|%-+05d|%-+05.3d|%-+05.1d|%-+05.0d|%-+05.d|\n\n", 0,0,0,0,0);
	// 	//6
	// 	printf ("printf6     :|% 05d|% 05.3d|% 05.1d|% 05.0d|% 05.d|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf6  :|% 05d|% 05.3d|% 05.1d|% 05.0d|% 05.d|\n\n", 0,0,0,0,0);
	// 	//7
	// 	printf("printf7      :|% 03d|\n", 0);
	// 	ft_printf("ft_printf7   :|% 03d|\n", 0);
	//
	// 	//unsigned\\
	// 	//1
	// 	printf("UNSIGNED____\n");
	// 	printf ("printf1     :|%+ 5u|%+ 5.3u|%+ 5.1u|%+ 5.0u|%+ 5.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf1  :|%+ 5u|%+ 5.3u|%+ 5.1u|%+ 5.0u|%+ 5.u|\n\n", 0,0,0,0,0);
	// 	//2
	// 	printf ("printf2     :|% 5u|% 5.3u|% 5.1u|% 5.0u|% 5.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf2  :|% 5u|% 5.3u|% 5.1u|% 5.0u|% 5.u|\n\n", 0,0,0,0,0);
	// 	//3
	// 	printf ("printf3     :|%-+5u|%-+5.3u|%-+5.1u|%-+5.0u|%-+5.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf3  :|%-+5u|%-+5.3u|%-+5.1u|%-+5.0u|%-+5.u|\n\n", 0,0,0,0,0);
	// 	//4
	// 	printf ("printf4     :|%0+5u|%0+5.3u|%0+5.1u|%0+5.0u|%0+5.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf4  :|%0+5u|%0+5.3u|%0+5.1u|%0+5.0u|%0+5.u|\n\n", 0,0,0,0,0);
	// 	//5
	// 	printf ("printf5     :|%-+05u|%-+05.3u|%-+05.1u|%-+05.0u|%-+05.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf5  :|%-+05u|%-+05.3u|%-+05.1u|%-+05.0u|%-+05.u|\n\n", 0,0,0,0,0);
	// 	//6
	// 	printf ("printf6     :|% 05u|% 05.3u|% 05.1u|% 05.0u|% 05.u|\n", 0,0,0,0,0);
	// 	ft_printf ("ft_printf6  :|% 05u|% 05.3u|% 05.1u|% 05.0u|% 05.u|\n\n", 0,0,0,0,0);
	// 	//7
	// 	printf("printf7      :|% 03u|\n", 0);
	// 	ft_printf("ft_printf7   :|% 03u|\n", 0);
	return (0);
}
/*
|     +10|
|        +10|
gerer les fields negatives pour %scf
|{3, 13, 7}             0000000156|
|{3, 13, 7}          0000000156|
|{11, -2, 0}
037777777775|
|        037777777775|
*/
// {3, 10, 7}
// |          0000000156|
// |          0000000156|
// {11, 7, 0}
// |
// |       037777777775|
// |        037777777775|
