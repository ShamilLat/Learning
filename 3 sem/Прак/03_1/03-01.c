int
bitcount(STYPE value)
{
    int kol = 0;

    while(value != 0)
    {
        kol += value & 1;
        value = (UTYPE) value >> 1;
    }
    return kol;
}
