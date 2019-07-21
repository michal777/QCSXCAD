#ifndef PAGEGEOMETRY_H
#define PAGEGEOMETRY_H

#include <QWizard>
#include <QWizardPage>
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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QDebug>
#include <QComboBox>
#include <QStringList>
#include <QTableWidget>
#include <QScriptEngine>

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
#include "CSPrimSphere.h"
#include "CSPrimSphericalShell.h"
#include "CSPrimCylinder.h"
#include "CSPrimCylindricalShell.h"
#include "CSPrimCurve.h"
#include "CSPrimWire.h"
#include "CSPrimPolygon.h"
#include "CSPrimLinPoly.h"
#include "CSPrimRotPoly.h"
#include "CSPrimPolyhedron.h"
#include "CSPrimPolyhedronReader.h"
#include "CSPropMetal.h"
#include "CSProperties.h"
#include "ContinuousStructure.h"



//////////////////////////////////////////////////////////////////////////////////////////////////
/// Parameters of shapes, common to all shapes (specific shapes will be derived)
//////////////////////////////////////////////////////////////////////////////////////////////////
class shape_parameters
{
public:
    QString name;
    QString type;
    QString priority;
    QString material;
    unsigned int id;

    QString transf_scale_x;
    QString transf_scale_y;
    QString transf_scale_z;
    QString transf_rotate_ax;
    QString transf_rotate_ay;
    QString transf_rotate_az;
    QString transf_rotate_angle;
    QString transf_move_x;
    QString transf_move_y;
    QString transf_move_z;
    QString transf_order[3];
};

//////////////////////////////////////////////////////////////////////////////////////////////////
/// Parameters of specific shapes
//////////////////////////////////////////////////////////////////////////////////////////////////
class shape_box_parameters : public shape_parameters
{
public:
    QString x_coord_1;
    QString x_coord_2;
    QString y_coord_1;
    QString y_coord_2;
    QString z_coord_1;
    QString z_coord_2;
};

class shape_sphere_parameters : public shape_parameters
{
public:
    QString x_coord;
    QString y_coord;
    QString z_coord;
    QString radius;
};

class shape_sphericalshell_parameters : public shape_parameters
{
public:
    QString x_coord;
    QString y_coord;
    QString z_coord;
    QString radius_outer;
    QString radius_inner;
};

class shape_cylinder_parameters : public shape_parameters
{
public:
    QString x_coord_1;
    QString x_coord_2;
    QString y_coord_1;
    QString y_coord_2;
    QString z_coord_1;
    QString z_coord_2;
    QString radius;
};

class shape_cylindricalshell_parameters : public shape_parameters
{
public:
    QString x_coord_1;
    QString x_coord_2;
    QString y_coord_1;
    QString y_coord_2;
    QString z_coord_1;
    QString z_coord_2;
    QString radius_outer;
    QString radius_inner;
};

class shape_curve_parameters : public shape_parameters
{
public:
    QVector<QString> points_x;
    QVector<QString> points_y;
    QVector<QString> points_z;
};

class shape_wire_parameters : public shape_parameters
{
public:
    QVector<QString> points_x;
    QVector<QString> points_y;
    QVector<QString> points_z;
    QString radius;
};

class shape_polygon_parameters : public shape_parameters
{
public:
    QVector<QString> points_x;
    QVector<QString> points_y;
    QString normal_dir;
    QString elevation;
};

class shape_extrudedpolygon_parameters : public shape_parameters
{
public:
    QVector<QString> points_x;
    QVector<QString> points_y;
    QString normal_dir;
    QString elevation;
    QString length;
};

class shape_rotationalpolygon_parameters : public shape_parameters
{
public:
    QVector<QString> points_x;
    QVector<QString> points_y;
    QString normal_dir;
    QString rot_axis_dir;
    QString angle1;
    QString angle2;
};

class shape_polyhedron_parameters : public shape_parameters
{
public:
    QVector<QString> vertices_x;
    QVector<QString> vertices_y;
    QVector<QString> vertices_z;
    QVector<QString> faces_x;
    QVector<QString> faces_y;
    QVector<QString> faces_z;

};

class shape_stlfile_parameters : public shape_parameters
{
public:
    QString path;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
/// The page of the wizard that is used to configure geometry
//////////////////////////////////////////////////////////////////////////////////////////////////

class PageGeometry : public QWizardPage
{
    Q_OBJECT
public:
    PageGeometry(QWizard *parent, QCSXCAD *wizardsparent, VariablesEditor *var_edit_main);

    //basic functions of wizard page
    bool validatePage();
    void SaveToSimScriptBuffer(void);
    void ReadFromSimScriptBuffer(void);
    QString text_save_to_simscript;

    //variables defined in variable editor can be used here, variables are processed using QScriptEngine
    QCSXCAD *wizardsparent_tmp;
    VariablesEditor *var_edit;
    double EvaluateVar(QString var_to_eval);

    //list of shapes widget
    QListWidget *shapes_list_widget;
    QVector<shape_parameters *> *shapes_param_list_ptr;

    //layouts
    QHBoxLayout *main_layout_shapes;
    QStackedLayout *stackedLayout;
    QGroupBox *shape_select_groupbox;
    QGroupBox *shape_list_groupbox;
    QGroupBox *transforms_groupbox;
    QGroupBox *groupbox_box_settings;
    QGroupBox *groupbox_sphere_settings;
    QGroupBox *groupbox_sphericalshell_settings;
    QGroupBox *groupbox_cylinder_settings;
    QGroupBox *groupbox_cylindricalshell_settings;
    QGroupBox *groupbox_curve_settings;
    QGroupBox *groupbox_wire_settings;
    QGroupBox *groupbox_polygon_settings;
    QGroupBox *groupbox_extrudedpolygon_settings;
    QGroupBox *groupbox_rotationalpolygon_settings;
    QGroupBox *groupbox_polyhedron_settings;
    QGroupBox *groupbox_stlfile_settings;

    void ShapeSelectLayout(void);
    void ShapeListLayout(void);
    void ShapeTransformsLayout(void);
    void ShapeBoxSettings(void);
    void ShapeSphereSettings(void);
    void ShapeSphericalshellSettings(void);
    void ShapeCylinderSettings(void);
    void ShapeCylindricalshellSettings(void);
    void ShapeCurveSettings(void);
    void ShapeWireSettings(void);
    void ShapePolygonSettings(void);
    void ShapeExtrudedPolygonSettings(void);
    void ShapeRotationalPolygonSettings(void);
    void ShapePolyhedronSettings(void);
    void ShapeSTLfileSettings(void);

    //updating QCSXCAD from wizard(displaying shapes in the main application)
    unsigned int UploadShapesToViewer(bool is_new);
    void RemoveShapesFromViewer(void);

    //load materials at the start
    virtual void initializePage(void);

    //user input (buttons, input fields...)
    QRadioButton *rad_but_type_box;
    QRadioButton *rad_but_type_sphere;
    QRadioButton *rad_but_type_sphericalshell;
    QRadioButton *rad_but_type_cylinder;
    QRadioButton *rad_but_type_cylindricalshell;
    QRadioButton *rad_but_type_curve;
    QRadioButton *rad_but_type_wire;
    QRadioButton *rad_but_type_polygon;
    QRadioButton *rad_but_type_extrudedpolygon;
    QRadioButton *rad_but_type_rotationalpolygon;
    QRadioButton *rad_but_type_polyhedron;
    QRadioButton *rad_but_type_stlfile;

    QLineEdit *sh_box_name;
    QLineEdit *sh_box_priority;
    QComboBox *sh_box_material;
    QLineEdit *sh_box_x_coord_1;
    QLineEdit *sh_box_x_coord_2;
    QLineEdit *sh_box_y_coord_1;
    QLineEdit *sh_box_y_coord_2;
    QLineEdit *sh_box_z_coord_1;
    QLineEdit *sh_box_z_coord_2;

    QLineEdit *sh_sphere_name;
    QLineEdit *sh_sphere_priority;
    QComboBox *sh_sphere_material;
    QLineEdit *sh_sphere_x_coord;
    QLineEdit *sh_sphere_y_coord;
    QLineEdit *sh_sphere_z_coord;
    QLineEdit *sh_sphere_radius;

    QLineEdit *sh_sphericalshell_name;
    QLineEdit *sh_sphericalshell_priority;
    QComboBox *sh_sphericalshell_material;
    QLineEdit *sh_sphericalshell_x_coord;
    QLineEdit *sh_sphericalshell_y_coord;
    QLineEdit *sh_sphericalshell_z_coord;
    QLineEdit *sh_sphericalshell_radius_outer;
    QLineEdit *sh_sphericalshell_radius_inner;

    QLineEdit *sh_cylinder_name;
    QLineEdit *sh_cylinder_priority;
    QComboBox *sh_cylinder_material;
    QLineEdit *sh_cylinder_x_coord_1;
    QLineEdit *sh_cylinder_x_coord_2;
    QLineEdit *sh_cylinder_y_coord_1;
    QLineEdit *sh_cylinder_y_coord_2;
    QLineEdit *sh_cylinder_z_coord_1;
    QLineEdit *sh_cylinder_z_coord_2;
    QLineEdit *sh_cylinder_radius;

    QLineEdit *sh_cylindricalshell_name;
    QLineEdit *sh_cylindricalshell_priority;
    QComboBox *sh_cylindricalshell_material;
    QLineEdit *sh_cylindricalshell_x_coord_1;
    QLineEdit *sh_cylindricalshell_x_coord_2;
    QLineEdit *sh_cylindricalshell_y_coord_1;
    QLineEdit *sh_cylindricalshell_y_coord_2;
    QLineEdit *sh_cylindricalshell_z_coord_1;
    QLineEdit *sh_cylindricalshell_z_coord_2;
    QLineEdit *sh_cylindricalshell_radius_outer;
    QLineEdit *sh_cylindricalshell_radius_inner;

    QLineEdit *sh_curve_name;
    QLineEdit *sh_curve_priority;
    QComboBox *sh_curve_material;
    QTableWidget *sh_curve_pointslist;

    QLineEdit *sh_wire_name;
    QLineEdit *sh_wire_priority;
    QComboBox *sh_wire_material;
    QTableWidget *sh_wire_pointslist;
    QLineEdit *sh_wire_radius;

    QLineEdit *sh_polygon_name;
    QLineEdit *sh_polygon_priority;
    QComboBox *sh_polygon_material;
    QTableWidget *sh_polygon_pointslist;
    QLineEdit *sh_polygon_norm_dir;
    QLineEdit *sh_polygon_elevation;

    QLineEdit *sh_extrudedpolygon_name;
    QLineEdit *sh_extrudedpolygon_priority;
    QComboBox *sh_extrudedpolygon_material;
    QTableWidget *sh_extrudedpolygon_pointslist;
    QLineEdit *sh_extrudedpolygon_norm_dir;
    QLineEdit *sh_extrudedpolygon_elevation;
    QLineEdit *sh_extrudedpolygon_length;

    QLineEdit *sh_rotationalpolygon_name;
    QLineEdit *sh_rotationalpolygon_priority;
    QComboBox *sh_rotationalpolygon_material;
    QTableWidget *sh_rotationalpolygon_pointslist;
    QLineEdit *sh_rotationalpolygon_norm_dir;
    QLineEdit *sh_rotationalpolygon_rot_axis;
    QLineEdit *sh_rotationalpolygon_angle1;
    QLineEdit *sh_rotationalpolygon_angle2;

    QLineEdit *sh_polyhedron_name;
    QLineEdit *sh_polyhedron_priority;
    QComboBox *sh_polyhedron_material;
    QTableWidget *sh_polyhedron_verticeslist;
    QTableWidget *sh_polyhedron_faceslist;

    QLineEdit *sh_stlfile_name;
    QLineEdit *sh_stlfile_priority;
    QComboBox *sh_stlfile_material;
    QLineEdit *sh_stlfile_path;

    QListWidget *transforms_list_widget;
    QPushButton *button_transform_scale;
    QPushButton *button_transform_rotate;
    QPushButton *button_transform_move;
    QPushButton *button_transform_remove;
    QLineEdit *transf_scale_x;
    QLineEdit *transf_scale_y;
    QLineEdit *transf_scale_z;
    QLineEdit *transf_rotate_ax;
    QLineEdit *transf_rotate_ay;
    QLineEdit *transf_rotate_az;
    QLineEdit *transf_rotate_angle;
    QLineEdit *transf_move_x;
    QLineEdit *transf_move_y;
    QLineEdit *transf_move_z;

public slots:
    void OnSetShapeTypeLayout(void);
    void OnAddOrChangeShape(void);
    void OnRemoveShape(void);
    void OnGetSelectedShape(QListWidgetItem* item);
    void OnPointslistUpdate(int row, int column);
    void OnChangeTransformOrder(void);
};

#endif // PAGEGEOMETRY_H
