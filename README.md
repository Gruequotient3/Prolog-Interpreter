# Prolog Interpreter

Repos Git de mon projet d'interpreteur prolog en C

## Participant
- LEVASTRE CLément

## Data Structure
- Linked List
- Binary Search Tree

## Compilation  
### Unix

```zsh
git clone https://github.com/Gruequotient3/Prolog-Interpgit reter.git
cd Prolog-Interpreter
make
./main fam.pl
```

## Comment l'utiliser?

```zsh
make
./main <path to prolog file>
```

## Fonctionnalités
- Parser (Analyse de chaine de caractère).
    - Gère mal les espaces (ne sont pas enlevés et sont donc stocker en mémoire)
    - Sensible à la casse
- Stockage des connaissances prolog dans un arbre.
- Unification de connaissances.
- Exploration des termes sur les connaissances.
- Pas d'implémentation des règles (ainsi pas de backtracking)
    - Exemple : __fils(X, Y) :- parent(Y, X).__
