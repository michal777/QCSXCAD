#ifndef VARIABLESEDITOR_H
#define VARIABLESEDITOR_H

#include <QWizard>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSettings>
#include <QDialog>
#include <QTableWidget>
#include <QScriptEngine>
#include <QHeaderView>

class VariablesEditor : public QDialog
{
    Q_OBJECT
public:
    VariablesEditor(QWizard *parent);

    QTableWidget *var_table;

    static const int tablesize = 100;
    QScriptEngine *expr_eval;
    QScriptValue expr_value[tablesize];

    QWizard *parent_tmp;    //parent object, needed here for file where settings are saved

    QTableWidget *GetVarTable(void) {return var_table;}
    QScriptEngine *GetExprEngine(void) {return expr_eval;}
    QString GetEvaluatedVar(QString var_to_eval) {return expr_eval->evaluate(var_to_eval).toString();}

    void SaveSettings(void);
    void LoadSettings(void);

public slots:
    void OnEvaluateVarTable();
};

#endif // VARIABLESEDITOR_H
