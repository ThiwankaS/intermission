/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:39:14 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/20 04:39:54 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Returns true if the character is ASCII whitespace (space or 9–13),
 * false otherwise.
 * Used by the float parser to skip leading whitespace safely.
 */
bool	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/**
 * Parses the integer part of a decimal number from a C string pointer.
 * Advances the input pointer past consecutive digits
 * and returns the accumulated value.
 */
float	get_interger_part(const char **str)
{
	float	result;

	result = 0.0;
	while (str && *str && **str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

/**
 * Parses the fractional part after the decimal point from a C string pointer.
 * Accumulates digits with decreasing powers of ten,
 * advancing the pointer as it reads.
 */
float	get_fractional_part(const char **str)
{
	float	fraction;
	float	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (str && *str && **str >= '0' && **str <= '9')
	{
		fraction += (**str - '0') / divisor;
		divisor *= 10.0;
		(*str)++;
	}
	return (fraction);
}

/**
 * Converts a decimal string to a float with optional leading whitespace
 * and sign.
 * Supports only integral and fractional parts (no exponent);
 * stops at the first non-digit.
 */
float	ft_atof(const char *str)
{
	float	result;
	float	fraction;
	bool	is_negative;

	result = 0.0;
	fraction = 0.0;
	is_negative = false;
	while (str && *str && ft_isspace(*str))
		str++;
	if (str && *str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			is_negative = true;
		str++;
	}
	result = get_interger_part(&str);
	if (str && *str && *str == '.')
	{
		str++;
		fraction = get_fractional_part(&str);
	}
	result += fraction;
	if (is_negative)
		result = -result;
	return (result);
}
