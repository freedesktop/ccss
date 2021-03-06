/* vim: set ts=8 sw=8 noexpandtab: */

#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <ccss-cairo/ccss-cairo.h>
#include <ccss/ccss-property-impl.h>
#include <gtk/gtk.h>
#include "config.h"

static ccss_property_class_t const *
peek_property_class (void);

/*
 * Custom property implementation start.
 */

typedef struct {
	ccss_property_t	 base;
	char		*font_family;
} font_family_t;

static ccss_property_t *
font_family_new (ccss_grammar_t	*grammar,
		 CRTerm const	*values,
		 void		*user_data)
{
	font_family_t *self;

	g_return_val_if_fail (values, NULL);

	self = NULL;

	switch (values->type) {
	case TERM_IDENT:
	case TERM_STRING:
		self = g_new0 (font_family_t, 1);
		ccss_property_init ((ccss_property_t *) self, peek_property_class ());
		self->font_family = g_strdup (cr_string_peek_raw_str (values->content.str));
		break;
	default:
		/* Unhandled, fall thru. */
		;
	}

	return (ccss_property_t *) self;
}

static void
font_family_free (font_family_t *self)
{
	g_free (self->font_family);
	g_free (self);
}

static bool
font_family_convert (font_family_t const	*self,
		     ccss_property_type_t	 target,
		     void			*value)
{
	/* Only conversion to string is supported. */

	if (CCSS_PROPERTY_TYPE_STRING == target) {
		* (char **) value = g_strdup (self->font_family);
		return true;
	}

	return false;
}

static ccss_property_class_t const _properties[] = {
    {
	.name = "font-family",
	.create = (ccss_property_create_f) font_family_new,
	.destroy = (ccss_property_destroy_f) font_family_free,
	.convert = (ccss_property_convert_f) font_family_convert,
	.factory = NULL,
	.inherit = NULL,
	.serialize = NULL	
    }, {
	.name = NULL
    }
};

/*
 * Custom property implementation end.
 */

static ccss_property_class_t const *
peek_property_class (void)
{
	return &_properties[0];
}

static gboolean
expose_cb (GtkWidget		*widget,
	   GdkEventExpose	*event,
	   ccss_style_t const	*style)
{
	cairo_t			 *cr;
	ccss_property_t const	 *property;
	PangoContext		 *context;
	PangoLayout		 *layout;

	cr = gdk_cairo_create (widget->window);

	property = NULL;
	ccss_style_get_property (style, "font-family", &property);
	if (property) {
		font_family_t const *font_family = (font_family_t const *) property;
		context = gtk_widget_get_pango_context (widget);
		layout = pango_layout_new (context);
		pango_layout_set_text (layout, font_family->font_family,
				       strlen (font_family->font_family));
		pango_cairo_show_layout (cr, layout);
		g_object_unref (G_OBJECT (layout)), layout = NULL;
	}

	cairo_destroy (cr);

	return FALSE;
}

static char const _css[] = "			\
	box { 					\
		font-family: Helvetica;		\
	}					\
";

int
main (int	  argc,
      char	**argv)
{
	ccss_grammar_t		*grammar;
	ccss_stylesheet_t	*stylesheet;
	ccss_style_t		*style;
	GtkWidget		*window;
	GtkWidget		*area;

	gtk_init (&argc, &argv);

	grammar = ccss_cairo_grammar_create ();
	ccss_grammar_add_properties (grammar, _properties);
	stylesheet = ccss_grammar_create_stylesheet_from_buffer (grammar,
							_css, sizeof (_css),
							NULL);

	style = ccss_stylesheet_query_type (stylesheet, "box");
	g_assert (style);

#ifdef CCSS_DEBUG
	ccss_style_dump (style);
#endif
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 160, 90);
	g_signal_connect (G_OBJECT (window), "delete-event",
			  G_CALLBACK (gtk_main_quit), NULL);

	area = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER (window), area);
	g_signal_connect (G_OBJECT (area), "expose-event",
			  G_CALLBACK (expose_cb), style);

	gtk_widget_show_all (window);
	gtk_main ();

	ccss_style_destroy (style);
	ccss_stylesheet_destroy (stylesheet);
	ccss_grammar_destroy (grammar);

	return EXIT_SUCCESS;
}

