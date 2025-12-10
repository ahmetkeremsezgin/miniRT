/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:47:33 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:47:33 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../mini_rt.h"

static void print_ambient(const t_ambient *a)
{
	if (!a) { printf("Ambient: (yok)\n"); return; }
	printf("Ambient:\n");
	printf("  ratio: %.2f\n", a->ratio);
	printf("  color: R=%d G=%d B=%d\n", a->red, a->green, a->blue);
}

static void print_camera(const t_camera *c)
{
	if (!c) { printf("Camera: (yok)\n"); return; }
	printf("Camera:\n");
	printf("  origin: (%.2f, %.2f, %.2f)\n", c->origin.x, c->origin.y, c->origin.z);
	printf("  direction: (%.2f, %.2f, %.2f)\n", c->dir.x, c->dir.y, c->dir.z);
	printf("  fov: %d\n", c->fov);
}

static void print_light(const t_light *l)
{
	if (!l) { printf("Light: (yok)\n"); return; }
	printf("Light:\n");
	printf("  coord     : (%.2f, %.2f, %.2f)\n", l->center.x, l->center.y, l->center.z);
	printf("  brightness: %.2f\n", l->brightness);
	printf("  color     : 0x%06X\n", l->color);
}

static void print_spheres(const t_sphere *s)
{
	if (!s) { printf("Spheres: (yok)\n"); return; }
	int i = 0;
	printf("Spheres:\n");
	while (s)
	{
		printf("  [%d]\n", i++);
		printf("    center: (%.2f, %.2f, %.2f)\n", s->center.x, s->center.y, s->center.z);
		printf("    radius: %.2f\n", s->radius);
		printf("    color : 0x%06X\n", s->color);
		s = s->next;
	}
}

static void print_planes(const t_plane *p)
{
	if (!p) { printf("Planes: (yok)\n"); return; }
	int i = 0;
	printf("Planes:\n");
	while (p != NULL)
	{
		printf("  [%d]\n", i++);
		printf("    point : (%.2f, %.2f, %.2f)\n", p->point.x, p->point.y, p->point.z);
		printf("    normal: (%.2f, %.2f, %.2f)\n", p->normal.x, p->normal.y, p->normal.z);
		printf("    color : 0x%06X\n", p->color);
		p = p->next;
	}
}

static void print_cylinders(const t_cylinder *cyl)
{
	if (!cyl) { printf("Cylinders: (yok)\n"); return; }
	int i = 0;
	printf("Cylinders:\n");
	while (cyl)
	{
		printf("  [%d]\n", i++);
		printf("    center: (%.2f, %.2f, %.2f)\n", cyl->center.x, cyl->center.y, cyl->center.z);
		printf("    axis  : (%.2f, %.2f, %.2f)\n", cyl->axis.x, cyl->axis.y, cyl->axis.z);
		printf("    diam  : %.2f\n", cyl->diam);
		printf("    height: %.2f\n", cyl->height);
		printf("    color : 0x%06X\n", cyl->color);
		cyl = cyl->next;
	}
}

void print_all(t_all *all)
{
	if (!all) { printf("(all yok)\n"); return; }

	printf("======== SCENE DUMP ========\n");
	print_ambient(all->ambient);
	print_camera(all->camera);
	print_light(all->light);
	print_spheres(all->sphere);
	print_planes(all->plane);
	print_cylinders(all->cylinder);
	printf("========  END DUMP  ========\n");
}
