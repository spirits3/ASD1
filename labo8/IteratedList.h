#ifndef _ITERATED_LIST_H_
#define _ITERATED_LIST_H_

#include <iostream>
#include <stdexcept>

/// Classe de liste simplement chainee
template < typename T >
class ForwardList
{
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        class iterator;       // forward declation d'iterator
        //  class const_iterator; // forward declation de const_iterator
        using const_iterator = iterator;

    private:
        /**
         *  @brief Maillon de la chaine.
         *
         * contient une valeur et le lien vers le maillon suivant.
         */
        struct Node {
            value_type data;
            Node* next;
        };
        static Node*& next(Node* n) { return n->next; }
        static reference value(Node* n) { return n->data; }

        /**
         *  @brief  Tete de la ForwardList
         */
        Node before_head;
        Node*& head;

    public:
        iterator before_begin() { return iterator(&before_head); }
        iterator begin() { return iterator(head); }
        iterator end() { return iterator(nullptr); }
        const_iterator before_begin() const { return const_iterator(&before_head); }
        const_iterator begin() const { return const_iterator(head); }
        const_iterator end() const { return const_iterator(nullptr); }
        const_iterator cbefore_begin() const { return const_iterator(&before_head); }
        const_iterator cbegin() const { return const_iterator(head); }
        const_iterator cend() const { return const_iterator(nullptr); }

    private:
        void insert_after(Node* n, const_reference val)
        {
            if( !n )
                throw std::runtime_error("Can't insert after null");
            next(n) = new Node{val,next(n)};
        }

        void erase_after(Node* n)
        {
            if( !n or !n->next )
                throw std::runtime_error("Can't erase null or after null");
            Node* tmp = next(n);
            next(n) = next(next(n));
            delete tmp;
        }

    public:
        /**
         *  @brief Constructeur par défaut. Construit une ForwardList vide
         *
         */
        ForwardList()
            : before_head { value_type(), nullptr },
            head(before_head.next)
            {
                // ne pas modifier.
            }

    public:
        /**
         *  @brief Constructeur de copie
         *
         *  @param other la ForwardList à copier
         */
        ForwardList( const ForwardList& other )
            : ForwardList()
        {
            /* ... */
        }

    public:
        /**
         *  @brief Opérateur d'affectation par copie
         *
         *  @param other la ForwardList à copier
         *
         *  @return la ForwardList courante *this (par référence)
         *
         *  @remark l'opérateur doit être une no-op si other
         *  est la ForwardList courante.
         *
         *  @remark le contenu précédent de la ForwardList courante est
         *  effacé.
         */
        ForwardList& operator= ( const ForwardList& other ) {
            /* ... */
            return *this;
        }

    public:
        /**
         *  @brief destructeur
         */
        ~ForwardList() {
            while(!empty()){
                erase_after(&before_head);
            }
        }


    public:
        bool empty() const noexcept {
            return head == nullptr;
        }

    public:
        /**
         *  @brief insertion d'une valeur dans un maillon en tête de liste
         *
         *  @param value la valeur à insérer
         *
         *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception lancée par la constructeur de copie de value_type
         */
        void push_front( const_reference value) {
            insert_after(&before_head, value);
        }

    public:
        /**
         *  @brief accès (lecture/écriture) à la valeur en tête de ForwardList
         *
         *  @return référence à cette valeur
         *
         *  @exception std::runtime_error si la liste est vide
         */
        reference front() {
            return const_cast<reference>(static_cast<const ForwardList*>(this)->front());
        }

        const_reference front() const {
            return head->data;
        }

    public:
        /**
         *  @brief Suppression de l'élément en tête de ForwardList
         *
         *  @exception std::runtime_error si la liste est vide
         */
        void pop_front( ) {
            erase_after(&before_head);
        }

        void insert_after(iterator& it, const_reference val)
        {
            insert_after(it.node, val);
        }

        void erase_after(iterator& it)
        {
            erase_after(it.node);
        }
};

template<typename T>
class ForwardList<T>::iterator
{
    friend ForwardList;
    private:
    // Le seul attribut autorisé est un pointeur vers
    // un noeud de la liste sur laquelle on itère.
    // On n'a donc pas de pointeur ni de référence vers
    // la liste elle-meme.

    Node* node;
    public:

    // Votre mission - si vous l'acceptez - consiste a
    // écrire les constructeurs (l'un prenant un Node*
    // comme parametre, l'autre de copie), les deux
    // opérateurs ++ (pré et postfixe), l'opérateur de
    // déréférencement *, et les opérateurs d'(in-)égalité.
    iterator() : node(nullptr) {}
    iterator(Node* node) : node(node) {}

    iterator(const iterator& it) : iterator(it.node) {}

    reference operator * () {
        return node->data;
    }

    bool operator != (const iterator& it) const {
        return node != it.node;
    }

    iterator operator ++ (int) {
        iterator tmp = iterator(*this);
        node = node->next;
        return tmp;
    }

    iterator& operator ++() {
        node = node->next;
        return *this;
    }

};


// opérateur permettant d'afficher le contenu de la liste. Ne pas modifier.
template <typename T>
std::ostream& operator << (std::ostream& os, const ForwardList<T>& liste) {
    for(auto it = liste.cbegin(); it != liste.cend(); ++it) {
        os << *it << " ";
    }
    return os;
}

#endif
