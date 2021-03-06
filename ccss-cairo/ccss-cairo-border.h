/* vim: set ts=8 sw=8 noexpandtab: */

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

#ifndef CCSS_CAIRO_BORDER_H
#define CCSS_CAIRO_BORDER_H

#ifndef CCSS_CAIRO_H
  #ifndef CCSS_CAIRO_BUILD
    #error "Only <ccss-cairo/ccss-cairo.h> can be included directly."
  #endif
#endif

#include <stdint.h>
#include <cairo.h>
#include <ccss/ccss.h>

CCSS_BEGIN_DECLS

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
	ccss_color_t const *		color;
	ccss_border_style_t const *	style;
	ccss_border_width_t const *	width;
} ccss_border_stroke_t;

void
ccss_cairo_border_clamp_radii (double     x,
			       double     y, 
			       double     width, 
			       double     height,
			       double    *left_top, 
			       double    *top_right,
			       double    *right_bottom, 
			       double    *bottom_left);

void
ccss_cairo_border_path (ccss_border_stroke_t const      *left, 
			ccss_border_join_t const	*left_top,
			ccss_border_stroke_t const      *top, 
			ccss_border_join_t const	*top_right,
			ccss_border_stroke_t const      *right,
			ccss_border_join_t const	*right_bottom,
			ccss_border_stroke_t const      *bottom, 
			ccss_border_join_t const	*bottom_left,
			cairo_t				*cr, 
			double				 x, 
			double				 y, 
			double				 width,
			double				 height);

void
ccss_cairo_border_draw (ccss_border_stroke_t const      *left, 
			ccss_border_join_t const	*left_top,
			ccss_border_stroke_t const      *top, 
			ccss_border_join_t const	*top_right,
			ccss_border_stroke_t const      *right,
			ccss_border_join_t const	*right_bottom,
			ccss_border_stroke_t const      *bottom, 
			ccss_border_join_t const	*bottom_left,
			uint32_t			 visibility_flags, 
			cairo_t				*cr, 
			double				 x,
			double				 y, 
			double				 width, 
			double				 height);

CCSS_END_DECLS

#endif /* CCSS_CAIRO_BORDER_H */

