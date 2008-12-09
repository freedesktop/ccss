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

#ifndef CCSS_GTK_GRAMMAR_H
#define CCSS_GTK_GRAMMAR_H

#include <ccss/ccss.h>
#include <gtk/gtk.h>

CCSS_BEGIN_DECLS

/*  */

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

ccss_grammar_t *
ccss_gtk_grammar_create (void);

CCSS_END_DECLS

#endif /* CCSS_GTK_GRAMMAR_H */

