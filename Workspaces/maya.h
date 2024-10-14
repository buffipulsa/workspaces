#pragma once

#include <QProcess>
#include <windows.h>


class Maya
{
public:
	Maya();
	~Maya();

	int start_maya_instance(int* port);

	void close_maya_instance();
	void focus_maya_instance();

public:
	QProcess* maya_process;
};

void SetForegroundWindowBypass(HWND hWnd);
