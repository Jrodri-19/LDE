/*
	AUTOR:
			CALLO HUAYNA, JUAN RODRIGO
*/
#include <iostream>
//-------------------------------------------------------------
//Definición de la clase Node----------------------------------
//-------------------------------------------------------------
template<typename T>
class Node {
public:
//--------Constructor
	Node(T data) : data(data), next(nullptr), prev(nullptr) {}
//--------Destructor
	~Node() {
		// No hay memoria dinamica, no necesita un destructor
	}
//--------Getter y Setter
	//----Data
	T getData() const { return data; }
	void setData(T newData) { data = newData; }
	//----Next
	Node<T>* getNext() const { return next; }
	void setNext(Node<T>* newNext) { next = newNext; }
	//----Prev
	Node<T>* getPrev() const { return prev; }
	void setPrev(Node<T>* newPrev) { prev = newPrev; }

private:
	T data;
	Node<T>* next;
	Node<T>* prev;
};
//-------------------------------------------------------------
//Definición de la clase LinkedList----------------------------
//-------------------------------------------------------------
template<typename T>
class DoubleLinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
public:
//--------Constructor
	DoubleLinkedList() : head(nullptr), tail(nullptr) {}
//--------Destructor
	~DoubleLinkedList() {
		Node<T>* current = head; 	//puntero a mover
		Node<T>* nextNode;			//puntero temporal
		while (current != nullptr) {
			nextNode = current->getNext();	
			delete current;
			current = nextNode;
		}
	}
//--------Métodos
	//---------------------------------------------------------
	//IMPRIMIR-------------------------------------------------
	//---------------------------------------------------------
	//----Método para imprimir la lista
	void print_list() const {
		Node<T>* temp = head;					//puntero temporal
		std::cout << "nullptr" << " <-> "; 		//Es el previus del primer nodo
		while (temp != nullptr) {
			std::cout << temp->getData() << " <-> ";
			temp = temp->getNext();				//recorre temp por la doble lista
		}
		std::cout << "nullptr\n" << std::endl; 	//Es el next del ultimo nodo
	}
	//----Método para imprimir la lista en reversa
	void print_reverse() const{
		Node<T>* temp = tail;					//puntero temporal
		std::cout<<"nullptr"<< " <-> ";  		//Es el next del ultimo nodo
		while (temp != nullptr) {
			std::cout << temp->getData() << " <-> ";
			temp = temp->getPrev();				//recorre temp por la doble lista
		}
		std::cout << "nullptr\n" << std::endl; 	//Es el previus del primer nodo
		return;
	}
	//---------------------------------------------------------
	//INSERTAR-------------------------------------------------
	//---------------------------------------------------------
	// Método para insertar al frente
	void push_front(T data) {
		Node<T>* newNode = new Node<T>(data); 	//Creo un nuevo nodo con el dato
		if(head == nullptr){					//Si no hay ningun nodo
			head = newNode;						//Tanto head como tail apuntan
			tail = newNode;						//al mismo nodo
			return;
		}
												//Si hay más de un nodo
		head -> setPrev(newNode);				//Asigno el previo de head a newNode
		newNode->setNext(head);					//Asigno el next de newNode a head
		head = newNode;							//Asignamos head al nuevo nodo
		return;
	}
	// Método para insertar por atras
	void push_back(T data) {
		Node<T>* newNode = new Node<T>(data);	//Creo un nuevo nodo con el dato
		if(head == nullptr){					//Si no hay ningun dato
			head = newNode;						//Tanto head como tail apuntan
			tail = newNode;						//al mismo nodo
			return;
		}
												//Si hay más de un nodo
		tail -> setNext(newNode);				//Asigno el next de tail a newNode
		newNode->setPrev(tail);					//Asigno el previo de newNode a tail
		tail = newNode;							//Asignamos tail al nuevo nodo
		return;
	}
	//---------------------------------------------------------
	//ELIMINAR-------------------------------------------------
	//---------------------------------------------------------
	// Método para eliminar por frente
	void pop_front() {
		if(head == nullptr ){					//Si no hay ningun nodo
			return;								//Retornar ya que no hay nodo por eliminar
		}
		if(head == tail ){						//Si hay un solo nodo
			Node<T>* temp = head;				//Asigno un puntero que apunte al unico nodo  
			head = nullptr;						//El head apuntando a nulo ya que no habria ningun nodo
			tail = nullptr;						//El tail apuntando a nulo ya que no habria ningun nodo
			delete temp;						//Elimino el unico nodo
			return;
		}
												//Si hay más de un nodo
		Node<T>* temp = head;					//Asigno un temporal para el head(primer nodo)
		head=head->getNext();					//Cambios el head al segundo nodo
		head->setPrev(nullptr);					//Este nuevo head asignamos su previo a nulo
		delete temp;							//Eliminamos el temporal apuntado a al primer nodo
		return;
	}
	// Método para eliminar por atras
	void pop_back() {
		if(head == nullptr ){					//Si no hay ningun nodo
			return;								//Retornar ya que no hay nodo por eliminar
		}
		if(head == tail ){						//Si hay un solo nodo
			Node<T>* temp = tail;				//Asigno un puntero que apunte al unico nodo 
			head = nullptr;						//El head apuntando a nulo ya que no habria ningun nodo
			tail = nullptr;						//El tail apuntando a nulo ya que no habria ningun nodo
			delete temp;						//Elimino el unico nodo
			return;
		}
		//Si hay más de un nodo
		Node<T>* temp = tail;					//Asigno un temporal para el tail(ultimo nodo)
		tail=tail->getPrev();					//Cambios el tail al penultimo nodo
		tail->setNext(nullptr);					//Este nuevo tail asignamos su next a nulo
		delete temp;							//Eliminamos el temporal apuntado a al ultimo nodo
		return;
	}
	//---------------------------------------------------------
	//GETTER---------------------------------------------------
	//---------------------------------------------------------
	// Método para get en front
	T getfront() const {
		try{
			if(head == nullptr){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			return head -> getData();
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en getData(): "<<e.what()<<std::endl;
			return T();
		}
	}
	// Método para get en back
	T getback() const {
		try{
			if(head == nullptr ){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			return tail -> getData();
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en getData(): "<<e.what()<<std::endl;
			return T();
		}
	}
	//---------------------------------------------------------
	//SETTER---------------------------------------------------
	//---------------------------------------------------------
	// Método para set en front
	void setfront(T data) {
		try{
			if(head == nullptr){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			head -> setData(data);
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en setData(): "<<e.what()<<std::endl;
			return;
		}
	}
	// Método para set en back
	void setback(T data) {
		try{
			if(head == nullptr ){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			tail -> setData(data);
			return ;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en setData(): "<<e.what()<<std::endl;
			return ;
		}
	}
	//---------------------------------------------------------
	//COMPROBACION DE LISTA VACIA------------------------------
	//---------------------------------------------------------
	bool empty() {
		if(head == tail && head== nullptr){
			return true;
		}
		return false; 
	}
	//---------------------------------------------------------
	//ELIMINAR TODOS LOS ELEMENTOS-----------------------------
	//---------------------------------------------------------
	void clear(){
		while(!empty()){						//Si no esta vacio, eliminar
			pop_front();
			pop_back();
		}
	}
	//---------------------------------------------------------
	//TAMAÑO-----------------------------
	//---------------------------------------------------------
	int sizeDoubleList(){
		Node<T>* temp = head;
		int contador = 0;
		while(temp != nullptr){
			contador++;
			temp = temp->getNext();	
		}
		return contador;
	}
	//---------------------------------------------------------
	//INSERTAR ELEMENTO----------------------------------------
	//---------------------------------------------------------
	void insert(int index, const T valor) {	//index de 0 a dato
		if (index == 0) {
			push_front(valor);
			return;
		}
		int sizeDL=sizeDoubleList();
		try{
			if(sizeDL<index || index<0){
				throw std::runtime_error("Intento de acceso a fuera de rango");
			}
			Node<T>* newNode = new Node<T>(valor);
			Node<T>* temp = head;
			int contador=0;
			while(contador<index-1){
				temp = temp->getNext();	
				contador++;
			}
			newNode->setNext(temp->getNext());
			newNode->setPrev(temp);
			if (temp->getNext() != nullptr) {
				temp->getNext()->setPrev(newNode);
			}
			temp->setNext(newNode);
			if (newNode->getNext() == nullptr) {
				tail = newNode;
			}
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de insercion: "<<e.what()<<std::endl;
			return;
		}
	}
	//---------------------------------------------------------
	//REMOVER ELEMENTO----------------------------------------
	//---------------------------------------------------------
	void remove(int index) {	//index de 0 a dato
		if (index == 0) {
			pop_front();
			return;
		}
		int sizeDL=sizeDoubleList();
		try{
			if(sizeDL<index || index<0){
				throw std::runtime_error("Intento de acceso a fuera de rango");
			}
			Node<T>* temp = head;
			int contador=0;
			while(contador<index-1){
				temp = temp->getNext();	
				contador++;
			}
			if (temp->getNext() == tail) {
				pop_back();
			}
			else {
				Node<T>* nodeToDelete = temp->getNext();
				temp->setNext(nodeToDelete->getNext());
				nodeToDelete->getNext()->setPrev(temp);
				delete nodeToDelete;
			}
			
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de eliminacion: "<<e.what()<<std::endl;
			return;
		}
	}
	//---------------------------------------------------------
	//BUSQUEDA ------------------------------------
	//---------------------------------------------------------
	Node<T>* busquedaNodoPorDato(const T value) const {
		Node<T>* temp = head;
		while (temp != nullptr) {
			if (temp->getData() == value) {
				return temp; 
			}
			temp = temp->getNext();
		}
		return nullptr;  
	}
	int busquedaIndicePorDato( const T valor) {
		Node<T>* datoEncontrado=busquedaNodoPorDato(valor);
		try{
			if(datoEncontrado==nullptr){
				throw std::runtime_error("Dato no encontrado");
			}
			Node<T>* temp = head;
			int contador = 0;
			while (temp != datoEncontrado) {
				temp = temp->getNext();
				contador++;
			}
			return contador;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de insercion: "<<e.what()<<std::endl;
			return -1;
		}
	}
};

int main() {
	DoubleLinkedList<int>* mi_lista = new DoubleLinkedList<int>;
	//mi_lista->setfront(4);
	//mi_lista->setback(10);
	//mi_lista->remove(2);
	//std::cout<<mi_lista->getfront()<<"\n";
	mi_lista->push_front(1);
	mi_lista->push_front(2);
	mi_lista->push_back(3);
	mi_lista->print_list();
	mi_lista->setfront(4);
	mi_lista->setback(10);
	mi_lista->print_list();
	mi_lista->insert(1, 100);
	mi_lista->print_list();
	mi_lista->remove(2);
	mi_lista->print_list();
	//mi_lista->pop_back();
	//mi_lista->print_list();
	//std::cout<<mi_lista->getfront()<<"\n";
	//std::cout<<mi_lista->getback()<<"\n";
	//std::cout<<mi_lista->empty()<<"\n";
	//mi_lista->clear();
	//std::cout<<mi_lista->empty()<<"\n";
	//std::cout<<mi_lista->sizeDoubleList()<<"\n";
	//std::cout<<(mi_lista->busquedaPorDato(100))->getData();
	//std::cout<<mi_lista->busquedaIndicePorDato(103);
	delete mi_lista;
	
	return 0;
}
