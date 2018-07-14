//
//  LinkedList.cpp
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//
//  Jonathan Zaehringer
//  Jorge-Andre Fulgencio Esteves
//  Florian Schaufelberger
//

#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

/// Forward declaration classe
template < typename T > class LinkedList;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator << (ostream& os, const LinkedList<T>& liste);

/// Classe de liste chainee
template < typename T > class LinkedList {

    /**
     * @brief Surcharge de l'operateur de flux (<size>: <element1> <element2> ...)
     *
     * @param[in,out] os flux de sortie utilise par l'envoi
     * @param[in] liste LinkedList a afficher
     *
     * @return flux de sortie recu pour chainage
     *
     * @remark Complexite de O(n), n etant la taille de la liste
     */
    friend ostream& operator << <T>(ostream& os, const LinkedList<T>& liste);

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

private:
    /**
     *  @brief Maillon de la chaine.
     *
     * contient une valeur et le lien vers le maillon suivant.
     */
    struct Node {
        value_type data;
        Node* next;

        Node(const_reference data, Node* next = nullptr)
            : data(data), next(next) {
                cout << "(C" << data << ") ";
            }

        Node(Node&) = delete;
        Node(Node&&) = delete;

        ~Node()
        {
            cout << "(D" << data << ") ";
        }
    };

private:
    /**
     *  @brief  Tete de la LinkedList
     */
    Node* head;

private:
    /**
     *  @brief Nombre d'elements
     */
    size_t nbElements;

public:
    /**
     *  @brief Constructeur par defaut. Construit une LinkedList vide
     *
     *  @remark Complexite de O(1)
     */
    LinkedList() : head(nullptr), nbElements(0) {
    }

public:
    /**
     *  @brief Constructeur de copie
     *
     *  @param[in] other la LinkedList a copier
     *
     *  @remark Complexite de O(n), n etant la taille de la liste a copier
     */
    LinkedList( const LinkedList& other ) : LinkedList() {
        appendByCopy(other);
    }

public:
    /**
     *  @brief Operateur d'affectation par copie
     *
     *  @param[in] other la LinkedList a copier
     *
     *  @return la LinkedList courante *this (par reference)
     *
     *  @remark l'operateur doit être une no-op si other
     *           est la LinkedList courante.
     *
     *  @remark le contenu precedent de la LinkedList courante est
     *           efface.
     *
     *  @remark Complexite de O(n), n etant la taille de la liste a copier
     */
    LinkedList& operator= ( const LinkedList& other ) {
        if(head == other.head)
            return *this;

        LinkedList<T> tmp(other);

        swap(head, tmp.head);
        swap(nbElements, tmp.nbElements);

        tmp.~LinkedList();

        return *this;
    }

public:
    /**
     *  @brief destructeur
	 *
     *  @remark Complexite de O(n), n etant la taille de la liste a copier
     */
    ~LinkedList() {
        while(head)
            removeNode(&head);
    }

public:
    /**
     *  @brief nombre d'elements stockes dans la liste
     *
     *  @return nombre d'elements.
     *
     *  @remark Complexite de O(1)
     */
    size_t size() const noexcept {
        return nbElements;
    }

public:
    /**
     *  @brief insertion d'une valeur dans un maillon en tête de liste
     *
     *  @param[in] value la valeur a inserer
     *
     *  @exception std::bad_alloc si pas assez de memoire, où toute autre exception lancee par la constructeur de copie de value_type
     *
     *  @remark Complexite de O(1)
     */
    void push_front( const_reference value) {
        head = new Node(value, head);
        ++nbElements;
    }

public:
    /**
     *  @brief accès (lecture/ecriture) a la valeur en tête de LinkedList
     *
     *  @return reference a cette valeur
     *
     *  @exception std::runtime_error si la liste est vide
     *
     *  @remark Complexite de O(1)
     */
    reference front() {
        if(!head) {
            throw std::runtime_error("LinkedList::front");
        }
        return head->data;
    }

    const_reference front() const {
        return static_cast<const_reference>(const_cast<LinkedList*>(this)->front());
    }

public:
    /**
     *  @brief Suppression de l'element en tête de LinkedList
     *
     *  @exception std::runtime_error si la liste est vide
     *
     *  @remark Complexite de O(1)
     */
    void pop_front( ) {
        if(!head) {
            throw std::runtime_error("LinkedList::pop_front");
        }

        removeNode(&head);
    }

public:
    /**
     *  @brief Insertion en position quelconque
     *
     *  @param[in] value la valeur a inserer
     *  @param[in] pos   la position où inserer, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::insert") si pos non valide
     *
     *  @exception std::bad_alloc si pas assez de memoire, où toute autre exception lancee
     *              par la constructeur de copie de value_type
     *
     *  @remark Complexite de O(n), n etant la taille de la liste
     */
    void insert( const_reference value, size_t pos ) {
        if(pos == 0)
            return push_front(value);

        if(!isValidLocationPos(pos))
            throw std::out_of_range("LinkedList::insert");

        Node** tmp = locationAt(pos);

        *tmp = new Node(value, (*tmp));

        nbElements++;
    }

public:
    /**
     *  @brief Acces a l'element en position quelconque
     *
     *  @param[in] pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::at") si pos non valide
     *
     *  @return une reference a l'element correspondant dans la liste
     *
     *  @remark Complexite de O(n), n etant la taille de la liste
     */
    reference at( size_t pos ) {
        if(!isValidElementPos(pos))
            throw std::out_of_range("LinkedList::at");

        return (*locationAt(pos))->data;
    }

    /**
     *  @brief Acces a l'element en position quelconque
     *
     *  @param[in] pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::at") si pos non valide
     *
     *  @return une const_reference a l'element correspondant dans la liste
     *
     *  @remark Complexite de O(n), n etant la taille de la liste
     */
    const_reference at( size_t pos ) const {
        return static_cast<const_reference>(const_cast<LinkedList*>(this)->at(pos));
    }

public:
    /**
     *  @brief Suppression en position quelconque
     *
     *  @param[in] pos la position, 0 est la position en tete
     *
     *  @exception std::out_of_range("LinkedList::erase") si pos non valide
     *
     *  @remark Complexite de O(n), n etant la taille de la liste
     */
    void erase( size_t pos ) {
        if(pos == 0) {
            return pop_front();
        }

        if(!isValidElementPos(pos))
            throw std::out_of_range("LinkedList::erase");

        removeNode(locationAt(pos));
    }

public:
    /**
     *  @brief Recherche du premier element correspondant
     a une valeur donnee dans la liste
     *
     *  @param[in] value la valeur a chercher
     *
     *  @return la position dans la liste. -1 si la valeur n'est pas trouvee
     *
     *  @remark Complexite de O(n), n etant la taille de la liste
     */
    size_t find( const_reference value ) const noexcept {
        Node* current = head;
        size_t pos = 0;

        while(current) {
            if(current->data == value)
                return pos;

            current = current->next;
            ++pos;
        }

        return -1;
    }

    /**
     *  @brief Tri des elements de la liste par tri fusion
     *  
     *  @remark Complexite de O(n*log(n)), n etant la taille de la liste
     */
    void sort() noexcept {
        mergeSort(&head, nbElements);
    }

private:

    /**
     * @brief Test si la position est un element valide
     *
     * @param[in] pos position de l'element entre 0 et nbElements - 1
     */
    bool isValidElementPos(size_t pos) const noexcept{
        return (pos < nbElements);
    }

    /**
     * @brief Test si la position est un emplacement valide
     *
     * @param[in] pos position de l'emplacement entre 0 et nbElements
     */
    bool isValidLocationPos(size_t pos) const noexcept {
        return (pos <= nbElements);
    }

    /**
     * @brief Recuperation de l'emplacement d'une position demande
     *
     * @param[in] pos Position de l'emplacement entre 0 et nbElements
     *
     * @return Adresse du noeud voulu
     *
     * @remark Complexite de O(n), n etant la taille de la liste
     *
     * Fonction pure qui ne test pas les valeurs d'entrés, il est nécessaire
     *  que les testes soit effecutés en amont
     */
    Node** locationAt( size_t pos ) noexcept {
        assert(pos <= nbElements);

        Node** current = &head;

        for(size_t i = 0; i < pos; i++){
            current = &((*current)->next);
        }

        return current;
    }
    /**
     * @brief Copie d'une liste a partir de la position voulu
     *
     * @param[in] other Liste a copier integralement
     *
     * @param[in] pos Position de depart de la copie
     *
     * @exception En provenance de locationAt si pos non valide
     * 
     * @exception std::bad_alloc si pas assez de memoire, où toute autre exception lancee
     *              par le constructeur de copie de value_type
     *
     * @remark Complexite de O(n), n etant la taille de la liste a copie
     */
    void appendByCopy( const LinkedList& other, size_t pos = 0 ) {
        Node** target = locationAt(pos);
        Node* end = *target;
        Node* source = other.head;

        while (source) {
            *target = new Node(source->data);
            target = &(*target)->next;
            source = source->next;
        }

        *target = end; //Rechainage du reste
        nbElements += other.nbElements;
    }
    
    /**
     * @brief Supprime un Node
     *
     * @param[in] pointeur sur l'emplacement du Node
     *
     * @remark Complexite de O(1)
     *
     * Fonction pure qui ne test pas les valeurs d'entrés, il est nécessaire
     *  que les testes soit effecutés en amont
     */
    void removeNode( Node** target ) noexcept {
        assert(*target);

        Node* tmp = *target;
        *target = (*target)->next;
        delete tmp;

        --nbElements;
    }

    /**
     * @brief Trie par fusion
     *
     * @param[in] start Pointeur de pointeur sur un noeud de depart du trie
     * @param[in] size Taille de la liste
     *
     * @return Emplacement de la fin de la chaine
     *
     * @remark Complexite de O(n*log(n)), n etant la taille de la liste
     *          pour l'ensemble du trie
     */
    Node** mergeSort( Node** start, size_t size ) noexcept {
        if(size == 0) return start;
        if(size == 1) return &(*start)->next;

        Node** half = mergeSort(start, size / 2); //trie sur la moitie gauche
        Node** end  = mergeSort(half,size - size / 2); //trie sur la moitie droite

        return merge(start, *half, *end);
    }

    /**
     * @brief Fonction de fusion du trie par fusion
     *
     * @param[in] start pointeur de pointeur sur le depart de la liste
     * @param[in] half  pointeur sur le noeud du milieu
     * @param[in] end   pointeur sur le noeud de fin (hors fusion)
     *
     * @return l'emplacement memoire du dernier noeud (hors fusion)
     *
     * @remark Complexite de O(n), n étant la taille de la liste
     */
    Node** merge( Node** start, Node* half, Node* end ) noexcept {
        Node*  first   = *start, // sentinelle gauche
            *  second  = half,   // sentinelle droite
            ** current = start;

        // Trie des valeurs par rapport au deux sentinelles
        while(first != half && second != end){
            if(first->data < second->data){
                *current = first;
                first = first->next;
            } else {
                *current = second;
                second = second->next;
            }

            current = &(*current)->next;
        }

        // Recopie du reste lorsqu'une sentinelle
        // arrive a la fin
        Node* target;
        if(first == half){
            *current = second;
            target = end;
        }
        else{
            *current = first;
            target = half;
        }

        while ((*current)->next != target)
            current = &(*current)->next;

        // Remet la fin correct
        (*current)->next = end;

        return &(*current)->next;
    }
};

template <typename T>
ostream& operator << ( ostream& os, const LinkedList<T>& liste ) {
    os << liste.size() << ": ";
    auto n = liste.head;

    while (n) {
        os << n->data << " ";
        n = n->next;
    }

    return os;
}
