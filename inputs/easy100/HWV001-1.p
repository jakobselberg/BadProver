%------------------------------------------------------------------------------
% File     : HWV001-1 : TPTP v9.2.1. Released v1.1.0.
% Domain   : Hardware Verification
% Problem  : Interchange inputs to outputs
% Version  : [ANL] axioms.
% English  : This validates one of the circuit designs that will take x and
%            y as input and output y and x without crossing any wires.

% Refs     : [WO+92] Wos et al. (1992), Automated Reasoning: Introduction a
% Source   : [ANL]
% Names    : - [WO+92]
%          : intchg_val.ver1.clauses [ANL]

% Status   : Unsatisfiable
% Rating   : 0.17 v9.1.0, 0.08 v9.0.0, 0.06 v8.2.0, 0.08 v8.1.0, 0.11 v7.5.0, 0.10 v7.4.0, 0.00 v7.0.0, 0.14 v6.3.0, 0.17 v6.2.0, 0.00 v6.0.0, 0.11 v5.5.0, 0.50 v5.4.0, 0.53 v5.3.0, 0.67 v5.2.0, 0.25 v5.1.0, 0.14 v5.0.0, 0.43 v4.1.0, 0.22 v4.0.1, 0.17 v3.3.0, 0.00 v3.1.0, 0.22 v2.7.0, 0.17 v2.6.0, 0.29 v2.5.0, 0.00 v2.4.0, 0.17 v2.3.0, 0.00 v2.2.1, 0.56 v2.2.0, 0.57 v2.1.0, 0.80 v2.0.0
% Syntax   : Number of clauses     :   47 (  47 unt;   0 nHn;  19 RR)
%            Number of literals    :   47 (  45 equ;   1 neg)
%            Maximal clause size   :    1 (   1 avg)
%            Maximal term depth    :    4 (   1 avg)
%            Number of predicates  :    2 (   1 usr;   0 prp; 2-2 aty)
%            Number of functors    :   24 (  24 usr;  19 con; 0-2 aty)
%            Number of variables   :   52 (   6 sgn)
% SPC      : CNF_UNS_RFO_SEQ_HRN

% Comments : See HWV002-1 for the design problem.
%------------------------------------------------------------------------------
%----Include definitions of AND, OR and NOT
include('Axioms/HWC002-0.ax').
%------------------------------------------------------------------------------
%----Commutativity and associativity
cnf(and_commutativity,axiom,
    and(X,Y) = and(Y,X) ).

cnf(or_commutativity,axiom,
    or(X,Y) = or(Y,X) ).

cnf(and_associativity,axiom,
    and(X,and(Y,Z)) = and(and(X,Y),Z) ).

cnf(or_associativity,axiom,
    or(X,or(Y,Z)) = or(or(X,Y),Z) ).

%----Sorting
cnf(or_sorting,axiom,
    or(or(X,Y),Z) = or(or(X,Z),Y) ).

cnf(and_sorting,axiom,
    and(and(X,Y),Z) = and(and(X,Z),Y) ).

%----Canonicalization to move Not to inside
cnf(not_canonicalization1,axiom,
    not(and(X,Y)) = or(not(X),not(Y)) ).

cnf(not_canonicalization2,axiom,
    not(or(X,Y)) = and(not(X),not(Y)) ).

%----Canonicalization to sum-of-products
cnf(and_or_canonicalization,axiom,
    and(or(X,Y),Z) = or(and(X,Z),and(Y,Z)) ).

%----Simplifiers
cnf(and_simplification1,axiom,
    and(X,X) = X ).

cnf(and_simplification2,axiom,
    and(and(X,Y),Y) = and(X,Y) ).

cnf(and_simplification3,axiom,
    and(and(X,Y),X) = and(X,Y) ).

cnf(or_simplification1,axiom,
    or(X,X) = X ).

cnf(or_simplification2,axiom,
    or(or(X,Y),Y) = or(X,Y) ).

cnf(or_simplification3,axiom,
    or(or(X,Y),X) = or(X,Y) ).

cnf(and_not_simplification1,axiom,
    and(X,not(X)) = n0 ).

cnf(and_not_simplification2,axiom,
    and(and(X,Y),not(Y)) = n0 ).

cnf(and_not_simplification3,axiom,
    and(and(X,Y),not(X)) = n0 ).

cnf(or_not_simplification1,axiom,
    or(X,not(X)) = n1 ).

cnf(or_not_simplification2,axiom,
    or(or(X,Y),not(Y)) = n1 ).

cnf(or_not_simplification3,axiom,
    or(or(X,Y),not(X)) = n1 ).

cnf(not_simplification,axiom,
    not(not(X)) = X ).

cnf(and_or_not_simplification1,axiom,
    or(and(X,Y),and(X,not(Y))) = X ).

cnf(and_or_not_simplification2,axiom,
    or(and(X,Y),and(Y,not(X))) = Y ).

%----Theorem clauses
cnf(constructor1,negated_conjecture,
    a1 = and(b1,b3) ).

cnf(constructor2,negated_conjecture,
    a2 = and(b2,b3) ).

cnf(constructor3,negated_conjecture,
    b1 = not(d1) ).

cnf(constructor4,negated_conjecture,
    b2 = not(d2) ).

cnf(constructor5,negated_conjecture,
    b3 = or(c1,c2) ).

cnf(constructor6,negated_conjecture,
    c1 = or(d1,d3) ).

cnf(constructor7,negated_conjecture,
    c2 = or(d2,d3) ).

cnf(constructor8,negated_conjecture,
    d3 = f3 ).

cnf(constructor9,negated_conjecture,
    d1 = not(e1) ).

cnf(constructor10,negated_conjecture,
    d2 = not(e2) ).

cnf(constructor11,negated_conjecture,
    e1 = or(f1,f3) ).

cnf(constructor12,negated_conjecture,
    e2 = or(f2,f3) ).

cnf(constructor13,negated_conjecture,
    f1 = not(i1) ).

cnf(constructor14,negated_conjecture,
    f2 = not(i2) ).

cnf(constructor15,negated_conjecture,
    f3 = and(i1,i2) ).

cnf(circuit_description,negated_conjecture,
    circuit(input(i1,i2),output(a1,a2)) ).

cnf(prove_interchange,negated_conjecture,
    ~ circuit(input(i1,i2),output(i2,i1)) ).

%------------------------------------------------------------------------------
