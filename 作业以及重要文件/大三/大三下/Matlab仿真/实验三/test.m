t=0:0.01:3*pi;
x=t.^3.*sin(3.*t).*eps.^-t;
y=t.^3.*cos(3.*t).*eps.^-t;
z=t.^2;
plot3(x,y,z);


[x,y]=meshgrid(-3:0.1:3,-2:0.1:2);
a=x.^2+2.*x;
b=eps.^(-(x.^2)-(y.^2)-(x.*y));
c=a.*b;
surf(x,y,c);
shading flat;

