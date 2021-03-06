/* vim: set ts=8 sw=8 noexpandtab: */

#include <stdlib.h>
#include <cairo.h>
#include <ccss-cairo/ccss-cairo.h>
#include <gtk/gtk.h>
#include "config.h"

/*
 * ccss-cairo appearance module interface.
 */

G_MODULE_EXPORT char const *
ccss_appearance_module_get_interface_version (void);

G_MODULE_EXPORT bool
custom_box (ccss_style_t const	*self,
	    cairo_t		*cr,
	    int			 x,
	    int			 y,
	    int			 width,
	    int			 height);

G_MODULE_EXPORT char const *
ccss_appearance_module_get_interface_version (void)
{
	return CCSS_CAIRO_APPEARANCE_MODULE_INTERFACE_VERSION;
}

G_MODULE_EXPORT bool
custom_box (ccss_style_t const	*self,
	    cairo_t		*cr,
	    int			 x,
	    int			 y,
	    int			 width,
	    int			 height)
{
	cairo_rectangle (cr, x, y, width, height);
	cairo_set_line_width (cr, 3);
	cairo_set_line_cap (cr, CAIRO_LINE_JOIN_ROUND);
	cairo_stroke (cr);

	ccss_style_dump (self);

	return true;
}

/*
 * Example binary.
 */

static gboolean
expose_cb (GtkWidget		*widget,
	   GdkEventExpose	*event,
	   ccss_style_t const	*style)
{
	cairo_t *cr;

	cr = gdk_cairo_create (widget->window);

	ccss_cairo_style_draw_rectangle_with_gap (style, cr,
						  widget->allocation.x + 10,
						  widget->allocation.y + 10,
						  widget->allocation.width - 20,
						  widget->allocation.height - 20,
						  CCSS_CAIRO_GAP_SIDE_TOP,
						  10,
						  30);

	cairo_destroy (cr);

	return FALSE;
}

static char const _css[] = "				\
	box { 						\
		ccss-appearance: custom_box example-8;	\
	}						\
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

