#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <sstream>

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

        float rnd()
        {
            point3d::getBackX;
            point3d::getBackY;
            point3d::getBackZ;

            points_arr.push_back(point3d(random_points_filling()));
        }

        point3d i_point_position(int i)
        {
            if (i < 0 || i >= points_arr.size()) {
                std::cout << "Incorrect index\n";
                return point3d();
            }
            return points_arr[i];
        }

        void new_user_point(double x, double y, double z)
        {
            points_arr.push_back(point3d(x, y, z));
        }

        void write_data_to_file() {
            std::ofstream out;
            out.open("points.txt");
            if (out.is_open())
            {
                for (int i = 0; i < points_arr.size(); i++)
                {
                    out << points_arr[i].x << "\t" << points_arr[i].y << "\t" << points_arr[i].z << "\n";
                }
            }
            out.close();
        }

        void run_visualization() {
            std::stringstream command;
            command << "python visualize.py";
            
            std::cout << "Running: " << command.str() << std::endl;
            int result = system(command.str().c_str());
            
            if (result == 0) {
                std::cout << "Visualization completed" << std::endl;
            } else {
                std::cout << "Visualization error" << std::endl;
            }
        }

        void printPoints() {
            std::cout << "Points in vector (" << points_arr.size() << " points):\n";
            for (auto point : points_arr) {
                point.print();
            }
        }
    
};

int main()
{
    int K;
    double R;
    double r;
    
    int i;

    double x;
    double y;
    double z;

    std::cout << "Enter K\n";
    std::cin >> K;
    std::cout << "Enter R\n";
    std::cin >> R;
    std::cout << "Enter r\n";
    std::cin >> r;

    Figure fig(R, r);
    fig.filling_K(K);
    // fig.printPoints();

    // std::cout << "i point position. Enter index i:\n";
    // std::cin >> i;
    // point3d i_point = fig.i_point_position(i);
    // i_point.print();

    // std::cout << "Enter coords of new point (x, y, z):\n";
    // std::cin >> x >> y >> z;
    // fig.new_user_point(x, y, z);
    // std::cout << "\n";
    // fig.printPoints();

    fig.write_data_to_file();

    fig.run_visualization();

    return 0;
}