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

#include "ccss-selector-group-priv.h"

typedef struct {
	GSList *selectors;
} ccss_selector_set_t;

/**
 * ccss_selector_group_t:
 * @sets:		
 * @min_specificity_e:	
 * @dangling_selectors:
 * 
 * Represents a set of associated styling information. 
 **/
struct ccss_selector_group_ {
	GHashTable	*sets;
	unsigned int	 n_selectors;
	unsigned int	 min_specificity_e;
	GSList		*dangling_selectors;
};

static void
free_set (ccss_selector_set_t *set)
{
	GSList		*iter;
	ccss_selector_t	*selector;

	g_assert (set);

	iter = set->selectors;
	while (iter) {
		selector = (ccss_selector_t *) iter->data;
		iter = g_slist_remove (iter, selector);
		ccss_selector_free (selector);
	}

	g_free (set);
}

/**
 * ccss_selector_group_new:
 *
 * Create an empty selector group.
 *
 * A newly allocated #ccss_selector_group_t.
 **/
ccss_selector_group_t *
ccss_selector_group_new (void)
{
	ccss_selector_group_t *self;

	self = g_new0 (ccss_selector_group_t, 1);
	self->sets = g_hash_table_new_full (g_direct_hash, g_direct_equal, 
					    NULL, (GDestroyNotify) free_set);

	self->n_selectors = 0;
	self->min_specificity_e = CCSS_SELECTOR_MAX_SPECIFICITY;

	return self;
}

/**
 * ccss_selector_group_free:
 * @self: a #ccss_selector_group_t.
 * 
 * Free the selector group and all associated resources.
 **/
void
ccss_selector_group_free (ccss_selector_group_t *self)
{
	g_assert (self);

	g_hash_table_destroy (self->sets);
	g_free (self);
}

/*
 * Takes ownership of the selector.
 */
void
ccss_selector_group_add_selector (ccss_selector_group_t	*self, 
				 ccss_selector_t		*selector)
{
	ccss_selector_set_t	*set;
	size_t			 specificity;

	g_return_if_fail (self && selector);

	/* insert or update the selector group */
	specificity = ccss_selector_get_specificity (selector);
	set = g_hash_table_lookup (self->sets, GSIZE_TO_POINTER (specificity));
	if (!set) {
		set = g_new0 (ccss_selector_set_t, 1);
		g_hash_table_insert (self->sets, GSIZE_TO_POINTER (specificity), set);
	}
	set->selectors = g_slist_prepend (set->selectors, selector);
	self->n_selectors++;
}

static unsigned int
calculate_min_specificity_e (ccss_selector_group_t	*group,
			     unsigned int		 n_specificities)
{
	unsigned int specificity_e;

	/* The tree is walked in order, so we remember how many 
	 * specificities `e' will be required to insert the merged selectors at 
	 * the right place. `- 1' because "group->min_specificity_e" already has
	 * the next free value. */
	g_assert (((signed) group->min_specificity_e - (signed) n_specificities - 1) >= 0);
	specificity_e = group->min_specificity_e - n_specificities - 1;

	group->min_specificity_e -= n_specificities;
	g_assert (group->min_specificity_e >= 0);

	return specificity_e;
}

typedef struct {
	ccss_selector_group_t	*self;
	bool			 as_base;
	unsigned int		 specificity_e;
} traverse_merge_info_t;

static bool
traverse_merge (size_t			 	 specificity,
		ccss_selector_set_t const	*set,
		traverse_merge_info_t		*info)
{
	ccss_selector_t const	*selector;
	ccss_selector_t		*new_selector;

	g_assert (info->self && set);

	for (GSList const *iter = set->selectors; iter != NULL; iter = iter->next) {
		selector = (ccss_selector_t const *) iter->data;
		if (info->as_base) {
			new_selector = ccss_selector_copy_as_base (selector, info->specificity_e);
		} else {
			new_selector = ccss_selector_copy (selector);
		}
		ccss_selector_group_add_selector (info->self, new_selector);
	}

	info->specificity_e++;

	return false;
}

void
ccss_selector_group_merge (ccss_selector_group_t		*self,
			  ccss_selector_group_t const	*group)
{
	traverse_merge_info_t info;

	g_assert (self && group);

	info.self = self;
	info.as_base = false;
	info.specificity_e = 0;
	g_hash_table_foreach (group->sets, (GHFunc) traverse_merge, &info);
}

void
ccss_selector_group_merge_base (ccss_selector_group_t		*self,
			       ccss_selector_group_t const	*group)
{
	traverse_merge_info_t info;

	g_assert (self && group);

	info.self = self;
	info.as_base = true;
	info.specificity_e = calculate_min_specificity_e (self, 
				self->n_selectors);

	g_hash_table_foreach (group->sets, (GHFunc) traverse_merge, &info);
}

GSList const *
ccss_selector_group_get_dangling_selectors (ccss_selector_group_t const *self)
{
	g_assert (self);

	return self->dangling_selectors;
}

void
ccss_selector_group_clear_dangling_selectors (ccss_selector_group_t *self)
{
	ccss_selector_t	*selector;
	GSList		*iter;

	g_return_if_fail (self && self->dangling_selectors);

	iter = self->dangling_selectors;
	while (iter) {
		selector = (ccss_selector_t *) iter->data;
		iter = g_slist_remove (iter, selector);
		ccss_selector_free (selector);
	}

	self->dangling_selectors = NULL;
}

typedef struct {
	ccss_node_t const	*node;
	ccss_style_t		*style;
	bool			 ret;
} traverse_match_info_t;

static bool
traverse_match (size_t			 specificity,
		ccss_selector_set_t	*set,
		traverse_match_info_t	*info)
{
	for (GSList const *iter = set->selectors; iter != NULL; iter = iter->next) {
		info->ret |= ccss_selector_query_apply ((ccss_selector_t const *) iter->data, 
						 info->node, info->style);
	}

	return false;
}

bool
ccss_selector_group_query_apply (ccss_selector_group_t const	*self,
				ccss_node_t const		*node,
				ccss_style_t			*style)
{
	traverse_match_info_t info;

	g_assert (self && self->sets && node && style);

	info.node = node;
	info.style = style;
	info.ret = false;

	g_hash_table_foreach (self->sets, (GHFunc) traverse_match, &info);

	return info.ret;
}

typedef struct {
	char const		*type_name;
	ccss_style_t		*style;
	bool			 ret;
} traverse_apply_info_t;

static bool
traverse_apply (size_t			 specificity,
		ccss_selector_set_t	*set,
		traverse_apply_info_t	*info)
{
	ccss_selector_t const	*selector;

	for (GSList const *iter = set->selectors; iter != NULL; iter = iter->next) {
	
		selector = (ccss_selector_t const *) iter->data;
		if (info->type_name) {

			/* Apply only if it's a specific type. */
			char const *key;
			unsigned int a, b, c, d, e;

			key = ccss_selector_get_key (selector);
			ccss_selector_get_specificity_values (selector,
							     &a, &b, &c, &d, &e);

			if (ccss_selector_is_type (selector) &&
			    0 == g_strcmp0 (info->type_name, key) &&
			    a == 0 && b == 0 && c == 0 && d == 1 && e == 0) {

				info->ret |= ccss_selector_apply (selector,
								 info->style);
			}

		} else {	
			info->ret |= ccss_selector_apply (selector, info->style);
		}
	}

	return false;
}

/**
 * ccss_selector_group_apply:
 * @self:	a #ccss_selector_group_t.
 * @style:	a #ccss_style_t.
 *
 * Apply the styling information held by #self to #style.
 **/
bool
ccss_selector_group_apply (ccss_selector_group_t const	*self, 
			  ccss_style_t			*style)
{
	traverse_apply_info_t info;

	g_assert (self && self->sets && style);

	info.type_name = NULL;
	info.style = style;
	info.ret = false;

	g_hash_table_foreach (self->sets, (GHFunc) traverse_apply, &info);

	return info.ret;
}

/**
 * ccss_selector_group_apply_type:
 * @self:	a #ccss_selector_group_t.
 * @type:	style information matching exactly this type name will be applied.
 * @style:	a #ccss_style_t.
 *
 * Apply the styling information held by #self to #style.
 *
 * Returns: %TRUE if applicable style information available.
 **/
bool
ccss_selector_group_apply_type (ccss_selector_group_t const	*self, 
			       char const			*type_name,
			       ccss_style_t			*style)
{
	traverse_apply_info_t info;

	g_assert (self && self->sets && style);

	info.type_name = type_name;
	info.style = style;
	info.ret = false;

	g_hash_table_foreach (self->sets, (GHFunc) traverse_apply, &info);

	return info.ret;
}

#ifdef CCSS_DEBUG

static bool
traverse_dump (size_t			 specificity,
	       ccss_selector_set_t	*set,
	       void			*data)
{
	for (GSList const *iter = set->selectors; iter != NULL; iter = iter->next) {
		ccss_selector_dump ((ccss_selector_t const *) iter->data);
	}

	return false;
}

/**
 * ccss_selector_group_dump:
 * @self:	a ccss_selector_group_t.
 *
 * Print informations about the internal state of this object.
 **/
void
ccss_selector_group_dump (ccss_selector_group_t const *self)
{
	

	g_return_if_fail (self);

	g_hash_table_foreach (self->sets, (GHFunc) traverse_dump, NULL);

	for (GSList const *iter = self->dangling_selectors; iter != NULL; iter = iter->next) {
		printf ("(dangling) ");
		ccss_selector_dump ((ccss_selector_t const *) iter->data);
	}
}

#endif /* CCSS_DEBUG */

