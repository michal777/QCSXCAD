#ifndef WIZARDINIT_H
#define WIZARDINIT_H

#include <QWizard>
#include <QWizardPage>
#include <QMainWindow>
#include <QFile>
#include <QLineEdit>
#include <QDialog>
#include <QSettings>
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

    void SaveSettings();
    void LoadSettings();
    QString file_main_settings;
    QSettings *main_settings;

public slots:
    void OnSetWorkflowFilePath();
    void OnRunWizard();

};

#endif // WIZARDINIT_H