#ifndef WIZARDINIT_H
#define WIZARDINIT_H

#include <QWizard>
#include <QWizardPage>
#include <QMainWindow>
#include <QFile>
#include <QLineEdit>
#include <QDialog>
#include <QSettings>
#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QVector>
#include <QRadioButton>
#include <QDebug>
#include <QHBoxLayout>
#include "VariablesEditor.h"
//??
#include "../QCSXCAD.h"

class WizardInit : public QWizard
{
    Q_OBJECT
public:
    WizardInit(QCSXCAD *wizardsparent, QWidget *parent = 0);
    QWizardPage *ReturnWorkflowStep(QString workflowname, VariablesEditor *var_edit_main);

    QCSXCAD *wizardsparent_tmp;

    void StartWizardWindow();
    QFile *workflowfile;
    QLineEdit *text_wffile_path;
    QDialog *dialog_load_workflow;
    VariablesEditor *var_edit_main;

    void SaveSettings();
    void LoadSettings();
    QString file_main_settings;
    QSettings *main_settings;
    QSettings *wizard_settings;

    QVector<QString> wizard_setup;

    QRadioButton *rad_but_workflow_s_param_sim;

public slots:
    void OnSetupWizard();
    void OnRunWizard();

};

#endif // WIZARDINIT_H
