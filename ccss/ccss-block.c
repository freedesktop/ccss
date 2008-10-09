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

#include "ccss-block.h"

static GQuark _BACKGROUND_ATTACHMENT		= 0;
static GQuark _BACKGROUND_COLOR			= 0;
static GQuark _BACKGROUND_IMAGE			= 0;
static GQuark _BACKGROUND_POSITION		= 0;
static GQuark _BACKGROUND_REPEAT		= 0;
static GQuark _BACKGROUND_SIZE			= 0;

static GQuark _BORDER_BOTTOM_COLOR		= 0;
static GQuark _BORDER_BOTTOM_STYLE		= 0;
static GQuark _BORDER_BOTTOM_WIDTH		= 0;

static GQuark _BORDER_LEFT_COLOR		= 0;
static GQuark _BORDER_LEFT_STYLE		= 0;
static GQuark _BORDER_LEFT_WIDTH		= 0;

static GQuark _BORDER_RIGHT_COLOR		= 0;
static GQuark _BORDER_RIGHT_STYLE		= 0;
static GQuark _BORDER_RIGHT_WIDTH		= 0;

static GQuark _BORDER_TOP_COLOR			= 0;
static GQuark _BORDER_TOP_STYLE			= 0;
static GQuark _BORDER_TOP_WIDTH			= 0;

static GQuark _BORDER_TOP_LEFT_RADIUS		= 0;
static GQuark _BORDER_TOP_RIGHT_RADIUS		= 0;
static GQuark _BORDER_BOTTOM_RIGHT_RADIUS	= 0;
static GQuark _BORDER_BOTTOM_LEFT_RADIUS	= 0;

static GQuark _COLOR				= 0;

/* FIXME: move each quark to its getter and initialise there. */
static void
init (void)
{
	static bool _first_call = true;

	if (!_first_call)
		return;

	_first_call = false;

	_BACKGROUND_ATTACHMENT		= g_quark_from_static_string ("background-attachment");
	_BACKGROUND_COLOR		= g_quark_from_static_string ("background-color");
	_BACKGROUND_IMAGE		= g_quark_from_static_string ("background-image");
	_BACKGROUND_POSITION		= g_quark_from_static_string ("background-position");
	_BACKGROUND_REPEAT		= g_quark_from_static_string ("background-repeat");
	_BACKGROUND_SIZE		= g_quark_from_static_string ("background-size");

	_BORDER_BOTTOM_COLOR		= g_quark_from_static_string ("border-bottom-color");
	_BORDER_BOTTOM_STYLE		= g_quark_from_static_string ("border-bottom-style");
	_BORDER_BOTTOM_WIDTH		= g_quark_from_static_string ("border-bottom-width");

	_BORDER_LEFT_COLOR		= g_quark_from_static_string ("border-left-color");
	_BORDER_LEFT_STYLE		= g_quark_from_static_string ("border-left-style");
	_BORDER_LEFT_WIDTH		= g_quark_from_static_string ("border-left-width");

	_BORDER_RIGHT_COLOR		= g_quark_from_static_string ("border-right-color");
	_BORDER_RIGHT_STYLE		= g_quark_from_static_string ("border-right-style");
	_BORDER_RIGHT_WIDTH		= g_quark_from_static_string ("border-right-width");

	_BORDER_TOP_COLOR		= g_quark_from_static_string ("border-top-color");
	_BORDER_TOP_STYLE		= g_quark_from_static_string ("border-top-style");
	_BORDER_TOP_WIDTH		= g_quark_from_static_string ("border-top-width");

	_BORDER_TOP_LEFT_RADIUS		= g_quark_from_static_string ("border-top-left-radius");
	_BORDER_TOP_RIGHT_RADIUS	= g_quark_from_static_string ("border-top-right-radius");
	_BORDER_BOTTOM_LEFT_RADIUS	= g_quark_from_static_string ("border-bottom-left-radius");
	_BORDER_BOTTOM_RIGHT_RADIUS	= g_quark_from_static_string ("border-bottom-right-radius");

	_COLOR				= g_quark_from_static_string ("color");
}

GQuark
ccss_property_background_attachment (void)
{
	init ();
	return _BACKGROUND_ATTACHMENT;
}

GQuark
ccss_property_background_color (void)
{
	init ();
	return _BACKGROUND_COLOR;
}

GQuark
ccss_property_background_image (void)
{
	init ();
	return _BACKGROUND_IMAGE;
}

GQuark
ccss_property_background_position (void)
{
	init ();
	return _BACKGROUND_POSITION;
}

GQuark
ccss_property_background_repeat (void)
{
	init ();
	return _BACKGROUND_REPEAT;
}

GQuark
ccss_property_background_size (void)
{
	init ();
	return _BACKGROUND_SIZE;
}

GQuark
ccss_property_border_bottom_color (void)
{
	init ();
	return _BORDER_BOTTOM_COLOR;
}

GQuark
ccss_property_border_bottom_style (void)
{
	init ();
	return _BORDER_BOTTOM_STYLE;
}

GQuark
ccss_property_border_bottom_width (void)
{
	init ();
	return _BORDER_BOTTOM_WIDTH;
}

GQuark
ccss_property_border_left_color (void)
{
	init ();
	return _BORDER_LEFT_COLOR;
}

GQuark
ccss_property_border_left_style (void)
{
	init ();
	return _BORDER_LEFT_STYLE;
}

GQuark
ccss_property_border_left_width (void)
{
	init ();
	return _BORDER_LEFT_WIDTH;
}

GQuark
ccss_property_border_right_color (void)
{
	init ();
	return _BORDER_RIGHT_COLOR;
}

GQuark
ccss_property_border_right_style (void)
{
	init ();
	return _BORDER_RIGHT_STYLE;
}

GQuark
ccss_property_border_right_width (void)
{
	init ();
	return _BORDER_RIGHT_WIDTH;
}

GQuark
ccss_property_border_top_color (void)
{
	init ();
	return _BORDER_TOP_COLOR;
}

GQuark
ccss_property_border_top_style (void)
{
	init ();
	return _BORDER_TOP_STYLE;
}

GQuark
ccss_property_border_top_width (void)
{
	init ();
	return _BORDER_TOP_WIDTH;
}

GQuark
ccss_property_border_top_left_radius (void)
{
	init ();
	return _BORDER_TOP_LEFT_RADIUS;
}

GQuark
ccss_property_border_top_right_radius (void)
{
	init ();
	return _BORDER_TOP_RIGHT_RADIUS;
}

GQuark
ccss_property_border_bottom_right_radius (void)
{
	init ();
	return _BORDER_BOTTOM_RIGHT_RADIUS;
}

GQuark
ccss_property_border_bottom_left_radius (void)
{
	init ();
	return _BORDER_BOTTOM_LEFT_RADIUS;
}

GQuark
ccss_property_color (void)
{
	init ();
	return _COLOR;
}

ccss_block_t *
ccss_block_new (void)
{
	ccss_block_t *self;

	init ();

	self = g_new0 (ccss_block_t, 1);
	self->properties = g_hash_table_new_full ((GHashFunc) g_direct_hash, 
						  (GEqualFunc) g_direct_equal,
						  NULL,
						  (GDestroyNotify) g_free);

	return self;
}

void
ccss_block_free (ccss_block_t *self)
{
	g_return_if_fail (self && self->properties);

	g_hash_table_destroy (self->properties), self->properties = NULL;
	g_free (self);
}

ccss_background_attachment_t *
ccss_block_new_background_attachment (ccss_block_t *self)
{
	ccss_background_attachment_t *bg_attachment;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_attachment = (ccss_background_attachment_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_ATTACHMENT);
	if (!bg_attachment) {
		bg_attachment = g_new0 (ccss_background_attachment_t, 1);
		g_hash_table_insert (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_ATTACHMENT,
				(gpointer) bg_attachment);
	}
	
	return bg_attachment;
}

ccss_color_t *
ccss_block_new_background_color (ccss_block_t *self)
{
	ccss_color_t *bg_color;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_COLOR);
	if (!bg_color) {
		bg_color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_COLOR,
				(gpointer) bg_color);
	}
	
	return bg_color;
}

ccss_background_image_t *
ccss_block_new_background_image (ccss_block_t *self)
{
	ccss_background_image_t *bg_image;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_image = (ccss_background_image_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_IMAGE);
	if (!bg_image) {
		bg_image = g_new0 (ccss_background_image_t, 1);
		g_hash_table_insert (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_IMAGE,
				(gpointer) bg_image);
	}
	
	return bg_image;
}

ccss_background_position_t *
ccss_block_new_background_position (ccss_block_t *self)
{
	ccss_background_position_t *bg_position;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_position = (ccss_background_position_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_POSITION);
	if (!bg_position) {
		bg_position = g_new0 (ccss_background_position_t, 1);
		g_hash_table_insert (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_POSITION,
				(gpointer) bg_position);
	}
	
	return bg_position;
}

ccss_background_repeat_t *
ccss_block_new_background_repeat (ccss_block_t *self)
{
	ccss_background_repeat_t *bg_repeat;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_repeat = (ccss_background_repeat_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_REPEAT);
	if (!bg_repeat) {
		bg_repeat = g_new0 (ccss_background_repeat_t, 1);
		g_hash_table_insert (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_REPEAT,
				(gpointer) bg_repeat);
	}
	
	return bg_repeat;
}

ccss_background_size_t *
ccss_block_new_background_size (ccss_block_t *self)
{
	ccss_background_size_t *bg_size;

	g_return_val_if_fail (self && self->properties, NULL);

	bg_size = (ccss_background_size_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_SIZE);
	if (!bg_size) {
		bg_size = g_new0 (ccss_background_size_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_SIZE,
				(gpointer) bg_size);
	}
	
	return bg_size;
}

ccss_color_t *
ccss_block_new_border_bottom_color (ccss_block_t *self)
{
	ccss_color_t *color;

	g_return_val_if_fail (self && self->properties, NULL);

	color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_COLOR);
	if (!color) {
		color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_COLOR,
				(gpointer) color);
	}
	
	return color;
}

ccss_border_style_t *
ccss_block_new_border_bottom_style (ccss_block_t *self)
{
	ccss_border_style_t *style;

	g_return_val_if_fail (self && self->properties, NULL);

	style = (ccss_border_style_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_STYLE);
	if (!style) {
		style = g_new0 (ccss_border_style_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_STYLE,
				(gpointer) style);
	}
	
	return style;
}

ccss_border_width_t *
ccss_block_new_border_bottom_width (ccss_block_t *self)
{
	ccss_border_width_t *width;

	g_return_val_if_fail (self && self->properties, NULL);

	width = (ccss_border_width_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_WIDTH);
	if (!width) {
		width = g_new0 (ccss_border_width_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_WIDTH,
				(gpointer) width);
	}
	
	return width;
}

ccss_color_t *
ccss_block_new_border_left_color (ccss_block_t *self)
{
	ccss_color_t *color;

	g_return_val_if_fail (self && self->properties, NULL);

	color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_COLOR);
	if (!color) {
		color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_COLOR,
				(gpointer) color);
	}
	
	return color;
}

ccss_border_style_t *
ccss_block_new_border_left_style (ccss_block_t *self)
{
	ccss_border_style_t *style;

	g_return_val_if_fail (self && self->properties, NULL);

	style = (ccss_border_style_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_STYLE);
	if (!style) {
		style = g_new0 (ccss_border_style_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_STYLE,
				(gpointer) style);
	}
	
	return style;
}

ccss_border_width_t *
ccss_block_new_border_left_width (ccss_block_t *self)
{
	ccss_border_width_t *width;

	g_return_val_if_fail (self && self->properties, NULL);

	width = (ccss_border_width_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_WIDTH);
	if (!width) {
		width = g_new0 (ccss_border_width_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_WIDTH,
				(gpointer) width);
	}
	
	return width;
}

ccss_color_t *
ccss_block_new_border_right_color (ccss_block_t *self)
{
	ccss_color_t *color;

	g_return_val_if_fail (self && self->properties, NULL);

	color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_COLOR);
	if (!color) {
		color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_COLOR,
				(gpointer) color);
	}
	
	return color;
}

ccss_border_style_t *
ccss_block_new_border_right_style (ccss_block_t *self)
{
	ccss_border_style_t *style;

	g_return_val_if_fail (self && self->properties, NULL);

	style = (ccss_border_style_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_STYLE);
	if (!style) {
		style = g_new0 (ccss_border_style_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_STYLE,
				(gpointer) style);
	}
	
	return style;
}

ccss_border_width_t *
ccss_block_new_border_right_width (ccss_block_t *self)
{
	ccss_border_width_t *width;

	g_return_val_if_fail (self && self->properties, NULL);

	width = (ccss_border_width_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_WIDTH);
	if (!width) {
		width = g_new0 (ccss_border_width_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_WIDTH,
				(gpointer) width);
	}
	
	return width;
}

ccss_color_t *
ccss_block_new_border_top_color (ccss_block_t *self)
{
	ccss_color_t *color;

	g_return_val_if_fail (self && self->properties, NULL);

	color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_COLOR);
	if (!color) {
		color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_COLOR,
				(gpointer) color);
	}
	
	return color;
}

ccss_border_style_t *
ccss_block_new_border_top_style (ccss_block_t *self)
{
	ccss_border_style_t *style;

	g_return_val_if_fail (self && self->properties, NULL);

	style = (ccss_border_style_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_STYLE);
	if (!style) {
		style = g_new0 (ccss_border_style_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_STYLE,
				(gpointer) style);
	}
	
	return style;
}

ccss_border_width_t *
ccss_block_new_border_top_width (ccss_block_t *self)
{
	ccss_border_width_t *width;

	g_return_val_if_fail (self && self->properties, NULL);

	width = (ccss_border_width_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_WIDTH);
	if (!width) {
		width = g_new0 (ccss_border_width_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_WIDTH,
				(gpointer) width);
	}
	
	return width;
}

ccss_border_join_t *
ccss_block_new_border_bottom_left_radius (ccss_block_t *self)
{
	ccss_border_join_t *join;

	g_return_val_if_fail (self && self->properties, NULL);

	join = (ccss_border_join_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_LEFT_RADIUS);
	if (!join) {
		join = g_new0 (ccss_border_join_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_LEFT_RADIUS,
				(gpointer) join);
	}
	
	return join;
}

ccss_border_join_t *
ccss_block_new_border_bottom_right_radius (ccss_block_t *self)
{
	ccss_border_join_t *join;

	g_return_val_if_fail (self && self->properties, NULL);

	join = (ccss_border_join_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS);
	if (!join) {
		join = g_new0 (ccss_border_join_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS,
				(gpointer) join);
	}
	
	return join;
}

ccss_border_join_t *
ccss_block_new_border_top_left_radius (ccss_block_t *self)
{
	ccss_border_join_t *join;

	g_return_val_if_fail (self && self->properties, NULL);

	join = (ccss_border_join_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_LEFT_RADIUS);
	if (!join) {
		join = g_new0 (ccss_border_join_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_LEFT_RADIUS,
				(gpointer) join);
	}
	
	return join;
}

ccss_border_join_t *
ccss_block_new_border_top_right_radius (ccss_block_t *self)
{
	ccss_border_join_t *join;

	g_return_val_if_fail (self && self->properties, NULL);

	join = (ccss_border_join_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_RIGHT_RADIUS);
	if (!join) {
		join = g_new0 (ccss_border_join_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_RIGHT_RADIUS,
				(gpointer) join);
	}
	
	return join;
}

ccss_color_t *
ccss_block_new_color (ccss_block_t *self)
{
	ccss_color_t *color;

	g_return_val_if_fail (self && self->properties, NULL);

	color = (ccss_color_t *) g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_COLOR);
	if (!color) {
		color = g_new0 (ccss_color_t, 1);
		g_hash_table_insert (self->properties,
				(gpointer) CCSS_PROPERTY_COLOR,
				(gpointer) color);
	}
	
	return color;
}

ccss_background_attachment_t const *
ccss_block_get_background_attachment (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_background_attachment_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_ATTACHMENT);
}

ccss_color_t const *
ccss_block_get_background_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_COLOR);
}

ccss_background_image_t const *
ccss_block_get_background_image (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_background_image_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_IMAGE);
}

ccss_background_position_t const *
ccss_block_get_background_position (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_background_position_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_POSITION);
}

ccss_background_repeat_t const *
ccss_block_get_background_repeat (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_background_repeat_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_REPEAT);
}

ccss_background_size_t const *
ccss_block_get_background_size (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_background_size_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BACKGROUND_SIZE);
}

ccss_color_t const *
ccss_block_get_border_bottom_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_COLOR);
}

ccss_border_style_t const *
ccss_block_get_border_bottom_style (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_style_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_STYLE);
}

ccss_border_width_t const *
ccss_block_get_border_bottom_width (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_width_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_WIDTH);
}

ccss_color_t const *
ccss_block_get_border_left_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_COLOR);
}

ccss_border_style_t const *
ccss_block_get_border_left_style (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_style_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_STYLE);
}

ccss_border_width_t const *
ccss_block_get_border_left_width (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_width_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_LEFT_WIDTH);
}

ccss_color_t const *
ccss_block_get_border_right_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_COLOR);
}

ccss_border_style_t const *
ccss_block_get_border_right_style (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_style_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_STYLE);
}

ccss_border_width_t const *
ccss_block_get_border_right_width (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_width_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_RIGHT_WIDTH);
}

ccss_color_t const *
ccss_block_get_border_top_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_COLOR);
}

ccss_border_style_t const *
ccss_block_get_border_top_style (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_style_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_STYLE);
}

ccss_border_width_t const *
ccss_block_get_border_top_width (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_width_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_WIDTH);
}

ccss_border_join_t const *
ccss_block_get_border_bottom_left_radius (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_join_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_LEFT_RADIUS);
}

ccss_border_join_t const *
ccss_block_get_border_bottom_right_radius (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_join_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS);
}

ccss_border_join_t const *
ccss_block_get_border_top_left_radius (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_join_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_LEFT_RADIUS);
}

ccss_border_join_t const *
ccss_block_get_border_top_right_radius (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_border_join_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_BORDER_TOP_RIGHT_RADIUS);
}

ccss_color_t const *
ccss_block_get_color (ccss_block_t const *self)
{
	g_return_val_if_fail (self && self->properties, NULL);

	return (ccss_color_t const *) 
			g_hash_table_lookup (
				self->properties,
				(gpointer) CCSS_PROPERTY_COLOR);
}

#ifdef CCSS_DEBUG

void
ccss_block_dump (ccss_block_t const *self)
{
/* TODO
	ccss_background_dump (&self->background);
	ccss_border_dump (&self->border);
	ccss_color_dump (&self->color);
*/
}

#endif /* CCSS_DEBUG */

