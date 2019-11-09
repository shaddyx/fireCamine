unsigned int random_number = 0;

unsigned int lfsr16_next(unsigned int n)
{
    return (n >> 0x01U) ^ (-(n & 0x01U) & 0xB400U);
}

void random_init(unsigned int seed)
{
    random_number = seed;
}

unsigned int u_random()
{
	if (random_number == 0 ){
		random_number =0xF400U;
	}
    return (random_number = lfsr16_next(random_number));
}
