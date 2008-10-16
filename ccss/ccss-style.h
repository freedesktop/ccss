/* The Cairo CSS Drawing Library.
 * Copyright (C) 2008 Robert Staudinger
 *
 * This  library is free  software; you can  redistribute it and/or
 * modify it  under  the terms  of the  GNU Lesser  General  Public
 * License  as published  by the Free  Software  Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed  in the hope that it will be useful,
 * but  WITHOUT ANY WARRANTY; without even  the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License  along  with  this library;  if not,  write to  the Free
 * Software Foundation, Inc., 51  Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef CCSS_STYLE_H
#define CCSS_STYLE_H

#include <stdint.h>
#include <glib.h>
#include <cairo.h>
#include <ccss/ccss-features.h>

G_BEGIN_DECLS

/**
 * ccss_style_t:
 *
 * Representation of a block of CSS statements.
 *
 * <emphasis>Memory management:</emphasis> Style objects are owned by the 
 * stylesheet, and therefore not created or modified by the CCSS consumer.
 **/
typedef struct {
	/*< private >*/
	GHashTable	*properties;

	int32_t		 viewport_x;
	int32_t		 viewport_y;
	int32_t		 viewport_width;
	int32_t		 viewport_height;
} ccss_style_t;

ccss_style_t *	ccss_style_new	(void);
void		ccss_style_free (ccss_style_t *self);

void ccss_style_draw_line (ccss_style_t const *self, cairo_t *cr, 
			  int32_t x1, int32_t x2, int32_t y1, int32_t y2);

void ccss_style_draw_outline (ccss_style_t const *self, cairo_t *cr, 
			     int32_t x, int32_t y, int32_t width, int32_t height);

void ccss_style_draw_rectangle (ccss_style_t const *self, cairo_t *cr, 
			       int32_t x, int32_t y, int32_t width, int32_t height);

bool ccss_style_get_double (ccss_style_t const *self, char const *property_name,
			    double *value);

bool ccss_style_get_string (ccss_style_t const *self, char const *property_name,
			    char **value);

/* Somewhat obscure, undocumented API, primarily for the css engine.
 * Maybe we should return a cairo pattern instead? */

bool ccss_style_get_color (ccss_style_t const *self,
			  double *red, double *green, double *blue);

bool ccss_style_get_background_color (ccss_style_t const *self,
				     double *red, double *green, double *blue);

bool ccss_style_get_border_color (ccss_style_t const *self,
				 double *red, double *green, double *blue);

void ccss_style_set_viewport (ccss_style_t *self, int32_t x, int32_t y,
			      int32_t width, int32_t height);

#ifdef CCSS_DEBUG
void ccss_style_dump (ccss_style_t const *self);
#endif

G_END_DECLS

#endif /* CCSS_STYLE_H */

