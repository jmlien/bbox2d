#include "bbox2d.h"
#include "chull.h"

//initialize with a given polygon
bbox2d::bbox2d(const c_polygon & poly)
{
  c_poly& ply=poly.front();
  hull2d(ply.getHead(), ply.getHead()->getPre(), this->m_chull );
}

obb bbox2d::build(bbox2d_problem & problem)
{
  mathtool::Vector2d v,n;
  int e[4]; //vertex indices of extreme points
  float a[4]; //angles
  int w; //index (0~3), so that e[w] has the smallest value a[w]
  int hullsize=m_chull.size();

  //init extreme points
  e[0]=0;
  v=(m_chull[1]-m_chull[0]).normalize();
  n.set(-v[1],v[0]);
  const mathtool::Vector2d v0=v;

  float max_v=-FLT_MAX, min_v=FLT_MAX, max_n=-FLT_MAX;
  for(int i=2;i<hullsize;i++)
  {
    auto& pt=m_chull[i];
    double dv=(pt-m_chull[0])*v;
    double dn=(pt-m_chull[0])*n;
    if(dv>max_v){ max_v=dv; e[1]=i;}
    if(dv<min_v){ min_v=dv; e[3]=i;}
    if(dn>max_n){ max_n=dn; e[2]=i;}
  }
  w=findAngles(e,a,v,n);

  //update extreme points
  while(v*v0>=0)
  {
    //create a box from v,n,e[4]
    obb box=createOBB(e,v,n);

    //check if this box solve the problem
    if(problem.solved(box)) break;

    //update
    int ne=(e[w]+1)%hullsize;
    mathtool::Vector2d nev=(m_chull[ne]-m_chull[e[w]]).normalize();
    if(w==0 || w==2)
    {
      v=nev;
      n.set(-v[1],v[0]);
    }
    else{
      n=nev;
      v.set(-n[1],n[0]);
    }
    e[w]=ne;

    w=findAngles(e,a,v,n);
  }

  return problem.getSolution(); //done
}

int bbox2d::findAngles
(int e[4], float a[4], const mathtool::Vector2d& v, const mathtool::Vector2d& n)
{
  int size=m_chull.size();
  mathtool::Vector2d u[4];
  for(int i=0;i<4;i++)
    u[i]=(m_chull[(e[i]+1)%size]-m_chull[e[i]]).normalize();

  int w=0;
  a[0]=v*u[0];
  a[1]=n*u[1]; if(a[1]>a[w]){ w=1; } //larger dot product means smaller angle
  a[2]=-(v*u[2]); if(a[2]>a[w]){ w=2; }
  a[3]=-(n*u[3]); if(a[3]>a[w]){ w=3; }

  return w;
}

obb bbox2d::createOBB(int e[4],const mathtool::Vector2d& v, const mathtool::Vector2d& n)
{
  obb box;
  box.corners[0]=m_chull[e[0]] + v*((m_chull[e[1]]-m_chull[e[0]])*v);
  box.corners[3]=m_chull[e[0]] + v*((m_chull[e[3]]-m_chull[e[0]])*v);
  box.corners[1]=m_chull[e[2]] + v*((m_chull[e[1]]-m_chull[e[2]])*v);
  box.corners[2]=m_chull[e[2]] + v*((m_chull[e[3]]-m_chull[e[2]])*v);

  box.width  = fabs((m_chull[e[3]]-m_chull[e[1]])*v);
  box.height = fabs((m_chull[e[1]]-m_chull[e[0]])*n);

  return box;
}

//the problem of finding the minimum area bounding box
bool min_area_bbox::solved(const obb& box)
{
  float area=box.m_width*box.m_height;
  if(area<m_min_area){
    m_min_area=area;
    this->m_solution=box;
  }
  return false; //always return false so search continues;
}

//the problem of finding the minimum boundary bounding box
bool min_perimeter_bbox::solved(const obb& box)
{
  float peri=box.m_width+box.m_height;
  if(peri<m_min_peri){
    m_min_peri=peri;
    this->m_solution=box;
  }
  return false; //always return false so search continues;
}

//the problem of finding a bounding box that can fit into another box
bool contained_bbox::solved(const obb& box)
{
  if(box.m_width<=m_width && box.m_height <= m_height)
    return true;

  if(box.m_height<=m_width && box.m_width <= m_height)
    return true;

  return false;
}
