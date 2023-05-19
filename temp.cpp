#include <iostream>

int main()
{
    int result = [](int n, auto &&f)
    { return (n == 0 || n == 1) ? 1 : n * f(n - 1, f); }(5, [](int n, auto &&f)
                                                         { return (n == 0 || n == 1) ? 1 : n * f(n - 1, f); });

    std::cout << "Factorial: " << result << std::endl; // Output: Factorial: 120

    return 0;
}
