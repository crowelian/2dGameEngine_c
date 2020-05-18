#ifndef ANIMATION.H
#define ANIMATION.H

class Animation {
    public:
        unsigned int index;
        unsigned int numFrames;
        unsigned int animationSpeed;
        Animation();
        Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
};

#endif