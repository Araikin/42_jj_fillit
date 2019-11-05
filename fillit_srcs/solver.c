/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:29:54 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/01 16:31:45 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			if_next_line(int pos, int i, int s, int m)
{
	float resulta;
	float a;

	resulta = (pos + i) / s;
	a = (pos + (s * (m - 1))) / s;
	if (resulta == a)
		return (1);
	else
		return (0);
}

static int	put_piece(char *piece, t_board **board, int pos, int index)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (piece[n])
	{
		if (piece[n] == '\n')
		{
			pos += (*board)->size;
			i = 0;
		}
		else if (piece[n] == '#')
		{
			(*board)->value[pos + i] = 'A' + index;
			i++;
		}
		else if (piece[n] == '.')
			i++;
		n++;
	}
	return (TRUE);
}

static int	findspot(char *p, char *board, int *po, int s)
{
	int i;
	int n;
	int m;

	while (board[*po] && !(i = 0))
	{
		n = 0;
		m = 1;
		while (p[n] && (*po + i) < (s * s))
		{
			if (p[n] != '\n' && !if_next_line(*po, i, s, m))
				break ;
			if (p[n] == '#' && (++i))
				if (board[*po + i - 1] >= 'A' && board[*po + i - 1] <= 'Z')
					break ;
			if (p[n] == '\n')
				i = s * m++;
			(p[n] == '.') ? i++ : (i += 0);
			n++;
			if (n == (int)ft_strlen(p))
				return (TRUE);
		}
		*po += 1;
	}
	return (FALSE);
}

int			solver(int (*p_a)[], t_board *board, char *mp[], int i)
{
	int pos;

	pos = 0;
	if (!(findspot(mp[(*p_a)[i]], board->value, &pos, board->size)))
		return (FALSE);
	else
	{
		put_piece(mp[(*p_a)[i]], &board, pos, i);
		if (i == 25 || (*p_a)[i + 1] == -1)
			return (TRUE);
		else
		{
			while (!(solver(p_a, board, mp, i + 1)))
			{
				clear_board(&board);
				pos++;
				if (!(findspot(mp[(*p_a)[i]], board->value, &pos, board->size)))
					return (FALSE);
				else if (put_piece(mp[(*p_a)[i]], &board, pos, i))
					if (i == 25 || (*p_a)[i + 1] == -1)
						return (TRUE);
			}
		}
	}
	return (TRUE);
}
