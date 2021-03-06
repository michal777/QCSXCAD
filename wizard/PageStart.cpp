#include "PageStart.h"

PageStart::PageStart(QWizard *parent, QCSXCAD *wizardsparent): QWizardPage(parent)
{
    parent_tmp = (WizardInit*)parent;
    ConfigPaths();
    LoadSettings();
}

void PageStart::ConfigPaths()
{
    QLabel *statictext_oemspath = new QLabel("path to the openEMS installation directory:", this);
    text_openems_path = new QLineEdit(this);
    text_openems_path->setMinimumWidth(300);
    QPushButton *button_set_openems_path = new QPushButton("...", this);
    button_set_openems_path->setMaximumSize(QSize(30, 20));

    QLabel *statictext_simpath = new QLabel("path to the simulation directory:", this);
    text_simulation_path = new QLineEdit(this);
    text_simulation_path->setMinimumWidth(300);
    QPushButton *button_set_simulation_path = new QPushButton("...", this);
    button_set_simulation_path->setMaximumSize(QSize(30, 20));

    connect(button_set_openems_path, SIGNAL(released()), this, SLOT(OnSetOpenEMSPath()));
    connect(button_set_simulation_path, SIGNAL(released()), this, SLOT(OnSetSimulationPath()));

    QGridLayout *grid_pagestart = new QGridLayout(this);
    grid_pagestart->addWidget(statictext_oemspath, 0, 0, 1, 2, Qt::AlignLeft);
    grid_pagestart->addWidget(text_openems_path, 1, 0, Qt::AlignRight);
    grid_pagestart->addWidget(button_set_openems_path, 1, 1, Qt::AlignLeft);
    grid_pagestart->addWidget(statictext_simpath, 2, 0, 1, 2, Qt::AlignLeft);
    grid_pagestart->addWidget(text_simulation_path, 3, 0, Qt::AlignRight);
    grid_pagestart->addWidget(button_set_simulation_path, 3, 1, Qt::AlignLeft);
}

bool PageStart::validatePage()
{
    parent_tmp->wizard_settings = new QSettings(text_simulation_path->text() + "/wizard_setting.ini", QSettings::NativeFormat, this);
    parent_tmp->var_edit_main->LoadSettings();
    SaveToSimScriptBuffer();
    SaveSettings();
    return true;
}

void PageStart::SaveToSimScriptBuffer(void)
{
    text_save_to_simscript.clear();
    text_save_to_simscript.append("##<OUTPUT_AUTOGENERATED_PageStart>##\n");
    text_save_to_simscript.append("close all;\n");
    text_save_to_simscript.append("clear;\n");
    text_save_to_simscript.append("clc;\n");
    #ifdef W_OS_LINUX
    text_save_to_simscript.append(QString("addpath('%1/share/CSXCAD/matlab');\n").arg(text_openems_path->text()));
    text_save_to_simscript.append(QString("addpath('%1/share/openEMS/matlab');\n").arg(text_openems_path->text()));
    #else
    text_save_to_simscript.append(QString("addpath('%1/matlab');\n").arg(text_openems_path->text()));
    #endif
    text_save_to_simscript.append(QString("sim_path = '%1';\n").arg(text_simulation_path->text()));
    text_save_to_simscript.append("sim_file = 'sim_file.xml';\n");
    text_save_to_simscript.append("##<END_OUTPUT_AUTOGENERATED_PageStart>##\n");

    /*
confirm_recursive_rmdir(0);
rmdir(sim_path, 's');
mkdir(sim_path);
*/
    qDebug("%s", qUtf8Printable(text_save_to_simscript));
}

void PageStart::ReadFromSimScriptBuffer(void)
{

}

void PageStart::LoadSettings()
{
    text_simulation_path->setText(parent_tmp->main_settings->value("last_selected_simulation_path", "").toString());
    text_openems_path->setText(parent_tmp->main_settings->value("last_selected_opemems_path", "").toString());
}

void PageStart::SaveSettings()
{
    parent_tmp->main_settings->setValue("last_selected_simulation_path", text_simulation_path->text());
    parent_tmp->main_settings->setValue("last_selected_opemems_path", text_openems_path->text());
}

void PageStart::OnSetOpenEMSPath()
{
    QFileDialog *dir_dialog = new QFileDialog(this);
    text_openems_path->insert(dir_dialog->getExistingDirectory(this));
}

void PageStart::OnSetSimulationPath()
{
    QFileDialog *dir_dialog = new QFileDialog(this);
    text_simulation_path->insert(dir_dialog->getExistingDirectory(this));
}
