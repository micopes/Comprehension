male(minjin).
male(hwaseok).
male(taebong).
male(wonseok).
male(sanggu).
male(bbb).
male(taejin).
female(eunsuk).
female(boksul).
female(haesuk).
female(aaa).

parents(minjin, eunsuk, hwaseok).
parents(taejin, eunsuk, hwaseok).
parents(hwaseok, boksul, taebong).
parents(wonseok, boksul, taebong).
parents(haesuk, boksul, taebong).
parents(eunsuk, aaa, bbb).
parents(sanggu, aaa, bbb).

mother(X, Y) :- parents(X, Y, _).
father(X, Y) :- parents(X, _, Y).

brother(X, Y) :- male(Y), father(X, Z), father(Y, Z), X \= Y.
sister(X, Y) :- female(Y), father(X, Z), father(Y, Z), X \= Y.

grandfather(X, Z) :-
    father(X, Y), father(Y, Z).
grandmother(X, Z) :-
    father(X, Y), mother(Y, Z).

uncle(X, Z) :-
    mother(X, Y), brother(Y, Z).
uncle(X, Z) :-
    father(X, Y), brother(Y, Z).

aunt(X, Z) :-
    mother(X, Y), sister(Y, Z).
aunt(X, Z) :-
    father(X, Y), sister(Y, Z).





