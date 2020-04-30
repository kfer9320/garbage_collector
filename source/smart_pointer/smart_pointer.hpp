// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <iostream>
#include "RefCount.hpp"


using namespace std;
/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  RefCount*ref; 


 public:
  /* Constructor: SmartPointer(Type* resource=NULL)
   * Uso: SmartPointer<string> myPtr(new string);
   *      SmartPointer<string> myPtr;
   * ------------------------------------------------------------
   * Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso también podría ser NULL lo que ocasionaría que el
   * recurso no administre ningún recurso.
   */
  explicit SmartPointer(Type *resource = nullptr) {
  		//cout<<"falle aqui 1"<<endl;
  		resource_ = resource;
  		ref = new RefCount();
  		//ref = 0; //inicializamos el contador;
  		
  		if(resource_){
  			
  			
  			(*ref)++;
  			//cout<<"holaaa"<<endl;
  		}
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() {
  		std::cout<<"llamado al destructor"<<endl;
  		(*ref)--;
  		
  		if(ref->getCount()==0){
  			delete ref;
  			delete resource_;
  			

  		}


  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { 
  	

  	return *resource_;
  }

  Type *operator->() const { 

  	return resource_; 
  }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) {
  	cout<<"falle aqui 2"<<endl;
    if(resource_ == other.resource_)
	    return *this;

    (*(ref))--;
    if(ref->getCount()==0)
	{
		delete ref;
		delete resource_;
	}    	
    
    resource_=other.resource_;
    ref = other.ref;
    if(resource_)
    {
    	(*ref)++;
    }
    
    	
    

	return *this;    


  }

  SmartPointer &operator=(Type *other) {
  	//cout<<"falle aqui 3"<<endl;
    (*(ref))--;
    if(ref->getCount()==0)
	{
		delete ref;
		delete resource_;
	}    	

    	
    	resource_=other;
    	ref = new RefCount();
    	if (resource_)
    	{
    		(*ref)++;
    	}
    	
    	
    

	return *this;   



  }
  SmartPointer(const SmartPointer &other) {
  	resource_ = other.resource_;
  	ref = other.ref;
  	(*ref)++;


  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { 
  	return ref->getCount(); 
  }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
  	
      
      if (ref->getCount() == 0) {
        delete resource_;
        delete ref;
      }
    	
  }
  
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
