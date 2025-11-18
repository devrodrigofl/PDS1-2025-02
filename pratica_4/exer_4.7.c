float arredonda(float num) {
    if (num > 0) {
        num = (int)(num + 0.5);
    } else {
        num = (int)(num - 0.5);
    }
    return num;
}