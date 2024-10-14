#pragma once

#include "ui_emm_pipe.h"
#include "settings_dialog.h"

#include <QMainWindow>
#include <QScopedPointer>
#include <QStringList>

/**
 * @brief The EmmPipe class represents the main window of the EmmPipe application.
 * It inherits from QMainWindow and provides functionality for managing projects and settings.
 */
class Workspaces : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an EmmPipe object.
     * @param parent The parent widget.
     */
    Workspaces(QWidget *parent = nullptr);

    /**
     * @brief Destroys the EmmPipe object.
     */
    ~Workspaces();

private:
    Ui::EmmPipeWindow ui; /**< The user interface for the main window. */

    QScopedPointer<SettingsDialog> settings_dialog; /**< The settings dialog. */

    static int workspace_count;

    /**
     * @brief Saves the application settings.
     */
    void save_settings();

    /**
     * @brief Loads the application settings.
     */
    void load_settings();

    /**
     * @brief Retrieves the list of projects.
     * @return The list of projects.
     */
    QStringList get_projects();

    /**
     * @brief Sets the projects combobox with the list of projects.
     */
    void set_projects_combobox();

    /**
     * @brief Retrieves the index of the selected department.
     * @return The index of the selected department.
     */
    int get_department_index();

    /**
     * @brief Retrieves the index of the selected project.
     * @return The index of the selected project.
     */
    int get_project_index();

    /**
     * @brief Adds a new tab with the given name.
     * @param name The name of the tab.
     * @return The index of the added tab.
     */
    int add_tab(QString name);

private slots:
    /**
     * @brief Handles the action triggered when the Preferences menu item is clicked.
     */
    void on_actionPreferences_triggered();

    /**
     * @brief Handles the button click event for the Maya button.
     */
    void on_maya_btn_clicked();

    /**
     * @brief Handles the button click event for the Unreal button.
     */
    void on_unreal_btn_clicked();

protected:
    /**
     * @brief Handles the close event of the main window.
     * @param event The close event.
     */
    void closeEvent(QCloseEvent* event) override;
};
