# include "include/miniRt.h"

# define WIDTH  1600
# define HEIGHT 1200

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

uint32_t tuple_to_color(t_tuple *tp)
{
	uint8_t red   = (uint8_t)(tp->t[0] * 255.0f);
	uint8_t green = (uint8_t)(tp->t[1] * 255.0f);
	uint8_t blue  = (uint8_t)(tp->t[2] * 255.0f);
	uint8_t alpha = (uint8_t)(tp->t[3] * 255.0f);

	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
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

	float light_x = 0, light_y = 0, light_z = -5;
	float wall_x, wall_y, wall_z = 10.0;
	float wall_size = 10.0;
	int width = 300, height = 300;
	float pixel_size = wall_size / width;

	t_material mat;
	mat.ambient = 0.1;
	mat.diffiuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200.0;
	color(&mat.color, 1.0, 1.0, 1.0);

	//seting up the sphere
	t_object s;
	s.id = 1;
	s.material = &mat;
	s.radius = 1.0;
	s.type = 1;
	s.x = 0.0;
	s.y = 0.0;
	s.z = 0.0;
	indentity(&s.transform);
	matrix_inverse(&s.invs, &s.transform);

	//setting up the ray
	t_ray r;
	point(&r.origin, light_x, light_y, light_z);

	t_light light;
	color(&light.color, 1.0, 1.0, 1.0);
	point(&light.position, -10, 10, -10);


	t_tuple p, temp, colour, p1, normal, eye;
	t_intersect xs[2];

	for(int y = 0; y < (height -1); y++)
	{
		wall_y = (wall_size / 2) - (pixel_size * y);
		for(int x = 0; x <(width - 1); x++)
		{
			wall_x = (pixel_size * x) - (wall_size / 2);
			point(&p, wall_x, wall_y, wall_z);
			tuple_subtract(&temp, &p, &r.origin);
			normalize(&r.direction, &temp);
			if(cal_intersects(&s, &r, xs) && (xs[0].value >= 0 || xs[1].value >= 0))
			{
				position(&p1, &r, get_value(xs));
				normal_at(&normal, &s, &p1);
				tuple_negate(&eye, &r.direction);
				lighting(&colour, s.material, &light, &p1, &eye, &normal);
				mlx_put_pixel(img, x, y, tuple_to_color(&colour));
			}
		}
	}
	// Keep window open
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
