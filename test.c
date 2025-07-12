# include "include/miniRt.h"

# define WIDTH  1000
# define HEIGHT  800

float get_value(t_intersect *xs)
{
	float value = 0.0;
	if(xs)
	{
		if(xs[0].value > 0)
			value = xs[0].value;
		if(xs[1].value > 0)
		{
			if(xs[0].value > xs[1].value)
				value = xs[1].value;
		}
	}
	return value;
}

int main(void)
{
		// Create window and image
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "My Window", true);
	if (!mlx)
		return 1;

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return 1;

	// SHOW THE IMAGE FIRST!
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return 1;

	t_world world;

	t_object *s1, *s2, *s3, *s4, *s5, *s6;

	s1 = ft_calloc(1, sizeof(t_object));
	s2 = ft_calloc(1, sizeof(t_object));
	s3 = ft_calloc(1, sizeof(t_object));
	s4 = ft_calloc(1, sizeof(t_object));
	s5 = ft_calloc(1, sizeof(t_object));
	s6 = ft_calloc(1, sizeof(t_object));

	t_material mat1, mat2, mat3, mat4, mat5, mat6;

	mat1.ambient = 0.1f;
	mat1.diffuse = 0.7f;
	mat1.specular = 0.0f;
	mat1.shininess = 200.0f;
	color(&mat1.color, 1.0f, 0.9f, 0.9f);

	mat2.ambient = 0.1f;
	mat2.diffuse = 0.7f;
	mat2.specular = 0.0f;
	mat2.shininess = 200.0f;
	color(&mat2.color, 1.0f, 0.9f, 0.9f);

	mat3.ambient = 0.1f;
	mat3.diffuse = 0.7f;
	mat3.specular = 0.0f;
	mat3.shininess = 200.0f;
	color(&mat3.color, 1.0f, 0.9f, 0.9f);

	mat4.ambient = 0.1f;
	mat4.diffuse = 0.7f;
	mat4.specular = 0.3f;
	mat4.shininess = 200.0f;
	color(&mat4.color, 0.1f, 1.0f, 0.5f);

	mat5.ambient = 0.1f;
	mat5.diffuse = 0.7f;
	mat5.specular = 0.3f;
	mat5.shininess = 200.0f;
	color(&mat5.color, 0.5f, 1.0f, 0.1f);

	mat6.ambient = 0.1f;
	mat6.diffuse = 0.7f;
	mat6.specular = 0.3f;
	mat6.shininess = 200.0f;
	color(&mat6.color, 1.0f, 0.8f, 0.1f);

	t_mat m1;
	scaling(&m1, 10.0f, 0.01f, 10.0f);
	s1->id = 1;
	s1->type = 1;
	s1->x = 0.0f;
	s1->y = 0.0f;
	s1->z = 0.0f;
	s1->radius = 1.0f;
	s1->material = &mat1;
	set_transform(&s1->transform, &m1);
	matrix_inverse(&s1->invs, &s1->transform);
	s1->next = s2;

	t_mat m2, m3, m4, m5, m6;
	rotate_x(&m2, M_PI/2);
	rotate_y(&m3, - M_PI/4);
	translation(&m4, 0.0f, 0.0f, 5.0f);
	matrix_multiply(&m5, &m2, &m1);
	matrix_multiply(&m6, &m3, &m5);
	matrix_multiply(&m5, &m4, &m6);
	s2->id = 2;
	s2->type = 1;
	s2->x = 0.0f;
	s2->y = 0.0f;
	s2->z = 0.0f;
	s2->radius = 1.0f;
	s2->material = &mat2;
	set_transform(&s2->transform, &m5);
	matrix_inverse(&s2->invs, &s2->transform);
	s2->next = s3;

	t_mat m7, m8, m9;
	rotate_y(&m7, M_PI/4);
	matrix_multiply(&m8, &m2, &m1);
	matrix_multiply(&m9, &m7, &m8);
	matrix_multiply(&m8, &m1, &m9);
	s3->id = 3;
	s3->type = 1;
	s3->x = 0.0f;
	s3->y = 0.0f;
	s3->z = 0.0f;
	s3->radius = 1.0f;
	s3->material = &mat3;
	set_transform(&s3->transform, &m8);
	matrix_inverse(&s3->invs, &s3->transform);
	s3->next = s4;

	t_mat m0;
	translation(&m0, -0.05f, 1.0f, 0.5f);
	s4->id = 4;
	s4->type = 1;
	s4->x = 0.0f;
	s4->y = 0.0f;
	s4->z = 0.0f;
	s4->radius = 1.0f;
	s4->material = &mat4;
	set_transform(&s4->transform, &m0);
	matrix_inverse(&s4->invs, &s4->transform);
	s4->next = s5;

	t_mat m10, m11, m12;
	translation(&m10, 1.5f, 0.5f, -0.5f);
	scaling(&m11, 0.5f, 0.5f, 0.5f);
	matrix_multiply(&m12, &m10, &m11);
	s5->id = 5;
	s5->type = 1;
	s5->x = 0.0f;
	s5->y = 0.0f;
	s5->z = 0.0f;
	s5->radius = 1.0f;
	s5->material = &mat5;
	set_transform(&s5->transform, &m12);
	matrix_inverse(&s5->invs, &s5->transform);
	s5->next = s6;

	t_mat m13, m14, m15;
	translation(&m13, -1.5f, 0.33f, -0.75f);
	scaling(&m14, 0.33f, 0.33f, 0.33f);
	matrix_multiply(&m15, &m13, &m14);
	s6->id = 6;
	s6->type = 1;
	s6->x = 0.0f;
	s6->y = 0.0f;
	s6->z = 0.0f;
	s6->radius = 1.0f;
	s6->material = &mat6;
	set_transform(&s6->transform, &m15);
	matrix_inverse(&s6->invs, &s6->transform);
	s6->next = NULL;

	point(&world.light.position, -10.0f, 10.0f, -10.0f);
	color(&world.light.color, 1.0f, 1.0f, 1.0f);
	world.components = s1;

	t_camera *camera = camera_init(100, 50, M_PI / 3);
	t_tuple from, to, up;
	point(&from, 0.0f, 1.5f, -0.5f);
	point(&to, 0.0f, 1.0f, 0.0f);
	vector(&up, 0.0f, 1.0f, 0.0f);
	camera->transform = view_transformation(&from, &to, &up);

	render(img, camera, &world);

	free(camera->transform);
	free(camera);
	free(s1);
	free(s2);
	free(s3);
	free(s4);
	free(s5);
	free(s6);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
