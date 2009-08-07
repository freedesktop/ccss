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

#ifndef CCSS_CAIRO_BACKGROUND_H
#define CCSS_CAIRO_BACKGROUND_H

#ifndef CCSS_CAIRO_H
  #ifndef CCSS_CAIRO_BUILD
    #error "Only <ccss-cairo/ccss-cairo.h> can be included directly."
  #endif
#endif

#include <stdint.h>
#include <cairo.h>
#include <libcroco/libcroco.h>
#include <ccss/ccss.h>

CCSS_BEGIN_DECLS

void
ccss_cairo_background_fill (ccss_background_attachment_t const  *bg_attachment,
			    ccss_color_t const			*bg_color,
			    ccss_background_image_t const       *bg_image,
			    ccss_background_position_t const    *bg_position,
			    ccss_background_repeat_t const      *bg_repeat,
			    ccss_background_size_t const	*bg_size,
			    cairo_t				*cr,
			    double				 x,
			    double				 y,
			    double				 width,
			    double				 height);

CCSS_END_DECLS

#endif /* CCSS_CAIRO_BACKGROUND_H */

