/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <widgets/viewport.h>
#include <util/logger.h>
#include <librobot.h>
#include <math.h>

static vec2 target;
static vec2 center_point;
static cairo_matrix_t transform_matrix;

static arm_joints current_joints;

static inline void recalculate_arm_points(void)
{
	// int a1 = angle_to_pulse(arm_angles[0]);
	// int a2 = middle_angle_to_pulse(arm_angles[1]);
	// int a3 = middle_angle_to_pulse(-arm_angles[2]);

	current_joints = librobot_calculate_angles(current_joints, target);
}

static inline void cairo_point(cairo_t *ctx, float x, float y)
{
	cairo_arc(ctx, x, y, 10, 0, 2 * M_PI);
}

static inline void update_transform_matrix(void)
{
	cairo_matrix_init_identity(&transform_matrix);
	cairo_matrix_translate(&transform_matrix, center_point.x, center_point.y);
	cairo_matrix_rotate(&transform_matrix, M_PI);
}

static inline void set_target_point(double x, double y)
{
	cairo_matrix_transform_point(&transform_matrix, &x, &y);

	target.x = x;
	target.y = y;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *ctx, gpointer user)
{
	cairo_set_source_rgba(ctx, 0.1, 0.1, 0, 0.6);
	cairo_set_line_width(ctx, 10.8);
	cairo_set_line_cap(ctx, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_join(ctx, CAIRO_LINE_JOIN_ROUND);

	cairo_transform(ctx, &transform_matrix);

	cairo_move_to(ctx, \
		current_joints.j1.position.x, current_joints.j1.position.y);
	cairo_line_to(ctx, \
		current_joints.j2.position.x, current_joints.j2.position.y);
	cairo_line_to(ctx, \
		current_joints.j3.position.x, current_joints.j3.position.y);
	cairo_line_to(ctx, \
		current_joints.j4.position.x, current_joints.j4.position.y);

	cairo_stroke(ctx);

	cairo_set_source_rgb(ctx, 0, 0, 0);
	cairo_set_line_width(ctx, 0.2);
	cairo_move_to(ctx, center_point.x, 0);
	cairo_line_to(ctx, -center_point.x, 0);

	cairo_stroke(ctx);

	cairo_set_source_rgba(ctx, 1.0, 0, 0, 0.2);
	cairo_point(ctx, target.x, target.y);

	cairo_fill(ctx);
	cairo_stroke(ctx);

	return FALSE;
}

static gboolean on_resize(GtkWidget *widget, GdkRectangle *size, gpointer user)
{
	center_point.x = size->width / 2;
	center_point.y = size->height / 2;

	update_transform_matrix();
	recalculate_arm_points();

	gtk_widget_queue_draw(widget);

	return FALSE;
}

static gboolean on_mouse(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{
	int x, y;
	GdkModifierType state;

	gdk_window_get_device_position(event->window, event->device, &x, &y, &state);

	if (state & GDK_BUTTON1_MASK) {
		set_target_point(x, y);

		recalculate_arm_points();
		gtk_widget_queue_draw(widget);
	}

	/* We've handled it, stop processing */
	return TRUE;
}

gboolean on_keypress(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	gboolean retval = FALSE;

	if (event->keyval == GDK_KEY_w){
		target.y -= 10.0f;
		retval = TRUE;
	}

	if (event->keyval == GDK_KEY_s){
		target.y += 10.0f;
		retval = TRUE;
	}

	if (event->keyval == GDK_KEY_a){
		target.x -= 10.0f;
		retval = TRUE;
	}

	if (event->keyval == GDK_KEY_d){
		target.x += 10.0f;
		retval = TRUE;
	}

	recalculate_arm_points();
	gtk_widget_queue_draw(widget);

	return retval;
}

GtkWidget *viewport_create(void)
{
	GtkWidget *canvas;

	canvas = gtk_drawing_area_new();

	gtk_widget_set_size_request(canvas, 100, 100);

	gtk_widget_add_events(canvas, GDK_KEY_PRESS_MASK);
	gtk_widget_add_events(canvas, GDK_BUTTON_PRESS_MASK);
	gtk_widget_add_events(canvas, GDK_POINTER_MOTION_MASK);

	gtk_widget_set_can_focus(canvas, TRUE);

	g_signal_connect(canvas, "draw", G_CALLBACK(on_draw), NULL);
	g_signal_connect(canvas, "size-allocate", G_CALLBACK(on_resize), NULL);

	g_signal_connect(canvas, "motion-notify-event", \
			G_CALLBACK(on_mouse), NULL);
	g_signal_connect(canvas, "key-press-event", \
			G_CALLBACK(on_keypress), NULL);

	librobot_init(100, 100, 100);

	return canvas;
}

