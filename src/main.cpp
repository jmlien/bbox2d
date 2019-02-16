#include "bbox2d.h"
#include "polygon.h"
#include <fstream>
using namespace std;

void createPoly(const string& filename, masc::polygon::c_polygon& poly); //see below

int main(int argc, char ** argv)
{
  if(argc!=2)
  {
    cerr<<"Usage: "<<argv[0]<<" polygon"<<endl;
    return 1;
  }

  //create polygon
  masc::polygon::c_polygon poly;
  createPoly(argv[1],poly);

  //create bbox of the polygon
  masc::polygon::bbox2d bbox(poly);

  //create min-area bbox
  masc::polygon::min_area_bbox p1;
  masc::polygon::obb min_area_bbox = bbox.build(p1);
  cout<<"BBox with min area: "<<min_area_bbox<<endl;
  saveSVG("min_area_bbox.svg",poly.front(),min_area_bbox);

  //build min-perimeter box
  masc::polygon::min_perimeter_bbox p2;
  masc::polygon::obb min_peri_bbox = bbox.build(p2);
  cout<<"BBox with min perimeter: "<<min_peri_bbox<<endl;
  saveSVG("min_perimeter_bbox.svg",poly.front(),min_peri_bbox);

  //build a box that fits into 13X13 square
  float W=28, H=28;
  masc::polygon::contained_bbox p3(W,H);
  masc::polygon::obb bbox_WXH = bbox.build(p3);
  if(p3.solved(bbox_WXH)==false)
    cerr<<"! Error: Cannot find a bounding box that fits into "<<W<<"X"<<H<<" square"<<endl;
  else
  {
    cout<<"BBox contained in "<<W<<"X"<<H<<" square: "<<bbox_WXH<<endl;
    saveSVG("contained_bbox.svg",poly.front(),bbox_WXH);
  }

  return 0;
}


void createPoly(const string& filename, masc::polygon::c_polygon& poly)
{
    //read polygon from poly files
    if(filename.find(".poly") != string::npos ){
  		ifstream fin(filename.c_str());
  		if( fin.good()==false ){
  			cerr<<"! ERROR: can NOT open file : "<<filename<<endl;
  			return;
  		}
  		fin>>poly;
  		//close the file
  		fin.close();
    }
/*
    else  //assume shape file
    {
      ShapeReader reader;

      bool r=reader.read(filename);
      if(!r || reader.getPolyList().empty()){
        return; //failed reading...
      }

      cout<<"- Read in "<<reader.getPolyList().size()<<" polygons from "<<filename<<endl;
      poly=reader.getPolyList().front();
      //auto& pos=poly.front().getHead()->getPos();
      //const Vector2d offset(-pos[0],-pos[1]);
    }
*/
}
