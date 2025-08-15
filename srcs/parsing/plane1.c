/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:14 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Parses plane position (x,y,z) from a comma-separated string into v[0..2].
 * Validates basic format and frees temporary buffers on failure.
 */
bool	get_position_pl(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[0] = ft_atof(values[0]);
	v[1] = ft_atof(values[1]);
	v[2] = ft_atof(values[2]);
	free_split(values);
	return (true);
}

/**
 * Parses plane normal (nx,ny,nz) from a comma-separated string into v[3..5].
 * Ensures each component is within [-1, 1]; rejects invalid input.
 */
bool	get_normal_pl(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[3] = ft_atof(values[0]);
	v[4] = ft_atof(values[1]);
	v[5] = ft_atof(values[2]);
	free_split(values);
	if (v[3] < -1.0f || v[3] > 1.0f)
		return (false);
	if (v[4] < -1.0f || v[4] > 1.0f)
		return (false);
	if (v[5] < -1.0f || v[5] > 1.0f)
		return (false);
	return (true);
}

/**
 * Parses plane color (r,g,b) from a comma-separated string into v[6..8].
 * Each channel must be in [0, 255]; rejects invalid input.
 */
bool	get_color_pl(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[6] = ft_atof(values[0]);
	v[7] = ft_atof(values[1]);
	v[8] = ft_atof(values[2]);
	free_split(values);
	if (v[6] < 0.0f || v[6] > 255.0f)
		return (false);
	if (v[7] < 0.0f || v[7] > 255.0f)
		return (false);
	if (v[8] < 0.0f || v[8] > 255.0f)
		return (false);
	return (true);
}

/**
 * Initializes a plane object's fields from parsed values,
 * normalizes its normal,
 * sets material pointers, builds its transform, and adds it to the world.
 */
void	set_plane_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 2;
	s->type = PLANE;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	s->radius = 0.0f;
	s->height = 0.0f;
	color(&s->color, v[6] / 255.0f, v[7] / 255.0f, v[8] / 255.0f);
	vector(&s->norm_v, v[3], v[4], v[5]);
	s->norm_v = normalize(&s->norm_v);
	s->ambient = &state->world.ambient;
	s->diffuse = &state->world.diffuse;
	s->specular = 0.0f;
	s->shininess = 200.0f;
	s->transform = identity();
	s->invs = identity();
	s->invs_trans = identity();
	s->next = NULL;
	creating_plane_object(s);
	add_object(state, &s);
	state->world.obj_count++;
}

/**
 * Reads plane parameters (position, normal, color) from the input line,
 * creates and populates the plane object, and registers it with the world.
 * Returns nonzero on parsing or allocation error.
 */
int	set_plane(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[9];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!get_position_pl(v, items[0]))
		return (free_split(items), 1);
	if (!get_normal_pl(v, items[1]))
		return (free_split(items), 1);
	if (!get_color_pl(v, items[2]))
		return (free_split(items), 1);
	s = init_object();
	set_plane_values(state, s, v);
	free_split(items);
	return (0);
}
