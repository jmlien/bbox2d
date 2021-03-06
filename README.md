# bbox2d
C++ code that solves several 2D bounding box problems using the **rotating calipers algorithm**
  - bounding box with minimal area
  - bounding box with shortest perimeter
  - bounding box that fits into a given rectangle

Runs in _O(n)_ for a polygon with _n_ vertices
<img width="200" src="./examples/tw.gif">

## Examples
  - **build**
  ```
  > mkdir build
  > cd build
  > cmake ..
  > make
  ```
  
  This creates bbox2d in _build_ folder and libbbox2dlib.a in _build/src_ folder
  
  - **command**: 
  `> bbox2d ../examples/dragon.poly`

  - **output**:
  
_notice the slight difference near the foot of the dragon._

| Left: Minimum area bounding box        | Right: Minimum perimeter bounding box           | 
| ------------- |:-------------:|
| <img width=450 src="./examples/dragon-min-area.png">      | <img width=450 src="./examples/dragon-min-perimeter.png"> |







