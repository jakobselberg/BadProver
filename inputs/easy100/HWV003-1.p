%--------------------------------------------------------------------------
% File     : HWV003-1 : TPTP v9.2.1. Released v1.1.0.
% Domain   : Hardware Verification
% Problem  : One bit Full Adder
% Version  : [WO+92] axioms.
% English  :

% Refs     : [WO+92] Wos et al. (1992), Automated Reasoning: Introduction a
% Source   : [WO+92]
% Names    : - [WO+92]

% Status   : Unsatisfiable
% Rating   : 0.33 v9.1.0, 0.46 v9.0.0, 0.56 v8.2.0, 0.67 v8.1.0, 0.44 v7.5.0, 0.50 v7.4.0, 0.44 v7.3.0, 0.33 v7.2.0, 0.38 v7.1.0, 0.43 v7.0.0, 0.57 v6.4.0, 0.71 v6.3.0, 0.67 v6.2.0, 0.00 v6.1.0, 0.40 v6.0.0, 0.67 v5.5.0, 0.75 v5.4.0, 0.73 v5.3.0, 0.75 v5.2.0, 0.50 v5.1.0, 0.57 v5.0.0, 0.71 v4.1.0, 0.56 v4.0.1, 0.50 v4.0.0, 0.67 v3.7.0, 0.50 v3.5.0, 0.33 v3.3.0, 0.29 v3.1.0, 0.67 v2.7.0, 0.50 v2.6.0, 0.86 v2.5.0, 0.80 v2.4.0, 0.83 v2.3.0, 1.00 v2.2.1, 0.89 v2.2.0, 0.86 v2.1.0, 1.00 v2.0.0
% Syntax   : Number of clauses     :   47 (  47 unt;   0 nHn;  13 RR)
%            Number of literals    :   47 (  45 equ;   1 neg)
%            Maximal clause size   :    1 (   1 avg)
%            Maximal term depth    :    4 (   2 avg)
%            Number of predicates  :    2 (   1 usr;   0 prp; 2-2 aty)
%            Number of functors    :   20 (  20 usr;  14 con; 0-3 aty)
%            Number of variables   :   69 (  14 sgn)
% SPC      : CNF_UNS_RFO_SEQ_HRN

% Comments :
%--------------------------------------------------------------------------
%----Include definitions of AND, OR and NOT
include('Axioms/HWC002-0.ax').
%--------------------------------------------------------------------------
%----Simplifiers
cnf(demorgan1,axiom,
    not(and(X,Y)) = or(not(X),not(Y)) ).

cnf(demorgan2,axiom,
    not(or(X,Y)) = and(not(X),not(Y)) ).

cnf(not_involution,axiom,
    not(not(X)) = X ).

cnf(and_symmetry,negated_conjecture,
    and(X,Y) = and(Y,X) ).

cnf(or_symmetry,negated_conjecture,
    or(X,Y) = or(Y,X) ).

cnf(and_or_simplification,negated_conjecture,
    and(or(X,Y),Z) = or(and(X,Z),and(Y,Z)) ).

cnf(and_commutativity,negated_conjecture,
    and(and(X,Y),Z) = and(and(X,Z),Y) ).

cnf(or_commutativity,negated_conjecture,
    or(or(X,Y),Z) = or(or(X,Z),Y) ).

%----Evaluators
cnf(and_not_evaluation1,axiom,
    and(X,not(X)) = n0 ).

cnf(or_not_evaluation1,axiom,
    or(X,not(X)) = n1 ).

cnf(and_idempotency,axiom,
    and(X,X) = X ).

cnf(or_idempotency,axiom,
    or(X,X) = X ).

%----Evaluators of lists of 3 terms
cnf(and_not_evaluation2,axiom,
    and(and(X,Y),not(Y)) = n0 ).

cnf(and_not_evaluation3,axiom,
    and(and(X,Y),not(X)) = n0 ).

cnf(or_not_evaluation2,axiom,
    or(or(X,Y),not(Y)) = n1 ).

cnf(or_not_evaluation3,axiom,
    or(or(X,Y),not(X)) = n1 ).

cnf(and_evaluation1,axiom,
    and(and(X,Y),Y) = and(X,Y) ).

cnf(or_evaluation1,axiom,
    or(or(X,Y),Y) = or(X,Y) ).

%----Simplifiers for products of 4 terms
cnf(and_not_evaluation4,axiom,
    and(and(and(X1,X2),X3),not(X1)) = n0 ).

cnf(and_not_evaluation5,axiom,
    and(and(and(X1,X2),X3),not(X2)) = n0 ).

%----Subsumption type demodulators
cnf(and_or_subsumption1,axiom,
    or(and(X,Y),Y) = Y ).

cnf(and_or_subsumption2,axiom,
    or(and(X,Y),X) = X ).

cnf(and_or_subsumption3,axiom,
    or(or(and(X,Y),Z),Y) = or(Z,Y) ).

cnf(and_or_subsumption4,axiom,
    or(or(X,and(Y,Z)),Z) = or(X,Z) ).

%----Karnaugh map technique
cnf(karnaugh1,axiom,
    or(and(X,not(Y)),Y) = or(X,Y) ).

cnf(karnaugh2,axiom,
    or(and(not(X),not(Y)),Y) = or(Y,not(X)) ).

%----Karnaugh simplifier of inside product
cnf(karnaugh3,axiom,
    or(and(and(X,Y),not(Z)),and(X,Z)) = or(and(X,Y),and(X,Z)) ).

%----Circuit description
cnf(xor_definition,axiom,
    xor(X,Y) = or(and(X,not(Y)),and(Y,not(X))) ).

cnf(carryout_definition,negated_conjecture,
    carryout(X,Y,Z) = or(and(X,or(Y,Z)),and(not(X),and(Y,Z))) ).

cnf(sum_definition,negated_conjecture,
    sum(X,Y,Z) = xor(xor(X,Y),Z) ).

cnf(circuit1,negated_conjecture,
    a11 = not(and(a,b)) ).

cnf(circuit2,negated_conjecture,
    a12 = not(and(a11,a)) ).

cnf(circuit3,negated_conjecture,
    a13 = not(and(a11,b)) ).

cnf(circuit4,negated_conjecture,
    a14 = not(and(a12,a13)) ).

cnf(circuit5,negated_conjecture,
    a15 = not(and(a14,carryin)) ).

cnf(circuit6,negated_conjecture,
    a16 = not(and(a14,a15)) ).

cnf(circuit7,negated_conjecture,
    a17 = not(and(a15,carryin)) ).

cnf(circuit8,negated_conjecture,
    s1 = not(and(a16,a17)) ).

cnf(circuit9,negated_conjecture,
    c1 = not(and(a11,a15)) ).

cnf(the_output_circuit,negated_conjecture,
    circuit(s1,c1) ).

cnf(prove_circuit,negated_conjecture,
    ~ circuit(sum(a,b,carryin),carryout(a,b,carryin)) ).

%--------------------------------------------------------------------------
