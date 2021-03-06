/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <dwisoky@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:39:31 by dwisoky           #+#    #+#             */
/*   Updated: 2019/11/02 20:17:09 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

# include "lexer.h"
# include "sh.h"

# define VAR			1
# define DIGIT			2
# define ASSIGNMENT		3
# define ADD_ASSIGNMENT	4
# define MIN_ASSIGNMENT	5
# define MUL_ASSIGNMENT	6
# define DIV_ASSIGNMENT	7
# define MOD_ASSIGNMENT	8
# define DLS_ASSIGNMENT	9
# define DGR_ASSIGNMENT	10
# define AND_ASSIGNMENT	11
# define OR_ASSIGNMENT	12
# define OR				13
# define AND			14
# define LOGICAL_OR		15
# define LOGICAL_AND	16
# define EQUAL_IF		17
# define NOT_EQUAL_IF	18
# define LESS_IF		19
# define LESS_EQ		20
# define GREAT_IF		21
# define GREAT_EQ		22
# define LEFT_SHIFT		23
# define RIGHT_SHIFT	24
# define PLUS			25
# define MINUS			26
# define MULTI			27
# define DIVISION		28
# define MODULE			29
# define SUFFIX_ADD		30
# define SUFFIX_MIN		31
# define PREFIX_ADD		32
# define PREFIX_MIN		33
# define LBRACKET_ARIF	34
# define RBRACKET_ARIF	35
# define DIVISION_NULL	36
# define EOF_AR			37
# define EXCLUSIVE_OR	38
# define LOGICAL_NOT	39
# define UNAR_PLUS		40

t_lex		*g_error_arithmetic;
t_lex		*g_lex_arif;

t_lex		*arithmetic_lexer(char *str);
char		*arithmetic_lexer_great(char *str, t_lex **lex);
char		*arithmetic_lexer_less(char *str, t_lex **lex);
char		*arithmetic_lexer_assignment(char *str, t_lex **lex);
char		*arithmetic_lexer_or(char *str, t_lex **lex);
char		*arithmetic_lexer_and(char *str, t_lex **lex);
char		*arithmetic_lexer_plus(char *str, t_lex **lex);
char		*arithmetic_lexer_minus(char *str, t_lex **lex);
char		*arithmetic_lexer_multi(char *str, t_lex **lex);
char		*arithmetic_lexer_division(char *str, t_lex **lex);
char		*arithmetic_lexer_module(char *str, t_lex **lex);
char		*arithmetic_lexer_check_token(char *str, t_lex **lex);
char		*arithmetic_lexer_var(char *str, t_lex **lex);
char		*arithmetic_lexer_digit(char *str, t_lex **lex);
char		*arithmetic_exp(char *str);
char		*arithmetic_print_lex_error(char *str);
void		*arithmetic_error(char *str, t_lex *begin);
long		expr(void);
long		expr_or(void);
long		expr_and(void);
long		expr_logic_or(void);
long		expr_exclusive_or(void);
long		expr_logic_and(void);
long		expr_equal(void);
long		expr_relat_op(void);
long		expr_shift(void);
long		expr_additive(void);
long		expr_multiplicativ(void);
long		expr_prefix(void);
long		expr_suffix(void);
long		expr_unar(void);
long		expr_get_var_value(void);
long		expr_return_value(void);
long		expr_digit(void);
long		expr_bracket(void);
long		expr_atoll(char *str, int base);
int			arithmetic_lexer_is_token(char str);

#endif
