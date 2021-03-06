/* vim: set ts=8 sw=8 noexpandtab: */

/* The Gtk+ CSS Drawing Library.
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

#include <string.h>
#include "ccss-gtk-property.h"
#include "ccss-gtk-stylesheet.h"
#include "config.h"

/*
 * Widget implementation for querying the stylesheet.
 */

typedef struct {
	char const	*type_name;
	char const	*id;
	char const	*pseudo_classes[2];
} Widget;

static char const *
get_type (ccss_node_t const *self)
{
	Widget *w = ccss_node_get_user_data (self);

	return w->type_name;
}

static char const *
get_id (ccss_node_t const *self)
{
	Widget *w = ccss_node_get_user_data (self);

	return w->id;
}

static char const **
get_pseudo_classes (ccss_node_t const *self)
{
	Widget *w = ccss_node_get_user_data (self);

	return (char const **) w->pseudo_classes;
}

static ccss_node_class_t _node_class = {
	.is_a			= NULL,
	.get_container		= NULL,
	.get_base_style		= NULL,
	.get_id			= get_id,
	.get_type		= get_type,
	.get_classes		= NULL,
	.get_pseudo_classes	= get_pseudo_classes,
	.get_attribute		= NULL,
	.get_viewport		= NULL,
	.release		= NULL
};

/*
 * Gtkrc creation infrastructure.
 */

enum { NORMAL = 0, ACTIVE, PRELIGHT, SELECTED, INSENSITIVE, N_STATES };
enum {
	FG_SET		= 1 << 0,
	BG_SET		= 1 << 1,
	BASE_SET	= 1 << 2,
	TEXT_SET	= 1 << 3
};
enum {
	STYLE_SET	= 1 << 0,	/* Styling information available. */
	NORMAL_SET	= 1 << 1,	/* `NORMAL' color available. */
	ACTIVE_SET	= 1 << 2,	/* `ACTIVE' color available. */
	PRELIGHT_SET	= 1 << 3,	/* ... */
	SELECTED_SET	= 1 << 4,	/* ... */
	INSENSITIVE_SET	= 1 << 5	/* ... */
};

struct RcBlock {
	struct RcState {
		char fg[8];
		char bg[8];
		char base[8];
		char text[8];
		guint	flags;
	} colors[N_STATES];
	guint		 flags;
	char const	*type_name;
	GSList		*style_properties;
};

static void
style_iterator (ccss_style_t const	 *style,
		char const		 *property_name,
		GSList			**style_properties)
{
	ccss_property_t const		*property;
	ccss_gtk_property_t const	*self;
	char				*prefix;
	char				*rc_string;

	self = NULL;
	property = NULL;
	ccss_style_get_property (style, property_name, &property);
	if (property && ccss_gtk_property_is_style_property (property)) {
		self = (ccss_gtk_property_t const *) property;
	} else {
		return;
	}

	if (self->class_name) {
		prefix = g_strdup_printf ("%s::", self->class_name);
	} else {
		prefix = g_strdup ("");
	}

	rc_string = NULL;
	if (G_TYPE_BOOLEAN == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = %s",
					     prefix, self->property_name,
					     self->content.gboolean_val ?
					     "TRUE" : "FALSE");
	} else if (G_TYPE_STRING == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = \"%s\"",
					     prefix, self->property_name,
					     self->content.gchararray_val);
	} else if (G_TYPE_FLOAT == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = %f",
					     prefix, self->property_name,
					     self->content.gfloat_val);
	} else if (G_TYPE_INT == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = %d",
					     prefix, self->property_name,
					     self->content.gint_val);
	} else if (G_TYPE_UCHAR == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = %d",
					     prefix, self->property_name,
					     self->content.guchar_val);
	} else if (GDK_TYPE_COLOR == self->gtype) {
		char *val;
		val = gdk_color_to_string (&self->content.gdkcolor_val);
		rc_string = g_strdup_printf ("%s%s = %s",
					     prefix, self->property_name,
					     val);
		g_free (val);
	} else if (GTK_TYPE_BORDER == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = { %d, %d, %d, %d }",
					     prefix, self->property_name,
					     self->content.gtkborder_val.left,
					     self->content.gtkborder_val.right,
					     self->content.gtkborder_val.top,
					     self->content.gtkborder_val.bottom);
	} else if (GTK_TYPE_RELIEF_STYLE == self->gtype) {
		char const *val;
		val = self->content.gtkreliefstyle_val == GTK_RELIEF_NORMAL ? "NORMAL" :
		      self->content.gtkreliefstyle_val == GTK_RELIEF_HALF ? "HALF" :
		      self->content.gtkreliefstyle_val == GTK_RELIEF_NONE ? "NONE" : "";
		rc_string = g_strdup_printf ("%s%s = %s",
					     prefix, self->property_name,
					     val);
	} else if (GTK_TYPE_REQUISITION == self->gtype) {
		rc_string = g_strdup_printf ("%s%s = { %d, %d }",
					     prefix, self->property_name,
					     self->content.gtkrequisition_val.width,
					     self->content.gtkrequisition_val.height);
	} else if (GTK_TYPE_SHADOW_TYPE == self->gtype) {
		char const *val;
		val = self->content.gtkshadowtype_val == GTK_SHADOW_NONE ? "NONE" :
		      self->content.gtkshadowtype_val == GTK_SHADOW_IN ? "IN" :
		      self->content.gtkshadowtype_val == GTK_SHADOW_OUT ? "OUT" :
		      self->content.gtkshadowtype_val == GTK_SHADOW_ETCHED_IN ? "ETCHED_IN" :
		      self->content.gtkshadowtype_val == GTK_SHADOW_ETCHED_OUT ? "ETCHED_OUT" : "";
		rc_string = g_strdup_printf ("%s%s = %s",
					     prefix, self->property_name,
					     val);
	} else if (GTK_TYPE_TOOLBAR_SPACE_STYLE == self->gtype) {
		char const *val;
		val = self->content.gtktoolbarspacestyle_val == GTK_TOOLBAR_SPACE_EMPTY ? "EMPTY" :
		      self->content.gtktoolbarspacestyle_val == GTK_TOOLBAR_SPACE_LINE ? "LINE" : "";
		rc_string = g_strdup_printf ("%s%s = %s",
					     prefix, self->property_name,
					     val);
	} else {
		g_assert_not_reached ();
	}

	if (rc_string) {
		*style_properties = g_slist_prepend (*style_properties, rc_string);
	}
}

static gboolean
set_base_and_text (char const *type_name)
{
	static char const *_text_widgets[] = { "GtkCellView", "GtkEntry",
						"GtkTextView" };

	for (unsigned int i = 0; i < G_N_ELEMENTS (_text_widgets); i++) {
		if (0 == g_strcmp0 (type_name, _text_widgets[i])) {
			return true;
		}
	}

	return false;
}

static char const *
get_rc_selector (char const *type_name)
{
	static const struct {
		char const *type_name;
		char const *rc_selector;
	} _selectors[] = {
		/* Apply button's style to its label. */
		{ "GtkButton", "widget_class \"*.<GtkButton>.*\"" },
		/* Apply menu-item's style to its label. */
		{ "GtkMenuItem", "widget_class \"*.<GtkMenuItem>.*\"" }
	};

	for (unsigned int i = 0; i < G_N_ELEMENTS (_selectors); i++) {
		if (0 == g_strcmp0 (type_name, _selectors[i].type_name)) {
			return _selectors[i].rc_selector;
		}
	}

	return NULL;
}

static gboolean
accumulate_state (ccss_stylesheet_t 	 *stylesheet,
		  char const		 *type_name,
		  char const		 *state_name,
		  struct RcState	 *state,
		  GSList		**style_properties)
{
	ccss_style_t	*style;
	ccss_node_t	*node;
	Widget		 widget;
	char		*color;
	gboolean	 ret;

	widget.type_name = type_name;
	widget.id = NULL;
	widget.pseudo_classes[0] = state_name;
	widget.pseudo_classes[1] = NULL;
	node = ccss_node_create (&_node_class,
				 CCSS_NODE_CLASS_N_METHODS (_node_class),
				 &widget);
	style = ccss_stylesheet_query (stylesheet, node);
	ccss_node_destroy (node);
	if (!style) {
		return false;
	}

	color = NULL;

	if (set_base_and_text (type_name)) {

		ret = ccss_style_get_string (style, "background-color", &color);
		if (ret) {
			state->flags |= BASE_SET;
			strncpy (state->base, color, 7); /* '#rrggbb', omit alpha */
			g_free (color), color = NULL;
		}

		ret = ccss_style_get_string (style, "color", &color);
		if (ret && color) {
			state->flags |= TEXT_SET;
			strncpy (state->text, color, 7); /* '#rrggbb', omit alpha */
			g_free (color), color = NULL;
		}

	} else {

		ret = ccss_style_get_string (style, "background-color", &color);
		if (ret) {
			state->flags |= BG_SET;
			strncpy (state->bg, color, 7); /* '#rrggbb', omit alpha */
			g_free (color), color = NULL;
		}

		ret = ccss_style_get_string (style, "color", &color);
		if (ret && color) {
			state->flags |= FG_SET;
			strncpy (state->fg, color, 7); /* '#rrggbb', omit alpha */
			g_free (color), color = NULL;
		}
	}

	/* Extract style properties, only for default state. */
	if (style_properties) {
		ccss_style_foreach (style, (ccss_style_iterator_f) style_iterator,
				    style_properties);
	}

	ccss_style_destroy (style), style = NULL;

	/* Having colors or style properties means there's something to serialise. */
	return true;
}

static bool
accumulate (ccss_stylesheet_t	*stylesheet,
	    struct RcBlock	*block)
{
	bool ret;

	/* Querying for `normal' state without any- and with the `normal' pseudo class. */
	ret = accumulate_state (stylesheet, block->type_name, NULL,
				&block->colors[NORMAL], &block->style_properties);
	if (ret) {
		block->flags |= STYLE_SET;
		if (block->colors[NORMAL].flags) {
			block->flags |= NORMAL_SET;
		}
	}

	ret = accumulate_state (stylesheet, block->type_name, "normal",
				&block->colors[NORMAL], NULL);
	if (ret && block->colors[NORMAL].flags) {
		block->flags |= NORMAL_SET;
	}

	ret = accumulate_state (stylesheet, block->type_name, "active",
				&block->colors[ACTIVE], NULL);
	if (ret && block->colors[ACTIVE].flags) {
		block->flags |= ACTIVE_SET;
	}

	ret = accumulate_state (stylesheet, block->type_name, "prelight",
				&block->colors[PRELIGHT], NULL);
	if (ret && block->colors[PRELIGHT].flags) {
		block->flags |= PRELIGHT_SET;
	}

	ret = accumulate_state (stylesheet, block->type_name, "selected",
				&block->colors[SELECTED], NULL);
	if (ret && block->colors[SELECTED].flags) {
		block->flags |= SELECTED_SET;
	}

	ret = accumulate_state (stylesheet, block->type_name, "insensitive",
				&block->colors[INSENSITIVE], NULL);
	if (ret && block->colors[INSENSITIVE].flags) {
		block->flags |= INSENSITIVE_SET;
	}

	return (bool) block->flags;
}

static void
serialize_state (struct RcState const	*state,
		 char const		*state_name,
		 GString		*rc_string)
{
	if (FG_SET & state->flags) {
		g_string_append_printf (rc_string, "\tfg[%s] = '%s'\n", state_name, state->fg);
	}

	if (BG_SET & state->flags) {
		g_string_append_printf (rc_string, "\tbg[%s] = '%s'\n", state_name, state->bg);
	}

	if (BASE_SET & state->flags) {
		g_string_append_printf (rc_string, "\tbase[%s] = '%s'\n", state_name, state->base);
	}

	if (TEXT_SET & state->flags) {
		g_string_append_printf (rc_string, "\ttext[%s] = '%s'\n", state_name, state->text);
	}
}

static gboolean
serialize (struct RcBlock const	*block,
	   GString		*rc_string)
{
	GString		*colors;
	GSList const	*iter;
	char		*style;
	char		*style_name;
	char const      *rc_selector;

	if (strlen (block->type_name) > 3 &&
	    0 == strncmp ("Gtk", block->type_name, 3)) {
		style = g_ascii_strdown (block->type_name + 3, -1);
	} else if (0 == strcmp ("*", block->type_name)) {
		style = g_strdup ("default");
	} else {
		return false;
	}

	style_name = g_strdup_printf ("gce-%s", style);
	g_free (style), style = NULL;

	g_string_append_printf (rc_string, "style \"%s\" {\n", style_name);

	/* Colors. */
	colors = g_string_new (NULL);
	if (NORMAL_SET & block->flags) {
		serialize_state (&block->colors[NORMAL], "NORMAL", colors);
	}

	if (ACTIVE_SET & block->flags) {
		serialize_state (&block->colors[ACTIVE], "ACTIVE", colors);
	}

	if (PRELIGHT_SET & block->flags) {
		serialize_state (&block->colors[PRELIGHT], "PRELIGHT", colors);
	}

	if (SELECTED_SET & block->flags) {
		serialize_state (&block->colors[SELECTED], "SELECTED", colors);
	}

	if (INSENSITIVE_SET & block->flags) {
		serialize_state (&block->colors[INSENSITIVE], "INSENSITIVE", colors);
	}

	g_string_append (rc_string, colors->str);

	/* Style properties. */
	iter = block->style_properties;
	while (iter) {
		g_string_append_printf (rc_string, "\t%s\n", (char const *) iter->data);
		iter = iter->next;
	}

	/* Selector, for NULL widget pointer
	 * PONDERING: support complex selectors? */
	g_string_append (rc_string, "\tengine \"css\" {\n");
	g_string_append_printf (rc_string, "\t\tselector = \"%s\"\n", block->type_name);
	g_string_append (rc_string, "\t}\n");

	/* Close block. */
	g_string_append (rc_string, "}\n");

	g_string_append_printf (rc_string, "class \"%s\" style \"%s\"\n\n", block->type_name, style_name);

	/* Need to add a custom selector, i.e. apply this style to child widgets? */
	rc_selector = get_rc_selector (block->type_name);
	if (rc_selector) {
		g_string_append_printf (rc_string, "%s style \"%s\"\n\n", rc_selector, style_name);
	}

	g_string_free (colors, true);
	g_free (style_name), style_name = NULL;

	return true;
}

static void
iter_func (ccss_stylesheet_t	*stylesheet,
	   char const		*type_name,
	   GString		*rc_string)
{
	struct RcBlock	block;
	gboolean	ret;

	/* Only feed widget styles back into gtk, not primitives. */
	if (strcmp ("*", type_name) != 0 &&
	    strncmp ("Gtk", type_name, 3) != 0) {
		return;
	}

	memset (&block, 0, sizeof (block));
	block.type_name = type_name;
	ret = accumulate (stylesheet, &block);
	if (ret) {
		serialize (&block, rc_string);
	}

	/* Free style properties. */
	while (block.style_properties) {
		g_free (block.style_properties->data);
		block.style_properties = g_slist_delete_link (block.style_properties,
							      block.style_properties);
	}
}

/**
 * ccss_gtk_stylesheet_to_gtkrc:
 * @self: a #ccss_stylesheet_t.
 *
 * Convert a stylesheet to a gtkrc string. CSS and gtkrc do not match one to
 * one onto each other so this is a best effort conversion.
 *
 * Returns: a gtkrc string.
 */
char *
ccss_gtk_stylesheet_to_gtkrc (ccss_stylesheet_t *self)
{
	GString		*rc_string;
	char		*str;

	g_return_val_if_fail (self, NULL);

	rc_string = g_string_new ("");

	ccss_stylesheet_foreach (self,
				 (ccss_stylesheet_iterator_f) iter_func,
				 rc_string);

	str = rc_string->str;
	g_string_free (rc_string, false), rc_string = NULL;
	return str;
}

