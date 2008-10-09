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

#ifndef CCSS_BORDER_H
#define CCSS_BORDER_H

#include <stdbool.h>
#include <stdint.h>
#include <cairo.h>
#include <glib.h>
#include <ccss/ccss-features.h>
#include <ccss/ccss-color.h>
#include <ccss/ccss-property.h>

G_BEGIN_DECLS

typedef enum {
	CCSS_BORDER_STYLE_HIDDEN,
	CCSS_BORDER_STYLE_DOTTED,
	CCSS_BORDER_STYLE_DASHED,
	CCSS_BORDER_STYLE_SOLID,
	CCSS_BORDER_STYLE_DOUBLE,
	CCSS_BORDER_STYLE_GROOVE,
	CCSS_BORDER_STYLE_RIDGE,
	CCSS_BORDER_STYLE_INSET,
	CCSS_BORDER_STYLE_OUTSET
} ccss_border_style_type_t;

typedef enum {
	CCSS_BORDER_VISIBILITY_SHOW_ALL			= 0,
	CCSS_BORDER_VISIBILITY_HIDE_LEFT		= 1 << 0,
	CCSS_BORDER_VISIBILITY_HIDE_LEFT_TOP		= 1 << 1,
	CCSS_BORDER_VISIBILITY_HIDE_TOP			= 1 << 2,
	CCSS_BORDER_VISIBILITY_HIDE_TOP_RIGHT		= 1 << 3,
	CCSS_BORDER_VISIBILITY_HIDE_RIGHT		= 1 << 4,
	CCSS_BORDER_VISIBILITY_HIDE_RIGHT_BOTTOM	= 1 << 5,
	CCSS_BORDER_VISIBILITY_HIDE_BOTTOM		= 1 << 6,
	CCSS_BORDER_VISIBILITY_HIDE_BOTTOM_LEFT		= 1 << 7,

	CCSS_BORDER_ROUNDING_UNRESTRICTED		= 1 << 8
} ccss_border_drawing_flags_t;

typedef struct {
	ccss_property_spec_t		spec;
	ccss_border_style_type_t	style;
} ccss_border_style_t;

typedef struct {
	ccss_property_spec_t		spec;
	double				width;
} ccss_border_width_t;

typedef struct {
	ccss_color_t const *		color;
	ccss_border_style_t const *	style;
	ccss_border_width_t const *	width;
} ccss_border_stroke_t; 

typedef struct {
	ccss_property_spec_t	spec;	
	double			radius;
	unsigned int		flags;
} ccss_border_join_t;

typedef struct {
	ccss_border_stroke_t	left;
	ccss_border_join_t	left_top;
	ccss_border_stroke_t	top;
	ccss_border_join_t	top_right;
	ccss_border_stroke_t	right;
	ccss_border_join_t	right_bottom;
	ccss_border_stroke_t	bottom;
	ccss_border_join_t	bottom_left;
} ccss_border_t;

void ccss_border_clamp_radii (double x, double y, double width, double height,
			     double *left_top, double *top_right,
			     double *right_bottom, double *bottom_left);

void ccss_border_path (ccss_border_stroke_t const *left, 
		      ccss_border_join_t const *left_top,
		      ccss_border_stroke_t const *top, 
		      ccss_border_join_t const *top_right,
		      ccss_border_stroke_t const *right,
		      ccss_border_join_t const *right_bottom,
		      ccss_border_stroke_t const *bottom, 
		      ccss_border_join_t const *bottom_left,
		      cairo_t *cr, 
		      double x, double y, double width, double height);

void ccss_border_draw (ccss_border_stroke_t const *left, 
		      ccss_border_join_t const *left_top,
		      ccss_border_stroke_t const *top, 
		      ccss_border_join_t const *top_right,
		      ccss_border_stroke_t const *right,
		      ccss_border_join_t const *right_bottom,
		      ccss_border_stroke_t const *bottom, 
		      ccss_border_join_t const *bottom_left,
		      uint32_t visibility_flags, cairo_t *cr, 
		      double x, double y, double width, double height);

#ifdef CCSS_DEBUG
void ccss_border_dump		(ccss_border_t const *self);
void ccss_border_join_dump	(ccss_border_join_t const *self);
void ccss_border_stroke_dump	(ccss_border_stroke_t const *self);
#endif

G_END_DECLS

#endif /* CCSS_BORDER_H */

