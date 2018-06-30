class CTX
{
public:
	CTX(unsigned char*key);
	~CTX();
	unsigned char key[16];
	unsigned char key_1[16];
	unsigned char key_2[16];
	void generate_subkey();
};