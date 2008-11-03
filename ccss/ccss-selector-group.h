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

#ifndef CCSS_SELECTOR_GROUP_H
#define CCSS_SELECTOR_GROUP_H

#include <stdbool.h>
#include <ccss/ccss-features.h>
#include <ccss/ccss-macros.h>
#include <ccss/ccss-style.h>

CCSS_BEGIN_DECLS

typedef struct ccss_selector_group_ ccss_selector_group_t;

#ifdef CCSS_DEBUG

void
ccss_selector_group_dump (ccss_selector_group_t const *self);

#endif

CCSS_END_DECLS

#endif /* CCSS_SELECTOR_GROUP_H */

