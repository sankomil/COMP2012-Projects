#ifndef PICTURE_H
#define PICTURE_H

class Picture_Pair;                             // Forward declaration. Picture_Pair
                                                // is used in conversion constructor
class Picture
{
private:
  int width {0};                                // Width
  int height {0};                               // Height
  char** pix {nullptr};                         // Character picture. 2D char array

public:
  Picture() = default;                          // Default constructor

  Picture(const Picture& p);                    // Copy constructor. Deep copy

  // Read a character picture from a file
  Picture(const char* filename);                // Conversion constructor

  // Convert Picture_Pair to side-by-side Picture so that the Picture
  // pointed to by pp[0] is on the left of the Picture pointed to by pp[1]
  Picture(const Picture_Pair& pp);              // Conversion constructor

  // Destructor: should release all previously dynamically allocated memory
  ~Picture();                           

  // Frame the character picture with the symbol with frame_width 
  void frame(char symbol, int frame_width);

  void draw() const;                            // Draw the picture to the screen
};

#endif