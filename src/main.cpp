#include "bbox2d.h"
#include "polygon.h"
#include <fstream>
using namespace std;

void createPoly(const string& filename, cd_polygon& poly); //see below
ostream & operator<<(ostream& out, const masc::polygon::obb& box)
{
  out<<"[w="<<box.m_width<<", h="<<box.m_height<<"], ("
     <<box.corners[0]<<") ,("<<box.corners[1]<<"), ("
     <<box.corners[2]<<") ,("<<box.corners[3]<<")";
  return out;
}

int main(int argc, char ** argv)
{
  if(arcg!=2)
  {
    cerr<<"Usage: "<<argv[0]<<" polygon"<<endl;
    return 1;
  }

  //create polygon
  masc::polygon::c_polygon poly;


  //create bbox of the polygon
  masc::polygon::bbox2d bbox(poly);

  //create min-area bbox
  masc::polygon::obb min_area_bbox = bbox.build(min_area_bbox());
  cout<<"BBox with min area: "<<min_area_bbox<<endl;

  //build min-perimeter box
  masc::polygon::obb min_peri_bbox = bbox.build(min_perimeter_bbox());
  cout<<"BBox with min perimeter: "<<min_peri_bbox<<endl;

  //build a box that fits into 13X13 square
  contained_bbox problem(13,13);
  masc::polygon::obb bbox_13X13 = bbox.build(problem);
  if(problem.solved(bbox_13X13)==false)
    cerr<<"! Error: Cannot find a bounding box that fits into 13X13 square"<<endl;
  else
    cout<<"BBox contained in 13X13 square: "<<bbox_13X13<<endl;

  return 0;
}


void createPoly(const string& filename, cd_polygon& poly)
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
