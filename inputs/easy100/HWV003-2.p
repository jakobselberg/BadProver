%--------------------------------------------------------------------------
% File     : HWV003-2 : TPTP v9.2.1. Released v2.7.0.
% Domain   : Hardware Verification
% Problem  : One bit Full Adder
% Version  : Especial.
% English  : Prove that the given implementation of a one-bit full adder
%            using only NAND gates is correct

% Refs     : [WO+92] Wos et al. (1992), Automated Reasoning: Introduction a
%          : [Bur]   Burris, Comments on Boolean Algebra
%          : [Bur98] Burris (1998), Logic for Mathematics and Computer Scie
%          : [Bou03] Boule (2003), Email to G. Sutcliffe
% Source   : [Bou03]
% Names    :

% Status   : Unsatisfiable
% Rating   : 0.41 v9.1.0, 0.60 v9.0.0, 0.40 v8.2.0, 0.44 v8.1.0, 0.47 v7.5.0, 0.41 v7.4.0, 0.47 v7.3.0, 0.38 v7.2.0, 0.42 v7.1.0, 0.27 v7.0.0, 0.46 v6.4.0, 0.50 v6.3.0, 0.30 v6.2.0, 0.40 v6.1.0, 0.64 v6.0.0, 0.43 v5.5.0, 0.50 v5.4.0, 0.56 v5.3.0, 0.70 v5.2.0, 0.50 v5.1.0, 0.67 v5.0.0, 0.70 v4.1.0, 0.56 v4.0.1, 0.62 v4.0.0, 0.57 v3.7.0, 0.43 v3.4.0, 0.17 v3.3.0, 0.22 v3.1.0, 0.00 v2.7.0
% Syntax   : Number of clauses     :   36 (  35 unt;   0 nHn;  14 RR)
%            Number of literals    :   37 (  37 equ;   2 neg)
%            Maximal clause size   :    2 (   1 avg)
%            Maximal term depth    :    4 (   2 avg)
%            Number of predicates  :    1 (   0 usr;   0 prp; 2-2 aty)
%            Number of functors    :   20 (  20 usr;  16 con; 0-2 aty)
%            Number of variables   :   40 (   4 sgn)
% SPC      : CNF_UNS_RFO_PEQ_NUE

% Comments : This is an alternate encoding of HWV003-1.p. In reality,
%            one could use a propositional logic encoding of the problem
%            in order for the problem to be fully-decidable and for run-
%            times to be much quicker.
%--------------------------------------------------------------------------
%----Boolean logic axioms (not a minimal set of axioms)
cnf(or_commutative,axiom,
    or(X,Y) = or(Y,X) ).

cnf(and_commutative,axiom,
    and(X,Y) = and(Y,X) ).

cnf(or_associative,axiom,
    or(or(X,Y),Z) = or(X,or(Y,Z)) ).

cnf(and_associative,axiom,
    and(and(X,Y),Z) = and(X,and(Y,Z)) ).

cnf(or_identity,axiom,
    or(X,ll0) = X ).

cnf(and_identity,axiom,
    and(X,ll1) = X ).

cnf(or_distributive,axiom,
    and(X,or(Y,Z)) = or(and(X,Y),and(X,Z)) ).

cnf(and_distributive,axiom,
    or(X,and(Y,Z)) = and(or(X,Y),or(X,Z)) ).

cnf(or_complement,axiom,
    or(X,not(X)) = ll1 ).

cnf(and_complement,axiom,
    and(X,not(X)) = ll0 ).

cnf(or_idempotent,axiom,
    or(X,X) = X ).

cnf(and_idempotent,axiom,
    and(X,X) = X ).

cnf(not_involution,axiom,
    not(not(X)) = X ).

cnf(ll0_inverse,axiom,
    not(ll0) = ll1 ).

cnf(ll1_inverse,axiom,
    not(ll1) = ll0 ).

cnf(or_boundedness,axiom,
    or(X,ll1) = ll1 ).

cnf(and_boundedness,axiom,
    and(X,ll0) = ll0 ).

cnf(or_absorption,axiom,
    or(X,and(X,Y)) = X ).

cnf(and_absorption,axiom,
    and(X,or(X,Y)) = X ).

cnf(or_demorgan,axiom,
    not(or(X,Y)) = and(not(X),not(Y)) ).

cnf(and_demorgan,axiom,
    not(and(X,Y)) = or(not(X),not(Y)) ).

%----full_adder problem:
cnf(xor_definition,axiom,
    or(and(not(X),Y),and(X,not(Y))) = xor(X,Y) ).

cnf(xor_commutative,axiom,
    xor(X,Y) = xor(Y,X) ).

cnf(xor_associative,axiom,
    xor(X,xor(Y,Z)) = xor(xor(X,Y),Z) ).

cnf(sum_def,negated_conjecture,
    xor(xor(a,b),cin) = sum_def ).

cnf(carry_def,negated_conjecture,
    or(and(cin,or(a,b)),and(not(cin),and(a,b))) = carry_def ).

cnf(t1,negated_conjecture,
    not(and(a,b)) = t1 ).

cnf(t2,negated_conjecture,
    not(and(a,t1)) = t2 ).

cnf(t3,negated_conjecture,
    not(and(b,t1)) = t3 ).

cnf(t4,negated_conjecture,
    not(and(t2,t3)) = t4 ).

cnf(t5,negated_conjecture,
    not(and(t4,cin)) = t5 ).

cnf(t6,negated_conjecture,
    not(and(t4,t5)) = t6 ).

cnf(t7,negated_conjecture,
    not(and(t5,cin)) = t7 ).

cnf(sum,negated_conjecture,
    not(and(t6,t7)) = sum ).

cnf(carry,negated_conjecture,
    not(and(t1,t5)) = carry ).

cnf(prove_circuit,negated_conjecture,
    ( sum != sum_def
    | carry != carry_def ) ).

%--------------------------------------------------------------------------
