%main.pl

:- [movie].

print_query_true(Q) :-
    forall(Q, writeln(true:Q)).

print_query_false(Q) :-
    forall(\+ Q, writeln(false:Q)).

main :- 
    writeln( "1. Did Leonardo DiCaprio act in Babel?" ),
    print_query_true(acted_in(leonardo_dicaprio,babel)),
    print_query_false(acted_in(leonardo_dicaprio,babel)),
    nl,
    halt.
