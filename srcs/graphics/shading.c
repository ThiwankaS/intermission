#include "../../include/miniRt.h"

t_tuple *normal_at(t_object *s, t_tuple *world_point)
{
	t_matrix *inverse = matrix_inverse(s->transform);
	t_tuple *abs_point = point(0,0,0);
	t_tuple *object_point = matrix_multiply_by_tuple(inverse, world_point);
	t_tuple *object_normal = substrctTuples(object_point, abs_point);
	t_matrix *trans = matrix_transpose(inverse);
	t_tuple *world_normal = matrix_multiply_by_tuple(trans, object_normal);
	free(abs_point);
	free(object_point);
	free(object_normal);
	matrix_free(inverse);
	matrix_free(trans);
	world_normal->components[3] = 0.0;
	t_tuple *normal = normalize(world_normal);
	free(world_normal);
	return normal;
}

t_tuple *reflect(t_tuple *in, t_tuple *normal)
{
	double product = dot(in, normal) * 2;
	t_tuple *t1 = scalerMultiplication(normal, product);
	t_tuple *t2 = substrctTuples(in, t1);
	free(t1);
	return t2;
}

t_light *point_light(t_tuple *position, t_tuple *intensity)
{
	t_light *light = calloc(1, sizeof(t_light));
	if(!light)
		return NULL;
	light->color = intensity;
	light->position = position;
	return light;
}

t_tuple *lighting(t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal)
{
	t_tuple *ambient, *diffiuse, *specular, *temp, *result;

	//combine the surface color with the light's color/intensity
	t_tuple *effective_color = hadamard_product(m->color, light->color);

	//find the direction to the light source
	temp = substrctTuples(light->position, position);
	t_tuple *lightv = normalize(temp);
	free(temp);

	//compute the ambient contribution
	ambient = scalerMultiplication(effective_color, m->ambient);

	/**
	 * light_dot_normal represents the cosine of the angle between the light vector
	 * and the normal vector. A negative number means the light is on the other
	 * side of the surface.
	 */
	double light_dot_normal = dot(lightv, normal);

	if(light_dot_normal < 0)
	{
		diffiuse = point(0,0,0);
		specular = point(0,0,0);
	}
	else
	{
		diffiuse = scalerMultiplication(effective_color, (m->diffiuse * light_dot_normal));
		/**
		 * reflect_dot_eye represents the cosine of the angle between the reflection vector
		 * and the eye vector. A negative number means the light reflects away from the eye.
		 */
		t_tuple *neg_lightv = negatingTuples(lightv);
		t_tuple *reflectv = reflect(neg_lightv, normal);
		double reflect_dot_eye = dot(reflectv, eye);
		if(reflect_dot_eye <= 0)
		{
			specular = point(0,0,0);
		}
		else
		{
			double factor = pow(reflect_dot_eye, m->shininess);
			specular = scalerMultiplication(light->color, (m->specular * factor));
		}
		free(neg_lightv);
		free(reflectv);
	}
	temp = addTuples(ambient, diffiuse);
	result = addTuples(temp, specular);
	result->components[3] = 1.0;
	free(temp);
	free(effective_color);
	free(lightv);
	free(ambient);
	free(diffiuse);
	free(specular);
	return result;
}
