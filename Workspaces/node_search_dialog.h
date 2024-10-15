#pragma once

#include "ui_node_search_dialog.h"

#include <QDialog>
#include <QPointF>

class NodeSearchDialog : public QDialog, public Ui::NodeSearchDialog
{
	Q_OBJECT

public:
	NodeSearchDialog(QObject *parent = nullptr);
	~NodeSearchDialog();

	void set_position(QPointF pos);

private:
	void apply_settings();

protected:
	void showEvent(QShowEvent* event) override;
	bool eventFilter(QObject* object, QEvent* event) override;
};
