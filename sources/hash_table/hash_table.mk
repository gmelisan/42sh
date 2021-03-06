# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hash_table.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtalea <wtalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/05 16:41:59 by ggwin-go          #+#    #+#              #
#    Updated: 2019/10/14 01:55:03 by wtalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HASH_HASH_DIR=hash
HASH_FLAGS_ARGS_DIR=flags_args

SRCS_HASH_HASH=\
	../ft_itoa_nm.c\
	../ft_intlen.c\
	create_bin.c\
	create_hash.c\
	del_hash.c\
	get_bin.c\
	null_hash.c\
	paste_path.c\
	add_force.c\
	count_hash_on.c\
	hash_print.c\
	hash_print_use.c\
	print_lib.c\
	print_usage.c\
	start_built_hash.c\
	find_and_del.c\
	hash_flag_r.c\

SRCS_FLAGS_ARGS_HASH=\
	find_and_add_flags.c\
	get_command_options.c

HASH_SUBDIRS=\
	$(HASH_HASH_DIR)\
	$(HASH_FLAGS_ARGS_DIR)

SRCS_HASH=\
	$(addprefix $(HASH_HASH_DIR)/, $(SRCS_HASH_HASH))\
	$(addprefix $(HASH_FLAGS_ARGS_DIR)/, $(SRCS_FLAGS_ARGS_HASH))
