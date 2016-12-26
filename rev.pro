getNum([N],N).

a_expr(E,Res,NewRes):-
  write("\nin + "),
  append(T,['+'|S],E),
  write("\nT is "), write(T), write(", S is "), write(S),
  a_term(T,Res,B),
  %write("\nB is: "), write(B),
  a_expr(S,Res,A),
  %write("\nA is: "), write(A),
  %getNum(S,S1),
  append(["+"|B],A,NewRes),
  %write("\nRes is: "), write(Res), 
  write(" NewRes+: "), write(NewRes).

a_expr(E,Res,NewRes):-
  write("\nin - "),
  append(T,['-'|S],E),
  a_term(T,Res,B),
  a_expr(S,Res,A),
  append(["-"|B],A,NewRes),
  %write("Res is: "), write(Res), 
  write(" NewRes-: "), write(NewRes).

a_expr(E,Res,NewRes):-
  write("\nin expr "),
  a_term(E,Res,NewRes).

a_term(T,Res,NewRes):-
  write("\nin num "),
  a_number(T,V),
  write("\nV = "), write(V),
  append(Res,[V],NewRes),
  write("\n NewRes num: "), write(NewRes). 

a_term(T,Res,NewRes):-
  write("\nin * "),
  append(N,['*'|S],T),
  a_number(N,B),
  write("\n B = "), write(B),
  a_term(S,Res,A),
write("\n **B = "), write(B),
  write("\n A = "), write(A),
  getNum(A,A1),
  append(["*"|B],A1,NewRes),
  write("\n !!!NewRes *: "), write(NewRes).

a_term(T,Res,NewRes):-
  write("\nin : "),
  append(N,[':'|S],T),
  a_number(N,B),
  a_term(S,Res,A),
  append(["/"|B],A,NewRes).

a_number([N],N):-
  write("\ncheck num "),
  number(N).

calculate(L,Res):-
 write("\nin calc "),
  %reverse(L,L1),
  a_expr(L,[],Res).

reverse([],[]). 
reverse([X],[X]).
reverse([X|Xs],R):-
  reverse(Xs,T),
  append(T,[X],R).

?- calculate([3,'*',2],NewRes), 
  write("\n  end res  "), write(NewRes).

