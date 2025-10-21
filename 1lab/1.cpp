#include <iostream>
#include <random>

struct point3d
{  
    double x,y,z;

    point3d(double x=0.0, double y=0.0, double z=0.0)            ///< Конструктор по умолчанию
    {
        x = x;
        y = y;
        z = z;
    }           
    void print() const { std::cout << x << y << z << "\n"; }     ///< Выводит на экран местоположение частиц
    double getBackX() const { return x; }                        ///< Возращает координату X
    double getBackY() const { return y; }                        ///< Возращает координату Y
    double getBackZ() const { return z; }                        ///< Возращает координату Z
};

class Figure
{
    private:
        double R;
        double r;
        double fi;
        double psi;

    static std::mt19937& getGenerator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    public:

        //параметрическое уравнение для рисования тора
        double x = (R + r * cos(psi)) * cos(fi);
        double y = (R + r * cos(psi)) * sin(fi);
        double z = r * sin(psi);

        Figure(double R=3.0, double r=1.0)
        {
            R = R;
            r = r;
        }

        static point3d point_fill(double x, double y, double z)
        {
            point3d point;
            
            std::uniform_real_distribution<double> xDist(-x, x);
            std::uniform_real_distribution<double> yDist(-y, y);
            std::uniform_real_distribution<double> zDist(0, z);

            point.x = xDist(getGenerator());
            point.y = yDist(getGenerator());
            point.z = zDist(getGenerator());
            
        }

    int rnd()
    {
        
    }
    
};

int main()
{
    return 0;
}