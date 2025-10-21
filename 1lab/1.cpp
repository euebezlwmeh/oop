#include <iostream>
#include <random>
#include <vector>
#include <cmath>

struct point3d
{  
    double x,y,z;

    point3d(double x = 0.0, double y = 0.0, double z = 0.0) : 
        x(x), y(y), z(z) {}                                         ///< Конструктор по умолчанию

    void print() const {
         std::cout << "(" << x << ", " << y << ", " << z << ")\n";  ///< Выводит на экран местоположение частиц
    }

    double getBackX() const { return x; }                           ///< Возращает координату X
    double getBackY() const { return y; }                           ///< Возращает координату Y
    double getBackZ() const { return z; }                           ///< Возращает координату Z
};

class Figure
{
    private:
        double R;
        double r;
        double fi = M_PI;
        double psi = M_PI;
        int K;

        static std::mt19937& getGenerator() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return gen;
        }

    public:

        std::vector<point3d> points_arr;

        double getX(double fi, double psi) const {
            return (R + r * cos(psi)) * cos(fi);
        }
        
        double getY(double fi, double psi) const {
            return (R + r * cos(psi)) * sin(fi);
        }
        
        double getZ(double psi) const {
            return r * sin(psi);
        }

        Figure(double R = 3.0, double r = 1.0) : R(R), r(r) {}

        point3d random_points_filling()
        {
            double x = getX(fi, psi);
            double y = getY(fi, psi);
            double z = getZ(psi);
            
            std::uniform_real_distribution<double> xDist(-x, x);
            std::uniform_real_distribution<double> yDist(-y, y);
            std::uniform_real_distribution<double> zDist(0, z);

            double x_point = xDist(getGenerator());
            double y_point = yDist(getGenerator());
            double z_point = zDist(getGenerator());

            return point3d(x_point, y_point, z_point);
        }
        
        void filling_K(int K)
        {
            for (int i = 0; i < K; i++)
            {
                points_arr.push_back(point3d(random_points_filling()));
            }
        }

        float rnd(int K)
        {
            point3d::getBackX;
            point3d::getBackY;
            point3d::getBackZ;

            points_arr.push_back(point3d(random_points_filling()));
        }

        void printPoints() const {
            std::cout << "Points in vector (" << points_arr.size() << " points):\n";
            for (const auto& point : points_arr) {
                point.print();
            }
        }
    
};

int main()
{
    int K;
    double R;
    double r;

    std::cout << "Enter K\n";
    std::cin >> K;
    std::cout << "Enter R\n";
    std::cin >> R;
    std::cout << "Enter r\n";
    std::cin >> r;

    Figure fig(R, r);
    fig.filling_K(K);
    fig.printPoints();

    return 0;
}