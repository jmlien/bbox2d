#pragma once

#include <Point.h>

namespace masc {
namespace polygon {

  //oritented bounding box (obb)
  struct obb
  {
      obb(){ width=heigh=0; }
      mathtool::Point2d corners[4];
      float width, height;
  };

  class bbox2d_problem
  {
    public:
      //return true if the problem is solved by the given box
      bool solved(const obb& box)=0;
      const obb & getSolution() const { return m_solution; }

    private:
      obb m_solution;
  };

  class bbox2d
  {
  public:

      //initialize with a given polygon
      bbox2d(const c_polygon & poly);

      //build an obb of the provided polygon that solved the given problem.
      //return: obb that solves the given problem.
      obb build(bbox2d_problem & problem);

  private:

      //return the index of the smallest angle
      int findAngles(int e[4], float a[4], const mathtool::Vector2d& v, const mathtool::Vector2d& n);

      //create create OBB
      obb createOBB(int e[4],const mathtool::Vector2d& v, const mathtool::Vector2d& n);

      //data
      vector<mathtool::Poin2d> m_chull; //convex hull of the input poly
  };

  //we now define problems of finding various boudning boxes

  //the problem of finding the minimum area bounding box
  class min_area_bbox : public bbox2d_problem
  {
    public:
      min_area_bbox(){ m_min_area=FLT_MAX; }
      bool solved(const obb& box);
    private:
      float m_min_area;
  };

  //the problem of finding the minimum boundary bounding box
  class min_perimeter_bbox : public bbox2d_problem
  {
    public:
      min_perimeter_bbox(){ m_min_peri=FLT_MAX; }
      bool solved(const obb& box);
    private:
      float m_min_peri;
  };

  //the problem of finding a bounding box that can fit into another box
  class contained_bbox : public bbox2d_problem
  {
    public:
      contained_bbox(float width, float height){m_width=width; m_height=height;}
      bool solved(const obb& box);
    private:
      float m_width, m_height;
  };

}//end namespace polygon
}//end namespace masc
