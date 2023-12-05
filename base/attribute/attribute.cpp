#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

/* 属性可用于 类 函数 变量 或其他语句的标识
   格式1： [[ attribute-list ]]
   例如：[[ noreturn, gnu::always_inline ]]
   格式2：[[ using attribute-namespace : attribute-list ]]
   如： [[using gnu : const, always_inline, hot]] 等价于 [[gnu::always_inline]] [[gnu::hot]] [[gnu::const]]
*/

/*
系统自带的退出程序函数(Terminating functions)，都带 [[ noreturn ]]
如 
    [[noreturn]] void _Exit( int exit_code ) noexcept;
    [[noreturn]] void abort() noexcept;
    [[noreturn]] void exit( int exit_code );
    [[noreturn]] void quick_exit( int exit_code ) noexcept;
    [[noreturn]] void terminate() noexcept;
*/

/*
deprecated 标记该函数已经被废弃，但目前仍然可以使用 不过使用会有警告
警告的内容可以设置
*/
[[deprecated]]
void TriassicPeriod()
{
    std::clog << "Triassic Period: [251.9 - 208.5] million years ago.\n";
}
 
[[deprecated("Use NeogenePeriod() instead.")]]
void JurassicPeriod()
{
    std::clog << "Jurassic Period: [201.3 - 152.1] million years ago.\n";
}
 
[[deprecated("Use calcSomethingDifferently(int).")]]    
int calcSomething(int x)
{
    return x * 2;
}

/*  [[nodiscard]]
    [[nodiscard( reason )]]	
    声明函数返回值不应该被忽略，并且可以指定不能被忽略的理由
    如标准库中的：allocate 函数
        [[nodiscard]] constexpr T* allocate( std::size_t n );
    已经stl容器的 empty() 函数
*/

/*  [[maybe_unused]]		
    声明参数可能不会被使用
*/
[[maybe_unused]] void f([[maybe_unused]] bool thing1,
                        [[maybe_unused]] bool thing2) {
    [[maybe_unused]] bool b = thing1 && thing2;
    assert(b); // in release mode, assert is compiled out, and b is unused
               // no warning because it is declared [[maybe_unused]]
} // parameters thing1 and thing2 are not used, no warning

/*  [[fallthrough]]
    声明在switch中，case语句故意跳到下一个case，防止编译器报错
*/
void test(int n){
    switch (n)
    {
    case 1:
        [[fallthrough]];    //指明这里并非忘记写 break 而是故意不写
    case 2:
        break;
    default:
        break;
    }
}

/*  [[likely]] [[unlikely]]	可以优化性能(如下面的测试)
*/
namespace with_attributes
{
    constexpr double pow(double x, long long n) noexcept
    {
        if (n > 0) [[likely]]
            return x * pow(x, n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr long long fact(long long n) noexcept
    {
        if (n > 1) [[likely]]
            return n * fact(n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr double cos(double x) noexcept
    {
        constexpr long long precision{16LL};
        double y{};
        for (auto n{0LL}; n < precision; n += 2LL) [[likely]]
            y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
        return y;
    }
} // namespace with_attributes
 
namespace no_attributes
{
    constexpr double pow(double x, long long n) noexcept
    {
        if (n > 0)
            return x * pow(x, n - 1);
        else
            return 1;
    }
    constexpr long long fact(long long n) noexcept
    {
        if (n > 1)
            return n * fact(n - 1);
        else
            return 1;
    }
    constexpr double cos(double x) noexcept
    {
        constexpr long long precision{16LL};
        double y{};
        for (auto n{0LL}; n < precision; n += 2LL)
            y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
        return y;
    }
} // namespace no_attributes

double gen_random() noexcept
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0, 1.0);
    return dis(gen);
}
 
volatile double sink{}; // ensures a side effect

void test1(){
    auto benchmark = [](auto fun, auto rem)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (auto size{1ULL}; size != 10'000'000ULL; ++size)
            sink = fun(gen_random());
        const std::chrono::duration<double> diff =
            std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
                  << " sec " << rem << std::endl; 
    };

    // Time: 0.579122 sec (with attributes)
    benchmark(with_attributes::cos, "(with attributes)");
    // Time: 0.722553 sec (without attributes)
    benchmark(no_attributes::cos, "(without attributes)");
}

/*  [[no_unique_address]]
    声明为不需要地址，可节约空间
*/
struct Empty{};
// sizeof(X) > sizeof(int)
struct X{
    int i;
    Empty e;    //Empty对象也会占用空间
};
// sizeof(Y) == sizeof(int)
struct Y{
    int i;
    [[no_unique_address]] Empty e;    //Empty对象不会占用空间
};

/*  [[assume( expression )]]
    程序对表达式进行确保，类似于assert
*/
void f(int& x, int y){
    void g(int);
    void h();

    [[ assume( x > 0) ]];   // Compiler may assume x is positive

    int z = x;
    [[assume((h(), x == z))]]; //程序确保调用h()后,z依然等于x,但不会真的调用h
    h();

    [[assume((g(z), true))]]; // Compiler may assume g(z) will return
}

int main() {
    TriassicPeriod();
    JurassicPeriod();

    return 0;
}