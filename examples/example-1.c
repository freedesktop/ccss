
#include <stdlib.h>
#include <cairo.h>
#include <ccss/ccss.h>
#include <gtk/gtk.h>

static gboolean
expose_cb (GtkWidget		*widget,
	   GdkEventExpose	*event,
	   ccss_style_t const	*style)
{
	cairo_t *cr;

	cr = gdk_cairo_create (widget->window);

	ccss_style_draw_rectangle (style, cr, 
				  widget->allocation.x + 10,
				  widget->allocation.y + 10,
				  widget->allocation.width - 20, 
				  widget->allocation.height - 20);

	cairo_destroy (cr);

	return FALSE;
}

static char const _css[] = "			\
	box { 					\
		border: 3px solid black		\
	}					\
";

int
main (int	  argc,
      char	**argv)
{
	ccss_stylesheet_t		*stylesheet;
	ccss_selector_group_t const	*group;
	ccss_style_t			 style;
	GtkWidget			*window;

	gtk_init (&argc, &argv);

	stylesheet = ccss_stylesheet_new_from_buffer (_css, sizeof (_css));
	/* stylesheet = ccss_stylesheet_new_from_file ("example-1.css"); */

	group = ccss_stylesheet_query_type (stylesheet, "box");
	g_assert (group);

	ccss_style_init (&style);
	ccss_selector_group_apply_type (group, "box", &style);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 160, 90);
	gtk_widget_set_app_paintable (window, TRUE);
	g_signal_connect (G_OBJECT (window), "delete-event", 
			  G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT (window), "expose-event", 
			  G_CALLBACK (expose_cb), &style);

	gtk_widget_show_all (window);
	gtk_main ();

	ccss_stylesheet_free (stylesheet);

	return EXIT_SUCCESS;
}

