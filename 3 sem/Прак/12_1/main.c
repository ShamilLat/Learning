STYPE bit_reverse(STYPE value)
{
    UTYPE num2 = 1;
    STYPE size = 0;
    while (num2 != 0) {
        num2 = num2 << 1;
        size++;
    }
    num2 = 0;
    for (int i = 0; i < size; i++) {
        num2 = num2 << 1;
        num2 += ((UTYPE)value) % 2;
        value = ((UTYPE)value) >> 1;
    }
    return (STYPE)num2;
}
