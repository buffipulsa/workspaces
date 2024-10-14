#include "settings_dialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

SettingsDialog::~SettingsDialog()
{}

QString SettingsDialog::get_project_path()
{
	qDebug() << path_le->text();
	return path_le->text();
}

void SettingsDialog::set_project_path(QString& path)
{
	path_le->setText(path);
}



void SettingsDialog::on_browse_btn_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	path_le->setText(path);
}
