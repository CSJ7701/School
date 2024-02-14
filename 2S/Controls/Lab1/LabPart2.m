%% Linear

% Part a
a1=[3,1,2;-1,1,1];
a2=[1;2;1];
% a1.*a2;
% Not possible - array sizes don't match

% Part b
b1=[2,1,0,1;1,0,1,1];
b2=[1;2;1;4];
% b1.*b2;
% Not possible - array sizes don't match

% Part c
c1=[1;2;1];
c2=[3,1,2;-1,1,1];
% c1.*c2;
% Not possible - array sizes don't match

% Part d
d1=[1,0,0;0,1,0;0,0,1];
d2=[1;2;1];
d1.*d2;

%% Transpose
e=[2,-1;1,4;3,2]';
f=[2+j,-4,6;7,8-5j,3;7-j,-7,6+3j]';

%% Inverse
g=[3,-2;-8,-5];
g_inv=inv(g);
h=[2-j,3+j, 1;4,6-8j,0;-1-j,1,4];
h_inv=inv(h);
%% Equality
h*h_inv;
% This gives the identity matrix:
%{
1 0 0
0 1 0
0 0 1
%}

%% Solve
syms x y z
eqn1=x-3*y+2*z==1;
eqn2=2*x+y+11*z==-5;  
eqn3=-3*x+y-z==4;
eqns=[eqn1 eqn2 eqn3];
solve(eqns);
% x=-21/3  y=-12/13  z=-1/13

eqn1=2*x+y+z==1;
eqn2=x+2*y+z==2;
eqn3=-x+4*y==-1;
eqns=[eqn1 eqn2 eqn3];
solve(eqns);
% x=-5/3  y=-2/3  z=5

%% Linear Least Squares
x1=[62,64,66,68,70,72];
y1=[120.5,127.2,137.1,143.3,151.8,161.7];
X1=[ones(length(x1),1),(x1.')];
B1=X1./y1.';
ID1=X1.*B1;
figure(1)
plot(x1,y1,'*',x1,ID1,'-');

x2=[0,1,2,3,4];
y2=[9.1,2.8,1.2,3.1,8.7];
X2=[ones(length(x2),1),(x2.')];
B2=X2./y2.';
ID2=X2.*B2;
figure(2)
plot(x2,y2,'*',x2,ID2,'-');
%% Paragraph Summary
%{
This portion of the lab served to introduce us to basic linear algebra
concepts that we will need throughout the semester as we progress this
class. We were able to practice a variety of techniques for manipulating
matrices and determining their interactions among each other. This exercise
helped us gain experience multiplying matrices, transposing matrices,
finding their inverse, taking the determinants of matrices, and solving
using the method of linear least squares. 

%}