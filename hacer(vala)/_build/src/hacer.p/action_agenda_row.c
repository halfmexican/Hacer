/* action_agenda_row.c generated by valac 0.56.3, the Vala compiler
 * generated from action_agenda_row.vala, do not modify */

#include <adwaita.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#if !defined(VALA_EXTERN)
#if defined(_MSC_VER)
#define VALA_EXTERN __declspec(dllexport) extern
#elif __GNUC__ >= 4
#define VALA_EXTERN __attribute__((visibility("default"))) extern
#else
#define VALA_EXTERN extern
#endif
#endif

#define HACER_TYPE_ACTION_AGENDA_ROW (hacer_action_agenda_row_get_type ())
#define HACER_ACTION_AGENDA_ROW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), HACER_TYPE_ACTION_AGENDA_ROW, HacerActionAgendaRow))
#define HACER_ACTION_AGENDA_ROW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), HACER_TYPE_ACTION_AGENDA_ROW, HacerActionAgendaRowClass))
#define HACER_IS_ACTION_AGENDA_ROW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), HACER_TYPE_ACTION_AGENDA_ROW))
#define HACER_IS_ACTION_AGENDA_ROW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), HACER_TYPE_ACTION_AGENDA_ROW))
#define HACER_ACTION_AGENDA_ROW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), HACER_TYPE_ACTION_AGENDA_ROW, HacerActionAgendaRowClass))

typedef struct _HacerActionAgendaRow HacerActionAgendaRow;
typedef struct _HacerActionAgendaRowClass HacerActionAgendaRowClass;
typedef struct _HacerActionAgendaRowPrivate HacerActionAgendaRowPrivate;
enum  {
	HACER_ACTION_AGENDA_ROW_0_PROPERTY,
	HACER_ACTION_AGENDA_ROW_NUM_PROPERTIES
};
static GParamSpec* hacer_action_agenda_row_properties[HACER_ACTION_AGENDA_ROW_NUM_PROPERTIES];
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _HacerActionAgendaRow {
	AdwActionRow parent_instance;
	HacerActionAgendaRowPrivate * priv;
};

struct _HacerActionAgendaRowClass {
	AdwActionRowClass parent_class;
};

struct _HacerActionAgendaRowPrivate {
	GtkCheckButton* check_button;
	GtkButton* trash_button;
	GtkButton* star_button;
	GtkButton* edit_button;
	GtkEditableLabel* edit_label;
	GtkListBox* parent_list_box;
	gchar* task_name;
	gboolean starred;
	gboolean completed;
};

static gint HacerActionAgendaRow_private_offset;
static gpointer hacer_action_agenda_row_parent_class = NULL;

VALA_EXTERN GType hacer_action_agenda_row_get_type (void) G_GNUC_CONST ;
G_DEFINE_AUTOPTR_CLEANUP_FUNC (HacerActionAgendaRow, g_object_unref)
VALA_EXTERN HacerActionAgendaRow* hacer_action_agenda_row_new (const gchar* task_name,
                                                   gboolean completed,
                                                   gboolean starred,
                                                   GtkListBox* parent_list_box);
VALA_EXTERN HacerActionAgendaRow* hacer_action_agenda_row_construct (GType object_type,
                                                         const gchar* task_name,
                                                         gboolean completed,
                                                         gboolean starred,
                                                         GtkListBox* parent_list_box);
VALA_EXTERN void hacer_action_agenda_row_complete_task (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_complete_task_gtk_check_button_toggled (GtkCheckButton* _sender,
                                                                      gpointer self);
VALA_EXTERN void hacer_action_agenda_row_check_selection (HacerActionAgendaRow* self,
                                              GtkListBoxRow* row);
static void _hacer_action_agenda_row_check_selection_gtk_list_box_row_activated (GtkListBox* _sender,
                                                                          GtkListBoxRow* row,
                                                                          gpointer self);
VALA_EXTERN void hacer_action_agenda_row_show_edit_button (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_show_edit_button_adw_action_row_activated (AdwActionRow* _sender,
                                                                         gpointer self);
VALA_EXTERN void hacer_action_agenda_row_remove_task (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_remove_task_gtk_button_clicked (GtkButton* _sender,
                                                              gpointer self);
VALA_EXTERN void hacer_action_agenda_row_star_task (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_star_task_gtk_button_clicked (GtkButton* _sender,
                                                            gpointer self);
VALA_EXTERN void hacer_action_agenda_row_show_editable_label (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_show_editable_label_gtk_button_clicked (GtkButton* _sender,
                                                                      gpointer self);
VALA_EXTERN void hacer_action_agenda_row_change_task_name (HacerActionAgendaRow* self);
static void _hacer_action_agenda_row_change_task_name_gtk_text_activate (GtkText* _sender,
                                                                  gpointer self);
VALA_EXTERN void hacer_action_agenda_row_strikethrough (HacerActionAgendaRow* self);
static void hacer_action_agenda_row_finalize (GObject * obj);
static GType hacer_action_agenda_row_get_type_once (void);

static inline gpointer
hacer_action_agenda_row_get_instance_private (HacerActionAgendaRow* self)
{
	return G_STRUCT_MEMBER_P (self, HacerActionAgendaRow_private_offset);
}

static gpointer
_g_object_ref0 (gpointer self)
{
#line 20 "../src/action_agenda_row.vala"
	return self ? g_object_ref (self) : NULL;
#line 113 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_complete_task_gtk_check_button_toggled (GtkCheckButton* _sender,
                                                                 gpointer self)
{
#line 27 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_complete_task ((HacerActionAgendaRow*) self);
#line 122 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_check_selection_gtk_list_box_row_activated (GtkListBox* _sender,
                                                                     GtkListBoxRow* row,
                                                                     gpointer self)
{
#line 28 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_check_selection ((HacerActionAgendaRow*) self, row);
#line 132 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_show_edit_button_adw_action_row_activated (AdwActionRow* _sender,
                                                                    gpointer self)
{
#line 29 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_show_edit_button ((HacerActionAgendaRow*) self);
#line 141 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_remove_task_gtk_button_clicked (GtkButton* _sender,
                                                         gpointer self)
{
#line 30 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_remove_task ((HacerActionAgendaRow*) self);
#line 150 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_star_task_gtk_button_clicked (GtkButton* _sender,
                                                       gpointer self)
{
#line 31 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_star_task ((HacerActionAgendaRow*) self);
#line 159 "action_agenda_row.c"
}

static void
_hacer_action_agenda_row_show_editable_label_gtk_button_clicked (GtkButton* _sender,
                                                                 gpointer self)
{
#line 32 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_show_editable_label ((HacerActionAgendaRow*) self);
#line 168 "action_agenda_row.c"
}

HacerActionAgendaRow*
hacer_action_agenda_row_construct (GType object_type,
                                   const gchar* task_name,
                                   gboolean completed,
                                   gboolean starred,
                                   GtkListBox* parent_list_box)
{
	HacerActionAgendaRow * self = NULL;
	GtkListBox* _tmp0_;
	gchar* _tmp1_;
	GtkCheckButton* _tmp2_;
	GtkButton* _tmp3_;
	GtkButton* _tmp4_;
	GtkButton* _tmp5_;
#line 17 "../src/action_agenda_row.vala"
	g_return_val_if_fail (task_name != NULL, NULL);
#line 17 "../src/action_agenda_row.vala"
	g_return_val_if_fail (parent_list_box != NULL, NULL);
#line 17 "../src/action_agenda_row.vala"
	self = (HacerActionAgendaRow*) g_object_new (object_type, NULL);
#line 20 "../src/action_agenda_row.vala"
	_tmp0_ = _g_object_ref0 (parent_list_box);
#line 20 "../src/action_agenda_row.vala"
	_g_object_unref0 (self->priv->parent_list_box);
#line 20 "../src/action_agenda_row.vala"
	self->priv->parent_list_box = _tmp0_;
#line 21 "../src/action_agenda_row.vala"
	_tmp1_ = g_strdup (task_name);
#line 21 "../src/action_agenda_row.vala"
	_g_free0 (self->priv->task_name);
#line 21 "../src/action_agenda_row.vala"
	self->priv->task_name = _tmp1_;
#line 22 "../src/action_agenda_row.vala"
	adw_preferences_row_set_title ((AdwPreferencesRow*) self, task_name);
#line 23 "../src/action_agenda_row.vala"
	self->priv->starred = starred;
#line 24 "../src/action_agenda_row.vala"
	self->priv->completed = completed;
#line 27 "../src/action_agenda_row.vala"
	_tmp2_ = self->priv->check_button;
#line 27 "../src/action_agenda_row.vala"
	g_signal_connect_object (_tmp2_, "toggled", (GCallback) _hacer_action_agenda_row_complete_task_gtk_check_button_toggled, self, 0);
#line 28 "../src/action_agenda_row.vala"
	g_signal_connect_object (parent_list_box, "row-activated", (GCallback) _hacer_action_agenda_row_check_selection_gtk_list_box_row_activated, self, 0);
#line 29 "../src/action_agenda_row.vala"
	g_signal_connect_object ((AdwActionRow*) self, "activated", (GCallback) _hacer_action_agenda_row_show_edit_button_adw_action_row_activated, self, 0);
#line 30 "../src/action_agenda_row.vala"
	_tmp3_ = self->priv->trash_button;
#line 30 "../src/action_agenda_row.vala"
	g_signal_connect_object (_tmp3_, "clicked", (GCallback) _hacer_action_agenda_row_remove_task_gtk_button_clicked, self, 0);
#line 31 "../src/action_agenda_row.vala"
	_tmp4_ = self->priv->star_button;
#line 31 "../src/action_agenda_row.vala"
	g_signal_connect_object (_tmp4_, "clicked", (GCallback) _hacer_action_agenda_row_star_task_gtk_button_clicked, self, 0);
#line 32 "../src/action_agenda_row.vala"
	_tmp5_ = self->priv->edit_button;
#line 32 "../src/action_agenda_row.vala"
	g_signal_connect_object (_tmp5_, "clicked", (GCallback) _hacer_action_agenda_row_show_editable_label_gtk_button_clicked, self, 0);
#line 17 "../src/action_agenda_row.vala"
	return self;
#line 231 "action_agenda_row.c"
}

HacerActionAgendaRow*
hacer_action_agenda_row_new (const gchar* task_name,
                             gboolean completed,
                             gboolean starred,
                             GtkListBox* parent_list_box)
{
#line 17 "../src/action_agenda_row.vala"
	return hacer_action_agenda_row_construct (HACER_TYPE_ACTION_AGENDA_ROW, task_name, completed, starred, parent_list_box);
#line 242 "action_agenda_row.c"
}

void
hacer_action_agenda_row_check_selection (HacerActionAgendaRow* self,
                                         GtkListBoxRow* row)
{
#line 35 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 36 "../src/action_agenda_row.vala"
	if (row != G_TYPE_CHECK_INSTANCE_CAST (self, gtk_list_box_row_get_type (), GtkListBoxRow)) {
#line 253 "action_agenda_row.c"
		GtkButton* _tmp0_;
#line 37 "../src/action_agenda_row.vala"
		_tmp0_ = self->priv->edit_button;
#line 37 "../src/action_agenda_row.vala"
		gtk_widget_hide ((GtkWidget*) _tmp0_);
#line 259 "action_agenda_row.c"
	}
}

void
hacer_action_agenda_row_remove_task (HacerActionAgendaRow* self)
{
	GtkListBox* task_list = NULL;
	GtkWidget* _tmp0_;
	GtkListBox* _tmp1_;
#line 41 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 42 "../src/action_agenda_row.vala"
	_tmp0_ = gtk_widget_get_parent ((GtkWidget*) self);
#line 42 "../src/action_agenda_row.vala"
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp0_, gtk_list_box_get_type ()) ? ((GtkListBox*) _tmp0_) : NULL);
#line 42 "../src/action_agenda_row.vala"
	task_list = _tmp1_;
#line 43 "../src/action_agenda_row.vala"
	gtk_list_box_remove (task_list, (GtkWidget*) self);
#line 41 "../src/action_agenda_row.vala"
	_g_object_unref0 (task_list);
#line 281 "action_agenda_row.c"
}

void
hacer_action_agenda_row_star_task (HacerActionAgendaRow* self)
{
#line 46 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 47 "../src/action_agenda_row.vala"
	if (!self->priv->starred) {
#line 291 "action_agenda_row.c"
		GtkButton* _tmp0_;
		GtkButton* _tmp1_;
#line 48 "../src/action_agenda_row.vala"
		_tmp0_ = self->priv->star_button;
#line 48 "../src/action_agenda_row.vala"
		gtk_button_set_icon_name (_tmp0_, "starred-symbolic");
#line 49 "../src/action_agenda_row.vala"
		_tmp1_ = self->priv->star_button;
#line 49 "../src/action_agenda_row.vala"
		gtk_widget_add_css_class ((GtkWidget*) _tmp1_, "suggested-action");
#line 50 "../src/action_agenda_row.vala"
		self->priv->starred = TRUE;
#line 304 "action_agenda_row.c"
	} else {
		GtkButton* _tmp2_;
		GtkButton* _tmp3_;
#line 52 "../src/action_agenda_row.vala"
		_tmp2_ = self->priv->star_button;
#line 52 "../src/action_agenda_row.vala"
		gtk_button_set_icon_name (_tmp2_, "non-starred-symbolic");
#line 53 "../src/action_agenda_row.vala"
		_tmp3_ = self->priv->star_button;
#line 53 "../src/action_agenda_row.vala"
		gtk_widget_remove_css_class ((GtkWidget*) _tmp3_, "suggested-action");
#line 54 "../src/action_agenda_row.vala"
		self->priv->starred = FALSE;
#line 318 "action_agenda_row.c"
	}
}

void
hacer_action_agenda_row_show_edit_button (HacerActionAgendaRow* self)
{
	GtkButton* _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
#line 58 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 60 "../src/action_agenda_row.vala"
	_tmp0_ = self->priv->edit_button;
#line 60 "../src/action_agenda_row.vala"
	_tmp1_ = gtk_widget_get_visible ((GtkWidget*) _tmp0_);
#line 60 "../src/action_agenda_row.vala"
	_tmp2_ = _tmp1_;
#line 60 "../src/action_agenda_row.vala"
	if (!_tmp2_) {
#line 338 "action_agenda_row.c"
		GtkButton* _tmp3_;
#line 61 "../src/action_agenda_row.vala"
		_tmp3_ = self->priv->edit_button;
#line 61 "../src/action_agenda_row.vala"
		gtk_widget_show ((GtkWidget*) _tmp3_);
#line 344 "action_agenda_row.c"
	} else {
		GtkButton* _tmp4_;
#line 64 "../src/action_agenda_row.vala"
		_tmp4_ = self->priv->edit_button;
#line 64 "../src/action_agenda_row.vala"
		gtk_widget_hide ((GtkWidget*) _tmp4_);
#line 351 "action_agenda_row.c"
	}
}

static void
_hacer_action_agenda_row_change_task_name_gtk_text_activate (GtkText* _sender,
                                                             gpointer self)
{
#line 77 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_change_task_name ((HacerActionAgendaRow*) self);
#line 361 "action_agenda_row.c"
}

void
hacer_action_agenda_row_show_editable_label (HacerActionAgendaRow* self)
{
	GtkEditableLabel* _tmp0_;
	const gchar* _tmp1_;
	GtkEditableLabel* _tmp2_;
	GtkEditableLabel* _tmp3_;
	GtkEditableLabel* _tmp4_;
	GtkText* gtk_text = NULL;
	GtkEditableLabel* _tmp5_;
	GtkEditable* _tmp6_;
	GtkText* _tmp7_;
#line 68 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 69 "../src/action_agenda_row.vala"
	adw_preferences_row_set_title ((AdwPreferencesRow*) self, " ");
#line 70 "../src/action_agenda_row.vala"
	_tmp0_ = self->priv->edit_label;
#line 70 "../src/action_agenda_row.vala"
	_tmp1_ = self->priv->task_name;
#line 70 "../src/action_agenda_row.vala"
	gtk_editable_set_text ((GtkEditable*) _tmp0_, _tmp1_);
#line 71 "../src/action_agenda_row.vala"
	_tmp2_ = self->priv->edit_label;
#line 71 "../src/action_agenda_row.vala"
	gtk_widget_show ((GtkWidget*) _tmp2_);
#line 72 "../src/action_agenda_row.vala"
	_tmp3_ = self->priv->edit_label;
#line 72 "../src/action_agenda_row.vala"
	gtk_widget_grab_focus ((GtkWidget*) _tmp3_);
#line 73 "../src/action_agenda_row.vala"
	_tmp4_ = self->priv->edit_label;
#line 73 "../src/action_agenda_row.vala"
	gtk_editable_label_start_editing (_tmp4_);
#line 76 "../src/action_agenda_row.vala"
	_tmp5_ = self->priv->edit_label;
#line 76 "../src/action_agenda_row.vala"
	_tmp6_ = gtk_editable_get_delegate ((GtkEditable*) _tmp5_);
#line 76 "../src/action_agenda_row.vala"
	_tmp7_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp6_, gtk_text_get_type ()) ? ((GtkText*) _tmp6_) : NULL);
#line 76 "../src/action_agenda_row.vala"
	gtk_text = _tmp7_;
#line 77 "../src/action_agenda_row.vala"
	g_signal_connect_object (gtk_text, "activate", (GCallback) _hacer_action_agenda_row_change_task_name_gtk_text_activate, self, 0);
#line 68 "../src/action_agenda_row.vala"
	_g_object_unref0 (gtk_text);
#line 410 "action_agenda_row.c"
}

void
hacer_action_agenda_row_complete_task (HacerActionAgendaRow* self)
{
	GtkEditableLabel* _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	GtkCheckButton* _tmp5_;
#line 81 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 84 "../src/action_agenda_row.vala"
	_tmp0_ = self->priv->edit_label;
#line 84 "../src/action_agenda_row.vala"
	_tmp1_ = gtk_widget_get_visible ((GtkWidget*) _tmp0_);
#line 84 "../src/action_agenda_row.vala"
	_tmp2_ = _tmp1_;
#line 84 "../src/action_agenda_row.vala"
	if (_tmp2_) {
#line 430 "action_agenda_row.c"
		GtkEditableLabel* _tmp3_;
		const gchar* _tmp4_;
#line 85 "../src/action_agenda_row.vala"
		_tmp3_ = self->priv->edit_label;
#line 85 "../src/action_agenda_row.vala"
		gtk_widget_hide ((GtkWidget*) _tmp3_);
#line 86 "../src/action_agenda_row.vala"
		_tmp4_ = self->priv->task_name;
#line 86 "../src/action_agenda_row.vala"
		adw_preferences_row_set_title ((AdwPreferencesRow*) self, _tmp4_);
#line 87 "../src/action_agenda_row.vala"
		hacer_action_agenda_row_strikethrough (self);
#line 88 "../src/action_agenda_row.vala"
		return;
#line 445 "action_agenda_row.c"
	}
#line 91 "../src/action_agenda_row.vala"
	_tmp5_ = self->priv->check_button;
#line 91 "../src/action_agenda_row.vala"
	if (!gtk_check_button_get_active (_tmp5_)) {
#line 451 "action_agenda_row.c"
		const gchar* _tmp6_;
#line 92 "../src/action_agenda_row.vala"
		_tmp6_ = self->priv->task_name;
#line 92 "../src/action_agenda_row.vala"
		adw_preferences_row_set_title ((AdwPreferencesRow*) self, _tmp6_);
#line 457 "action_agenda_row.c"
	} else {
#line 94 "../src/action_agenda_row.vala"
		hacer_action_agenda_row_strikethrough (self);
#line 95 "../src/action_agenda_row.vala"
		self->priv->completed = TRUE;
#line 463 "action_agenda_row.c"
	}
}

void
hacer_action_agenda_row_change_task_name (HacerActionAgendaRow* self)
{
	GtkEditableLabel* _tmp0_;
	GtkButton* _tmp1_;
	GtkEditableLabel* _tmp2_;
	const gchar* _tmp3_;
	gchar* _tmp4_;
	GtkCheckButton* _tmp5_;
#line 99 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 100 "../src/action_agenda_row.vala"
	_tmp0_ = self->priv->edit_label;
#line 100 "../src/action_agenda_row.vala"
	gtk_widget_hide ((GtkWidget*) _tmp0_);
#line 101 "../src/action_agenda_row.vala"
	_tmp1_ = self->priv->edit_button;
#line 101 "../src/action_agenda_row.vala"
	gtk_widget_hide ((GtkWidget*) _tmp1_);
#line 102 "../src/action_agenda_row.vala"
	_tmp2_ = self->priv->edit_label;
#line 102 "../src/action_agenda_row.vala"
	_tmp3_ = gtk_editable_get_text ((GtkEditable*) _tmp2_);
#line 102 "../src/action_agenda_row.vala"
	_tmp4_ = g_strdup (_tmp3_);
#line 102 "../src/action_agenda_row.vala"
	_g_free0 (self->priv->task_name);
#line 102 "../src/action_agenda_row.vala"
	self->priv->task_name = _tmp4_;
#line 104 "../src/action_agenda_row.vala"
	_tmp5_ = self->priv->check_button;
#line 104 "../src/action_agenda_row.vala"
	if (!gtk_check_button_get_active (_tmp5_)) {
#line 500 "action_agenda_row.c"
		const gchar* _tmp6_;
#line 105 "../src/action_agenda_row.vala"
		_tmp6_ = self->priv->task_name;
#line 105 "../src/action_agenda_row.vala"
		adw_preferences_row_set_title ((AdwPreferencesRow*) self, _tmp6_);
#line 506 "action_agenda_row.c"
	} else {
		const gchar* _tmp7_;
#line 107 "../src/action_agenda_row.vala"
		_tmp7_ = self->priv->task_name;
#line 107 "../src/action_agenda_row.vala"
		adw_preferences_row_set_title ((AdwPreferencesRow*) self, _tmp7_);
#line 108 "../src/action_agenda_row.vala"
		hacer_action_agenda_row_strikethrough (self);
#line 515 "action_agenda_row.c"
	}
}

void
hacer_action_agenda_row_strikethrough (HacerActionAgendaRow* self)
{
	const gchar* _tmp0_;
	gchar* _tmp1_;
	gchar* _tmp2_;
	gchar* _tmp3_;
	gchar* _tmp4_;
#line 112 "../src/action_agenda_row.vala"
	g_return_if_fail (self != NULL);
#line 113 "../src/action_agenda_row.vala"
	_tmp0_ = self->priv->task_name;
#line 113 "../src/action_agenda_row.vala"
	_tmp1_ = g_strconcat ("<s>", _tmp0_, NULL);
#line 113 "../src/action_agenda_row.vala"
	_tmp2_ = _tmp1_;
#line 113 "../src/action_agenda_row.vala"
	_tmp3_ = g_strconcat (_tmp2_, "</s>", NULL);
#line 113 "../src/action_agenda_row.vala"
	_tmp4_ = _tmp3_;
#line 113 "../src/action_agenda_row.vala"
	adw_preferences_row_set_title ((AdwPreferencesRow*) self, _tmp4_);
#line 113 "../src/action_agenda_row.vala"
	_g_free0 (_tmp4_);
#line 113 "../src/action_agenda_row.vala"
	_g_free0 (_tmp2_);
#line 545 "action_agenda_row.c"
}

static void
hacer_action_agenda_row_class_init (HacerActionAgendaRowClass * klass,
                                    gpointer klass_data)
{
#line 4 "../src/action_agenda_row.vala"
	hacer_action_agenda_row_parent_class = g_type_class_peek_parent (klass);
#line 4 "../src/action_agenda_row.vala"
	g_type_class_adjust_private_offset (klass, &HacerActionAgendaRow_private_offset);
#line 4 "../src/action_agenda_row.vala"
	G_OBJECT_CLASS (klass)->finalize = hacer_action_agenda_row_finalize;
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/com/github/halfmexican/hacer/agenda_row.ui");
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "check_button", FALSE, HacerActionAgendaRow_private_offset + G_STRUCT_OFFSET (HacerActionAgendaRowPrivate, check_button));
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "trash_button", FALSE, HacerActionAgendaRow_private_offset + G_STRUCT_OFFSET (HacerActionAgendaRowPrivate, trash_button));
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "star_button", FALSE, HacerActionAgendaRow_private_offset + G_STRUCT_OFFSET (HacerActionAgendaRowPrivate, star_button));
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "edit_button", FALSE, HacerActionAgendaRow_private_offset + G_STRUCT_OFFSET (HacerActionAgendaRowPrivate, edit_button));
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "edit_label", FALSE, HacerActionAgendaRow_private_offset + G_STRUCT_OFFSET (HacerActionAgendaRowPrivate, edit_label));
#line 570 "action_agenda_row.c"
}

static void
hacer_action_agenda_row_instance_init (HacerActionAgendaRow * self,
                                       gpointer klass)
{
#line 4 "../src/action_agenda_row.vala"
	self->priv = hacer_action_agenda_row_get_instance_private (self);
#line 4 "../src/action_agenda_row.vala"
	gtk_widget_init_template (GTK_WIDGET (self));
#line 581 "action_agenda_row.c"
}

static void
hacer_action_agenda_row_finalize (GObject * obj)
{
	HacerActionAgendaRow * self;
#line 4 "../src/action_agenda_row.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, HACER_TYPE_ACTION_AGENDA_ROW, HacerActionAgendaRow);
#line 11 "../src/action_agenda_row.vala"
	_g_object_unref0 (self->priv->parent_list_box);
#line 12 "../src/action_agenda_row.vala"
	_g_free0 (self->priv->task_name);
#line 4 "../src/action_agenda_row.vala"
	G_OBJECT_CLASS (hacer_action_agenda_row_parent_class)->finalize (obj);
#line 596 "action_agenda_row.c"
}

static GType
hacer_action_agenda_row_get_type_once (void)
{
	static const GTypeInfo g_define_type_info = { sizeof (HacerActionAgendaRowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) hacer_action_agenda_row_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (HacerActionAgendaRow), 0, (GInstanceInitFunc) hacer_action_agenda_row_instance_init, NULL };
	GType hacer_action_agenda_row_type_id;
	hacer_action_agenda_row_type_id = g_type_register_static (adw_action_row_get_type (), "HacerActionAgendaRow", &g_define_type_info, 0);
	HacerActionAgendaRow_private_offset = g_type_add_instance_private (hacer_action_agenda_row_type_id, sizeof (HacerActionAgendaRowPrivate));
	return hacer_action_agenda_row_type_id;
}

GType
hacer_action_agenda_row_get_type (void)
{
	static volatile gsize hacer_action_agenda_row_type_id__once = 0;
	if (g_once_init_enter (&hacer_action_agenda_row_type_id__once)) {
		GType hacer_action_agenda_row_type_id;
		hacer_action_agenda_row_type_id = hacer_action_agenda_row_get_type_once ();
		g_once_init_leave (&hacer_action_agenda_row_type_id__once, hacer_action_agenda_row_type_id);
	}
	return hacer_action_agenda_row_type_id__once;
}

