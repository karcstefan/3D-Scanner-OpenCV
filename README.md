##3D Scanner using OpenCV  / Qt

The 3D Scanner uses the triangulation method to determine the shape of the object. A laser line is used to mark the subject and the camera to capture the movement.The key point is the position that the laser emitter, camera and the subject are placed which they form a triangle, hence the name of the method.
Parameters that are known: the angle of the laser emitter relative to the camera position, the distance between the camera and laser emitter.
The OpenCV library is used to analyse the images/videos, and to filter out the noise so the shape can be analyzed according to the laser line. For easier filtering the HSV color format is used.

![3D Scanner](http://i.imgur.com/jYG66N2.png)
![3D Scanner](http://i.imgur.com/Gsd1g7K.png)
