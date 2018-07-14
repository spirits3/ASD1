//
//  Binary Search Tree
//
//  Copyright (c) 2017 Olivier Cuisenaire. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>
#include <cassert>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <limits>

using namespace std;

template < typename T >
class BinarySearchTree {
    public:

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

    private:
        /**
         *  @brief Noeud de l'arbre.
         *
         * contient une cle et les liens vers les sous-arbres droit et gauche.
         */
        struct Node {
            const value_type key; // clé non modifiable
            Node* right;          // sous arbre avec des cles plus grandes
            Node* left;           // sous arbre avec des cles plus petites
            size_t nbElements;    // nombre de noeuds dans le sous arbre dont
            // ce noeud est la racine

            Node(const_reference key)  // seul constructeur disponible. key est obligatoire
                : key(key), right(nullptr), left(nullptr), nbElements(1)
            {
                cout << "(C" << key << ") ";
            }
            ~Node()               // destructeur
            {
                cout << "(D" << key << ") ";
            }
            Node() = delete;             // pas de construction par défaut
            Node(const Node&) = delete;  // pas de construction par copie
            Node(Node&&) = delete;       // pas de construction par déplacement
        };

        /**
         *  @brief  Racine de l'arbre. nullptr si l'arbre est vide
         */
        Node* _root;

    public:
        /**
         *  @brief Constructeur par défaut. Construit un arbre vide
         */
        BinarySearchTree() : _root(nullptr) { }

        /**
         *  @brief Constucteur de copie.
         *
         *  @param other le BinarySearchTree à copier
         *
         *  @remark Complexite de O(N), N étant la taille de l'arbre other
         *          garanti forte
         *
         */
        BinarySearchTree( const BinarySearchTree& other ) : BinarySearchTree(){
            Node* tmp;
            try {
                copieSubTree(other._root, tmp);
            } catch(...){
                deleteSubTree(tmp);
                throw;
            }

            _root = tmp;
        }

        /**
         *  @brief Opérateur d'affectation par copie.
         *
         *  @param other le BinarySearchTree à copier
         *
         *  @remark Complexite de O(N), N étant la taille de l'arbre other
         *          garanti forte
         *
         */
        BinarySearchTree& operator= ( const BinarySearchTree& other ) {
            Node* tmp;
            try {
                copieSubTree(other._root, tmp);
            } catch(...){
                deleteSubTree(tmp);
                throw;
            }


            deleteSubTree(_root);
            _root = tmp;

            return *this;
        }

        /**
         *  @brief Echange le contenu avec un autre BST
         *
         *  @param other le BST avec lequel on echange le contenu
         *
         *  @remark Complexite de O(1)
         *
         */
        void swap(BinarySearchTree& other ) noexcept {
            std::swap(_root, other._root);
        }

        /**
         *  @brief constructeur de copie par déplacement
         *
         *  @param other le BST dont on vole le contenu
         *
         *  @remark Complexite de O(1)
         *
         */
        BinarySearchTree( BinarySearchTree&& other ) noexcept: BinarySearchTree() {
            swap(other);
        }

        /**
         *  @brief Opérateur d'affectation par déplacement.
         *
         *  @param other le BST dont on vole le contenu
         *
         *  @remark Complexite de O(N), N étant le nombre d'element de l'arbre root
         *
         */
        BinarySearchTree& operator= ( BinarySearchTree&& other ) noexcept {
            swap(other);
            other.~BinarySearchTree();

            return *this;
        }

        /**
        *   @brief Destructeur
        *
        *   Ne pas modifier mais écrire la fonction récursive privée deleteSubTree(Node*)
        *
        *   @remark Complexite de O(N), N étant le nombre d'element de l'arbre root
        */
        ~BinarySearchTree() {
            deleteSubTree( _root );
            _root = nullptr;
        }

    private:
        /**
        *   @brief Fonction détruisant (delete) un sous arbre
        *
        *   @param r la racine du sous arbre à détruire peut éventuellement valoir nullptr
        *   
        *   @remark Complexite de O(N), N etant le nombre d'element du sous arbre
        */
        static void deleteSubTree(Node* r) noexcept {
            if(r == nullptr)
                return;

            deleteSubTree(r->left);

            deleteSubTree(r->right);

            delete r;
        }

        /**
        *   @brief Fonction copiant le sous arbre source dans target
        *
        *   @param source le sous arbre qu'on veut copier
        *   @param target la ou on va copier le sous arbre
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre source
        */
        static void copieSubTree(const Node* const source, Node*& target) {
            if(source == nullptr)
                return;

            target = new Node(source->key);
            target->nbElements = source->nbElements;

            copieSubTree(source->left, target->left);
            copieSubTree(source->right, target->right);
        }

    public:
        /**
        *   @brief Insertion d'une cle dans l'arbre
        *
        *   @param key la clé à insérer.
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element de l'arbre
        *
        *   Ne pas modifier mais écrire la fonction
        *   récursive privée insert(Node*&,const_reference)
        */
        void insert( const_reference key) {
            insert(_root,key);
        }

    private:
        /**
        *   @brief Insertion d'une cle dans un sous-arbre
        *
        *   @param r la racine du sous-arbre dans lequel insérer la cle.
        *   @param key la clé à insérer.
        *
        *   @return vrai si la cle est inseree. faux si elle etait deja presente.
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous-arbre
        *
        *   Si la cle est deja presente, cette fonction ne fait rien.
        *   x peut éventuellement valoir nullptr en entrée.
        *   la fonction peut modifier x, reçu par référence, si nécessaire
        */
        static bool insert(Node*& r, const_reference key) {
            bool c = false;

            if(r == nullptr) {
                r = new Node(key);
                return true;
            } else if(key < r->key) {
                c = insert(r->left, key);
            } else if(key > r->key) {
                c = insert(r->right, key);
            }

            if(c)
                ++r->nbElements;

            return c;
        }

    public:
        /**
        *   @brief Recherche d'une cle.
        *
        *   @param key la cle a rechercher
        *
        *   @return vrai si la cle trouvee, faux sinon.
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element de l'arbre
        *
        *   Ne pas modifier mais écrire la fonction
        *   récursive privée contains(Node*,const_reference)
        */
        bool contains( const_reference key ) const noexcept {
            return contains(_root,key);
        }

    private:
        /**
        *   @brief Recherche d'une cle dans un sous-arbre
        *
        *   @param key la cle a rechercher
        *   @param r   la racine du sous-arbre
        *
        *   @return vrai si la cle trouvee, faux sinon.
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous-arbre
        */
        static bool contains(Node* r, const_reference key) noexcept {
            if(r) {
                if(key == r->key)
                    return true;
                if(key < r->key)
                    return contains(r->left, key);
                else
                    return contains(r->right, key);
            }
            return false;
        }

    private:
        /**
        *   @brief trouver le plus petit noeud
        *
        *   @param root      racine du sous-arbre sous l'on cherche le minimum
        *   @param function  fonction a appliquer a l'ensemble des noeuds parcouru
        *
        *   @return le plus petit noeud du sous-arbre
        *
        *   @remark Complexite de O(Log(N)), N étant le nombre d'element du sous arbre
        */
        static Node*& minNode(Node*& root, void f(Node*) = [](Node*){}) {
            assert(root != nullptr);

            f(root);

            if(root->left == nullptr)
                return root;

            return minNode(root->left, f);
        }
        /**
        *   @brief trouver le plus petit noeud
        *
        *   @param root on cherche dans tout l'arbre
        *
        *   @return on retourne le plus petit noeud
        */
        static const Node* minNode(const Node* root) {
            assert(root != nullptr);

            if(root->left == nullptr)
                return root;

            return minNode(root->left);
        }

        /**
        *   @brief Supprime l'element minimum du sous-arbre
        *
        *   @param root racine du sous-arbre ou l'on cherche le minimum
        *
        *   @return le plus petit Noeud du sous-arbre
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous-arbre
        */
        static Node* deleteByMin(Node*& root) {
            assert(root != nullptr);

            if(root->left == nullptr) {
                Node* tmp = root;
                root = root->right;
                return tmp;
            }

            --root->nbElements;

            return deleteByMin(root->left);
        }

    public:
        /**
        *   @brief Recherche de la cle minimale.
        *
        *   @return une const reference a la cle minimale
        *
        *   @exception std::logic_error si necessaire
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element dans l'arbre
        *
        *   vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
        */
        const_reference min() const {
            if(!size())
                throw std::logic_error("BinarySearchTree::min");

            return minNode(_root)->key;
        }

        /**
        *   @brief Supprime le plus petit element de l'arbre.
        *
        *   @exception std::logic_error si necessaire
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element dans l'arbre
        *
        *   vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
        */
        void deleteMin() {
            if(!size())
                throw std::logic_error("BinarySearchTree::min");

            delete deleteByMin(_root);
        }

    public:


        /**
        *   @brief Supprime l'element de cle key de l'arbre.
        *
        *   @param key l'element a supprimer
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element dans l'arbre
        *
        *   si l'element n'est pas present, la fonction ne modifie pas
        *   l'arbre mais retourne false. Si l'element est present, elle
        *   retourne vrai
        *
        *   Ne pas modifier mais écrire la fonction
        *   récursive privée deleteElement(Node*&,const_reference)
        */
        bool deleteElement(const_reference key) noexcept {
            return deleteElement( _root, key );
        }

    private:
        /**
        *   @brief interchanger de place 2 elements
        *
        *   @param n1 premier noeud que l'on veut changer de place
        *   @param n2 deuxieme noeud que l'on veut changer de place
        *
        *   @remark Complexite de O(1)
        */
        static void swap(Node*& n1, Node*& n2) {
            std::swap(n1->left, n2->left);
            std::swap(n1->right, n2->right);
            std::swap(n1->nbElements, n2->nbElements);
            std::swap(n1, n2);
        }

        /**
        *   @brief Suppression d'un noeud selon la methode de Hibbard
        *
        *   @param r noeud que l'on veut supprimer
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous arbre r
        */
        static void deleteByHibbard(Node*& r) {
            assert(r != nullptr && r->right != nullptr);

            Node*& min = minNode(r->right, [](Node* n){ --n->nbElements; });

            swap(r, min);

            Node* old = min;
            min = min->right;
            delete old;
        }

        /**
        *   @brief Supprime l'element de cle key du sous arbre.
        *
        *   @param r la racine du sous arbre
        *   @param key l'element a supprimer
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous arbre r
        *
        *   si l'element n'est pas present, la fonction ne modifie pas
        *   l'arbre mais retourne false. Si l'element est present, elle
        *   retourne vrai
        */
        static bool deleteElement(Node*& r, const_reference key) noexcept {
            if(!r)
                return false;

            bool c = true;
            if(key < r->key){
                c = deleteElement(r->left, key);
            } else if(key > r->key) {
                c = deleteElement(r->right, key);
            } else if(r->right != NULL && r->left != NULL) {
                deleteByHibbard(r);
            } else {
                Node* old = r;
                r = (r->right != nullptr)? r->right: r->left;
                delete old;

                return true;
            }

            if(c)
                --r->nbElements;

            return c;
        }

    public:
        /**
        *  @brief taille de l'arbre
        *
        *  @return le nombre d'elements de l'arbre
        *
        *  @remark Complexite de O(1)
        */
        size_t size() const noexcept {
            if(_root != nullptr)
                return _root->nbElements;

            return 0;
        }

        /**
        *   @brief cle en position n
        *
        *   @return une reference a la cle en position n par ordre croissant des elements
        *
        *   @exception std::logic_error si nécessaire
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element de l'arbre r
        *
        *   ajoutez le code de gestion des exceptions, puis mettez en oeuvre la fonction
        *   recursive nth_element(Node*, n)
        */
        const_reference nth_element(size_t n) const {
            if(n >= size())
                throw std::logic_error("BinarySearchTree::nth_element");

            return nth_element(_root,n);
        }

    private:
        /**
        *   @brief cle en position n dans un sous arbre
        *
        *   @param r la racine du sous arbre. ne peut pas etre nullptr
        *   @param n la position n
        *
        *   @return une reference a la cle en position n par ordre croissant des elements
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous arbre r
        */
        static const_reference nth_element(Node* r, size_t n) noexcept {
            assert(r != nullptr);

            if(r->left == nullptr && r->right == nullptr)
                return r->key;

            if(r->left && n < r->left->nbElements)
                return nth_element(r->left, n);
            else if(r->right && n >= (r->nbElements - r->right->nbElements))
                return nth_element(r->right, n - (r->nbElements - r->right->nbElements));

            return r->key;
        }

    public:
        /**
        *   @brief position d'une cle dans l'ordre croissant des elements de l'arbre
        *
        *   @param key la cle dont on cherche le rang
        *
        *   @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element de l'arbre
        *
        *   Ne pas modifier mais écrire la fonction
        *   récursive privée rank(Node*,const_reference)
        */
        size_t rank(const_reference key) const noexcept {
            return rank(_root,key);
        }

    private:
        /**
        *   @brief position d'une cle dans l'ordre croissant des elements du sous-arbre
        *
        *   @param key la cle dont on cherche le rang
        *   @param r la racine du sous arbre
        *
        *   @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous arbre
        */
        static size_t rank(Node* r, const_reference key) noexcept {
            if(r == nullptr)
                return size_t(-1);

            if(key == r->key)
                return (r->left)? r->left->nbElements: 0;

            if(key < r->key)
                return rank(r->left, key);

            size_t result = rank(r->right, key);

            if(result == size_t(-1)) //repropagation de l'erreur
                return size_t(-1);

            return ((r->left)? r->left->nbElements + 1: 1) + rank(r->right, key);
        }

    public:
        /**
        *  @brief linearise l'arbre
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        *
        *  transforme l'arbre en une liste simplement chainee composee des memes
        *  noeuds que precedemment, mais dont les pointeurs left sont tous egaux
        *  a nullptr. Cette liste doit toujours respecter les conditions d'un
        *  arbre binaire de recherche
        *
        *  Ne pas modifier cette fonction qui sert essentiellement a tester la
        *  fonction recursive linearize(Node*, Node*&, size_t&) utilisée par
        *  la methode publique arborize
        */
        void linearize() noexcept {
            size_t cnt = 0;
            Node* list = nullptr;
            linearize(_root,list,cnt);
            _root = list;
        }

    private:
        /**
        *  @brief linearise une sous arbre tree en une liste
        *
        *  @param tree pointe vers la racine de l'arbre a lineariser
        *  @param list reference a la tete de la liste a creer. sera modifiee
        *              par la fonction pour que list pointe vers le plus petit
        *              element de tree
        *  @param cnt  calcule au fure et a mesure le nombre d'elements de la liste
        *              cree. l'effet de la fonction doit etre d'ajouter le nombre
        *              d'elements du sous-arbre de racine tree. Cependant, vous
        *              avez uniquement le droit d'utiliser l'opérateur ++.
        *
        *   @remark Complexite de O(N), N etant le nombre d'element du sous arbre
        */
        static void linearize(Node* tree, Node*& list, size_t& cnt) noexcept {
            if(tree == nullptr)
                return;

            linearize(tree->right, list, cnt);

            if(list != nullptr)
                tree->right = list;

            list = tree;

            ++cnt;
            tree->nbElements = cnt;

            linearize(tree->left, list, cnt);

            tree->left  = nullptr;
        }

    public:
        /**
        *  @brief equilibre l'arbre
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        *
        *   applique l'algorithme d'equilibrage de l'arbre par linearisation et
        *   arborisation
        *
        *   Ne pas modifier cette fonction.
        */
        void balance() noexcept {
            size_t cnt = 0;
            Node* list = nullptr;
            linearize(_root,list,cnt);
            arborize(_root,list,cnt);
        }

    private:
        /**
        *   @brief arborise les cnt premiers elements d'une liste en un arbre
        *
        *   @param tree reference dans laquelle il faut ecrire la racine de l'arbre
        *               arborise par la fonction
        *   @param list IN - reference a la tete de la liste a parcourir. La liste
        *                    est composee de Node dont le pointer left est nullptr
        *               OUT - debut de la suite de la liste dont on a utilise cnt
        *                     elements
        *   @param cnt  nombre d'elements de la liste que l'on doit utiliser pour
        *               arboriser le sous arbre
        *
        *   @remark Complexite de O(Log(N)), N etant le nombre d'element du sous arbre
        */
        static void arborize(Node*& tree, Node*& list, size_t cnt) noexcept {
            if(cnt == 0) {
                tree = nullptr;
                return;
            } 

            Node* temp = nullptr;
            arborize(temp, list, (cnt - 1) / 2);

            tree = list;
            tree->nbElements = cnt;
            tree->left = temp;

            list = list->right;

            arborize(tree->right, list, cnt / 2);
        }

    private:
        /**
        *   @brief    ne fait rien
        *
        *   @param a  un element quelconque
        */

        static void defaultVisitor(const value_type& a){ }

        /**
        *   @brief creer une visite pre-ordonnee, symetrique et post ordonnee de notre arbre
        *
        *   @param r     un noeud de l'arbre choisit
        *   @param pre   visite de l'arbre pre ordonne
        *   @param sym   visite de l'arbre symetriquement
        *   @param post  visite de l'arbre post ordonne
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        */
        template < typename Fn = decltype(defaultVisitor), typename Fn2 = decltype(defaultVisitor), typename Fn3 = decltype(defaultVisitor) >
            static void visit (Node* r, Fn pre = &defaultVisitor, Fn2 sym = &defaultVisitor, Fn3 post = &defaultVisitor) {
                if(!r)
                    return;

                pre(r->key);
                visit(r->left, pre, sym, post);
                sym(r->key);
                visit(r->right, pre, sym, post);
                post(r->key);
            }
    public:
        /**
        *   @brief Parcours pre-ordonne de l'arbre
        *
        *   @param f une fonction capable d'être appelée en recevant une cle
        *           en parametre. Pour le noeud n courrant, l'appel sera f(n->key);
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        */
        template < typename Fn >
            void visitPre (Fn f) {
                visit(_root, f);
            }

        /**
        *   @brief Parcours symétrique de l'arbre
        *
        *   @param f une fonction capable d'être appelée en recevant une cle
        *           en parametre. Pour le noeud n courrant, l'appel sera f(n->key);
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        */
        template < typename Fn >
            void visitSym (Fn f) {
                visit(_root, &defaultVisitor, f);
            }

        /**
        *   @brief Parcours post-ordonne de l'arbre
        *
        *   @param f une fonction capable d'être appelée en recevant une cle
        *           en parametre. Pour le noeud n courrant, l'appel sera f(n->key);
        *
        *   @remark Complexite de O(N), N etant le nombre d'element de l'arbre
        */
        template < typename Fn >
            void visitPost (Fn f) {
                visit(_root, &defaultVisitor, &defaultVisitor, f);
            }


        /**
        *   Les fonctions suivantes sont fournies pour permettre de tester votre classe
        *   Merci de ne rien modifier au dela de cette ligne
        */
        void display() const {
            stringstream ss1, ss2, ss3;
            displayKeys(ss1);
            displayKeys(ss3);
            displayCounts(ss2);
            string l1, l2;

            size_t W = 11;
            while( getline(ss3,l1) )
                if (l1.length() > W) W = l1.length();

            displayKeys(ss1);

            cout << "\n";
            cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
            cout << "| "<< left << setw(W) << "key" << "| " << setw(W) << "nbElements" << "|" << endl;
            cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
            while( getline(ss1,l1) and getline(ss2, l2) ) {
                cout << "| "<< left << setw(W) << l1 << "| " << setw(W) << l2 << "|" << endl;
            }
            cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;

        }

        void displayKeys(ostream& os = cout) const {
            display([](Node* n) -> const_reference { return n->key; }, os);
        }


        void displayCounts(ostream& os = cout) const {
            display([](Node* n) -> size_t { return n->nbElements; }, os);
        }

        /**
        *  utilise un parcours de l'arbre en largeur avec
        *  un noeud sentinelle newLevel qui traque les
        *  changements de niveaux
        */
        template <typename Fn>
            void display (Fn func, ostream& os = cout ) const {
                Node* newLevel = (Node*) -1;
                // addresse non nulle dont on est sur qu'elle ne contient pas
                // vraiment un Node. Utilisée comme sentinelle.

                queue<Node*> Q;
                Q.push(_root);
                Q.push(newLevel);

                while(!Q.empty()) {
                    Node* cur = Q.front();
                    Q.pop();

                    if(cur == newLevel) {
                        os << endl;
                        if(!Q.empty())
                            Q.push(newLevel);
                    } else if(cur == nullptr) {
                        os << "- ";
                    } else {
                        os << func(cur) << " ";
                        Q.push(cur->left);
                        Q.push(cur->right);
                    }
                }
            }
};
