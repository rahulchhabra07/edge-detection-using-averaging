# edge-detection-using-averaging
The program is basically a novel method for edge detection using alternate matrix averaging technique.

The code uses OpenCV to access the pixel values in the matrices of the RGB image.

Techniques employed -

Initially, a mask is made which is called Grayscale Edge Matrix.

The Grayscale Edge Matrix is made by storing the pixel-by-pixel data of the target image using the folowing function: 

if the (i + j) % 3 value i.e. (coordinate sum) % 3 == 0 , Red pixel value is stored. Similarly for 1 and 2 mod 3, Green and Blue values are stored in the Grayscale Edge Matrix.

The matrix is then converted into an RGB image by reading the value of the pixel and averaging the other two values from its neighbours. Leading to nearly same values as the original image in the same color region but a different value on the edges as the neighbourhood has different values on edges.

Finally, the re-evaluated RGB image is subtracted from the original image and the resultant is multiplied to a small constant, say 5 to get the edge image.

For using the code, download the latest version of OpenCV.

make
./a

Cheers, 

airsig (Saurabh Dabral, Rahul Chhabra, Archit Jain)
