%------------------------------------------------------------------------------
% File     : HWV052-1.001.002 : TPTP v9.2.1. Released v4.1.0.
% Domain   : Hardware Verification
% Problem  : Faulty channel 1 2
% Version  : Especial.
% English  : The problem of sending N bits over a faulty channel that can
%            mutilate any one bit. We can use K extra bits to help us do this.
%            Satisfiable means that it is possible, unsatisfiable means that
%            it is not possible.

% Refs     : [Cla10] Claessen (2010), Email to Geoff Sutcliffe
% Source   : [Cla10]
% Names    : fault_1_2 [Cla10]

% Status   : Satisfiable
% Rating   : 0.38 v9.1.0, 0.44 v9.0.0, 0.40 v8.2.0, 0.60 v8.1.0, 0.62 v7.5.0, 0.56 v7.4.0, 0.55 v7.3.0, 0.56 v7.1.0, 0.62 v7.0.0, 0.57 v6.4.0, 0.29 v6.3.0, 0.25 v6.2.0, 0.10 v6.1.0, 0.33 v6.0.0, 0.29 v5.5.0, 0.38 v5.4.0, 0.60 v5.3.0, 0.56 v5.2.0, 0.60 v5.0.0, 0.67 v4.1.0
% Syntax   : Number of clauses     :    6 (   5 unt;   1 nHn;   1 RR)
%            Number of literals    :    7 (   7 equ;   1 neg)
%            Maximal clause size   :    2 (   1 avg)
%            Maximal term depth    :    4 (   2 avg)
%            Number of predicates  :    1 (   0 usr;   0 prp; 2-2 aty)
%            Number of functors    :    6 (   6 usr;   2 con; 0-3 aty)
%            Number of variables   :    6 (   0 sgn)
% SPC      : CNF_SAT_RFO_EQU_NUE

% Comments :
%------------------------------------------------------------------------------
cnf(bit_domain,axiom,
    ( X = o
    | X = i ) ).

cnf(bit_inverse,axiom,
    inv(X) != X ).

cnf(unpack1,axiom,
    unpack1(X1,pack1(X1),pack2(X1)) = X1 ).

cnf(unpack1_01,axiom,
    unpack1(inv(X1),pack1(X1),pack2(X1)) = X1 ).

cnf(unpack1_02,axiom,
    unpack1(X1,inv(pack1(X1)),pack2(X1)) = X1 ).

cnf(unpack1_03,axiom,
    unpack1(X1,pack1(X1),inv(pack2(X1))) = X1 ).

%------------------------------------------------------------------------------
