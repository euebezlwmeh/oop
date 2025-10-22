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

        point3d get_torus_point(double u, double v) const {
            double x = (R + r * cos(v)) * cos(u);
            double y = (R + r * cos(v)) * sin(u);
            double z = r * sin(v);
            return point3d(x, y, z);
        }

        Figure(double R = 3.0, double r = 1.0) : R(R), r(r) {}

        point3d random_point_on_torus() {
            std::uniform_real_distribution<double> uDist(0, 2 * M_PI);
            std::uniform_real_distribution<double> vDist(0, M_PI);
            
            double u = uDist(getGenerator());
            double v = vDist(getGenerator());
            
            return get_torus_point(u, v);
        }

        point3d rnd()
        {
            std::uniform_real_distribution<double> uDist(0, 2 * M_PI);
            std::uniform_real_distribution<double> vDist(0, M_PI);
            std::uniform_real_distribution<double> radiusDist(0, r);
            
            double u = uDist(getGenerator());
            double v = vDist(getGenerator());
            double random_r = radiusDist(getGenerator());
            
            double x = (R + random_r * cos(v)) * cos(u);
            double y = (R + random_r * cos(v)) * sin(u);
            double z = random_r * sin(v);
            
            return point3d(x, y, z);
        }
        
        void filling_K(int K)
        {
            for (int i = 0; i < K; i++)
            {
                points_arr.push_back(point3d(rnd()));
            }
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

        void write_parameters_to_file(int K, double R, double r) {
            std::ofstream out;
            out.open("setting.dat");
            if (out.is_open())
            {
                out << "K: " << K << "\n" << "R: " << R << "\n" << "r: " << r << "\n";      
            }
            out.close();
        }

        void printPoints() {
            std::cout << "Points in vector (" << points_arr.size() << " points):\n";
            for (auto point : points_arr) {
                point.print();
            }
        }
    
};

int menu_func(int choise)
{
    std::cout << "Menu:\n" 
            << "1. i point coords\n"
            << "2. Add new point\n"
            << "3. Save data in points.txt\n"
            << "4. Save parameters in setting.dat\n"
            << "5. Visualization (matplotlib)\n"
            << "0. Exit\n"
            << "Enter your choise: ";

    std::cin >> choise;
    return choise;
}

int main()
{
    int K;
    double R;
    double r;

    int choise;
    
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

    while (choise != 0) {

        choise = menu_func(choise);

        switch (choise)
        {
            case 1: {
                std::cout << "i point position. Enter index i:\n";
                std::cin >> i;
                point3d i_point = fig.i_point_position(i);
                i_point.print();
                std::cout << "\n";
                break;
            }
            case 2: {
                std::cout << "Enter coords of new point (x, y, z):\n";
                std::cin >> x >> y >> z;
                fig.new_user_point(x, y, z);
                std::cout << "\n";
                break;
            }
            case 3: {
                fig.write_data_to_file();
                std::cout << "\n";
                break;
            }
            case 4: {
                fig.write_parameters_to_file(K, R, r);
                std::cout << "\n";
                break;
            }
            case 5: {
                fig.run_visualization();
                std::cout << "\n";
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                std::cout << "Incorrect choise\n";
                break;
            }
        }
    }

    return 0;
}