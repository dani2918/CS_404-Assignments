(* Mathematica file for 2 layer NN *)
(* define some helper functions *)
In[34]:= second[x_]:=x[[2]]
pm[x_]:=Print[MatrixForm[x]]
size[x_]:=Print[Dimensions[x]]

(* A simple evaluation function of 3 variables and 2 local variables h and y*)
forward[x_, v_, w_]:=Module[{h, y},
h= x . v;
h = Map[tf, h, {2}];
(* hidden nodes for each input *)
h= Map[Append[#, -1] & , h];
y = h . w;
y = Map[tf, y, {2}];
y]   (* returns y *)

(* MultiLayer Perceptron *)
(* or functions: x is input, t is target *)x = {{0,0}, {0, 1}, {1, 0},{1, 1}};
t = {{0, 1, 0},{ 1, 1,1}, {1, 1,1},{1, 0, 0}};
t = {{0},{1},{1},{0}};
inD = Length[First[x]];
outD = Length[First[t]];
hSize = 2;
spread = .7;
v= RandomReal[{-spread, spread}, {inD+1,hSize}];
w = RandomReal[{-spread, spread}, {hSize+1,outD}];
slope = 4;
tf[z_]:=N[1/(1+Exp[-4*slope*z])];

x= Map[Append[#, -1] & , x];
xx = x;
tt = t
Do[r = RandomInteger[{1, Length[xx]}];

(* 1 based indexing of arrays. Braces take row and make it an row in a matrix. *)
(* comment out next 2 lines for batch mode *)
(* x = {xx[[r]]}; 
t=  {tt[[r]]}; *)

(* FORWARD *)
h= x . v;
h = Map[tf, h, {2}]; 
h= Map[Append[#, -1] & , h];
y = h . w;
y = Map[tf, y, {2}];

(* BACKWARD *)
dy = (y - t) y (1 - y);
dh = h (1-h)(dy . Transpose[w]);

(* UPDATE *)
eta = .1;
(* now adjust w after using it *)
w-= eta*(Transpose[h] . dy);
dh = Map[Drop[#, -1]&, dh];
v-= eta*(Transpose[x] . dh);
, 100000]

(* print input translated by NN *)
pm[forward[xx, v, w]]

(* how far off were we? *)
EuclideanDistance[forward[xx, v, w], tt]
