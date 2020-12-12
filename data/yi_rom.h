#include <string>
#include <fstream>
#include <iostream>

class yi_rom_t {
private:
	bool m_has_header;
	char *m_rom_data;
	ssize_t m_rom_sz;

	std::string m_filename;
public:
	yi_rom_t(const std::string& filename);
	~yi_rom_t();
	const char * rom_data() const;
};
