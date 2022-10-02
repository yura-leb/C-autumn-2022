#include <map>

template <typename T>
class Vector {
private:
    std::map<int, T> dictionary;
    double eps;
    int len;
public:

    Vector(const Vector& vec);
    Vector(const std::map<int, T>& dictionary, double eps,int begin, int end);
    bool is_zero(T num);


    const T& operator()(int i);
    const Vector operator+(const Vector& right) const;
    const Vector operator-(const Vector& right) const;
};
