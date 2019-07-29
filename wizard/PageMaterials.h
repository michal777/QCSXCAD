#ifndef PAGEMATERIALS_H
#define PAGEMATERIALS_H

#include <QWizard>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QVector>
#include <QGroupBox>
#include <QRadioButton>
#include <QDebug>
#include <string>
#include <QStackedLayout>
#include <QHBoxLayout>

#include "VariablesEditor.h"
//??
#include "../QCSXCAD.h"
#include "../QCSPrimEditor.h"
#include "../QCSPropEditor.h"
#include "../QCSTreeWidget.h"
#include "../QParameterGui.h"
#include "ParameterCoord.h"
#include "CSPrimitives.h"
#include "CSPrimBox.h"
#include "CSPropMetal.h"
#include "CSPropMaterial.h"
#include "CSProperties.h"
#include "ContinuousStructure.h"


class property_parameters
{
public:
    QString name;
    QString type;
};
class material_parameters : public property_parameters
{
public:
    QString epsilon;
    QString mue;
    QString kappa;
    QString sigma;
};
class metal_parameters : public property_parameters
{
public:
    QString conductivity;
    QString thickness;
};


class PageMaterials : public QWizardPage
{
    Q_OBJECT
public:
    PageMaterials(QWizard *parent, QCSXCAD *wizardsparent, VariablesEditor *var_edit_main);

    bool validatePage();
    void SaveToSimScriptBuffer(void);
    void ReadFromSimScriptBuffer(void);
    QString text_save_to_simscript;

    //variables defined in variable editor can be used here, variables are processed using QScriptEngine
    QCSXCAD *wizardsparent_tmp;
    VariablesEditor *var_edit;
//    double EvaluateVar(QString var_to_eval);

    //list of properties widget
    QListWidget *properties_list_widget;
    QVector<property_parameters *> *properties_list_ptr;


    //layouts
    QHBoxLayout *main_layout_property;
    QStackedLayout *stackedLayout;
    QGroupBox *property_select_groupbox;
    QGroupBox *property_list_groupbox;
    QGroupBox *groupbox_material_settings;
    QGroupBox *groupbox_metal_settings;

    void MaterialSelectLayout(void);
    void MaterialListLayout(void);
    void MaterialSettings(void);
    void MetalSettings(void);

    //updating QCSXCAD from wizard(adding materials to the main application)
    void UploadMaterialsToViewer(void);
    void RemoveMaterialsFromViewer(void);

    //user input (buttons, input fields...)
    QRadioButton *rad_but_type_material;
    QRadioButton *rad_but_type_metal;

    QLineEdit *material_name;
    QLineEdit *material_epsilon;
    QLineEdit *material_mue;
    QLineEdit *material_kappa;
    QLineEdit *material_sigma;

    QLineEdit *metal_name;
    QLineEdit *metal_conductivity;
    QLineEdit *metal_thickness;

public slots:
    void OnSetMaterialTypeLayout(void);
    void OnAddOrChangeMaterial(void);
    void OnRemoveMaterial(void);
    void OnGetSelectedMaterial(QListWidgetItem* item);
};

#endif // PAGEMATERIALS_H
