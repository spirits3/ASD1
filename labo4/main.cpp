#include "linked_list.cpp"

int main() {

    const int N = 10;

    cout << "Creation d'une liste de " << N << " entiers aléatoires \n";
    LinkedList<int> liste;
    for (unsigned i = 0; i < N; ++i) {
        liste.push_front(rand()%100);
    }
    cout << "\n" << liste;

    cout << "\nModification de l'élément en tête à 42 \n";
    liste.front() = 42;
    cout << "\n" << liste;

    cout << "\nModification de l'élément en position " << N/2 << " à 24 \n";
    liste.at(N/2) = 24;
    cout << "\n" << liste;

    cout << "\nSuppression de l'élément en position " << 2*N/3 << "\n";
    liste.erase(2*N/3);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 421 en position 0\n";
    liste.insert(421, 0);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 422 en position " << N/3 << "\n";
    liste.insert(422, N/3);
    cout << "\n" << liste;

    cout << "\nInsertion de l'élément 423 en dernière position\n";
    liste.insert(423, liste.size());
    cout << "\n" << liste;

    liste.erase(0);

    {
        cout << "\nCopie d0une liste constant\n";
        const LinkedList<int> test(liste);
        cout << "\n" << test;

        cout << "\n Recupération d'un element\n";
        cout << test.at(10) << endl;

        cout << "\nDestruction de la copie liste \n";
    }
    {
        cout << "\nCopie d'une liste constant\n";
        LinkedList<int> liste2(liste);
        cout << "\n" << liste2;
        cout << "\nSuppression des 4 premiers éléments\n";
        liste2.erase(0);
        liste2.erase(0);
        liste2.erase(0);
        liste2.erase(0);
        cout << "\n" << liste2;

        cout << "\nRecopie d'une liste constant\n";
        liste2 = liste;
        cout << "\n" << liste2;

        cout << "\nDestruction de la copie liste \n";
    }

    try{
        liste.insert(10, 22);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    try{
        liste.erase(22);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    try{
        liste.at(liste.size());
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    try{
        LinkedList<int> test;
        test.front();
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    try{
        LinkedList<int> test;
        test.pop_front();
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    for (unsigned i = 0; i < N; ++i) {
        liste.push_front(rand()%100);
    }
    cout << "\n" << liste;

    cout << "\nTrie de la liste \n";
    liste.sort();
    cout << "\n" << liste;

    cout << "\nDestruction de la liste \n";
}

