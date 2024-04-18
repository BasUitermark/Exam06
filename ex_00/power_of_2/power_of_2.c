int pow_of_2(unsigned int n)
{
    return n && !(n & (n - 1));
}