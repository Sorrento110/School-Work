% This is the family relations exercise at the end of Ch.4 [L].
child(alberto,guido). child(alberto,antonietta).
child(giulia,enrico). child(giulia,annamaria).
child(dante,marco).   child(clara,marco).
child(dante,laura).   child(clara,laura).
child(marco,alberto).   child(marco,giulia).
child(laura,lawrence).  child(laura,julie).
child(emily,lawrence).  child(emily, julie).
child(claire,lawrence). child(claire, julie).
child(sam,emily). child(ben,emily).
child(sam,dave). child(ben,dave).
child(eve,claire). child(annabelle,claire).
child(eve,ed). child(annabelle,ed).
child(giulio,guido). child(donata,giulio).
child(sara,donata). child(marco2,donata).

male(guido). male(enrico).
male(marco). male(dante). male(alberto). male(lawrence).
male(sam). male(ben). male(dave). male(ed).
male(giulio). male(marco2).
female(antonietta). female(annamaria).
female(clara).  female(laura).  female(giulia). female(julie).
female(emily). female(claire). female(eve). female(annabelle).
female(donata). female(sara).

%Clauses from Figure 3.1, as required by Exercise of Ch.4[L]
parent(Y,X) :- child(X,Y).
father(Y,X) :- child(X,Y), male(Y).
opp_sex(X,Y) :- male(X), female(Y).
opp_sex(Y,X) :- male(X), female(Y).
grand_father(X,Z) :- father(X,Y), parent(Y,Z).

%New clauses for Exercise of Ch.4[L] follow
mother(Y,X) :- child(X,Y), female(Y).
grand_parent(Y,Z) :- parent(Y,X), parent(X,Z).
great_grand_mother(X,Y) :- mother(X,Z), parent(Z,A), parent(A,Y).
sibling(X,Y) :- parent(Z,Y), parent(Z,X), \+(X=Y).
brother(X,Y) :- male(X), parent(Z,Y), parent(Z,X), \+(X=Y).
sister(Y,X) :- female(Y), parent(Z,Y), parent(Z,X), \+(X=Y).
half_sibling(X,Y) :- parent(Z,Y), parent(Z,X), parent(M,Y), \+parent(M,X), \+(M=Z).
full_sibling(X,Y) :- parent(Z,Y), parent(Z,X), parent(M,Y), parent(M,X), \+(M=Z), \+(X=Y).
first_cousin(X,Y) :- parent(Z,X), parent(A,Y), \+(A=Z), sibling(Z,A).
second_cousin(X,Y) :- parent(Z,X), parent(A,Y), \+(A=Z), first_cousin(Z,A).
half_first_cousin(X,Y) :- parent(Z,X), parent(A,Y), half_sibling(Z,A).
double_first_cousin(X,Y) :- parent(Z,X), parent(A,X), \+(A=Z), parent(B,Y), sibling(B,Z), sibling(A,B).
first_cousin_twice_removed(X,Y) :- grand_parent(Z,X), first_cousin(Z,Y).
descendant(X,Y) :- (parent(Y,X); parent(Z,X), descendant(Z,Y)).
ancestor(X,Y) :- descendant(Y,X).
cousin(X,Y) :- parent(Z,X), parent(A,Y), \+(A=Z), (sibling(A,Z); cousin(A,Z)).
closest_common_ancestor(X,Y,Z) :- ancestor(X,Y), ancestor(X,Z), child(A,X), \+ancestor(A,Y), \+ancestor(A,Z), \+(Z=Y).
write_child(X,Y) :- write(X), write(' is a child of '), write(Y), nl.
write_descendant_chain(X,Y) :- descendant(X,Y), (parent(Y,X) -> write_child(X,Y); grand_parent(Y,X), parent(Y,Z), parent(Z,X) -> write_child(Z,Y), write_child(X,Z)); parent(Z,X), descendant(Z,Y), write_descendant_chain(Z,Y).


