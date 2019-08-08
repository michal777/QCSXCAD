#include "VariablesEditor.h"
#include "WizardInit.h"
#include <QDebug>

VariablesEditor::VariablesEditor(QWizard *parent): QDialog(parent)
{
    parent_tmp = parent;

    var_table = new QTableWidget(this);
    this->resize(QSize(300, 300));
    var_table->setRowCount(100);
    var_table->setColumnCount(3);

    QStringList table_header;
    table_header << "variable" << "expression" << "value";
    var_table->setHorizontalHeaderLabels(table_header);
    var_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    centralLayout->addWidget(var_table);
    OnEvaluateVarTable();   //call the function at the beginning to initialize so avoid crash

    connect(var_table, SIGNAL(itemSelectionChanged()), this, SLOT(OnEvaluateVarTable()));

}


void VariablesEditor::OnEvaluateVarTable()
{
    QString line_var, line_value;
    expr_eval = new QScriptEngine();
    QScriptValue expr_value[tablesize];

    QString table_line;
    QTableWidgetItem *line_var_tmp, *line_value_tmp;
    int i_expr = 0;
    int all_valid = 1;
    int timeout = 1000;

    do
    {
        for(i_expr = 0; i_expr < tablesize; ++i_expr)
        {
            line_var_tmp = var_table->item(i_expr, 0);
            line_value_tmp = var_table->item(i_expr, 1);
            if((line_var_tmp != NULL) && (line_value_tmp != NULL))
            {
                line_var = line_var_tmp->text();
                line_value = line_value_tmp->text();
                table_line.clear();
                table_line.append(QString("%1 = %2").arg(line_var).arg(line_value));
                expr_value[i_expr] = expr_eval->evaluate(table_line);
                QTableWidgetItem *line_output_val_tmp = new QTableWidgetItem(0);
                line_output_val_tmp->setText(expr_value[i_expr].toString());
                var_table->setItem(i_expr, 2, line_output_val_tmp);
                if(expr_value[i_expr].isError())
                    all_valid = 0;
            }
        }
        timeout--;
    } while(all_valid == 0 && timeout);
    SaveSettings();
}



void VariablesEditor::LoadSettings()
{
    for(int i_loadset = 0; "" != ((WizardInit*)parent_tmp)->wizard_settings->value(QString("Variables_var%1").arg(i_loadset), "").toString(); ++i_loadset)
    {
        QTableWidgetItem *line_var_tmp = new QTableWidgetItem(0);
        line_var_tmp->setText(((WizardInit*)parent_tmp)->wizard_settings->value(QString("Variables_var%1").arg(i_loadset), "").toString());
        var_table->setItem(i_loadset, 0, line_var_tmp);
    }
    for(int i_loadset = 0; "" != ((WizardInit*)parent_tmp)->wizard_settings->value(QString("Variables_value%1").arg(i_loadset), "").toString(); ++i_loadset)
    {
        QTableWidgetItem *line_value_tmp = new QTableWidgetItem(0);
        line_value_tmp->setText(((WizardInit*)parent_tmp)->wizard_settings->value(QString("Variables_value%1").arg(i_loadset), "").toString());
        var_table->setItem(i_loadset, 1, line_value_tmp);
    }
}

void VariablesEditor::SaveSettings()
{
    QTableWidgetItem *line_var_tmp, *line_value_tmp;
    for(int i_saveset = 0; i_saveset < tablesize; ++i_saveset)
    {
        line_var_tmp = var_table->item(i_saveset, 0);
        line_value_tmp = var_table->item(i_saveset, 1);
        if((line_var_tmp != NULL) && (line_value_tmp != NULL))
        {
            ((WizardInit*)parent_tmp)->wizard_settings->setValue(QString("Variables_var%1").arg(i_saveset), line_var_tmp->text());
            ((WizardInit*)parent_tmp)->wizard_settings->setValue(QString("Variables_value%1").arg(i_saveset), line_value_tmp->text());
        }
    }
}
