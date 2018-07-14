void transfert(Tour& from, Tour& via, Tour& to, int n)
{
   
    // A COMPLETER
    
    // transfère n disques de la tour from à la tour to
    // en utilisant la tour via comme intermediaire
    //
    // appeler display() après chaque movement de disque.
    
    if(n == 0) return;
    
    transfert(from,to,via, n-1);
    to.push_back(from.back());
    from.pop_back();
    display();
    transfert(via,from,to,n-1);
    
}
