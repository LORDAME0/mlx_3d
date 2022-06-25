#include "main.h"

t_sphere	make_sphere(t_point origin, double radius)
{
	static int	id;

	return ((t_sphere){
		.type = Sphere,
		.id = ++id,
		.center = origin,
		.radius = radius,
		.t = identity(),
		.material = material(),
	});
}

t_sphere	sphere(void)
{
	return (make_sphere(point(0, 0, 0), 1));
}

t_hit	sphere_roots(double a, double b, double discriminant, t_sphere sp)
{
	const double			sqrt_dis = sqrt(discriminant);
	const double			root1 = ((-1 * b) - sqrt_dis) / (2 * a);
	const double			root2 = ((-1 * b) + sqrt_dis) / (2 * a);
	const t_intersection	is[2] = {
		intersection(root1, (t_shape)sp),
		intersection(root2, (t_shape)sp),
	};

	return ((t_hit){{is[0], is[1]}, 2});
}

t_hit	intersect_sphere(const t_sphere sp, const t_ray r)
{
	const t_vec		e_c = sub(r.origin, sp.center);
	const double	a = dot(r.direction, r.direction);
	const double	b = 2.0 * dot(e_c, r.direction);
	const double	c = dot(e_c, e_c) - sp.radius * sp.radius;
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (no_intersection());
	return (sphere_roots(a, b, discriminant, sp));
}

t_vec	normal_at_sphere(t_sphere s, t_point local_point)
{
	return (sub(local_point, s.center));
}