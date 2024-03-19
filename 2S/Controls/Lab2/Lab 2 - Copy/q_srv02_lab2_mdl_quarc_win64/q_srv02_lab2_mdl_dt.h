/*
 * q_srv02_lab2_mdl_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_srv02_lab2_mdl".
 *
 * Model version              : 5.4
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Tue Feb 27 15:16:16 2024
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_task),
  sizeof(t_card),
  sizeof(t_boolean)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_task",
  "t_card",
  "t_boolean"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o1), 0, 0, 24 }
  ,

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[0]), 0, 0, 14 },

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Task), 14, 0, 1 },

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILReadEncoder_PWORK), 11, 0, 5 },

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILInitialize_ClockModes), 6, 0, 6 },

  { (char_T *)(&q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[0]), 16, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_srv02_lab2_mdl_P.K_AMP), 0, 0, 8 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILReadEncoder_channels), 7, 0, 6 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILInitialize_OOTerminate), 0, 0, 32 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILInitialize_CKChannels), 6, 0, 5 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILInitialize_AIChannels[0]), 7, 0, 10 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILInitialize_Active), 8, 0, 39 },

  { (char_T *)(&q_srv02_lab2_mdl_P.HILReadAnalogTimebase_OverflowM), 3, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  7U,
  rtPTransitions
};

/* [EOF] q_srv02_lab2_mdl_dt.h */
