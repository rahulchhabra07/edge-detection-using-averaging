# edge-detection-using-averaging
The program is basically a novel method for edge detection using alternate matrix averaging technique.

The code uses opencv to access the pixel values in the matrices of the rgb image.
Techniques employed -

Initially a mask is made which i call say the grayscale edge matrix,

The grayscale edge matrix is made by storing the pixel by pixel data of the target image using the folowing function - 

if the (i+J) %3 value i.e. (coordinate sum)%3 == 0 , redpixel value is stored similarly for 1 and 2 , green and blue values are stored in the grayscale edge matrix.

the matrix is th ereconverted into an rgb image by reading the value of the pixel and averaging the other two values from it's neighbours. leading to nearly same values as the original image in the same color region but a different value on the edges as the neighbourhood has different values on edges.

finally the re-evaluated rgb image is subtracted from the original image and the resultant is multiplied to a small constant say 5 to get the edge image.

for using the code download the latest version of opencv 

make

./a

cheers, 

airsig
