# bbox2d
C++ code that solves several 2D bounding box problems using rotating calibers algorithm
  - bounding box with minimal area
  - bounding box with minimal perimeter
  - bounding box that fits into a given rectangle

## Examples
  - **build**
  
  > mkdir build
  
  > cd build
  
  > cmake ..
  
  > make
  
  
  This creates bbox2d in _build_ folder and libbbox2dlib.a in _build/src_ folder
  
  - **command**: 
  > bbox2d ../examples/dragon.poly

  - **output**:

| Left: Minimum area bounding box        | Right: Minimum perimeter bounding box           | 
| ------------- |:-------------:|
| <img width=450 src="./examples/dragon-min-area.png">      | <img width=450 src="./examples/dragon-min-perimeter.png"> |







