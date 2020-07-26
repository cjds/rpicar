/*
 * @author Carl Saldanha <cjds92@gmail.com>
 * @brief Can time functions
 */

template <typename F, typename ... Ts>
double time_function(F&& f, Ts&&...args)
{
    std::clock_t start = std::clock();
    std::forward<F>(f)(std::forward<Ts>(args)...);
    return static_cast<double>(std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
}
