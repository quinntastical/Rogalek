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
	std::vector<AnyType*> *s_List; //Lista wskaŸników do zasobów
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
		//SprawdŸmy czy te zmienne przypadkiem nie s¹ puste
		//Zwróæ NULL jeœli zmienne s¹ puste
		if(name.empty() || path.empty() || s_List == NULL || s_List->empty()) return NULL;

		//// Iteracja (taki œredni przyk³ad) by wyszkuaæ zasób
		for(std::vector<AnyType*>::iterator rsrc = s_List->begin(); rsrc !=s_List->end(); rsrc++)
		{
			if((*rsrc) !=NULL)
				if((*rsrc)->getName() == name)
					if((*rsrc)->getPath() == path)
						return (*rsrc);
		}

		//Jeœli nic nie znaleziono o tych parametrach, wówczas:
		return NULL;
	}
	AnyType* getElement(const unsigned int handle)
	{
		if(handle <s_List->size() && handle >= 0) return (*s_List)[handle];
		//Jeœli nic nie znaleziono o tych parametrach, wówczas:
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
			

		while(!s_Handles.empty()) s_Handles.pop(); //jeœli lista uchwytów nie jest pusta, to usuñ element ze stosu

			s_List->clear();
			s_List->swap(*s_List); //trik z odwracaniem wektorów (wyszukane)
	}
	void Remove(const unsigned int handle)
	{
		// Upewnij siê, ¿e lista i zasób s¹ poprawne, bo program siê posypie
		if(handle < 0 || s_List == NULL || handle >= s_List->size() || (*s_List)[handle] == NULL) return;

		AnyType* resource = (*s_List)[handle];

		//faktycznie usuwamy zasób
		s_Handles.push(handle);
		delete resource;
		(*s_List)[handle] = NULL; // Slot ju¿ nie zwraca czegokolwiek wartoœciowego.
	}

	int Add(const std::string& name, const std::string& path = "./" )
	{
		//SprawdŸmy czy te zmienne przypadkiem nie s¹ puste
		//Zwróæ -1 jeœli zmienne s¹ puste
		if (s_List == NULL || name.empty() || path.empty()) return -1;

		AnyType *element = getElement(name, path);
		if(element != NULL) return element->getHandle();

		//Mamy jakiœ wolny uchwyt? Jeœli nie, stwórz go.
		bool handleAvailable = !s_Handles.empty();
		unsigned int handle;
		if (handleAvailable) { handle =s_Handles.top(); s_Handles.pop(); }
		else handle = s_List->size();

		AnyType *resource = NULL;
		if(createResource != NULL){createResource( &resource, handle, name, path);}
		else resource = new AnyType(handle, name, path);

		//Dodaj element do zarz¹dcy - jeœli jest dostêpny uchwyt, to u¿ywamy uchwytu.
		//W innym przypadku dodajemy go do wektora.
		if(handleAvailable){(*s_List)[handle] = resource;}
		else s_List->push_back(resource);

		//zwróæ uchwyt
		return handle;
	}
	AnyType* operator [](unsigned int handle)
	{
		if(handle < s_List->size() && handle >= 0) return (*s_List)[handle];

		return NULL;
	}
};
#endif