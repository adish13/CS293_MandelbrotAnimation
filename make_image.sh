# building image for mandel
# arguments are width,height,coordinates and magnification
x_coord=-0.743643887037158704752191506114774
y_coord=0.131825904205311970493132056385139
executables/mandel 1920 1080 $x_coord $y_coord 100 > out.ppm
convert out.ppm -format png mandel.png
rm out.ppm
