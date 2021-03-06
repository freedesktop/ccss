/* vim: set ts=8 sw=8 noexpandtab: */

/* The `C' CSS Library.
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
#include <glib.h>
#include <ccss/ccss-node.h>
#include <ccss/ccss-macros.h>
#include <ccss/ccss-selector.h>
#include <ccss/ccss-style.h>

CCSS_BEGIN_DECLS

typedef struct ccss_selector_group_ ccss_selector_group_t;

ccss_selector_group_t *	
ccss_selector_group_create	(void);

void
ccss_selector_group_destroy	(ccss_selector_group_t		*self);

bool
ccss_selector_group_unload	(ccss_selector_group_t		*self,
				 unsigned int			 descriptor);

bool
ccss_selector_group_apply_type (ccss_selector_group_t const	*self, 
				char const			*type,
				ccss_style_t			*style);

bool
ccss_selector_group_apply	(ccss_selector_group_t const	*self,
				 ccss_node_t const		*node,
				 ccss_style_t			*style);

void
ccss_selector_group_add_selector	(ccss_selector_group_t		*self, 
					 ccss_selector_t		*selector);

void
ccss_selector_group_merge_as_base	(ccss_selector_group_t		*self,
					 ccss_selector_group_t const	*group);

GSList const *
ccss_selector_group_get_dangling_selectors	(ccss_selector_group_t const	*self);

void
ccss_selector_group_clear_dangling_selectors	(ccss_selector_group_t		*self);

bool
ccss_selector_group_query (ccss_selector_group_t const	*self, 
			   ccss_node_t			*node,
			   bool				 as_base,
			   ccss_selector_group_t	*result_group);

void
ccss_selector_group_dump (ccss_selector_group_t const *self);

CCSS_END_DECLS

#endif /* CCSS_SELECTOR_GROUP_H */

