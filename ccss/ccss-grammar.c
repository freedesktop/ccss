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

#include <glib.h>
#include "ccss-grammar-priv.h"
#include "ccss-property-generic.h"
#include "ccss-stylesheet-priv.h"
#include "config.h"

/**
 * ccss_grammar_create:
 *
 * Create a new grammar instance.
 *
 * Grammar objects provide a factory to create stylesheets of the same class.
 *
 * Returns: a new #ccss_grammar_t instance.
 **/
ccss_grammar_t *
ccss_grammar_create (void)
{
	ccss_grammar_t *self;

	self = g_new0 (ccss_grammar_t, 1);
	self->reference_count = 1;
	self->properties = g_hash_table_new (g_str_hash, g_str_equal);
	self->functions = g_hash_table_new (g_str_hash, g_str_equal);

	ccss_grammar_add_properties (self, ccss_property_generic_get_ptable ());

	return self;
}

/**
 * ccss_grammar_destroy:
 * @self: a #ccss_grammar_t.
 *
 * Decreases the reference count on @self by one. If the result is zero, then
 * @self and all associated resources are freed. See #ccss_grammar_reference().
 **/
void
ccss_grammar_destroy (ccss_grammar_t *self)
{
	g_assert (self && self->reference_count > 0);

	self->reference_count--;

	if (0 == self->reference_count) {
		g_hash_table_destroy (self->properties), self->properties = NULL;
		g_hash_table_destroy (self->functions), self->functions = NULL;
		g_free (self);
	}
}

/**
 * ccss_grammar_reference:
 * @self: a #ccss_grammar_t.
 *
 * Increases the reference count on cr by one. This prevents cr from being
 * destroyed until a matching call to ccss_grammar_destroy() is made.
 *
 * The number of references to a #ccss_grammar_t can be acquired using
 * #ccss_grammar_get_reference_count().
 *
 * Returns: the referenced #ccss_grammar_t.
 **/
ccss_grammar_t *
ccss_grammar_reference (ccss_grammar_t *self)
{
	g_return_val_if_fail (self, NULL);

	self->reference_count++;

	return self;
}

/**
 * ccss_grammar_get_reference_count:
 * @self: a #ccss_grammar_t.
 *
 * Returns: the current reference count of @self.
 *	    If @self is a nil object, 0 will be returned.
 **/
unsigned int
ccss_grammar_get_reference_count (ccss_grammar_t const *self)
{
	g_return_val_if_fail (self, 0);

	return self->reference_count;
}

/**
 * ccss_grammar_add_properties:
 * @self: a #ccss_grammar_t.
 * @properties:	Null-terminated array of #ccss_property_class_t to register.
 *
 * Register a set of custom CSS properties with the grammar.
 **/
void
ccss_grammar_add_properties (ccss_grammar_t			*self,
			     ccss_property_class_t const	*properties)
{
	g_return_if_fail (self && properties);

	for (unsigned int i = 0; properties[i].name != NULL; i++) {

		/* Handler already exists? */
		g_warn_if_fail (NULL == g_hash_table_lookup (self->properties, properties[i].name));

		g_hash_table_insert (self->properties,
				     (gpointer) properties[i].name,
				     (gpointer) &properties[i]);
	}
}

/**
 * ccss_grammar_add_functions:
 * @functions:	Null-terminated array of #ccss_function_t to register.
 *
 * Register a set of custom css function handlers with the grammar.
 **/
void
ccss_grammar_add_functions (ccss_grammar_t		*self,
			    ccss_function_t const	*functions)
{
	g_return_if_fail (self && functions);

	for (unsigned int i = 0; functions[i].name != NULL; i++) {

		/* Handler already exists? */
		g_warn_if_fail (NULL == g_hash_table_lookup (self->functions, functions[i].name));

		g_hash_table_insert (self->functions,
				     (gpointer) functions[i].name,
				     (gpointer) &functions[i]);
	}
}

/**
 * ccss_grammar_create_stylesheet_from_buffer:
 * @self:	a #ccss_grammar_t.
 * @buffer:	buffer to parse.
 * @size:	size of the buffer.
 *
 * Create a new stylesheet instance based on a CSS string.
 *
 * Returns: a #ccss_stylesheet_t representation of the CSS string.
 **/
ccss_stylesheet_t *
ccss_grammar_create_stylesheet_from_buffer (ccss_grammar_t	*self,
					    char const		*buffer,
					    size_t		 size)
{
	ccss_stylesheet_t	*stylesheet;
	enum CRStatus		 ret;

	stylesheet = ccss_stylesheet_create ();
	stylesheet->grammar = ccss_grammar_reference (self);

	ret = ccss_parser_parse_buffer (self, buffer, size, 
					CCSS_STYLESHEET_AUTHOR,
					stylesheet->groups, stylesheet->blocks);

	ccss_stylesheet_fix_dangling_selectors (stylesheet);

	// FIXME handle `ret'

	return stylesheet;
}

/**
 * ccss_grammar_create_stylesheet_from_file:
 * @self:	a #ccss_grammar_t.
 * @css_file:	file to parse.
 *
 * Create a new stylesheet instance based on a CSS file.
 *
 * Returns: a #ccss_stylesheet_t representation of the CSS file.
 **/
ccss_stylesheet_t *
ccss_grammar_create_stylesheet_from_file (ccss_grammar_t	*self,
					  char const		*css_file)
{
	ccss_stylesheet_t	*stylesheet;
	enum CRStatus		 ret;

	stylesheet = ccss_stylesheet_create ();
	stylesheet->grammar = ccss_grammar_reference (self);

	ret = ccss_parser_parse_file (self, css_file, CCSS_STYLESHEET_AUTHOR,
				      stylesheet->groups, stylesheet->blocks);

	ccss_stylesheet_fix_dangling_selectors (stylesheet);

	// FIXME handle `ret'

	return stylesheet;
}
