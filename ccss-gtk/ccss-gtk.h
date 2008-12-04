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

#ifndef CCSS_GTK_H
#define CCSS_GTK_H

#include <ccss-cairo/ccss-cairo.h>
#include <ccss-gtk/ccss-gtk-grammar.h>
#include <ccss-gtk/ccss-gtk-style.h>

CCSS_BEGIN_DECLS

void
ccss_gtk_init (void);

void
ccss_gtk_shutdown (void);

CCSS_END_DECLS

#endif /* CCSS_GTK_H */
