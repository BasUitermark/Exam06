int multi_of_3(unsigned int n)
{
    while (n % 3 != 0)
        n++;
    return n;
}