#include "Maya.h"

#include <QDebug>

#include <QStringList>
#include <QString>
#include <QProcess>

#include <windows.h>


Maya::Maya() 
	: maya_process(new QProcess()) {}

Maya::~Maya()
{
    delete maya_process;
}

int Maya::start_maya_instance(int* port)
{
    QString port_script = QString("python(\"import maya.cmds as cmds; cmds.evalDeferred(cmds.commandPort(name=':%1', echoOutput=False, sourceType='python'));\")").arg(*port);
    QStringList arguments;
    arguments << "-command" << port_script;
    maya_process->start("C:/Program Files/Autodesk/Maya2024/bin/maya.exe", arguments);

    return 0;
}

void Maya::close_maya_instance()
{
	maya_process->close();
}

void Maya::focus_maya_instance()
{
	qDebug() << "Window to front!!";
    DWORD process_id = maya_process->processId();

    HWND window_handle = nullptr;
	EnumWindows([](HWND window_handle, LPARAM lParam) -> BOOL {
		DWORD window_pid;
		GetWindowThreadProcessId(window_handle, &window_pid);
		if (window_pid == (DWORD)lParam) {
			if (!IsWindow(window_handle)) {
				// Invalid window handle; log and return
				qDebug() << "Invalid window handle";
				return TRUE; // Continue enumerating
			}
			qDebug() << "Found Maya window!!" << window_handle;
			SetForegroundWindowBypass(window_handle);
			return FALSE;
		}
		return TRUE;
		}, (LPARAM)process_id);
}

void SetForegroundWindowBypass(HWND hWnd)
{
	if (!::IsWindow(hWnd)) return;

	// Simulate ALT key press to bypass foreground window restrictions
	BYTE keyState[256] = { 0 };
	if (::GetKeyboardState(keyState))
	{
		if (!(keyState[VK_MENU] & 0x80))
		{
			::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		}
	}

	// Bring the window to the foreground
	::SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	::SetForegroundWindow(hWnd);

	// Release the ALT key
	if (::GetKeyboardState(keyState))
	{
		if (!(keyState[VK_MENU] & 0x80))
		{
			::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		}
	}
}
