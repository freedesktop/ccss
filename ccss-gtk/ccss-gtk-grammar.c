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

#include <math.h>
#include <string.h>
#include <gtk/gtk.h>
#include <ccss-cairo/ccss-cairo.h>
#include "ccss-gtk-grammar.h"
#include "config.h"

typedef struct {
	ccss_property_base_t	 base;
	char			*class_name;
	char			*property_name;
	GType			 gtype;
	union {
		gboolean		gboolean_val;
		gchararray		gchararray_val;
		gfloat			gfloat_val;
		gint			gint_val;
		guchar			guchar_val;
		GdkColor		gdkcolor_val;
		GtkBorder		gtkborder_val;
		GtkReliefStyle		gtkreliefstyle_val;
		GtkRequisition		gtkrequisition_val;
		GtkShadowType		gtkshadowtype_val;
		GtkToolbarSpaceStyle	gtktoolbarspacestyle_val;
	} content;
} ccss_gtk_property_t;

static ccss_property_class_t const *
peek_property_class (void);

static ccss_property_class_t const *_generic_property_class = NULL;

static bool
parse_gboolean (CRTerm const		*values,
		ccss_gtk_property_t	*property)
{
	char const	*str;
	bool		 ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		ret = true;
		str = cr_string_peek_raw_str (values->content.str);
		if (0 == g_ascii_strcasecmp ("true", str))
			property->content.gboolean_val = true;
		else if (0 == g_ascii_strcasecmp ("false", str))
			property->content.gboolean_val = false;
		else
			ret = false;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gchararray (CRTerm const		*values,
		  ccss_gtk_property_t	*property)
{
	char const	*str;
	bool		 ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		str = cr_string_peek_raw_str (values->content.str);
		property->content.gchararray_val = g_strdup (str);
		ret = true;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gfloat (CRTerm const		*values,
	      ccss_gtk_property_t	*property)
{
	bool ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_NUMBER:
		property->content.gfloat_val = values->content.num->val;
		ret = true;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gint (CRTerm const	*values,
	    ccss_gtk_property_t	*property)
{
	bool ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_NUMBER:
		/* Be strict about fractionals. */
		if (lround (values->content.num->val) == values->content.num->val) {
			property->content.gint_val = (int) values->content.num->val;
			ret = true;
		}
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_guchar (CRTerm const		*values,
	      ccss_gtk_property_t	*property)
{
	bool ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_NUMBER:
		/* Be strict about fractionals. */
		if (lround (values->content.num->val) == values->content.num->val) {
			if (values->content.num->val > G_MAXUINT8)
				property->content.guchar_val = G_MAXUINT8;
			else if (values->content.num->val < 0)
				property->content.guchar_val = 0;
			else
				property->content.guchar_val = (guchar) values->content.num->val;
			ret = true;
		}
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gdk_color (ccss_grammar_t const	*grammar,
		 CRTerm const		*values,
		 void			*user_data,
		 ccss_gtk_property_t	*property)
{
	ccss_cairo_color_t	color;
	bool			ret;

	g_return_val_if_fail (values && property, false);

	memset (&color, 0, sizeof (color));
	ret = ccss_cairo_color_parse (&color, grammar, user_data, &values);
	if (ret) {
		property->content.gdkcolor_val.red = color.red * 65535;
		property->content.gdkcolor_val.green = color.green * 65535;
		property->content.gdkcolor_val.blue = color.blue * 65535;
	}

	return ret;
}

static bool
parse_gtk_border (CRTerm const		*values,
		  ccss_gtk_property_t	*property)
{
	gint		 *border_ptr;
	int		  i;

	g_return_val_if_fail (values && property, false);

	border_ptr = (gint *) &property->content.gtkborder_val;
	for (i = 0; i < 4; i++) {

		if (!values) {
			break;
		}
		
		/* Be strict about fractionals. */
		if (TERM_NUMBER == values->type &&
		    lround (values->content.num->val) == values->content.num->val) {

			border_ptr[i] = (gint) values->content.num->val;
			values = values->next;
		}
	}

	return i == 4;
}

static bool
parse_gtk_relief_style (CRTerm const		*values,
			ccss_gtk_property_t	*property)
{
	char const	*str;
	bool		 ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		ret = true;
		str = cr_string_peek_raw_str (values->content.str);
		if (0 == g_ascii_strcasecmp ("normal", str))
			property->content.gtkreliefstyle_val = GTK_RELIEF_NORMAL;
		else if (0 == g_ascii_strcasecmp ("half", str))
			property->content.gtkreliefstyle_val = GTK_RELIEF_HALF;
		else if (0 == g_ascii_strcasecmp ("none", str))
			property->content.gtkreliefstyle_val = GTK_RELIEF_NONE;
		else
			ret = false;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gtk_requisition (CRTerm const		*values,
		       ccss_gtk_property_t	*property)
{
	gint		 *border_ptr;
	int		  i;

	g_return_val_if_fail (values && property, false);

	border_ptr = (gint *) &property->content.gtkrequisition_val;
	for (i = 0; i < 2; i++) {

		if (!values) {
			break;
		}
		
		/* Be strict about fractionals. */
		if (TERM_NUMBER == values->type &&
		    lround (values->content.num->val) == values->content.num->val) {

			border_ptr[i] = (gint) values->content.num->val;
			values = values->next;
		}
	}

	return i == 2;
}

static bool
parse_gtk_shadow_type (CRTerm const		*values,
		       ccss_gtk_property_t	*property)
{
	char const	*str;
	bool		 ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		ret = true;
		str = cr_string_peek_raw_str (values->content.str);
		if (0 == g_ascii_strcasecmp ("none", str))
			property->content.gtkshadowtype_val = GTK_SHADOW_NONE;
		else if (0 == g_ascii_strcasecmp ("in", str))
			property->content.gtkreliefstyle_val = GTK_SHADOW_IN;
		else if (0 == g_ascii_strcasecmp ("out", str))
			property->content.gtkreliefstyle_val = GTK_SHADOW_OUT;
		else if (0 == g_ascii_strcasecmp ("etched-in", str))
			property->content.gtkreliefstyle_val = GTK_SHADOW_ETCHED_IN;
		else if (0 == g_ascii_strcasecmp ("etched-out", str))
			property->content.gtkreliefstyle_val = GTK_SHADOW_ETCHED_OUT;
		else
			ret = false;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static bool
parse_gtk_toolbar_space_style (CRTerm const		*values,
			       ccss_gtk_property_t	*property)
{
	char const	*str;
	bool		 ret;

	g_return_val_if_fail (values && property, false);

	ret = false;
	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		ret = true;
		str = cr_string_peek_raw_str (values->content.str);
		if (0 == g_ascii_strcasecmp ("empty", str))
			property->content.gtktoolbarspacestyle_val = GTK_TOOLBAR_SPACE_EMPTY;
		else if (0 == g_ascii_strcasecmp ("line", str))
			property->content.gtktoolbarspacestyle_val = GTK_TOOLBAR_SPACE_LINE;
		else
			ret = false;
		break;
	default:
		/* Shut up compiler. */
		ret = false;
	}

	return ret;
}

static ccss_gtk_property_t *
parse_gtk_style_property (ccss_grammar_t const	*grammar,
			  char const		*name,
			  CRTerm const		*values,
			  void			*user_data)
{
	char			**tokens;
	char			 *class_name = NULL;
	char			 *property_name = NULL;
	GtkBuilder		 *builder = NULL;
	GType			  type = 0;
	GtkWidget		 *widget = NULL;
	GParamSpec		 *property = NULL;
	ccss_gtk_property_t	 *self = NULL, s;

	/* Parse property name. */
	tokens = g_strsplit (name, "-", 2);
	if (tokens && tokens[0]) {
		class_name = tokens[0];
	} else {
		goto bail;
	}
	if (tokens && tokens[1]) {
		property_name = tokens[1];
	} else {
		goto bail;
	}

	/* Introspect property type. */
	builder = gtk_builder_new ();
	type = gtk_builder_get_type_from_name (builder, class_name);
	if (0 == type)
		goto bail;

	widget = GTK_WIDGET (g_object_new (type, NULL));
	if (NULL == widget)
		goto bail;

	property = gtk_widget_class_find_style_property (GTK_WIDGET_GET_CLASS (widget),
							 property_name);
	if (NULL == property)
		goto bail;

	/* Parse value. */
	memset (&s, 0, sizeof (s));
	ccss_property_init (&self->base, peek_property_class ());
	if (G_TYPE_BOOLEAN == property->value_type) {
		if (parse_gboolean (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (G_TYPE_STRING == property->value_type) {
		if (parse_gchararray (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (G_TYPE_FLOAT == property->value_type) {
		if (parse_gfloat (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (G_TYPE_INT == property->value_type) {
		if (parse_gint (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (G_TYPE_UCHAR == property->value_type) {
		if (parse_guchar (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GDK_TYPE_COLOR == property->value_type) {
		if (parse_gdk_color (grammar, values, user_data, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GTK_TYPE_BORDER == property->value_type) {
		if (parse_gtk_border (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GTK_TYPE_RELIEF_STYLE == property->value_type) {
		if (parse_gtk_relief_style (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GTK_TYPE_REQUISITION == property->value_type) {
		if (parse_gtk_requisition (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GTK_TYPE_SHADOW_TYPE == property->value_type) {
		if (parse_gtk_shadow_type (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else if (GTK_TYPE_TOOLBAR_SPACE_STYLE == property->value_type) {
		if (parse_gtk_toolbar_space_style (values, &s)) {
			s.gtype = property->value_type;
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
		}
	} else {
		g_assert_not_reached ();
	}

	if (self) {
		self->class_name = class_name, class_name = NULL;
		self->property_name = property_name, property_name = NULL;
	}

bail:
	if (tokens)
		g_free (tokens);
	if (class_name)
		g_free (class_name);
	if (property_name)
		g_free (property_name);
	if (builder)
		g_object_unref (G_OBJECT (builder));
	if (widget)
		gtk_widget_destroy (widget);

	return self;
}

static void 
property_destroy (ccss_gtk_property_t *self)
{
	g_return_if_fail (self);

	if (G_TYPE_STRING == self->gtype && self->content.gchararray_val) {
		g_free (self->content.gchararray_val);
	}
	g_free (self);
}

static bool
property_convert (ccss_gtk_property_t const	*self,
		  ccss_property_type_t		 target,
		  void				*value)
{
	char *prefix;

	g_return_val_if_fail (self, false);
	g_return_val_if_fail (value, false);

	if (CCSS_PROPERTY_TYPE_DOUBLE == target) {
		return false;
	}

	if (self->class_name) {
		prefix = g_strdup_printf ("%s::", self->class_name);
	} else {
		prefix = g_strdup ("");
	}

	if (G_TYPE_BOOLEAN == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = %s", 
						     prefix, self->property_name,
						     self->content.gboolean_val ? 
						     "TRUE" : "FALSE");
	} else if (G_TYPE_STRING == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = \"%s\"", 
						     prefix, self->property_name,
						     self->content.gchararray_val);
	} else if (G_TYPE_FLOAT == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = %f", 
						     prefix, self->property_name,
						     self->content.gfloat_val);
	} else if (G_TYPE_INT == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = %d", 
						     prefix, self->property_name,
						     self->content.gint_val);
	} else if (G_TYPE_UCHAR == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = %d", 
						     prefix, self->property_name,
						     self->content.guchar_val);
	} else if (GDK_TYPE_COLOR == self->gtype) {
		char *val;
		val = gdk_color_to_string (&self->content.gdkcolor_val);
		* (char **) value = g_strdup_printf ("%s%s = %s", 
						     prefix, self->property_name,
						     val);
		g_free (val);
	} else if (GTK_TYPE_BORDER == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = { %d, %d, %d, %d }", 
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
		* (char **) value = g_strdup_printf ("%s%s = %s", 
						     prefix, self->property_name,
						     val);
	} else if (GTK_TYPE_REQUISITION == self->gtype) {
		* (char **) value = g_strdup_printf ("%s%s = { %d, %d }", 
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
		* (char **) value = g_strdup_printf ("%s%s = %s", 
						     prefix, self->property_name,
						     val);
	} else if (GTK_TYPE_TOOLBAR_SPACE_STYLE == self->gtype) {
		char const *val;
		val = self->content.gtktoolbarspacestyle_val == GTK_TOOLBAR_SPACE_EMPTY ? "EMPTY" :
		      self->content.gtktoolbarspacestyle_val == GTK_TOOLBAR_SPACE_LINE ? "LINE" : "";
		* (char **) value = g_strdup_printf ("%s%s = %s",
						     prefix, self->property_name,
						     val);
	} else {
		g_assert_not_reached ();
	}

	g_free (prefix), prefix = NULL;
	return true;
}

static bool
property_factory (ccss_grammar_t const	*grammar,
		  ccss_block_t		*block,
		  char const		*name,
		  CRTerm const		*values,
		  void			*user_data)
{
	ccss_gtk_property_t s, *self;

	g_return_val_if_fail (grammar, false);
	g_return_val_if_fail (block, false);
	g_return_val_if_fail (name, false);
	g_return_val_if_fail (values, false);

	/* PONDERING: Handle things like GtkSettings `gtk-button-images' in the future? */

	memset (&s, 0, sizeof (s));
	ccss_property_init (&self->base, peek_property_class ());

	if (0 == g_strcmp0 (name, "xthickness")) {
		if (parse_gint (values, &s)) {
			s.class_name = NULL;
			s.property_name = g_strdup ("xthickness");
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
			ccss_block_add_property (block, "xthickness", &self->base);
			return true;
		}
	} else if (0 == g_strcmp0 (name, "ythickness")) {
		if (parse_gint (values, &s)) {
			s.class_name = NULL;
			s.property_name = g_strdup ("ythickness");
			self = g_new0 (ccss_gtk_property_t, 1);
			*self = s;
			ccss_block_add_property (block, "ythickness", &self->base);
			return true;
		}
	} else if (g_str_has_prefix (name, "Gtk")) {
		self = parse_gtk_style_property (grammar, name, values, user_data);
		if (self) {
			ccss_block_add_property (block, name, &self->base);
		}
		return (bool) self;
	} else if (g_ascii_isupper (name[0])) {
		// TODO introspect style property and feed back to gtk directly.
		// Non-gtk style properties (wnck, nautilus, ...) can't be
		// resolved offline because css2gtkrc doesn't link against them.
		// May cause some breakage, let's see how it goes.
		// TODO link css2gtkrc against gtk.
	}


	/* Fall back. */
	g_return_val_if_fail (_generic_property_class, false);
	g_return_val_if_fail (_generic_property_class->property_factory, false);
	return _generic_property_class->property_factory (grammar, block, name,
							  values, user_data);
}

static ccss_property_class_t const _properties[] = {
    {
	.name = "*",
	.property_create = NULL,
	.property_destroy = (ccss_property_destroy_f) property_destroy,
	.property_convert = (ccss_property_convert_f) property_convert,
	.property_factory = property_factory,
	.property_inherit = NULL
    }, {
	.name = NULL
    }
};

static ccss_property_class_t const *
peek_property_class (void)
{
	return &_properties[0];
}

/**
 * ccss_gtk_grammar_create:
 *
 * Create a new gtk-grammar instance.
 *
 * The gtk-grammar object provides a factory to load stylesheets restricted to 
 * the supported CSS subset.
 *
 * Returns: a new #ccss_grammar_t instance.
 **/
ccss_grammar_t *
ccss_gtk_grammar_create (void)
{
	ccss_grammar_t *self;

	self = ccss_cairo_grammar_create ();

	if (NULL == _generic_property_class) {
		_generic_property_class = ccss_grammar_lookup_property (self,
									"*");
	}

	ccss_grammar_add_properties (self, _properties);

	return self;
}

