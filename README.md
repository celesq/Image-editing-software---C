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
