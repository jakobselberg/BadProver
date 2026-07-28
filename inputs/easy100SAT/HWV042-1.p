%------------------------------------------------------------------------------
% File     : HWV042-1 : TPTP v9.2.1. Released v5.3.0.
% Domain   : Software Verification
% Problem  : Robot verification problem 4
% Version  : Especial.
%            Theorem formulation: Epr encoding mode bitblast
% English  :

% Refs     : [Kha11] Khasidashvili (2011), Email to Geoff Sutcliffe
% Source   : [Kha11]
% Names    : robot_p4b200eBb.cnf [Kha11]

% Status   : Satisfiable
% Rating   : 0.43 v9.1.0, 0.75 v9.0.0, 0.67 v8.2.0, 0.40 v7.5.0, 0.50 v7.0.0, 0.40 v6.4.0, 0.33 v6.3.0, 0.50 v6.1.0, 0.60 v6.0.0, 0.67 v5.5.0, 0.33 v5.4.0, 0.83 v5.3.0
% Syntax   : Number of clauses     :  889 ( 617 unt;  73 nHn; 880 RR)
%            Number of literals    : 1521 ( 201 equ; 498 neg)
%            Maximal clause size   :  202 (   1 avg)
%            Maximal term depth    :    1 (   1 avg)
%            Number of predicates  :   87 (  86 usr;   0 prp; 1-2 aty)
%            Number of functors    :  205 ( 205 usr; 205 con; 0-0 aty)
%            Number of variables   :  320 (  14 sgn)
% SPC      : CNF_SAT_EPR_EQU_NUE

% Comments : Verification strategy is bmc1 with bound 200, Verification model
%            is Sequential word-level (with or w/o memories)
%------------------------------------------------------------------------------
cnf(addAssignment_13_2,axiom,
    ( v9(VarCurr)
    | ~ v13(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_13_1,axiom,
    ( v13(VarNext)
    | ~ v9(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_59_1_1_2,axiom,
    ( v19(VarCurr)
    | v13(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_59_1_1_1,axiom,
    ( v19(VarCurr)
    | v1(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_1_1_1_1_2,axiom,
    ( v22(VarCurr)
    | ~ v13(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_1_1_1_1_1,axiom,
    ( v22(VarCurr)
    | ~ v1(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_2_1_1_1,axiom,
    ( v18(VarCurr)
    | ~ v22(VarCurr)
    | ~ v19(VarCurr) ) ).

cnf(addAssignment_1_1_1,axiom,
    ~ v26(VarCurr) ).

cnf(addAssignmentInitValue_9_1,axiom,
    v36(constB0) ).

cnf(writeBinaryOperatorShiftedRanges_4_1_1_3,axiom,
    ( v36(VarCurr)
    | ~ v34(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_4_1_1_2,axiom,
    ( ~ v184(VarCurr)
    | ~ v34(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_4_1_1_1,axiom,
    ( v34(VarCurr)
    | v184(VarCurr)
    | ~ v36(VarCurr) ) ).

cnf(addAssignment_2_1_2,axiom,
    ( v34(VarCurr)
    | ~ v36(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_2_1_1,axiom,
    ( v36(VarNext)
    | ~ v34(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignmentInitValue_1_1_1_1,axiom,
    ~ v46(constB0) ).

cnf(writeBinaryOperatorShiftedRanges_5_1_1_3,axiom,
    ( v46(VarCurr)
    | ~ v47(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_5_1_1_2,axiom,
    ( ~ v184(VarCurr)
    | ~ v47(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_5_1_1_1,axiom,
    ( v47(VarCurr)
    | v184(VarCurr)
    | ~ v46(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_7_1_1_3,axiom,
    ( v36(VarCurr)
    | ~ v48(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_7_1_1_2,axiom,
    ( v54(VarCurr)
    | ~ v48(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_7_1_1_1,axiom,
    ( v48(VarCurr)
    | ~ v54(VarCurr)
    | ~ v36(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_8_1_3,axiom,
    ( v48(VarCurr)
    | v47(VarCurr)
    | ~ v44(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_8_1_2,axiom,
    ( v44(VarCurr)
    | ~ v47(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_8_1_1,axiom,
    ( v44(VarCurr)
    | ~ v48(VarCurr) ) ).

cnf(addAssignment_3_1_2,axiom,
    ( v44(VarCurr)
    | ~ v46(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_3_1_1,axiom,
    ( v46(VarNext)
    | ~ v44(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_9_1_1_3,axiom,
    ( v26(VarCurr)
    | ~ v54(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_9_1_1_2,axiom,
    ( v184(VarCurr)
    | ~ v54(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_9_1_1_1,axiom,
    ( v54(VarCurr)
    | ~ v184(VarCurr)
    | ~ v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_10_1_1_1_1,axiom,
    ( v53(VarCurr)
    | ~ v54(VarCurr)
    | ~ v46(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_11_1_4,axiom,
    ( v1(VarCurr)
    | v9(VarCurr)
    | ~ v64(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_11_1_3,axiom,
    ( ~ v1(VarCurr)
    | ~ v9(VarCurr)
    | ~ v64(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_11_1_2,axiom,
    ( v64(VarCurr)
    | v1(VarCurr)
    | ~ v9(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_11_1_1,axiom,
    ( v64(VarCurr)
    | v9(VarCurr)
    | ~ v1(VarCurr) ) ).

cnf(addAssignment_4_1_2,axiom,
    ( v26(VarCurr)
    | ~ v66(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_4_1_1,axiom,
    ( v66(VarNext)
    | ~ v26(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_3_1_2,axiom,
    ( v66(VarNext)
    | ~ v60(VarNext)
    | ~ v64(VarNext) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_3_1_1,axiom,
    ( v60(VarNext)
    | ~ v66(VarNext)
    | ~ v64(VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_3_1_1_2,axiom,
    ( v60(VarCurr)
    | ~ v60(VarNext)
    | v64(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_3_1_1_1,axiom,
    ( v60(VarNext)
    | ~ v60(VarCurr)
    | v64(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addBitVectorEqualityBitBlasted_16_1_2,axiom,
    ( v60(VarCurr)
    | ~ v26(VarCurr)
    | ~ v74(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_16_1_1,axiom,
    ( v26(VarCurr)
    | ~ v60(VarCurr)
    | ~ v74(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_13_1_1_1_1,axiom,
    ( v72(VarCurr)
    | v74(VarCurr)
    | v1(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_14_1_1_1_2,axiom,
    ( v78(VarCurr)
    | v9(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_14_1_1_1_1,axiom,
    ( v78(VarCurr)
    | v1(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_15_1_1_1_2,axiom,
    ( v80(VarCurr)
    | ~ v9(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_15_1_1_1_1,axiom,
    ( v80(VarCurr)
    | ~ v1(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_16_1_1_1,axiom,
    ( v76(VarCurr)
    | ~ v80(VarCurr)
    | ~ v78(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_17_1_1_1,axiom,
    ( v71(VarCurr)
    | ~ v76(VarCurr)
    | ~ v72(VarCurr) ) ).

cnf(addAssignmentInitValue_2_1_1,axiom,
    ~ v90(constB0,bitIndex0) ).

cnf(addAssignmentInitValue_3_1_1,axiom,
    ~ v90(constB0,bitIndex1) ).

cnf(addAssignmentInitValue_4_1_1,axiom,
    ~ v90(constB0,bitIndex2) ).

cnf(addAssignment_5_1_2,axiom,
    ( v1(VarCurr)
    | ~ v104(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_5_1_1,axiom,
    ( v104(VarNext)
    | ~ v1(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeUnaryOperator_12_1_2,axiom,
    ( v104(VarNext)
    | v102(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeUnaryOperator_12_1_1,axiom,
    ( ~ v102(VarNext)
    | ~ v104(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_18_1_3,axiom,
    ( v102(VarNext)
    | ~ v101(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_18_1_2,axiom,
    ( v1(VarNext)
    | ~ v101(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_18_1_1,axiom,
    ( v101(VarNext)
    | ~ v1(VarNext)
    | ~ v102(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addBitVectorEqualityBitBlasted_2_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex0)
    | ~ v119(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_2_1_1_3,axiom,
    ( ~ v90(VarCurr,bitIndex1)
    | ~ v119(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_2_1_1_2,axiom,
    ( ~ v90(VarCurr,bitIndex2)
    | ~ v119(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_2_1_1_1,axiom,
    ( v119(VarCurr)
    | v90(VarCurr,bitIndex2)
    | v90(VarCurr,bitIndex1)
    | v90(VarCurr,bitIndex0) ) ).

cnf(addBitVectorEqualityBitBlasted_3_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex1)
    | ~ v120(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_3_1_1_3,axiom,
    ( ~ v90(VarCurr,bitIndex2)
    | ~ v120(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_3_1_1_2,axiom,
    ( v90(VarCurr,bitIndex0)
    | ~ v120(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_3_1_1_1,axiom,
    ( v120(VarCurr)
    | ~ v90(VarCurr,bitIndex0)
    | v90(VarCurr,bitIndex2)
    | v90(VarCurr,bitIndex1) ) ).

cnf(writeBinaryOperatorShiftedRanges_19_1_3,axiom,
    ( v120(VarCurr)
    | v119(VarCurr)
    | ~ v118(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_19_1_2,axiom,
    ( v118(VarCurr)
    | ~ v119(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_19_1_1,axiom,
    ( v118(VarCurr)
    | ~ v120(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_4_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex0)
    | ~ v121(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_4_1_1_3,axiom,
    ( ~ v90(VarCurr,bitIndex2)
    | ~ v121(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_4_1_1_2,axiom,
    ( v90(VarCurr,bitIndex1)
    | ~ v121(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_4_1_1_1,axiom,
    ( v121(VarCurr)
    | ~ v90(VarCurr,bitIndex1)
    | v90(VarCurr,bitIndex2)
    | v90(VarCurr,bitIndex0) ) ).

cnf(writeBinaryOperatorShiftedRanges_20_1_3,axiom,
    ( v121(VarCurr)
    | v118(VarCurr)
    | ~ v117(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_20_1_2,axiom,
    ( v117(VarCurr)
    | ~ v118(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_20_1_1,axiom,
    ( v117(VarCurr)
    | ~ v121(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_5_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex2)
    | ~ v122(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_5_1_1_3,axiom,
    ( v90(VarCurr,bitIndex0)
    | ~ v122(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_5_1_1_2,axiom,
    ( v90(VarCurr,bitIndex1)
    | ~ v122(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_5_1_1_1,axiom,
    ( v122(VarCurr)
    | ~ v90(VarCurr,bitIndex1)
    | ~ v90(VarCurr,bitIndex0)
    | v90(VarCurr,bitIndex2) ) ).

cnf(writeBinaryOperatorShiftedRanges_21_1_3,axiom,
    ( v122(VarCurr)
    | v117(VarCurr)
    | ~ v116(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_21_1_2,axiom,
    ( v116(VarCurr)
    | ~ v117(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_21_1_1,axiom,
    ( v116(VarCurr)
    | ~ v122(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_6_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex0)
    | ~ v123(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_6_1_1_3,axiom,
    ( ~ v90(VarCurr,bitIndex1)
    | ~ v123(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_6_1_1_2,axiom,
    ( v90(VarCurr,bitIndex2)
    | ~ v123(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_6_1_1_1,axiom,
    ( v123(VarCurr)
    | ~ v90(VarCurr,bitIndex2)
    | v90(VarCurr,bitIndex1)
    | v90(VarCurr,bitIndex0) ) ).

cnf(writeBinaryOperatorShiftedRanges_22_1_3,axiom,
    ( v123(VarCurr)
    | v116(VarCurr)
    | ~ v115(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_22_1_2,axiom,
    ( v115(VarCurr)
    | ~ v116(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_22_1_1,axiom,
    ( v115(VarCurr)
    | ~ v123(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_7_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex1)
    | ~ v124(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_7_1_1_3,axiom,
    ( v90(VarCurr,bitIndex0)
    | ~ v124(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_7_1_1_2,axiom,
    ( v90(VarCurr,bitIndex2)
    | ~ v124(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_7_1_1_1,axiom,
    ( v124(VarCurr)
    | ~ v90(VarCurr,bitIndex2)
    | ~ v90(VarCurr,bitIndex0)
    | v90(VarCurr,bitIndex1) ) ).

cnf(writeBinaryOperatorShiftedRanges_23_1_3,axiom,
    ( v124(VarCurr)
    | v115(VarCurr)
    | ~ v114(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_23_1_2,axiom,
    ( v114(VarCurr)
    | ~ v115(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_23_1_1,axiom,
    ( v114(VarCurr)
    | ~ v124(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_8_1_1_4,axiom,
    ( ~ v90(VarCurr,bitIndex0)
    | ~ v125(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_8_1_1_3,axiom,
    ( v90(VarCurr,bitIndex1)
    | ~ v125(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_8_1_1_2,axiom,
    ( v90(VarCurr,bitIndex2)
    | ~ v125(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_8_1_1_1,axiom,
    ( v125(VarCurr)
    | ~ v90(VarCurr,bitIndex2)
    | ~ v90(VarCurr,bitIndex1)
    | v90(VarCurr,bitIndex0) ) ).

cnf(writeBinaryOperatorShiftedRanges_24_1_3,axiom,
    ( v125(VarCurr)
    | v114(VarCurr)
    | ~ v113(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_24_1_2,axiom,
    ( v113(VarCurr)
    | ~ v114(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_24_1_1,axiom,
    ( v113(VarCurr)
    | ~ v125(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_25_1_1_3,axiom,
    ( ~ v26(VarCurr)
    | ~ v112(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_25_1_1_2,axiom,
    ( v113(VarCurr)
    | ~ v112(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_25_1_1_1,axiom,
    ( v112(VarCurr)
    | ~ v113(VarCurr)
    | v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_26_1_1_3,axiom,
    ( v112(VarCurr)
    | v26(VarCurr)
    | ~ v108(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_26_1_1_2,axiom,
    ( v108(VarCurr)
    | ~ v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_26_1_1_1,axiom,
    ( v108(VarCurr)
    | ~ v112(VarCurr) ) ).

cnf(addAssignment_6_1_2,axiom,
    ( v108(VarCurr)
    | ~ v110(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_6_1_1,axiom,
    ( v110(VarNext)
    | ~ v108(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_27_1_3,axiom,
    ( v101(VarNext)
    | ~ v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_27_1_2,axiom,
    ( v110(VarNext)
    | ~ v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_27_1_1,axiom,
    ( v100(VarNext)
    | ~ v110(VarNext)
    | ~ v101(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_4_3,axiom,
    ( v130(VarCurr,bitIndex2)
    | ~ v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_4_2,axiom,
    ( ~ v130(VarCurr,bitIndex1)
    | ~ v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_4_1,axiom,
    ( ~ v130(VarCurr,bitIndex0)
    | ~ v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_4_3,axiom,
    ( ~ v130(VarCurr,bitIndex2)
    | ~ v120(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_4_2,axiom,
    ( v130(VarCurr,bitIndex1)
    | ~ v120(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_4_1,axiom,
    ( ~ v130(VarCurr,bitIndex0)
    | ~ v120(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges2_2_3,axiom,
    ( ~ v130(VarCurr,bitIndex2)
    | ~ v121(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges2_2_2,axiom,
    ( v130(VarCurr,bitIndex1)
    | ~ v121(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges2_2_1,axiom,
    ( v130(VarCurr,bitIndex0)
    | ~ v121(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges3_1_3,axiom,
    ( v130(VarCurr,bitIndex2)
    | ~ v122(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges3_1_2,axiom,
    ( ~ v130(VarCurr,bitIndex1)
    | ~ v122(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges3_1_1,axiom,
    ( ~ v130(VarCurr,bitIndex0)
    | ~ v122(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges4_1_3,axiom,
    ( v130(VarCurr,bitIndex2)
    | ~ v123(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges4_1_2,axiom,
    ( v130(VarCurr,bitIndex1)
    | ~ v123(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges4_1_1,axiom,
    ( ~ v130(VarCurr,bitIndex0)
    | ~ v123(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges5_1_3,axiom,
    ( ~ v130(VarCurr,bitIndex2)
    | ~ v124(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges5_1_2,axiom,
    ( v130(VarCurr,bitIndex1)
    | ~ v124(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges5_1_1,axiom,
    ( v130(VarCurr,bitIndex0)
    | ~ v124(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges6_1_3,axiom,
    ( ~ v130(VarCurr,bitIndex2)
    | v124(VarCurr)
    | v123(VarCurr)
    | v122(VarCurr)
    | v121(VarCurr)
    | v120(VarCurr)
    | v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges6_1_2,axiom,
    ( ~ v130(VarCurr,bitIndex1)
    | v124(VarCurr)
    | v123(VarCurr)
    | v122(VarCurr)
    | v121(VarCurr)
    | v120(VarCurr)
    | v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges6_1_1,axiom,
    ( v130(VarCurr,bitIndex0)
    | v124(VarCurr)
    | v123(VarCurr)
    | v122(VarCurr)
    | v121(VarCurr)
    | v120(VarCurr)
    | v119(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_1_1_1_3,axiom,
    ( ~ v127(VarCurr,bitIndex2)
    | ~ v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_1_1_1_2,axiom,
    ( ~ v127(VarCurr,bitIndex1)
    | ~ v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_1_1_1_1,axiom,
    ( ~ v127(VarCurr,bitIndex0)
    | ~ v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_6,axiom,
    ( v130(VarCurr,bitIndex2)
    | ~ v127(VarCurr,bitIndex2)
    | v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_5,axiom,
    ( v127(VarCurr,bitIndex2)
    | ~ v130(VarCurr,bitIndex2)
    | v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_4,axiom,
    ( v130(VarCurr,bitIndex1)
    | ~ v127(VarCurr,bitIndex1)
    | v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_3,axiom,
    ( v127(VarCurr,bitIndex1)
    | ~ v130(VarCurr,bitIndex1)
    | v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_2,axiom,
    ( v130(VarCurr,bitIndex0)
    | ~ v127(VarCurr,bitIndex0)
    | v26(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_1_1_1_1,axiom,
    ( v127(VarCurr,bitIndex0)
    | ~ v130(VarCurr,bitIndex0)
    | v26(VarCurr) ) ).

cnf(addAssignment_7_1_6,axiom,
    ( v127(VarCurr,bitIndex2)
    | ~ v129(VarNext,bitIndex2)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_7_1_5,axiom,
    ( v129(VarNext,bitIndex2)
    | ~ v127(VarCurr,bitIndex2)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_7_1_4,axiom,
    ( v127(VarCurr,bitIndex1)
    | ~ v129(VarNext,bitIndex1)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_7_1_3,axiom,
    ( v129(VarNext,bitIndex1)
    | ~ v127(VarCurr,bitIndex1)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_7_1_2,axiom,
    ( v127(VarCurr,bitIndex0)
    | ~ v129(VarNext,bitIndex0)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_7_1_1,axiom,
    ( v129(VarNext,bitIndex0)
    | ~ v127(VarCurr,bitIndex0)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_6,axiom,
    ( v129(VarNext,bitIndex2)
    | ~ v90(VarNext,bitIndex2)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_5,axiom,
    ( v90(VarNext,bitIndex2)
    | ~ v129(VarNext,bitIndex2)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_4,axiom,
    ( v129(VarNext,bitIndex1)
    | ~ v90(VarNext,bitIndex1)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_3,axiom,
    ( v90(VarNext,bitIndex1)
    | ~ v129(VarNext,bitIndex1)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_2,axiom,
    ( v129(VarNext,bitIndex0)
    | ~ v90(VarNext,bitIndex0)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges0_1_1,axiom,
    ( v90(VarNext,bitIndex0)
    | ~ v129(VarNext,bitIndex0)
    | ~ v100(VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_6,axiom,
    ( v90(VarCurr,bitIndex2)
    | ~ v90(VarNext,bitIndex2)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_5,axiom,
    ( v90(VarNext,bitIndex2)
    | ~ v90(VarCurr,bitIndex2)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_4,axiom,
    ( v90(VarCurr,bitIndex1)
    | ~ v90(VarNext,bitIndex1)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_3,axiom,
    ( v90(VarNext,bitIndex1)
    | ~ v90(VarCurr,bitIndex1)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_2,axiom,
    ( v90(VarCurr,bitIndex0)
    | ~ v90(VarNext,bitIndex0)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addCaseBooleanConditionEqualRanges1_1_1,axiom,
    ( v90(VarNext,bitIndex0)
    | ~ v90(VarCurr,bitIndex0)
    | v100(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_8_1_6,axiom,
    ( v90(VarCurr,bitIndex2)
    | ~ v88(VarCurr,bitIndex2) ) ).

cnf(addAssignment_8_1_5,axiom,
    ( v88(VarCurr,bitIndex2)
    | ~ v90(VarCurr,bitIndex2) ) ).

cnf(addAssignment_8_1_4,axiom,
    ( v90(VarCurr,bitIndex1)
    | ~ v88(VarCurr,bitIndex1) ) ).

cnf(addAssignment_8_1_3,axiom,
    ( v88(VarCurr,bitIndex1)
    | ~ v90(VarCurr,bitIndex1) ) ).

cnf(addAssignment_8_1_2,axiom,
    ( v90(VarCurr,bitIndex0)
    | ~ v88(VarCurr,bitIndex0) ) ).

cnf(addAssignment_8_1_1,axiom,
    ( v88(VarCurr,bitIndex0)
    | ~ v90(VarCurr,bitIndex0) ) ).

cnf(addAssignmentInitValue_5_1_1,axiom,
    ~ v86(constB0) ).

cnf(addBitVectorEqualityBitBlasted_9_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex0)
    | ~ v139(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_9_1_1_3,axiom,
    ( ~ v88(VarCurr,bitIndex1)
    | ~ v139(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_9_1_1_2,axiom,
    ( ~ v88(VarCurr,bitIndex2)
    | ~ v139(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_9_1_1_1,axiom,
    ( v139(VarCurr)
    | v88(VarCurr,bitIndex2)
    | v88(VarCurr,bitIndex1)
    | v88(VarCurr,bitIndex0) ) ).

cnf(addBitVectorEqualityBitBlasted_10_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex1)
    | ~ v140(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_10_1_1_3,axiom,
    ( ~ v88(VarCurr,bitIndex2)
    | ~ v140(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_10_1_1_2,axiom,
    ( v88(VarCurr,bitIndex0)
    | ~ v140(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_10_1_1_1,axiom,
    ( v140(VarCurr)
    | ~ v88(VarCurr,bitIndex0)
    | v88(VarCurr,bitIndex2)
    | v88(VarCurr,bitIndex1) ) ).

cnf(addBitVectorEqualityBitBlasted_11_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex2)
    | ~ v141(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_11_1_1_3,axiom,
    ( v88(VarCurr,bitIndex0)
    | ~ v141(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_11_1_1_2,axiom,
    ( v88(VarCurr,bitIndex1)
    | ~ v141(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_11_1_1_1,axiom,
    ( v141(VarCurr)
    | ~ v88(VarCurr,bitIndex1)
    | ~ v88(VarCurr,bitIndex0)
    | v88(VarCurr,bitIndex2) ) ).

cnf(addBitVectorEqualityBitBlasted_12_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex0)
    | ~ v143(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_12_1_1_3,axiom,
    ( ~ v88(VarCurr,bitIndex2)
    | ~ v143(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_12_1_1_2,axiom,
    ( v88(VarCurr,bitIndex1)
    | ~ v143(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_12_1_1_1,axiom,
    ( v143(VarCurr)
    | ~ v88(VarCurr,bitIndex1)
    | v88(VarCurr,bitIndex2)
    | v88(VarCurr,bitIndex0) ) ).

cnf(addBitVectorEqualityBitBlasted_13_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex0)
    | ~ v144(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_13_1_1_3,axiom,
    ( v88(VarCurr,bitIndex1)
    | ~ v144(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_13_1_1_2,axiom,
    ( v88(VarCurr,bitIndex2)
    | ~ v144(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_13_1_1_1,axiom,
    ( v144(VarCurr)
    | ~ v88(VarCurr,bitIndex2)
    | ~ v88(VarCurr,bitIndex1)
    | v88(VarCurr,bitIndex0) ) ).

cnf(writeBinaryOperatorShiftedRanges_30_1_3,axiom,
    ( v144(VarCurr)
    | v143(VarCurr)
    | ~ v142(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_30_1_2,axiom,
    ( v142(VarCurr)
    | ~ v143(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_30_1_1,axiom,
    ( v142(VarCurr)
    | ~ v144(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_14_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex0)
    | ~ v146(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_14_1_1_3,axiom,
    ( ~ v88(VarCurr,bitIndex1)
    | ~ v146(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_14_1_1_2,axiom,
    ( v88(VarCurr,bitIndex2)
    | ~ v146(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_14_1_1_1,axiom,
    ( v146(VarCurr)
    | ~ v88(VarCurr,bitIndex2)
    | v88(VarCurr,bitIndex1)
    | v88(VarCurr,bitIndex0) ) ).

cnf(addBitVectorEqualityBitBlasted_15_1_1_4,axiom,
    ( ~ v88(VarCurr,bitIndex1)
    | ~ v147(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_15_1_1_3,axiom,
    ( v88(VarCurr,bitIndex0)
    | ~ v147(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_15_1_1_2,axiom,
    ( v88(VarCurr,bitIndex2)
    | ~ v147(VarCurr) ) ).

cnf(addBitVectorEqualityBitBlasted_15_1_1_1,axiom,
    ( v147(VarCurr)
    | ~ v88(VarCurr,bitIndex2)
    | ~ v88(VarCurr,bitIndex0)
    | v88(VarCurr,bitIndex1) ) ).

cnf(writeBinaryOperatorShiftedRanges_32_1_3,axiom,
    ( v147(VarCurr)
    | v146(VarCurr)
    | ~ v145(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_32_1_2,axiom,
    ( v145(VarCurr)
    | ~ v146(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_32_1_1,axiom,
    ( v145(VarCurr)
    | ~ v147(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_2_1_1_1,axiom,
    ( ~ v148(VarCurr)
    | ~ v166(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_2_1_1_1,axiom,
    ( v148(VarCurr)
    | v166(VarCurr) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_4_1_2,axiom,
    ( v148(VarNext)
    | ~ v86(VarNext)
    | ~ v165(VarNext) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_4_1_1,axiom,
    ( v86(VarNext)
    | ~ v148(VarNext)
    | ~ v165(VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_4_1_1_2,axiom,
    ( v86(VarCurr)
    | ~ v86(VarNext)
    | v165(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_4_1_1_1,axiom,
    ( v86(VarNext)
    | ~ v86(VarCurr)
    | v165(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignmentInitValue_6_1_1,axiom,
    ~ v162(constB0) ).

cnf(writeBinaryOperatorShiftedRanges_38_1_1_3,axiom,
    ( v170(VarCurr)
    | v141(VarCurr)
    | ~ v167(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_38_1_1_2,axiom,
    ( v167(VarCurr)
    | ~ v141(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_38_1_1_1,axiom,
    ( v167(VarCurr)
    | ~ v170(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_39_1_1_3,axiom,
    ( v167(VarCurr)
    | v142(VarCurr)
    | ~ v166(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_39_1_1_2,axiom,
    ( v166(VarCurr)
    | ~ v142(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_39_1_1_1,axiom,
    ( v166(VarCurr)
    | ~ v167(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_40_1_1_3,axiom,
    ( v166(VarCurr)
    | v145(VarCurr)
    | ~ v165(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_40_1_1_2,axiom,
    ( v165(VarCurr)
    | ~ v145(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_40_1_1_1,axiom,
    ( v165(VarCurr)
    | ~ v166(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_41_1_3,axiom,
    ( v140(VarCurr)
    | v139(VarCurr)
    | ~ v170(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_41_1_2,axiom,
    ( v170(VarCurr)
    | ~ v139(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_41_1_1,axiom,
    ( v170(VarCurr)
    | ~ v140(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges0_3_1_1,axiom,
    ( ~ v169(VarCurr)
    | ~ v170(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges1_3_1_1,axiom,
    ( v169(VarCurr)
    | ~ v141(VarCurr) ) ).

cnf(addParallelCaseBooleanConditionEqualRanges2_1_1_1,axiom,
    ( ~ v169(VarCurr)
    | v141(VarCurr)
    | v170(VarCurr) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_5_2,axiom,
    ( v169(VarNext)
    | ~ v162(VarNext)
    | ~ v165(VarNext) ) ).

cnf(addConditionBooleanCondEqualRangesThenBranch_5_1,axiom,
    ( v162(VarNext)
    | ~ v169(VarNext)
    | ~ v165(VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_5_1_2,axiom,
    ( v162(VarCurr)
    | ~ v162(VarNext)
    | v165(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(aaddConditionBooleanCondEqualRangesElseBranch_5_1_1,axiom,
    ( v162(VarNext)
    | ~ v162(VarCurr)
    | v165(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignmentInitValue_7_1_1_1,axiom,
    ~ v180(constB0) ).

cnf(writeBinaryOperatorShiftedRanges_43_1_1_3,axiom,
    ( v9(VarCurr)
    | ~ v184(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_43_1_1_2,axiom,
    ( ~ v1(VarCurr)
    | ~ v184(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_43_1_1_1,axiom,
    ( v184(VarCurr)
    | v1(VarCurr)
    | ~ v9(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_44_1_1_3,axiom,
    ( v184(VarCurr)
    | v26(VarCurr)
    | ~ v183(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_44_1_1_2,axiom,
    ( v183(VarCurr)
    | ~ v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_44_1_1_1,axiom,
    ( v183(VarCurr)
    | ~ v184(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_45_1_1_3,axiom,
    ( ~ v183(VarCurr)
    | ~ v181(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_45_1_1_2,axiom,
    ( v180(VarCurr)
    | ~ v181(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_45_1_1_1,axiom,
    ( v181(VarCurr)
    | ~ v180(VarCurr)
    | v183(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_46_1_1_3,axiom,
    ( v162(VarCurr)
    | ~ v187(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_46_1_1_2,axiom,
    ( v184(VarCurr)
    | ~ v187(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_46_1_1_1,axiom,
    ( v187(VarCurr)
    | ~ v184(VarCurr)
    | ~ v162(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_47_1_1_3,axiom,
    ( ~ v26(VarCurr)
    | ~ v185(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_47_1_1_2,axiom,
    ( v187(VarCurr)
    | ~ v185(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_47_1_1_1,axiom,
    ( v185(VarCurr)
    | ~ v187(VarCurr)
    | v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_48_1_3,axiom,
    ( v185(VarCurr)
    | v181(VarCurr)
    | ~ v178(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_48_1_2,axiom,
    ( v178(VarCurr)
    | ~ v181(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_48_1_1,axiom,
    ( v178(VarCurr)
    | ~ v185(VarCurr) ) ).

cnf(addAssignment_11_1_2,axiom,
    ( v178(VarCurr)
    | ~ v180(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_11_1_1,axiom,
    ( v180(VarNext)
    | ~ v178(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignmentInitValue_8_1_1_1,axiom,
    ~ v196(constB0) ).

cnf(writeBinaryOperatorShiftedRanges_49_1_1_3,axiom,
    ( ~ v183(VarCurr)
    | ~ v197(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_49_1_1_2,axiom,
    ( v196(VarCurr)
    | ~ v197(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_49_1_1_1,axiom,
    ( v197(VarCurr)
    | ~ v196(VarCurr)
    | v183(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_50_1_1_3,axiom,
    ( v86(VarCurr)
    | ~ v200(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_50_1_1_2,axiom,
    ( v184(VarCurr)
    | ~ v200(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_50_1_1_1,axiom,
    ( v200(VarCurr)
    | ~ v184(VarCurr)
    | ~ v86(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_51_1_1_3,axiom,
    ( ~ v26(VarCurr)
    | ~ v199(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_51_1_1_2,axiom,
    ( v200(VarCurr)
    | ~ v199(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_51_1_1_1,axiom,
    ( v199(VarCurr)
    | ~ v200(VarCurr)
    | v26(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_52_1_1_3,axiom,
    ( v180(VarCurr)
    | ~ v198(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_52_1_1_2,axiom,
    ( v199(VarCurr)
    | ~ v198(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_52_1_1_1,axiom,
    ( v198(VarCurr)
    | ~ v199(VarCurr)
    | ~ v180(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_53_1_3,axiom,
    ( v198(VarCurr)
    | v197(VarCurr)
    | ~ v194(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_53_1_2,axiom,
    ( v194(VarCurr)
    | ~ v197(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_53_1_1,axiom,
    ( v194(VarCurr)
    | ~ v198(VarCurr) ) ).

cnf(addAssignment_12_1_2,axiom,
    ( v194(VarCurr)
    | ~ v196(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(addAssignment_12_1_1,axiom,
    ( v196(VarNext)
    | ~ v194(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(writeBinaryOperatorShiftedRanges_54_1_1_1_2,axiom,
    ( ~ v86(VarCurr)
    | ~ v207(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_54_1_1_1_1,axiom,
    ( v184(VarCurr)
    | ~ v207(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_55_1_1_1_2,axiom,
    ( ~ v26(VarCurr)
    | ~ v206(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_55_1_1_1_1,axiom,
    ( v207(VarCurr)
    | ~ v206(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_56_1_1_1_2,axiom,
    ( v180(VarCurr)
    | ~ v205(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_56_1_1_1_1,axiom,
    ( v206(VarCurr)
    | ~ v205(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_57_1_1_1_2,axiom,
    ( v196(VarCurr)
    | ~ v209(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_57_1_1_1_1,axiom,
    ( v206(VarCurr)
    | ~ v209(VarCurr) ) ).

cnf(writeBinaryOperatorShiftedRanges_58_1_1_1,axiom,
    ( v209(VarCurr)
    | v205(VarCurr)
    | ~ v204(VarCurr) ) ).

cnf(addGlobalAssumption_3_1_1,axiom,
    ~ v18(VarCurr) ).

cnf(addGlobalAssumption_1_1_1_1,axiom,
    ~ v71(VarCurr) ).

cnf(addGlobalAssumption_2_1_1_1,axiom,
    ~ v53(VarCurr) ).

cnf(addAssertion_1_1_2,negated_conjecture,
    reachableState(sK0_VarCurr) ).

cnf(addAssertion_1_1_1,negated_conjecture,
    v204(sK0_VarCurr) ).

cnf(reachableStateAxiom_203,axiom,
    reachableState(constB0) ).

cnf(reachableStateAxiom_1_1,axiom,
    reachableState(constB1) ).

cnf(reachableStateAxiom_2_1,axiom,
    reachableState(constB2) ).

cnf(reachableStateAxiom_3_1,axiom,
    reachableState(constB3) ).

cnf(reachableStateAxiom_4_1,axiom,
    reachableState(constB4) ).

cnf(reachableStateAxiom_5_1,axiom,
    reachableState(constB5) ).

cnf(reachableStateAxiom_6_1,axiom,
    reachableState(constB6) ).

cnf(reachableStateAxiom_7_1,axiom,
    reachableState(constB7) ).

cnf(reachableStateAxiom_8_1,axiom,
    reachableState(constB8) ).

cnf(reachableStateAxiom_9_1,axiom,
    reachableState(constB9) ).

cnf(reachableStateAxiom_10_1,axiom,
    reachableState(constB10) ).

cnf(reachableStateAxiom_11_1,axiom,
    reachableState(constB11) ).

cnf(reachableStateAxiom_12_1,axiom,
    reachableState(constB12) ).

cnf(reachableStateAxiom_13_1,axiom,
    reachableState(constB13) ).

cnf(reachableStateAxiom_14_1,axiom,
    reachableState(constB14) ).

cnf(reachableStateAxiom_15_1,axiom,
    reachableState(constB15) ).

cnf(reachableStateAxiom_16_1,axiom,
    reachableState(constB16) ).

cnf(reachableStateAxiom_17_1,axiom,
    reachableState(constB17) ).

cnf(reachableStateAxiom_18_1,axiom,
    reachableState(constB18) ).

cnf(reachableStateAxiom_19_1,axiom,
    reachableState(constB19) ).

cnf(reachableStateAxiom_20_1,axiom,
    reachableState(constB20) ).

cnf(reachableStateAxiom_21_1,axiom,
    reachableState(constB21) ).

cnf(reachableStateAxiom_22_1,axiom,
    reachableState(constB22) ).

cnf(reachableStateAxiom_23_1,axiom,
    reachableState(constB23) ).

cnf(reachableStateAxiom_24_1,axiom,
    reachableState(constB24) ).

cnf(reachableStateAxiom_25_1,axiom,
    reachableState(constB25) ).

cnf(reachableStateAxiom_26_1,axiom,
    reachableState(constB26) ).

cnf(reachableStateAxiom_27_1,axiom,
    reachableState(constB27) ).

cnf(reachableStateAxiom_28_1,axiom,
    reachableState(constB28) ).

cnf(reachableStateAxiom_29_1,axiom,
    reachableState(constB29) ).

cnf(reachableStateAxiom_30_1,axiom,
    reachableState(constB30) ).

cnf(reachableStateAxiom_31_1,axiom,
    reachableState(constB31) ).

cnf(reachableStateAxiom_32_1,axiom,
    reachableState(constB32) ).

cnf(reachableStateAxiom_33_1,axiom,
    reachableState(constB33) ).

cnf(reachableStateAxiom_34_1,axiom,
    reachableState(constB34) ).

cnf(reachableStateAxiom_35_1,axiom,
    reachableState(constB35) ).

cnf(reachableStateAxiom_36_1,axiom,
    reachableState(constB36) ).

cnf(reachableStateAxiom_37_1,axiom,
    reachableState(constB37) ).

cnf(reachableStateAxiom_38_1,axiom,
    reachableState(constB38) ).

cnf(reachableStateAxiom_39_1,axiom,
    reachableState(constB39) ).

cnf(reachableStateAxiom_40_1,axiom,
    reachableState(constB40) ).

cnf(reachableStateAxiom_41_1,axiom,
    reachableState(constB41) ).

cnf(reachableStateAxiom_42_1,axiom,
    reachableState(constB42) ).

cnf(reachableStateAxiom_43_1,axiom,
    reachableState(constB43) ).

cnf(reachableStateAxiom_44_1,axiom,
    reachableState(constB44) ).

cnf(reachableStateAxiom_45_1,axiom,
    reachableState(constB45) ).

cnf(reachableStateAxiom_46_1,axiom,
    reachableState(constB46) ).

cnf(reachableStateAxiom_47_1,axiom,
    reachableState(constB47) ).

cnf(reachableStateAxiom_48_1,axiom,
    reachableState(constB48) ).

cnf(reachableStateAxiom_49_1,axiom,
    reachableState(constB49) ).

cnf(reachableStateAxiom_50_1,axiom,
    reachableState(constB50) ).

cnf(reachableStateAxiom_51_1,axiom,
    reachableState(constB51) ).

cnf(reachableStateAxiom_52_1,axiom,
    reachableState(constB52) ).

cnf(reachableStateAxiom_53_1,axiom,
    reachableState(constB53) ).

cnf(reachableStateAxiom_54_1,axiom,
    reachableState(constB54) ).

cnf(reachableStateAxiom_55_1,axiom,
    reachableState(constB55) ).

cnf(reachableStateAxiom_56_1,axiom,
    reachableState(constB56) ).

cnf(reachableStateAxiom_57_1,axiom,
    reachableState(constB57) ).

cnf(reachableStateAxiom_58_1,axiom,
    reachableState(constB58) ).

cnf(reachableStateAxiom_59_1,axiom,
    reachableState(constB59) ).

cnf(reachableStateAxiom_60_1,axiom,
    reachableState(constB60) ).

cnf(reachableStateAxiom_61_1,axiom,
    reachableState(constB61) ).

cnf(reachableStateAxiom_62_1,axiom,
    reachableState(constB62) ).

cnf(reachableStateAxiom_63_1,axiom,
    reachableState(constB63) ).

cnf(reachableStateAxiom_64_1,axiom,
    reachableState(constB64) ).

cnf(reachableStateAxiom_65_1,axiom,
    reachableState(constB65) ).

cnf(reachableStateAxiom_66_1,axiom,
    reachableState(constB66) ).

cnf(reachableStateAxiom_67_1,axiom,
    reachableState(constB67) ).

cnf(reachableStateAxiom_68_1,axiom,
    reachableState(constB68) ).

cnf(reachableStateAxiom_69_1,axiom,
    reachableState(constB69) ).

cnf(reachableStateAxiom_70_1,axiom,
    reachableState(constB70) ).

cnf(reachableStateAxiom_71_1,axiom,
    reachableState(constB71) ).

cnf(reachableStateAxiom_72_1,axiom,
    reachableState(constB72) ).

cnf(reachableStateAxiom_73_1,axiom,
    reachableState(constB73) ).

cnf(reachableStateAxiom_74_1,axiom,
    reachableState(constB74) ).

cnf(reachableStateAxiom_75_1,axiom,
    reachableState(constB75) ).

cnf(reachableStateAxiom_76_1,axiom,
    reachableState(constB76) ).

cnf(reachableStateAxiom_77_1,axiom,
    reachableState(constB77) ).

cnf(reachableStateAxiom_78_1,axiom,
    reachableState(constB78) ).

cnf(reachableStateAxiom_79_1,axiom,
    reachableState(constB79) ).

cnf(reachableStateAxiom_80_1,axiom,
    reachableState(constB80) ).

cnf(reachableStateAxiom_81_1,axiom,
    reachableState(constB81) ).

cnf(reachableStateAxiom_82_1,axiom,
    reachableState(constB82) ).

cnf(reachableStateAxiom_83_1,axiom,
    reachableState(constB83) ).

cnf(reachableStateAxiom_84_1,axiom,
    reachableState(constB84) ).

cnf(reachableStateAxiom_85_1,axiom,
    reachableState(constB85) ).

cnf(reachableStateAxiom_86_1,axiom,
    reachableState(constB86) ).

cnf(reachableStateAxiom_87_1,axiom,
    reachableState(constB87) ).

cnf(reachableStateAxiom_88_1,axiom,
    reachableState(constB88) ).

cnf(reachableStateAxiom_89_1,axiom,
    reachableState(constB89) ).

cnf(reachableStateAxiom_90_1,axiom,
    reachableState(constB90) ).

cnf(reachableStateAxiom_91_1,axiom,
    reachableState(constB91) ).

cnf(reachableStateAxiom_92_1,axiom,
    reachableState(constB92) ).

cnf(reachableStateAxiom_93_1,axiom,
    reachableState(constB93) ).

cnf(reachableStateAxiom_94_1,axiom,
    reachableState(constB94) ).

cnf(reachableStateAxiom_95_1,axiom,
    reachableState(constB95) ).

cnf(reachableStateAxiom_96_1,axiom,
    reachableState(constB96) ).

cnf(reachableStateAxiom_97_1,axiom,
    reachableState(constB97) ).

cnf(reachableStateAxiom_98_1,axiom,
    reachableState(constB98) ).

cnf(reachableStateAxiom_99_1,axiom,
    reachableState(constB99) ).

cnf(reachableStateAxiom_100_1,axiom,
    reachableState(constB100) ).

cnf(reachableStateAxiom_101_1,axiom,
    reachableState(constB101) ).

cnf(reachableStateAxiom_102_1,axiom,
    reachableState(constB102) ).

cnf(reachableStateAxiom_103_1,axiom,
    reachableState(constB103) ).

cnf(reachableStateAxiom_104_1,axiom,
    reachableState(constB104) ).

cnf(reachableStateAxiom_105_1,axiom,
    reachableState(constB105) ).

cnf(reachableStateAxiom_106_1,axiom,
    reachableState(constB106) ).

cnf(reachableStateAxiom_107_1,axiom,
    reachableState(constB107) ).

cnf(reachableStateAxiom_108_1,axiom,
    reachableState(constB108) ).

cnf(reachableStateAxiom_109_1,axiom,
    reachableState(constB109) ).

cnf(reachableStateAxiom_110_1,axiom,
    reachableState(constB110) ).

cnf(reachableStateAxiom_111_1,axiom,
    reachableState(constB111) ).

cnf(reachableStateAxiom_112_1,axiom,
    reachableState(constB112) ).

cnf(reachableStateAxiom_113_1,axiom,
    reachableState(constB113) ).

cnf(reachableStateAxiom_114_1,axiom,
    reachableState(constB114) ).

cnf(reachableStateAxiom_115_1,axiom,
    reachableState(constB115) ).

cnf(reachableStateAxiom_116_1,axiom,
    reachableState(constB116) ).

cnf(reachableStateAxiom_117_1,axiom,
    reachableState(constB117) ).

cnf(reachableStateAxiom_118_1,axiom,
    reachableState(constB118) ).

cnf(reachableStateAxiom_119_1,axiom,
    reachableState(constB119) ).

cnf(reachableStateAxiom_120_1,axiom,
    reachableState(constB120) ).

cnf(reachableStateAxiom_121_1,axiom,
    reachableState(constB121) ).

cnf(reachableStateAxiom_122_1,axiom,
    reachableState(constB122) ).

cnf(reachableStateAxiom_123_1,axiom,
    reachableState(constB123) ).

cnf(reachableStateAxiom_124_1,axiom,
    reachableState(constB124) ).

cnf(reachableStateAxiom_125_1,axiom,
    reachableState(constB125) ).

cnf(reachableStateAxiom_126_1,axiom,
    reachableState(constB126) ).

cnf(reachableStateAxiom_127_1,axiom,
    reachableState(constB127) ).

cnf(reachableStateAxiom_128_1,axiom,
    reachableState(constB128) ).

cnf(reachableStateAxiom_129_1,axiom,
    reachableState(constB129) ).

cnf(reachableStateAxiom_130_1,axiom,
    reachableState(constB130) ).

cnf(reachableStateAxiom_131_1,axiom,
    reachableState(constB131) ).

cnf(reachableStateAxiom_132_1,axiom,
    reachableState(constB132) ).

cnf(reachableStateAxiom_133_1,axiom,
    reachableState(constB133) ).

cnf(reachableStateAxiom_134_1,axiom,
    reachableState(constB134) ).

cnf(reachableStateAxiom_135_1,axiom,
    reachableState(constB135) ).

cnf(reachableStateAxiom_136_1,axiom,
    reachableState(constB136) ).

cnf(reachableStateAxiom_137_1,axiom,
    reachableState(constB137) ).

cnf(reachableStateAxiom_138_1,axiom,
    reachableState(constB138) ).

cnf(reachableStateAxiom_139_1,axiom,
    reachableState(constB139) ).

cnf(reachableStateAxiom_140_1,axiom,
    reachableState(constB140) ).

cnf(reachableStateAxiom_141_1,axiom,
    reachableState(constB141) ).

cnf(reachableStateAxiom_142_1,axiom,
    reachableState(constB142) ).

cnf(reachableStateAxiom_143_1,axiom,
    reachableState(constB143) ).

cnf(reachableStateAxiom_144_1,axiom,
    reachableState(constB144) ).

cnf(reachableStateAxiom_145_1,axiom,
    reachableState(constB145) ).

cnf(reachableStateAxiom_146_1,axiom,
    reachableState(constB146) ).

cnf(reachableStateAxiom_147_1,axiom,
    reachableState(constB147) ).

cnf(reachableStateAxiom_148_1,axiom,
    reachableState(constB148) ).

cnf(reachableStateAxiom_149_1,axiom,
    reachableState(constB149) ).

cnf(reachableStateAxiom_150_1,axiom,
    reachableState(constB150) ).

cnf(reachableStateAxiom_151_1,axiom,
    reachableState(constB151) ).

cnf(reachableStateAxiom_152_1,axiom,
    reachableState(constB152) ).

cnf(reachableStateAxiom_153_1,axiom,
    reachableState(constB153) ).

cnf(reachableStateAxiom_154_1,axiom,
    reachableState(constB154) ).

cnf(reachableStateAxiom_155_1,axiom,
    reachableState(constB155) ).

cnf(reachableStateAxiom_156_1,axiom,
    reachableState(constB156) ).

cnf(reachableStateAxiom_157_1,axiom,
    reachableState(constB157) ).

cnf(reachableStateAxiom_158_1,axiom,
    reachableState(constB158) ).

cnf(reachableStateAxiom_159_1,axiom,
    reachableState(constB159) ).

cnf(reachableStateAxiom_160_1,axiom,
    reachableState(constB160) ).

cnf(reachableStateAxiom_161_1,axiom,
    reachableState(constB161) ).

cnf(reachableStateAxiom_162_1,axiom,
    reachableState(constB162) ).

cnf(reachableStateAxiom_163_1,axiom,
    reachableState(constB163) ).

cnf(reachableStateAxiom_164_1,axiom,
    reachableState(constB164) ).

cnf(reachableStateAxiom_165_1,axiom,
    reachableState(constB165) ).

cnf(reachableStateAxiom_166_1,axiom,
    reachableState(constB166) ).

cnf(reachableStateAxiom_167_1,axiom,
    reachableState(constB167) ).

cnf(reachableStateAxiom_168_1,axiom,
    reachableState(constB168) ).

cnf(reachableStateAxiom_169_1,axiom,
    reachableState(constB169) ).

cnf(reachableStateAxiom_170_1,axiom,
    reachableState(constB170) ).

cnf(reachableStateAxiom_171_1,axiom,
    reachableState(constB171) ).

cnf(reachableStateAxiom_172_1,axiom,
    reachableState(constB172) ).

cnf(reachableStateAxiom_173_1,axiom,
    reachableState(constB173) ).

cnf(reachableStateAxiom_174_1,axiom,
    reachableState(constB174) ).

cnf(reachableStateAxiom_175_1,axiom,
    reachableState(constB175) ).

cnf(reachableStateAxiom_176_1,axiom,
    reachableState(constB176) ).

cnf(reachableStateAxiom_177_1,axiom,
    reachableState(constB177) ).

cnf(reachableStateAxiom_178_1,axiom,
    reachableState(constB178) ).

cnf(reachableStateAxiom_179_1,axiom,
    reachableState(constB179) ).

cnf(reachableStateAxiom_180_1,axiom,
    reachableState(constB180) ).

cnf(reachableStateAxiom_181_1,axiom,
    reachableState(constB181) ).

cnf(reachableStateAxiom_182_1,axiom,
    reachableState(constB182) ).

cnf(reachableStateAxiom_183_1,axiom,
    reachableState(constB183) ).

cnf(reachableStateAxiom_184_1,axiom,
    reachableState(constB184) ).

cnf(reachableStateAxiom_185_1,axiom,
    reachableState(constB185) ).

cnf(reachableStateAxiom_186_1,axiom,
    reachableState(constB186) ).

cnf(reachableStateAxiom_187_1,axiom,
    reachableState(constB187) ).

cnf(reachableStateAxiom_188_1,axiom,
    reachableState(constB188) ).

cnf(reachableStateAxiom_189_1,axiom,
    reachableState(constB189) ).

cnf(reachableStateAxiom_190_1,axiom,
    reachableState(constB190) ).

cnf(reachableStateAxiom_191_1,axiom,
    reachableState(constB191) ).

cnf(reachableStateAxiom_192_1,axiom,
    reachableState(constB192) ).

cnf(reachableStateAxiom_193_1,axiom,
    reachableState(constB193) ).

cnf(reachableStateAxiom_194_1,axiom,
    reachableState(constB194) ).

cnf(reachableStateAxiom_195_1,axiom,
    reachableState(constB195) ).

cnf(reachableStateAxiom_196_1,axiom,
    reachableState(constB196) ).

cnf(reachableStateAxiom_197_1,axiom,
    reachableState(constB197) ).

cnf(reachableStateAxiom_198_1,axiom,
    reachableState(constB198) ).

cnf(reachableStateAxiom_199_1,axiom,
    reachableState(constB199) ).

cnf(reachableStateAxiom_200_1,axiom,
    reachableState(constB200) ).

cnf(reachableStateAxiom_201_1_1,axiom,
    ( constB200 = VarState
    | constB199 = VarState
    | constB198 = VarState
    | constB197 = VarState
    | constB196 = VarState
    | constB195 = VarState
    | constB194 = VarState
    | constB193 = VarState
    | constB192 = VarState
    | constB191 = VarState
    | constB190 = VarState
    | constB189 = VarState
    | constB188 = VarState
    | constB187 = VarState
    | constB186 = VarState
    | constB185 = VarState
    | constB184 = VarState
    | constB183 = VarState
    | constB182 = VarState
    | constB181 = VarState
    | constB180 = VarState
    | constB179 = VarState
    | constB178 = VarState
    | constB177 = VarState
    | constB176 = VarState
    | constB175 = VarState
    | constB174 = VarState
    | constB173 = VarState
    | constB172 = VarState
    | constB171 = VarState
    | constB170 = VarState
    | constB169 = VarState
    | constB168 = VarState
    | constB167 = VarState
    | constB166 = VarState
    | constB165 = VarState
    | constB164 = VarState
    | constB163 = VarState
    | constB162 = VarState
    | constB161 = VarState
    | constB160 = VarState
    | constB159 = VarState
    | constB158 = VarState
    | constB157 = VarState
    | constB156 = VarState
    | constB155 = VarState
    | constB154 = VarState
    | constB153 = VarState
    | constB152 = VarState
    | constB151 = VarState
    | constB150 = VarState
    | constB149 = VarState
    | constB148 = VarState
    | constB147 = VarState
    | constB146 = VarState
    | constB145 = VarState
    | constB144 = VarState
    | constB143 = VarState
    | constB142 = VarState
    | constB141 = VarState
    | constB140 = VarState
    | constB139 = VarState
    | constB138 = VarState
    | constB137 = VarState
    | constB136 = VarState
    | constB135 = VarState
    | constB134 = VarState
    | constB133 = VarState
    | constB132 = VarState
    | constB131 = VarState
    | constB130 = VarState
    | constB129 = VarState
    | constB128 = VarState
    | constB127 = VarState
    | constB126 = VarState
    | constB125 = VarState
    | constB124 = VarState
    | constB123 = VarState
    | constB122 = VarState
    | constB121 = VarState
    | constB120 = VarState
    | constB119 = VarState
    | constB118 = VarState
    | constB117 = VarState
    | constB116 = VarState
    | constB115 = VarState
    | constB114 = VarState
    | constB113 = VarState
    | constB112 = VarState
    | constB111 = VarState
    | constB110 = VarState
    | constB109 = VarState
    | constB108 = VarState
    | constB107 = VarState
    | constB106 = VarState
    | constB105 = VarState
    | constB104 = VarState
    | constB103 = VarState
    | constB102 = VarState
    | constB101 = VarState
    | constB100 = VarState
    | constB99 = VarState
    | constB98 = VarState
    | constB97 = VarState
    | constB96 = VarState
    | constB95 = VarState
    | constB94 = VarState
    | constB93 = VarState
    | constB92 = VarState
    | constB91 = VarState
    | constB90 = VarState
    | constB89 = VarState
    | constB88 = VarState
    | constB87 = VarState
    | constB86 = VarState
    | constB85 = VarState
    | constB84 = VarState
    | constB83 = VarState
    | constB82 = VarState
    | constB81 = VarState
    | constB80 = VarState
    | constB79 = VarState
    | constB78 = VarState
    | constB77 = VarState
    | constB76 = VarState
    | constB75 = VarState
    | constB74 = VarState
    | constB73 = VarState
    | constB72 = VarState
    | constB71 = VarState
    | constB70 = VarState
    | constB69 = VarState
    | constB68 = VarState
    | constB67 = VarState
    | constB66 = VarState
    | constB65 = VarState
    | constB64 = VarState
    | constB63 = VarState
    | constB62 = VarState
    | constB61 = VarState
    | constB60 = VarState
    | constB59 = VarState
    | constB58 = VarState
    | constB57 = VarState
    | constB56 = VarState
    | constB55 = VarState
    | constB54 = VarState
    | constB53 = VarState
    | constB52 = VarState
    | constB51 = VarState
    | constB50 = VarState
    | constB49 = VarState
    | constB48 = VarState
    | constB47 = VarState
    | constB46 = VarState
    | constB45 = VarState
    | constB44 = VarState
    | constB43 = VarState
    | constB42 = VarState
    | constB41 = VarState
    | constB40 = VarState
    | constB39 = VarState
    | constB38 = VarState
    | constB37 = VarState
    | constB36 = VarState
    | constB35 = VarState
    | constB34 = VarState
    | constB33 = VarState
    | constB32 = VarState
    | constB31 = VarState
    | constB30 = VarState
    | constB29 = VarState
    | constB28 = VarState
    | constB27 = VarState
    | constB26 = VarState
    | constB25 = VarState
    | constB24 = VarState
    | constB23 = VarState
    | constB22 = VarState
    | constB21 = VarState
    | constB20 = VarState
    | constB19 = VarState
    | constB18 = VarState
    | constB17 = VarState
    | constB16 = VarState
    | constB15 = VarState
    | constB14 = VarState
    | constB13 = VarState
    | constB12 = VarState
    | constB11 = VarState
    | constB10 = VarState
    | constB9 = VarState
    | constB8 = VarState
    | constB7 = VarState
    | constB6 = VarState
    | constB5 = VarState
    | constB4 = VarState
    | constB3 = VarState
    | constB2 = VarState
    | constB1 = VarState
    | constB0 = VarState
    | ~ reachableState(VarState) ) ).

cnf(reachableStateAxiom_202_1_2,axiom,
    ( reachableState(VarCurr)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(reachableStateAxiom_202_1_1,axiom,
    ( reachableState(VarNext)
    | ~ nextState(VarCurr,VarNext) ) ).

cnf(pathAxiom_200,axiom,
    nextState(constB0,constB1) ).

cnf(pathAxiom_1_1,axiom,
    nextState(constB1,constB2) ).

cnf(pathAxiom_2_1,axiom,
    nextState(constB2,constB3) ).

cnf(pathAxiom_3_1,axiom,
    nextState(constB3,constB4) ).

cnf(pathAxiom_4_1,axiom,
    nextState(constB4,constB5) ).

cnf(pathAxiom_5_1,axiom,
    nextState(constB5,constB6) ).

cnf(pathAxiom_6_1,axiom,
    nextState(constB6,constB7) ).

cnf(pathAxiom_7_1,axiom,
    nextState(constB7,constB8) ).

cnf(pathAxiom_8_1,axiom,
    nextState(constB8,constB9) ).

cnf(pathAxiom_9_1,axiom,
    nextState(constB9,constB10) ).

cnf(pathAxiom_10_1,axiom,
    nextState(constB10,constB11) ).

cnf(pathAxiom_11_1,axiom,
    nextState(constB11,constB12) ).

cnf(pathAxiom_12_1,axiom,
    nextState(constB12,constB13) ).

cnf(pathAxiom_13_1,axiom,
    nextState(constB13,constB14) ).

cnf(pathAxiom_14_1,axiom,
    nextState(constB14,constB15) ).

cnf(pathAxiom_15_1,axiom,
    nextState(constB15,constB16) ).

cnf(pathAxiom_16_1,axiom,
    nextState(constB16,constB17) ).

cnf(pathAxiom_17_1,axiom,
    nextState(constB17,constB18) ).

cnf(pathAxiom_18_1,axiom,
    nextState(constB18,constB19) ).

cnf(pathAxiom_19_1,axiom,
    nextState(constB19,constB20) ).

cnf(pathAxiom_20_1,axiom,
    nextState(constB20,constB21) ).

cnf(pathAxiom_21_1,axiom,
    nextState(constB21,constB22) ).

cnf(pathAxiom_22_1,axiom,
    nextState(constB22,constB23) ).

cnf(pathAxiom_23_1,axiom,
    nextState(constB23,constB24) ).

cnf(pathAxiom_24_1,axiom,
    nextState(constB24,constB25) ).

cnf(pathAxiom_25_1,axiom,
    nextState(constB25,constB26) ).

cnf(pathAxiom_26_1,axiom,
    nextState(constB26,constB27) ).

cnf(pathAxiom_27_1,axiom,
    nextState(constB27,constB28) ).

cnf(pathAxiom_28_1,axiom,
    nextState(constB28,constB29) ).

cnf(pathAxiom_29_1,axiom,
    nextState(constB29,constB30) ).

cnf(pathAxiom_30_1,axiom,
    nextState(constB30,constB31) ).

cnf(pathAxiom_31_1,axiom,
    nextState(constB31,constB32) ).

cnf(pathAxiom_32_1,axiom,
    nextState(constB32,constB33) ).

cnf(pathAxiom_33_1,axiom,
    nextState(constB33,constB34) ).

cnf(pathAxiom_34_1,axiom,
    nextState(constB34,constB35) ).

cnf(pathAxiom_35_1,axiom,
    nextState(constB35,constB36) ).

cnf(pathAxiom_36_1,axiom,
    nextState(constB36,constB37) ).

cnf(pathAxiom_37_1,axiom,
    nextState(constB37,constB38) ).

cnf(pathAxiom_38_1,axiom,
    nextState(constB38,constB39) ).

cnf(pathAxiom_39_1,axiom,
    nextState(constB39,constB40) ).

cnf(pathAxiom_40_1,axiom,
    nextState(constB40,constB41) ).

cnf(pathAxiom_41_1,axiom,
    nextState(constB41,constB42) ).

cnf(pathAxiom_42_1,axiom,
    nextState(constB42,constB43) ).

cnf(pathAxiom_43_1,axiom,
    nextState(constB43,constB44) ).

cnf(pathAxiom_44_1,axiom,
    nextState(constB44,constB45) ).

cnf(pathAxiom_45_1,axiom,
    nextState(constB45,constB46) ).

cnf(pathAxiom_46_1,axiom,
    nextState(constB46,constB47) ).

cnf(pathAxiom_47_1,axiom,
    nextState(constB47,constB48) ).

cnf(pathAxiom_48_1,axiom,
    nextState(constB48,constB49) ).

cnf(pathAxiom_49_1,axiom,
    nextState(constB49,constB50) ).

cnf(pathAxiom_50_1,axiom,
    nextState(constB50,constB51) ).

cnf(pathAxiom_51_1,axiom,
    nextState(constB51,constB52) ).

cnf(pathAxiom_52_1,axiom,
    nextState(constB52,constB53) ).

cnf(pathAxiom_53_1,axiom,
    nextState(constB53,constB54) ).

cnf(pathAxiom_54_1,axiom,
    nextState(constB54,constB55) ).

cnf(pathAxiom_55_1,axiom,
    nextState(constB55,constB56) ).

cnf(pathAxiom_56_1,axiom,
    nextState(constB56,constB57) ).

cnf(pathAxiom_57_1,axiom,
    nextState(constB57,constB58) ).

cnf(pathAxiom_58_1,axiom,
    nextState(constB58,constB59) ).

cnf(pathAxiom_59_1,axiom,
    nextState(constB59,constB60) ).

cnf(pathAxiom_60_1,axiom,
    nextState(constB60,constB61) ).

cnf(pathAxiom_61_1,axiom,
    nextState(constB61,constB62) ).

cnf(pathAxiom_62_1,axiom,
    nextState(constB62,constB63) ).

cnf(pathAxiom_63_1,axiom,
    nextState(constB63,constB64) ).

cnf(pathAxiom_64_1,axiom,
    nextState(constB64,constB65) ).

cnf(pathAxiom_65_1,axiom,
    nextState(constB65,constB66) ).

cnf(pathAxiom_66_1,axiom,
    nextState(constB66,constB67) ).

cnf(pathAxiom_67_1,axiom,
    nextState(constB67,constB68) ).

cnf(pathAxiom_68_1,axiom,
    nextState(constB68,constB69) ).

cnf(pathAxiom_69_1,axiom,
    nextState(constB69,constB70) ).

cnf(pathAxiom_70_1,axiom,
    nextState(constB70,constB71) ).

cnf(pathAxiom_71_1,axiom,
    nextState(constB71,constB72) ).

cnf(pathAxiom_72_1,axiom,
    nextState(constB72,constB73) ).

cnf(pathAxiom_73_1,axiom,
    nextState(constB73,constB74) ).

cnf(pathAxiom_74_1,axiom,
    nextState(constB74,constB75) ).

cnf(pathAxiom_75_1,axiom,
    nextState(constB75,constB76) ).

cnf(pathAxiom_76_1,axiom,
    nextState(constB76,constB77) ).

cnf(pathAxiom_77_1,axiom,
    nextState(constB77,constB78) ).

cnf(pathAxiom_78_1,axiom,
    nextState(constB78,constB79) ).

cnf(pathAxiom_79_1,axiom,
    nextState(constB79,constB80) ).

cnf(pathAxiom_80_1,axiom,
    nextState(constB80,constB81) ).

cnf(pathAxiom_81_1,axiom,
    nextState(constB81,constB82) ).

cnf(pathAxiom_82_1,axiom,
    nextState(constB82,constB83) ).

cnf(pathAxiom_83_1,axiom,
    nextState(constB83,constB84) ).

cnf(pathAxiom_84_1,axiom,
    nextState(constB84,constB85) ).

cnf(pathAxiom_85_1,axiom,
    nextState(constB85,constB86) ).

cnf(pathAxiom_86_1,axiom,
    nextState(constB86,constB87) ).

cnf(pathAxiom_87_1,axiom,
    nextState(constB87,constB88) ).

cnf(pathAxiom_88_1,axiom,
    nextState(constB88,constB89) ).

cnf(pathAxiom_89_1,axiom,
    nextState(constB89,constB90) ).

cnf(pathAxiom_90_1,axiom,
    nextState(constB90,constB91) ).

cnf(pathAxiom_91_1,axiom,
    nextState(constB91,constB92) ).

cnf(pathAxiom_92_1,axiom,
    nextState(constB92,constB93) ).

cnf(pathAxiom_93_1,axiom,
    nextState(constB93,constB94) ).

cnf(pathAxiom_94_1,axiom,
    nextState(constB94,constB95) ).

cnf(pathAxiom_95_1,axiom,
    nextState(constB95,constB96) ).

cnf(pathAxiom_96_1,axiom,
    nextState(constB96,constB97) ).

cnf(pathAxiom_97_1,axiom,
    nextState(constB97,constB98) ).

cnf(pathAxiom_98_1,axiom,
    nextState(constB98,constB99) ).

cnf(pathAxiom_99_1,axiom,
    nextState(constB99,constB100) ).

cnf(pathAxiom_100_1,axiom,
    nextState(constB100,constB101) ).

cnf(pathAxiom_101_1,axiom,
    nextState(constB101,constB102) ).

cnf(pathAxiom_102_1,axiom,
    nextState(constB102,constB103) ).

cnf(pathAxiom_103_1,axiom,
    nextState(constB103,constB104) ).

cnf(pathAxiom_104_1,axiom,
    nextState(constB104,constB105) ).

cnf(pathAxiom_105_1,axiom,
    nextState(constB105,constB106) ).

cnf(pathAxiom_106_1,axiom,
    nextState(constB106,constB107) ).

cnf(pathAxiom_107_1,axiom,
    nextState(constB107,constB108) ).

cnf(pathAxiom_108_1,axiom,
    nextState(constB108,constB109) ).

cnf(pathAxiom_109_1,axiom,
    nextState(constB109,constB110) ).

cnf(pathAxiom_110_1,axiom,
    nextState(constB110,constB111) ).

cnf(pathAxiom_111_1,axiom,
    nextState(constB111,constB112) ).

cnf(pathAxiom_112_1,axiom,
    nextState(constB112,constB113) ).

cnf(pathAxiom_113_1,axiom,
    nextState(constB113,constB114) ).

cnf(pathAxiom_114_1,axiom,
    nextState(constB114,constB115) ).

cnf(pathAxiom_115_1,axiom,
    nextState(constB115,constB116) ).

cnf(pathAxiom_116_1,axiom,
    nextState(constB116,constB117) ).

cnf(pathAxiom_117_1,axiom,
    nextState(constB117,constB118) ).

cnf(pathAxiom_118_1,axiom,
    nextState(constB118,constB119) ).

cnf(pathAxiom_119_1,axiom,
    nextState(constB119,constB120) ).

cnf(pathAxiom_120_1,axiom,
    nextState(constB120,constB121) ).

cnf(pathAxiom_121_1,axiom,
    nextState(constB121,constB122) ).

cnf(pathAxiom_122_1,axiom,
    nextState(constB122,constB123) ).

cnf(pathAxiom_123_1,axiom,
    nextState(constB123,constB124) ).

cnf(pathAxiom_124_1,axiom,
    nextState(constB124,constB125) ).

cnf(pathAxiom_125_1,axiom,
    nextState(constB125,constB126) ).

cnf(pathAxiom_126_1,axiom,
    nextState(constB126,constB127) ).

cnf(pathAxiom_127_1,axiom,
    nextState(constB127,constB128) ).

cnf(pathAxiom_128_1,axiom,
    nextState(constB128,constB129) ).

cnf(pathAxiom_129_1,axiom,
    nextState(constB129,constB130) ).

cnf(pathAxiom_130_1,axiom,
    nextState(constB130,constB131) ).

cnf(pathAxiom_131_1,axiom,
    nextState(constB131,constB132) ).

cnf(pathAxiom_132_1,axiom,
    nextState(constB132,constB133) ).

cnf(pathAxiom_133_1,axiom,
    nextState(constB133,constB134) ).

cnf(pathAxiom_134_1,axiom,
    nextState(constB134,constB135) ).

cnf(pathAxiom_135_1,axiom,
    nextState(constB135,constB136) ).

cnf(pathAxiom_136_1,axiom,
    nextState(constB136,constB137) ).

cnf(pathAxiom_137_1,axiom,
    nextState(constB137,constB138) ).

cnf(pathAxiom_138_1,axiom,
    nextState(constB138,constB139) ).

cnf(pathAxiom_139_1,axiom,
    nextState(constB139,constB140) ).

cnf(pathAxiom_140_1,axiom,
    nextState(constB140,constB141) ).

cnf(pathAxiom_141_1,axiom,
    nextState(constB141,constB142) ).

cnf(pathAxiom_142_1,axiom,
    nextState(constB142,constB143) ).

cnf(pathAxiom_143_1,axiom,
    nextState(constB143,constB144) ).

cnf(pathAxiom_144_1,axiom,
    nextState(constB144,constB145) ).

cnf(pathAxiom_145_1,axiom,
    nextState(constB145,constB146) ).

cnf(pathAxiom_146_1,axiom,
    nextState(constB146,constB147) ).

cnf(pathAxiom_147_1,axiom,
    nextState(constB147,constB148) ).

cnf(pathAxiom_148_1,axiom,
    nextState(constB148,constB149) ).

cnf(pathAxiom_149_1,axiom,
    nextState(constB149,constB150) ).

cnf(pathAxiom_150_1,axiom,
    nextState(constB150,constB151) ).

cnf(pathAxiom_151_1,axiom,
    nextState(constB151,constB152) ).

cnf(pathAxiom_152_1,axiom,
    nextState(constB152,constB153) ).

cnf(pathAxiom_153_1,axiom,
    nextState(constB153,constB154) ).

cnf(pathAxiom_154_1,axiom,
    nextState(constB154,constB155) ).

cnf(pathAxiom_155_1,axiom,
    nextState(constB155,constB156) ).

cnf(pathAxiom_156_1,axiom,
    nextState(constB156,constB157) ).

cnf(pathAxiom_157_1,axiom,
    nextState(constB157,constB158) ).

cnf(pathAxiom_158_1,axiom,
    nextState(constB158,constB159) ).

cnf(pathAxiom_159_1,axiom,
    nextState(constB159,constB160) ).

cnf(pathAxiom_160_1,axiom,
    nextState(constB160,constB161) ).

cnf(pathAxiom_161_1,axiom,
    nextState(constB161,constB162) ).

cnf(pathAxiom_162_1,axiom,
    nextState(constB162,constB163) ).

cnf(pathAxiom_163_1,axiom,
    nextState(constB163,constB164) ).

cnf(pathAxiom_164_1,axiom,
    nextState(constB164,constB165) ).

cnf(pathAxiom_165_1,axiom,
    nextState(constB165,constB166) ).

cnf(pathAxiom_166_1,axiom,
    nextState(constB166,constB167) ).

cnf(pathAxiom_167_1,axiom,
    nextState(constB167,constB168) ).

cnf(pathAxiom_168_1,axiom,
    nextState(constB168,constB169) ).

cnf(pathAxiom_169_1,axiom,
    nextState(constB169,constB170) ).

cnf(pathAxiom_170_1,axiom,
    nextState(constB170,constB171) ).

cnf(pathAxiom_171_1,axiom,
    nextState(constB171,constB172) ).

cnf(pathAxiom_172_1,axiom,
    nextState(constB172,constB173) ).

cnf(pathAxiom_173_1,axiom,
    nextState(constB173,constB174) ).

cnf(pathAxiom_174_1,axiom,
    nextState(constB174,constB175) ).

cnf(pathAxiom_175_1,axiom,
    nextState(constB175,constB176) ).

cnf(pathAxiom_176_1,axiom,
    nextState(constB176,constB177) ).

cnf(pathAxiom_177_1,axiom,
    nextState(constB177,constB178) ).

cnf(pathAxiom_178_1,axiom,
    nextState(constB178,constB179) ).

cnf(pathAxiom_179_1,axiom,
    nextState(constB179,constB180) ).

cnf(pathAxiom_180_1,axiom,
    nextState(constB180,constB181) ).

cnf(pathAxiom_181_1,axiom,
    nextState(constB181,constB182) ).

cnf(pathAxiom_182_1,axiom,
    nextState(constB182,constB183) ).

cnf(pathAxiom_183_1,axiom,
    nextState(constB183,constB184) ).

cnf(pathAxiom_184_1,axiom,
    nextState(constB184,constB185) ).

cnf(pathAxiom_185_1,axiom,
    nextState(constB185,constB186) ).

cnf(pathAxiom_186_1,axiom,
    nextState(constB186,constB187) ).

cnf(pathAxiom_187_1,axiom,
    nextState(constB187,constB188) ).

cnf(pathAxiom_188_1,axiom,
    nextState(constB188,constB189) ).

cnf(pathAxiom_189_1,axiom,
    nextState(constB189,constB190) ).

cnf(pathAxiom_190_1,axiom,
    nextState(constB190,constB191) ).

cnf(pathAxiom_191_1,axiom,
    nextState(constB191,constB192) ).

cnf(pathAxiom_192_1,axiom,
    nextState(constB192,constB193) ).

cnf(pathAxiom_193_1,axiom,
    nextState(constB193,constB194) ).

cnf(pathAxiom_194_1,axiom,
    nextState(constB194,constB195) ).

cnf(pathAxiom_195_1,axiom,
    nextState(constB195,constB196) ).

cnf(pathAxiom_196_1,axiom,
    nextState(constB196,constB197) ).

cnf(pathAxiom_197_1,axiom,
    nextState(constB197,constB198) ).

cnf(pathAxiom_198_1,axiom,
    nextState(constB198,constB199) ).

cnf(pathAxiom_199_1,axiom,
    nextState(constB199,constB200) ).

cnf(clock_pattern_201,axiom,
    v1(constB0) ).

cnf(clock_pattern_1_1_1,axiom,
    ~ v1(constB1) ).

cnf(clock_pattern_2_1,axiom,
    v1(constB2) ).

cnf(clock_pattern_3_1_1,axiom,
    ~ v1(constB3) ).

cnf(clock_pattern_4_1,axiom,
    v1(constB4) ).

cnf(clock_pattern_5_1_1,axiom,
    ~ v1(constB5) ).

cnf(clock_pattern_6_1,axiom,
    v1(constB6) ).

cnf(clock_pattern_7_1_1,axiom,
    ~ v1(constB7) ).

cnf(clock_pattern_8_1,axiom,
    v1(constB8) ).

cnf(clock_pattern_9_1_1,axiom,
    ~ v1(constB9) ).

cnf(clock_pattern_10_1,axiom,
    v1(constB10) ).

cnf(clock_pattern_11_1_1,axiom,
    ~ v1(constB11) ).

cnf(clock_pattern_12_1,axiom,
    v1(constB12) ).

cnf(clock_pattern_13_1_1,axiom,
    ~ v1(constB13) ).

cnf(clock_pattern_14_1,axiom,
    v1(constB14) ).

cnf(clock_pattern_15_1_1,axiom,
    ~ v1(constB15) ).

cnf(clock_pattern_16_1,axiom,
    v1(constB16) ).

cnf(clock_pattern_17_1_1,axiom,
    ~ v1(constB17) ).

cnf(clock_pattern_18_1,axiom,
    v1(constB18) ).

cnf(clock_pattern_19_1_1,axiom,
    ~ v1(constB19) ).

cnf(clock_pattern_20_1,axiom,
    v1(constB20) ).

cnf(clock_pattern_21_1_1,axiom,
    ~ v1(constB21) ).

cnf(clock_pattern_22_1,axiom,
    v1(constB22) ).

cnf(clock_pattern_23_1_1,axiom,
    ~ v1(constB23) ).

cnf(clock_pattern_24_1,axiom,
    v1(constB24) ).

cnf(clock_pattern_25_1_1,axiom,
    ~ v1(constB25) ).

cnf(clock_pattern_26_1,axiom,
    v1(constB26) ).

cnf(clock_pattern_27_1_1,axiom,
    ~ v1(constB27) ).

cnf(clock_pattern_28_1,axiom,
    v1(constB28) ).

cnf(clock_pattern_29_1_1,axiom,
    ~ v1(constB29) ).

cnf(clock_pattern_30_1,axiom,
    v1(constB30) ).

cnf(clock_pattern_31_1_1,axiom,
    ~ v1(constB31) ).

cnf(clock_pattern_32_1,axiom,
    v1(constB32) ).

cnf(clock_pattern_33_1_1,axiom,
    ~ v1(constB33) ).

cnf(clock_pattern_34_1,axiom,
    v1(constB34) ).

cnf(clock_pattern_35_1_1,axiom,
    ~ v1(constB35) ).

cnf(clock_pattern_36_1,axiom,
    v1(constB36) ).

cnf(clock_pattern_37_1_1,axiom,
    ~ v1(constB37) ).

cnf(clock_pattern_38_1,axiom,
    v1(constB38) ).

cnf(clock_pattern_39_1_1,axiom,
    ~ v1(constB39) ).

cnf(clock_pattern_40_1,axiom,
    v1(constB40) ).

cnf(clock_pattern_41_1_1,axiom,
    ~ v1(constB41) ).

cnf(clock_pattern_42_1,axiom,
    v1(constB42) ).

cnf(clock_pattern_43_1_1,axiom,
    ~ v1(constB43) ).

cnf(clock_pattern_44_1,axiom,
    v1(constB44) ).

cnf(clock_pattern_45_1_1,axiom,
    ~ v1(constB45) ).

cnf(clock_pattern_46_1,axiom,
    v1(constB46) ).

cnf(clock_pattern_47_1_1,axiom,
    ~ v1(constB47) ).

cnf(clock_pattern_48_1,axiom,
    v1(constB48) ).

cnf(clock_pattern_49_1_1,axiom,
    ~ v1(constB49) ).

cnf(clock_pattern_50_1,axiom,
    v1(constB50) ).

cnf(clock_pattern_51_1_1,axiom,
    ~ v1(constB51) ).

cnf(clock_pattern_52_1,axiom,
    v1(constB52) ).

cnf(clock_pattern_53_1_1,axiom,
    ~ v1(constB53) ).

cnf(clock_pattern_54_1,axiom,
    v1(constB54) ).

cnf(clock_pattern_55_1_1,axiom,
    ~ v1(constB55) ).

cnf(clock_pattern_56_1,axiom,
    v1(constB56) ).

cnf(clock_pattern_57_1_1,axiom,
    ~ v1(constB57) ).

cnf(clock_pattern_58_1,axiom,
    v1(constB58) ).

cnf(clock_pattern_59_1_1,axiom,
    ~ v1(constB59) ).

cnf(clock_pattern_60_1,axiom,
    v1(constB60) ).

cnf(clock_pattern_61_1_1,axiom,
    ~ v1(constB61) ).

cnf(clock_pattern_62_1,axiom,
    v1(constB62) ).

cnf(clock_pattern_63_1_1,axiom,
    ~ v1(constB63) ).

cnf(clock_pattern_64_1,axiom,
    v1(constB64) ).

cnf(clock_pattern_65_1_1,axiom,
    ~ v1(constB65) ).

cnf(clock_pattern_66_1,axiom,
    v1(constB66) ).

cnf(clock_pattern_67_1_1,axiom,
    ~ v1(constB67) ).

cnf(clock_pattern_68_1,axiom,
    v1(constB68) ).

cnf(clock_pattern_69_1_1,axiom,
    ~ v1(constB69) ).

cnf(clock_pattern_70_1,axiom,
    v1(constB70) ).

cnf(clock_pattern_71_1_1,axiom,
    ~ v1(constB71) ).

cnf(clock_pattern_72_1,axiom,
    v1(constB72) ).

cnf(clock_pattern_73_1_1,axiom,
    ~ v1(constB73) ).

cnf(clock_pattern_74_1,axiom,
    v1(constB74) ).

cnf(clock_pattern_75_1_1,axiom,
    ~ v1(constB75) ).

cnf(clock_pattern_76_1,axiom,
    v1(constB76) ).

cnf(clock_pattern_77_1_1,axiom,
    ~ v1(constB77) ).

cnf(clock_pattern_78_1,axiom,
    v1(constB78) ).

cnf(clock_pattern_79_1_1,axiom,
    ~ v1(constB79) ).

cnf(clock_pattern_80_1,axiom,
    v1(constB80) ).

cnf(clock_pattern_81_1_1,axiom,
    ~ v1(constB81) ).

cnf(clock_pattern_82_1,axiom,
    v1(constB82) ).

cnf(clock_pattern_83_1_1,axiom,
    ~ v1(constB83) ).

cnf(clock_pattern_84_1,axiom,
    v1(constB84) ).

cnf(clock_pattern_85_1_1,axiom,
    ~ v1(constB85) ).

cnf(clock_pattern_86_1,axiom,
    v1(constB86) ).

cnf(clock_pattern_87_1_1,axiom,
    ~ v1(constB87) ).

cnf(clock_pattern_88_1,axiom,
    v1(constB88) ).

cnf(clock_pattern_89_1_1,axiom,
    ~ v1(constB89) ).

cnf(clock_pattern_90_1,axiom,
    v1(constB90) ).

cnf(clock_pattern_91_1_1,axiom,
    ~ v1(constB91) ).

cnf(clock_pattern_92_1,axiom,
    v1(constB92) ).

cnf(clock_pattern_93_1_1,axiom,
    ~ v1(constB93) ).

cnf(clock_pattern_94_1,axiom,
    v1(constB94) ).

cnf(clock_pattern_95_1_1,axiom,
    ~ v1(constB95) ).

cnf(clock_pattern_96_1,axiom,
    v1(constB96) ).

cnf(clock_pattern_97_1_1,axiom,
    ~ v1(constB97) ).

cnf(clock_pattern_98_1,axiom,
    v1(constB98) ).

cnf(clock_pattern_99_1_1,axiom,
    ~ v1(constB99) ).

cnf(clock_pattern_100_1,axiom,
    v1(constB100) ).

cnf(clock_pattern_101_1_1,axiom,
    ~ v1(constB101) ).

cnf(clock_pattern_102_1,axiom,
    v1(constB102) ).

cnf(clock_pattern_103_1_1,axiom,
    ~ v1(constB103) ).

cnf(clock_pattern_104_1,axiom,
    v1(constB104) ).

cnf(clock_pattern_105_1_1,axiom,
    ~ v1(constB105) ).

cnf(clock_pattern_106_1,axiom,
    v1(constB106) ).

cnf(clock_pattern_107_1_1,axiom,
    ~ v1(constB107) ).

cnf(clock_pattern_108_1,axiom,
    v1(constB108) ).

cnf(clock_pattern_109_1_1,axiom,
    ~ v1(constB109) ).

cnf(clock_pattern_110_1,axiom,
    v1(constB110) ).

cnf(clock_pattern_111_1_1,axiom,
    ~ v1(constB111) ).

cnf(clock_pattern_112_1,axiom,
    v1(constB112) ).

cnf(clock_pattern_113_1_1,axiom,
    ~ v1(constB113) ).

cnf(clock_pattern_114_1,axiom,
    v1(constB114) ).

cnf(clock_pattern_115_1_1,axiom,
    ~ v1(constB115) ).

cnf(clock_pattern_116_1,axiom,
    v1(constB116) ).

cnf(clock_pattern_117_1_1,axiom,
    ~ v1(constB117) ).

cnf(clock_pattern_118_1,axiom,
    v1(constB118) ).

cnf(clock_pattern_119_1_1,axiom,
    ~ v1(constB119) ).

cnf(clock_pattern_120_1,axiom,
    v1(constB120) ).

cnf(clock_pattern_121_1_1,axiom,
    ~ v1(constB121) ).

cnf(clock_pattern_122_1,axiom,
    v1(constB122) ).

cnf(clock_pattern_123_1_1,axiom,
    ~ v1(constB123) ).

cnf(clock_pattern_124_1,axiom,
    v1(constB124) ).

cnf(clock_pattern_125_1_1,axiom,
    ~ v1(constB125) ).

cnf(clock_pattern_126_1,axiom,
    v1(constB126) ).

cnf(clock_pattern_127_1_1,axiom,
    ~ v1(constB127) ).

cnf(clock_pattern_128_1,axiom,
    v1(constB128) ).

cnf(clock_pattern_129_1_1,axiom,
    ~ v1(constB129) ).

cnf(clock_pattern_130_1,axiom,
    v1(constB130) ).

cnf(clock_pattern_131_1_1,axiom,
    ~ v1(constB131) ).

cnf(clock_pattern_132_1,axiom,
    v1(constB132) ).

cnf(clock_pattern_133_1_1,axiom,
    ~ v1(constB133) ).

cnf(clock_pattern_134_1,axiom,
    v1(constB134) ).

cnf(clock_pattern_135_1_1,axiom,
    ~ v1(constB135) ).

cnf(clock_pattern_136_1,axiom,
    v1(constB136) ).

cnf(clock_pattern_137_1_1,axiom,
    ~ v1(constB137) ).

cnf(clock_pattern_138_1,axiom,
    v1(constB138) ).

cnf(clock_pattern_139_1_1,axiom,
    ~ v1(constB139) ).

cnf(clock_pattern_140_1,axiom,
    v1(constB140) ).

cnf(clock_pattern_141_1_1,axiom,
    ~ v1(constB141) ).

cnf(clock_pattern_142_1,axiom,
    v1(constB142) ).

cnf(clock_pattern_143_1_1,axiom,
    ~ v1(constB143) ).

cnf(clock_pattern_144_1,axiom,
    v1(constB144) ).

cnf(clock_pattern_145_1_1,axiom,
    ~ v1(constB145) ).

cnf(clock_pattern_146_1,axiom,
    v1(constB146) ).

cnf(clock_pattern_147_1_1,axiom,
    ~ v1(constB147) ).

cnf(clock_pattern_148_1,axiom,
    v1(constB148) ).

cnf(clock_pattern_149_1_1,axiom,
    ~ v1(constB149) ).

cnf(clock_pattern_150_1,axiom,
    v1(constB150) ).

cnf(clock_pattern_151_1_1,axiom,
    ~ v1(constB151) ).

cnf(clock_pattern_152_1,axiom,
    v1(constB152) ).

cnf(clock_pattern_153_1_1,axiom,
    ~ v1(constB153) ).

cnf(clock_pattern_154_1,axiom,
    v1(constB154) ).

cnf(clock_pattern_155_1_1,axiom,
    ~ v1(constB155) ).

cnf(clock_pattern_156_1,axiom,
    v1(constB156) ).

cnf(clock_pattern_157_1_1,axiom,
    ~ v1(constB157) ).

cnf(clock_pattern_158_1,axiom,
    v1(constB158) ).

cnf(clock_pattern_159_1_1,axiom,
    ~ v1(constB159) ).

cnf(clock_pattern_160_1,axiom,
    v1(constB160) ).

cnf(clock_pattern_161_1_1,axiom,
    ~ v1(constB161) ).

cnf(clock_pattern_162_1,axiom,
    v1(constB162) ).

cnf(clock_pattern_163_1_1,axiom,
    ~ v1(constB163) ).

cnf(clock_pattern_164_1,axiom,
    v1(constB164) ).

cnf(clock_pattern_165_1_1,axiom,
    ~ v1(constB165) ).

cnf(clock_pattern_166_1,axiom,
    v1(constB166) ).

cnf(clock_pattern_167_1_1,axiom,
    ~ v1(constB167) ).

cnf(clock_pattern_168_1,axiom,
    v1(constB168) ).

cnf(clock_pattern_169_1_1,axiom,
    ~ v1(constB169) ).

cnf(clock_pattern_170_1,axiom,
    v1(constB170) ).

cnf(clock_pattern_171_1_1,axiom,
    ~ v1(constB171) ).

cnf(clock_pattern_172_1,axiom,
    v1(constB172) ).

cnf(clock_pattern_173_1_1,axiom,
    ~ v1(constB173) ).

cnf(clock_pattern_174_1,axiom,
    v1(constB174) ).

cnf(clock_pattern_175_1_1,axiom,
    ~ v1(constB175) ).

cnf(clock_pattern_176_1,axiom,
    v1(constB176) ).

cnf(clock_pattern_177_1_1,axiom,
    ~ v1(constB177) ).

cnf(clock_pattern_178_1,axiom,
    v1(constB178) ).

cnf(clock_pattern_179_1_1,axiom,
    ~ v1(constB179) ).

cnf(clock_pattern_180_1,axiom,
    v1(constB180) ).

cnf(clock_pattern_181_1_1,axiom,
    ~ v1(constB181) ).

cnf(clock_pattern_182_1,axiom,
    v1(constB182) ).

cnf(clock_pattern_183_1_1,axiom,
    ~ v1(constB183) ).

cnf(clock_pattern_184_1,axiom,
    v1(constB184) ).

cnf(clock_pattern_185_1_1,axiom,
    ~ v1(constB185) ).

cnf(clock_pattern_186_1,axiom,
    v1(constB186) ).

cnf(clock_pattern_187_1_1,axiom,
    ~ v1(constB187) ).

cnf(clock_pattern_188_1,axiom,
    v1(constB188) ).

cnf(clock_pattern_189_1_1,axiom,
    ~ v1(constB189) ).

cnf(clock_pattern_190_1,axiom,
    v1(constB190) ).

cnf(clock_pattern_191_1_1,axiom,
    ~ v1(constB191) ).

cnf(clock_pattern_192_1,axiom,
    v1(constB192) ).

cnf(clock_pattern_193_1_1,axiom,
    ~ v1(constB193) ).

cnf(clock_pattern_194_1,axiom,
    v1(constB194) ).

cnf(clock_pattern_195_1_1,axiom,
    ~ v1(constB195) ).

cnf(clock_pattern_196_1,axiom,
    v1(constB196) ).

cnf(clock_pattern_197_1_1,axiom,
    ~ v1(constB197) ).

cnf(clock_pattern_198_1,axiom,
    v1(constB198) ).

cnf(clock_pattern_199_1_1,axiom,
    ~ v1(constB199) ).

cnf(clock_pattern_200_1,axiom,
    v1(constB200) ).

%------------------------------------------------------------------------------
