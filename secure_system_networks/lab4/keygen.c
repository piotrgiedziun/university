int gen(int arg0, int arg1, int arg2) {
    int var_24 = LODWORD(arg0);
    int var_30 = arg1;
    int var_38 = arg2;
    char[] var_10 = "lrjz1ust0obix7vp6ym9kcd4q3egw8an5h2fxyz";
    char[] var_18 = "2swx9loh3dec8nik4frv7jum5gtb1aqz06py";
    if ((var_24 == 0x0) || (var_24 == 0x1)) {
            var_18 = *tab0;
    }
    var_4 = 0x0;
    do {
            LODWORD(rax) = var_4;
            if (rax >= var_38) {
                break;
            }
            ...
            temp_2 = LOWORD(var_3C) * LODWORD(0x51eb851f);
            if (LODWORD(LODWORD(LODWORD(HIDWORD(temp_2)) >> 0x5) & 0x1) == 0x0) {
                    *(int8_t *)(var_4 + var_30) = LOBYTE(
                        *(int8_t *)(var_8 + var_18) & 0xff);
            }
            else {
                    *(int8_t *)(var_4 + var_30) = LOBYTE(*(int8_t *)(
                        LODWORD(LODWORD(0x23) - var_8) + var_18) & 0xff);
            }
            var_4 = var_4 + 0x1;
    } while (true);
    return rax;
}