# include "include/miniRt.h"

# define WIDTH  500
# define HEIGHT  300

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
	t_object *s1, *s2, *s3;
	s1 = ft_calloc(1, sizeof(t_object));
	s2 = ft_calloc(1, sizeof(t_object));
	s3 = ft_calloc(1, sizeof(t_object));

	t_material mat1;
	mat1.ambient = 0.1f;
	mat1.diffuse = 0.7f;
	mat1.specular = 0.0f;
	mat1.shininess = 200.0f;
	color(&mat1.color, 1.0f, 0.0f, 0.0f);

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

	t_material mat2;
	mat2.ambient = 0.1f;
	mat2.diffuse = 0.7f;
	mat2.specular = 0.0f;
	mat2.shininess = 200.0f;
	color(&mat2.color, 0.0f, 1.0f, 0.0f);

	t_mat m2, m3, m4, m5, m6, m7, m8;
	scaling(&m2, 10.0f, 0.01f, 10.0f);
	rotate_x(&m3, M_PI/2);
	rotate_y(&m4, -(M_PI/4));
	translation(&m5, 0.0f, 0.0f, 5.0f);
	matrix_multiply(&m6, &m3, &m2);
	matrix_multiply(&m7, &m4, &m6);
	matrix_multiply(&m8, &m5, &m7);
	s2->id = 2;
	s2->type = 1;
	s2->x = 0.0f;
	s2->y = 0.0f;
	s2->z = 0.0f;
	s2->radius = 1.0f;
	s2->material = &mat2;
	set_transform(&s2->transform, &m8);
	matrix_inverse(&s2->invs, &s2->transform);
	s2->next = s3;

	t_material mat3;
	mat3.ambient = 0.1f;
	mat3.diffuse = 0.7f;
	mat3.specular = 0.0f;
	mat3.shininess = 200.0f;
	color(&mat3.color, 0.0f, 0.0f, 1.0f);

	t_mat m9, m10, m11, m12, m13, m14, m15;
	scaling(&m9, 10.0f, 0.01f, 10.0f);
	rotate_x(&m10, M_PI/2);
	rotate_y(&m11, M_PI/4);
	translation(&m12, 0.0f, 0.0f, 5.0f);
	matrix_multiply(&m13, &m10, &m9);
	matrix_multiply(&m14, &m11, &m13);
	matrix_multiply(&m15, &m12, &m14);
	s3->id = 3;
	s3->type = 1;
	s3->x = 0.0f;
	s3->y = 0.0f;
	s3->z = 0.0f;
	s3->radius = 1.0f;
	s3->material = &mat3;
	set_transform(&s3->transform, &m15);
	matrix_inverse(&s3->invs, &s3->transform);
	s3->next = NULL;

	point(&world.light.position, -10.0f, 10.0f, -10.0f);
	color(&world.light.color, 1.0f, 1.0f, 1.0f);
	world.components = s1;

	t_camera *camera = camera_init(WIDTH, HEIGHT, M_PI / 3);
	t_tuple from, to, up;
	point(&from, 0.0f, 1.5f, -0.5f);
	point(&to, 0.0f, 1.0f, 0.0f);
	vector(&up, 0.0f, 1.0f, 0.0f);
	view_transformation(&camera->transform, &from, &to, &up);

	render(img, camera, &world);

	free(camera);
	free(s1);
	free(s2);
	free(s3);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
