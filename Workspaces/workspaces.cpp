#include "workspaces.h"
#include "maya.h"
#include "workspace.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QSettings>
#include <QSize>
#include <QStringList>
#include <QString>
#include <QScreen>


int Workspaces::workspace_count = 0;

Workspaces::Workspaces(QWidget *parent) : QMainWindow(parent), settings_dialog(new SettingsDialog(this))
{
    ui.setupUi(this);

	set_projects_combobox();
	load_settings();

	this->setWindowTitle("Workspaces");
}

Workspaces::~Workspaces() {}

void Workspaces::save_settings()
{
	QSettings settings("ws", "workspaces");

	settings.beginGroup("main_window_group");
	bool is_maximized = (this->windowState() & Qt::WindowMaximized) == Qt::WindowMaximized;
	settings.setValue("is_maximized", is_maximized);
	if (is_maximized) {
		QScreen* screen = this->screen();
		QRect screen_geometry = screen->geometry();
		settings.setValue("maximized_screen_geometry", screen_geometry);
	}
	if (!is_maximized){
		settings.setValue("window_size", this->size());
		settings.setValue("window_position", this->geometry());
	}
	settings.endGroup();

	settings.beginGroup("project_info");
	settings.setValue("department", get_department_index());
	settings.setValue("project", get_project_index());
	settings.endGroup();

	settings.beginGroup("settings_dialog_group");
	settings.setValue("projects_path", settings_dialog->get_project_path());
	settings.endGroup();
}

void Workspaces::load_settings()
{
	QSettings settings("ws", "workspaces");

	// main_window settings
	settings.beginGroup("main_window_group");
	bool is_maximized = settings.value("is_maximized", false).toBool();
	if (is_maximized) {
		QRect saved_geometry = settings.value("maximized_screen_geometry").toRect();
		if (!saved_geometry.isNull()) {
			this->move(saved_geometry.topLeft());
		}
		this->showMaximized();
	}
	else {
		QSize window_size = settings.value("window_size", QSize(1000, 800)).toSize();
		QRect window_position = settings.value("window_position", QRect(100, 100, 1000, 800)).toRect();
		settings.endGroup();

		this->resize(window_size);
		this->move(window_position.topLeft());
	}
	//project_info settings
	settings.beginGroup("project_info");
	int deparment_index = settings.value("department", 0).toInt();
	int project_index = settings.value("project", 0).toInt();
	settings.endGroup();

	ui.department_cbox->setCurrentIndex(deparment_index);
	ui.project_cbox->setCurrentIndex(project_index);

	//settings_dialog settings
	settings.beginGroup("settings_dialog_group");
	QString projects_path = settings.value("projects_path", "").toString();
	settings.endGroup();

	settings_dialog->set_project_path(projects_path);
}

QStringList Workspaces::get_projects()
{
	QString path = settings_dialog->get_project_path();
	QDir projects_dir(path);

	if (!projects_dir.exists()) {
		qDebug() << "Path does not exist" << path;
		return QStringList();
	}

	projects_dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

	return projects_dir.entryList();

}

void Workspaces::set_projects_combobox()
{
	ui.project_cbox->addItems(get_projects());
}

int Workspaces::get_department_index()
{
	return ui.department_cbox->currentIndex();
}

int Workspaces::get_project_index()
{
	return ui.project_cbox->currentIndex();
}

void Workspaces::on_maya_btn_clicked()
{
	int tab_index = add_tab(QString("Workspace %1").arg(workspace_count+1));
	ui.tab_widget->setCurrentIndex(tab_index);

	workspace_count += 1;
}

void Workspaces::on_unreal_btn_clicked()
{
}

int Workspaces::add_tab(QString name)
{	

	int tab_count = ui.tab_widget->count();
	qDebug() << "Tab count:" << tab_count;

	WorkSpace* workspace = new WorkSpace(this);

	int tab_index = ui.tab_widget->addTab(workspace, name);

	return tab_index;
}

void Workspaces::closeEvent(QCloseEvent* event)
{
	qDebug() << "Closing and saving settings!";
	save_settings();
	QMainWindow::closeEvent(event);
}

void Workspaces::on_actionPreferences_triggered()
{
	settings_dialog->show();
}

