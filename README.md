# BicubicBSpline
The aim of this assessment was to produce a program to generate and display cubic and bicubic B-splines to represent curves and surfaces respectively. All three parts of the assessment have been completed successfully. The amount of replicated code in the program could be substantially reduced by adding polymorphism to the curve and surface classes.
 
#Program Features
Curves
The program can generate a cubic B-spline curve, which is represented by either one, two or three component functions of one control parameter. The curve is displayed alongside individual views of its component functions. The control points of the curve can be displayed, and the current control point can be highlighted. Control points can be edited using the mouse, and inserted or deleted as required. The control points defining a curve can be preset or cleared, or read from and written to a data file. Animation allows the path of a curve to be traced out according to its control parameter. A curve, which is defined by three component functions, can be rotated or spun in three dimensions.
Surfaces
The program can generate a bicubic B-spline surface, which is represented by either one or three component functions of two control parameters. The control points of the surface can be displayed, and the current control point can be highlighted. Control points can be edited using the mouse, and rows and columns of control points can be inserted and deleted as required. The control points defining a surface can be preset or cleared, or read from and written to a data file. The surface can be displayed in either a solid or wireframe mode. A surface, which is defined by three components, can be displayed together with its convex hull, and with a set of axes attached to the current control point. The surface is rendered with ambient, diffuse and specular lighting, as determined by the computed normals to the surface. The surface can be coloured according to its patches, or texture mapped. To improve the update rate, the matrices defining a patch, and the tiles produced by the subdivision of a patch are recomputed only when a relevant control point is edited. Any surface can be rotated or spun in three dimensions. A surface, which is defined by three components, can be output to a data file, which is suitable as the input to a ray-tracer. This data file includes the camera, lights, bounding boxes and meshes of vertices, normals and faces. The resolution of the subdivision of a patch can be adjusted to suit the required rendering speed and quality.
#Method Tests
The method for creating B-splines is tested by evaluating a cubic function at several points, and determining the B-spline function that corresponds to these control points. This B-spline function is evaluated at both end points of each of its sections, and these values are compared with weighted sums of the three nearest control points. This gives a maximum absolute error of 1.66533e-016, and the results are shown in appendix 2. All the other methods in the program were tested purely through visual inspection of the generated images.
#Method Descriptions
Curves y = f(x)
The Curve class includes the vertex() method, which is used to return the value of a cubic B-spline curve at a point x. The required section of the spline i, and the control parameter for this section s, are determined using the method t(). The control parameter s, and the basis matrix a[][], are used to determine the blending functions b. These blending functions b are applied to the array of control points, which are accessed through the method f(). The products are summed into the result point, which is divided by 6.0 and returned.
 
 

 

#Appendix 1: User Guide
The program is run from the command line as “BicubicBSpline.exe”. The following menu details the use of the mouse and
keyboard.

Escape
Exit Program
F1
1D Curve
F2
2D Curve
F3
3D Curve
F4
1D Surface
F5
3D Surface
F6
Preset Curve or Surface
F7
Read Curve or Surface
F8
Clear Curve or Surface
F9
Spin (3D Curve, 1D Surface, 3D Surface only)
F10
Change Spin Axis (3D Curve, 1D Surface, 3D Surface only)
F11
Stop Spin (3D Curve, 1D Surface, 3D Surface only)
1
Markers
2
Hull (3D Surface)
3
Axes (3D Surface only)
4
Wireframe (3D Surface only)
5
Solid (3D Surface only)
6
Texture (3D Surface only)
7
Animate (1D Curve, 2D Curve, 3D Curve only)
8
Write Curve or Surface
9
Ray-Trace (3D Surface only)
Enter
Rotate (3D Curve, 1D Surface, 3D Surface only)
Insert
Insert
Delete
Delete
Left or Down
Previous
Right or Up
Next
Home or Page Down
First
End or Page Up
Last
< or >
Tiles (3D Surface only)
Left Mouse Button
X and Y Coordinates
Right Mouse Button
Z Coordinate


#Appendix 2: Method Tests
The cubic function was evaluated for 11 values of x

    y = (((((a * x) + b) * x) + c) * x) + d

    a = 0.5
    b = -0.25
    c = 0.5
    d = 0.25

The corresponding B-spline function was evaluated at the end points of each of its sections
These values were compared with the relevant weighted sums of the cubic function

    y = (y0 + 4.0 * y1 + y2) / 6.0
    y = (y1 + 4.0 * y2 + y3) / 6.0

The errors between the weighted sums and the B-spline function were evaluated

    x = -1       y = -1         weighted sum = -0.927667  B-spline = -0.927667  error = 0
    x = -0.8     y = -0.566     weighted sum = -0.585333  B-spline = -0.585333  error = 0
    x = -0.8     y = -0.566     weighted sum = -0.585333  B-spline = -0.585333  error = 0
    x = -0.6     y = -0.248     weighted sum = -0.263333  B-spline = -0.263333  error = 0
    x = -0.6     y = -0.248     weighted sum = -0.263333  B-spline = -0.263333  error = 0
    x = -0.4     y = -0.022     weighted sum = -0.0333333 B-spline = -0.0333333 error = -7.63278e-017
    x = -0.4     y = -0.022     weighted sum = -0.0333333 B-spline = -0.0333333 error = -7.63278e-017
    x = -0.2     y = 0.136      weighted sum = 0.128667   B-spline = 0.128667   error = -2.77556e-017
    x = -0.2     y = 0.136      weighted sum = 0.128667   B-spline = 0.128667   error = -2.77556e-017
    x = 0        y = 0.25       weighted sum = 0.246667   B-spline = 0.246667   error = -5.55112e-017
    x = 0        y = 0.25       weighted sum = 0.246667   B-spline = 0.246667   error = -5.55112e-017
    x = 0.2      y = 0.344      weighted sum = 0.344667   B-spline = 0.344667   error = -1.66533e-016
    x = 0.2      y = 0.344      weighted sum = 0.344667   B-spline = 0.344667   error = -1.66533e-016
    x = 0.4      y = 0.442      weighted sum = 0.446667   B-spline = 0.446667   error = -5.55112e-017
    x = 0.4      y = 0.442      weighted sum = 0.446667   B-spline = 0.446667   error = -5.55112e-017
    x = 0.6      y = 0.568      weighted sum = 0.576667   B-spline = 0.576667   error = 0
    x = 0.6      y = 0.568      weighted sum = 0.576667   B-spline = 0.576667   error = 0
    x = 0.8      y = 0.746      weighted sum = 0.758667   B-spline = 0.758667   error = 0
    x = 0.8      y = 0.746      weighted sum = 0.758667   B-spline = 0.758667   error = 0
    x = 1        y = 1          weighted sum = 0.957667   B-spline = 0.957667   error = 0

The maximum absolute error was 1.66533e-016
