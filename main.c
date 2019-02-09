/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/09 02:40:57 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
	// char *string = "|%-20d|%-20x|%-20X|%-20u|%-20o|%-20p|%-#2P|\n";
	// int n =  110;
	// int n_ = -3;
	// ft_printf(string,n, n, n, n, n, n, n);
	// printf(string,n, n, n, n, n, n, n);
	// ft_printf(string,n_, n_,n_, n_, n_, n_, n_);
	// printf(string, n_, n_,n_,n_, n_, n_, n_);
	// char *string = "|%020p|\n";
   // int n =  110;
   // int n_ = -3;
   // ft_printf(string,  n);
   // printf(string, n);
   // ft_printf(string,  n_);
   // printf(string,  n_);
	// ft_printf("|%20p|\n", "xd");
	// printf("|%20p|\n", "xd");
	// // printf(string, -5);
	// ft_printf(string, 5);
	int a = ft_printf(" %10.6d%s %10c\n", 1000,"xddddd", 50);
	int b = printf("\n %10.6d%s %10c", 1000, "xddddd", 50);
	printf("\na: %d|b: %d\n", a, b);
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
