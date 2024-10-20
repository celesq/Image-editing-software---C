# Image-editing-software---C
I developed the core functionality of a photo editor using C. The project allowed for advanced image manipulation, including applying filters, resizing, cropping, generating histograms, and an "equalize" function to enhance image contrast. These operations could be applied to both grayscale and colored images. Users could also select specific portions of an image to apply these operations, adding flexibility to the tool. All image handling was done programmatically, with no GUI elements involved, ensuring efficient and flexible image processing.

# How to Use the Image Editor

  # Loading an Image
      Command: LOAD <file>
      Loads an image (PPM/PGM format) into the program. If an image is already loaded, it will be replaced.
      Example: LOAD example.ppm
      Output: Loaded example.ppm or Failed to load example.ppm

  # Selecting a Region

      Command: SELECT <x1> <y1> <x2> <y2>

      Selects a region of the image between the given coordinates. You can specify the top-left and bottom-right corners.

      Example: SELECT 0 0 3 3

      Output: Selected 0 0 3 3 or Invalid set of coordinates

      Select the Entire Image
        Command: SELECT ALL
            Selects the entire image for further operations.
            Output: Selected ALL

  # Cropping the Image
      Command: CROP
      Crops the image to the currently selected region.
      Example: CROP
      Output: Image cropped

  # Applying Filters
      Command: APPLY <filter_name>
      Applies a filter to the selected region of a color image. Available filters: EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR.
      Example: APPLY SHARPEN
      Output: APPLY SHARPEN done or Easy, Charlie Chaplin (if applied to a grayscale image)

  # Generating a Histogram
      Command: HISTOGRAM <max_stars> <bins>
      Generates a histogram for grayscale images. The number of stars (max_stars) and bins (range 2-256) determine the histogram's format.
      Example: HISTOGRAM 32 16
      Output: A histogram or Black and white image needed

  # Equalizing the Image
      Command: EQUALIZE
      Performs histogram equalization on grayscale images.
      Example: EQUALIZE
      Output: Equalize done or Black and white image needed

  # Rotating the Image
      Command: ROTATE <angle>
      Rotates the selected region by a specified angle (+/-90, +/-180, etc.).
      Example: ROTATE 90
      Output: Rotated 90 or The selection must be square

  # Saving the Image
      Command: SAVE <filename> [ascii]
      Saves the current image. Optionally, you can save it in ASCII format by including the ascii parameter.
      Example: SAVE output_image.ppm or SAVE output_image.pgm ascii
      Output: Saved output_image.ppm

  # Exiting the Program
      Command: EXIT
      Ends the program and deallocates all resources.
      Example: EXIT
      Output: No message is shown.
      
# Brief presentation of the implementation
This project implements various image processing operations, including reading, selecting, cropping, applying filters, and saving images. Below is a detailed explanation of how each feature works:

Image Reading
I used two functions to read images, one for binary files and another for ASCII files. If the magic word indicated P4, P5, or P6 (binary formats), I used fread to efficiently store the data in an unsigned char matrix. For ASCII formats, I used fscanf. For PPM images, I multiplied the number of columns by 3 to handle the R, G, and B channels properly. Once read, the files were closed to prevent memory leaks.

SELECT Command
This command allows you to select a portion of the image. If the command was SELECT ALL, the entire image was selected. Otherwise, I read the coordinates (x1, y1, x2, y2) and converted them using atoi. I checked if the selection was valid and displayed an error if not, returning to the previous selection. For PPM images, I handled the selection for each pixel by multiplying the coordinates by 3, ensuring that all color channels were properly selected.

CROP Function
To crop the image, I used an auxiliary matrix with the new dimensions, transferred the cropped content, and then updated the main image matrix.

HISTOGRAM Function
I implemented a frequency vector to count the occurrences of each pixel value in the image. I divided the 256 possible values into bins based on the number of bins chosen (a power of 2). I then calculated the number of stars to display for each bin and printed the result.

EQUALIZE Function
I used a frequency vector again, storing the pixel occurrences. I applied a grayscale equalization formula to each pixel and then updated the image using a clamp function to prevent out-of-range values.

Error Handling and Modularity
To prevent segmentation faults from invalid commands, I used fgets for reading input. Each operation is modularized into separate functions, with the main function only reading commands and calling the appropriate functions. Memory was released within each function after the auxiliary matrices were used.

APPLY Command
This command applies filters using a predefined kernel matrix. After verifying the selection, I adjusted invalid selection coordinates and then applied the kernel for each pixel. For colored images, I applied the kernel separately to the R, G, and B channels. After processing, the values were clamped and transferred back to the main matrix.

ROTATE Function
I implemented functions to rotate the entire image or just a selected area. There are two types of rotation functions: one for grayscale images and another for color images. For color images, I rotated each channel (R, G, B) separately. For full-image rotation, the dimensions were swapped after rotation, while for selections, the region remained square.

SAVE Function
In the save function, I checked the file format and updated the magic word accordingly. The matrix was saved using fprintf for ASCII files and fwrite for binary files. The file was then closed to prevent memory leaks.

EXIT Function
The EXIT command stopped the main loop by setting the continue variable to false, and all allocated memory used for image processing was freed.
