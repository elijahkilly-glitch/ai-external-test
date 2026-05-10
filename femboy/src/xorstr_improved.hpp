#pragma once

/*
 * XOR string encoding for anti-analysis
 * Strings are encoded at compile time and decoded at runtime
 */

template<size_t N>
class xorstr
{
private:
    char data[N];
    size_t size;

    static constexpr char xor_key = 0x42;

public:
    constexpr xorstr(const char(&str)[N]) : size(N - 1)
    {
        for (size_t i = 0; i < N - 1; ++i)
        {
            data[i] = str[i] ^ xor_key;
        }
        data[N - 1] = '\0';
    }

    const char* operator()() const
    {
        static char decoded[256];
        for (size_t i = 0; i < size; ++i)
        {
            decoded[i] = data[i] ^ xor_key;
        }
        decoded[size] = '\0';
        return decoded;
    }
};

template<size_t N>
constexpr xorstr<N> make_xorstr(const char(&str)[N])
{
    return xorstr<N>(str);
}
