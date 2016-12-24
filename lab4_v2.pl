isVerb(Word):-
    member(Word, ["is"]). 
isArticle(Word):-
    member(Word, ["The", "the"]).
isObject(Word):-
    member(Word, ["book", "pen", "стол"]).
isLocation(Word):-    
    member(Word, ["in", "on", "behind", "under", "over"]).
isSize(Word):-    
    member(Word, ["small", "little", "medium", "big", "large"]).
isColor(Word):-    
    member(Word, ["red", "blue", "green", "yellow", "orange", "pink", "brown", "black", "gray", "white"]).


findLocation("in", Object, Result):-
    Result = in(Object).
findLocation("on", Object, Result):-
    Result = on(Object).
findLocation("behind", Object, Result):-
    Result = behind(Object).
findLocation("under", Object, Result):-
    Result = under(Object).
findLocation("over", Object, Result):-
    Result = over(Object).


checkObject(Sentence, Result):-
    isArticle(A), isSize(S), isObject(O),
    [A, S, O] == Sentence,
    Result = object(O, size(S)).
 
checkObject(Sentence, Result):-
    isArticle(A), isColor(C), isObject(O),
    [A, C, O] == Sentence,
    Result = object(O, color(C)).

checkObject(Sentence, Result):-
    isArticle(A), isObject(O),
    [A, O] == Sentence,
    Result = object(O).

checkDescription(Sentence, Object, Result):-
    Object \= object(_, color(_)),
    isVerb(V), isColor(C),
    [V, C] == Sentence,
    Result = s(Object, color(C)).
 
checkDescription(Sentence, Object, Result):-
    Object \= object(_, size(_)),
    isVerb(V), isSize(S),
    [V, S] == Sentence,
    Result = s(Object, size(S)).

checkDescription(Sentence, Object, Result):-
    isVerb(V), isLocation(L), A = "the", isObject(O),
    [V, L, A, O] == Sentence,
    findLocation(L, O, R),
    Result = s(location(Object), R).

checkDescription([], Object, Result):-
    Result = s(Object).

parse(Sentence, Result):-
    append(S1, S2, Sentence),
    checkObject(S1, R),
    checkDescription(S2, R, Result).

main :- parse(["The", "big", "book", "is", "under", "the", "стол"], Result), write(Result), write('\n').
        %parse(["The", "red", "book", "is", "on", "the", "table"], Result), write(Result), write('\n').
        %parse(["The", "little", "pen", "is", "red"], Result), write(Result), write('\n').
        %parse(["The", "table"], Result), write(Result), write('\n').
        %parse(["The", "large", "book", "is", "small"], Result), write(Result), write('\n').