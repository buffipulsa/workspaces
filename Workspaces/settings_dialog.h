#pragma once

#include "ui_settings_dialog.h"

#include <QDialog>
#include <QString>
#include <QScopedPointer>
#include <QSettings>

class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent = nullptr);
	~SettingsDialog();

	QString get_project_path();
	void set_project_path(QString& path);

private slots:
	void on_browse_btn_clicked();
};
