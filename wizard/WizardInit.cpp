#include "WizardInit.h"
#include "PageStart.h"
#include "PageBasicSimSetup.h"
#include "PageGeneralGeometrySettings.h"
#include "PageGeometry.h"
#include "PagePorts.h"
#include "PageResultsSparam.h"
#include "PageMaterials.h"


WizardInit::WizardInit(QCSXCAD *wizardsparent, QWidget *parent): QWizard(parent)
{
    wizardsparent_tmp = wizardsparent;
    file_main_settings = "app_settings.ini";
    main_settings = new QSettings(file_main_settings, QSettings::NativeFormat, this);

    var_edit_main = new VariablesEditor(this);
    var_edit_main->show();

    StartWizardWindow();    //dialog with workflow selection will appear, when selected the listed pages are added to this wizard

    for(int i_wizardorder = 0; i_wizardorder < wizard_setup.length(); ++i_wizardorder)
        this->addPage(ReturnWorkflowStep(wizard_setup.at(i_wizardorder), var_edit_main));
}


QWizardPage *WizardInit::ReturnWorkflowStep(QString workflowname, VariablesEditor *var_edit_main)
{
    if(!workflowname.compare("Start page"))
        return new PageStart(this, wizardsparent_tmp);
    else if(!workflowname.compare("Basic simulation setup"))
        return new PageBasicSimSetup(this, wizardsparent_tmp);
    else if(!workflowname.compare("General geometry settings"))
        return new PageGeneralGeometrySettings(this, wizardsparent_tmp);
    else if(!workflowname.compare("Materials"))
        return new PageMaterials(this, wizardsparent_tmp, var_edit_main);
    else if(!workflowname.compare("Geometry"))
        return new PageGeometry(this, wizardsparent_tmp, var_edit_main);
    else if(!workflowname.compare("Ports"))
        return new PagePorts(this, wizardsparent_tmp);
    else if(!workflowname.compare("Results"))
        return new PageResultsSparam(this, wizardsparent_tmp);
}


void WizardInit::StartWizardWindow()
{
    dialog_load_workflow = new QDialog(this);

    LoadSettings();

    //selecting pages presence and order
    QGroupBox *workflows_list_groupbox = new QGroupBox(tr("workflows list"));
    QGridLayout *grid_layout_workflows_list = new QGridLayout;
    rad_but_workflow_s_param_sim = new QRadioButton("basic s-parameters simulation", this);
    rad_but_workflow_s_param_sim->setChecked(true);
    grid_layout_workflows_list->addWidget(rad_but_workflow_s_param_sim, 0, 0, Qt::AlignLeft);
    workflows_list_groupbox->setLayout(grid_layout_workflows_list);

    //button starting the wizard
    QPushButton *button_run_wizard = new QPushButton("Run the wizard", dialog_load_workflow);

    QHBoxLayout *wizard_init_qhboxlayout = new QHBoxLayout;
    wizard_init_qhboxlayout->addWidget(workflows_list_groupbox);
    wizard_init_qhboxlayout->addWidget(button_run_wizard);
    dialog_load_workflow->setLayout(wizard_init_qhboxlayout);

    connect(button_run_wizard, SIGNAL(released()), this, SLOT(OnRunWizard()));

    //after closing the dialog the wizard will add pages according to loaded file
    dialog_load_workflow->exec();
}

void WizardInit::LoadSettings()
{
//    text_wffile_path->setText(main_settings->value("last_selected_workflow", "").toString());
}

void WizardInit::SaveSettings()
{
//    main_settings->setValue("last_selected_workflow", text_wffile_path->text());
}

void WizardInit::OnSetupWizard() //presence and order of pages that will appar in the wizard
{
    if(rad_but_workflow_s_param_sim->isChecked())
    {
        wizard_setup.clear();
        wizard_setup.push_back("Start page");
        wizard_setup.push_back("Basic simulation setup");
        wizard_setup.push_back("General geometry settings");
        wizard_setup.push_back("Materials");
        wizard_setup.push_back("Geometry");
        wizard_setup.push_back("Ports");
        wizard_setup.push_back("Results");
    }
}

void WizardInit::OnRunWizard()
{
    SaveSettings();
    OnSetupWizard();
    dialog_load_workflow->close();
}
