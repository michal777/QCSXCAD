#include "PageResultsSparam.h"

PageResultsSparam::PageResultsSparam(QWizard *parent, QCSXCAD *wizardsparent): QWizardPage(parent)
{
    QLabel *statictext_TODO = new QLabel("Configuration of results postprocessing for selected workflow TO BE DONE", this);
    statictext_TODO->setGeometry(QRect(QPoint(22, 20), QSize(500, 30)));

}


bool PageResultsSparam::validatePage()
{
    SaveToSimScriptBuffer();
    return true;
}


void PageResultsSparam::SaveToSimScriptBuffer(void)
{
    text_save_to_simscript.clear();
    text_save_to_simscript.append("##<OUTPUT_AUTOGENERATED_PageResultsSparam>##\n");


    text_save_to_simscript.append("##<END_OUTPUT_AUTOGENERATED_PageResultsSparam>##\n");
    qDebug("%s", qUtf8Printable(text_save_to_simscript));
}


void PageResultsSparam::ReadFromSimScriptBuffer(void)
{

}