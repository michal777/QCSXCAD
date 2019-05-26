#ifndef PAGEGEOMETRY_H
#define PAGEGEOMETRY_H

#include <QWizard>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
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


class PageGeometry : public QWizardPage
{
    Q_OBJECT
public:
    PageGeometry(QWizard *parent, QCSXCAD *wizardsparent);

    bool validatePage();
    void SaveToSimScriptBuffer(void);
    void ReadFromSimScriptBuffer(void);
    QString text_save_to_simscript;

/* START experiments with qcsxcad*/
    QCSXCAD *wizardsparent_tmp;
    double thecord[3];
    void EXPERIMENTS1(void);
public slots:
    void EXPERIMENTS(void);
/* END experiments with qcsxcad*/

};

#endif // PAGEGEOMETRY_H
