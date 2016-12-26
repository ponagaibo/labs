my_memb(X,[X|_]).
my_memb(X,[_|Y]):-
  my_memb(X,Y).

my_rem(X,[X|Y],Y).
my_rem(X,[Z|Y],[Z|Y1]):-
  my_rem(X,Y,Y1).

my_perm([],[]).
my_perm(L,[X|T]):-
  my_rem(X,L,Z),
  my_perm(Z,T).

surname(arkadeva).
surname(babanova).
surname(korsakova).
surname(dashkov).
surname(ilin).
surname(flerov).

gender(f).
genger(m).

pers(arkadeva,f).
pers(babanova,f).
pers(korsakova,f).
pers(dashkov,m).
pers(ilin,m).
pers(flerov,m).

prof(geography).
prof(english).
prof(french).
prof(german).
prof(history).
prof(math).

last([_,_,_,_,_,X],X).

order(X,Y,[X|T]):-
  my_memb(Y,T).
order(X,Y,[_|T]):-
  order(X,Y,T).

solve(Res):-
  my_perm([pers(arkadeva,f),pers(babanova,f),pers(korsakova,f),pers(dashkov,m),pers(ilin,m),pers(flerov,m)],[A1,B1,C1,D1,E1,F1]),
  my_perm([geography,english,french,german,history,math],[A2,B2,C2,D2,E2,F2]),
  Res = [p(A1,A2),p(B1,B2),p(C1,C2),p(D1,D2),p(E1,E2),p(F1,F2)],

  last(Res,p(_,english)),
  not(my_memb(p(pers(ilin,m),english),Res)),
  not(my_memb(p(pers(flerov,m),english),Res)),
  not(my_memb(p(pers(arkadeva,f),english),Res)),
  not(my_memb(p(pers(babanova,f),english),Res)),
  order(p(pers(flerov,m),_),p(pers(ilin,m),_),Res),
  order(p(_,french),p(pers(flerov,m),_),Res),
  order(p(_,french),p(pers(ilin,m),_),Res),
  order(p(_,german),p(pers(arkadeva,f),_),Res),
  my_memb(p(pers(_,f),german),Res),
  my_memb(p(pers(_,f),math),Res),
  not(my_memb(p(pers(arkadeva,f),math),Res)),
  not(my_memb(p(pers(babanova,f),math),Res)),
  not(my_memb(p(pers(ilin,m),geography),Res)),
  not(my_memb(p(pers(ilin,m),french),Res)),
  not(my_memb(p(pers(flerov,m),french),Res)),
  not(my_memb(p(pers(arkadeva,f),history),Res)),
  not(my_memb(p(pers(babanova,f),history),Res)).

?- solve(Res), write(Res), nl.