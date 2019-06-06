#ifndef PAGEMATERIALS_H
#define PAGEMATERIALS_H

#include <QWizard>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QVector>
#include <QString>
#include <QPushButton>

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
#include "ContinuousStructure.h"



struct material_parameters_struct
{
    QString name;
    QString type;
    QString epsilon;
    QString mue;
    QString kappa;
    QString sigma;
    QString conductivity;
    QString thickness;
};


class PageMaterials : public QWizardPage
{
    Q_OBJECT
public:
    PageMaterials(QWizard *parent, QCSXCAD *wizardsparent);

    bool validatePage();
    void SaveToSimScriptBuffer(void);
    void ReadFromSimScriptBuffer(void);
    QString text_save_to_simscript;

    QCSXCAD *wizardsparent_tmp;

    QListWidget *materials_list_widget;
    QVector<material_parameters_struct> *materials_param_list_ptr;

    QGridLayout *grid_material;

    void MaterialsSettings(void);
    void UploadMaterialsToViewer(void);


    QLineEdit *name;
    QLineEdit *type;
    QLineEdit *epsilon;
    QLineEdit *mue;
    QLineEdit *kappa;
    QLineEdit *sigma;
    QLineEdit *conductivity;
    QLineEdit *thickness;

public slots:
    void OnAddMaterial(void);
    void OnGetSelectedMaterial(QListWidgetItem* item);

};

#endif // PAGEMATERIALS_H
