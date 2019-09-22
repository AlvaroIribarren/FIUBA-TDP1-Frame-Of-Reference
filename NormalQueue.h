//
// Created by alvaro on 22/9/19.
//

#ifndef FRAMEOFREFERENCE_COLA_H
#define FRAMEOFREFERENCE_COLA_H
#include <string>
#include "Nodo.h"

/*
 * Una NormalQueue es una estructura dinámica de datos organizada de acuerdo al
 * principio FIFO (First In - First Out).
 *
 * El primer elemento en entrar es el primer elemento en salir.
 *
 * Sólo permite el acceso al elemento que denomina frente.
 *
 */
template<class T> class NormalQueue {

private:

    Nodo<T>* frente;

    Nodo<T>* fondo;

public:

    /*
     * post: instancia de NormalQueue vacía y lista para ser usada.
     */
    NormalQueue();

    /*
     * post: devuelve si la NormalQueue no tiene ningún elemento.
     */
    bool isEmpty();

    /*
     * post: agrega 'elemento' en el fondo de la NormalQueue.
     */
    void push(T element);

    /*
     * pre : la NormalQueue no está vacía.
     * post: remueve el frente de la NormalQueue y lo devuelve.
     */
    T pop();

    /*
     * pre : la NormalQueue no está vacía.
     * post: devuelve el frente de la NormalQueue.
     */
    T getFront();

    /*
     * post: remueve todos los elementos y libera
     *       los recursos tomados por la estructura de datos.
     */
    ~NormalQueue();
};

template<class T>
NormalQueue<T>::NormalQueue() {

    this->frente = NULL;
    this->fondo = NULL;
}

template<class T>
bool NormalQueue<T>::isEmpty() {

    return (this->frente == NULL);
}

template<class T>
void NormalQueue<T>::push(T element) {

    Nodo<T>* nuevoFondo = new Nodo<T>(element);

    if (this->isEmpty()) {
        this->frente = nuevoFondo;

    } else {
        this->fondo->cambiarSiguiente(nuevoFondo);
    }

    this->fondo = nuevoFondo;
}

template<class T>
T NormalQueue<T>::pop() {

    if (this->isEmpty()) {
        throw std::string("No se puede desacolar, la cola está vacía.");
    }

    /* remueve el frente de la estructura */
    Nodo<T>* frenteAnterior = this->frente;
    this->frente = frenteAnterior->obtenerSiguiente();

    if (this->frente == NULL) {
        this->fondo = NULL;
    }

    /* devuelve el elemento y libera los recursos asociados */
    T elemento = frenteAnterior->obtenerDato();
    delete frenteAnterior;

    return elemento;
}

template<class T>
T NormalQueue<T>::getFront() {

    if (this->isEmpty()) {
        throw std::string("No se puede obtener el frente, la cola está vacía.");
    }

    T elemento = this->frente->obtenerDato();

    return elemento;
}

template<class T>
NormalQueue<T>::~NormalQueue() {

    while (!this->isEmpty()) {
        this->pop();
    }
}

#endif //FRAMEOFREFERENCE_COLA_H
