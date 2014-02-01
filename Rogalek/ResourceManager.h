#ifndef RESOURCEMANAGER_CLASS_HEADER
#define RESOURCEMANAGER_CLASS_HEADER
#include <string>
#include <vector>
#include <stack>
#include "Resource.h"

template <class AnyType>
class ResourceManager{

private:
	std::stack<int> s_Handles;
	std::vector<AnyType*> *s_List; //Lista wska�nik�w do zasob�w
	void (*createResource)(AnyType **resource, const unsigned int handle, const std::string& name, const std::string& path );

public:
	ResourceManager( void (*createResourceFunction)(AnyType **resource,
		const unsigned int handle, const std::string& name, const std::string& path ) = NULL ) //Konstruktor
	{
		s_List = new std::vector<AnyType*>;

		createResource = createResourceFunction;
	}
	~ResourceManager() //Destruktor
	{
		emptyList();
		delete s_List;
	}
	std::vector<AnyType*> *getList(){return s_List;}
	AnyType* getElement(const std::string& name, const std::string& path = "./" ) 
	{
		//Sprawd�my czy te zmienne przypadkiem nie s� puste
		//Zwr�� NULL je�li zmienne s� puste
		if(name.empty() || path.empty() || s_List == NULL || s_List->empty()) return NULL;

		//// Iteracja (taki �redni przyk�ad) by wyszkua� zas�b
		for(std::vector<AnyType*>::iterator rsrc = s_List->begin(); rsrc !=s_List->end(); rsrc++)
		{
			if((*rsrc) !=NULL)
				if((*rsrc)->getName() == name)
					if((*rsrc)->getPath() == path)
						return (*rsrc);
		}

		//Je�li nic nie znaleziono o tych parametrach, w�wczas:
		return NULL;
	}
	AnyType* getElement(const unsigned int handle)
	{
		if(handle <s_List->size() && handle >= 0) return (*s_List)[handle];
		//Je�li nic nie znaleziono o tych parametrach, w�wczas:
		return NULL;
	}
	void emptyList()
	{
		for(std::vector<AnyType*>::iterator rsrc = s_List->begin(); rsrc !=s_List->end(); rsrc++)
			
			if(*rsrc) //bezpieczne usuwanie
			{
				delete *rsrc;
				(*rsrc) = NULL;
			}
			

		while(!s_Handles.empty()) s_Handles.pop(); //je�li lista uchwyt�w nie jest pusta, to usu� element ze stosu

			s_List->clear();
			s_List->swap(*s_List); //trik z odwracaniem wektor�w (wyszukane)
	}
	void Remove(const unsigned int handle)
	{
		// Upewnij si�, �e lista i zas�b s� poprawne, bo program si� posypie
		if(handle < 0 || s_List == NULL || handle >= s_List->size() || (*s_List)[handle] == NULL) return;

		AnyType* resource = (*s_List)[handle];

		//faktycznie usuwamy zas�b
		s_Handles.push(handle);
		delete resource;
		(*s_List)[handle] = NULL; // Slot ju� nie zwraca czegokolwiek warto�ciowego.
	}

	int Add(const std::string& name, const std::string& path = "./" )
	{
		//Sprawd�my czy te zmienne przypadkiem nie s� puste
		//Zwr�� -1 je�li zmienne s� puste
		if (s_List == NULL || name.empty() || path.empty()) return -1;

		AnyType *element = getElement(name, path);
		if(element != NULL) return element->getHandle();

		//Mamy jaki� wolny uchwyt? Je�li nie, stw�rz go.
		bool handleAvailable = !s_Handles.empty();
		unsigned int handle;
		if (handleAvailable) { handle =s_Handles.top(); s_Handles.pop(); }
		else handle = s_List->size();

		AnyType *resource = NULL;
		if(createResource != NULL){createResource( &resource, handle, name, path);}
		else resource = new AnyType(handle, name, path);

		//Dodaj element do zarz�dcy - je�li jest dost�pny uchwyt, to u�ywamy uchwytu.
		//W innym przypadku dodajemy go do wektora.
		if(handleAvailable){(*s_List)[handle] = resource;}
		else s_List->push_back(resource);

		//zwr�� uchwyt
		return handle;
	}
	AnyType* operator [](unsigned int handle)
	{
		if(handle < s_List->size() && handle >= 0) return (*s_List)[handle];

		return NULL;
	}
};
#endif