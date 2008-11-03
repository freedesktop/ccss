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

#ifndef CCSS_COLOR_H
#define CCSS_COLOR_H

#include <stdbool.h>
#include <libcroco/libcroco.h>
#include <ccss/ccss-macros.h>
#include <ccss/ccss-property.h>

CCSS_BEGIN_DECLS

#define CCSS_COLOR_ASSIGN(lhs_, rhs_) {		\
	(lhs_).spec = (rhs_).spec;		\
	(lhs_).red = (rhs_).red;		\
	(lhs_).green = (rhs_).green;		\
	(lhs_).blue = (rhs_).blue;		\
}

typedef struct {
	ccss_property_spec_t	spec;
	double			red;
	double			green;
	double			blue;
} ccss_color_t;

void ccss_color_init (ccss_color_t *self);

bool ccss_color_parse (ccss_color_t *self, CRTerm const **values);

#ifdef CCSS_DEBUG
void ccss_color_dump (ccss_color_t const *self);
#endif

CCSS_END_DECLS

#endif /* CCSS_COLOR_H */

