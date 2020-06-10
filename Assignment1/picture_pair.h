#ifndef PICTURE_PAIR_H
#define PICTURE_PAIR_H

class Picture;                              // Forward declaration. Picture
                                            // is used in general constructor

class Picture_Pair
{
private:
  Picture* pp[2] {nullptr, nullptr};        // Pointers to the two Pictures

public:
  Picture_Pair() = default;                 // Default constructor

  Picture_Pair(const Picture_Pair& pp);     // Copy constructor. Shallow copy

  // Add the Pictures. 
  // pp[0] contains p1, pp[1] contains p2
  Picture_Pair(Picture* p1, Picture* p2);   // General constructor. Shallow copy 

  // Destructor: Don't destruct the Picture it contains
  ~Picture_Pair();                          

  Picture* get_picture(int n) const;        // Get one of the two Pictures.
                                            // Return nullptr if n is neither 0 nor 1

  // Draw the Pictures to screen with the Picture pointed
  // to by pp[0]  on top of the Picture pointed to by pp[1]
  void draw() const;                        
};

#endif