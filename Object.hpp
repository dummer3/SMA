#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object
{
    public:
        virtual void action() = 0;
};

class PlacableObject : public Object
{
    private:
        int x;
        int y;
    
    public:
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        virtual void action() = 0;

};

// TODO: Other objects


#endif // OBJECT_HPP