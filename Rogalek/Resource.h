#ifndef RESOURCE_CLASS_HEADER
#define RESOURCE_CLASS_HEADER
#include <string>

class Resource{
protected:
	
	std::string m_filename;
	int m_handle; //TODO: Mo¿e lepiej tu siê nada unsigned?
	std::string m_name;
	std::string m_path;

public:
	Resource(const int handle, const std::string& name, const std::string& path ="./") //Konstruktor
	{
		m_handle = handle; //"Uchwyt" przyda siê przy zarz¹dzaniu zasobami
		if(!name.empty()) m_name = name;
		if(!path.empty()) m_path = path;
		if(!name.empty() && !path.empty() ) m_filename = path+name;
	}
	virtual ~Resource() //destrukcja konstruktora
	{
	}

	/* Poni¿ej podstawowe funkcje zasobów,
	takie jak zwracanie nazwy, œcie¿ki itp. */
	std::string getName(){return m_name;}
	std::string getPath(){return m_path;}
	std::string getFileName(){return m_filename;}
	unsigned int getHandle(){return m_handle;}
};
#endif