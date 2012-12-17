#include <CGAL/IO/Qt_widget_Nef_3.h>
#include <qapplication.h>

#include "defs.h"

using namespace std;
using namespace Rice;

void show_Nef_polyhedron_3(Nef_polyhedron_3 N){

  char *args[]={"Nef_Polyhedron_3 Viewer"};
  int argc=1;
  
  QApplication a(argc, args); 
  CGAL::Qt_widget_Nef_3<Nef_polyhedron_3>* w =
    new CGAL::Qt_widget_Nef_3<Nef_polyhedron_3>(N);
  a.setMainWidget(w);
  w->show();
  
  a.exec();
}

