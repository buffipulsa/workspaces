#include "node_search_dialog.h"

#include <QShowEvent>
#include <QMouseEvent>


NodeSearchDialog::NodeSearchDialog(QObject* parent /*= nullptr*/)
	: QDialog((QWidget*)parent)
{
	setupUi(this);

	apply_settings();
	
	qApp->installEventFilter(this);
}

NodeSearchDialog::~NodeSearchDialog()
{
	qApp->removeEventFilter(this);
}

void NodeSearchDialog::set_position(QPointF pos)
{
	move(pos.toPoint());
}

void NodeSearchDialog::apply_settings()
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_DeleteOnClose);
}

void NodeSearchDialog::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);

	search_le->setFocus();
}

 bool NodeSearchDialog::eventFilter(QObject* object, QEvent* event)
 {
	 if (event->type() == QEvent::MouseButtonPress)
	 {
		 QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
		 if (mouse_event->button() == Qt::LeftButton)
		 {
			 QPoint global_pos = mouse_event->globalPosition().toPoint();
             if (!this->rect().contains(this->mapFromGlobal(global_pos)))
			 {
				 this->close();
				 return true;
			 }
		 }
	 }
	 return false;
 }
