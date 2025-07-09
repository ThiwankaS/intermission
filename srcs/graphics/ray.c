/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/10 02:50:42 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	position(t_tuple *pp, t_ray *r, float t)
{
	t_tuple	temp;

	tuple_multiply_scalor(&temp, &r->direction, t);
	tuple_add(pp, &r->origin, &temp);
}

t_intersect	*intersection(double t, t_object *object)
{
	t_intersect	*i;

	i = ft_calloc(1, sizeof(t_intersect));
	if (!i)
		return (NULL);
	i->value = t;
	i->object = object;
	return (i);
}

t_intersect	*cal_intersects(t_object *object, t_ray *rp, t_intersect out[2])
{
	t_tuple	abs;
	t_tuple	sphere_to_ray;
	t_ray	r;
	float	values[4];
	float	discriminent;

	point(&abs, 0, 0, 0);
	transform(&r, rp, &object->invs);
	tuple_subtract(&sphere_to_ray, &r.origin, &abs);
	values[0] = dot(&r.direction, &r.direction);
	values[1] = 2 * dot(&r.direction, &sphere_to_ray);
	values[2] = dot(&sphere_to_ray, &sphere_to_ray) - 1;
	discriminent = (values[1] * values[1]) - (4 * values[0] * values[2]);
	if (discriminent < 0)
		return (NULL);
	values[3] = sqrt(discriminent);
	out[0].value = (-values[1] - values[3]) / (2 * values[0]);
	out[0].object = object;
	out[1].value = (-values[1] + values[3]) / (2 * values[0]);
	out[1].object = object;
	return (out);
}

t_intersections	*intersections(t_intersections *xs, t_intersect *intersect)
{
	t_intersections	*current;
	t_intersections	*previous;
	t_intersections	*new;

	if (!xs)
	{
		xs = ft_calloc(1, sizeof(t_intersections));
		if (!xs)
			return (NULL);
		xs->intersect = intersect;
		xs->next = NULL;
		xs->count = 1;
		return (xs);
	}
	current = xs;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	new = ft_calloc(1, sizeof(t_intersections));
	if (!new)
		return (xs);
	new->intersect = intersect;
	new->next = NULL;
	previous->next = new;
	xs->count++;
	return (xs);
}

t_intersect	*hit(t_intersections *xs)
{
	t_intersect		*i;
	t_intersections	*current;
	t_intersections	*previous;

	current = xs;
	i = NULL;
	while (current)
	{
		previous = current;
		if (previous->intersect->value > 0.0)
		{
			if (!i || previous->intersect->value < i->value)
				i = previous->intersect;
		}
		current = current->next;
	}
	return (i);
}
